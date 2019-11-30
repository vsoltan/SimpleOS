#include <Adafruit_SSD1306.h>

#define UIScreenWidth 128
#define UIScreenHeight 64
#define TextSize 2

// textSize 1, character takes up 6 (width) by 8 (height) pixel matrix
#define widthScale 6
#define heightScale 8

#define staticTime "12:45"

#define centerWidth  (UIScreenWidth - widthScale * TextSize * strlen(staticTime))/2
#define centerHeight (UIScreenHeight - heightScale * TextSize)/2 

typedef struct {
    // other data regarding current display state
    volatile byte displayOn;
} DisplayStatus;

void initializeDisplay(Adafruit_SSD1306 *lcd);

DisplayStatus * createDisplayStatus();

void sleepDisplay(Adafruit_SSD1306 *display);

void wakeDisplay(Adafruit_SSD1306 *display);

void togglePower(DisplayStatus *watchDisplay, Adafruit_SSD1306 *lcd);
