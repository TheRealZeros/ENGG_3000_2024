// Last update: 2024-09-14
// BR09 EAC Code: Comms_4

#ifndef EAC_VARIABLES_H
#define EAC_VARIABLES_H

// External Libraries
#include <Arduino.h>

// Speed Variables (mm/s)
extern float acceleration;
extern float targetSpeed;
extern double currentSpeed;

// Status Variables
extern bool doorStatus;
extern bool currentDoorStatus;
extern bool currentMotorStatus; 
extern bool targetDoorStatus;

// Time Variables
extern unsigned long oldTime;
extern unsigned long currentTime;
extern unsigned long deltaTime;

// Functions
void getDeltaTime();

#endif // EAC_VARIABLES_H