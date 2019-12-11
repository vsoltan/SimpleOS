
#include "graphics.h"

#ifndef APPLICATIONS_H_
#define APPLICATIONS_H_

class Window {
  
  private:
    Icon **applications;

  public:
    Window(Icon **applications);
    Icon **getApplications();
    void setApplications(Icon **newApps);

};

void navigate(RotaryEncoder *encoder, Icon **icons, int *pos);


void updateScreenOnClick(ColorDisplay *display, DisplayInfo *info, Window *window);

void drawScreen(ColorDisplay *display, DisplayInfo *info, Window *window);

// add RTC as param
void updateScreenPeriodically();

//      getTime(rtc, rtcda->timeStamp);      
//      display->drawStr(0, centerHeight, rtcda->timeStamp);
//      display->drawStr(0, centerHeight + PADDING, rtcda->date);
//      rtcda->timeStamp[0] = '\0'; // clear buffer

#endif
