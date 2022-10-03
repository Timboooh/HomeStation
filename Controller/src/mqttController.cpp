#include "mqttController.hpp"

#include <WiFi.h>

#include "Credentials.h"

namespace MqttController
{
    WiFiClient wifiClient;
    PubSubClient mqttClient(wifiClient);
    JsonVariant document;

    void setup(JsonVariant documentVariant)
    {
        document = documentVariant;
        mqttClient.setServer(MQTT_SERVER, 1883);
    }

    void update()
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
                    Serial.println("connected!");
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

    void publish()
    {
        char messageBuffer[256];
        size_t length = serializeJsonPretty(document, messageBuffer);

        Serial.println(messageBuffer);

        mqttClient.publish(OUTGOING_TOPIC, messageBuffer, length);
    }

    void setCallback(MQTT_CALLBACK_SIGNATURE)
    {
        mqttClient.setCallback(callback);
    }
}