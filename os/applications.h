
#include "graphics.h"

#ifndef APPLICATIONS_H_
#define APPLICATIONS_H_

#define HOME_D   0
#define SWATCH_D 1

class Window {
  private:
    Icon **applications;
    uint8_t descriptor;

  public:
    Window(Icon **applications, uint8_t desc);
    void runApp(uint8_t button);
    uint8_t getDescriptor();
};

void navigate(RotaryEncoder *encoder, Icon **icons, int *pos);


#endif
