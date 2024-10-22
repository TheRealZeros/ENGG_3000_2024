// Last update: 2024-09-14
// BR09 EAC Code: Comms_4

#include "EAC_ServoControl.h"

// Component Variables
Servo doorServoL;
Servo doorServoR;

/* The following function does the initial setup o the servo including the PWM frequcny and the .attach() function */
void initialiseServos() {
    doorServoL.setPeriodHertz(50); // PWM frequency for SG90
    doorServoR.setPeriodHertz(50); 
    doorServoL.attach(Servo1_PWM1A, 500, 2500); // Minimum and maximum pulse width (in µs) 
    doorServoR.attach(Servo2_PWM1B, 500, 2500); // Minimum and maximum pulse width (in µs) 
}

/* The following function will check the door status and if it is meant to be open (True) then it ill open otherwise do the opposite and close (False)*/
void updateDoors(int doorStatus) {
    if(doorStatus == 1) {
        doorServoL.writeTicks(190);
        doorServoR.writeTicks(190);
        currentDoorStatus = 1;
        //Serial.println("Door Opened");
    } else {
        doorServoL.writeTicks(0);
        doorServoR.writeTicks(0);
        currentDoorStatus = 0;
        //Serial.println("Door Closed");
    }
}