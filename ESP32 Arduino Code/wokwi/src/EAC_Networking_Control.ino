#include <WiFi.h>
#include <WiFiClient.h>
#include <SPI.h>
#include <ArduinoJson.h>

WiFiServer server(80);
WiFiClient client;
char buffer[256] = "";
//IPAddress host(127,0,0,1);
char ssid[] = "Wokwi-GUEST";

JsonDocument json;

void setup() {
  conenctToCCP();
}

void loop() {
  // put your main code here, to run repeatedly:
  if(client.connected()) {
    if(client.available()) {
      client.readBytes((char *)&buffer, 256);
      Serial.printf("buffer: %s\n", buffer);
      deserializeJson(json, buffer);
      Serial.printf("Speed is: %d\n", json["speed"].as<int>());
      Serial.printf("1 is: %d\n", json["1"]);
    }
  } else {
    client = server.available();
  }
}

void conenctToCCP() {
  WiFi.begin(ssid);
  Serial.println("wifi began");
  
  while(WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  server.begin();
  Serial.println("server started");
}

void serialiseJSON(JsonDocument json) {
  serializeJson(json, buffer);
  Serial.printf("buffer: %s\n", buffer);
}


/* 
if(CCP.command.equals("STAT")) {
    serialiseJSON(receivedJSON);
    sendData(JSONToSend);
}

*/