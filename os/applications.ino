
#include "applications.h"
#include "display.h"

Window::Window(Icon **applications) {
  this->applications = applications;
}

Icon **Window::getApplications() {
  return this->applications;
}

void Window::setApplications(Icon **newApps) {
  this->applications = newApps;
}

Window **initWindows() {
  Window *windows[2];

  windows[HOME_D] = new Window(generateHomeIcons());
  windows[SWATCH_D] = new Window(generateStopwatchIcons());

  return windows;
}

void navigate(RotaryEncoder *encoder, Icon **icons, int *pos) {
    int newPos = encoder->getPosition();
    
    if (*pos != newPos) {
        icons[bidirMod(newPos, 3)]->renderHighlight(&tft);
        icons[bidirMod(*pos, 3)]->removeHighlight(&tft);
        *pos = newPos;
    }
}

void drawScreen(ColorDisplay *display, DisplayInfo *info, Window *window) {
  display->fillScreen(DEFAULT_BACKGROUND);
  drawPageIcons(window->getApplications(), display);
  
  switch(info->currPage) {
    case HOME_D: 
      drawHomeScreen(display);
      break;
    case SWATCH_D: 
      drawStopWatchScreen(display);
      break;
    default:
      break;
  }
}

void updateScreenOnClick(ColorDisplay *display, DisplayInfo *info, Window *window) {
 
}

void updateScreenTime(ColorDisplay *display, RTCData *rtcda, RTC_Millis *rtc) {
    display->fillRect(0, 0, 128, 40, DEFAULT_BACKGROUND);
    display->setCursor(20, 30);
    getTime(rtc, rtcda->timeStamp);
    display->setTextColor(DEFAULT_TEXT_COLOR, DEFAULT_BACKGROUND);
    display->print(rtcda->timeStamp);      
    rtcda->timeStamp[0] = '\0'; // clear buffer  
}

//char timeBuffer[9];
//
//void runStopWatchApp(ColorDisplay *display) {}
//
//void display_MSm(ColorDisplay *display, unsigned long t, char *timeBuffer) {
//    int minutes = (t / 1000) / 60;
//    int seconds = (t / 1000) % 60;
//    int milliseconds = (t % 1000) / 10;

//    display->print(minutes / 10);
//    display->print(minutes % 10);
//    display->print(":");
//    display->print(seconds / 10);
//    display->print(seconds % 10);
//    display->print(":");
//    display->print(milliseconds / 10);
//    display->print(milliseconds % 10);
