
#include "display.h"
#include "utils.h"

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

// APPLICATION ASSETS
#define STOP_WATCH_ICON 0x23F1

void drawHomeScreen(ColorDisplay *display, RTCData *rtcda);

void updateScreen(ColorDisplay *display, DisplayInfo *info, RTC_Millis *rtc);

const unsigned char PROGMEM heart[] =

{ B00000000, B00000000,
  B00000000, B00000000,
  B00111100, B00111100,
  B01111110, B11111110,
  B11111111, B11111111,
  B11111111, B11111111,
  B01111111, B11111110,
  B00111111, B11111100,
  B00011111, B11111000,
  B00001111, B11110000,
  B00000111, B11100000,
  B00000011, B11000000,
  B00000001, B10000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000

};






#endif
