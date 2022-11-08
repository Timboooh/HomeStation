#include "ws2812b.hpp"

#include <NeoPixelBus.h>

#define lightness = 0.02

namespace WS2812B
{
    const uint16_t PixelCount = 128;
    const uint8_t PixelPin = 4;

    NeoPixelBus<NeoGrbFeature, Neo800KbpsMethod> strip(PixelCount, PixelPin);

    void setup()
    {
        strip.Begin();
        strip.Show();
    }

    uint16_t animCounter = 0;
    double maxSteps = 200.0;
    void update()
    {
        HslColor color(animCounter / maxSteps, 1, 0.02);

        strip.SetPixelColor(0, color);
        strip.ShiftRight(1);
        strip.Show();

        animCounter++;
        if (animCounter > maxSteps)
            animCounter = 0;
        delay(10);
    }
} // namespace WS2812B