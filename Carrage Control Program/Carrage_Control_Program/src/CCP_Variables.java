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
        eacMessage.put("Type", "");
        eacMessage.put("currentSpeed",  "");
        eacMessage.put("dStatus", "");
        eacMessage.put("mStatus",  "");
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
        ccpMessage.put("Type", "CCP");
        ccpMessage.put("Message", "");
        ccpMessage.put("targetSpeed", null);
        ccpMessage.put("targetDoorStatus", null);
        ccpMessage.put("targetMotorStatus", null);
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
        statMessage.put("Type", "CCP");
        statMessage.put("Message", "STAT");
    }
    
        
        /* {
         * "Type": "CCP",
         * "Message": "STAT"
         * }
        */

    // RECEVING
    public static volatile JSONObject mcpMessageCCP = new JSONObject();
    static {
        mcpMessage.put("Type", "");
        mcpMessage.put("Message", "");
        mcpMessage.put("targetSpeed", "");
        mcpMessage.put("targetDoorStatus", "");
        mcpMessage.put("targetMotorStatus", "");
    }

    // SENDING
    public static volatile JSONObject ccpMessageMCP = new JSONObject();
    static {
        mcpMessage.put("Type", "");
        mcpMessage.put("Message", "");
        mcpMessage.put("targetSpeed", "");
        mcpMessage.put("targetDoorStatus", "");
        mcpMessage.put("targetMotorStatus", "");
    }

////////////// VARIBLE METHODS //////////////

            // Method to update the low level variables
            public void updateLowLevelValues() {
                lowLevelCarrageSpeed = Integer.parseInt((String) eacMessage.get("currentSpeed"));
                lowLevelDoorStatus = Integer.parseInt((String) eacMessage.get("dStatus"));
                lowLevelMotorStatus = Integer.parseInt((String) eacMessage.get("mStatus"));
            }

            // Method to update ccpMessage with instance values
            public void updateCCPMessage() {
                ccpMessage.put("targetSpeed", carrageSpeed);
                ccpMessage.put("targetDoorStatus", doorStatus);
                ccpMessage.put("targetMotorStatus", motorStatus);
            }


}
