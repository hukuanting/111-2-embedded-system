#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);

const int analogInPin = A0;
  const int count = 0;
  const float sum = 0.0;
  const char buffer[10];

 void setup(void) {
   Serial.begin(9600);
   u8g2.begin();
}

  void loop(void) {

  float sum;
  int count;
  int value = analogRead(analogInPin);

  count += 1;
  float voltage = (value * 5.0) / 1023.0;
  sum += voltage * voltage;
  float rms = sqrt(sum / count);

  dtostrf(rms, 6, 2, buffer);

  u8g2.clearBuffer();					// clear the internal memory
  u8g2.setFont(u8g2_font_logisoso28_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
  u8g2.drawStr(8,29,buffer);	// write something to the internal memory
  u8g2.sendBuffer();					// transfer internal memory to the display

  // Wait for a short time before sampling again
  delay(100);

   
}

