// To write serial data received from LoRa.
#include <SoftwareSerial.h>

// Pins for receiving and transmitting LoRa data
#define RXD2 2
#define TXD2 3
SoftwareSerial mySerial(RXD2, TXD2);

//LED pins
#define openPin 11
#define closedPin 12

String content = "";

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);
  mySerial.setTimeout(1000);

  pinMode(openPin, OUTPUT);
  pinMode(closedPin, OUTPUT);
}

void loop() {
  if (Serial.available()){
    Serial.println("Writing");
    content = Serial.readString();
    content.trim();
    Serial.println();
    content = content + "\r\n";
    char* bufc = (char*) malloc(sizeof(char) * content.length() + 1);
    content.toCharArray(bufc, content.length() + 1);
    mySerial.write(bufc);
    free(bufc);
  }

  if (mySerial.available()) {
    String incomming = mySerial.readString();
    if (incomming.length() <= 10)
      Serial.println(incomming);
    else {
      String channel_ID = incomming.substring(incomming.indexOf('=') + 1, incomming.indexOf(','));
      //Serial.println("Channel ID : " + channel_ID);

      String str = incomming.substring(incomming.indexOf(',') + 1);

      String msgLength = str.substring(0, str.indexOf(','));
      //Serial.println("Message Length : " + msgLength);

      String str2 = str.substring(str.indexOf(',') + 1);

      String message = str2.substring(0, str2.indexOf(','));
      
      if (message=="CLOSED") {
        Serial.println("Garage closed.");
        digitalWrite(openPin, LOW);
        digitalWrite(closedPin, HIGH);
      }
      else if (message=="OPEN") {
        Serial.println("Garage open.");
        digitalWrite(openPin, HIGH);
        digitalWrite(closedPin, LOW);
      }
    }
  }
}