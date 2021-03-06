
#include "display.h"
#include "utils.h"
#include <Arduino_JSON.h>


#ifndef GRAPHICS_H_
#define GRAPHICS_H_

#define highlightPadding 5
#define NAV_TICKRATE 2

// WEATHER TYPES
#define THUNDERSTORM 2
#define DRIZZLE 3
#define RAIN 5
#define SNOW 6
#define ATMOSPHERE 7
#define CLOUDS 8

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
    void setColor(uint16_t color);
    void renderHighlight(ColorDisplay *display);
    void removeHighlight(ColorDisplay *display);
    void drawIcon(ColorDisplay *display);
    uint8_t getDestinationDescriptor();
};

typedef struct {
  
    byte stopwatchRunning;
    
    bool musicPlaying;
    bool inVolumeControls;

    bool *bluetoothConnection;
    bool stopWatchRunning;

    bool *weatherDataReceived;
    bool *newWeatherData; 
    
    unsigned long stopWatchStartTime;
    unsigned long stopWatchPauseTime;
    unsigned long stopWatchCurrTime; 
    
    JSONVar *weatherObj;
    
    const unsigned char *weatherIcon;
    uint16_t iconColor;

} AppStatus;

Icon **generateHomeIcons();

Icon **generateStopWatchIcons();

Icon ***generateAllApps();

void drawHomeScreen(ColorDisplay *display, AppStatus *appStatus);

void drawWeatherScreen(ColorDisplay *display, AppStatus *appStatus);

void drawStopWatchScreen(ColorDisplay *display, AppStatus *appStatus);

void displayFormatedStopwatch(ColorDisplay *display, unsigned long t);

void drawMusicScreen(ColorDisplay *display, AppStatus *appStatus);

void drawPageIcons(Icon **appIcons, ColorDisplay *display, uint8_t numIcons);

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
static unsigned char PROGMEM play_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x30, 0x00, 0x00, 0xf8, 0x00, 0x00,
   0xf8, 0x03, 0x00, 0xf8, 0x07, 0x00, 0xf8, 0x1f, 0x00, 0xf8, 0x7f, 0x00,
   0xf8, 0xff, 0x00, 0xf8, 0xff, 0x03, 0xf8, 0xff, 0x0f, 0xf8, 0xff, 0x1f,
   0xf8, 0xff, 0x0f, 0xf8, 0xff, 0x03, 0xf8, 0xff, 0x00, 0xf8, 0x7f, 0x00,
   0xf8, 0x1f, 0x00, 0xf8, 0x07, 0x00, 0xf8, 0x03, 0x00, 0xf8, 0x00, 0x00,
   0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

#define pause_width 24
#define pause_height 24
static unsigned char PROGMEM pause_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xc3, 0x01,
   0xc0, 0xe7, 0x03, 0xc0, 0xe7, 0x03, 0xc0, 0xe7, 0x03, 0xc0, 0xe7, 0x03,
   0xc0, 0xe7, 0x03, 0xc0, 0xe7, 0x03, 0xc0, 0xe7, 0x03, 0xc0, 0xe7, 0x03,
   0xc0, 0xe7, 0x03, 0xc0, 0xe7, 0x03, 0xc0, 0xe7, 0x03, 0xc0, 0xe7, 0x03,
   0xc0, 0xe7, 0x03, 0xc0, 0xe7, 0x03, 0xc0, 0xe7, 0x03, 0xc0, 0xe7, 0x03,
   0x80, 0xc3, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

#define prev_track_width 16
#define prev_track_height 16
static unsigned char PROGMEM prev_track_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x0c, 0x60, 0x0c, 0x78, 0x0c, 0x7e, 0x8c, 0x7f,
   0xec, 0x7f, 0xfc, 0x7f, 0xec, 0x7f, 0x8c, 0x7f, 0x0c, 0x7e, 0x0c, 0x78,
   0x0c, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

#define next_track_width 16
#define next_track_height 16
static unsigned char PROGMEM next_track_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x06, 0x30, 0x1e, 0x30, 0x7e, 0x30, 0xfe, 0x31,
   0xfe, 0x37, 0xfe, 0x3f, 0xfe, 0x37, 0xfe, 0x31, 0x7e, 0x30, 0x1e, 0x30,
   0x06, 0x30, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

#define swatch_width 24
#define swatch_height 24
static unsigned char PROGMEM swatch_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x3c, 0x00, 0x00, 0x00, 0x03, 0x00, 0x7e, 0x04,
   0x80, 0xff, 0x09, 0xc0, 0x81, 0x03, 0x60, 0x18, 0x06, 0x30, 0x00, 0x0c,
   0x30, 0x81, 0x0c, 0x18, 0x40, 0x18, 0x18, 0x20, 0x18, 0x58, 0x10, 0x1a,
   0x58, 0x00, 0x1a, 0x18, 0x00, 0x18, 0x18, 0x00, 0x18, 0x30, 0x81, 0x0c,
   0x30, 0x00, 0x0c, 0x60, 0x18, 0x06, 0xc0, 0x81, 0x03, 0x80, 0xff, 0x01,
   0x00, 0x7e, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

#define weather_width 24
#define weather_height 24
static unsigned char PROGMEM weather_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x07, 0x00, 0x40, 0x08,
   0x00, 0x20, 0x10, 0x00, 0x10, 0x20, 0x00, 0x17, 0x20, 0xc0, 0xdf, 0x21,
   0xc0, 0xff, 0x27, 0xe0, 0xff, 0x17, 0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x1f,
   0xfc, 0xff, 0x3f, 0xfc, 0xff, 0x3f, 0xfc, 0xff, 0x3f, 0xf8, 0xff, 0x1f,
   0xf8, 0xff, 0x1f, 0xe0, 0x38, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

#define back_width 16
#define back_height 16
static unsigned char PROGMEM back_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x40, 0x00, 0x60, 0x00, 0x70, 0x00, 0xf8, 0x3f,
   0xfc, 0x3f, 0xfe, 0x3f, 0xfc, 0x3f, 0xf8, 0x3f, 0x70, 0x00, 0x60, 0x00,
   0x40, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

#define stop_width 24
#define stop_height 24
static unsigned char PROGMEM stop_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0x1f,
   0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x1f,
   0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x1f,
   0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x1f,
   0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x1f, 0xf8, 0xff, 0x1f,
   0xf8, 0xff, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

#define reset_width 24
#define reset_height 24
static unsigned char PROGMEM reset_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x7e, 0x00, 0x80, 0xff, 0x23, 0xe0, 0x01, 0x37,
   0x70, 0x00, 0x3c, 0x18, 0x00, 0x3c, 0x0c, 0x00, 0x3e, 0x0c, 0x00, 0x3f,
   0x0c, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x00,
   0x06, 0x00, 0x00, 0x06, 0x00, 0x00, 0x06, 0x00, 0x20, 0x0c, 0x00, 0x30,
   0x0c, 0x00, 0x30, 0x1c, 0x00, 0x30, 0x18, 0x00, 0x18, 0x70, 0x00, 0x1c,
   0xe0, 0x00, 0x0e, 0xc0, 0xff, 0x07, 0x00, 0xff, 0x01, 0x00, 0x00, 0x00 
};

#define sunny_width 60
#define sunny_height 60
static unsigned char PROGMEM sun_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0x07, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xe0, 0xff, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff,
   0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0x07, 0x00, 0x00,
   0x00, 0x00, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff,
   0xff, 0x3f, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00,
   0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff,
   0xff, 0xff, 0x01, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00,
   0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0xfe, 0xff, 0xff,
   0xff, 0xff, 0x07, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00,
   0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x80, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x1f, 0x00, 0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00,
   0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0xc0, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x3f, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00,
   0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0xe0, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x7f, 0x00, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00,
   0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 0xe0, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x7f, 0x00, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00,
   0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 0xe0, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x7f, 0x00, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00,
   0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 0xe0, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x7f, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00,
   0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00, 0xc0, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x3f, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00,
   0x80, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x80, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x1f, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00,
   0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0xfe, 0xff, 0xff,
   0xff, 0xff, 0x07, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00,
   0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0xf8, 0xff, 0xff,
   0xff, 0xff, 0x01, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
   0x00, 0xe0, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff,
   0xff, 0x3f, 0x00, 0x00, 0x00, 0x00, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00,
   0x00, 0x00, 0xfe, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff,
   0xff, 0x01, 0x00, 0x00, 0x00, 0x00, 0xe0, 0xff, 0x7f, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xfe, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

#define drizzle_width 60
#define drizzle_height 60
static unsigned char PROGMEM drizzle_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xfe, 0xf8, 0x03, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff,
   0xff, 0x0f, 0x00, 0x00, 0x00, 0x80, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00,
   0x00, 0xe0, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff,
   0xff, 0x3f, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00,
   0x00, 0xf8, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff,
   0xff, 0x7f, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00,
   0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0xfc, 0xff, 0xff,
   0xff, 0xff, 0x03, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00,
   0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0xfe, 0xff, 0xff,
   0xff, 0xff, 0x0f, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00,
   0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0xfe, 0xff, 0xff,
   0xff, 0xff, 0x0f, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00,
   0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0xfe, 0xff, 0xff,
   0xff, 0xff, 0x0f, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00,
   0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0xf8, 0xff, 0xff,
   0xe7, 0xff, 0x03, 0x00, 0x00, 0xf0, 0x7f, 0xfc, 0xc1, 0xff, 0x01, 0x00,
   0x00, 0xc0, 0x1f, 0x00, 0x00, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x10, 0x42, 0x08, 0x02, 0x00, 0x00, 0x00, 0x00, 0x18, 0x63,
   0x0c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x08, 0x21, 0x04, 0x01, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

#define rain_width 60
#define rain_height 60
static unsigned char PROGMEM rain_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xfe, 0xf8, 0x03, 0x00, 0x00,
   0x00, 0x00, 0x80, 0xff, 0xff, 0x0f, 0x00, 0x00, 0x00, 0x80, 0xff, 0xff,
   0xff, 0x1f, 0x00, 0x00, 0x00, 0xe0, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00,
   0x00, 0xf0, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff,
   0xff, 0x7f, 0x00, 0x00, 0x00, 0xf8, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00,
   0x00, 0xfc, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff,
   0xff, 0x7f, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00,
   0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00, 0x00, 0xfc, 0xff, 0xff,
   0xff, 0xff, 0x07, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00,
   0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0xfe, 0xff, 0xff,
   0xff, 0xff, 0x0f, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00,
   0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0xfe, 0xff, 0xff,
   0xff, 0xff, 0x0f, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00,
   0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00, 0x00, 0xfc, 0xff, 0xff,
   0xff, 0xff, 0x07, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00,
   0x00, 0xf8, 0xff, 0xff, 0xe7, 0xff, 0x03, 0x00, 0x00, 0xf0, 0x7f, 0xfc,
   0xc1, 0xff, 0x01, 0x00, 0x00, 0xc0, 0x1f, 0x00, 0x00, 0x7f, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x10, 0x42, 0x08, 0x02, 0x00, 0x00, 0x00, 0x00, 0x18, 0x63,
   0x0c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x08, 0x21, 0x04, 0x01, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x84, 0x10, 0x82, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xc6, 0x18, 0xc3, 0x00, 0x00, 0x00, 0x00, 0x00, 0x42, 0x08,
   0x41, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0x10, 0x42,
   0x10, 0x00, 0x00, 0x00, 0x00, 0xc0, 0x18, 0x63, 0x18, 0x00, 0x00, 0x00,
   0x00, 0x40, 0x08, 0x21, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

#define cloud_width 60
#define cloud_height 60
static unsigned char PROGMEM cloud_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x7f, 0xfc, 0x01, 0x00, 0x00,
   0x00, 0x00, 0xc0, 0xff, 0xff, 0x07, 0x00, 0x00, 0x00, 0xc0, 0xff, 0xff,
   0xff, 0x0f, 0x00, 0x00, 0x00, 0xf0, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00,
   0x00, 0xf8, 0xff, 0xff, 0xff, 0x1f, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff,
   0xff, 0x3f, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00,
   0x00, 0xfe, 0xff, 0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff,
   0xff, 0x3f, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x00, 0x00,
   0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x01, 0x00, 0x00, 0xfe, 0xff, 0xff,
   0xff, 0xff, 0x03, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00,
   0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x07, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00,
   0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x07, 0x00, 0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00,
   0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x00, 0xfe, 0xff, 0xff,
   0xff, 0xff, 0x03, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00,
   0x00, 0xfc, 0xff, 0xff, 0xf3, 0xff, 0x01, 0x00, 0x00, 0xf8, 0x3f, 0xfe,
   0xe0, 0xff, 0x00, 0x00, 0x00, 0xe0, 0x0f, 0x00, 0x80, 0x3f, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

#define snow_width 60
#define snow_height 60
static unsigned char PROGMEM snow_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x98,
   0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06,
   0x06, 0x00, 0x00, 0x00, 0x00, 0x3e, 0x00, 0x0c, 0x03, 0xc0, 0x07, 0x00,
   0x00, 0x63, 0x00, 0x98, 0x01, 0x60, 0x0c, 0x00, 0x00, 0x41, 0x00, 0xf0,
   0x00, 0x20, 0x08, 0x00, 0x00, 0x41, 0x00, 0x60, 0x00, 0x20, 0x08, 0x00,
   0x00, 0x41, 0x00, 0x60, 0x00, 0x20, 0x08, 0x00, 0x00, 0x63, 0x18, 0xfe,
   0x87, 0x61, 0x0c, 0x00, 0x00, 0xfe, 0x18, 0xfe, 0x87, 0xf1, 0x07, 0x00,
   0x00, 0xc0, 0x19, 0x60, 0x80, 0x39, 0x00, 0x00, 0x00, 0x80, 0x1f, 0x60,
   0x80, 0x1f, 0x00, 0x00, 0x00, 0x00, 0x1f, 0x62, 0x84, 0x0f, 0x00, 0x00,
   0x00, 0x00, 0x1b, 0x67, 0x8e, 0x0d, 0x00, 0x00, 0x00, 0xe0, 0x9f, 0x63,
   0x9c, 0x7f, 0x00, 0x00, 0x00, 0xe0, 0xff, 0x61, 0xf8, 0x7f, 0x00, 0x00,
   0x00, 0x00, 0x90, 0xf8, 0x91, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0xf8,
   0x91, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0x61, 0xf8, 0x01, 0x00, 0x00,
   0x00, 0x00, 0x9c, 0x67, 0x9e, 0x03, 0x00, 0x00, 0xc0, 0x60, 0x0e, 0x65,
   0x0a, 0x67, 0x30, 0x00, 0xe0, 0x61, 0x04, 0x6f, 0x0f, 0x62, 0x78, 0x00,
   0x30, 0x63, 0x60, 0xfc, 0x63, 0x60, 0xcc, 0x00, 0x18, 0x66, 0x60, 0x68,
   0x61, 0x60, 0x86, 0x01, 0x0c, 0xfc, 0xff, 0x9f, 0xff, 0xff, 0x03, 0x03,
   0x0c, 0xfc, 0xff, 0x9f, 0xff, 0xff, 0x03, 0x03, 0x18, 0x66, 0x60, 0x68,
   0x61, 0x60, 0x86, 0x01, 0x30, 0x63, 0x60, 0xfc, 0x63, 0x60, 0xcc, 0x00,
   0xe0, 0x61, 0x04, 0x6f, 0x0f, 0x62, 0x78, 0x00, 0xc0, 0x60, 0x0e, 0x65,
   0x0a, 0x67, 0x30, 0x00, 0x00, 0x00, 0x9c, 0x67, 0x9e, 0x03, 0x00, 0x00,
   0x00, 0x00, 0xf8, 0x61, 0xf8, 0x01, 0x00, 0x00, 0x00, 0x00, 0x90, 0xf8,
   0x91, 0x00, 0x00, 0x00, 0x00, 0x00, 0x90, 0xf8, 0x91, 0x00, 0x00, 0x00,
   0x00, 0xe0, 0xff, 0x61, 0xf8, 0x7f, 0x00, 0x00, 0x00, 0xe0, 0x9f, 0x63,
   0x9c, 0x7f, 0x00, 0x00, 0x00, 0x00, 0x1b, 0x67, 0x8e, 0x0d, 0x00, 0x00,
   0x00, 0x00, 0x1f, 0x62, 0x84, 0x0f, 0x00, 0x00, 0x00, 0x80, 0x1f, 0x60,
   0x80, 0x1f, 0x00, 0x00, 0x00, 0xc0, 0x19, 0x60, 0x80, 0x39, 0x00, 0x00,
   0x00, 0xfe, 0x18, 0xfe, 0x87, 0xf1, 0x07, 0x00, 0x00, 0x63, 0x18, 0xfe,
   0x87, 0x61, 0x0c, 0x00, 0x00, 0x41, 0x00, 0x60, 0x00, 0x20, 0x08, 0x00,
   0x00, 0x41, 0x00, 0x60, 0x00, 0x20, 0x08, 0x00, 0x00, 0x41, 0x00, 0xf0,
   0x00, 0x20, 0x08, 0x00, 0x00, 0x63, 0x00, 0x98, 0x01, 0x60, 0x0c, 0x00,
   0x00, 0x3e, 0x00, 0x0c, 0x03, 0xc0, 0x07, 0x00, 0x00, 0x00, 0x00, 0x06,
   0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x06, 0x06, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x0c, 0x03, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x98,
   0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x60, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

#define volume_width 16
#define volume_height 16
static unsigned char PROGMEM volume_bits[] = {
   0x00, 0x00, 0x40, 0x04, 0x60, 0x08, 0x60, 0x12, 0x70, 0x24, 0x7e, 0x29,
   0x7e, 0x2a, 0x7e, 0x2a, 0x7e, 0x2a, 0x7e, 0x2a, 0x7e, 0x29, 0x70, 0x24,
   0x60, 0x12, 0x60, 0x08, 0x40, 0x04, 0x00, 0x00 
};

#define thunder_width 60
#define thunder_height 60
static unsigned char PROGMEM thunder_bits[] = {
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x38,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x80, 0xff, 0x03, 0x00, 0x00, 0x00,
   0x00, 0x00, 0xc0, 0xff, 0x07, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf0, 0xff,
   0x1f, 0x00, 0x00, 0x00, 0x00, 0x00, 0xf8, 0xff, 0x3f, 0x07, 0x00, 0x00,
   0x00, 0xe0, 0xf8, 0xff, 0xff, 0x7f, 0x00, 0x00, 0x00, 0xfc, 0xff, 0xff,
   0xff, 0xff, 0x00, 0x00, 0x00, 0xfe, 0xff, 0xff, 0xff, 0xff, 0x03, 0x00,
   0x00, 0xff, 0xff, 0xff, 0xff, 0xff, 0x07, 0x00, 0x80, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x07, 0x00, 0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x0f, 0x00,
   0xc0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x1f, 0x00, 0xc0, 0xff, 0xff, 0xff,
   0xff, 0xff, 0x1f, 0x00, 0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x3f, 0x00,
   0xe0, 0xff, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 0xe0, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0x00, 0xf0, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01,
   0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01, 0xfc, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0x01, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03,
   0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xfc, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0x03, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03,
   0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x03, 0xfc, 0xff, 0xff, 0xff,
   0xff, 0xff, 0xff, 0x03, 0xf8, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0x01,
   0xf0, 0xf7, 0xff, 0xff, 0xff, 0xff, 0x7f, 0x00, 0x00, 0xe0, 0xff, 0xff,
   0xff, 0xff, 0x3f, 0x00, 0x00, 0x00, 0xc7, 0xff, 0x27, 0xf7, 0x1f, 0x00,
   0x00, 0x10, 0x80, 0xff, 0x13, 0x80, 0x03, 0x00, 0x00, 0x18, 0x08, 0xff,
   0x09, 0x81, 0x00, 0x00, 0x00, 0x0c, 0x0c, 0x3a, 0x84, 0xc1, 0x00, 0x00,
   0x00, 0x0c, 0x06, 0x01, 0xc2, 0x60, 0x00, 0x00, 0x00, 0x06, 0x86, 0x00,
   0xc1, 0x60, 0x00, 0x00, 0x00, 0x02, 0x43, 0x80, 0x60, 0x30, 0x00, 0x00,
   0x00, 0x00, 0x41, 0x40, 0x20, 0x10, 0x00, 0x00, 0x00, 0x08, 0x20, 0x20,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x0c, 0x14, 0x10, 0x80, 0x40, 0x00, 0x00,
   0x00, 0x06, 0x0e, 0x08, 0xc0, 0x60, 0x00, 0x00, 0x00, 0x06, 0x07, 0x04,
   0x60, 0x30, 0x00, 0x00, 0x00, 0x03, 0x1b, 0x08, 0x60, 0x30, 0x00, 0x00,
   0x00, 0x81, 0x21, 0x10, 0x30, 0x18, 0x00, 0x00, 0x00, 0x80, 0x40, 0x20,
   0x10, 0x08, 0x00, 0x00, 0x00, 0x04, 0x80, 0x41, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x06, 0x02, 0x82, 0x40, 0x20, 0x00, 0x00, 0x00, 0x03, 0x03, 0x0c,
   0x61, 0x30, 0x00, 0x00, 0x00, 0x83, 0x01, 0x90, 0x30, 0x18, 0x00, 0x00,
   0x80, 0x81, 0x01, 0x48, 0x30, 0x18, 0x00, 0x00, 0x80, 0xc0, 0x00, 0x28,
   0x18, 0x0c, 0x00, 0x00, 0x00, 0x40, 0x00, 0x1c, 0x08, 0x04, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x06, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x02,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
   0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00 
};

#endif
