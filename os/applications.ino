
#include "applications.h"
#include "display.h"

char timeBuffer[9];

void runStopWatchApp(ColorDisplay *display) {}

void display_MSm(ColorDisplay *display, unsigned long t, char *timeBuffer) {
    int minutes = (t / 1000) / 60;
    int seconds = (t / 1000) % 60;
    int milliseconds = (t % 1000) / 10;
  
//    display->print(minutes / 10);
//    display->print(minutes % 10);
//    display->print(":");
//    display->print(seconds / 10);
//    display->print(seconds % 10);
//    display->print(":");
//    display->print(milliseconds / 10);
//    display->print(milliseconds % 10);

}
