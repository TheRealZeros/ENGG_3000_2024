// Last update: 2024-09-14
// BR09 EAC Code: Comms_4

#include "EAC_Networking.h"

// Network Variables
WiFiUDP udp;
char readBuffer[255];
char ssid[] = "ENGG2K3K";
char pass[] = "";
int udpPort = 3009;
char* udpAdd = "10.20.30.1";

// JSON Variables
JsonDocument json;
JsonDocument newJson;
char ccpMessage[] = "";
char eacMessage[] = "";

// Functions

/* The following function will start the WiFi as required */
void initialiseWifi() {
    Serial.begin(115200);
    WiFi.begin(ssid, pass);
    Serial.println("Wifi has started");
    while(WiFi.status() != WL_CONNECTED) {
        delay(100);
        Serial.print(".");
    }
    Serial.println(WiFi.localIP());
}

/* The following function will start the UDP as required */
void initialiseUDP() {
    udp.begin(udpPort);
    Serial.println(udpPort);
    Serial.println("UDP has started");
    firstUDPmsg();
}

/* The following function will send the first UDP message */
void firstUDPmsg() {
    const char* buffer = "EAC Says Hello World!";
    udp.beginPacket(udpAdd, udpPort);
    udp.write((const uint8_t*)buffer, strlen(buffer));
    udp.endPacket();
    Serial.println("First UDP message sent");
}

/* The following function will read the JSON message from the CCP and delegate the appropriate variables to the EAC variables*/
void readJson() {
    int packetSize = udp.parsePacket();
    if (packetSize) {
        int size = udp.read(readBuffer, packetSize);
        readBuffer[size] = '\0'; // Null-terminate the buffer
        Serial.println(readBuffer);
        deserializeJson(json, readBuffer);
        const char* buffer = "EAC has Received the JSON!";
        udp.beginPacket(udpAdd, udpPort);
        udp.write((const uint8_t*)buffer, strlen(buffer));
        udp.endPacket();
    }
}

void setJsonVariables() {
        targetSpeed = json["targetSpeed"].as<double>();
        targetDoorStatus = json["targetDoorStatus"].as<int>();
        targetMotorStatus = json["targetMotorStatus"].as<int>();
        strncpy(ccpMessage, json["Message"].as<const char*>(), sizeof(ccpMessage) - 1);
        ccpMessage[sizeof(ccpMessage) - 1] = '\0'; // Ensure null-termination
}

/* The following function will check the message that the EAC receives from the CCP and delegate them to the variables read by the EAC */
void checkMsgForSend(const char msg[]) {
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
        const char* buffer = "ACK";
        udp.beginPacket(udpAdd, udpPort);
        udp.write((const uint8_t*)buffer, strlen(buffer));
        udp.endPacket();
    }
}