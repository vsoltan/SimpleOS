
#include "graphics.h"

Icon::Icon(uint8_t x, uint8_t y, uint8_t width, uint8_t height, const unsigned char *icon, const char *label, uint8_t descriptor) {
    this->x = x;
    this->y = y; 
    this->width = width;
    this->height = height;
    this->icon = icon;
    this->label = label;
    this->destinationDescriptor = descriptor;
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
   display->drawBitmap(this->x, this->y, this->icon, this->width, this->height, DEFAULT_ICON_COLOR);
}

uint8_t Icon::getDestinationDescriptor() {
  return this->destinationDescriptor;  
}

void drawHomeScreen(ColorDisplay *display) {
  display->setCursor(20, 30);
  display->print(staticTime);
}

void drawStopWatchScreen(ColorDisplay *display) {
  display->setCursor(0, 20);
  display->print("00:00:00");
}

void drawPageIcons(Icon **appIcons, ColorDisplay *display) {
  for (int i = 0; i < 3; i = i + 1) {
    appIcons[i]->drawIcon(display);
  }
}
