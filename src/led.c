#include "led.h"
#include "nrfx_pwm.h"

#define PWM_TOP 1000U

static const nrfx_pwm_t pwm = NRFX_PWM_INSTANCE(0);

static nrf_pwm_values_individual_t pwm_values = {
    .channel_0 = 0,
    .channel_1 = 0,
    .channel_2 = 0,
    .channel_3 = 0
};

static const nrf_pwm_sequence_t pwm_sequence = {
    .values.p_individual = &pwm_values,
    .length = 4,
    .repeats = 0,
    .end_delay = 0
};

static uint16_t rgb_to_pwm(uint8_t value)
{
    return (uint16_t)(
        (uint32_t)value * PWM_TOP / 255U
    );
}

static void pwm_start(void)
{
    nrfx_pwm_simple_playback(
        &pwm,
        &pwm_sequence,
        1,
        NRFX_PWM_FLAG_LOOP
    );
}

bool leds_init(void)
{
    nrfx_pwm_config_t config = {
        .output_pins = {
            LED_0 | NRFX_PWM_PIN_INVERTED,
            LED_1 | NRFX_PWM_PIN_INVERTED,
            LED_2 | NRFX_PWM_PIN_INVERTED,
            LED_3 | NRFX_PWM_PIN_INVERTED
        },
        .irq_priority = 6,
        .base_clock = NRF_PWM_CLK_1MHz,
        .count_mode = NRF_PWM_MODE_UP,
        .top_value = PWM_TOP,
        .load_mode = NRF_PWM_LOAD_INDIVIDUAL,
        .step_mode = NRF_PWM_STEP_AUTO
    };

    if (nrfx_pwm_init(&pwm, &config, NULL) != NRFX_SUCCESS)
    {
        return false;
    }

    pwm_start();

    return true;
}

void led_set_rgb(rgb_color_t color)
{
    uint16_t red = rgb_to_pwm(color.r);
    uint16_t green = rgb_to_pwm(color.g);
    uint16_t blue = rgb_to_pwm(color.b);

    if (pwm_values.channel_1 == red &&
        pwm_values.channel_2 == green &&
        pwm_values.channel_3 == blue)
    {
        return;
    }

    nrfx_pwm_stop(&pwm, true);

    pwm_values.channel_1 = red;
    pwm_values.channel_2 = green;
    pwm_values.channel_3 = blue;

    pwm_start();
}

void led_set_indicator(bool on)
{
    uint16_t value = on ? PWM_TOP : 0U;

    if (pwm_values.channel_0 == value)
    {
        return;
    }

    nrfx_pwm_stop(&pwm, true);

    pwm_values.channel_0 = value;

    pwm_start();
}