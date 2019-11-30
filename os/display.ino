
Adafruit_SSD1306 * initializeDisplay() {
    Adafruit_SSD1306 lcd(UIScreenWidth, UIScreenHeight);
    lcd.begin(SSD1306_SWITCHCAPVCC, 0x3C);
    lcd.setTextColor(WHITE);
    lcd.setTextSize(2);
    lcd.setCursor(0,0);
    lcd.clearDisplay();
    lcd.println(staticTime);
    lcd.display();
    return &lcd;
}

display * createDisplay() {
    display watchDisplay = {
        .displayOn = 1,
        .lcd = initializeDisplay(),
    };
    return &watchDisplay;
}

void wakeDisplay(Adafruit_SSD1306* display) {
    display->ssd1306_command(SSD1306_DISPLAYON);
}

void sleepDisplay(Adafruit_SSD1306* display) {
    display->ssd1306_command(SSD1306_DISPLAYOFF);
}

void togglePower(display *watchDisplay) {
  if (watchDisplay->displayOn) {
    sleepDisplay(watchDisplay->lcd);
   } else {
    wakeDisplay(watchDisplay->lcd);
   }
   watchDisplay->displayOn = !watchDisplay->displayOn;
}
