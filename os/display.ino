
#include "display.h"

void initializeDisplay(ColorDisplay *display) {
    display->init();
    display->setRotation(2);
    display->setCursor(TIME_CENTER, 30);
    display->fillScreen(DEFAULT_BACKGROUND);
    display->setTextColor(DEFAULT_TEXT_COLOR);
    display->setFont(DEFAULT_FONT);
    ledcSetup(0, 5000, 8);
    ledcAttachPin(LCD, 0);
    setBrightness(255);
}

void setBrightness(uint8_t value) {
    ledcWrite(0, value);
}

void wakeDisplay(DisplayInfo *info) {
    setBrightness(info->brightness);
}

void sleepDisplay() {
    setBrightness(0);
}

DisplayInfo *createDisplayInfo() {
    DisplayInfo *dinfo = NULL;
    dinfo = (DisplayInfo *) malloc(sizeof(DisplayInfo));

    if (dinfo == NULL) {
        exit(EXIT_FAILURE);
    }

    dinfo->displayOn = 1;
    dinfo->currPage = HOME_D;
    dinfo->currIcon = 1;
    dinfo->brightness = 255;

    return dinfo;
}

void togglePower(DisplayInfo *info) {
    if (info->displayOn) {
      sleepDisplay();
    } else {
      wakeDisplay(info);
    }
    info->displayOn = !info->displayOn;
}
