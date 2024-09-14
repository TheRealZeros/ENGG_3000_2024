// Last update: 2024-09-14
// BR09 EAC Code: Comms_4

#ifndef EAC_SERVOCONTROL_H
#define EAC_SERVOCONTROL_H

#include <ESP32Servo.h>
#include <Arduino.h>

// Internal libraries
#include "EAC_Variables.h"

// Pin Definitions
#define Servo1_PWM1A 18
#define Servo2_PWM1B 19

// Component Variables
extern Servo doorServoL;
extern Servo doorServoR;

void setupServos();
void updateDoors(bool doorStatus);

#endif // EAC_SERVOCONTROL_H