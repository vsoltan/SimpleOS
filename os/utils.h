
#include "RTClib.h"
#include <RotaryEncoder.h>
#include <Wire.h>

#ifndef UTILS_H_
#define UTILS_H_

#define NAV_BUTTON 0
#define RO_A 4
#define RO_B 5

// RTC 

typedef struct {
  char timeStamp[9];
  char date[30];
} RTCData;

void initRTC(RTC_Millis *rtc);
void getTime(RTC_Millis *rtc, char *timeStamp);

// ENCODER

int getPosition();

#endif
