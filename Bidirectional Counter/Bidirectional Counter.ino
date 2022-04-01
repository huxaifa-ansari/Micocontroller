#include <LiquidCrystal.h>
LiquidCrystal lcd(13,12,10,9,8,7);

#define in 2
#define out 3
#define fan 4

int count = 0;

void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  lcd.print("Visitors Counter");
  delay(2000);
  pinMode(in, INPUT);
  pinMode(out, INPUT);
  pinMode(fan, OUTPUT);
  lcd.clear();
  lcd.print("Person in Room: ");
  lcd.setCursor(0,1);
  lcd.print(count);
}

void loop() {
  // put your main code here, to run repeatedly:
  int in_out = digitalRead(in);
  int out_out = digitalRead(out);
  if(in_out == HIGH){
    count++;
    lcd.clear();
    lcd.print("Person in Room: ");
    lcd.setCursor(0,1);
    lcd.print(count);
    delay(2000);
  }
  if(out_out == HIGH){
    count--;
    lcd.clear();
    lcd.print("Person in Room: ");
    lcd.setCursor(0,1);
    lcd.print(count);
    delay(2000);
  }
  if(count == 0){
    digitalWrite(fan, LOW);
    lcd.print("Nobody in Room");
    lcd.setCursor(0,1);
    lcd.print("Fan is OFF");
    delay(200);
  }
  else{
    digitalWrite(fan, HIGH);
  }
}
