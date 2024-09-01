#ifndef BR_EAC_Networking_Commands_H
#define BR_EAC_Networking_Commands_H

class BR_EAC_Networking_Commands {
    public:
        void ccpForward();
        void ccpBackward();
        void ccpStop();
        void ccpEmergencyStop(); 
        void ccpOpenDoor();
        void ccpCloseDoor();
        void eacStat();
};

#endif // BR_EAC_Networking_Commands_H