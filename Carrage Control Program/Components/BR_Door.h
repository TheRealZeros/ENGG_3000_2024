#ifndef BR_DOOR_H
#define BR_DOOR_H

#include "../Enumerations/Status.h"
#include "BR_EAC_Networking_Commands.h"

class BR_Door {
    private:
        BR_EAC_Networking_Commands espNetworkCommands;
        D_Status doorStatus;
    public:
        BR_Door();
        D_Status getDoorStatus();
        void setDoorStatus(D_Status doorStatus);
        void openDoor();
        void closeDoor();
};

#endif // BR_DOOR_H