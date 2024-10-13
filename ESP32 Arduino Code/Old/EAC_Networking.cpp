#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include "network.h"

extern char ssid[];
extern char pass[];
extern WiFiUDP udp;
extern int udpPort;
extern char* udpAdd;

void startWifi() {
    WiFi.begin(ssid, pass);
    while (WiFi.status() != WL_CONNECTED) {
        delay(1000);
        Serial.println("Connecting to WiFi...");
    }
    Serial.println("Connected to WiFi");
}

void startUDP() {
    udp.begin(udpPort);
    Serial.println("UDP started");
}