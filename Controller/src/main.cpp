#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>

void setup() {
  Serial.begin(115200);
}

void loop() {
  Serial.println("Hello World!");
  delay(1000);
}