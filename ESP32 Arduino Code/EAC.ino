#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include <stdlib.h>
#include <ESP32Servo.h>

#define CLK_DIR 17
#define EN_DIR 14
#define SER_DIR 12
#define Servo1_PWM1A 18
#define Servo2_PWM1B 19
#define MotorPinA 16
#define MotorPinB 17
#define MotorPinP 14
#define M1_PWM2A 23
#define Latch_DIR 19

Servo myServo1;
Servo myServo2;


WiFiUDP udp;
JsonDocument json;
static float acc = 10; // mm/s2
float targetSpeed = 180;
double speed = 0;
unsigned long oldTime = 0;
unsigned long currentTime = 0;
unsigned long deltaTime = 0;
char readBuffer[255];

//IPAddress host(127,0,0,1);

char ssid[] = "ENGG2K3K";
char pass[] = "";
int udpPort = 3009;
char* udpAdd = "10.20.30.176";

void readJson() {
  int packetSize = udp.parsePacket();
  if(packetSize) {
    int size = udp.read(readBuffer, packetSize);
    //readBuffer[size] = '\0';
    Serial.println(readBuffer);
    Serial.println(speed);
    deserializeJson(json, readBuffer);

    const uint8_t buffer[50] = "recieved!";
    udp.beginPacket(udpAdd, udpPort);
    udp.write(buffer, 11);
    udp.endPacket();
  }
}

void updateDoors() {
  myServo1.write(json["doors"].as<int>());
  myServo1.write(json["doors"].as<int>());
}

void updateMotors() {
  targetSpeed = json["speed"].as<float>();
  if(speed != targetSpeed) {
    double accDelta = (acc*deltaTime)/1000;
    if(abs(speed - targetSpeed) < accDelta) {
      speed = targetSpeed;
    } else if(speed > targetSpeed) {
      speed = speed - accDelta;
    } else {
      speed = speed + accDelta;
    }
  }
  if(targetSpeed = 10) {
    speed = 100;
  }
  digitalWrite(MotorPinP, speed);
}

void setup() {


  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  Serial.println("wifi began");
  while(WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
  udp.begin(udpPort);
  Serial.println(udpPort);
  Serial.println("udp began");

  pinMode(MotorPinA, OUTPUT);
  pinMode(MotorPinB, OUTPUT);
  pinMode(MotorPinP, OUTPUT);
  // digitalWrite(MotorPinA, HIGH);
  // digitalWrite(MotorPinB, LOW);
  myServo1.setPeriodHertz(50); // PWM frequency for SG90
  myServo2.setPeriodHertz(50); 
  myServo1.attach(Servo1_PWM1A, 500, 2400); // Minimum and maximum pulse width (in µs) 
  myServo2.attach(Servo2_PWM1B, 500, 2400); // Minimum and maximum pulse width (in µs) 

  const uint8_t buffer[50] = "hello world!";
  udp.beginPacket(udpAdd, udpPort);
  udp.write(buffer, 11);
  udp.endPacket();
  Serial.println("udp mesg sent");
}

void loop() {
  // put your main code here, to run repeatedly:
  currentTime = micros();
  deltaTime = currentTime - oldTime;
  oldTime = currentTime;

  readJson();
  digitalWrite(MotorPinA, HIGH);
  digitalWrite(MotorPinB, LOW);
  updateMotors();
  updateDoors();
  //Serial.printf(" millis: '%d'; delta: %d; accDelta: %f", currentTime, deltaTime, accDelta);
  //myServo1.write(speed);

//    //rotation from 0 to 180°
//   for (int pos = 0; pos <= 180; pos += 1) {
//     myServo1.write(pos);
//     myServo2.write(pos);
//     delay(10);
//   }
//  // Rotation from 180° to 0
//   for (int pos = 180; pos >= 0; pos -= 1) {
//     myServo1.write(pos);
//     myServo2.write(pos);
//     delay(10);
//   }
}
