
#include "utils.h"

// RTC

void initRTC(RTC_Millis *rtc) {
    rtc->begin(DateTime(__DATE__, __TIME__)); 
}

DateTime getTime(RTC_Millis *rtc) {
    return rtc->now();
}
