#include "stm32f10x.h"
#include "LED.h"
#include "Delay.h"
#include "Seg.h"
#include "Key.h"

int main(void)
{
    Key_Init();
	LED_Init();
	Seg_Init();

	int Number = 0;
    
	while (1)
    {
		
	//	Seg_Set(5,0);
		
		if (Key_GetFlag()==1)
		{
		    LED_Turn();
			Number ++;
			if(Number==10)
			{ Number=0;}
		}
	if (Key_GetFlag2()==1)
		{
		    LED_Turn();
			Number --;
			if(Number==-1)
			{ Number=9;}
		}   
     Seg_Set(Number,0);
		
    }
}
