// ENGG3000 T2_M3 Control
// By: Neil Quisumbing
// Date Modified: 06-09-2024

// NOTE: Set upload speed to 115200 (Tools > Upload Speed > "115200")

// All other electronics
#include <Arduino.h>
#include <stdlib.h>
#include <ESP32Servo.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>
#include <Adafruit_NeoPixel.h>

// WiFi + UDP
#include <WiFi.h>
#include <WiFiClient.h>
#include <WiFiUdp.h>
#include <SPI.h>
#include <ArduinoJson.h>

#define PIN_WS2812B1 16
#define PIN_WS2812B2 17
#define NUM_PIXELS   16

#define Servo_Pin_1 19
#define Servo_Pin_2 18

#define TRAFFIC_LED_RED     32
#define TRAFFIC_LED_YELLOW  33
#define TRAFFIC_LED_GREEN   25

// Helper Functions
void readJson();
void encoderISR();

WiFiUDP udp;
JsonDocument json;

double speed = 0;
char* readBuffer;

char ssid[] = "ENGG2K3K";
char pass[] = "";
int udpPort = 3009;
char* udpAdd = "10.20.30.176";

// Motor encoder pins
const int encoderA = 15; // Encoder A output
const int encoderB = 5; // Encoder B output

// PID variables
float kp = 1.0, ki = 0.05, kd = 0.1; // PID constants (tune these for your system)
float targetPosition = 1000; // Desired encoder position
float currentPosition = 0;   // Current encoder position
float error, lastError = 0;
float integral = 0, derivative = 0;
float motorSpeed = 0;

// Variables for encoder position tracking
volatile long encoderPosition = 0;
volatile bool direction = true; // true for CW, false for CCW

void scrollText(int row, String message, int delayTime, int lcdColumns);

int lcdColumns = 16;
int lcdRows = 2;

// TIMERS
uint16_t myMillis = millis();
uint16_t myMicros = micros();

// 2 x LED Strips
Adafruit_NeoPixel ws2812b1(NUM_PIXELS, PIN_WS2812B1, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel ws2812b2(NUM_PIXELS, PIN_WS2812B2, NEO_GRB + NEO_KHZ800);

// 1 x LCD Display
LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

String messageStatic = "Central";
String messageToScroll = "Stopping at A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P";

Servo Servo_1;
Servo Servo_2;

// Pin assignments for Ultrasonic Sensor 1
const int trigPin1 = 13; // Trigger pin for Ultrasonic Sensor 1
const int echoPin1 = 12; // Echo pin for Ultrasonic Sensor 1

// Pin assignments for Ultrasonic Sensor 2
const int trigPin2 = 35; // Trigger pin for Ultrasonic Sensor 2
const int echoPin2 = 34; // Echo pin for Ultrasonic Sensor 2

// Variables to store duration and distance for each sensor
long duration1, duration2;
int distance1, distance2;

int motor1Pin1 = 27; 
int motor1Pin2 = 26; 
int enable1Pin = 14; 

void setup() {
  Serial.begin(115200);

  // Encoder pins as inputs
  pinMode(encoderA, INPUT);
  pinMode(encoderB, INPUT);

  // Attach interrupts for encoder
  attachInterrupt(digitalPinToInterrupt(encoderA), encoderISR, CHANGE);
  attachInterrupt(digitalPinToInterrupt(encoderB), encoderISR, CHANGE);

  // BELOW ARE ALL ELECTRONIC AND ELECTRICAL COMPONENTS
  ws2812b1.begin();
  ws2812b2.begin();

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.clear();

  pinMode(TRAFFIC_LED_RED, OUTPUT);
  pinMode(TRAFFIC_LED_YELLOW, OUTPUT);
  pinMode(TRAFFIC_LED_GREEN, OUTPUT);

  // Set the trigger and echo pins as output and input respectively
  pinMode(trigPin1, OUTPUT);
  pinMode(echoPin1, INPUT);
  
  pinMode(trigPin2, OUTPUT);
  pinMode(echoPin2, INPUT);

  // 2 x Servos (Positional)
  Servo_1.attach(Servo_Pin_1);
  Servo_2.attach(Servo_Pin_2);
}

void loop() {
  digitalWrite(TRAFFIC_LED_RED, HIGH);
  digitalWrite(TRAFFIC_LED_YELLOW, HIGH);
  digitalWrite(TRAFFIC_LED_GREEN, HIGH);

  // Turn on Strips
  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {         // for each pixel
    ws2812b1.setPixelColor(pixel, ws2812b1.Color(255, 0, 0));  // it only takes effect if pixels.show() is called
    ws2812b2.setPixelColor(pixel, ws2812b2.Color(0, 255, 0));  // it only takes effect if pixels.show() is called
  }

  delay(2000);

  // Change Colour
  ws2812b1.clear();
  ws2812b2.clear();

  for (int pixel = 0; pixel < NUM_PIXELS; pixel++) {
    ws2812b1.setPixelColor(pixel, ws2812b1.Color(255, 0, 255));
    ws2812b2.setPixelColor(pixel, ws2812b2.Color(0, 0, 255));
  }

  ws2812b1.show();
  ws2812b2.show();
  delay(2000);

  // Print LCD Components Message
  lcd.setCursor(5, 0);
  lcd.print(messageStatic);
  scrollText(1, messageToScroll, 250, lcdColumns);

  // Motor Full Speed (Clockwise)
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);  
  analogWrite(enable1Pin, 255);  // speed 0 to 255
  delay(5000);

  // Motor Full Speed (Anti-Clockwise)
  digitalWrite(motor1Pin1, LOW);
  digitalWrite(motor1Pin2, HIGH);  
  analogWrite(enable1Pin, 255);  // speed 0 to 255
  delay(5000);

  // Motor Acceleration (Clockwise)
  for(int i = 0; i <= 255; i++) {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);  
    analogWrite(enable1Pin, i);  // speed 0 to 255
    delay(100);
  }

  delay(1000);

  // Motor deceleration (Anti-Clockwise)
  for(int i = 255; i >= 0; i--) {
    digitalWrite(motor1Pin1, HIGH);
    digitalWrite(motor1Pin2, LOW);  
    analogWrite(enable1Pin, i);  // speed 0 to 255
    delay(100);
  }

  delay(1000);

	for (int pos = 0; pos <= 180; pos += 5) { // goes from 0 degrees to 180 degrees
		// in steps of 1 degree
		Servo_1.write(pos);    // tell servo to go to position in variable 'pos'
    Servo_2.write(pos);
		delay(100);             // waits 15ms for the servo to reach the position
	}
	for (int pos = 180; pos >= 0; pos -= 5) { // goes from 180 degrees to 0 degrees
		Servo_1.write(pos);    // tell servo to go to position in variable 'pos'
    Servo_2.write(pos);
		delay(100);             // waits 15ms for the servo to reach the position
	}
}

void scrollText(int row, String message, int delayTime, int lcdColumns) {
  for (int i=0; i < lcdColumns; i++) {
    message = " " + message;  
  } 
  message = message + " "; 
  for (int pos = 0; pos < message.length(); pos++) {
    lcd.setCursor(0, row);
    lcd.print(message.substring(pos, pos + lcdColumns));
    delay(delayTime);
  }
}

// Encoder interrupt service routine (ISR)
void encoderISR() {
  // Read the direction of rotation from encoder pins
  int encoderAState = digitalRead(encoderA);
  int encoderBState = digitalRead(encoderB);
  
  if (encoderAState == HIGH) {
    if (encoderBState == LOW) {
      encoderPosition++;  // Clockwise rotation
    } else {
      encoderPosition--;  // Counter-clockwise rotation
    }
  } else {
    if (encoderBState == HIGH) {
      encoderPosition++;  // Clockwise rotation
    } else {
      encoderPosition--;  // Counter-clockwise rotation
    }
  }
}

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