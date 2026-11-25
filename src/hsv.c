#include "hsv.h"
#include <math.h>

rgb_color_t hsv_to_rgb(float h, float s, float v)
{
    rgb_color_t rgb = {0, 0, 0};

    float saturation = s / 100.0f;
    float value = v / 100.0f;

    float c = value * saturation;
    float m = value - c;

    float x = c * (1.0f -
        fabsf(fmodf(h / 60.0f, 2.0f) - 1.0f));

    float r1 = 0.0f;
    float g1 = 0.0f;
    float b1 = 0.0f;

    if (h < 60.0f)
    {
        r1 = c;
        g1 = x;
    }
    else if (h < 120.0f)
    {
        r1 = x;
        g1 = c;
    }
    else if (h < 180.0f)
    {
        g1 = c;
        b1 = x;
    }
    else if (h < 240.0f)
    {
        g1 = x;
        b1 = c;
    }
    else if (h < 300.0f)
    {
        r1 = x;
        b1 = c;
    }
    else if (h < 360.0f)
    {
        r1 = c;
        b1 = x;
    }

    rgb.r = (uint8_t)((r1 + m) * 255.0f);
    rgb.g = (uint8_t)((g1 + m) * 255.0f);
    rgb.b = (uint8_t)((b1 + m) * 255.0f);

    return rgb;
}