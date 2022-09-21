#include "sr602.hpp"

#include <Arduino.h>

//TODO Use interrupts
namespace SR602
{
    long lastDetected = 0;
    bool isOn = false;

    std::function<void()> upCallback;
    std::function<void()> downCallback;

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

    void setUpCallback(std::function<void()> callback)
    {
        upCallback = callback;
    }

    void setDownCallback(std::function<void()> callback)
    {
        downCallback = callback;
    }
} // namespace SR602
