
#include "graphics.h"
#include "button.h"
#include "ble.h"
#include "applications.h"

#define BAUD 115200

// DISPLAY

ColorDisplay tft = Adafruit_ST7735(TFT_CS,  TFT_DC, TFT_RST);
DisplayInfo *tftInfo;

// ENCODER

RotaryEncoder encoder(EDA, ECLK);
int pos = 0;

// RTC

RTC_Millis rtc;
RTCData *rtcda;

// BUTTONS

Button NAV(HIGH);
unsigned long lastPress = 0;

// BLE and COMMS

BLEServer *pServer = NULL;
BLECharacteristic *pTxCharacteristic;
bool deviceConnected = false;
bool oldDeviceConnected = false;

// WINDOW | APP MANAGEMENT

Window *window;

Icon *homeIcons[3] = { new Icon(20, 60, 16, 16, heart, "Weather", HOME_D, RED), new Icon(55, 60, 16, 16, heart, "Stopwatch", SWATCH_D, RED), new Icon(90, 60, 16, 16, heart, "Music", MUSIC_D, RED) };
Icon *stopWatch[3] = { new Icon(20, 60, 16, 16, heart, "Start/Stop", SWATCH_D, BLUE), new Icon(55, 60, 16, 16, heart, "Clear", SWATCH_D, BLUE), new Icon(90, 60, 16, 16, heart, "Back", HOME_D, BLUE) };
Icon *musicControl[4] = { new Icon(20, 60, 16, 16, heart, "Previous", MUSIC_D, GREEN), new Icon(55, 60, 16, 16, heart, "Stop/Play", MUSIC_D, GREEN), new Icon(90, 60, 16, 16, heart, "FastForward", MUSIC_D, GREEN), new Icon(55, 95, 16, 16, heart, "Stop/Play", HOME_D, RED) };

Icon **allApps[3] = {homeIcons, stopWatch, musicControl};
uint8_t numApps[3] = {3, 3, 4};

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

    appStatus = initAppStatus(&deviceConnected);
}

uint8_t currMin = getMinute(&rtc);
uint8_t rotatingDescriptor = HOME_D;

void loop() {

    encoder.tick();

    tftInfo->currIcon = pos;

    navigate(&encoder, window->getApplications(), &pos, numApps[tftInfo->currPage]);

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
                if (millis() > lastPress + DEBOUNCE) {
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
                    lastPress = millis();
                }
                break;

            case HELD:
                if (tftInfo->displayOn) {
                    togglePower(tftInfo);
                }
                break;

            case RELEASED:
                lastPress = millis();
                break;

            default:
                break;
        }
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
        showBluetoothConnected(&tft);
        oldDeviceConnected = deviceConnected;
    }
}
