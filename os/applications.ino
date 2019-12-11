
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

//Icon *initApps() {
//  Icon *allApps[2][3] = {
//    { new Icon(20, 60, 16, 16, heart, "Health", HOME_D), new Icon(55, 60, 16, 16, heart, "Stopwatch", SWATCH_D), new Icon(90, 60, 16, 16, heart, "Music", HOME_D) },
//    { new Icon(20, 60, 16, 16, heart, "Start/Stop", SWATCH_D), new Icon(55, 60, 16, 16, heart, "Clear", SWATCH_D), new Icon(90, 60, 16, 16, heart, "Back", HOME_D) }
//  };
//
////  Icon *homeIcons[3] = { new Icon(20, 60, 16, 16, heart, "Health", HOME_D), new Icon(55, 60, 16, 16, heart, "Stopwatch", SWATCH_D), new Icon(90, 60, 16, 16, heart, "Music", HOME_D) };
////  Icon *stopWatch[3] = { new Icon(20, 60, 16, 16, heart, "Start/Stop", SWATCH_D), new Icon(55, 60, 16, 16, heart, "Clear", SWATCH_D), new Icon(90, 60, 16, 16, heart, "Back", HOME_D) };
////
////  allApps[HOME_D] = homeIcons;
////  allApps[SWATCH_D] = stopWatch;
//
//  return allApps;
//}

void navigate(RotaryEncoder *encoder, Icon **icons, int *pos) {
    int newPos = encoder->getPosition();
    //int numApps = sizeof(icons) / sizeof(icons[0]);
    //Serial.println(numApps);

    // TODO: change 3 to numapps
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
