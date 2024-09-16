// Last update: 2024-09-14
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
extern bool doorStatus;
extern bool currentDoorStatus;
extern bool targetDoorStatus;
extern int motorStatus;

// Time Variables
extern unsigned long oldTime;
extern unsigned long currentTime;
extern unsigned long deltaTime;

// LCD Variables
extern std::string messageStatic;
extern std::string messageToScroll;

// Functions
void getDeltaTime();
void updateDirection();

#endif // EAC_VARIABLES_H