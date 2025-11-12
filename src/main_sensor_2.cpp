#include <Arduino.h>
#include <OSCMessage.h>

// const char* ssid = "USNGHz";
// const char* password = "USNgallery";

// WiFiUDP Udp;
// IPAddress outIp(192, 168, 0, 67); // ← your PC IP
// const unsigned int outPort = 7777;

const int pulse2Pin = 36;  // VP
const int ledPin = 2;

void blinkLED() {
  digitalWrite(ledPin, HIGH);
  delay(10);
  digitalWrite(ledPin, LOW);
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
}


void loop() {
  int pulse2 = analogRead(pulse2Pin);

  OSCMessage msg2("/pulse2");
  msg2.add((float)pulse2);
  msg2.send(Serial);
  msg2.empty();
  blinkLED();
  
  delay(50);
}
