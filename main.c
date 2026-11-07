/**
 * Copyright (c) 2014 - 2021, Nordic Semiconductor ASA
 *
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without modification,
 * are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice, this
 *    list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form, except as embedded into a Nordic
 *    Semiconductor ASA integrated circuit in a product or a software update for
 *    such product, must reproduce the above copyright notice, this list of
 *    conditions and the following disclaimer in the documentation and/or other
 *    materials provided with the distribution.
 *
 * 3. Neither the name of Nordic Semiconductor ASA nor the names of its
 *    contributors may be used to endorse or promote products derived from this
 *    software without specific prior written permission.
 *
 * 4. This software, with or without modification, must only be used with a
 *    Nordic Semiconductor ASA integrated circuit.
 *
 * 5. Any software provided in binary form under this license must not be reverse
 *    engineered, decompiled, modified and/or disassembled.
 *
 * THIS SOFTWARE IS PROVIDED BY NORDIC SEMICONDUCTOR ASA "AS IS" AND ANY EXPRESS
 * OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY, NONINFRINGEMENT, AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL NORDIC SEMICONDUCTOR ASA OR CONTRIBUTORS BE
 * LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
 * CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE
 * GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 */
/** @file
 *
 * @defgroup blinky_example_main main.c
 * @{
 * @ingroup blinky_example
 * @brief Blinky Example Application main file.
 *
 * This file contains the source code for a sample application to blink LEDs.
 *
 */

#include <stdbool.h>
#include <stdint.h>
#include "nrf_delay.h"
#include "nrf_gpio.h"

#define BLINK_DELAY_MS 200
#define PAUSE_DELAY_MS 800

#define LED_0 NRF_GPIO_PIN_MAP(0, 6)
#define LED_1 NRF_GPIO_PIN_MAP(0, 8)
#define LED_2 NRF_GPIO_PIN_MAP(1, 9)
#define LED_3 NRF_GPIO_PIN_MAP(0, 12)

/**
 * @brief Function for application main entry.
 */

// Initialization of LEDs as output pins
 static void leds_init(void)
{
    // Prepare output levels: HIGH means OFF
    nrf_gpio_pin_write(LED_0, 1);
    nrf_gpio_pin_write(LED_1, 1);
    nrf_gpio_pin_write(LED_2, 1);
    nrf_gpio_pin_write(LED_3, 1);

    // Enable GPIO output drivers
    nrf_gpio_cfg_output(LED_0);
    nrf_gpio_cfg_output(LED_1);
    nrf_gpio_cfg_output(LED_2);
    nrf_gpio_cfg_output(LED_3);
}

// Turns LED on by its pin
static void led_on(uint32_t pin){
    nrf_gpio_pin_write(pin, 0);
}

// Turns LED off by its pin
static void led_off(uint32_t pin){
    nrf_gpio_pin_write(pin, 1);
}

// Blink a selected LED a specified number of times
static void blink_led(uint32_t led, uint32_t count)
{
    for (uint32_t i = 0; i < count; i++)
    {
        led_on(led);
        nrf_delay_ms(BLINK_DELAY_MS);

        led_off(led);
        nrf_delay_ms(BLINK_DELAY_MS);
    }
}



int main(void)
{
    /* Configure board. */
    leds_init();

    /* Toggle LEDs. */
    while (true)
    {
        // Device ID: #7207

        blink_led(LED_0, 7);  // Yellow/green
        nrf_delay_ms(PAUSE_DELAY_MS);

        blink_led(LED_1, 2);  // Red
        nrf_delay_ms(PAUSE_DELAY_MS);

        blink_led(LED_2, 0);  // Green
        nrf_delay_ms(PAUSE_DELAY_MS);

        blink_led(LED_3, 7);  // Blue
        nrf_delay_ms(PAUSE_DELAY_MS);
    }
}

/**
 *@}
 **/
