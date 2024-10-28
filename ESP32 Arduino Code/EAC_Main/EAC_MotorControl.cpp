// Last update: 2024-09-17
// BR09 EAC Code: Comms_4

#include "EAC_MotorControl.h"

int oldSpeed = 0;


/* The following function will set the pins of the motor */
void initialiseMotors() {
  pinMode(MotorPinA, OUTPUT);
  pinMode(MotorPinB, OUTPUT);
  pinMode(MotorPinP, OUTPUT);
  digitalWrite(MotorPinA, LOW);
  digitalWrite(MotorPinB, HIGH);
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
}

/* The following function will update the motor speed depending on the current speed in tangent with the target speed, using the acceleration as the baseline */
void updateCurrentSpeed() { 
  Serial.printf("speed before: %lf ", currentSpeed);
  while(currentSpeed != targetSpeed) {
    if(currentSpeed < targetSpeed) {
      currentSpeed += (acceleration * deltaTime) / 1000000;
    } else if(currentSpeed > targetSpeed) {
      currentSpeed -= (acceleration * deltaTime) / 1000000;
    }
  }
  currentSpeed = targetSpeed;
  Serial.printf("speed after: %lf\n", currentSpeed);
  Serial.printf("targetSpeed: %lf\n", targetSpeed);
  analogWrite(MotorPinP, abs(currentSpeed));
}

// emergency stopping! quick, reversable
void forceStop() {
  analogWrite(MotorPinP, 0);
  digitalWrite(MotorPinA, LOW);
  digitalWrite(MotorPinB, LOW);
  oldSpeed = currentSpeed;
  currentSpeed = 0;
} 

// after using forcestop, use this to start again
void restartMotor() {
  currentSpeed = oldSpeed;
  digitalWrite(MotorPinA, LOW);
  digitalWrite(MotorPinB, HIGH);
  analogWrite(MotorPinP, currentSpeed);
}

// slows down normally, same as targetSpeed = 0;
void stop() {
  while(currentSpeed != 0) {
    if(currentSpeed > 0) {
      currentSpeed -= acceleration;
    } else if (currentSpeed < 0) {
      currentSpeed += acceleration;
    }
  }
  digitalWrite(MotorPinP, currentSpeed);
}