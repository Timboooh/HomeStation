#include "bme680.hpp"

#include <Arduino.h>
#include <Adafruit_BME680.h>

namespace BME680
{
    Adafruit_BME680 bme;
    JsonVariant document;

    void setup(JsonVariant documentVariant)
    {
        document = documentVariant;

        if (!bme.begin())
            Serial.println(F("Error connecting BME680 Sensor"));

        // Set up oversampling and filter initialization
        bme.setTemperatureOversampling(BME680_OS_8X);
        bme.setHumidityOversampling(BME680_OS_2X);
        bme.setPressureOversampling(BME680_OS_4X);
        bme.setIIRFilterSize(BME680_FILTER_SIZE_3);
        bme.setGasHeater(320, 150); // 320*C for 150 ms
    }

    void update()
    {
        if (!bme.performReading())
        {
            Serial.println("Failed to read BME680 Sensor");
            return;
        }

        document["Temperature"] = bme.temperature;
        document["Pressure"] = bme.pressure / 100.0;
        document["Humidity"] = bme.humidity;
        document["Gas"] = bme.gas_resistance / 1000.0;
    }
}