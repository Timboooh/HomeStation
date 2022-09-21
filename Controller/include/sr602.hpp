#ifndef SR602_HPP
#define SR602_HPP

#define SR602_DATAPIN 23
#define SR602_TIMEOUT 5000

#include <ArduinoJson.h>

namespace SR602
{
    void setup(JsonVariant documentVariant);
    void update();
    void setUpCallback(std::function<void()> callback);
    void setDownCallback(std::function<void()> callback);
} // namespace SR602

#endif
