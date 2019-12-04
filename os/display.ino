
void initializeDisplay(OLED *display) {
  display->begin();
  display->setBusClock(BUS_CLOCK);
  display->setFont(DEFAULT_FONT);
}

DisplayStatus * createDisplayStatus() {
    DisplayStatus *watchDisplay = NULL;
    watchDisplay = (DisplayStatus *) malloc(sizeof(DisplayStatus));

    if (watchDisplay == NULL) {
      exit(EXIT_FAILURE);
    }

    watchDisplay->displayOn = 1;
    return watchDisplay;
}

void wakeDisplay(OLED *display) {
  display->setPowerSave(0);
}

void sleepDisplay(OLED *display) {
  display->setPowerSave(1);
}

void togglePower(bool displayOn, OLED *display) {
  if (displayOn) {
      sleepDisplay(display);
  } else {
      wakeDisplay(display);
  }
}

uint8_t getStringWidth(OLED *display, const char *string) {
  return display->getUTF8Width(string);
}
