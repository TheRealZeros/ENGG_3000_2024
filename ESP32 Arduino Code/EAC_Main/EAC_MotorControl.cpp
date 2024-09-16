// Last update: 2024-09-14
// BR09 EAC Code: Comms_4

#include "EAC_MotorControl.h"


/* The following function will set the pins of the motor */
void initialiseMotors() {
  pinMode(MotorPinA, OUTPUT);
  pinMode(MotorPinB, OUTPUT);
  pinMode(MotorPinP, OUTPUT);
}

/* The following function will spin the motor from A and B awaiting P*/
void spinMotor() {
  digitalWrite(MotorPinA, HIGH);
  digitalWrite(MotorPinB, LOW);
}

/* The following function checks motor status */
void changeTargetDirection(int mStatus) {

  // If motor should be REVERSE (0)
  if(mStatus == 0) {
    digitalWrite(MotorPinA, LOW);
    digitalWrite(MotorPinB, HIGH);
  } else 
  // If motor should be FULL POWER (1)
  if(mStatus == 1) {
    digitalWrite(MotorPinA, HIGH);
    digitalWrite(MotorPinB, LOW); 
  } 
  delay(200);
}

/* The following function will update the motor speed depending on the current speed in tangent with the target speed, using the acceleration as the baseline */
void updateCurrentSpeed(int mStatus) {

  while(currentSpeed != targetSpeed) {
    if(currentSpeed < targetSpeed) {
      currentSpeed += acceleration;
    } else if(currentSpeed > targetSpeed) {
      currentSpeed -= acceleration;
    }
  }
  digitalWrite(MotorPinP, currentSpeed);
  delay(200);
}