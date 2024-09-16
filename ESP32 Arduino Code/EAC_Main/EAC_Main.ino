// Last update: 2024-09-14
// BR09 EAC Code: Comms_4

// External Libraries
#include <Arduino.h>

// Internal Libraries
#include "EAC_Variables.h"
#include "EAC_Networking.h"
#include "EAC_ServoControl.h"
#include "EAC_MotorControl.h"
#include "EAC_LEDScreen.h"

// PIN Definitions
#define CLK_DIR 17
#define EN_DIR 14
#define SER_DIR 12S
#define M1_PWM2A 23
#define Latch_DIR 19

///////////////////////////////////////// Intial ESP32 Setup /////////////////////////////////////////
void setup() {
  
  // Starts the WiFi Connection
  initialiseWifi();

  // Starts the UDP Connection
  initialiseUDP();

  // Initialises the motor
  initialiseMotors();

  // Initialises the door servos
  initialiseServos();

  // Initialises the LCD
  initialiseLCD();
  Serial.println("EAC Setup has finished");

}

///////////////////////////////////////// ESP32 Loop /////////////////////////////////////////
void loop() {
  // Get the most approximate time from micros()  
  getDeltaTime();

  // Read the JSON message from the CCP
  readJson();
  checkMsgForSend(ccpMessage);

  // Spin the motor & update depending on variables
  spinMotor();

  // Update the direction of the motor
  updateDirection();

  // Change the target speed of the motor
  changeTargetSpeed(motorStatus);

  // Update the motors speed
  updateCurrentSpeed();

  // print LCD Components
  printLCD();

  // Update the doors
  updateDoors(targetDoorStatus);

  // Delay for 100ms
  delay(100);
}
