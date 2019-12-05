
#include "utils.h"

// RTC

void initRTC(RTC_Millis *rtc) {
    rtc->begin(DateTime(__DATE__, __TIME__)); 
}

void getTime(RTC_Millis *rtc, char *timeStamp) {
    DateTime now = rtc->now();
    sprintf(timeStamp, "%02hhu:%02hhu:%02hhu", now.hour(), now.minute(), now.second());
}

void getDate(RTC_Millis *rtc, char *date) {
    DateTime now = rtc->now();
    Serial.println(now.year(), DEC);
    sprintf(date, "%02hhu:%02hhu:%u", now.month(), now.day(), now.year());
}

RTCData *setRTCData(RTC_Millis *rtc) {
  RTCData *rtcda = NULL;
  rtcda = (RTCData *) malloc(sizeof(RTCData));

  if (rtcda == NULL) {
    exit(EXIT_FAILURE);
  }

  getTime(rtc, rtcda->timeStamp);
  getDate(rtc, rtcda->date);
  
  return rtcda;
}

// ENCODER NAVIGATION

/*
 * create a rotating queue of icons, to cycle through all possibilities on screen. 
 * If you turn to the left and run out in that direction, instead of stopping, highlight
 * the rightmost icon
 */
 */
