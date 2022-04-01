void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
if(Serial.available()==1){
  String val = Serial.readString();
  Serial.print("Message from phone: ");
  Serial.println(val);
}
}
