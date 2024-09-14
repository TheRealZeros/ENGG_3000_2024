// Last update: 2024-09-14
// BR09 EAC Code: Comms_4

// External Libraries
#include <Arduino.h>

// Internal Libraries
#include "EAC_Variables.h"
#include "EAC_Networking.h"
#include "EAC_ServoControl.h"
#include "EAC_MotorControl.h"

// PIN Definitions
#define CLK_DIR 17
#define EN_DIR 14
#define SER_DIR 12S
#define M1_PWM2A 23
#define Latch_DIR 19

///////////////////////////////////////// Intial ESP32 Setup /////////////////////////////////////////
void setup() {
  
  startWifi();
  startUDP();
  setupMotors();
  setupServos();
  Serial.println("EAC Setup has finished");

}

///////////////////////////////////////// ESP32 Loop /////////////////////////////////////////
void loop() {
  // Get the most approximate time from micros()  
  getDeltaTime();

  // Read the JSON message from the CCP
  readJson();
  checkMsg(ccpMessage);

  // Spin the motor & update depending on variables
  spinMotor();
  updateMotors();
  updateDoors(targetDoorStatus);

  // Delay for 100ms
  delay(100);
}
