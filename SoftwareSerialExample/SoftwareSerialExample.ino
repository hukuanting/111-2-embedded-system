#include <SoftwareSerial.h>

SoftwareSerial mySerial(10, 11); // RX, TX

void setup() {
  // Open serial communications and wait for port to open:
  Serial.begin(57600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for native USB port only
  }

  Serial.println("Goodnight moon!");

  // set the data rate for the SoftwareSerial port
  mySerial.begin(57600);
  mySerial.println("Hello, world?");
}

void loop() { // run over and over
  int chr;
  if (mySerial.available()) {                                             //|chr==66|chr==67|chr==68|chr==82)
    Serial.write(mySerial.read());
  }
  if (Serial.available()) {
    chr = Serial.read();
        mySerial.println(chr[i], BIN);
    }
    mySerial.write(Serial.read());
    
  }
}
