#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Delay.h"

int main(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6| GPIO_Pin_7;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA, &GPIO_Initstructure);

	while(1)
	{
	  //点亮第一个LED
		GPIO_SetBits(GPIOA, GPIO_Pin_7 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 );
		GPIO_ResetBits(GPIOA, GPIO_Pin_0| GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_6 );
		Delay_ms(500);
	 //关闭所有LED
		GPIO_ResetBits(GPIOA, GPIO_Pin_7 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3 );
	 //点亮第二个LED
		GPIO_SetBits(GPIOA, GPIO_Pin_6 | GPIO_Pin_3 | GPIO_Pin_2 | GPIO_Pin_0 );
		GPIO_ResetBits(GPIOA, GPIO_Pin_1| GPIO_Pin_4 | GPIO_Pin_5 | GPIO_Pin_7 );
		Delay_ms(500);
	//关闭所有LED	
		GPIO_ResetBits(GPIOA, GPIO_Pin_6 | GPIO_Pin_3 | GPIO_Pin_2 | GPIO_Pin_0 );
		
    }
}
 