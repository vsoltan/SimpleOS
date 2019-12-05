
#ifndef DISPLAY_H_
#define DISPLAY_H_

#include <U8g2lib.h>

#define OLED U8G2_SSD1327_MIDAS_128X128_F_HW_I2C
#define BUS_CLOCK 1500000
#define UIScreenWidth 128
#define UIScreenHeight 128
#define staticTime "12:45"

// 8 pixel height font
#define DEFAULT_FONT u8g2_font_ncenB08_tr

#define heightScale 8
#define widthScale 3

#define centerHeight (UIScreenHeight - heightScale)/2

enum PAGES {HOME, STOPWATCH};

typedef struct {
  byte displayOn;
  enum PAGES currPage;
} DisplayInfo;

DisplayInfo *createDisplayInfo();

void initializeDisplay(OLED *display);

void sleepDisplay(OLED *display);

void wakeDisplay(OLED *display);

void togglePower(byte displayOn, OLED *display);

// text manipulation

uint8_t getStringWidth(OLED *display, const char *string);

#endif
