#include <ESP8266WiFi.h>
#include <ArduinoOTA.h>

const char* ssid = "LAPTOP-7NG8FVHL-9713";
const char* password = "17171717";

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  //設定Baud rate
  Serial.println("") ;
  pinMode(LED_BUILTIN, OUTPUT); // 設置LED_BUILTIN引腳模式為輸出模式，可以通過它控制LED燈
  
  connectWifi();

  // 設置OTA主機名和密碼
  ArduinoOTA.setHostname("ESP8266");
  ArduinoOTA.setPassword("12345678");

  //開始使用OTA
  ArduinoOTA.begin();
  // 顯示OTA已經準備好
  Serial.println("OTA ready");
}

void loop() {
  // put your main code here, to run repeatedly:
  ArduinoOTA.handle();  //讓 Arduino 收到並處理OTA更新請求
  digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));
  delay(500);
}

void connectWifi(){
  //開始連接Wifi
  WiFi.begin(ssid, password);

  // 等待WiFi連接
  while (WiFi.status() != WL_CONNECTED){
    delay(100);
    Serial.print(".");
  }
  // 顯示連接成功的訊息和IP地址
  Serial.println("");
  Serial.println("WiFi Connected!");
  Serial.print("IP address:/t");
  Serial.println(WiFi.localIP());
}