
#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <Adafruit_GFX.h>    // Core graphics library
#include <XTronical_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <Fonts/FreeMonoBold12pt7b.h>

#define ColorDisplay Adafruit_ST7735
#define DEFAULT_BACKGROUND ST7735_BLACK
#define DEFAULT_TEXT_COLOR ST7735_WHITE
#define DEFAULT_ICON_COLOR ST7735_RED
#define DEFAULT_HIGHLIGHT  ST7735_GREEN

#define UIScreenWidth 128
#define UIScreenHeight 128

#define DEFAULT_FONT &FreeMonoBold12pt7b
#define FONT_SIZE 12
#define TIME_CENTER 31
#define SWATCH_CENTER 16

#define staticTime "12:45"

#define TFT_SCLK 18
#define TFT_MOSI 23
#define TFT_CS    5
#define TFT_RST   2
#define TFT_DC    4

// LCD pin attached to GPIO instead of 3v3 for PWM brightness
#define LCD      16

#define HOME_D    0
#define SWATCH_D  1
#define MUSIC_D   2
#define WEATHER_D 3

#define RED    ST7735_RED
#define BLUE   ST7735_BLUE
#define GREEN  ST7735_GREEN
#define WHITE  ST7735_WHITE
#define CYAN   ST7735_CYAN
#define YELLOW ST7735_YELLOW
#define ORANGE 0xFBEC


typedef struct {

  byte displayOn;
  uint8_t brightness;
  uint8_t currPage;
  int currIcon;

} DisplayInfo;

DisplayInfo *createDisplayInfo();

void initializeDisplay(ColorDisplay *display);

void sleepDisplay(ColorDisplay *display);

void wakeDisplay(ColorDisplay *display);

void togglePower(DisplayInfo *info);

void screenSaver();

void setBrightness(uint8_t value);

#endif
