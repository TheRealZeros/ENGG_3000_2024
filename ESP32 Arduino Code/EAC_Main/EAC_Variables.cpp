// Last update: 2024-10-8
// BR09 EAC Code: Comms_4

#include "EAC_Variables.h"

// Speed Variables (mm/s)
float acceleration = 10;
double targetSpeed = 0;      // WHAT WE WANT IT TO GO
double currentSpeed = 0;    // WHAT IT ACTUALLY IS GOING

// Status Variables
// Door
int targetDoorStatus = 0;  // WHAT WE WANT IT TO BE
int currentDoorStatus = 0; // WHAT IT ACTUALLY IS

// Motor
int targetMotorStatus = 0;
int currentMotorStatus = 0; 

// Time Variables
unsigned long currentTime = 0;
unsigned long oldTime = 0;
unsigned long deltaTime = 0;

// LCD Variables
std::string LCDmessageStatic = "Central";
std::string LCDmessageToScroll = "Stopping at A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P";

// Sensor Variables
extern long distance1 = 0;
extern long distance2 = 0;

/* This function will get an approximate time difference in comparissson of the rest of the time / micros function */
void getDeltaTime() {
  currentTime = micros();
  deltaTime = currentTime - oldTime;
  oldTime = currentTime;
}