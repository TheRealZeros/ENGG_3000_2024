// Last update: 2024-09-14
// BR09 EAC Code: Comms_4

#include "EAC_MotorControl.h"

void setupMotors() {
  pinMode(MotorPinA, OUTPUT);
  pinMode(MotorPinB, OUTPUT);
  pinMode(MotorPinP, OUTPUT);
}

void spinMotor() {
  digitalWrite(MotorPinA, HIGH);
  digitalWrite(MotorPinB, LOW);
}

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