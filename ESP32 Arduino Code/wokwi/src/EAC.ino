#include <Servo.h>

int MOTOR_PIN = 5;
int SERVO_PIN = 6;
Servo dcMotor;
Servo sgServo;

void setup() {
  dcMotor.attach(MOTOR_PIN);
  sgServo.attach(SERVO_PIN);
  Serial.begin(9600);
  Serial.println("Serial started");
  //conenctToCCP();
  //Serial.println("Connected to CCP");
  //setMotor(0);
  //setServo(0);
}

void loop() {

}

void setMotor(int) {
  
}

void setServo(int) {
  
}


/* 
if(CCP.command.equals("Forward")) {
    setMotor(speed);
}
*/