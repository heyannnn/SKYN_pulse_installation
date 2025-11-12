#include <Arduino.h>
#include <WiFi.h>
#include <WiFiUdp.h>
#include <OSCMessage.h>

const char* ssid = "USNGHz";
const char* password = "USNgallery";

WiFiUDP Udp;
IPAddress outIp(192, 168, 0, 67); // ← your PC IP
const unsigned int outPort = 6666;

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

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(300);
    Serial.print(".");
  }

  Serial.println("\nWiFi connected. IP: ");
  Serial.println(WiFi.localIP());

  Udp.begin(8889); // use different local port
}

void loop() {
  int pulse1 = analogRead(pulse2Pin);

  OSCMessage msg2("/pulse1");
  msg2.add((float)pulse1);
  Udp.beginPacket(outIp, outPort);
  msg2.send(Udp); Udp.endPacket(); msg2.empty();
  blinkLED();

  delay(50);
}
