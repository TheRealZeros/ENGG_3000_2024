#include "BR_Door.h"
#include "BR_EAC_Networking_Commands.h"

// Constructor implementation
BR_Door::BR_Door() {
    BR_EAC_Networking_Commands espNetworkCommands;
    doorStatus = D_Status::CLOSE;
}

// Member function implementation
D_Status BR_Door::getDoorStatus() {
    return doorStatus;
}

// Member function implementation
void BR_Door::setDoorStatus(D_Status status) {
    doorStatus = status;
}

void BR_Door::openDoor() {
    espNetworkCommands.ccpOpenDoor();
    doorStatus = D_Status::OPEN;
}

void BR_Door::closeDoor() {
    espNetworkCommands.ccpCloseDoor();
    doorStatus = D_Status::CLOSE;
}