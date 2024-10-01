#include "EAC_Networking.h"

void setup() {
    initialiseWifi();
    Serial.println("Wifi has started");
    delay(1000);
    initialiseUDP();
    Serial.println("UDP has started");
    delay(3000);
}

void loop() {
    
    readUDPmsg();

    delay(1000);
    if(ccpMessage == "CCP Says Hello World!") {
        sendUDPmsg("OKAY");
    }
    else {
        sendUDPmsg("NOPE");
    }
}