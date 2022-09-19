#include "sr602.hpp"

#include <Arduino.h>

namespace SR602
{
    long lastDetected = 0;
    bool isOn = false;

    void setup(JsonVariant documentVariant)
    {
        pinMode(SR602_DATAPIN, INPUT);
    }
    void update()
    {
        if (digitalRead(SR602_DATAPIN))
            lastDetected = millis();

        long diff = millis() - lastDetected;
        isOn = diff < SR602_TIMEOUT;
    }
} // namespace SR602
