// Last update: 2024-10-8
// BR09 EAC Code: Comms_4

#ifndef EAC_LEDCONTROL_H
#define EAC_LEDCONTROL_H
#include "EAC_Variables.h"

#define Rpin 32
#define Ypin 33
#define Gpin 25

void initialiseLED();
void setRLED(bool input);
void setYLED(bool input);
void setGLED(bool input);

#endif