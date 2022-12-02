#include "ws2812b.hpp"

#include <NeoPixelBus.h>

namespace WS2812B
{
    const uint16_t PixelCount = 128;
    const uint8_t PixelPin = 4;
    const float lightness = 0.01f;
    bool rainbow = false;

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
        if (rainbow)
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
    }

    void setColor(LedColor color)
    {
        rainbow = false;

        HslColor ledColor;
        switch (color)
        {
        case Red:
            ledColor = HslColor(0 / 6.0f, 1, lightness);
            break;
        case Yellow:
            ledColor = HslColor(1 / 6.0f, 1, lightness);
            break;
        case Green:
            ledColor = HslColor(2 / 6.0f, 1, lightness);
            break;
        case LightBlue:
            ledColor = HslColor(3 / 6.0f, 1, lightness);
            break;
        case Blue:
            ledColor = HslColor(4 / 6.0f, 1, lightness);
            break;
        case Pink:
            ledColor = HslColor(5 / 6.0f, 1, lightness);
            break;
        case Rainbow:
            rainbow = true;
            break;
        case Black:
        default:
            ledColor = HslColor(0, 0, 0);
            break;
        }

        for (size_t i = 0; i < PixelCount; i++)
        {
            strip.SetPixelColor(i, ledColor);
        }

        strip.Show();
    }

    void setColor(const char *color)
    {
        if (strcmp(color, "Red") == 0)
            setColor(Red);
        else if (strcmp(color, "Pink") == 0)
            setColor(Pink);
        else if (strcmp(color, "LightBlue") == 0)
            setColor(LightBlue);
        else if (strcmp(color, "Green") == 0)
            setColor(Green);
        else if (strcmp(color, "Yellow") == 0)
            setColor(Yellow);
        else if (strcmp(color, "Blue") == 0)
            setColor(Blue);
        else if (strcmp(color, "Rainbow") == 0)
            setColor(Rainbow);
        else if (strcmp(color, "Black") == 0)
            setColor(Black);
        else
            setColor(Black);

    }
} // namespace WS2812B