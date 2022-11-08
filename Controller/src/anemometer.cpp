#include "anemometer.hpp"

#include <Arduino.h>

#define ANEMO_PIN 32

namespace ANEMO
{
    JsonVariant document;

    void setup(JsonVariant documentVariant)
    {
        document = documentVariant;
        pinMode(ANEMO_PIN, INPUT);
    }

    void update()
    {
        double read = analogRead(ANEMO_PIN);

        double volt = (read * 3.3) / (4095);
        double speed = (volt - 0.26) / 1.6 * 32.4;
        
        document["Windspeed"] = speed;
    }
} // namespace Anemometer
