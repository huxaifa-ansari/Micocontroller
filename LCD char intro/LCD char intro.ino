#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
byte smiley[8] = {
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.clear();
  lcd.createChar(1, smiley);
  lcd.print("Custom!");
}

void loop() {
  for(int i=0; i<=15; i++){
    lcd.setCursor(i,0);
    lcd.write(1);
  }
}
