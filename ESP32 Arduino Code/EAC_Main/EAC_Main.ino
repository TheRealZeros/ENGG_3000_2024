// Last update: 2024-10-8
// BR09 EAC Code: Comms_4

// External Libraries
#include <Arduino.h>

// Internal Libraries
#include "EAC_Variables.h"
#include "EAC_Networking.h"
#include "EAC_ServoControl.h"
#include "EAC_MotorControl.h"
#include "EAC_LEDScreen.h"
#include "EAC_SensorControl.h"
#include "EAC_LEDControl.h"

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

  // Initialise Sensors
  initialiseSensors();

  // Initialise LEDs
  initialiseLED();

}

///////////////////////////////////////// ESP32 Loop /////////////////////////////////////////
void loop() {
  // Get the most approximate time from micros()  
  getDeltaTime();

  // read Sensors
  readSensors();

  // Read the JSON message from the CCP
  readJson();

  // Sets the Variables depeading on the JSON that was read
  setJsonVariables();

  // checks the message sent by ccp
  checkMsgForSend(ccpMessage);

  // Update the motors speed
  updateCurrentSpeed();

  // print LCD Components
  printLCD();

  //update LEDs based on sensor readings (for testing)
  if(distance2 > 20) {
    setGLED(true);
    setRLED(false);
    setYLED(false);
    restartMotor();
  } else if(distance2 > 10) {
    setYLED(true);
    setRLED(false);
    setGLED(false);
    restartMotor();
  } else {
    setRLED(true);
    setGLED(false);
    setYLED(false);
    forceStop();
  }

  // Update the doors
  updateDoors(targetDoorStatus);

  // Delay for 100ms
}
