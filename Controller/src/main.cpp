#include <Arduino.h>
#include <ArduinoJson.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_BME680.h>

#include "Credentials.h"

void wifi_setup();
void wifi_update();
void mqtt_setup();
void mqtt_update();
void bme680_setup();
void bme680_update();
void mqtt_receive(const char *topic, byte *message, unsigned int length);
void mqtt_publish();

DynamicJsonDocument jsonDocument(1024);
WiFiClient wifiClient;
PubSubClient mqttClient(wifiClient);

Adafruit_BME680 bme;

long lastUpdate = 0;

void wifi_setup()
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

void wifi_update()
{
}

void mqtt_setup()
{
    mqttClient.setServer(MQTT_SERVER, 1883);
    mqttClient.setCallback(mqtt_receive);
}

void mqtt_update()
{
    if (!mqttClient.connected())
    {
        // Reconnect
        // Loop until we're reconnected
        while (!mqttClient.connected())
        {
            Serial.print("Attempting MQTT connection...");
            // Attempt to connect
            if (mqttClient.connect("ESP32", MQTT_USER, MQTT_PW))
            {
                Serial.println("connected");
                // Subscribe
                mqttClient.subscribe(INCOMING_TOPIC);
            }
            else
            {
                Serial.print("failed, rc=");
                Serial.print(mqttClient.state());
                Serial.println(" try again in 5 seconds");
                // Wait 5 seconds before retrying
                bool led_status = false;
                for (size_t i = 0; i < 25; i++)
                {
                    delay(200);
                    
                    led_status = !led_status;
                    digitalWrite(LED_BUILTIN, led_status);
                }
                digitalWrite(LED_BUILTIN, false);
                
            }
        }
    }

    mqttClient.loop();
}

void bme680_setup()
{
    if (!bme.begin())
        Serial.println(F("Error connecting BME680 Sensor"));

    // Set up oversampling and filter initialization
    bme.setTemperatureOversampling(BME680_OS_8X);
    bme.setHumidityOversampling(BME680_OS_2X);
    bme.setPressureOversampling(BME680_OS_4X);
    bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
    bme.setGasHeater(320, 150); // 320*C for 150 ms
}

void bme680_update()
{
    if (!bme.performReading())
    {
        Serial.println("Failed to read BME680 Sensor");
        return;
    }

    jsonDocument["Temperature"] = bme.temperature;
    jsonDocument["Pressure"] = bme.pressure / 100.0;
    jsonDocument["Humidity"] = bme.humidity;
    jsonDocument["Gas"] = bme.gas_resistance / 1000.0;
}

void setup()
{
    // Communication setup
    Serial.begin(115200);
    pinMode(LED_BUILTIN, OUTPUT);
    wifi_setup();
    mqtt_setup();

    // Sensor setup
    bme680_setup();
}

void loop()
{
    wifi_update();
    mqtt_update();

    long now = millis();
    if (now - lastUpdate > 5000)
    {
        lastUpdate = now;

        bme680_update();

        mqtt_publish();
    }
}

void mqtt_publish()
{
    char messageBuffer[256];
    size_t length = serializeJsonPretty(jsonDocument, messageBuffer);

    mqttClient.publish(OUTGOING_TOPIC, messageBuffer, length);
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