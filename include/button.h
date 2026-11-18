#ifndef ESL_BUTTON_H
#define ESL_BUTTON_H
#include <stdbool.h>
bool button_init(void);
/* Call once per 10 ms. True for one tick after a valid double-click. */
bool button_double_click_tick(void);
#endif
