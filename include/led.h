#ifndef ESL_LED_H
#define ESL_LED_H

#include <stdbool.h>
#include <stdint.h>
#include "nrf_gpio.h"
#include "hsv.h"

#define LED_0 NRF_GPIO_PIN_MAP(0, 6) // Indicator
#define LED_1 NRF_GPIO_PIN_MAP(0, 8) // Red
#define LED_2 NRF_GPIO_PIN_MAP(1, 9) // Green
#define LED_3 NRF_GPIO_PIN_MAP(0, 12) // Blue

bool leds_init(void);
void led_set_rgb(rgb_color_t color);
void led_set_indicator(bool on);

#endif