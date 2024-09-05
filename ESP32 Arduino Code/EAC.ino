#include <ESP32Servo.h>

Servo dcMotor;
Servo sgServo1;
Servo sgServo2;

int MOTOR_PIN = 5;
int SERVO_PIN = 6;

void setup() {

}

void loop() {

    setMotor(targetSpeed);
    serial.delay(200);

    if(dStatus = 0) {
        setServo(0);
    } else {
        setServo(180);
    }
    
}

void setMotor(int x) {
    speedRateChange(x);
    dcMotor.write(currentSpeed)
}

void setServo(int x) {
    sgServo1.write(x);
    sgServo2.write(x);
}

void speedRateChange() {
    if(x != currentSpeed && currentSpeed < x) {
        currentSpeed + speedChangeRate;
    } else if(x != currentSpeed && currentSpeed > x) {
        currentSpeed - speedChangeRate;
    }
}