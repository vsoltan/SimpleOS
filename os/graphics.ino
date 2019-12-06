
#include "graphics.h"

//display->drawStr((UIScreenWidth - widthScale * getStringWidth(&u8g2, staticTime))/2, centerHeight, "Hello World!");

class Icon {
  private:
    uint8_t width;
    uint8_t height;
    char *icon;
    bool isHighlighted;
    char *label;
    
  public:
    Icon(uint8_t width, uint8_t height, char *label);
    uint8_t getWidth();
    uint8_t getHeight();
    void Highlight();
};

Icon::Icon(uint8_t width, uint8_t height, char *label) {
    this->width = width;
    this->width = height;
    this->label = label;
    this->isHighlighted = false;
}

uint8_t Icon::getWidth() {
  return this->width;
}

uint8_t Icon::getHeight() {
  return this->height;
}

void Icon::Highlight() {
  // set colored border to indicate where the encoder is
  
}

void drawHomeScreen(ColorDisplay *display, RTCData *rtcda) {


}

void updateScreen(ColorDisplay *display, DisplayInfo *info, RTC_Millis *rtc) {
  switch (info->currPage) {
    case HOME:
//      getTime(rtc, rtcda->timeStamp);      
//      display->drawStr(0, centerHeight, rtcda->timeStamp);
//      display->drawStr(0, centerHeight + PADDING, rtcda->date);
//      rtcda->timeStamp[0] = '\0'; // clear buffer
      break;
    case STOPWATCH:
      break;
  }
}
