
#include "graphics.h"
#include "ble.h"

#ifndef APPLICATIONS_H_
#define APPLICATIONS_H_

#define STOP_START 0
#define CLEAR 1

class Window {
  
  private:
  
    Icon **applications;

  public:
  
    Window(Icon **applications);
    Icon **getApplications();
    void setApplications(Icon **newApps);

};

void navigate(RotaryEncoder *encoder, Icon **icons, int *pos, uint8_t size);


void updateScreenOnClick(ColorDisplay *display, DisplayInfo *info, Window *window, BLECharacteristic *pTxCharacteristic, bool *deviceConnected);

void updateScreenTime(ColorDisplay *display, RTCData *rtcda, RTC_Millis *rtc);


void drawScreen(ColorDisplay *display, DisplayInfo *info, Window *window, RTCData *rtcda, RTC_Millis *rtc);

void updateStopwatch(uint8_t flag);

void updateMusic(uint8_t flag, BLECharacteristic *pTxCharacteristic, bool *deviceConnected);

#endif
