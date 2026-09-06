#ifndef __LED_H
#define __LED_H

#include <stdint.h>

#define LED_1    1U
#define LED_2    2U
#define LED_3    3U
#define LED_4    4U

#define LED_OFF  0U
#define LED_ON   1U

void LED_Init(void);
void LED_Set(uint8_t led_num, uint8_t led_state);

#endif
