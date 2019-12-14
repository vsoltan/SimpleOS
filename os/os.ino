
#include "graphics.h"
#include "button.h"
#include "ble.h"
#include "applications.h"

#define BAUD 115200

// UTILITIES

ColorDisplay tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
DisplayInfo *tftInfo;

RotaryEncoder encoder(EDA, ECLK);

RTC_Millis rtc;
RTCData *rtcda;

Window *window;

Button NAV(HIGH);

BLEServer *pServer = NULL;
BLECharacteristic *pTxCharacteristic;
bool deviceConnected = false;
//bool oldDeviceConnected = false;

Icon *homeIcons[3] = { new Icon(20, 60, 16, 16, heart, "Weather", HOME_D, RED), new Icon(55, 60, 16, 16, heart, "Stopwatch", SWATCH_D, RED), new Icon(90, 60, 16, 16, heart, "Music", MUSIC_D, RED) };
Icon *stopWatch[3] = { new Icon(20, 60, 16, 16, heart, "Start/Stop", SWATCH_D, BLUE), new Icon(55, 60, 16, 16, heart, "Clear", SWATCH_D, BLUE), new Icon(90, 60, 16, 16, heart, "Back", HOME_D, BLUE) };
Icon *musicControl[4] = { new Icon(20, 60, 16, 16, heart, "Previous", MUSIC_D, GREEN), new Icon(55, 60, 16, 16, heart, "Stop/Play", MUSIC_D, GREEN), new Icon(90, 60, 16, 16, heart, "FastForward", MUSIC_D, GREEN), new Icon(55, 95, 16, 16, heart, "Stop/Play", HOME_D, RED) };

Icon **allApps[3] = {homeIcons, stopWatch, musicControl};

uint8_t numApps[3] = {3, 3, 4};

int pos = 0;

void setup() {
    Serial.begin(BAUD);
    initializeDisplay(&tft);
    initRTC(&rtc);
    rtcda = setRTCData(&rtc);
    window = new Window(allApps[HOME_D]);
    tftInfo = createDisplayInfo();
    updateScreenTime(&tft,rtcda, &rtc);
    drawPageIcons(window->getApplications(), &tft);
    initBLE(&pServer, &pTxCharacteristic);
    initNavButton(&NAV);
}

uint8_t currMin = rtc.now().minute();
uint8_t rotatingDescriptor = HOME_D;

void loop() {

  encoder.tick();

  tftInfo->currIcon = pos;

  byte myButton = NAV.checkButton(NAV_BUTTON);

  navigate(&encoder, window->getApplications(), &pos, numApps[tftInfo->currPage]);

  // gets the destination descriptor
  rotatingDescriptor = window->getApplications()[bidirMod(pos, numApps[tftInfo->currPage])]->getDestinationDescriptor();

   // only update screen when time is updated
  if (tftInfo->currPage == HOME_D && currMin != rtc.now().minute()) {
      updateScreenTime(&tft, rtcda, &rtc);
      currMin = rtc.now().minute();
  }

  if (myButton) // if myButton is anything but 0, it is true
  {
    switch (myButton)
    {
      case PRESSED:
        if (!tftInfo->displayOn) {
            togglePower(tftInfo);
        } else {
            if (rotatingDescriptor != tftInfo->currPage) {
                 tftInfo->currPage = rotatingDescriptor;
                 pos = 0;
                 window->setApplications(allApps[tftInfo->currPage]);
                 drawScreen(&tft, tftInfo, window, rtcda, &rtc);
               } else {
                 updateScreenOnClick(&tft, tftInfo, window, pTxCharacteristic, &deviceConnected);
               }
        }
        break;
        
      case HELD:
        if (tftInfo->displayOn) {
            togglePower(tftInfo);
        }
        break;
        
      default: break;
    }
  }
}
