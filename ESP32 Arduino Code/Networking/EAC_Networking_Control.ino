#include <WiFiClient.h>
#include <ArduinoJson.h>
class EAC_Networking_Control
{
private:
    String ipAddress;
    int ccpPort;
    WiFiClient client;
    File receivedJSON;
    File JSONToSend;

public:
    // Constructor
    EAC_Networking_Control(String ip, int port) : ipAddress(ip), ccpPort(port)
    {
        ipAddress = "10.20.30.109";
        ccpPort = 3009;
    }

    void setup()
    {
        Serial.begin(9600);
        if (WiFi.begin() != WL_CONNECTED)
        {
            Serial.println("Connecting to WiFi...");
            while (WiFi.status() != WL_CONNECTED)
            {
                delay(1000);
                Serial.print(".");
            }
            Serial.println("Connected to WiFi");
        }
    }

    void loop()
    {
        if (client.connected())
        {
            sendData();
            receiveJSON();
        }
    }

    void connectToCCP()
    {
        if (!client.connect(ipAddress.c_str(), ccpPort))
        {
            Serial.println("Connection to CCP failed");
        }
        else
        {
            Serial.println("Connected to CCP");
        }
    }

    void sendData()
    {
        if (client.connected())
        {
            String jsonString;
            if (serialiseJSON(jsonString))
            {
                client.print(jsonString);
                Serial.println("Data sent: " + jsonString);
            }
            else
            {
                Serial.println("Failed to serialize JSON");
            }
        }
        else
        {
            Serial.println("Client not connected, cannot send data");
        }
    }

    // void createJSON()
    // {
    // }
    bool serialiseJSON(String &jsonString, String clientType, String message, int speed, String dStatus, String mStatus)
    {
        JsonDocument doc;

        doc["client_type"] = clientType;
        doc["message"] = message;
        doc["speed"] = speed;
        doc["dStatus"] = dStatus;
        doc["mStatus"] = mStatus;

        if (serializeJson(doc, jsonString) == 0)
        {
            return false; // Serialization failed
        }
        return true; // Successfully serialized
    }

    void deserialiseJSON(String jsonString)
    {
        JsonDocument doc;
        DeserializationError error = deserializeJson(doc, jsonString);

        if (error)
        {
            Serial.print(F("Failed to read JSON: "));
            Serial.println(error.f_str());
            return;
        }

        const char *clientType = doc["client_type"];
        const char *message = doc["message"];
        int speed = doc["speed"];
        const char *dStatus = doc["dStatus"];
        const char *mStatus = doc["mStatus"];

        // Print the received values unnecessary
        Serial.println("Received JSON:");
        Serial.println("client_type: " + String(clientType));
        Serial.println("message: " + String(message));
        Serial.println("speed: " + String(speed));
        Serial.println("dStatus: " + String(dStatus));
        Serial.println("mStatus: " + String(mStatus));
    }

    void receiveJSON()
    {
        if (client.available())
        {
            String jsonString = client.readStringUntil('\n');
            deserialiseJSON(jsonString);
        }
    }
}