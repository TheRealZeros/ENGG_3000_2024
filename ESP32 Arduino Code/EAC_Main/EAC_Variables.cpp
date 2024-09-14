// Last update: 2024-09-14
// BR09 EAC Code: Comms_4

#include "EAC_Variables.h"

// Speed Variables (mm/s)
float acceleration = 10;
float targetSpeed = 0;
double currentSpeed = 0;

// Status Variables
bool doorStatus = false;
bool currentDoorStatus = false;
bool targetDoorStatus = false;
bool currentMotorStatus = false;

// Time Variables
unsigned long currentTime = 0;
unsigned long oldTime = 0;
unsigned long deltaTime = 0;

/* This function will get an approximate time difference in comparissson of the rest of the time / micros function */
void getDeltaTime() {
  currentTime = micros();
  deltaTime = currentTime - oldTime;
  oldTime = currentTime;
}