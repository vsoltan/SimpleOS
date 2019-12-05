
#include "display.h"

void initializeDisplay(OLED *display) {
  display->begin();
  display->setBusClock(BUS_CLOCK);
  display->setFont(DEFAULT_FONT);
}

void wakeDisplay(OLED *display) {
  Serial.println("WAKE");
  display->setPowerSave(0);
}

void sleepDisplay(OLED *display) {
  Serial.println("SLEEP");
  display->setPowerSave(1);
}

DisplayInfo *createDisplayInfo() {
  DisplayInfo *dinfo = NULL;
  dinfo = (DisplayInfo *) malloc(sizeof(DisplayInfo));

  if (dinfo == NULL) {
    exit(EXIT_FAILURE);
  }

  dinfo->displayOn = 1;
  dinfo->currPage = HOME;

  return dinfo;
}

void togglePower(byte displayOn, OLED *display) {
  if (displayOn) {
      sleepDisplay(display);
  } else {
      wakeDisplay(display);
  }
}

uint8_t getStringWidth(OLED *display, const char *string) {
  return display->getUTF8Width(string);
}
