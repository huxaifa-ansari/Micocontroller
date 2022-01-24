const int pushbutton = 4;
const int LED = 7;
int value = 0;

void setup() {
  // put your setup code here, to run once:
  pinMode(LED, OUTPUT);
  pinMode(pushbutton, INPUT_PULLUP);
}

void loop() {
  // put your main code here, to run repeatedly:
value = digitalRead(pushbutton);
if(value == LOW){
  delay(10);
  if(value == LOW){
    digitalWrite(LED, HIGH);
    delay(3000);
    digitalWrite(LED, LOW);
  }
}
}
