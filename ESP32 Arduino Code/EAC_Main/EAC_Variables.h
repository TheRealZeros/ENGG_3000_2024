// Last update: 2024-10-8
// BR09 EAC Code: Comms_4

#ifndef EAC_VARIABLES_H
#define EAC_VARIABLES_H

// External Libraries
#include <Arduino.h>
#include <string>

// Speed Variables (mm/s)
extern float acceleration;
extern float targetSpeed;
extern double currentSpeed;

// Status Variables
extern int doorStatus;
extern int currentDoorStatus;
extern int targetDoorStatus;
extern int motorStatus;

// Time Variables
extern unsigned long oldTime;
extern unsigned long currentTime;
extern unsigned long deltaTime;

// LCD Variables
extern std::string LCDmessageStatic;
extern std::string LCDmessageToScroll;

// Sensor Variables
extern long distance1;
extern long distance2;

// Functions
void getDeltaTime();
void updateDirection();

#endif // EAC_VARIABLES_H