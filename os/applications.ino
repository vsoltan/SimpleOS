
#include "display.h"

char *timeBuffer[6] = {};

void runStopWatchApp(OLED *display) {
  display->clearBuffer();
  display->setFont(DEFAULT_FONT);
  display->drawStr((UIScreenWidth - widthScale * getStringWidth(&u8g2, staticTime))/2, centerHeight, "00:00:00");  
  
}

void display_MSm(OLED *display, unsigned long t, char *timeBuffer) {

  // clear all structures
  timeBuffer[0] = '\0';
  display->clearBuffer();

  int minutes = (t / 1000) / 60;
  int seconds = (t / 1000) % 60;
  int milliseconds = (t % 1000) / 10;

//  lcd.print(minutes / 10);
//  lcd.print(minutes % 10);
//  lcd.print(":");
//  lcd.print(seconds / 10);
//  lcd.print(seconds % 10);
//  lcd.print(":");
//  lcd.print(milliseconds / 10);
//  lcd.print(milliseconds % 10);
//
//  lcd.display();
}
