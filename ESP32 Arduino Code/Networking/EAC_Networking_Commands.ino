#include <Arduino.h>
#include <Servo.h>
#include <ArduinoJson.h>

class EAC_Networking_Commands
{

    void ccpForward()
    {
        Serial.println("Moving forward...");
        speed = 32;
        mStatus = 1;
        dStatus = 0;
    }

    void ccpBackward()
    {
        Serial.println("Moving backward...");
        speed = -22;
        mStatus = 1;
        dStatus = 0;
    }

    void ccpStop()
    {
        Serial.println("Stopping...");
        speed = 0;
        mStatus = 0;
        dStatus = 0;
    }

    void ccpEmergencyStop()
    {
        Serial.println("Emergency Stop!");
        speed = 0;
        mStatus = 0;
        dStatus = 0;
    }

    void ccpOpenDoor()
    {
        Serial.println("Opening door...");
        dStatus = 1;
    }

    void ccpCloseDoor()
    {
        Serial.println("Closing door...");
        dStatus = 0;

        if(error) {
            Serial.println("Error: Cannot close door");
            dStatus = 2;
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
