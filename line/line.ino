#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <TridentTD_LineNotify.h>

#define LINE_TOKEN "xzaohCq9aDAirUuoiRq4x8wJZuZYV2VBAsqr5Pf47PU"

// Setup the SSID(name of WIFI) and password of WIFI
const char* ssid = "LAPTOP-7NG8FVHL-9713";
const char* password = "17171717";

void connectWifi(){
  //開始連接Wifi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED){
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi Connected!");
  Serial.print("IP address:\t");
  Serial.println(WiFi.localIP());
}

void setup()
{
  Serial.begin(115200);  //Set up Baud rate
  WiFi.mode(WIFI_STA);
  
  // Connect with WIFI
  WiFi.begin(ssid, password);
  Serial.print("\n \r \n \rworking to connect");
  
  // Wait for connection, and dispaly on the Serial monitor window
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".") ;
  }
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println (WiFi.localIP()) ;
  Serial.println("Please enter the message you want sent to the chat room of LINE");
}

void loop(){
  // The message will be sent later,  Must Stored by a variable and the data type must be "String"
  String data;
  
  // Check if any message enter from Serial monitor window
  if(Serial.available()){
    // Receive the message enter from Serial monitor window
    data = Serial.readString();
  
    // Certify with LINE Token
    LINE.setToken(LINE_TOKEN) ;
    
    // Send the message by LINE notify
    LINE.notify("\n" + data);
    
    //Check the message is sent successfully
    Serial.println("Succeed to send the message");
  }
}
