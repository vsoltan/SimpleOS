
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
