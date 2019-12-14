
#include "utils.h"

// RTC

void initRTC(RTC_Millis *rtc) {
    rtc->begin(DateTime(__DATE__, __TIME__));
}

uint8_t getMinute(RTC_Millis *rtc) {
    return rtc->now().minute();
}

uint8_t getHour(RTC_Millis *rtc) {
    return rtc->now().hour();
}

void getTime(RTC_Millis *rtc, char *timeStamp) {
    DateTime now = rtc->now();
    sprintf(timeStamp, "%02hhu:%02hhu", now.hour(), now.minute());
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

// ENCODER

uint8_t bidirMod(int8_t n, uint8_t m) {
  if (n < 0) {
    return bidirMod(n + m, m);
  } return n % m;
}
