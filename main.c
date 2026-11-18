#include <stdbool.h>
#include "nrf_delay.h"
#include "led.h"
#include "button.h"
#include "sequence.h"

int main(void)
{
    if (!leds_init() || !button_init())
    {
        while (true) { } /* Initialization failed. */
    }

    /* 10 ms scheduler; physical button edges are delivered by GPIOTE. */
    while (true)
    {
        nrf_delay_ms(10);
        sequence_tick();
    }
}
