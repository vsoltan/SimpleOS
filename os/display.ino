
#include "display.h"

void initializeDisplay(ColorDisplay *display) {
  display->init();
  setBrightness(255);
  tft.setCursor(20, 30);
  display->fillScreen(ST7735_WHITE);
  display->setTextColor(ST7735_RED);
  display->setFont(DEFAULT_FONT);
  ledcSetup(0, 5000, 8);
  ledcAttachPin(LED, 0);
  display->print(staticTime);
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

  dinfo->displayOn = 0;
  dinfo->currPage = HOME;
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
