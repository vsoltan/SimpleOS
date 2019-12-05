
#include "graphics.h"

//display->drawStr((UIScreenWidth - widthScale * getStringWidth(&u8g2, staticTime))/2, centerHeight, "Hello World!");

class Icon {
  private:
    uint8_t width;
    uint8_t height;
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

void drawHomeScreen(OLED *display, RTCData *rtcda) {
    display->clearBuffer();
    display->sendBuffer();
}

void updateScreen(OLED *display, DisplayInfo *info, RTC_Millis *rtc) {
  switch (info->currPage) {
    case HOME:
      getTime(rtc, rtcda->timeStamp);
      display->clearBuffer();      
      display->setFont(u8g2_font_ncenB08_tr); 
      display->drawStr(0, centerHeight, rtcda->timeStamp);
      display->drawStr(0, centerHeight + PADDING, rtcda->date);
      display->sendBuffer();         
      rtcda->timeStamp[0] = '\0'; // clear buffer
      break;
    case STOPWATCH:
      break;
  }
}
