#include "BR_Door.h"

// Constructor implementation
BR_Door::BR_Door() {
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
    // Implementation for opening the door
}

void BR_Door::closeDoor() {
    // Implementation for closing the door
}