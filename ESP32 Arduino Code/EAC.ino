// Last update: 2024-09-14
// BR09 EAC Code: Comms_4

// Libraries
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include <stdlib.h>
#include <ESP32Servo.h>

// PIN Definitions
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

// Component Variables
Servo doorServoL;
Servo doorServoR;

// Network Variables
WiFiUDP udp;
char readBuffer[255];
char ssid[] = "ENGG2K3K";
char pass[] = "";
int udpPort = 3009;
char* udpAdd = "10.20.30.176";
JsonDocument json;

// EAC Variables
static float acc = 10; // mm/s2
float targetSpeed = 180;
double currentSpeed = 0;

// Time Variables
unsigned long oldTime = 0;
unsigned long currentTime = 0;
unsigned long deltaTime = 0;

///////////////////////////////////////// Intial ESP32 Setup /////////////////////////////////////////
void setup() {
  
  startWifi();
  startUDP();
  setupMotors();
  setupServos();
  Serial.println("Setup has finished");

}

///////////////////////////////////////// ESP32 Loop /////////////////////////////////////////
void loop() {
  // Get the most approximate time from micros()  
  getDeltaTime();

  // Read the JSON message from the CCP
  readJson();

  // Spin the motor & update depending on variables
  spinMotor();
  updateMotors();
  updateDoors();

  // Delay for 100ms
  delay(100);
}

///////////////////////////////////////// Functions /////////////////////////////////////////

void getDeltaTime() {
  currentTime = micros();
  deltaTime = currentTime - oldTime;
  oldTime = currentTime;
}

void startWifi() {
  Serial.begin(115200);
  WiFi.begin(ssid, pass);
  Serial.println("Wifi has started");
  while(WiFi.status() != WL_CONNECTED) {
    delay(100);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());
}

void startUDP() {
  udp.begin(udpPort);
  Serial.println(udpPort);
  Serial.println("UDP has started");
  firstUDPmsg();
}

void firstUDPmsg() {
  const uint8_t buffer[50] = "hello world!";
  udp.beginPacket(udpAdd, udpPort);
  udp.write(buffer, 11);
  udp.endPacket();
  Serial.println("udp mesg sent");
}

void setupMotors() {
  pinMode(MotorPinA, OUTPUT);
  pinMode(MotorPinB, OUTPUT);
  pinMode(MotorPinP, OUTPUT);
}

void spinMotor() {
  digitalWrite(MotorPinA, HIGH);
  digitalWrite(MotorPinB, LOW);
}

void setupServos() {
  doorServoL.setPeriodHertz(50); // PWM frequency for SG90
  doorServoR.setPeriodHertz(50); 
  doorServoL.attach(Servo1_PWM1A, 500, 2400); // Minimum and maximum pulse width (in µs) 
  doorServoR.attach(Servo2_PWM1B, 500, 2400); // Minimum and maximum pulse width (in µs) 
}

void readJson() {
  int packetSize = udp.parsePacket();
  if(packetSize) {
    int size = udp.read(readBuffer, packetSize);
    //readBuffer[size] = '\0';
    Serial.println(readBuffer);
    Serial.println(curentSpeed);
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
  if(currentSpeed != targetSpeed) {
    double accDelta = (acc*deltaTime)/1000;
    if(abs(currentSpeed - targetSpeed) < accDelta) {
      currentSpeed = targetSpeed;
    } else if(currentSpeed > targetSpeed) {
      currentSpeed = currentSpeed - accDelta;
    } else {
      currentSpeed = currentSpeed + accDelta;
    }
  }
  if(targetSpeed = 10) {
    currentSpeed = 100;
  }
  digitalWrite(MotorPinP, currentSpeed);
}
