// Last update: 2024-09-14
// BR09 EAC Code: Comms_4

#include "EAC_Variables.h"

// Speed Variables (mm/s)
float acceleration = 10;
float targetSpeed = 0;      // WHAT WE WANT IT TO GO
double currentSpeed = 0;    // WHAT IT ACTUALLY IS GOING

// Status Variables
// Door
bool targetDoorStatus = false;  // WHAT WE WANT IT TO BE
bool currentDoorStatus = false; // WHAT IT ACTUALLY IS

// Motor
int motorStatus = 0; 

// Time Variables
unsigned long currentTime = 0;
unsigned long oldTime = 0;
unsigned long deltaTime = 0;

// LCD Variables
std::string LCDmessageStatic = "Central";
std::string LCDmessageToScroll = "Stopping at A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P";

/* This function will get an approximate time difference in comparissson of the rest of the time / micros function */
void getDeltaTime() {
  currentTime = micros();
  deltaTime = currentTime - oldTime;
  oldTime = currentTime;
}

void updateDirection() {
  if(targetSpeed < 0) {
    motorStatus = 0;
  } else {
    motorStatus = 1;
  }
  delay(200);
}