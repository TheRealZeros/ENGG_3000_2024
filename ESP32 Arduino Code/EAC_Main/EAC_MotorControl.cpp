// Last update: 2024-09-14
// BR09 EAC Code: Comms_4

#include "EAC_MotorControl.h"


/* The following function will set the pins of the motor */
void setupMotors() {
  pinMode(MotorPinA, OUTPUT);
  pinMode(MotorPinB, OUTPUT);
  pinMode(MotorPinP, OUTPUT);
}

/* The following function will spin the motor from A and B awaiting P*/
void spinMotor() {
  digitalWrite(MotorPinA, HIGH);
  digitalWrite(MotorPinB, LOW);
}

/* The following function will update the motor speed depending on the current speed in tangent with the target speed, using the acceleration as the baseline */
void updateMotors() {
  if(currentSpeed != targetSpeed) {
    double accDelta = (acceleration*deltaTime)/1000;
    if(abs(currentSpeed - targetSpeed) < accDelta) {
      currentSpeed = targetSpeed;
    } else if(currentSpeed > targetSpeed) {
      currentSpeed = currentSpeed - accDelta;
    } else {
      currentSpeed = currentSpeed + accDelta;
    }
  }
  if(targetSpeed = 10) {
    currentSpeed = 100;
  }
  digitalWrite(MotorPinP, currentSpeed);
}