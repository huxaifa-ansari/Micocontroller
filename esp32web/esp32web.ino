#include <WiFi.h> //Including Libraries
#include <WebServer.h>

const char* ssid = "MyNetwork"; //Including Credentials
const char* password = "myPassword";

//Last entry of local Ip should be such that no-one had taken
IPAddress local_ip(10,7,35,1); //Including IP Configurations which we get by typing "IPconfig" in cmd
IPAddress gateaway(10,7,32,1);
IPAddress subnet(255,255,248,0);

uint8_t LEDPin1=2; //Initializing LED pins along with Status
bool LED1Status = LOW; 
uint8_t LEDPin2 = 5;
bool LED2Status = LOW;

WebServer server(80); //Staring webserver with port-number "80" for html request


void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  pinMode(LEDPin1, OUTPUT); 
  pinMode(LEDPin2, OUTPUT);

  WiFi.softAP(ssid, password); //Setting credentials for software access point or Virtual Router 
  WiFi.softAPConfig(local_ip, gateaway, subnet); // Setting configurations for software access point or Virtual Router
  delay(100);

// 10,7,32,1/-Add handles here-

  server.on("/", handle_ONConnect); 
  server.on("/LED1on", handle_LED1on);
  server.on("/LED1off", handle_LED1off);
  server.on("/LED2on", handle_LED2on);
  server.on("/LED2off", handle_LED2off);
  server.onNotFound(handle_NotFound);

  server.begin();
  Serial.println("HTTP Server has started");
}

void loop() {
  // put your main code here, to run repeatedly:
  server.handleClient();
  if(LED1Status) {
    digitalWrite(LEDPin1 , HIGH);
  }
  else {
    digitalWrite(LEDPin1, LOW);
  }
  if(LED2Status){
    digitalWrite(LEDPin2, HIGH);
  }
  else{
    digitalWrite(LEDPin2, LOW);
  }
}

void handle_ONConnect(){
  LED1Status = LOW;
  LED2Status = LOW;
  Serial.println("GPIO 2 = OFF,  GPIO 5 = OFF");
  server.send(200, "text/html", SendHTML(LED1Status, LED2Status));
}

void handle_LED1on(){
  LED1Status = HIGH;
  Serial.println("GPIO 2 = ON");
  server.send(200, "text/html", SendHTML(true, LED2Status));
}

void handle_LED1off(){
  LED1Status = LOW;
  Serial.println("GPIO 2 = OFF");
  server.send(200, "text/html", SendHTML(false, LED2Status));
}

void handle_LED2on(){
  LED2Status = HIGH;
  Serial.println("GPIO 5 = ON");
  server.send(200, "text/html", SendHTML(LED1Status, true));
}

void handle_LED2off(){
  LED2Status = LOW;
  Serial.println("GPIO 5 = OFF");
  server.send(200, "text/html", SendHTML(LED1Status, false));
}

void handle_NotFound(){
  Serial.println("Not Found");
  server.send(404, "text/html", "Not Found");
}

String SendHTML(uint8_t led1stat,uint8_t led2stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>LED Control</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +=".button-on:active {background-color: #2980b9;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>ESP32 Web Server Text</h1>\n";
  ptr +="<h3>Using AP Mode</h3>\n";
  
   if(led1stat)
  {ptr +="<p>LED1 Status: ON</p><a class=\"button button-off\" href=\"/led1off\">OFF</a>\n";}
  else
  {ptr +="<p>LED1 Status: OFF</p><a class=\"button button-on\" href=\"/led1on\">ON</a>\n";}

  if(led2stat)
  {ptr +="<p>LED2 Status: ON</p><a class=\"button button-off\" href=\"/led2off\">OFF</a>\n";}
  else
  {ptr +="<p>LED2 Status: OFF</p><a class=\"button button-on\" href=\"/led2on\">ON</a>\n";}

  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}
