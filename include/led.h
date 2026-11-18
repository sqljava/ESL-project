#ifndef ESL_LED_H
#define ESL_LED_H
#include <stdbool.h>
#include <stdint.h>
#include "nrf_gpio.h"
#define LED_0 NRF_GPIO_PIN_MAP(0, 6)
#define LED_1 NRF_GPIO_PIN_MAP(0, 8)
#define LED_2 NRF_GPIO_PIN_MAP(1, 9)
#define LED_3 NRF_GPIO_PIN_MAP(0, 12)
bool leds_init(void);
void leds_advance(void);
#endif
