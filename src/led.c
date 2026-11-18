#include "led.h"
#include "nrfx_pwm.h"

#define PWM_TOP 1000U
#define FADE_STEPS 201U
#define PAUSE_STEPS 80U
#define TOTAL_FRAMES (16U * FADE_STEPS + 4U * PAUSE_STEPS)

/* PWM EasyDMA reads RAM directly. */
static nrf_pwm_values_individual_t frames[TOTAL_FRAMES];
static const nrfx_pwm_t pwm = NRFX_PWM_INSTANCE(0);
static const nrf_pwm_sequence_t pwm_sequence = {
    .values.p_individual = frames,
    .length = TOTAL_FRAMES * 4U,
    .repeats = 0,
    .end_delay = 0
};

static void append_fade(uint32_t *position, uint32_t channel)
{
    for (uint32_t step = 0; step < FADE_STEPS; ++step)
    {
        uint16_t brightness = (step <= 100U)
                                  ? (uint16_t)(step * 10U)
                                  : (uint16_t)((200U - step) * 10U);
        nrf_pwm_values_individual_t *value = &frames[(*position)++];
        switch (channel)
        {
            case 0: value->channel_0 = brightness; break;
            case 1: value->channel_1 = brightness; break;
            case 2: value->channel_2 = brightness; break;
            case 3: value->channel_3 = brightness; break;
            default: break;
        }
    }
}

bool leds_init(void)
{
    uint32_t position = 0;
    /* Device ID 7207: 7 yellow, 2 red, 0 green, 7 blue. */
    for (uint32_t i = 0; i < 7U; ++i) append_fade(&position, 0);
    position += PAUSE_STEPS;
    for (uint32_t i = 0; i < 2U; ++i) append_fade(&position, 1);
    position += PAUSE_STEPS;
    position += PAUSE_STEPS; /* Zero green fades, with group pause. */
    for (uint32_t i = 0; i < 7U; ++i) append_fade(&position, 3);
    position += PAUSE_STEPS;
    if (position != TOTAL_FRAMES) return false;

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
        .step_mode = NRF_PWM_STEP_TRIGGERED
    };
    if (nrfx_pwm_init(&pwm, &config, NULL) != NRFX_SUCCESS) return false;
    /* Triggered stepping holds current duty indefinitely while paused. */
    nrfx_pwm_simple_playback(&pwm, &pwm_sequence, 1, NRFX_PWM_FLAG_LOOP);
    return true;
}

void leds_advance(void)
{
    nrfx_pwm_step(&pwm);
}
