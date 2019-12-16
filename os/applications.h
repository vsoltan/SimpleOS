
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

AppStatus *initAppStatus(bool *deviceConnected, JSONVar *weatherObj);

void showBluetoothStatus(ColorDisplay *display, AppStatus *appStatus);

// NAVIGATION

void navigate(RotaryEncoder *encoder, Icon **icons, int *pos, uint8_t size);

uint8_t getCurrentIconDestination(Window *window, int *pos, DisplayInfo *info, uint8_t *numApps);

// RENDERING

void drawScreen(ColorDisplay *display, DisplayInfo *info, Window *window, RTCData *rtcda, RTC_Millis *rtc, uint8_t numIcons, AppStatus *appStatus);

// SCREEN UPDATES

void updateScreenTime(ColorDisplay *display, RTCData *rtcda, RTC_Millis *rtc);

void updateScreenOnClick(ColorDisplay *display, DisplayInfo *info, Window *window, BLECharacteristic *pTxCharacteristic, AppStatus *appStatus);

void updateMusic(uint8_t flag, BLECharacteristic *pTxCharacteristic, AppStatus *appStatus, ColorDisplay *display);

void runStopWatch(ColorDisplay *display, AppStatus *appStatus);

void updateStopwatch(uint8_t flag, AppStatus *appStatus, ColorDisplay *display);

void showBluetoothConnected(ColorDisplay *display);

void showBluetoothDisconnected(ColorDisplay *display);

#endif
