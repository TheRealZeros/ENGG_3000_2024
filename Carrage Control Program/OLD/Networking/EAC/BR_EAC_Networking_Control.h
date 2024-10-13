#ifndef BR_EAC_Networking_Control_H
#define BR_EAC_Networking_Control_H

#include <string>
#include "BR_EAC_Networking_Commands.h"
#include "BR_EAC_Variables.h"
#include "BR_CCP_Variables.h"
#include <nlohmann/json.hpp>

class BR_EAC_Networking_Control {
    private:
        std::string ipAdress;
        nlohmann::json receivedJSON;
        nlohmann::json JSONToSend;


    public:
        BR_EAC_Networking_Commands commands;
        BR_EAC_Variables eacVariables;
        BR_CCP_Variables ccpVariables;
};

#endif // BR_EAC_Networking_Control_H