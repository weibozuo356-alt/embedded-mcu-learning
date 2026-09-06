#include "stm32f10x.h"
#include "LED.h"
#include "Delay.h"

int main(void)
{
    LED_Init();

    while (1)
    {
        LED_Set(LED_1, LED_ON);
        Delay_s(1);
        LED_Set(LED_1, LED_OFF);

        LED_Set(LED_2, LED_ON);
        Delay_s(1);
        LED_Set(LED_2, LED_OFF);

        LED_Set(LED_3, LED_ON);
        Delay_s(1);
        LED_Set(LED_3, LED_OFF);

        LED_Set(LED_4, LED_ON);
        Delay_s(1);
        LED_Set(LED_4, LED_OFF);
    }
}
