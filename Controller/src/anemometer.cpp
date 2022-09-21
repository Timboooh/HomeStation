#include "anemometer.hpp"

#include <Arduino.h>

#define HALL_PIN 34

namespace Anemometer
{
    JsonVariant document;
    long last = 0;

    void ISR(){
        last = millis();
    }

    void setup(JsonVariant documentVariant){
        document = documentVariant;
        attachInterrupt(HALL_PIN, ISR, RISING);
    }

    void update(){
        Serial.println(last);
    }
} // namespace Anemometer
