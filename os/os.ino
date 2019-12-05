
#include "graphics.h"
#include "buttons.h"

#define BAUD 115200

// UTILITIES

OLED u8g2(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);
RotaryEncoder encoder(RO_A, RO_B);
RTC_Millis rtc;
DisplayInfo *oledInfo;

char timeStamp[9];
char date[30];

// GLOBALS

volatile byte displayOn = true;
volatile unsigned long lastclick_time = 0;
unsigned timeUpdateTick = 0;

void setup() {
    Serial.begin(BAUD);
    initializeDisplay(&u8g2);
    oledInfo = createDisplayInfo();
    initializePeripherals();
    initRTC(&rtc);
    drawHomeScreen(&u8g2);
}

// INTERRUPTS

void IRAM_ATTR power() {
    if (millis() > lastclick_time + DEBOUNCE) {
        Serial.println("pressed");
        togglePower(displayOn, &u8g2);
        displayOn = !displayOn;
        lastclick_time = millis();
    }
}

// INITIALIZERS

void initializePeripherals() {
    pinMode(POWERBUTTON, INPUT_PULLUP);
    attachInterrupt(POWERBUTTON, power, FALLING);
}

void loop() {
//  encoder.tick();

  getTime(&rtc, timeStamp);
  u8g2.clearBuffer();          // clear the internal memory
  u8g2.setFont(u8g2_font_ncenB08_tr); // choose a suitable font
  u8g2.drawStr(0,10, timeStamp);  // write something to the internal memory
  u8g2.sendBuffer();          // transfer internal memory to the display
  timeStamp[0] = '\0'; 
  date[0] = '\0';
 
//  if ()

  
  
//  static int pos = 0;
//  
//  int newPos = encoder.getPosition();
//  if (pos != newPos) {
//    Serial.print(newPos);
//    Serial.println();
//    pos = newPos;
//  } 
}

//long lastButtonPress = 0;
//byte prev_state = 1;
 
//    byte curr_state = digitalRead(POWERBUTTON);
//    if (curr_state == 0 && prev_state == 1 && millis() >= lastButtonPress + DEBOUNCE) {
//        togglePower(displayStatus, &u8g2);
//        lastButtonPress = millis();
//    }
//    prev_state = curr_state;
