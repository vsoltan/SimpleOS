
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

typedef struct {
    byte stopwatchRunning;
    byte musicPlaying;
    bool *bluetoothConnection;
} AppStatus;

AppStatus *initAppStatus(bool *deviceConnected);

// NAVIGATION

void navigate(RotaryEncoder *encoder, Icon **icons, int *pos, uint8_t size);
uint8_t getCurrentIconDestination(Window *window, int *pos, DisplayInfo *info, uint8_t *numApps);

// RENDERING

void drawScreen(ColorDisplay *display, DisplayInfo *info, Window *window, RTCData *rtcda, RTC_Millis *rtc, uint8_t numIcons);

// SCREEN UPDATES

void updateScreenTime(ColorDisplay *display, RTCData *rtcda, RTC_Millis *rtc);

void updateScreenOnClick(ColorDisplay *display, DisplayInfo *info, Window *window, BLECharacteristic *pTxCharacteristic, bool *deviceConnected, AppStatus *appStatus);

void updateStopwatch(uint8_t flag, uint8_t stopwatchRunning);

void updateMusic(uint8_t flag, BLECharacteristic *pTxCharacteristic, bool *deviceConnected);

#endif
