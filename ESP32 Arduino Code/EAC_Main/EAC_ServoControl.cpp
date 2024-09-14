// Last update: 2024-09-14
// BR09 EAC Code: Comms_4

#include "EAC_ServoControl.h"

// Component Variables
Servo doorServoL;
Servo doorServoR;

void setupServos() {
    doorServoL.setPeriodHertz(50); // PWM frequency for SG90
    doorServoR.setPeriodHertz(50); 
    doorServoL.attach(Servo1_PWM1A, 500, 2400); // Minimum and maximum pulse width (in µs) 
    doorServoR.attach(Servo2_PWM1B, 500, 2400); // Minimum and maximum pulse width (in µs) 
}

void updateDoors(bool doorStatus) {
    if(doorStatus) {
        doorServoL.write(180);
        doorServoR.write(180);
        currentDoorStatus = true;
        Serial.println("Door Opened");
    } else {
        doorServoL.write(0);
        doorServoR.write(0);
        currentDoorStatus = false;
        Serial.println("Door Closed");
    }
}