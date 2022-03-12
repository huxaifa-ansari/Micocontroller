const int UpButton = 12;
const int DownButton = 11;
const int LeftButton = 10;
const int RightButton = 9;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(digitalRead(UpButton) == HIGH){
    Serial.println("Up");
    delay(1000);
  } 
  if(digitalRead(DownButton) == HIGH){
    Serial.println("Down");
    delay(1000);
  } 
  if(digitalRead(LeftButton) == HIGH){
    Serial.println("left");
    delay(1000);
  } 
  if(digitalRead(RightButton) == HIGH){
    Serial.println("Right");
    delay(1000);
  } 
}
