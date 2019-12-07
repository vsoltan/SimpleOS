
#include "graphics.h"
#include "buttons.h"
#include "ble.h"

#define BAUD 115200

// UTILITIES

ColorDisplay tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
RotaryEncoder encoder(EDA, ECLK);

DisplayInfo *tftInfo;
Icon *pageIcons[2];


//RTC_Millis rtc;
//RTCData *rtcda;


// GLOBALS

volatile unsigned long lastclick_time = 0;
unsigned timeUpdateTick = 0;
static int pos = 0;

int16_t x1, ya;
uint16_t w, h;
     
void setup() {
    Serial.begin(BAUD);
    initializeDisplay(&tft);
    initBLE();
    tftInfo = createDisplayInfo();

    pageIcons[0] = new Icon(20, 60, 16, 16, heart, "Health");
    pageIcons[1] = new Icon(50, 60, 16, 16, heart, "Stopwatch");
    pageIcons[2] = new Icon(80, 60, 16, 16, heart, "Music");

    pageIcons[0]->drawIcon(&tft);
    pageIcons[1]->drawIcon(&tft);
    pageIcons[2]->drawIcon(&tft);

    Serial.println(bidirMod(-50, 15));

//    tft.getTextBounds(staticTime, 20, 30, &x1, &ya, &w, &h);
//    Serial.println(w);

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
    Serial.print(bidirMod(newPos, 3));
    pageIcons[bidirMod(newPos, 3)]->renderHighlight(&tft);
    Serial.println();
    pageIcons[bidirMod(pos, 3)]->removeHighlight(&tft);
    pos = newPos;
  } 
}
  
