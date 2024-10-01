#include "EAC_Networking.h"

// Network Variables
WiFiUDP udp;
char ssid[] = "ENGG2K3K";
char pass[] = "";
int udpPort = 3009;
char* udpAdd = "10.20.30.176";

// MSG Variables
char readBuffer[255];
char ccpMessage[] = "";
char eacMessage[] = "";

// Functions

/* The following function will start the WiFi as required */
void initialiseWifi() {
    Serial.begin(115200);
    WiFi.begin(ssid, pass);
    while(WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.print(".");
    }
    Serial.println(WiFi.localIP());
}

/* The following function will start the UDP as required */
void initialiseUDP() {
    udp.begin(udpPort);
    Serial.println(udpPort);
    firstUDPmsg();
}

/* The following function will send the first UDP message */
void firstUDPmsg() {
    const char* firstBuffer = "EAC Says Hello World!";
    udp.beginPacket(udpAdd, udpPort);
        udp.write((const uint8_t*)firstBuffer, strlen(firstBuffer));
    udp.endPacket();
    
    eacMessage = firstBuffer;
    Serial.println("First UDP message '" + firstBuffer + "' sent");
}

void readUDPmsg() {
    int packetSize = udp.parsePacket();
    if (packetSize) {
        int size = udp.read(readBuffer, packetSize);
        readBuffer[size] = '\0';

        ccpMessage = readBuffer;
        Serial.println("CCP message " + readBuffer + " received");
    }
}

void sendUDPmsg(const char msg[]) {
    udp.beginPacket(udpAdd, udpPort);
        udp.write((const uint8_t*)msg, strlen(msg));
    udp.endPacket();

    eacMessage = msg;
    Serial.println("UDP message '" + msg + "' sent");
}
