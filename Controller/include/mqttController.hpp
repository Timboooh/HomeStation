#ifndef MQTTCONTROLLER_HPP
#define MQTTCONTROLLER_HPP

#include <ArduinoJson.h>
#include <PubSubClient.h>

namespace MqttController
{
    void setup(JsonVariant documentVariant);
    void update();
    void publish();
    void setCallback(MQTT_CALLBACK_SIGNATURE);
}

#endif