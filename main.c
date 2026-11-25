#include <stdbool.h>
#include <stdint.h>

#include "nrfx_timer.h"
#include "led.h"
#include "button.h"
#include "color_picker.h"

#define TICK_INTERVAL_MS 10U

static const nrfx_timer_t timer = NRFX_TIMER_INSTANCE(1);

static volatile uint32_t pending_ticks = 0;

static void timer_handler(nrf_timer_event_t event_type,
                          void *p_context)
{
    (void)p_context;

    if (event_type == NRF_TIMER_EVENT_COMPARE0)
    {
        ++pending_ticks;
    }
}

static bool timer_init(void)
{
    nrfx_timer_config_t config = NRFX_TIMER_DEFAULT_CONFIG;

    config.frequency = NRF_TIMER_FREQ_1MHz;
    config.bit_width = NRF_TIMER_BIT_WIDTH_32;

    if (nrfx_timer_init(&timer, &config, timer_handler)
        != NRFX_SUCCESS)
    {
        return false;
    }

    uint32_t ticks = nrfx_timer_ms_to_ticks(
        &timer, TICK_INTERVAL_MS
    );

    nrfx_timer_extended_compare(
        &timer,
        NRF_TIMER_CC_CHANNEL0,
        ticks,
        NRF_TIMER_SHORT_COMPARE0_CLEAR_MASK,
        true
    );

    nrfx_timer_enable(&timer);

    return true;
}

int main(void)
{
    if (!leds_init() || !button_init())
    {
        while (true) {}
    }

    color_picker_init();

    if (!timer_init())
    {
        while (true) {}
    }

    while (true)
    {
        __disable_irq();

        if (pending_ticks > 0)
        {
            --pending_ticks;
            __enable_irq();

            color_picker_tick();
        }
        else
        {
            __DSB();
            __WFI();
            __enable_irq();
        }
    }
}