#ifndef ESL_HSV_H
#define ESL_HSV_H

#include <stdint.h>

typedef struct
{
    uint8_t r;
    uint8_t g;
    uint8_t b;
} rgb_color_t;

rgb_color_t hsv_to_rgb(float h, float s, float v);

#endif