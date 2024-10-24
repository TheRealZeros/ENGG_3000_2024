// Last update: 2024-09-14
// BR09 EAC Code: Comms_4

#include "EAC_ServoControl.h"

// Component Variables
Servo doorServoL;
Servo doorServoR;
int realTimeServo = 0;

/* The following function does the initial setup o the servo including the PWM frequcny and the .attach() function */
void initialiseServos() {
    doorServoL.attach(Servo1_PWM1A); // Minimum and maximum pulse width (in µs) 
    doorServoR.attach(Servo2_PWM1B); // Minimum and maximum pulse width (in µs) 
}

/* The following function will check the door status and if it is meant to be open (True) then it ill open otherwise do the opposite and close (False)*/
// servo stopped is 93
void updateDoors(int doorStatus) {
  // if(currentDoorStatus != doorStatus) {
  //   if(doorStatus == 1) {
  //     if(realTimeServo <= 10000) {
  //       doorServoL.writeTicks(180);
  //       doorServoR.writeTicks(180);
  //       realTimeServo += deltaTime;
  //       Serial.println("Door Opened");
  //     } else {
  //       currentDoorStatus = 1;
  //       realTimeServo = 0;
  //     }
  //   } else if(doorStatus = 0) {
  //     if(realTimeServo <= 10000) {
  //       doorServoL.writeTicks(0);
  //       doorServoR.writeTicks(0);
  //       realTimeServo += deltaTime;
  //       Serial.println("Door Opened");
  //     } else {
  //       currentDoorStatus = 0;
  //       realTimeServo = 0;
  //     }
  //       // doorServoL.writeTicks(0);
  //       // doorServoR.writeTicks(0);
  //       // currentDoorStatus = 0;
  //       Serial.println("Door Closed");
  //   } else {
  //       doorServoL.writeTicks(93);
  //       doorServoR.writeTicks(93);
  //   }
  // }
  if(targetDoorStatus != currentDoorStatus) {
    doorServoL.write(180*targetDoorStatus);
    doorServoR.write(180*targetDoorStatus);
    realTimeServo += deltaTime;
    if(realTimeServo > 1000000) {
      realTimeServo = 0;
      currentDoorStatus = targetDoorStatus;
    }
  } else {
    doorServoL.write(93);
    doorServoR.write(93);
  }
  Serial.printf("Servo current: %d, Servo target %d, Servo realTime: %d\n", currentDoorStatus, targetDoorStatus, realTimeServo);
}