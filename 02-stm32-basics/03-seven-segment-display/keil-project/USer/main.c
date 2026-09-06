#include "stm32f10x.h"
#include "Delay.h"

/* 数码管各段对应的GPIO引脚 */
#define SEG_A       GPIO_Pin_0
#define SEG_B       GPIO_Pin_1
#define SEG_C       GPIO_Pin_2
#define SEG_D       GPIO_Pin_3
#define SEG_E       GPIO_Pin_4
#define SEG_F       GPIO_Pin_5
#define SEG_G       GPIO_Pin_6
#define SEG_DP      GPIO_Pin_7

#define SEG_ALL    (SEG_A | SEG_B | SEG_C | SEG_D | \
                    SEG_E | SEG_F | SEG_G | SEG_DP)

int main(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;
    uint8_t i = 1;

    /* 开启GPIOA和GPIOB时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    /* 配置PA0～PA7，控制a～g和小数点 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = SEG_ALL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* 配置PB0，控制数码管公共阳极 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* PB0输出高电平，启用共阳数码管 */
    GPIO_SetBits(GPIOB, GPIO_Pin_0);

    /* 共阳数码管：高电平关闭所有灯段 */
    GPIO_SetBits(GPIOA, SEG_ALL);

    while (1)
    {
        /*
         * 每次显示新数字前先关闭所有灯段。
         * 共阳数码管中：
         * SetBits   = 高电平 = 熄灭
         * ResetBits = 低电平 = 点亮
         */
        GPIO_SetBits(GPIOA, SEG_ALL);

        switch (i)
        {
            case 0:
            {
                /* 0：a、b、c、d、e、f */
                GPIO_ResetBits(GPIOA,
                               SEG_A | SEG_B | SEG_C |
                               SEG_D | SEG_E | SEG_F);
                break;
            }

            case 1:
            {
                /* 1：b、c */
                GPIO_ResetBits(GPIOA,
                               SEG_B | SEG_C);
                break;
            }

            case 2:
            {
                /* 2：a、b、d、e、g */
                GPIO_ResetBits(GPIOA,
                               SEG_A | SEG_B | SEG_D |
                               SEG_E | SEG_G);
                break;
            }

            case 3:
            {
                /* 3：a、b、c、d、g */
                GPIO_ResetBits(GPIOA,
                               SEG_A | SEG_B | SEG_C |
                               SEG_D | SEG_G);
                break;
            }

            case 4:
            {
                /* 4：b、c、f、g */
                GPIO_ResetBits(GPIOA,
                               SEG_B | SEG_C |
                               SEG_F | SEG_G);
                break;
            }

            case 5:
            {
                /* 5：a、c、d、f、g */
                GPIO_ResetBits(GPIOA,
                               SEG_A | SEG_C | SEG_D |
                               SEG_F | SEG_G);
                break;
            }

            case 6:
            {
                /* 6：a、c、d、e、f、g */
                GPIO_ResetBits(GPIOA,
                               SEG_A | SEG_C | SEG_D |
                               SEG_E | SEG_F | SEG_G);
                break;
            }

            case 7:
            {
                /* 7：a、b、c */
                GPIO_ResetBits(GPIOA,
                               SEG_A | SEG_B | SEG_C);
                break;
            }

            case 8:
            {
                /* 8：a、b、c、d、e、f、g */
                GPIO_ResetBits(GPIOA,
                               SEG_A | SEG_B | SEG_C |
                               SEG_D | SEG_E | SEG_F |
                               SEG_G);
                break;
            }

            case 9:
            {
                /* 9：a、b、c、d、f、g */
                GPIO_ResetBits(GPIOA,
                               SEG_A | SEG_B | SEG_C |
                               SEG_D | SEG_F | SEG_G);
                break;
            }

            default:
            {
                GPIO_SetBits(GPIOA, SEG_ALL);
                break;
            }
        }

        Delay_s(1);

        i++;

        if (i > 9)
        {
            i = 0;
        }
    }
}