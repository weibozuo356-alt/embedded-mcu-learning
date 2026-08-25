#include "led.h"

#include <stdio.h>

static LedState current_state = LED_STATE_OFF;

static void print_state(void)
{
    const char *state_text = current_state == LED_STATE_ON ? "ON" : "OFF";
    printf("LED state: %s\n", state_text);
}

void led_init(void)
{
    current_state = LED_STATE_OFF;
    printf("LED initialized.\n");
    print_state();
}

void led_on(void)
{
    current_state = LED_STATE_ON;
    print_state();
}

void led_off(void)
{
    current_state = LED_STATE_OFF;
    print_state();
}

void led_blink(unsigned int count)
{
    for (unsigned int index = 0U; index < count; ++index)
    {
        printf("Blink %u\n", index + 1U);
        led_on();
        led_off();
    }
}

LedState led_get_state(void)
{
    return current_state;
}
