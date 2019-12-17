
#include "display.h"
#include "applications.h"

Window::Window(Icon **applications) {
    this->applications = applications;
}

Icon **Window::getApplications() {
    return this->applications;
}

void Window::setApplications(Icon **newApps) {
    this->applications = newApps;
}

AppStatus *initAppStatus(bool *deviceConnected, JSONVar *weatherObj, bool *weatherDataReceived, bool *newWeatherData) {
    AppStatus *appInfo = NULL;
    appInfo = (AppStatus *) malloc(sizeof(AppStatus));

    if (appInfo == NULL) {
        exit(EXIT_FAILURE);
    }

    appInfo->stopwatchRunning = 0;
    appInfo->musicPlaying = false;
    appInfo->bluetoothConnection = deviceConnected;
    appInfo->stopWatchStartTime = 0;
    appInfo->stopWatchCurrTime = 0;
    appInfo->stopWatchPauseTime = 0;
    appInfo->stopWatchRunning = false;
    appInfo->weatherObj = weatherObj;
    appInfo->weatherDataReceived = weatherDataReceived;
    appInfo->newWeatherData = newWeatherData;

    return appInfo;
}

void showBluetoothStatus(ColorDisplay *display, AppStatus *appStatus) {
    if (*appStatus->bluetoothConnection) {
        showBluetoothConnected(display);
    } else {
        showBluetoothDisconnected(display);
    }
}

void navigate(RotaryEncoder *encoder, Icon **icons, int *pos, uint8_t size) {

    int newPos = encoder->getPosition();

    if (*pos != newPos) {
        icons[bidirMod(newPos, size)]->renderHighlight(&tft);
        icons[bidirMod(*pos, size)]->removeHighlight(&tft);
    }

    *pos = newPos;
}

void runStopWatch(ColorDisplay *display, AppStatus *appStatus) {
    display->setTextSize(2);
    display->setCursor(16, 20);
    display->setTextColor(WHITE, DEFAULT_BACKGROUND);
    displayFormatedStopwatch(display, appStatus->stopWatchCurrTime);
}

uint8_t getCurrentIconDestination(Window *window, int *pos, DisplayInfo *info, uint8_t *numApps) {
    return window->getApplications()[bidirMod(*pos, numApps[info->currPage])]->getDestinationDescriptor();
}

void updateScreenTime(ColorDisplay *display, RTCData *rtcda, RTC_Millis *rtc) {
    display->fillRect(0, 15, 128, 40, DEFAULT_BACKGROUND);
    display->setCursor(TIME_CENTER, 30);
    getTime(rtc, rtcda->timeStamp);
    display->setTextColor(DEFAULT_TEXT_COLOR, DEFAULT_BACKGROUND);
    display->print(rtcda->timeStamp);
    rtcda->timeStamp[0] = '\0'; // clear buffer
}

// TODO implement stopwatch app
void updateStopwatch(uint8_t flag, AppStatus *appStatus, ColorDisplay *display, Window *window) {
    switch(flag) {
        case STOP_START:
            if (appStatus->stopWatchRunning) {
                appStatus->stopWatchRunning = false;
                appStatus->stopWatchStartTime = millis();
                window->getApplications()[flag]->setIcon(play_bits);
                window->getApplications()[flag]->setColor(BLUE);
            } else {
                appStatus->stopWatchRunning = true;
                appStatus->stopWatchStartTime = millis() - appStatus->stopWatchCurrTime;
                window->getApplications()[flag]->setIcon(stop_bits);
                window->getApplications()[flag]->setColor(RED);
            }
            display->fillRect(26, 60, 24, 24, DEFAULT_BACKGROUND);
            drawPageIcons(window->getApplications(), display, 3);
            break;
        case CLEAR:
            if (appStatus->stopWatchRunning) {
                window->getApplications()[0]->setIcon(play_bits);
                window->getApplications()[0]->setColor(BLUE);
                display->fillRect(26, 60, 24, 24, DEFAULT_BACKGROUND);
                drawPageIcons(window->getApplications(), display, 3); 
            }
            appStatus->stopWatchCurrTime = 0;
            appStatus->stopWatchRunning = false;
            display->setTextSize(2);
            display->setCursor(SWATCH_CENTER, 20);
            display->setTextColor(WHITE, DEFAULT_BACKGROUND);
            display->print("00:00:00");
            break;  
        default:
            break;
    }
}

void updateMusic(uint8_t flag, Window *window, BLECharacteristic *pTxCharacteristic, AppStatus *appStatus, ColorDisplay *display) {

    if (*appStatus->bluetoothConnection) {
        // play or pause pressed
        if (flag == 1) {
          if (appStatus->musicPlaying) {
            window->getApplications()[flag]->setIcon(play_bits);
          } else {
            window->getApplications()[flag]->setIcon(pause_bits);
          }
          appStatus->musicPlaying = !(appStatus->musicPlaying);
        }
        pTxCharacteristic->setValue(&flag, 1);
        pTxCharacteristic->notify();

        display->fillRect(55, 55, 24, 24, DEFAULT_BACKGROUND);
        drawPageIcons(window->getApplications(), display, 4);

    } else {
        perror("not connected to a bluetooth device");
    }
}

void drawScreen(ColorDisplay *display, DisplayInfo *info, Window *window, RTCData *rtcda, RTC_Millis *rtc, uint8_t numIcons, AppStatus *appStatus) {
    display->setTextSize(1);
    display->fillScreen(DEFAULT_BACKGROUND);
    drawPageIcons(window->getApplications(), display, numIcons);

    switch(info->currPage) {
        case HOME_D:
            display->setFont(DEFAULT_FONT);
            updateScreenTime(display, rtcda, rtc);
            drawHomeScreen(display, appStatus);
            break;

        case SWATCH_D:
            drawStopWatchScreen(display, appStatus);
            break;

        case MUSIC_D:
            drawMusicScreen(display, appStatus);
            break;

        case WEATHER_D:
            // won't have weather data without connection
            if (appStatus->bluetoothConnection) {
              drawWeatherScreen(display, appStatus);  
            }
            break;
        
        default:
            break;
     }
}

void updateScreenOnClick(ColorDisplay *display, DisplayInfo *info, Window *window, BLECharacteristic *pTxCharacteristic, AppStatus *appStatus) {
    switch(info->currPage) {
        case SWATCH_D:
            updateStopwatch(info->currIcon, appStatus, display, window);
            break;

         case MUSIC_D:
            updateMusic(info->currIcon, window, pTxCharacteristic, appStatus, display);
            break;

        default:
            break;
    }
}
