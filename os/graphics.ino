
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

void drawHomeScreen(ColorDisplay *display, AppStatus *appInfo) {
    showBluetoothStatus(display, appStatus);
}

void drawStopWatchScreen(ColorDisplay *display, AppStatus *appInfo) {
    showBluetoothStatus(display, appStatus);
    // return to stock font
    display->setFont();
    display->setTextSize(2);
    display->setCursor(16, 20);
    display->print("00:00:00");
}

void drawMusicScreen(ColorDisplay *display, AppStatus *appInfo) {
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
