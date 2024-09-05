#include <Arduino.h>
#include <Servo.h>
#include <ArduinoJson.h>

class EAC_Networking_Commands
{

    void ccpForward(String action)
    {
        if(action = "Slow") {
            Serial.println("Moving forward Slow...");
            targetSpeed = 25;
            mStatus = 1;
            dStatus = 0;
        } else if(action = "Fast") {
            Serial.println("Moving forward...");
            targetSpeed = 75;
            mStatus = 1;
            dStatus = 0;
        }
    }

    void ccpBackward()
    {
        Serial.println("Moving backward...");
        targetSpeed = -25;
        mStatus = 1;
        dStatus = 0;
    }

    void ccpStop()
    {
        Serial.println("Stopping...");
        targetSpeed = 0;
        mStatus = 0;
        dStatus = 0;
    }

    void ccpEmergencyStop()
    {
        Serial.println("Emergency Stop!");
        targetSpeed = 0;
        mStatus = 0;
        dStatus = 0;
    }

    void ccpOpenDoor()
    {
        Serial.println("Opening door...");
        dStatus = 1;

        if(error) {
            Serial.println("Error: Cannot open door");
            dStatus = 2;
        }
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
        Serial.println("EAC Status:");
        Serial.printf("Motor Status: %d\n", mStatus);
        Serial.printf("Door Status: %d\n", dStatus);
        Serial.printf("Current Speed: %d\n", currentSpeed);
        Serial.printf("Target Speed: %d\n", targetSpeed);
        

        StaticJsonDocument<1024> jsonDoc;
        jsonDoc["Motor Status"] = mStatus;
        jsonDoc["Door Status"] = dStatus;
        jsonDoc["Current Speed"] = currentSpeed;
        jsonDoc["Target Speed"] = targetSpeed;
    }
}
