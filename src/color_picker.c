#include <stdbool.h>
#include <stdint.h>

#include "color_picker.h"
#include "button.h"
#include "led.h"
#include "hsv.h"

#define HUE_UPDATE_TICKS 5U
#define HOLD_TICKS 30U

#define HUE_BLINK_TICKS 50U
#define SAT_BLINK_TICKS 10U

static input_mode_t current_mode = MODE_IDLE;

static float hue = 25.2f;
static float saturation = 100.0f;
static float brightness = 100.0f;

static uint8_t blink_counter = 0;
static uint8_t hold_counter = 0;
static uint8_t update_counter = 0;

static bool indicator_on = false;
static bool saturation_increasing = false;
static bool brightness_increasing = false;

static void update_color(void)
{
    rgb_color_t color = hsv_to_rgb(
        hue, saturation, brightness
    );

    led_set_rgb(color);
}

static void change_mode(void)
{
    current_mode = (input_mode_t)(
        (current_mode + 1) % 4
    );

    blink_counter = 0;
    hold_counter = 0;
    update_counter = 0;
    indicator_on = false;
}

static void indicator_tick(void)
{
    uint8_t toggle_ticks = 0;

    switch (current_mode)
    {
        case MODE_IDLE:
            indicator_on = false;
            break;

        case MODE_HUE:
            toggle_ticks = HUE_BLINK_TICKS;
            break;

        case MODE_SATURATION:
            toggle_ticks = SAT_BLINK_TICKS;
            break;

        case MODE_BRIGHTNESS:
            indicator_on = true;
            break;
    }

    if (toggle_ticks > 0)
    {
        if (++blink_counter >= toggle_ticks)
        {
            blink_counter = 0;
            indicator_on = !indicator_on;
        }
    }

    led_set_indicator(indicator_on);
}

static void adjust_percentage(float *value,
                              bool *increasing)
{
    if (*increasing)
    {
        *value += 1.0f;

        if (*value >= 100.0f)
        {
            *value = 100.0f;
            *increasing = false;
        }
    }
    else
    {
        *value -= 1.0f;

        if (*value <= 0.0f)
        {
            *value = 0.0f;
            *increasing = true;
        }
    }
}

static void adjust_color(void)
{
    switch (current_mode)
    {
        case MODE_HUE:
            hue += 2.0f;

            if (hue >= 360.0f)
            {
                hue -= 360.0f;
            }
            break;

        case MODE_SATURATION:
            adjust_percentage(
                &saturation,
                &saturation_increasing
            );
            break;

        case MODE_BRIGHTNESS:
            adjust_percentage(
                &brightness,
                &brightness_increasing
            );
            break;

        case MODE_IDLE:
            return;
    }

    update_color();
}

static void adjustment_tick(void)
{
    if (!button_is_pressed() ||
        current_mode == MODE_IDLE)
    {
        hold_counter = 0;
        update_counter = 0;
        return;
    }

    if (hold_counter < HOLD_TICKS)
    {
        ++hold_counter;
        return;
    }

    if (++update_counter >= HUE_UPDATE_TICKS)
    {
        update_counter = 0;
        adjust_color();
    }
}

void color_picker_init(void)
{
    update_color();
    led_set_indicator(false);
}

void color_picker_tick(void)
{
    if (button_double_click_tick())
    {
        change_mode();
    }

    indicator_tick();
    adjustment_tick();
}