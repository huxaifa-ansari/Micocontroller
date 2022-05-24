//PWM pins can be used to get analog output on digital pins
//command: analogWrite(____, amount)
//0 duty cycle = analogWrite(0)
//25 duty cycle = analogWrite(64)
//50 duty cycle = analogWrite(127)
//75 duty cycle = analogWrite(191)
//100 duty cycle = analogWrite(255)

#define led 11 //PWM pin

void setup() {
  // put your setup code here, to run once:
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  for(int i=0; i<=255; i++){
  analogWrite(led, i);
  }
  for(int j=255; j<=0; j++){
  analogWrite(led, j);
  }
}
