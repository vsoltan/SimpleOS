
#include "graphics.h"

//display->drawStr((UIScreenWidth - widthScale * getStringWidth(&u8g2, staticTime))/2, centerHeight, "Hello World!");

void drawHomeScreen(OLED *display, RTCData *rtcda) {
    display->clearBuffer();
    display->sendBuffer();
}

void updateScreen(OLED *display, DisplayInfo *info, RTC_Millis *rtc) {
  switch (info->currPage) {
    case HOME:
      getTime(rtc, rtcda->timeStamp);
      display->clearBuffer();      
      display->setFont(u8g2_font_ncenB08_tr); 
      display->drawStr(0, centerHeight, rtcda->timeStamp);
      display->drawStr(0, centerHeight + PADDING, rtcda->date);
      display->sendBuffer();         
      rtcda->timeStamp[0] = '\0'; // clear buffer
      break;
    case STOPWATCH:
      break;
  }
}
