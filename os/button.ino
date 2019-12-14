#include "button.h"


void initNavButton(Button *button) {
  pinMode(NAV_BUTTON, INPUT_PULLUP);
  button->SetStateAndTime(LOW, 1000);
}
