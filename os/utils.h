
#include "RTClib.h"
#include <RotaryEncoder.h>
#include <Wire.h>

#ifndef UTILS_H_
#define UTILS_H_

#define NAV_BUTTON 0
#define RO_A 4
#define RO_B 5

// RTC 

void initRTC(RTC_Millis *rtc);
DateTime getTime(RTC_Millis *rtc);

// ENCODER

int getPosition();

#endif
