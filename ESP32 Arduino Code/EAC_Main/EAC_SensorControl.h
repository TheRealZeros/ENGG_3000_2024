// Last update: 2024-10-8
// BR09 EAC Code: Comms_4

#ifndef EAC_SENSORCONTROL_H
#define EAC_SENSORCONTROL_H

#include "EAC_Variables.h"

#define trigPin1 34
#define echoPin1 35
#define trigPin2 12
#define echoPin2 13
#define speed 343

extern long duration1, duration2;

void initialiseSensors();
void readSensors();

#endif