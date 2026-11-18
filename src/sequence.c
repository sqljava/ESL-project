#include <stdbool.h>
#include "sequence.h"
#include "button.h"
#include "led.h"
static bool running;
void sequence_tick(void)
{
    if (button_double_click_tick()) running = !running;
    if (running) leds_advance();
}
