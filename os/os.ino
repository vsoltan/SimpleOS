
#include "graphics.h"
#include "buttons.h"
#include "ble.h"
#include "applications.h"

#define BAUD 115200

// UTILITIES

ColorDisplay tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
RotaryEncoder encoder(EDA, ECLK);

DisplayInfo *tftInfo;
Icon *homeIcons[3] = { new Icon(20, 60, 16, 16, heart, "Health"), new Icon(50, 60, 16, 16, heart, "Stopwatch"), new Icon(80, 60, 16, 16, heart, "Music") };
Icon *stopWatch[3] = { new Icon(20, 60, 16, 16, heart, "Start/Stop"), new Icon(50, 60, 16, 16, heart, "Clear"), new Icon(80, 60, 16, 16, heart, "Back") };
//Icon *pageIcons[3];


//RTC_Millis rtc;
//RTCData *rtcda;


// GLOBALS

volatile unsigned long lastclick_time = 0;
unsigned timeUpdateTick = 0;
int pos = -1;

int16_t x1, ya;
uint16_t w, h;
     
void setup() {
    Serial.begin(BAUD);
    initializeDisplay(&tft);
    drawPageNav(homeIcons, &tft);
    initBLE();
    tftInfo = createDisplayInfo();

//    drawHomeScreen(&u8g2, rtcda);
//    initRTC(&rtc);
//    rtcda = setRTCData(&rtc);

}

// INITIALIZERS

long lastButtonPress = 0;
byte prev_state = 1;

void loop() {
  encoder.tick();
    
//  updateScreen(&u8g2, oledInfo, &rtc);

  byte curr_state = digitalRead(POWERBUTTON);
  if (curr_state == 0 && prev_state == 1 && millis() >= lastButtonPress + DEBOUNCE) {
      togglePower(tftInfo);
      lastButtonPress = millis();
  }
  prev_state = curr_state;

  navigate(&encoder, homeIcons, &pos);
}
  
