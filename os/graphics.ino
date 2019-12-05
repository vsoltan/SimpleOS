
#include "graphics.h"

//display->drawStr((UIScreenWidth - widthScale * getStringWidth(&u8g2, staticTime))/2, centerHeight, "Hello World!");

void drawHomeScreen(OLED *display) {
    display->clearBuffer();
    display->sendBuffer();
}

void updateScreen(OLED *display) {
  
}
