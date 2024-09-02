// By: Neil Quisumbimg
#include <ESP32Servo.h>
//#include <AFMotor.h>
#include <WiFi.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

#define CLK_DIR 17
#define EN_DIR 14
#define SER_DIR 12
#define Servo1_PWM1A 13
#define Servo2_PWM1B 5
#define M1_PWM2A 23
#define Latch_DIR 19

//AF_DCMotor motor(1);

Servo myServo1;
Servo myServo2;

LiquidCrystal_I2C lcd(0x27, 16,2);  // set the LCD address to 0x27 for a 16 chars and 2 line display

// Network credentials
const char* ssid     = "YOURSSID";
const char* password = "YOURPW";
 
// Web server on port 80 (http)
WiFiServer server(80);
 
// Variable to store the HTTP request
String header;
 
// Decode HTTP GET value
String valueString = String(5);
int pos1 = 0;
int pos2 = 0;
 
// Current time
unsigned long currentTime = millis();
// Previous time
unsigned long previousTime = 0; 
// Define timeout time in milliseconds (example: 2000ms = 2s)
const long timeoutTime = 2000;

// PIN ALLOCATIONS
// SERVOS
//int servoPin1 = 13;
//int servoPin2 = 5; // w/ L293D
int servoPin1 = 2;
int servoPin2 = 4;

// INDIVIDUAL LEDS
int LED_RED = 33;
int LED_YELLOW = 32;
int LED_GREEN = 25;

// VARIABLES
int pos = 0;

void setup() {
  // NOTE: Set upload speed via Tools > 115200
  Serial.begin(115200);
  //Wire.begin();

  pinMode(LED_RED, OUTPUT);
  pinMode(LED_YELLOW, OUTPUT);
  pinMode(LED_GREEN, OUTPUT);

  //lcd.begin();
  //lcd.backlight();

  myServo1.attach(servoPin1, 500, 2400); 
  myServo2.attach(servoPin2, 500, 2400);

  //motor.setSpeed(200);
    //motor.run(RELEASE);
}

void loop() {
  digitalWrite(LED_RED, HIGH);
  digitalWrite(LED_YELLOW, HIGH);
  digitalWrite(LED_GREEN, HIGH);

  lcd.setCursor(0, 1);
  lcd.print(millis() / 1000);
  lcd.print("SECONDS");
  delay(100);

  for (pos = 0; pos <= 180; pos += 1) {
          myServo1.write(pos);
      myServo2.write(pos);
          delay(15);
    }

    for (pos = 180; pos >= 0; pos -= 1) {
        myServo1.write(pos);
    myServo2.write(pos);
        delay(15);
    }

  // uint8_t i;

    // // Turn on motor
    // motor.run(FORWARD);
    
    // // Accelerate from zero to maximum speed
    // for (i=0; i<255; i++) 
    // {
    //     motor.setSpeed(i);  
    //     delay(10);
    // }
    
    // // Decelerate from maximum speed to zero
    // for (i=255; i!=0; i--) 
    // {
    //     motor.setSpeed(i);  
    //     delay(10);
    // }

    // // Now change motor direction
    // motor.run(BACKWARD);
    
    // // Accelerate from zero to maximum speed
    // for (i=0; i<255; i++) 
    // {
    //     motor.setSpeed(i);  
    //     delay(10);
    // }

    // // Decelerate from maximum speed to zero
    // for (i=255; i!=0; i--) 
    // {
    //     motor.setSpeed(i);  
    //     delay(10);
    // }

    // // Now turn off motor
    // motor.run(RELEASE);
    // delay(1000);
}