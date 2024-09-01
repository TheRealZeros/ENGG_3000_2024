
class EAC_Networking_Commands
{

    void ccpForward()
    {
        Serial.println("Moving forward...");
        speed = 32;
        String jsonString;
        if (serialiseJSON(jsonString, "CCP", "Forward", speed, "Closed", "On"))
        {
            // Send jsonString over the network
            sendData(jsonString);
        }
    }

    void ccpBackward()
    {
        Serial.println("Moving backward...");
        speed = -22;
        String jsonString;
        if (serialiseJSON(jsonString, "CCP", "Backward", speed, "Closed", "On"))
        {
            // Send jsonString over the network
            sendData(jsonString);
        }
    }

    void ccpStop()
    {
        Serial.println("Stopping...");
        speed = 0;
        String jsonString;
        if (serialiseJSON(jsonString, "CCP", "Stop", speed, "Closed", "On"))
        {
            // Send jsonString over the network
            sendData(jsonString);
        }
    }

    void ccpEmergencyStop()
    {
        Serial.println("Emergency Stop!");
        speed = 0;
        String jsonString;
        if (serialiseJSON(jsonString, "CCP", "Emergency_Stop", speed, "Closed", "Off"))
        {
            // Send jsonString over the network
            sendData(jsonString);
        }
    }

    void ccpOpenDoor()
    {
        Serial.println("Opening door...");
        String jsonString;
        if (serialiseJSON(jsonString, "CCP", "Open_Door", 0, "Open", "On"))
        {
            // Send jsonString over the network
            sendData(jsonString);
        }
    }

    void ccpCloseDoor()
    {
        Serial.println("Closing door...");
        String jsonString;
        if (serialiseJSON(jsonString, "CCP", "Close_Door", 0, "Closed", "On"))
        {
            // Send jsonString over the network
            sendData(jsonString);
        }
    }

    void eacStat()
    {
        Serial.println("Retrieving EAC status...");
        // This function might involve collecting current status data from EAC
        String jsonString;
        if (serialiseJSON(jsonString, "EAC", "Status", speed, "Closed", "On"))
        {
            // Send jsonString over the network
            sendData(jsonString);
        }
    }
}
