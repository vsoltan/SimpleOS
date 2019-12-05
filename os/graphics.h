
#include "display.h"
#include "utils.h"

#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#define HOME_PAGE 1
#define STOP_WATCH_PAGE 2

// APPLICATION ASSETS
#define STOP_WATCH_ICON 0x23F1

void drawHomeScreen(OLED *display, RTCData *rtcda);

void updateScreen(OLED *display, DisplayInfo *info, RTC_Millis *rtc);

#endif
