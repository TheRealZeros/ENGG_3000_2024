#include "BR_DC_Motor.h"

BR_DC_Motor::BR_DC_Motor() {
    
}

void BR_DC_Motor::move(std::string direction) {
    if(direction == "forward") {
        espNetworkCommands.ccpForward();
    } else if(direction == "backward") {
        espNetworkCommands.ccpBackward();
    }
    else {
        printf("Invalid direction\n");
    }
}


void BR_DC_Motor::stop() {
    espNetworkCommands.ccpStop();
}


void BR_DC_Motor::emergencyStop() {
    espNetworkCommands.ccpEmergencyStop();
}