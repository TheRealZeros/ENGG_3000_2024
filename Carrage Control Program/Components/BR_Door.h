#ifndef BR_DOOR_H
#define BR_DOOR_H

#include "../Enumerations/Status.h"

class BR_Door {
    private:
        D_Status doorStatus;
    public:
        BR_Door();
        D_Status getDoorStatus();
        void setDoorStatus(D_Status doorStatus);
        void openDoor();
        void closeDoor();
};

#endif // BR_DOOR_H