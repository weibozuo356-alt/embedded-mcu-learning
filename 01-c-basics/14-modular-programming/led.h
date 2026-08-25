#ifndef LED_H
#define LED_H

typedef enum
{
    LED_STATE_OFF = 0,
    LED_STATE_ON
} LedState;

void led_init(void);
void led_on(void);
void led_off(void);
void led_blink(unsigned int count);
LedState led_get_state(void);

#endif
