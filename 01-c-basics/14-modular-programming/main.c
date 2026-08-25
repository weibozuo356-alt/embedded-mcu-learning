#include <stdio.h>

#include "config.h"
#include "led.h"

int main(void)
{
    printf("Application: %s\n", APP_NAME);

#if DEBUG_OUTPUT
    printf("Debug output is enabled.\n");
#endif

    led_init();
    led_on();
    led_off();
    led_blink(LED_BLINK_COUNT);

    if (led_get_state() == LED_STATE_OFF)
    {
        printf("The final LED state is OFF.\n");
    }

    return 0;
}
