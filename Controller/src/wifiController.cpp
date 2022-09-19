#include "wifiController.hpp"

#include <Arduino.h>
#include <WiFi.h>
#include "Credentials.h"

namespace WiFiController{

void setup()
{
    Serial.print(F("Connecting to "));
    Serial.print(WIFI_SSID);

    WiFi.begin(WIFI_SSID, WIFI_PW);

    bool led_status = false;
    while (WiFi.status() != WL_CONNECTED)
    {
        delay(500);
        Serial.print(".");
        
        led_status = !led_status;
        digitalWrite(LED_BUILTIN, led_status);
    }
    digitalWrite(LED_BUILTIN, false);
    Serial.println("");

    Serial.println(F("WiFi connected"));
    Serial.print(F("IP address: "));
    Serial.println(WiFi.localIP());
}

void update()
{
}
}