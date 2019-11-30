#include <Adafruit_SSD1306.h>

#define UIScreenWidth 128
#define UIScreenHeight 64
#define staticTime "12:45"

typedef struct {
    byte displayOn;
    Adafruit_SSD1306 *lcd;
} display;

Adafruit_SSD1306 * initializeDisplay();

display * createDisplay();

void sleepDisplay(Adafruit_SSD1306 *display);

void wakeDisplay(Adafruit_SSD1306 *display);

void togglePower(display *displayStatus, Adafruit_SSD1306 *lcd);
