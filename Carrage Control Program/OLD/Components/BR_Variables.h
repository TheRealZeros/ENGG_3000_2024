#ifndef BR_Variables_H
#define BR_Variables_H

#include "../Enumerations/Status.h"
#include <string>

class BR_Variables {
    private:
        std::string carrageID;
        int carrageSpeed;
        C_Status carrageStatus;
    public:
        BR_Variables();
        C_Status getCarrageStatus();
        void setCarrageStatus(C_Status carrageStatus);
        std::string getCarrageID();
        void setCarrageID(std::string carrageID);
        int getCarrageSpeed();
        void setCarrageSpeed(int carrageSpeed);
};

#endif // BR_Variables_H