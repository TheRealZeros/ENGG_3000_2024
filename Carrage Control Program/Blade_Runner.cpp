#include "../Components/BR_Door.h"
#include "../Components/BR_Engine.h"
#include "../Components/BR_Variables.h"

class Blade_Runner {
private:
    BR_Variables bladeRunnerInfo;
    BR_Door bladeRunnerDoor;
    BR_Engine bladeRunnerEngine;
    BR_EAC_Networking_Control espNetwork;
    BR_MCP_Networking_Control mcpNetwork;

    
public:
    void initialiseRunner() {
        bladeRunnerInfo.setCarrageID("BR09");
        bladeRunnerInfo.setCarrageSpeed(0);
        bladeRunnerInfo.setCarrageStatus(C_Status::ON);
        mcpNetwork.connectToMCP();
    }

    void moveRunner() {
        
    }

    void stopRunner() {
        
    }

    void emergancyStop() {
        
    }

};