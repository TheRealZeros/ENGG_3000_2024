// Last update: 2024-09-14
// BR09 EAC Code: Comms_4

#ifndef EAC_MOTORCONTROL_H
#define EAC_MOTORCONTROL_H

// Interal Libraries
#include "EAC_Variables.h"

// PIN Definitions
#define MotorPinA 27
#define MotorPinB 26
#define MotorPinP 14

// Function Declarations
void initialiseMotors();
void spinMotor();
void changeTargetSpeed(int mStatus);
void updateCurrentSpeed();


#endif // EAC_MOTORCONTROL_H