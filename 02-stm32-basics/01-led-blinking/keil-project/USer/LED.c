#include "stm32f10x.h"
#include "LED.h"

void LED_Init(void)
{
    GPIO_InitTypeDef gpio_init_structure;

    RCC_APB2PeriphClockCmd(
        RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB,
        ENABLE);

    /* 本实验采用低电平点亮，初始化前先将输出锁存器设为高电平。 */
    GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_1);
    GPIO_SetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);

    gpio_init_structure.GPIO_Mode = GPIO_Mode_Out_PP;
    gpio_init_structure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    gpio_init_structure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_Init(GPIOA, &gpio_init_structure);
    GPIO_Init(GPIOB, &gpio_init_structure);
}

void LED_Set(uint8_t led_num, uint8_t led_state)
{
    GPIO_TypeDef *gpio_port;
    uint16_t gpio_pin;

    switch (led_num)
    {
        case LED_1:
            gpio_port = GPIOA;
            gpio_pin = GPIO_Pin_0;
            break;

        case LED_2:
            gpio_port = GPIOA;
            gpio_pin = GPIO_Pin_1;
            break;

        case LED_3:
            gpio_port = GPIOB;
            gpio_pin = GPIO_Pin_0;
            break;

        case LED_4:
            gpio_port = GPIOB;
            gpio_pin = GPIO_Pin_1;
            break;

        default:
            return;
    }

    if (led_state == LED_ON)
    {
        GPIO_ResetBits(gpio_port, gpio_pin);
    }
    else
    {
        GPIO_SetBits(gpio_port, gpio_pin);
    }
}
