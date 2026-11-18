#include <stdint.h>
#include "nrf_delay.h"

#include "led.h"
#include "button.h"
#include "sequence.h"

#define BLINK_DELAY_MS 200
#define PAUSE_DELAY_MS 800
#define POLL_INTERVAL_MS 10

static void wait_while_pressed(uint32_t duration_ms)
{
    uint32_t elapsed = 0;

    while (elapsed < duration_ms)
    {
        if (button_pressed())
        {
            nrf_delay_ms(POLL_INTERVAL_MS);
            elapsed += POLL_INTERVAL_MS;
        }
    }
}

static void blink_led(uint32_t pin, uint32_t count)
{
    for (uint32_t i = 0; i < count; i++)
    {
        while (!button_pressed())
        {
        }

        led_on(pin);
        wait_while_pressed(BLINK_DELAY_MS);

        while (!button_pressed())
        {
        }

        led_off(pin);
        wait_while_pressed(BLINK_DELAY_MS);
    }
}

void sequence_run(void)
{
    blink_led(LED_0, 7);
    wait_while_pressed(PAUSE_DELAY_MS);

    blink_led(LED_1, 2);
    wait_while_pressed(PAUSE_DELAY_MS);

    blink_led(LED_2, 0);
    wait_while_pressed(PAUSE_DELAY_MS);

    blink_led(LED_3, 7);
    wait_while_pressed(PAUSE_DELAY_MS);
}