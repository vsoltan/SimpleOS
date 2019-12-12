
#include "display.h"
#include "utils.h"


#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#define highlightPadding 5
#define NAV_TICKRATE 2

class Icon {
  private:
    uint8_t x;
    uint8_t y;
    uint8_t width;
    uint8_t height;
    uint16_t color;
    const unsigned char *icon;
    const char *label;
    uint8_t destinationDescriptor;
    
  public:
    Icon(uint8_t x, uint8_t y, uint8_t width, uint8_t height, const unsigned char *icon, const char *label, uint8_t descriptor, uint16_t color);
    uint8_t getX();
    uint8_t getY();
    uint8_t getWidth();
    uint8_t getHeight();
    const char *getLabel();
    void renderHighlight(ColorDisplay *display);
    void removeHighlight(ColorDisplay *display);
    void drawIcon(ColorDisplay *display);
    uint8_t getDestinationDescriptor();
};

Icon **generateHomeIcons();

Icon **generateStopWatchIcons();

void homeScreen(ColorDisplay *display);

void drawStopWatchScreen(ColorDisplay *display);

const unsigned char PROGMEM heart[] =

{ B00000000, B00000000,
  B00000000, B00000000,
  B00111100, B00111100,
  B01111110, B11111110,
  B11111111, B11111111,
  B11111111, B11111111,
  B01111111, B11111110,
  B00111111, B11111100,
  B00011111, B11111000,
  B00001111, B11110000,
  B00000111, B11100000, 
  B00000011, B11000000,
  B00000001, B10000000,
  B00000000, B00000000,
  B00000000, B00000000,
  B00000000, B00000000

};

void drawPageIcons(Icon **appIcons, ColorDisplay *display);

void runApp(Icon *app);

#endif
