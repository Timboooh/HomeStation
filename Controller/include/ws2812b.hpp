#ifndef WS2812B_H
#define WS2812B_H

namespace WS2812B
{
    enum LedColor
    {
        Red,
        Pink,
        LightBlue,
        Green,
        Yellow,
        Blue,
        Rainbow,
        Black
    };

    void setup();
    void update();
    void setColor(LedColor color);
    void setColor(const char *color);

} // namespace WS2812B

#endif
