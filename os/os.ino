
#include "graphics.h"
#include "buttons.h"
#include "ble.h"

#define BAUD 115200

// UTILITIES

ColorDisplay tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
RotaryEncoder encoder(EDA, ECLK);
DisplayInfo *tftInfo;

//RTC_Millis rtc;
//RTCData *rtcda;

// GLOBALS

volatile unsigned long lastclick_time = 0;
unsigned timeUpdateTick = 0;
static int pos = 0;

void setup() {
    Serial.begin(BAUD);
    initializeDisplay(&tft);
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

  int newPos = encoder.getPosition();
  if (pos != newPos) {
    Serial.print(newPos);
    Serial.println();
    pos = newPos;

  } 
}
  
