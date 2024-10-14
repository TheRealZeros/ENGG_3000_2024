// External Libraries
import org.json.simple.JSONObject;

// Internal Libraries
import Enums.*;

public class CCP_Variables {

    public CCP_Variables() {
        while(true) {
            updateCCPMessage();
            updateLowLevelValues();
        }
    }
    
    // Carrage Information
    String carrageID = "BR09"; // Carrage ID
    Integer carrageSpeed;      // Carrage Speed
    D_Status doorStatus;       // Door Status
    M_Status motorStatus;      // Motor Status
    int lowLevelDoorStatus;    // currentDoorStatus as per EAC
    int lowLevelMotorStatus;   // currentMotorStatus as per EAC
    int lowLevelCarrageSpeed;  // currentSpeed as per EAC


    // Networking information
    // RECEVING
    public static volatile JSONObject eacMessageCCP = new JSONObject();
    static {
        eacMessageCCP.put("Type", "");
        eacMessageCCP.put("currentSpeed",  "");
        eacMessageCCP.put("dStatus", "");
        eacMessageCCP.put("mStatus",  "");
    }    
        

        /* {
         * "Type": "",
         * "currentSpeed": "",
         * "currentDoorStatus": "",
         * "dStatus": "",
         * "mStatus": ""
         * }
        */
        

    // SENDING
    public static volatile JSONObject ccpMessageEAC = new JSONObject();
    static {
        ccpMessageEAC.put("Type", "CCP");
        ccpMessageEAC.put("Message", "");
        ccpMessageEAC.put("targetSpeed", null);
        ccpMessageEAC.put("targetDoorStatus", null);
        ccpMessageEAC.put("targetMotorStatus", null);
    }

        /* {
         * "Type": "CCP",
         * "Message": "",
         * "targetSpeed": "",
         * "targetDoorStatus": "",
         * "targetMotorStatus": ""
         * }
        */

    //SENDING
    public static volatile JSONObject eacStatMessage = new JSONObject();
    static {
        eacStatMessage.put("Type", "CCP");
        eacStatMessage.put("Message", "STAT");
    }
    
        
        /* {
         * "Type": "CCP",
         * "Message": "STAT"
         * }
        */

    // RECEVING
    public static volatile JSONObject mcpMessageCCP = new JSONObject();
    static {
        mcpMessageCCP.put("client_type", "");
        mcpMessageCCP.put("message", "");
        mcpMessageCCP.put("client_id", "");
        mcpMessageCCP.put("action", "");
        mcpMessageCCP.put("status", "");
        mcpMessageCCP.put("br_id", "")
    }

    // SENDING
    public static volatile JSONObject ccpMessageMCP = new JSONObject();
    static {
        mcpMessageCCP.put("client_type", "");
        mcpMessageCCP.put("message", "");
        mcpMessageCCP.put("client_id", "");
        mcpMessageCCP.put("action", "");
        mcpMessageCCP.put("status", "");
        mcpMessageCCP.put("br_id", "")
    }

////////////// VARIBLE METHODS //////////////

            // Method to update the low level variables
            public void updateLowLevelValues() {
                lowLevelCarrageSpeed = Integer.parseInt((String) eacMessageCCP.get("currentSpeed"));
                lowLevelDoorStatus = Integer.parseInt((String) eacMessageCCP.get("dStatus"));
                lowLevelMotorStatus = Integer.parseInt((String) eacMessageCCP.get("mStatus"));
            }

            // Method to update ccpMessage with instance values
            public void updateCCPMessage() {
                ccpMessageEAC.put("targetSpeed", carrageSpeed);
                ccpMessageEAC.put("targetDoorStatus", doorStatus);
                ccpMessageEAC.put("targetMotorStatus", motorStatus);
            }


}
