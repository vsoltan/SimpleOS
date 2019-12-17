
#include "RTClib.h"
#include <RotaryEncoder.h>
#include <Button.h>
#include <Wire.h>

#ifndef UTILS_H_
#define UTILS_H_

// ENCODER PINS

#define ECLK 13 // A
#define EDA 12  // B

#define BUZZER 17

#define NAV_BUTTON 0
#define DEBOUNCE 300

typedef struct {
  char timeStamp[9];
  char date[30];
} RTCData;

void initRTC(RTC_Millis *rtc);
void getTime(RTC_Millis *rtc, char *timeStamp);

uint8_t getMinute(RTC_Millis *rtc);
uint8_t getHour(RTC_Millis *rtc);

void initNavButton(Button *button);

uint8_t bidirMod(int8_t n, uint8_t m);

#endif
