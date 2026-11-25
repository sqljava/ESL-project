#include <stdint.h>
#include "button.h"
#include "nrf_gpio.h"
#include "nrfx_gpiote.h"
#define BUTTON_PIN NRF_GPIO_PIN_MAP(1, 6)
#define DEBOUNCE_TICKS 3U
#define DOUBLE_CLICK_TICKS 30U

static volatile bool raw_pressed;
static bool candidate;
static bool stable_pressed;
static uint8_t stable_ticks;
static bool first_click_pending;
static uint8_t click_age;

static void button_event_handler(nrfx_gpiote_pin_t pin,
                                 nrf_gpiote_polarity_t action)
{
    (void)pin;
    (void)action;
    raw_pressed = (nrf_gpio_pin_read(BUTTON_PIN) == 0);
}

bool button_init(void)
{
    if (nrfx_gpiote_init() != NRFX_SUCCESS) return false;
    nrfx_gpiote_in_config_t config = NRFX_GPIOTE_CONFIG_IN_SENSE_TOGGLE(true);
    config.pull = NRF_GPIO_PIN_PULLUP;
    if (nrfx_gpiote_in_init(BUTTON_PIN, &config, button_event_handler) != NRFX_SUCCESS)
        return false;
    raw_pressed = (nrf_gpio_pin_read(BUTTON_PIN) == 0);
    candidate = raw_pressed;
    stable_pressed = raw_pressed;
    stable_ticks = 0;
    first_click_pending = false;
    click_age = 0;
    nrfx_gpiote_in_event_enable(BUTTON_PIN, true);
    return true;
}

bool button_double_click_tick(void)
{
    bool raw = raw_pressed;
    if (first_click_pending && ++click_age > DOUBLE_CLICK_TICKS)
        first_click_pending = false;
    if (raw != candidate)
    {
        candidate = raw;
        stable_ticks = 0;
        return false;
    }
    if (stable_ticks < DEBOUNCE_TICKS) ++stable_ticks;
    if (stable_ticks < DEBOUNCE_TICKS || candidate == stable_pressed)
        return false;
    stable_pressed = candidate;
    if (stable_pressed) return false; /* Count completed press-release clicks. */
    if (first_click_pending)
    {
        first_click_pending = false;
        return true;
    }
    first_click_pending = true;
    click_age = 0;
    return false;
}

bool button_is_pressed(void)
{
    return stable_pressed;
}