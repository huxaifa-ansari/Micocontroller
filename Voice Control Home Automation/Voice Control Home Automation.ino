// Coding part is not as tough as Schematic part

#define fan 2
#define bulb 3

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(fan, OUTPUT);
  pinMode(bulb, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Serial.available()){
    String voice = Serial.readString();
    if(voice == "fan on"){
      digitalWrite(fan, HIGH);
    }
    if(voice == "fan off"){
      digitalWrite(fan, LOW);
    }
    if(voice == "bulb on"){
      digitalWrite(bulb, HIGH);
    }
    if(voice == "bulb off"){
      digitalWrite(bulb, LOW);
    }
    if(voice == "all on"){
      digitalWrite(fan, HIGH);
      digitalWrite(bulb, HIGH);
    }
    if(voice == "fan on"){
      digitalWrite(fan, LOW);
      digitalWrite(bulb, LOW);
    }
  }
}
