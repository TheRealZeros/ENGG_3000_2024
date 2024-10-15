// Last update: 2024-09-16
// BR09 EAC Code: Comms_4

#ifndef EAC_LEDSCREEN_H
#define EAC_LEDSCREEN_H

// External Libraries
#include <Arduino.h>
#include <stdlib.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

// Internal Libraries
#include "EAC_Variables.h"

// LCD Variables
extern int lcdColumns;
extern int lcdRows;
extern int pos;
extern int realTime;
extern std::string scrollingString;

// Function Declarations
void initialiseLCD();
void printLCD();
void scrollText(int row, std::string message, int delayTime, int lcdColumns);

#endif // EAC_MOTORCONTROL_H