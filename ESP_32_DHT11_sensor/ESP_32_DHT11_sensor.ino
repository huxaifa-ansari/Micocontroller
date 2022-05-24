#include <DHT.h>
#include <LiquidCrystal.h>
// for lcd
//1,5,16 -> Ground
//2,5 ->3.3V
//

LiquidCrystal lcd(22, 23, 5, 18, 19, 21); // rs,en,d4,d5,d6,d7

#define DHTPin 2
#define DHTType DHT11

DHT dht(DHTPin, DHTType);

void setup() {
  // put your setup code here, to run once:
  dht.begin();
  lcd.begin(16, 2);
  lcd.clear();
  lcd.print("Temperature and ");
  lcd.setCursor(0,1);
  lcd.print("Humidity");
  delay(2000);

}

void loop() {
  // put your main code here, to run repeatedly:
  float tem =dht.readTemperature();
  float hum = dht.readHumidity();

  lcd.clear();
  lcd.print("Temperature");
  lcd.setCursor(0,1);
  lcd.print(tem);
  delay(1000);

  lcd.clear();
  lcd.print("Humidity");
  lcd.setCursor(0,1);
  lcd.print(hum);

  delay(2000);
}
