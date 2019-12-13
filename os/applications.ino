
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

void navigate(RotaryEncoder *encoder, Icon **icons, int *pos, uint8_t size) {
    int newPos = encoder->getPosition();
    
    if (*pos != newPos) {
        icons[bidirMod(newPos, size)]->renderHighlight(&tft);
        icons[bidirMod(*pos, size)]->removeHighlight(&tft);
        *pos = newPos;
    }
}

void updateScreenTime(ColorDisplay *display, RTCData *rtcda, RTC_Millis *rtc) {
    display->fillRect(0, 0, 128, 40, DEFAULT_BACKGROUND);
    display->setCursor(30, 30);
    getTime(rtc, rtcda->timeStamp);
    display->setTextColor(DEFAULT_TEXT_COLOR, DEFAULT_BACKGROUND);
    display->print(rtcda->timeStamp);      
    rtcda->timeStamp[0] = '\0'; // clear buffer  
}

void updateStopwatch(uint8_t flag) {
  switch(flag) {
    case STOP_START:
      break;
    case CLEAR:
      break;
    default: 
      break; 
  }
}

void updateMusic(uint8_t flag, BLECharacteristic *pTxCharacteristic, bool *deviceConnected) {
 
  if (*deviceConnected) {
     pTxCharacteristic->setValue(&flag, 1);
     pTxCharacteristic->notify();  
  }
}

void drawScreen(ColorDisplay *display, DisplayInfo *info, Window *window, RTCData *rtcda, RTC_Millis *rtc) {
  display->fillScreen(DEFAULT_BACKGROUND);
  drawPageIcons(window->getApplications(), display);
  
  switch(info->currPage) {
    case HOME_D:
      updateScreenTime(display, rtcda, rtc);
      drawHomeScreen(display);
      break;
    case SWATCH_D: 
      drawStopWatchScreen(display);
      break;
    case MUSIC_D: 
      
      break;
    default:
      break;
  }
}

void updateScreenOnClick(ColorDisplay *display, DisplayInfo *info, Window *window, BLECharacteristic *pTxCharacteristic, bool *deviceConnected) {
  
  switch(info->currPage) {
    case SWATCH_D:
      updateStopwatch(info->currIcon);
      break;
     case MUSIC_D:
        updateMusic(info->currIcon, pTxCharacteristic, deviceConnected);
        break;
     
    default:
      break; 
      
  }
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
