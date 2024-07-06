// To write serial data received from LoRa.
#include <SoftwareSerial.h>

// Pins for receiving and transmitting LoRa data

#define RXD2 10
#define TXD2 11
SoftwareSerial mySerial(RXD2, TXD2);

// The receiver LoRa is identified as "2"
#define TARGET_ID 2

//setup for ultrasonic sensor
#define echoPin 2
#define trigPin 3

bool garageClosed = false;

void setup()
{
  Serial.begin(9600);
  mySerial.begin(9600);

  pinMode(echoPin, INPUT);
  pinMode(trigPin, OUTPUT);
}

int timeSinceLastCheck = 0;
int lastCheckTime = 0;
void loop() {
  timeSinceLastCheck = millis() - lastCheckTime;
  if (timeSinceLastCheck>=5000) {
    float distance = getDistance();
    Serial.println("distance: " + String(distance));
    lastCheckTime = millis();

    if (garageClosed==false && distance<=50.0) {
      sendLoraData("CLOSED", TARGET_ID);
      garageClosed = true;
    }
    else if (garageClosed==true && distance>50.0) {
      sendLoraData("OPEN", TARGET_ID);
      garageClosed = false;
    }
  }

  if (Serial.available()){
    Serial.println("Writing");
    String content = Serial.readString();
    content.trim();
    Serial.println();
    content = content + "\r\n";
    char* bufc = (char*) malloc(sizeof(char) * content.length() + 1);
    content.toCharArray(bufc, content.length() + 1);
    mySerial.write(bufc);
    free(bufc);
  }

}

void sendLoraData(String data, int address) {
  String myString = "AT+SEND=" + String(address) + "," + String(data.length()) + "," + data + "\r\n";
  char* buf = (char*) malloc(sizeof(char) * myString.length() + 1);
  //Serial.println(myString);
  myString.toCharArray(buf, myString.length() + 1);

  mySerial.write(buf);
  free(buf);

  Serial.println("Sending: " + data + "...");
  delay(4000); // Time to send data
}

float getDistance() {
  digitalWrite(trigPin, LOW);  
	delayMicroseconds(2);  

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  float duration = pulseIn(echoPin, HIGH);
  return (duration*.0343)/2; 
}