#include "led.h"

void leds_init(void)
{
    // HIGH = OFF for active-low LEDs
    nrf_gpio_pin_write(LED_0, 1);
    nrf_gpio_pin_write(LED_1, 1);
    nrf_gpio_pin_write(LED_2, 1);
    nrf_gpio_pin_write(LED_3, 1);

    nrf_gpio_cfg_output(LED_0);
    nrf_gpio_cfg_output(LED_1);
    nrf_gpio_cfg_output(LED_2);
    nrf_gpio_cfg_output(LED_3);
}

void led_on(uint32_t pin)
{
    nrf_gpio_pin_write(pin, 0);
}

void led_off(uint32_t pin)
{
    nrf_gpio_pin_write(pin, 1);
}