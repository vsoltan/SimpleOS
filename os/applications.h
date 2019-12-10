
#include "graphics.h"

#ifndef APPLICATIONS_H_
#define APPLICATIONS_H_

class Window {
  
  private:
    Icon **applications;
    uint8_t descriptor;

  public:
    Window(Icon **applications, uint8_t desc);
    uint8_t getDescriptor();
    Icon **getApplications();

};

void navigate(RotaryEncoder *encoder, Icon **icons, int *pos);


#endif
