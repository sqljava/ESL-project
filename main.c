#include <stdbool.h>

#include "nrf_delay.h"
#include "led.h"
#include "button.h"
#include "color_picker.h"

int main(void)
{
    if (!leds_init() || !button_init())
    {
        while (true) {}
    }

    color_picker_init();

    while (true)
    {
        nrf_delay_ms(10);
        color_picker_tick();
    }
}