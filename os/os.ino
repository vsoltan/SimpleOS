
#include "graphics.h"
#include "ble.h"
#include "applications.h"

// DISPLAY

ColorDisplay tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
DisplayInfo *tftInfo;

// ENCODER

RotaryEncoder encoder(EDA, ECLK);
int pos = 0;
int oldPos = 0;

// RTC

RTC_Millis rtc;
RTCData *rtcda;

// BUTTONS

Button NAV(HIGH);
unsigned long lastButtonPress = 0;

// BLE and COMMS

BLEServer *pServer = NULL;
BLECharacteristic *pTxCharacteristic;

// TODO make this all a struct

bool deviceConnected = false;
bool oldDeviceConnected = false;
bool weatherDataReceived;
bool weatherLoaded = false;
bool newWeatherData = false;

JSONVar weatherObj;

// WINDOW | APP MANAGEMENT

Window *window;

Icon *homeIcons[3] = { new Icon(14, 60, 24, 24, weather_bits, "Weather", WEATHER_D, CYAN), new Icon(52, 60, 24, 24, swatch_bits, "Stopwatch", SWATCH_D, ORANGE), new Icon(90, 60, 24, 24, music_bits, "Music", MUSIC_D, YELLOW) };
Icon *stopWatch[3] = { new Icon(26, 60, 24, 24, play_bits, "Start/Stop", SWATCH_D, BLUE), new Icon(76, 60, 24, 24, reset_bits, "Clear", SWATCH_D, ORANGE), new Icon(56, 95, 16, 16, back_bits, "Back", HOME_D, RED) };
Icon *musicControl[5] = { new Icon(10, 60, 16, 16, prev_track_bits, "Previous", MUSIC_D, GREEN), new Icon(52, 55, 24, 24, play_bits, "Stop/Play", MUSIC_D, GREEN), new Icon(102, 60, 16, 16, next_track_bits, "FastForward", MUSIC_D, GREEN), new Icon(32, 95, 16, 16, back_bits, "Stop/Play", HOME_D, RED), new Icon(80, 95, 16, 16, volume_bits, "Volume", MUSIC_D, WHITE) };
Icon *weatherIcons[1] = { new Icon(56, 95, 16, 16, back_bits, "Back", HOME_D, RED)};

Icon **allApps[4] = {homeIcons, stopWatch, musicControl, weatherIcons};
uint8_t numApps[4] = {3, 3, 5, 1};

AppStatus *appStatus;

void setup() {
    Serial.begin(BAUD);

    initializeDisplay(&tft);
    tftInfo = createDisplayInfo();

    initRTC(&rtc);
    rtcda = setRTCData(&rtc);

    window = new Window(allApps[HOME_D]);

    updateScreenTime(&tft, rtcda, &rtc);
    drawPageIcons(window->getApplications(), &tft, numApps[HOME_D]);

    initBLE(&pServer, &pTxCharacteristic);
    initNavButton(&NAV);

    appStatus = initAppStatus(&deviceConnected, &weatherObj, &weatherDataReceived, &newWeatherData);
}

uint8_t currMin = getMinute(&rtc);
uint8_t rotatingDescriptor = HOME_D;

void loop() {

    encoder.tick();

    if (appStatus->inVolumeControls) {
        updateVolume(&encoder, &oldPos, pTxCharacteristic, appStatus);
    } else {
        navigate(&encoder, window->getApplications(), &pos, numApps[tftInfo->currPage]);
    }

    tftInfo->currIcon = bidirMod(pos, numApps[tftInfo->currPage]);

    // gets the destination descriptor
    rotatingDescriptor = getCurrentIconDestination(window, &pos, tftInfo, numApps);

    // only update screen when time is updated
    if (tftInfo->currPage == HOME_D && currMin != getMinute(&rtc)) {
      updateScreenTime(&tft, rtcda, &rtc);
      currMin = getMinute(&rtc);
    }

    byte navPress = NAV.checkButton(NAV_BUTTON);

    if (navPress) {
        switch (navPress) {
            case PRESSED:
                if (millis() > lastButtonPress + DEBOUNCE) {
                    if (!tftInfo->displayOn) {
                        togglePower(tftInfo);
                    } else {
                        if (rotatingDescriptor != tftInfo->currPage) {
                            tftInfo->currPage = rotatingDescriptor;
                            pos = 0;
                            window->setApplications(allApps[tftInfo->currPage]);
                            drawScreen(&tft, tftInfo, window, rtcda, &rtc, numApps[tftInfo->currPage], appStatus);
                        } else {
                            updateScreenOnClick(&tft, tftInfo, window, pTxCharacteristic, appStatus);
                        }
                    }
                    lastButtonPress = millis();
                }
                break;

            case HELD:
                if (tftInfo->displayOn) {
                    togglePower(tftInfo);
                }
                break;

            case RELEASED:
                lastButtonPress = millis();
                break;

            default:
                break;
        }
    }

    if (appStatus->stopWatchRunning) {
        appStatus->stopWatchCurrTime = millis() - appStatus->stopWatchStartTime;
        encoder.tick();
        if (tftInfo->currPage == SWATCH_D) {
          runStopWatch(&tft, appStatus);
        }
    }

    if (tftInfo->currPage == WEATHER_D && *appStatus->newWeatherData) {
        drawWeatherScreen(&tft, appStatus);
    }

    // BLE on disconnect
    if (!deviceConnected && oldDeviceConnected) {
        showBluetoothDisconnected(&tft);
        delay(500);
        // restart advertising
        pServer->startAdvertising();
        oldDeviceConnected = deviceConnected;
    }

    // BLE on connection
    if (deviceConnected && !oldDeviceConnected) {
        if (tftInfo->currPage != WEATHER_D) {
          showBluetoothConnected(&tft);
        }
        oldDeviceConnected = deviceConnected;
    }
}
