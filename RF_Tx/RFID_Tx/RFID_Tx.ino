#include <VirtualWire.h> //Including library

#define button 6 // Defining the pin location for button on arduino
char *msg; // defining variables
int val;
int value = 0;

void setup() {
  // put your setup code here, to run once:
  vw_set_tx_pin(12); // Initializing the transmitter part
  vw_setup(2000); // Initialzing the transmitter module
  pinMode(button, INPUT_PULLUP); // PULLUP -> input stays HIGH until its set LOW by external means
}

void loop() {
  // put your main code here, to run repeatedly:
  val = digitalRead(button); // Reading value
  if(val == LOW && value ==0){
    msg = 'a';
    vw_send((uint8_t)msg, strlen(msg)); // Sending the message // uint8_t -> 8 bit data to be send
    vw_wait_tx();//Waiting for all data to be send
    delay(500);
    value = 1;
  }
  if(val == LOW && value ==1){
    msg = 'b';
    vw_send((uint8_t)msg, strlen(msg));
    vw_wait_tx();
    delay(500);
    value = 0;
  }
}
