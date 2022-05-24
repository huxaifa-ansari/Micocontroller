#include <WiFi.h>
#include <HTTPClient.h>

HTTPClient http;

const char* ssid = "eduroam";
const char* password = "Your Password";
const char* serverName = "https://seasonable-projecti.000webhostapp.com/php_data.php";

String ApiKeyValue = "E8sjWJ";
String sensorName = "Touch";
String sensorLocation = "Hostel Room";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(115200);
  WiFi.begin(ssid, password);
  Serial.println("Connecting to IP Address...");
  while(WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println(".");
  }
  Serial.print("Connected to following IP Address: ");
  Serial.print(WiFi.localIP());
}

void loop() {
  // put your main code here, to run repeatedly:
  if(WiFi.status() == WL_CONNECTED){
    http.begin(serverName);
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");
    String httpRequestData = "apiKey= ", ApiKeyValue, "&SensorName= ", sensorName, "&Location= ", sensorLocation, "&value1= ", touchRead(2), 
                              "&value2= ", touchRead(4), "&value3= ", touchRead(15);
    Serial.print("httpRequestData: ");
    Serial.print(httpRequestData);

    int httpResponseCode = http.POST(httpRequestData);
    if(httpResponseCode > 0) {
      Serial.print("http Response Code: ");
      Serial.println(httpResponseCode);
    }
    else {
     Serial.print("Error Code: ");
     Serial.println(httpResponseCode); 
    }
  }
  else{Serial.println("WIFI Disconnected");}
  delay(30000);
}
