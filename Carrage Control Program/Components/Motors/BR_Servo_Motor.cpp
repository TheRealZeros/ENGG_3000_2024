#include "BR_Servo_Motor.h"

BR_Servo_Motor::BR_Servo_Motor() {
    
}

void BR_Servo_Motor::openDoor() {
    espNetworkCommands.ccpOpenDoor();
}

void BR_Servo_Motor::closeDoor() {
    espNetworkCommands.ccpCloseDoor();
}