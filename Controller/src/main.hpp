#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include "Credentials.h"

void setup_wifi();
void setup_mqtt();
void callback_mqtt(const char* topic, byte* message, unsigned int length);