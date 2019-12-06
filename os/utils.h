
#include "RTClib.h"
#include <RotaryEncoder.h>
#include <Wire.h>

#ifndef UTILS_H_
#define UTILS_H_

#define ECLK 15 // A
#define EDA 13  // B
#define NAV_BUTTON 14
#define PWR 27

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
