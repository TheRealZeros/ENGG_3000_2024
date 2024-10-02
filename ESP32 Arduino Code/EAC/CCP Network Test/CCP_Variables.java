// External Libraries
import org.java.simple.JSONObject;

// Internal Libraries
import Enums.*;

public class CCP_Variables {
    
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
    public static volatile JSONDocument eacMessage = new JSONDocument();
        CCP_Variables.eacMessage.put("Type", "");
        CCP_Variables.eacMessage.put("currentSpeed",  "");
        CCP_Variables.eacMessage.put("dStatus", "");
        CCP_Variables.eacMessage.put("mStatus",  "");

        /* {
         * "Type": "",
         * "currentSpeed": "",
         * "currentDoorStatus": "",
         * "dStatus": "",
         * "mStatus": ""
         * }
        */

        lowLevelCarrageSpeed = eacMessage.getByName("currentSpeed");
        lowLevelDoorStatus = eacMessage.getByName("dStatus");
        lowLevelMotorStatus = eacMessage.getByName("mStatus");

    // SENDING
    public static volatile JSONDocument ccpMessage = new JSONDocument();
        ccpMessage.put("Type", "CCP");
        ccpMessage.put("Message", "");
        ccpMessage.put("targetSpeed", carrageSpeed);
        ccpMessage.put("targetDoorStatus", doorStatus);
        ccpMessage.put("targetMotorStatus", motorStatus);

        /* {
         * "Type": "CCP",
         * "Message": "",
         * "targetSpeed": "",
         * "targetDoorStatus": "",
         * "targetMotorStatus": ""
         * }
        */

    //SENDING
    public static volatile JSONDocument statMessage = new JSONObject();
        statMessage.put("Type", "CCP");
        statMessage.put("Message", "STAT");
        
        /* {
         * "Type": "CCP",
         * "Message": "STAT"
         * }
        */


}
