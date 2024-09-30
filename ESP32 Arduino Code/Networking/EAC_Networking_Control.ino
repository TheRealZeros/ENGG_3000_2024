#include <WiFi.h>
#include <WiFiUDP.h>
#include <Serial.h>
#include <ArduinoJson.h>

class EAC_Networking_Control {
private:
    // WiFi Credentials
    const char* ssid = "EAC-Network";
    const char* password = "HolyMoly";
    
    // UDP Settings
    WiFiUDP udp;
    unsigned int localUdpPort = 4210;
    char incomingPacket[255];
    char packetBuffer[255];
    char replyPacket[1024];

    // JSON 
    StaticJsonDocument<1024> doc;

public:

    void setup() {
        Serial.begin(115200);
        connectToWiFi(ssid, password);
        startUDP(localUdpPort);
    }

    void loop() {
        checkUDPPacket();
    }

    void startUDP(unsigned int port) {
        udp.begin(port);
        Serial.printf("UDP server started at port %d\n", localUdpPort);
    }

    void connectToWiFi(string ssid, string password) {
        WiFi.begin(ssid, password);
        if (WiFi.begin() != WL_CONNECTED) {
            Serial.println("Connecting to WiFi...");
            while (WiFi.status() != WL_CONNECTED) {
                delay(1000);
                Serial.print(".");
            }
            Serial.println("Connected to WiFi");
        }
    }

    void checkUDPPacket() {
        int packetSize = udp.parsePacket();
        if (packetSize) {
            // Read the incoming packet into the buffer
            int len = udp.read(incomingPacket, 1024);
            if (len > 0) {
                incomingPacket[len] = 0; // Null-terminate the string
            }
            Serial.printf("Received packet of size %d\n", packetSize);
            Serial.printf("From %s, port %d\n", udp.remoteIP().toString().c_str(), udp.remotePort());
            Serial.printf("Message: %s\n", incomingPacket);
        }
    }

    void parseJSON(StaticJsonDocument doc) {
        DeserializationError error = deserializeJson(doc, incomingPacket);
        if (error) {
            Serial.print(F("Couldn't parse JSON: :( "));
            Serial.println(error.f_str());
        return;
        }
    }
}