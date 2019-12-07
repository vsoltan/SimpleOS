
#include "graphics.h"

Icon::Icon(uint8_t x, uint8_t y, uint8_t width, uint8_t height, const unsigned char *icon, const char *label) {
    this->x = x;
    this->y = y; 
    this->width = width;
    this->height = height;
    this->icon = icon;
    this->label = label;
    this->isHighlighted = false;
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

void Icon::setHighlight(bool value) {
  this->isHighlighted = value; 
}

void Icon::renderHighlight(ColorDisplay *display) {
  // set colored border to indicate icon is selected
    display->drawRect(this->x - highlightPadding, this->y - highlightPadding, this->width + highlightPadding, this->height + highlightPadding, ST7735_RED);
}

void Icon::removeHighlight(ColorDisplay *display) {
  // set colored border to indicate icon is selected
    display->drawRect(this->x - highlightPadding, this->y - highlightPadding, this->width + highlightPadding, this->height + highlightPadding, ST7735_WHITE);
}

void Icon::drawIcon(ColorDisplay *display) {
   display->drawBitmap(this->x, this->y, this->icon, this->width, this->height, ST7735_BLUE);
}

void drawHomeScreen(ColorDisplay *display) {
  display->setCursor(20, 30);
  display->print(staticTime);
}

void navigate(RotaryEncoder *encoder, Icon **icons, int *pos) {
  int newPos = encoder->getPosition();
  if (newPos != *pos) {
    
    *pos = newPos;
  }  
}

void updateScreen(ColorDisplay *display, DisplayInfo *info) {
  switch (info->currPage) {
    case HOME:
//      getTime(rtc, rtcda->timeStamp);      
//      display->drawStr(0, centerHeight, rtcda->timeStamp);
//      display->drawStr(0, centerHeight + PADDING, rtcda->date);
//      rtcda->timeStamp[0] = '\0'; // clear buffer
      break;
    case STOPWATCH:
      break;
  }
}
