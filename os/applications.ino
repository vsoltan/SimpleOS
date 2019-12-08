
#include "applications.h"
#include "display.h"

Window::Window(Icon **applications, uint8_t desc) {
  this->applications = applications;
  this->descriptor = desc;
}

void Window::runApp(uint8_t button) {

}

uint8_t Window::getDescriptor() {
  return this->descriptor;
}

void navigate(RotaryEncoder *encoder, Icon **icons, int *pos) {
    int newPos = encoder->getPosition();
    if (*pos != newPos) {
        icons[bidirMod(newPos, 3)]->renderHighlight(&tft);
        icons[bidirMod(*pos, 3)]->removeHighlight(&tft);
        *pos = newPos;
    }
}

//char timeBuffer[9];
//
//void runStopWatchApp(ColorDisplay *display) {}
//
//void display_MSm(ColorDisplay *display, unsigned long t, char *timeBuffer) {
//    int minutes = (t / 1000) / 60;
//    int seconds = (t / 1000) % 60;
//    int milliseconds = (t % 1000) / 10;

//    display->print(minutes / 10);
//    display->print(minutes % 10);
//    display->print(":");
//    display->print(seconds / 10);
//    display->print(seconds % 10);
//    display->print(":");
//    display->print(milliseconds / 10);
//    display->print(milliseconds % 10);
