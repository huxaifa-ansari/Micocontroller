#include <VirtualWire.h>

#define m1 2
#define m2 3
#define m3 4
#define m4 5

void setup() {
  // put your setup code here, to run once:
  vw_set_rx_pin(12);
  vw_setup(2000);
  pinMode(m1, OUTPUT);
  pinMode(m2, OUTPUT);
  pinMode(m3, OUTPUT);
  pinMode(m4, OUTPUT);
  vw_rx_start();
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t val1[VW_MAX_MESSAGE_LEN];
  uint8_t val2 = VW_MAX_MESSAGE_LEN;
  if(vw_get_message(val1, &val2)){
    if(val1[0] =='f'){
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, LOW);
    }
    else if(val1[0] =='b'){
      digitalWrite(m1, LOW);
      digitalWrite(m2, HIGH);
      digitalWrite(m3, LOW);
      digitalWrite(m4, HIGH);
    }
    else if(val1[0] =='l'){
      digitalWrite(m1, HIGH);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, LOW);
    }
    else if(val1[0] =='r'){
      digitalWrite(m1, LOW);
      digitalWrite(m2, LOW);
      digitalWrite(m3, HIGH);
      digitalWrite(m4, LOW);
    }
    else if(val1[0] =='s'){
      digitalWrite(m1, LOW);
      digitalWrite(m2, LOW);
      digitalWrite(m3, LOW);
      digitalWrite(m4, LOW);
    }
  }
}
