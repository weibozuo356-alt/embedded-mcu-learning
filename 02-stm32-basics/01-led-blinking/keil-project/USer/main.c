#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Delay.h"

int main(void)
{
	LED_Init();

	while(1)
	{
	  GPIO_ResetBits(GPIOA, GPIO_Pin_0);
	  Delay_s(1);
	  GPIO_SetBits(GPIOA, GPIO_Pin_0);
	  Delay_s(1);
	  GPIO_ResetBits(GPIOA, GPIO_Pin_1);
	  Delay_s(1);
	  GPIO_SetBits(GPIOA, GPIO_Pin_1);
	  Delay_s(1);
      GPIO_ResetBits(GPIOB, GPIO_Pin_0);
	  Delay_s(1);
	  GPIO_SetBits(GPIOB, GPIO_Pin_0);
	  Delay_s(1);
	  GPIO_ResetBits(GPIOB, GPIO_Pin_1);
	  Delay_s(1);
	  GPIO_SetBits(GPIOB, GPIO_Pin_1);
	  Delay_s(1);
	}
}
