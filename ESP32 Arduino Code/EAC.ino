#include <Servo.h>

Servo dcMotor;
Servo sgServo;

int MOTOR_PIN = 5;
int SERVO_PIN = 6;

void setup() {

}

void loop() {
    
    while(mStatus = 1) {
        setMotor(speed);
        serial.delay(200);
    }

    if(dStatus = 0) {
        setServo(0);
    } else {
        setServo(180);
    }
    
}

void setMotor(int x) {
    
    dcMotor.attach(MOTOR_PIN);
    dcMotor.write(255);

}

void setServo(int) {

}