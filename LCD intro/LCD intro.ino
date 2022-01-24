#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11,  5, 4, 3, 2);
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  delay(2000);
  lcd.print("Hello Yashal");
}

void loop() {
  // put your main code here, to run repeatedly:
  lcd.setCursor(0,1);
  delay(2000);
  lcd.print("Hello Zummer");
  lcd.setCursor(0,1);
  delay(2000);
  lcd.print("Hello Huzefa");
  lcd.noDisplay();
  lcd.display();
}