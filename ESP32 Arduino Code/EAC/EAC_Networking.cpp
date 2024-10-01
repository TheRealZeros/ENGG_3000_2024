#include "EAC_Networking.h"

// Network Variables
WiFiUDP udp;
char ssid[] = "ENGG2K3K";
char pass[] = "";
int udpPort = 3009;
char* udpAdd = "10.20.30.176";

// MSG Variables
char readBuffer[255];
char ccpMessage[256];
char eacMessage[256];

// Functions
const char* wifiStatusToString(wl_status_t status) { 
    switch (status) {
        case WL_IDLE_STATUS:     return "Idle";
        case WL_NO_SSID_AVAIL:   return "SSID Not Available";
        case WL_SCAN_COMPLETED:  return "Scan Completed";
        case WL_CONNECTED:       return "Connected";
        case WL_CONNECT_FAILED:  return "Connection Failed";
        case WL_CONNECTION_LOST: return "Connection Lost";
        case WL_DISCONNECTED:    return "Disconnected";
        default:                 return "Unknown";
    }
}

/* The following function will start the WiFi as required */
void initialiseWifi() {
    Serial.println();
    Serial.println("Initializing Wi-Fi...");
    WiFi.begin(ssid, pass);
    Serial.print("Connecting to Wi-Fi network: ");
    Serial.println(ssid);

    unsigned long startAttemptTime = millis();
    const unsigned long timeout = 20000; // 20 seconds timeout

    while (WiFi.status() != WL_CONNECTED && millis() - startAttemptTime < timeout) {
        delay(1000);
        Serial.print("Attempting to connect... Status: ");
        Serial.println(wifiStatusToString(WiFi.status()));
    }

    if (WiFi.status() == WL_CONNECTED) {
        Serial.println("Connected to Wi-Fi network.");
        Serial.print("IP address: ");
        Serial.println(WiFi.localIP());
    } else {
        Serial.println("Failed to connect to Wi-Fi network.");
        Serial.println("IP address: 0.0.0.0");
    }
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
    
    strcpy(eacMessage, firstBuffer);
    Serial.println("First UDP message '" + String(firstBuffer) + "' sent");
}

void readUDPmsg() {
    int packetSize = udp.parsePacket();
    if (packetSize) {
        int size = udp.read(readBuffer, packetSize);
        readBuffer[size] = '\0';

        strcpy(ccpMessage, readBuffer);
        Serial.println("CCP message " + String(readBuffer) + " received");
    }
}

void sendUDPmsg(const char msg[]) {
    udp.beginPacket(udpAdd, udpPort);
        udp.write((const uint8_t*)msg, strlen(msg));
    udp.endPacket();

    strcpy(eacMessage, msg);
    Serial.println("UDP message '" + String(msg) + "' sent");
}

void showLastmsg(const char type[]) {
  if(type == "EAC") {
    Serial.println(eacMessage);
  }
  if(type == "CCP") {
    Serial.println(ccpMessage);
  } else {
    Serial.println("Choose CCP or EAC");
  }
}