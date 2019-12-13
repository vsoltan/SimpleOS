
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
   display->drawBitmap(this->x, this->y, this->icon, this->width, this->height, this->color);
}

uint8_t Icon::getDestinationDescriptor() {
  return this->destinationDescriptor;  
}

//Icon **generateHomeIcons() {
//  Icon *homeIcons[3] = { new Icon(20, 60, 16, 16, heart, "Health", HOME_D, RED), new Icon(55, 60, 16, 16, heart, "Stopwatch", SWATCH_D, RED), new Icon(90, 60, 16, 16, heart, "Music", HOME_D, RED) };
//  return homeIcons;
//}
//
//Icon **generateStopwatchIcons() {
//  Icon *stopWatch[3] = { new Icon(20, 60, 16, 16, heart, "Start/Stop", SWATCH_D, BLUE), new Icon(55, 60, 16, 16, heart, "Clear", SWATCH_D, BLUE), new Icon(90, 60, 16, 16, heart, "Back", HOME_D, BLUE) };
//  return stopWatch;
//}
//
//Icon **generateMusicControlIcons() {
//  Icon *musicControl[3] = { new Icon(20, 60, 16, 16, heart, "Start/Stop", SWATCH_D, GREEN), new Icon(55, 60, 16, 16, heart, "Clear", SWATCH_D, GREEN), new Icon(90, 60, 16, 16, heart, "Back", HOME_D, GREEN) };
//  return musicControl;
//}

//Icon ***generateAllApps() {
//  Icon **allApps[3];
//
//  allApps[HOME_D] = generateHomeIcons();
//  allApps[SWATCH_D] = generateStopwatchIcons();
//  allApps[MUSIC_D] = generateMusicControlIcons();
//
//  return allApps;
//}

void drawHomeScreen(ColorDisplay *display) {
  
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
