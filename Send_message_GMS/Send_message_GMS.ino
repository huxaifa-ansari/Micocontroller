void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("AT+CMGF=1");
  delay(1000);
  Serial.println("AT+CMGS=\"+92XXXXXXXXXXX\"\r");
  delay(1000);
  Serial.println("Hello");
  delay(1000);
  Serial.println("Bye");
  delay(1000);
  Serial.println((char)26);
}

void loop() {
  // put your main code here, to run repeatedly:

}
