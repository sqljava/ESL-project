#ifndef LED_H
#define LED_H

#include <stdint.h>
#include "nrf_gpio.h"

#define LED_0 NRF_GPIO_PIN_MAP(0, 6)
#define LED_1 NRF_GPIO_PIN_MAP(0, 8)
#define LED_2 NRF_GPIO_PIN_MAP(1, 9)
#define LED_3 NRF_GPIO_PIN_MAP(0, 12)

void leds_init(void);
void led_on(uint32_t pin);
void led_off(uint32_t pin);

#endif