
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

Window **initWindows();

void navigate(RotaryEncoder *encoder, Icon **icons, int *pos);

void updateScreenOnClick(ColorDisplay *display, DisplayInfo *info, Window *window);

void drawScreen(ColorDisplay *display, DisplayInfo *info, Window *window);

// add RTC as param
void updateScreenTime(ColorDisplay *display, RTCData *rtcda, RTC_Millis *rtc);

#endif
