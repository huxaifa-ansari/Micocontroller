#define BLYNK_PRINT Serial

#include <BlynkSimpleEsp32.h>

//Give crendentials of your WIFI and auth token here. (auth token comes from Blynk App)
char auth[] = "enter here";
char ssid[] = "enter here";
char pass[] = "enter here";

#define led 32

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(led, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  Blynk.run();
}
