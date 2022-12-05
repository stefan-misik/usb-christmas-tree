#include "rainbow_animation.h"

namespace
{

const uint16_t MAX_HUE = 0x02FF;

inline uint16_t incrementHue(uint16_t hue, int8_t value = 1)
{
    int16_t new_value = value + static_cast<int16_t>(hue);
    if (new_value < 0)
        return (MAX_HUE + 1) + new_value;
    else if (new_value > MAX_HUE)
        return new_value - (MAX_HUE + 1);
    else
        return new_value;
}

inline void toSaturatedHue(uint16_t hue, LedState * color)
{
    const uint8_t secondary_value = static_cast<uint8_t>(hue & 0xFF);
    const uint8_t primary_value = 0xFF - secondary_value;

    switch (static_cast<uint8_t>(hue >> 8))
    {
    case 0:
        color->red = primary_value;
        color->green = secondary_value;
        color->blue = 0;
        break;

    case 1:
        color->red = 0;
        color->green = primary_value;
        color->blue = secondary_value;
        break;

    case 2:
        color->red = secondary_value;
        color->green = 0;
        color->blue = primary_value;
        break;

    default:
        color->red = 0;
        color->green = 0;
        color->blue = 0;
        break;
    }
}

const uint8_t SPACE_INCREMENT = 8;
const uint8_t TIME_INCREMENT = 4;

}  // namespace


void RainbowAnimation::update(AbstractLedStrip * strip)
{
    ++step_;
    if (2 != step_)
        return;
    step_ = 0;

    uint16_t hue = hue_;
    LedState color;
    for (auto & led: *strip)
    {
        toSaturatedHue(hue, &color);
        hue = incrementHue(hue, SPACE_INCREMENT);
        led = color;
    }

    hue_ = incrementHue(hue_, -TIME_INCREMENT);
}

