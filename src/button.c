#include "button.h"
#include "nrf_gpio.h"

#define BUTTON_PIN NRF_GPIO_PIN_MAP(1, 6)

void button_init(void)
{
    nrf_gpio_cfg_input(BUTTON_PIN, NRF_GPIO_PIN_PULLUP);
}

bool button_pressed(void)
{
    return nrf_gpio_pin_read(BUTTON_PIN) == 0;
}