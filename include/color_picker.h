#ifndef ESL_COLOR_PICKER_H
#define ESL_COLOR_PICKER_H

typedef enum
{
    MODE_IDLE,
    MODE_HUE,
    MODE_SATURATION,
    MODE_BRIGHTNESS
} input_mode_t;

void color_picker_init(void);
void color_picker_tick(void);

#endif