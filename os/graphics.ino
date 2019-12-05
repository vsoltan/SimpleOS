
#include "graphics.h"

void drawHomeScreen(OLED *display) {
    display->clearBuffer();
    display->drawStr((UIScreenWidth - widthScale * getStringWidth(&u8g2, staticTime))/2, centerHeight, "Hello World!");
    display->sendBuffer();
}

void updateScreen(OLED *display) {
  
}
