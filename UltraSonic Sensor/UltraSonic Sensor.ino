#include <LiquidCrystal.h>

#define TrigPin 2
#define EchoPin 3
long duration;
int distanceCM, distanceINCH;
LiquidCrystal lcd (13, 12, 10, 9, 8, 7);
void setup() {
  // put your setup code here, to run once:
  lcd.begin(16,2);
  pinMode(TrigPin, OUTPUT);
  pinMode(EchoPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(TrigPin, HIGH);
  delay(2);
  digitalWrite(TrigPin, LOW);
  delay(10);
  digitalWrite(TrigPin, HIGH);
  delay(2);

  duration = pulseIn(EchoPin, HIGH);
  distanceCM = duration*0.034/2;
  distanceINCH = duration*0.0133/2;

  lcd.setCursor(0,0);
  lcd.print("Distance: ");
  lcd.print(distanceCM);
  lcd.print(" cm");
  delay(10);

  lcd.setCursor(0,1);
  lcd.print("Distance: ");
  lcd.print(distanceINCH);
  lcd.print(" inch");
  delay(10);
}
