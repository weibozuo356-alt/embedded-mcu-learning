#include "stm32f10x.h"                  // Device header




void LED_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_10 |GPIO_Pin_1| GPIO_Pin_9;
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_Initstructure);
	GPIO_Init(GPIOA, &GPIO_Initstructure);
}

void LED_Set( uint8_t LED_Num, uint8_t LED_On)  //定义一个函数
{
	switch (LED_Num)   //选择哪个led
		{
		case 1:
			switch(LED_On)      //选择led状态 开/关
			{
				case 0:{GPIO_SetBits( GPIOA, GPIO_Pin_0); break;}
				case 1:{GPIO_ResetBits( GPIOA, GPIO_Pin_0); break;}
			}
	    case 2:
			switch(LED_On)
			{
				case 0:{GPIO_SetBits( GPIOA, GPIO_Pin_1); break;}
				case 1:{GPIO_ResetBits( GPIOA, GPIO_Pin_1); break;}
			}
		case 3:
			switch(LED_On)
			{
				case 0:{GPIO_SetBits( GPIOB, GPIO_Pin_0); break;}
				case 1:{GPIO_ResetBits( GPIOB, GPIO_Pin_0); break;}
			}
		case 4:
			switch(LED_On)
			{
				case 0:{GPIO_SetBits( GPIOB, GPIO_Pin_1); break;}
				case 1:{GPIO_ResetBits( GPIOB, GPIO_Pin_1); break;}
			}
		}
}

void LED_Turn(void)
{
  if  (GPIO_ReadOutputDataBit(GPIOA, GPIO_Pin_9) == 1) 
	{
		GPIO_ResetBits( GPIOA, GPIO_Pin_9);
	}
  else
  {
    GPIO_SetBits( GPIOA, GPIO_Pin_9);
  }
	
}
