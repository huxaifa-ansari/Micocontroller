#include <WiFi.h>

#define WIFI_NETWORK "MyNetwork"
#define WIFI_PASSWORD "GoAway"
#define WIFI_TIMEOUT_MS 20000


void setup(){
  // put your setup code here, to run once:
  Serial.begin(9600);
  connectToWifi();
}

void loop() {
  // put your main code here, to run repeatedly:

}

void connectToWifi(){
  Serial.print("Connecting");
  WiFi.mode(WIFI_STA); //STA= Station Mode, AP=Acess Point Mode 
  WiFi.begin(WIFI_NETWORK, WIFI_PASSWORD); //Begin WIFI module

  unsigned long startAttempttime = millis();  
  
  while(WiFi.status() != WL_CONNECTED && millis()-startAttempttime < WIFI_TIMEOUT_MS){  //Until not connect
    Serial.print(".");
    delay(100);
  }

  if(WiFi.status() != WL_CONNECTED){ //If failed to connect
    Serial.print("FAILED!");
    //take action
  }
  else{
    Serial.print("Success");
    Serial.println(WiFi.localIP()); //Print the local IP
  }
}
