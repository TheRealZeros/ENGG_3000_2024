#include "EAC_Networking.h"

void setup() {
    Serial.begin(115200);
    initialiseWifi();
    Serial.println("Wifi has started");
    
    delay(1000);
    initialiseUDP();
    Serial.println("UDP has started");
    
    delay(5000);
}

void loop() {
    readUDPmsg();

    if(ccpMessage == "") {
      sendUDPmsg("ACK? (Do 'HELLO WORLD!')");
    }

    if(ccpMessage == "HELLO WORLD!") {
        delay(1000);
        sendUDPmsg("OKAY HELLO!");
    } else {
        delay(5000);
        Serial.print(".");
    }

    sendUDPmsg("OKAY HELLO!");
    
}