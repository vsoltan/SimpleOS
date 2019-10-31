
#include <Adafruit_SSD1306.h>

#define UIScreenWidth 128
#define UIScreenHeight 64
#define BAUD 9600
#define DEBOUNCE 300

#define POWERBUTTON 0

Adafruit_SSD1306 lcd(UIScreenWidth, UIScreenHeight);

void initializeDisplay() {
  lcd.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  lcd.setTextColor(WHITE);
  lcd.setTextSize(2); // use larger font
  lcd.setCursor(0,0); // set cursor to pixel (0,0)
  lcd.clearDisplay();
}

void initializePeripherals() {
  pinMode(POWERBUTTON, INPUT_PULLUP);
}

void sleepDisplay(Adafruit_SSD1306* display) {
  display->ssd1306_command(SSD1306_DISPLAYOFF);
}

void wakeDisplay(Adafruit_SSD1306* display) {
  display->ssd1306_command(SSD1306_DISPLAYON);
}

byte displayOn = 1;

void togglePower() {
  if (displayOn) {
    sleepDisplay(&lcd);
   } else {
    wakeDisplay(&lcd);
   }
   displayOn = !displayOn;
}

void setup() {
  Serial.begin(BAUD);
  initializeDisplay();
  initializePeripherals();
  lcd.println("Welcome to \n dumbOS");
  lcd.display();
}

long lastButtonPress = 0;
byte prev_state = 1;

void loop() {
  byte curr_state = digitalRead(POWERBUTTON);
  if (curr_state == 0 && prev_state == 1 && millis() >= lastButtonPress + DEBOUNCE) {
    togglePower();
    lastButtonPress = millis();
  }
  prev_state = curr_state;
}
