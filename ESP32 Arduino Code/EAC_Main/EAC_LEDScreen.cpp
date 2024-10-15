
#include "EAC_LEDScreen.h"

int lcdColumns = 16;
int lcdRows = 2;
int pos = 0;
int realTime = 0;
std::string scrollingString = "";

LiquidCrystal_I2C lcd(0x27, lcdColumns, lcdRows);

void initialiseLCD() {
  lcd.init();
  lcd.backlight();
  lcd.clear();
}

void printLCD() {
  lcd.setCursor(5, 0);
  lcd.print(LCDmessageStatic.c_str());
  scrollText(1, LCDmessageToScroll, 250, lcdColumns);
}

void scrollText(int row, std::string message, int delayTime, int lcdColumns) {
    
  for (int i=0; i < lcdColumns; i++) {
    message = " " + message;  
  } 
  message = message + " "; 
  Serial.printf("message: %s\n", message);
  realTime += deltaTime;
  Serial.printf("realTime: %d\n", realTime);
  if(realTime > delayTime*100) {
    realTime = 0;
    Serial.printf("message length: %d\n", message.length());
    Serial.printf("pos: %d\n", pos);
    if(pos >= message.length()) {
      pos = 0;
      
    }
    Serial.printf("pos after: %d\n", pos);
    lcd.setCursor(0, row);
    lcd.print(message.substr(pos, lcdColumns).c_str());
    pos++;
  }
}