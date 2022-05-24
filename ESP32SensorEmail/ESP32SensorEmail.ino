#include "ESP32_MailClient.h"
#include <WiFi.h>

const char* ssid = "eduroam";
const char* password = "";

int touchValue;

#define emailSenderAccount = ""
#define emailSenderPassword = ""
#define emailRecieverAccount = ""
#define smtpServer = "smtp.gmail.com"
#define smtpServerPort = "465"
#define emailSubject = "ESP32 Testing"

SMTPData smtpData;

void setup() {
  // put your setup code here, to run once:
WiFi.begin(ssid, password);
while(WiFi.status() != WL_CONNECTED){
  Serial.print(".");
  delay(100);
}
/*
Serial.println("Wifi Connected!");
smtpData.setLogin(smtpServer, smtpServerPort, emailSenderAccount, emailSenderPassword);
smtpData.setSender("ESP32 Sender", emailSenderAccount);
smtpData.setPriority("High");
smtpData.setSubject(emailSubject);
smtpData.setMessage("Hello Word! This is ESP32 Testing", false);
*/
//smtpData.setMessage("<div style=\"color:#2fffff;\"><h1>Hello</h1><p>- Sent from ESP32</p></div>", true);
// false -> for sending text
// true -> for sending html 
/*
smtpData.addRecipient(emailRecieverAccount);
if(!MailClient.sendMail(smtpData)){
  Serial.print("Error Sending data" + MailClient.smtpErrorReason());
  smtp.empty();  
}
*/
}

void loop() {
  // put your main code here, to run repeatedly:
  touchValue = touchRead(4);
  smtpData.setLogin(smtpServer, smtpServerPort, emailSenderAccount, emailSenderPassword);
  smtpData.setSender("ESP32 Sender", emailSenderAccount);
  smtpData.setPriority("High");
  smtpData.setSubject(emailSubject);
  Serial.print("Touch Sensor Value: ", touchValue);
  if(touchValue >= 100){
    smtp.setMessage("Sensor Value is above 100", false);
    smtpData.addRecipient(emailRecieverAccount);
    if(!MailClient.sendMail(smtpData)){
      Serial.print("Error Sending data" + MailClient.smtpErrorReason());
      smtp.empty(); 
  delay(100000); 
}
  }
}
void CallBack(SendStatus message){
  Serial.println(message.info());
  if(messgae.success()){Serial.println("Successfuly Call Back");}
}