
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
    // boolean for if already pressed or not

  public:
    Icon(uint8_t x, uint8_t y, uint8_t width, uint8_t height, const unsigned char *icon, const char *label, uint8_t descriptor, uint16_t color);
    uint8_t getX();
    uint8_t getY();
    uint8_t getWidth();
    uint8_t getHeight();
    const char *getLabel();
    void setIcon(const unsigned char *newIcon);
    void renderHighlight(ColorDisplay *display);
    void removeHighlight(ColorDisplay *display);
    void drawIcon(ColorDisplay *display);
    uint8_t getDestinationDescriptor();
};

typedef struct {
  
    byte stopwatchRunning;
    bool *musicPlaying;
    bool *bluetoothConnection;
    bool stopWatchRunning;
    unsigned long stopWatchStartTime;
    unsigned long stopWatchCurrTime; 

} AppStatus;

Icon **generateHomeIcons();

Icon **generateStopWatchIcons();

Icon ***generateAllApps();

void drawHomeScreen(ColorDisplay *display, AppStatus *appInfo);

void drawStopWatchScreen(ColorDisplay *display, AppStatus *appInfo);

void drawMusicScreen(ColorDisplay *display, AppStatus *appInfo);

void drawPageIcons(Icon **appIcons, ColorDisplay *display, uint8_t numIcons);

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

#define music_width 24
#define music_height 24
const unsigned char PROGMEM music_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x78, 0x00, 0x00,
   0xf8, 0x03, 0x00, 0x98, 0x1f, 0x00, 0x18, 0xfc, 0x01, 0x78, 0xe0, 0x01,
   0x98, 0x83, 0x01, 0x18, 0x9c, 0x01, 0x18, 0xe0, 0x01, 0x18, 0x80, 0x01,
   0x18, 0x80, 0x01, 0x18, 0x80, 0x01, 0x18, 0x80, 0x01, 0x78, 0x80, 0x01,
   0xf8, 0x81, 0x01, 0xf8, 0x83, 0x01, 0xf0, 0x83, 0x07, 0xe0, 0x81, 0x1f,
   0x00, 0x80, 0x3f, 0x00, 0x00, 0x3f, 0x00, 0x00, 0x1e, 0x00, 0x00, 0x00
};

#define play_width 24
#define play_height 24
static unsigned char play_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0xf8, 0x00, 0x00,
   0xf8, 0x03, 0x00, 0xf8, 0x07, 0x00, 0xf8, 0x1f, 0x00, 0xf8, 0x7f, 0x00,
   0xf8, 0xff, 0x00, 0xf8, 0xff, 0x03, 0xf8, 0xff, 0x0f, 0xf8, 0xff, 0x1f,
   0xf8, 0xff, 0x0f, 0xf8, 0xff, 0x03, 0xf8, 0xff, 0x00, 0xf8, 0x7f, 0x00,
   0xf8, 0x1f, 0x00, 0xf8, 0x07, 0x00, 0xf8, 0x03, 0x00, 0xf8, 0x00, 0x00,
   0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

#define pause_width 24
#define pause_height 24
static unsigned char pause_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc3, 0x01,
   0xc0, 0xe7, 0x03, 0xc0, 0xe7, 0x03, 0xc0, 0xe7, 0x03, 0xc0, 0xe7, 0x03,
   0xc0, 0xe7, 0x03, 0xc0, 0xe7, 0x03, 0xc0, 0xe7, 0x03, 0xc0, 0xe7, 0x03,
   0xc0, 0xe7, 0x03, 0xc0, 0xe7, 0x03, 0xc0, 0xe7, 0x03, 0xc0, 0xe7, 0x03,
   0xc0, 0xe7, 0x03, 0xc0, 0xe7, 0x03, 0xc0, 0xe7, 0x03, 0xc0, 0xe7, 0x03,
   0x80, 0xc3, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

#define prev_track_width 16
#define prev_track_height 16
static unsigned char prev_track_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x0c, 0x60, 0x0c, 0x78, 0x0c, 0x7e, 0x8c, 0x7f,
   0xec, 0x7f, 0xfc, 0x7f, 0xec, 0x7f, 0x8c, 0x7f, 0x0c, 0x7e, 0x0c, 0x78,
   0x0c, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

#define next_track_width 16
#define next_track_height 16
static unsigned char next_track_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x06, 0x30, 0x1e, 0x30, 0x7e, 0x30, 0xfe, 0x31,
   0xfe, 0x37, 0xfe, 0x3f, 0xfe, 0x37, 0xfe, 0x31, 0x7e, 0x30, 0x1e, 0x30,
   0x06, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

#define swatch_width 24
#define swatch_height 24
static unsigned char swatch_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x03, 0x00, 0x7e, 0x04,
   0x80, 0xff, 0x09, 0xc0, 0x81, 0x03, 0x60, 0x18, 0x06, 0x30, 0x00, 0x0c,
   0x30, 0x81, 0x0c, 0x18, 0x40, 0x18, 0x18, 0x20, 0x18, 0x58, 0x10, 0x1a,
   0x58, 0x00, 0x1a, 0x18, 0x00, 0x18, 0x18, 0x00, 0x18, 0x30, 0x81, 0x0c,
   0x30, 0x00, 0x0c, 0x60, 0x18, 0x06, 0xc0, 0x81, 0x03, 0x80, 0xff, 0x01,
   0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

#define weather_width 24
#define weather_height 24
static unsigned char weather_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 0x00, 0x40, 0x08,
   0x00, 0x20, 0x10, 0x00, 0x10, 0x20, 0x00, 0x17, 0x20, 0xc0, 0xdf, 0x21,
   0xc0, 0xff, 0x27, 0xe0, 0xff, 0x17, 0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x1f,
   0xfc, 0xff, 0x3f, 0xfc, 0xff, 0x3f, 0xfc, 0xff, 0x3f, 0xf8, 0xff, 0x1f,
   0xf8, 0xff, 0x1f, 0xe0, 0x38, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

#define back_width 16
#define back_height 16
static unsigned char back_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x60, 0x00, 0x70, 0x00, 0xf8, 0x3f,
   0xfc, 0x3f, 0xfe, 0x3f, 0xfc, 0x3f, 0xf8, 0x3f, 0x70, 0x00, 0x60, 0x00,
   0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

#endif
