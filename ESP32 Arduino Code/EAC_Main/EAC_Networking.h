// Last update: 2024-09-14
// BR09 EAC Code: Comms_4

#ifndef EAC_NETWORKING_H
#define EAC_NETWORKING_H

// External Libraries
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include <stdlib.h>
#include <ArduinoJson.h>

// Internal Libraries
#include "EAC_Variables.h"

// Network Variables
extern WiFiUDP udp;
extern char readBuffer[255];
extern char ssid[];
extern char pass[];
extern int udpPort;
extern char* udpAdd;


// Specific JSON Variables
extern JsonDocument json;
extern JsonDocument newJson;
extern char ccpMessage[];
extern char eacMessage[];

// Function Prototypes
void startWifi();
void startUDP();
void firstUDPmsg();
void readJson();
void checkMsgForSend(const char msg[]);

#endif // EAC_NETWORKING_H