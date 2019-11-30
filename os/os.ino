
#include "display.h"
#include "buttons.h"

#define BAUD 115200

Adafruit_SSD1306 lcd(UIScreenWidth, UIScreenHeight);
DisplayStatus * displayStatus;

void setup() {
    Serial.begin(BAUD);
    initializeDisplay(&lcd);
    displayStatus = createDisplayStatus();
    // initializePeripherals();
}

/*
 * TODO: tried to convert to an interrupt but it didn't work
 
 unsigned long lastclick_time = 0; 

 void IRAM_ATTR power() {
     if (millis() > lastclick_time + DEBOUNCE) {
         Serial.println("pressed");
         togglePower(displayStatus, &lcd);
         lastclick_time = millis();
     }
 }

 void initializePeripherals() {
     pinMode(POWERBUTTON, INPUT_PULLUP);
     attachInterrupt(POWERBUTTON, power, FALLING);
 }
 */

long lastButtonPress = 0;
byte prev_state = 1;

void loop() {
    byte curr_state = digitalRead(POWERBUTTON);
    if (curr_state == 0 && prev_state == 1 && millis() >= lastButtonPress + DEBOUNCE) {
        togglePower(displayStatus, &lcd);
        lastButtonPress = millis();
    }
    prev_state = curr_state;
}
