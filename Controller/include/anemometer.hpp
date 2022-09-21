#ifndef ANEMOMETER_HPP
#define ANEMOMETER_HPP

#include <ArduinoJson.h>

namespace Anemometer
{
    void setup(JsonVariant documentVariant);
    void update();


} // namespace Anemometer


#endif