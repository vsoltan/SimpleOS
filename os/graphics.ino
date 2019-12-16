
#include "graphics.h"

Icon::Icon(uint8_t x, uint8_t y, uint8_t width, uint8_t height, const unsigned char *icon, const char *label, uint8_t descriptor, uint16_t color) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->icon = icon;
    this->label = label;
    this->destinationDescriptor = descriptor;
    this->color = color;
}

uint8_t Icon::getX() {
    return this->x;
}

uint8_t Icon::getY() {
    return this->y;
}

uint8_t Icon::getWidth() {
    return this->width;
}

uint8_t Icon::getHeight() {
    return this->height;
}

const char *Icon::getLabel() {
    return this->label;
}

void Icon::renderHighlight(ColorDisplay *display) {
  // set colored border to indicate icon is selected
    display->drawRect(this->x - highlightPadding, this->y - highlightPadding, this->width + 2 * highlightPadding, this->height + 2 * highlightPadding, DEFAULT_HIGHLIGHT);
}

void Icon::removeHighlight(ColorDisplay *display) {
    display->drawRect(this->x - highlightPadding, this->y - highlightPadding, this->width + 2 * highlightPadding, this->height + 2* highlightPadding, DEFAULT_BACKGROUND);
}

void Icon::drawIcon(ColorDisplay *display) {
    display->drawXBitmap(this->x, this->y, this->icon, this->width, this->height, this->color);
}

void Icon::setIcon(const unsigned char *newIcon) {
    this->icon = newIcon;
}

uint8_t Icon::getDestinationDescriptor() {
    return this->destinationDescriptor;
}

void showBluetoothConnected(ColorDisplay *display) {
    display->drawCircle(7, 7, 3, WHITE);
}

void showBluetoothDisconnected(ColorDisplay *display) {
    display->drawCircle(7, 7, 3, DEFAULT_BACKGROUND);
}

void drawHomeScreen(ColorDisplay *display, AppStatus *appStatus) {
    showBluetoothStatus(display, appStatus);
}

void drawWeatherScreen(ColorDisplay *display, AppStatus *appStatus) {
    if (appStatus->weatherObj != NULL) {
        display->setFont();
        
        display->setCursor(20, 20);
        display->print((*appStatus->weatherObj)["weather"][0]["main"]);

        display->setCursor(20, 30);
        display->print("temp: ");
        display->print(weatherObj["main"]["temp"]);

        display->setCursor(20, 40);
        display->print("temp-max: ");
        display->print(weatherObj["main"]["temp_max"]);

        display->setCursor(20, 50);
        display->print("temp-min: ");
        display->println(weatherObj["main"]["temp_min"]);
    }
}

void displayFormatedStopwatch(ColorDisplay *display, unsigned long t) {
    int minutes = (t / 1000) / 60;
    int seconds = (t / 1000) % 60;
    int milliseconds = (t % 1000) / 10;

    display->print(minutes / 10);
    display->print(minutes % 10);
    display->print(":");
    display->print(seconds / 10);
    display->print(seconds % 10);
    display->print(":");
    display->print(milliseconds / 10);
    display->print(milliseconds % 10);
}

void drawStopWatchScreen(ColorDisplay *display, AppStatus *appStatus) {
    showBluetoothStatus(display, appStatus);
    display->setFont();
    display->setTextSize(2);
    display->setCursor(SWATCH_CENTER, 20);
    if (appStatus->stopWatchCurrTime != 0) {
      displayFormatedStopwatch(display, appStatus->stopWatchCurrTime);
    } else {
      display->print("00:00:00");
    }
}

void drawMusicScreen(ColorDisplay *display, AppStatus *appStatus) {
    showBluetoothStatus(display, appStatus);
    display->setFont(DEFAULT_FONT);
    display->setCursor(30, 20);
    display->print("Music");
}

void drawPageIcons(Icon **appIcons, ColorDisplay *display, uint8_t numIcons) {
    Serial.println(sizeof(appIcons) / sizeof(appIcons[0]));
    for (int i = 0; i < numIcons; i = i + 1) {
        appIcons[i]->drawIcon(display);
    }
}
