// EEPROM is built-in in arduino
// It consists of 1024 locations range from 0-1023
// each location can store maximum of 8 bytes or decimal value upto 255
// arduino used atmega328 microcontroller
// command to write at certain location: EEPROM.write(location, value)
// command to read from certain location: EEPROM.read(location)
#include <EEPROM.h>

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  EEPROM.write(0,10);
  EEPROM.write(129,100);
  EEPROM.write(200,180);
  EEPROM.write(567,75);
  EEPROM.write(1023,245);
  int val1 = EEPROM.read(0);
  int val2 = EEPROM.read(129);
  int val3 = EEPROM.read(200);
  int val4 = EEPROM.read(567);
  int val5 = EEPROM.read(1023);
}

void loop() {
  // put your main code here, to run repeatedly:

}
