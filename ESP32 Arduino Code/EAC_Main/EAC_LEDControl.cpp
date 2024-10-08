// Last update: 2024-10-8
// BR09 EAC Code: Comms_4

#include "EAC_LEDControl.h"

void initialiseLED() {
  pinMode(pinR, OUTPUT);
  pinMode(pinY, OUTPUT);
  pinMode(pinG, OUTPUT);
}

void setRLED(bool input) {
  if(input) {
    digitalWrite(pinR, HIGH);
  } else {
    digitalWrite(pinR, LOW);
  }
}

void setYLED(bool input) {
  if(input) {
    digitalWrite(pinY, HIGH);
  } else {
    digitalWrite(pinY, LOW);
  }
}

void setGLED(bool input) {
  if(input) {
    digitalWrite(pinG, HIGH);
  } else {
    digitalWrite(pinG, LOW);
  }
}