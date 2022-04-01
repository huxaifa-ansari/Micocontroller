char str[15];
int i=0;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial.println("AT+CNMI=2,2,0,0,0");
  Serial.println("AT+CMGF=1");
}

void loop() {
  // put your main code here, to run repeatedly:
  while(Serial.available()){
    if(Serial.find("#")){
      delay(1000);
      while(Serial.available()){
        char istr = Serial.read();
        str[i++] = istr;
        if(istr == '*'){
          Serial.println((String)str);
          return;
        }
      }
    }
  }
}
