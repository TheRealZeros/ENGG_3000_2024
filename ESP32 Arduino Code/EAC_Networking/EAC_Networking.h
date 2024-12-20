#ifndef EAC_NETWORKING_H
#define EAC_NETWORKING_H

// External Libraries
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <stdlib.h>

// Network Variables
extern WiFiUDP udp;
extern char ssid[];
extern char pass[];
extern int udpPort;
extern char* udpAdd;


// Specific MSG Variables
extern char readBuffer[255];
extern char ccpMessage[];
extern char eacMessage[];

// Function Prototypes
const char* wifiStatusToString(wl_status_t status);
void initialiseWifi();
void initialiseUDP();
void firstUDPmsg();
void readUDPmsg();
void sendUDPmsg(const char msg[]);
void showLastmsg(const char type[]);

#endif // EAC_NETWORKING_H