#ifndef BR_Servo_MOTOR_H
#define BR_Servo_MOTOR_H

#include "BR_EAC_Networking_Commands.h"

class BR_Servo_Motor {
    private:
        BR_EAC_Networking_Commands espNetworkCommands;
    public:
        BR_Servo_Motor();
        void openDoor();
        void closeDoor();
};

#endif // BR_Servo_MOTOR_H