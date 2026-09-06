#include "stm32f10x.h"
#include "Delay.h"

void Delay_us(uint32_t xus)
{
    uint32_t ticks;

    if (xus == 0U)
    {
        return;
    }

    ticks = (SystemCoreClock / 1000000U) * xus;
    SysTick->LOAD = ticks - 1U;
    SysTick->VAL = 0U;
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_ENABLE_Msk;

    while ((SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk) == 0U)
    {
    }

    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk;
}

void Delay_ms(uint32_t xms)
{
    while (xms-- > 0U)
    {
        Delay_us(1000U);
    }
}

void Delay_s(uint32_t xs)
{
    while (xs-- > 0U)
    {
        Delay_ms(1000U);
    }
}
