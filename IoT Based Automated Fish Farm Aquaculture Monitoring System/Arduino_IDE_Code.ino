#include <OneWire.h>            // Library for DS18B20 temperature sensor
#include <DallasTemperature.h>  // Library for DS18B20 temperature sensor
#include <WiFi.h>
#include <PubSubClient.h>
#include <String.h>
#include <EEPROM.h>            // Library for reading/writing to EEPROM

// Define the pins for the sensors
#define PH_SENSOR_PIN 39 // Analog input pin for pH sensor
#define TDS_SENSOR_PIN 35        // Analog pin for SEN0244 TDS sensor
#define TEMPERATURE_SENSOR_PIN 4 // Digital pin for DS18B20 temperature sensor
#define GAS_SENSOR_PIN 27        // Analog pin for MQ137 gas sensor
#define TURBIDITY_SENSOR_PIN 36  // Analog pin for SEN0189 turbidity sensor


unsigned long int avgValue;  //Store the average value of the sensor feedback
int buf[10],temp;


//Other things
const char *ssid = "MYDESKTOP"; // Enter your WiFi name
const char *password = "kemonojihen";  // Enter WiFi password
const char *mqtt_server = "broker.hivemq.com";
const char *topic = "esp32/test/1222221";
const char *topictds = "esp32/test/1222221/tds";
const char *topicph = "esp32/test/1222221/ph";
const char *topictur = "esp32/test/1222221/tur";
const char *topicamm = "esp32/test/1222221/amm";
const char *topictemp = "esp32/test/1222221/temp";
const char *mqtt_username = "FishFarmingFYP";
const char *mqtt_password = "FishFarmingFYP";
const int mqtt_port = 1883;

WiFiClient espClient;
PubSubClient client(espClient);
String buff, buff1, buff2, buff3, buff4, buff5;
String TDS;
String TURBIDITY;
String PH;
String AMMONIA;
String TEMP;


// Calibration constants for pH sensor (adjust these according to your sensor)
float calibrationOffset = 0.0;
float calibrationFactor = 1.0;

// Calibration constant for TDS sensor (adjust this according to your sensor)
float tdsCalibrationValue = 1.0;
const float voltageConversionFactor = 5.0 / 1024.0; // Conversion factor for converting analog reading to voltage
const float tdsFactor = 0.5; // Conversion factor for converting voltage to TDS value


const float RL = 46.7;         // Load resistance (RL) value
const float m = -0.243;        // Slope of the calibration curve
const float b = 0.323;         // Y-intercept of the calibration curve
const float Ro = -9.73;        // Sensor resistance in clean air

// Setup the OneWire and DallasTemperature libraries for DS18B20 sensor
OneWire oneWire(TEMPERATURE_SENSOR_PIN);
DallasTemperature sensors(&oneWire);


void setup() {
  Serial.begin(9600);
  WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
     Serial.println("Connecting to WiFi..");
 }
 Serial.println("Connected to the WiFi network");
 //connecting to a mqtt broker
 client.setServer(mqtt_server, mqtt_port);
 client.setCallback(callback);
 while (!client.connected()) {
     String client_id = "esp32-client-";
     client_id += String(WiFi.macAddress());
     Serial.printf("The client %s connects to the public mqtt broker\n", client_id.c_str());
     if (client.connect(client_id.c_str(), mqtt_username, mqtt_password)) {
         Serial.println("Public emqx mqtt broker connected");
     } else {
         Serial.print("failed with state ");
         Serial.print(client.state());
         delay(2000);
     }
 }
 EEPROM.get(0, calibrationOffset);
 EEPROM.get(sizeof(float), calibrationFactor);
}


void loop() {
  // Read ph value
  //float pHValue = readpH();
  int rawValue = analogRead(PH_SENSOR_PIN);

  // Convert the raw value to pH
  float voltage = rawValue * (5 / 1024.0);
  Serial.print("PH Voltage: ");
  Serial.println(voltage);
  float pHValue = voltage-11;
  // if(pHValue > 7.8){
  //   int temp = random(56, 60);
  //   pHValue = temp/100;
  // }
  Serial.print("PH: ");
  Serial.println(pHValue);
  //Read TDS Value
  //float tds = readTDS();
  int analogValue = analogRead(TDS_SENSOR_PIN);
  float voltage2 = analogValue ;
  float tdsValue = (voltage2/100) + 400;

  // if(tdsValue < 421){
  //   tdsValue = tdsValue - 300;
  // }
  
  Serial.print("TDS value: ");
  Serial.println(tdsValue);
  // Read the temperature value
  sensors.requestTemperatures();
  // Read the temperature value in Celsius
  float temperatureVal = sensors.getTempCByIndex(0);

  // Read the gas value
  int sensorValue = analogRead(GAS_SENSOR_PIN);
  float Rs = (1023.0 / sensorValue) - 1;
  float ammoniaConcentration = (RL * pow((Rs/Ro), m) - b) / 1000.0; 

  // Read the turbidity value
  int rawValue2 = analogRead(TURBIDITY_SENSOR_PIN);
  Serial.print("Turbidity Voltage: ");
  Serial.println(rawValue2);
  float turbidity = rawValue2/10;
  Serial.print("Turbidity: ");
  Serial.println(turbidity);


  TDS = String(tdsValue);
  PH = String(pHValue);
  TURBIDITY = String(turbidity);
  AMMONIA = String(ammoniaConcentration);
  TEMP = String(temperatureVal);
  
  buff = TDS + String(" ") + PH + String(" ") + TURBIDITY + String(" ") + AMMONIA + String(" ") + TEMP;
  buff1 = TDS + String(" ");
  buff2 = PH + String(" ");
  buff3 = TURBIDITY + String(" ");
  buff4 = AMMONIA + String(" ");
  buff5 = TEMP + String(" ");
  Serial.println(buff);
  client.publish(topic,buff.c_str());
  client.publish(topictds,buff1.c_str());
  client.publish(topicph,buff2.c_str());
  client.publish(topictur,buff3.c_str());
  client.publish(topicamm,buff4.c_str());
  client.publish(topictemp,buff5.c_str());
  

}

// float readpH() {
//   int sensorValue = analogRead(PH_SENSOR_PIN);

//   // Convert sensor value to pH
//   float voltage = sensorValue * (5.0 / 1023.0);  // Convert sensor value to voltage (assuming 5V reference)
//   float pHValue = voltage;  // Convert voltage to pH (assuming pH 7 at 0V)

//   return pHValue;
// }

// float readTDS() {
//   int sensorValue = analogRead(TDS_SENSOR_PIN);

//   // Convert sensor value to TDS
//   float tdsValue = (sensorValue / calibrationFactor);

//   return tdsValue;
// }

// float readTemperature() {
//   // Request the temperature from the DS18B20 sensor
  

//   return temperature;
// }

// float readGas() {
//   // Read the raw analog value from the gas sensor
//   int sensorValue = analogRead(GAS_SENSOR_PIN);
//   float Rs = (1023.0 / sensorValue) - 1;
//   float ammoniaConcentration = (RL * pow((Rs/Ro), m) - b) / 1000.0; 

//   return ammoniaConcentration;
// }

// float readTurbidity() {
//   // Read the raw analog value from the turbidity sensor
//   int rawValue = analogRead(TURBIDITY_SENSOR_PIN);

//   // Convert the raw value to turbidity
//   float turbidity = rawValue/100;

//   return turbidity;
// }


void callback(char *topic, byte *payload, unsigned int length) {
 Serial.print("Message arrived in topic: ");
 Serial.println(topic);
 Serial.print("Message:");
 for (int i = 0; i < length; i++) {
     Serial.print((char) payload[i]);
 }
 Serial.println();
 Serial.println("-----------------------");
}