#ifndef BME680_HPP
#define BME680_HPP

#include <ArduinoJson.h>

namespace BME680
{
    void setup(JsonVariant documentVariant);
    void update();
}

#endif