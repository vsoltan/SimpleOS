
#include "display.h"
#include "buttons.h"

#define BAUD 115200

OLED u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
//DisplayStatus * displayStatus;
volatile bool displayOn = true;

void setup() {
    Serial.begin(BAUD);
    initializeDisplay(&u8g2);
//    displayStatus = createDisplayStatus();
    initializePeripherals();
}

unsigned long lastclick_time = 0; 

void IRAM_ATTR power() {
    if (millis() > lastclick_time + DEBOUNCE) {
         Serial.println("pressed");
         togglePower(displayOn, &u8g2);
         displayOn = !displayOn;
         lastclick_time = millis();
     }
 }

 void initializePeripherals() {
     pinMode(POWERBUTTON, INPUT_PULLUP);
     attachInterrupt(POWERBUTTON, power, FALLING);
 }

//long lastButtonPress = 0;
//byte prev_state = 1;

void loop() {
    u8g2.clearBuffer();         
    u8g2.drawStr(0, centerHeight, "Hello World!");  
    u8g2.sendBuffer();          
//    byte curr_state = digitalRead(POWERBUTTON);
//    if (curr_state == 0 && prev_state == 1 && millis() >= lastButtonPress + DEBOUNCE) {
//        togglePower(displayStatus, &u8g2);
//        lastButtonPress = millis();
//    }
//    prev_state = curr_state;
}
