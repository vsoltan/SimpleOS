
#include "graphics.h"
#include "buttons.h"
#include "ble.h"
#include "applications.h"

#define BAUD 115200

// UTILITIES

ColorDisplay tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
RotaryEncoder encoder(EDA, ECLK);

DisplayInfo *tftInfo;

Icon *homeIcons[3] = { new Icon(20, 60, 16, 16, heart, "Health", HOME_D), new Icon(55, 60, 16, 16, heart, "Stopwatch", SWATCH_D), new Icon(90, 60, 16, 16, heart, "Music", HOME_D) };
Icon *stopWatch[3] = { new Icon(20, 60, 16, 16, heart, "Start/Stop", SWATCH_D), new Icon(55, 60, 16, 16, heart, "Clear", SWATCH_D), new Icon(90, 60, 16, 16, heart, "Back", HOME_D) };

Icon **apps[2][3] = {homeIcons, stopWatch};

Window *window;

//RTC_Millis rtc;
//RTCData *rtcda;

// GLOBALS

volatile unsigned long lastclick_time = 0;
unsigned timeUpdateTick = 0;
int pos = 0;

void setup() {
    Serial.begin(BAUD);
    initializeDisplay(&tft);
    window = new Window(*apps[0]);
    drawPageIcons(window->getApplications(), &tft);
    initBLE();
    tftInfo = createDisplayInfo();

//    drawHomeScreen(&u8g2, rtcda);
//    initRTC(&rtc);
//    rtcda = setRTCData(&rtc);

}

// INITIALIZERS

long lastPowerPress = 0;
long lastNavPress = 0;

byte prev_pwr_state = 1;
byte prev_nav_state = 1;

uint8_t rotatingDescriptor = HOME_D;

// update screen based on which window is open

void loop() {
  encoder.tick();

  navigate(&encoder, homeIcons, &pos);

  rotatingDescriptor = window->getApplications()[bidirMod(pos, 3)]->getDestinationDescriptor();

  byte curr_pwr_state = digitalRead(POWERBUTTON);
  byte curr_nav_state = digitalRead(NAV_BUTTON);

  if (curr_pwr_state == 0 && prev_pwr_state == 1 && millis() >= lastPowerPress + DEBOUNCE) {
      togglePower(tftInfo);
      lastPowerPress = millis();
  }

  if (curr_nav_state == 0 && prev_nav_state == 1 && millis() >= lastNavPress + DEBOUNCE * 2) {

    if (rotatingDescriptor != tftInfo->currPage) {
      tftInfo->currPage = rotatingDescriptor;
      pos = 0;
      window->setApplications(stopWatch);
      drawScreen(&tft, tftInfo, window);
    } else {
      updateScreenOnClick(&tft, tftInfo, window);
    }
    
    lastPowerPress = millis();
  }

  prev_pwr_state = curr_pwr_state;
  prev_nav_state = curr_nav_state;
}
