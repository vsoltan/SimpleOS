
#include "graphics.h"

Icon::Icon(uint8_t x, uint8_t y, uint8_t width, uint8_t height, const unsigned char *icon, const char *label, uint8_t descriptor, uint16_t color) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->icon = icon;
    this->label = label;
    this->destinationDescriptor = descriptor;
    this->color = color;
}

uint8_t Icon::getX() {
    return this->x;
}

uint8_t Icon::getY() {
    return this->y;
}

uint8_t Icon::getWidth() {
    return this->width;
}

uint8_t Icon::getHeight() {
    return this->height;
}

const char *Icon::getLabel() {
    return this->label;
}

void Icon::renderHighlight(ColorDisplay *display) {
  // set colored border to indicate icon is selected
    display->drawRect(this->x - highlightPadding, this->y - highlightPadding, this->width + 2 * highlightPadding, this->height + 2 * highlightPadding, DEFAULT_HIGHLIGHT);
}

void Icon::removeHighlight(ColorDisplay *display) {
    display->drawRect(this->x - highlightPadding, this->y - highlightPadding, this->width + 2 * highlightPadding, this->height + 2* highlightPadding, DEFAULT_BACKGROUND);
}

void Icon::drawIcon(ColorDisplay *display) {
    display->drawXBitmap(this->x, this->y, this->icon, this->width, this->height, this->color);
}

void Icon::setIcon(const unsigned char *newIcon) {
    this->icon = newIcon;
}

void Icon::setColor(uint16_t color) {
    this->color = color;
}

uint8_t Icon::getDestinationDescriptor() {
    return this->destinationDescriptor;
}

void showBluetoothConnected(ColorDisplay *display) {
    display->drawCircle(7, 7, 3, WHITE);
}

void showBluetoothDisconnected(ColorDisplay *display) {
    display->drawCircle(7, 7, 3, DEFAULT_BACKGROUND);
}

void drawHomeScreen(ColorDisplay *display, AppStatus *appStatus) {
    showBluetoothStatus(display, appStatus);
}

void drawWeatherScreen(ColorDisplay *display, AppStatus *appStatus) {
    display->setFont();
    display->setTextColor(WHITE, DEFAULT_BACKGROUND);
    
    if (*appStatus->bluetoothConnection) {
      
      if (*appStatus->weatherDataReceived) {
        display->fillRect(0, 0, 128, 95, DEFAULT_BACKGROUND);
        *appStatus->newWeatherData = false;

        char *description;
        uint8_t pos;

        switch((int)(*appStatus->weatherObj)["weather"][0]["id"] / 100) {
          case THUNDERSTORM: 
              appStatus->weatherIcon = thunder_bits;
              appStatus->iconColor = ORANGE;
              description = "Thunder";
              pos = 16;
              break;
          case DRIZZLE: 
              appStatus->weatherIcon = drizzle_bits;
              appStatus->iconColor= RED;
              description = "Drizzle";
              pos = 16;
          case RAIN:
              appStatus->weatherIcon = rain_bits;
              appStatus->iconColor = CYAN;
              description = "Raining";
              pos = 15;
              break;
          case SNOW:
              appStatus->weatherIcon = snow_bits;
              appStatus->iconColor = WHITE;
              description = "Snowing";
              pos = 16;
              break;
          case ATMOSPHERE:
              appStatus->weatherIcon = cloud_bits;
              appStatus->iconColor = WHITE; 
              description = "Foggy";
              pos = 30;
              break;
          case CLOUDS:
              // clear case
              if ((int)(*appStatus->weatherObj)["weather"][0]["id"] == 800) {
                  appStatus->weatherIcon = sun_bits;
                  appStatus->iconColor = YELLOW;
                  description = "Sunny";
                  pos = 31;
              } else {
                  appStatus->weatherIcon = cloud_bits;
                  appStatus->iconColor = WHITE;   
                  description = "Cloudy";
                  pos = 23;
              }
              break;
          default:
              perror("undefined weather type");
              break; 
        }

        display->drawXBitmap(0, 0, appStatus->weatherIcon, 60, 60, appStatus->iconColor);

        display->setCursor(65, 20);
        display->print("temp: ");
        display->print((int)(*appStatus->weatherObj)["main"]["temp"]);

        display->setCursor(65, 30);
        display->print("max:  ");
        display->print((int)(*appStatus->weatherObj)["main"]["temp_max"]);

        display->setCursor(65, 40);
        display->print("min:  ");
        display->println((int)(*appStatus->weatherObj)["main"]["temp_min"]);

        display->setFont(DEFAULT_FONT);
        display->setCursor(pos, 80);
        display->print(description);
        
    } else if (*appStatus->newWeatherData){
      display->fillRect(0, 0, 128, 95, DEFAULT_BACKGROUND);
      display->setCursor(20, 20);
      display->print("loading...");
      delay(200);
    }
  } else {
    display->setCursor(15, 20);
    display->print("Please connect");
    display->setCursor(15, 30);
    display->print("to a bluetooth");
    display->setCursor(15, 40);
    display->print("device");
  }
}

void displayFormatedStopwatch(ColorDisplay *display, unsigned long t) {
    int minutes = (t / 1000) / 60;
    int seconds = (t / 1000) % 60;
    int milliseconds = (t % 1000) / 10;

    display->print(minutes / 10);
    display->print(minutes % 10);
    display->print(":");
    display->print(seconds / 10);
    display->print(seconds % 10);
    display->print(":");
    display->print(milliseconds / 10);
    display->print(milliseconds % 10);
}

void drawStopWatchScreen(ColorDisplay *display, AppStatus *appStatus) {
    showBluetoothStatus(display, appStatus);
    display->setFont();
    display->setTextSize(2);
    display->setCursor(SWATCH_CENTER, 20);
    if (appStatus->stopWatchCurrTime != 0) {
      displayFormatedStopwatch(display, appStatus->stopWatchCurrTime);
    } else {
      display->print("00:00:00");
    }
}

void drawMusicScreen(ColorDisplay *display, AppStatus *appStatus) {
    showBluetoothStatus(display, appStatus);
    display->setFont(DEFAULT_FONT);
    display->setCursor(30, 20);
    display->print("Music");
}

void drawPageIcons(Icon **appIcons, ColorDisplay *display, uint8_t numIcons) {
    Serial.println(sizeof(appIcons) / sizeof(appIcons[0]));
    for (int i = 0; i < numIcons; i = i + 1) {
        appIcons[i]->drawIcon(display);
    }
}
