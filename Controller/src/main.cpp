#include <Arduino.h>
#include <ArduinoJson.h>

#include "bme680.hpp"
#include "wifiController.hpp"
#include "mqttController.hpp"
#include "sr602.hpp"

#define LATITUDE 51.917255
#define LONGITUDE 4.484172

void mqtt_receive(const char *topic, byte *message, unsigned int length);

DynamicJsonDocument jsonDocument(1024);
JsonVariant documentVariant = jsonDocument.to<JsonVariant>();

long lastUpdate = 0;

void setup()
{
    // Communication setup
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    WiFiController::setup();

    MqttController::setup(documentVariant);
    MqttController::setCallback(mqtt_receive);

    // Sensor setup
    BME680::setup(documentVariant);
    SR602::setup(documentVariant);

    //Location set
    jsonDocument["latitude"] = LATITUDE;
    jsonDocument["longitude"] = LONGITUDE;
}

void loop()
{
    WiFiController::update();
    MqttController::update();
    SR602::update();

    long now = millis();
    if (now - lastUpdate > 5000)
    {
        lastUpdate = now;

        BME680::update();
        MqttController::publish();
    }
}

void mqtt_receive(const char *topic, byte *message, unsigned int length)
{
    Serial.print(F("Message received: "));
    Serial.println(topic);
    Serial.print(F("Message: "));

    String messageTemp;

    for (int i = 0; i < length; i++)
    {
        Serial.print((char)message[i]);
        messageTemp += (char)message[i];
    }
    Serial.println();

    if (String(topic) == "esp32/testColor/R")
    {
    }
}