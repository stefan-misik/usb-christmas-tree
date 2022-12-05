/**
 * @file
 */

#ifndef RAINBOW_ANIMATION_H_
#define RAINBOW_ANIMATION_H_

#include <stdint.h>

#include "led_strip.h"

class RainbowAnimation
{
public:
    void update(AbstractLedStrip * strip);

private:
    uint8_t step_ = 0;
    uint16_t hue_ = 0;
};

#endif  // RAINBOW_ANIMATION_H_
