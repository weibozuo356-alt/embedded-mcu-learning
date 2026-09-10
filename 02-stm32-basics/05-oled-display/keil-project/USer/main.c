#include "stm32f10x.h"
#include "LED.h"
#include "Delay.h"
#include "Seg.h"
#include "Key.h"
#include "OLED.h"

int main(void)
{
    Key_Init();
	OLED_Init();

	int Number = 0;
    
	while (1)
    {
		
	   OLED_ShowHexNum(3,6,0x66,2);
		
		if (Key_GetFlag()==1)
		{
		    Number++;
		}
		OLED_ShowString(4,1,"Number=");
		OLED_ShowNum(4, 8, Number, 2);
		
    }
}
