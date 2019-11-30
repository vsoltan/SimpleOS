#include "display.h"
#include "buttons.h"

#define BAUD 115200

display * watchDisplay;

void setup() {
    Serial.begin(BAUD);
    watchDisplay = createDisplay();
}

long lastButtonPress = 0;
byte prev_state = 1;

void loop() {
  byte curr_state = digitalRead(POWERBUTTON);
  if (curr_state == 0 && prev_state == 1 && millis() >= lastButtonPress + DEBOUNCE) {
    togglePower(watchDisplay);
    lastButtonPress = millis();
  }
  prev_state = curr_state;
}
