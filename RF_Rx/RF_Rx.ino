#include <VirtualWire.h>

#define led 7

void setup() {
  // put your setup code here, to run once:
  vw_set_rx_pin(12);
  vw_setup(2000);
  pinMode(led, OUTPUT);
  vw_rx_start();
}

void loop() {
  // put your main code here, to run repeatedly:
  uint8_t val1[VW_MAX_MESSAGE_LEN];
  uint8_t val2 = VW_MAX_MESSAGE_LEN;
  if(vw_get_message(val1, &val2)){
    if(val1[0] =='a'){
      digitalWrite(led, HIGH);
    }
    else if(val1[0] == 'b'){
      digitalWrite(led, LOW);
    }
  }
}
