
#include "EAC_LEDScreen.h"

int lcdColumns = 16;
int lcdRows = 2;

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
  for (int pos = 0; pos < message.length(); pos++) {
    lcd.setCursor(0, row);
    lcd.print(message.substr(pos, lcdColumns).c_str());
    delay(delayTime);
  }
}