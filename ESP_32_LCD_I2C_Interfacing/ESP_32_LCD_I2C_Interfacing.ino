#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

void setup() {
  // put your setup code here, to run once:
  lcd.init();
  lcd.backlight();
  lcd.print("Working...");
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.clear();
  lcd.print("Seconds");
  lcd.setCursor(0,1);
  lcd.print(millis()/1000);
}
