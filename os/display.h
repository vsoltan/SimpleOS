
#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <Adafruit_GFX.h>    // Core graphics library
#include <XTronical_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <Fonts/FreeMonoBoldOblique12pt7b.h>

#define ColorDisplay Adafruit_ST7735

#define UIScreenWidth 128
#define UIScreenHeight 128
#define DEFAULT_FONT &FreeMonoBoldOblique12pt7b

#define staticTime "12:45"


#define TFT_SCLK 18         
#define TFT_MOSI 23         
#define TFT_CS    5        
#define TFT_RST   2        
#define TFT_DC    4

#define LED      12

enum PAGES {HOME, STOPWATCH};

typedef struct {
  
  byte displayOn;
  uint8_t brightness;
  enum PAGES currPage;
  
} DisplayInfo;

DisplayInfo *createDisplayInfo();

void initializeDisplay(ColorDisplay *display);

void sleepDisplay(ColorDisplay *display);

void wakeDisplay(ColorDisplay *display);

void togglePower(byte displayOn, ColorDisplay *display);

void screenSaver();

void setBrightness(uint8_t value);


#endif
