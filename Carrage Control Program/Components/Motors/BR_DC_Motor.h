#ifndef BR_DC_MOTOR_H
#define BR_DC_MOTOR_H

#include "BR_EAC_Networking_Commands.h"
#include <string>

class BR_DC_Motor {
    private:
        BR_EAC_Networking_Commands espNetworkCommands;
    public:
        void move(std::string direction);
        void stop();
        void emergencyStop();
};

#endif // BR_DC_MOTOR_H