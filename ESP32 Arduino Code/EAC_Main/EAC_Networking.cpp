// Last update: 2024-09-14
// BR09 EAC Code: Comms_4

#include "EAC_Networking.h"

// Network Variables
WiFiUDP udp;
char readBuffer[255];
char ssid[] = "ENGG2K3K";
char pass[] = "";
int udpPort = 3009;
char* udpAdd = "10.20.30.176";

// JSON Variables
JsonDocument json;
JsonDocument newJson;
char ccpMessage[] = "";
char eacMessage[] = "";

// Functions
void startWifi() {
    Serial.begin(115200);
    WiFi.begin(ssid, pass);
    Serial.println("Wifi has started");
    while(WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    }
    Serial.println(WiFi.localIP());
}

void startUDP() {
    udp.begin(udpPort);
    Serial.println(udpPort);
    Serial.println("UDP has started");
    firstUDPmsg();
}

void firstUDPmsg() {
    const char* buffer = "EAC Says Hello World!";
    udp.beginPacket(udpAdd, udpPort);
    udp.write((const uint8_t*)buffer, strlen(buffer));
    udp.endPacket();
    Serial.println("First UDP message sent");
}

void readJson() {
    int packetSize = udp.parsePacket();
    if (packetSize) {
        int size = udp.read(readBuffer, packetSize);
        readBuffer[size] = '\0'; // Null-terminate the buffer
        Serial.println(readBuffer);
        Serial.println(currentSpeed);
        deserializeJson(json, readBuffer);

        targetSpeed = json["speed"].as<float>();
        targetDoorStatus = json["door"].as<bool>();
        strncpy(ccpMessage, json["message"].as<const char*>(), sizeof(ccpMessage) - 1);
        ccpMessage[sizeof(ccpMessage) - 1] = '\0'; // Ensure null-termination

        const char* buffer = "EAC has Received the JSON!";
        udp.beginPacket(udpAdd, udpPort);
        udp.write((const uint8_t*)buffer, strlen(buffer));
        udp.endPacket();
    }
}

void checkMsg(const char msg[]) {
    newJson["eacSpeed"] = currentSpeed;
    newJson["doorStatus"] = currentDoorStatus;
    newJson["motorStatus"] = currentMotorStatus;
    newJson["message"] = eacMessage;

    if(msg == "STAT") {
        char buffer[200];
        size_t n = serializeJson(newJson, buffer);
        udp.beginPacket(udpAdd, udpPort);
        udp.write((const uint8_t*)buffer, n);
        udp.endPacket();
    } else {
        const char* buffer = "EAC has recieved an invalid message!";
        udp.beginPacket(udpAdd, udpPort);
        udp.write((const uint8_t*)buffer, strlen(buffer));
        udp.endPacket();
    }
}