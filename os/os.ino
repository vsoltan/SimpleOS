
#include "graphics.h"
#include "buttons.h"
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

BLEServer *pServer = NULL;
BLECharacteristic *pTxCharacteristic;
bool deviceConnected = false;
//bool oldDeviceConnected = false;
uint8_t txValue = 0;

Icon *homeIcons[3] = { new Icon(20, 60, 16, 16, heart, "Weather", HOME_D, RED), new Icon(55, 60, 16, 16, heart, "Stopwatch", SWATCH_D, RED), new Icon(90, 60, 16, 16, heart, "Music", MUSIC_D, RED) };
Icon *stopWatch[3] = { new Icon(20, 60, 16, 16, heart, "Start/Stop", SWATCH_D, BLUE), new Icon(55, 60, 16, 16, heart, "Clear", SWATCH_D, BLUE), new Icon(90, 60, 16, 16, heart, "Back", HOME_D, BLUE) };
Icon *musicControl[3] = { new Icon(20, 60, 16, 16, heart, "Previous", MUSIC_D, GREEN), new Icon(55, 60, 16, 16, heart, "Stop/Play", MUSIC_D, GREEN), new Icon(90, 60, 16, 16, heart, "FastForward", HOME_D, GREEN) };

Icon **allApps[3] = {homeIcons, stopWatch, musicControl};

uint8_t numApps[3] = {3, 3, 3};

// GLOBALS

volatile unsigned long lastclick_time = 0;
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

    if (pTxCharacteristic == NULL) {
      Serial.println("fuck me"); 
    }
}

// INITIALIZERS

unsigned long lastPowerPress = 0;
unsigned long lastNavPress = 0;

byte prev_pwr_state = 1;
byte prev_nav_state = 1;

uint8_t currMin = rtc.now().minute();
uint8_t rotatingDescriptor = HOME_D;

// update screen based on which window is open

void loop() {
  encoder.tick();

  // keeps track of 
  tftInfo->currIcon = pos;

  navigate(&encoder, window->getApplications(), &pos, numApps[tftInfo->currPage]);

  // only update screen when time is updated
  if (tftInfo->currPage == HOME_D && currMin != rtc.now().minute()) {
    updateScreenTime(&tft, rtcda, &rtc);
    currMin = rtc.now().minute();
  }

  // gets the destination descriptor 
  rotatingDescriptor = window->getApplications()[bidirMod(pos, numApps[tftInfo->currPage])]->getDestinationDescriptor();

  byte curr_pwr_state = digitalRead(POWERBUTTON);
  byte curr_nav_state = digitalRead(NAV_BUTTON);

  if (curr_pwr_state == 0 && prev_pwr_state == 1 && millis() >= lastPowerPress + DEBOUNCE) {
      togglePower(tftInfo);
      lastPowerPress = millis();
  }

  if (curr_nav_state == 0 && prev_nav_state == 1 && millis() >= lastNavPress + DEBOUNCE * 5) {

    Serial.println(deviceConnected);

    if (rotatingDescriptor != tftInfo->currPage) {
      tftInfo->currPage = rotatingDescriptor;
      pos = 0;
      window->setApplications(allApps[tftInfo->currPage]);
      drawScreen(&tft, tftInfo, window, rtcda, &rtc);
    } else {
      updateScreenOnClick(&tft, tftInfo, window, pTxCharacteristic, &deviceConnected);
    }
    
    lastPowerPress = millis();
  }

  prev_pwr_state = curr_pwr_state;
  prev_nav_state = curr_nav_state;
}
