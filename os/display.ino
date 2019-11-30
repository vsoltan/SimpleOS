
char *statictime = "12:54";

void initializeDisplay(Adafruit_SSD1306 *lcd) {
    lcd->begin(SSD1306_SWITCHCAPVCC, 0x3C);
    lcd->setTextColor(WHITE);
    lcd->setTextSize(TextSize);
    lcd->clearDisplay();
    lcd->setCursor(centerWidth, centerHeight);
    lcd->println(staticTime);
    lcd->display();
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

void wakeDisplay(Adafruit_SSD1306* display) {
    display->ssd1306_command(SSD1306_DISPLAYON);
}

void sleepDisplay(Adafruit_SSD1306* display) {
    display->ssd1306_command(SSD1306_DISPLAYOFF);
}

void togglePower(DisplayStatus *watchDisplay, Adafruit_SSD1306 *lcd) {
  Serial.println(watchDisplay->displayOn);
  if (watchDisplay->displayOn) {
      sleepDisplay(lcd);
  } else {
      wakeDisplay(lcd);
  }
  watchDisplay->displayOn = !watchDisplay->displayOn;
}
