#include "stm32f10x.h"
#include "Delay.h"
#include "Seg.h"

/* PA0～PA7分别连接a、b、c、d、e、f、g、dp */
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

/**
  * @brief  初始化数码管GPIO
  * @param  无
  * @retval 无
  */
void Seg_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStructure;

    /* 开启GPIOA和GPIOB时钟 */
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    /* PA0～PA7控制a～g和小数点 */
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = SEG_ALL;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* PB0、PB1控制两个数码管的公共阳极 */
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /* 共阳数码管：段线为高电平时熄灭 */
    GPIO_SetBits(GPIOA, SEG_ALL);

    /* 公共阳极为低电平时不选中 */
    GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);
}

/**
  * @brief  设置数码管显示的一个数字
  * @param  Number：需要显示的数字，范围0～9
  * @retval 无
  */
static void Seg_DisplayNumber(uint8_t Number)
{
    /* 每次显示新数字前，先熄灭所有灯段 */
    GPIO_SetBits(GPIOA, SEG_ALL);

    switch (Number)
    {
        case 0:
            GPIO_ResetBits(
                GPIOA,
                SEG_A | SEG_B | SEG_C |
                SEG_D | SEG_E | SEG_F
            );
            break;

        case 1:
            GPIO_ResetBits(
                GPIOA,
                SEG_B | SEG_C
            );
            break;

        case 2:
            GPIO_ResetBits(
                GPIOA,
                SEG_A | SEG_B | SEG_D |
                SEG_E | SEG_G
            );
            break;

        case 3:
            GPIO_ResetBits(
                GPIOA,
                SEG_A | SEG_B | SEG_C |
                SEG_D | SEG_G
            );
            break;

        case 4:
            GPIO_ResetBits(
                GPIOA,
                SEG_B | SEG_C |
                SEG_F | SEG_G
            );
            break;

        case 5:
            GPIO_ResetBits(
                GPIOA,
                SEG_A | SEG_C | SEG_D |
                SEG_F | SEG_G
            );
            break;

        case 6:
            GPIO_ResetBits(
                GPIOA,
                SEG_A | SEG_C | SEG_D |
                SEG_E | SEG_F | SEG_G
            );
            break;

        case 7:
            GPIO_ResetBits(
                GPIOA,
                SEG_A | SEG_B | SEG_C
            );
            break;

        case 8:
            GPIO_ResetBits(
                GPIOA,
                SEG_A | SEG_B | SEG_C |
                SEG_D | SEG_E | SEG_F | SEG_G
            );
            break;

        case 9:
            GPIO_ResetBits(
                GPIOA,
                SEG_A | SEG_B | SEG_C |
                SEG_D | SEG_F | SEG_G
            );
            break;

        default:
            /* 不是0～9时不显示 */
            GPIO_SetBits(GPIOA, SEG_ALL);
            break;
    }
}

/**
  * @brief  动态扫描两个数码管
  * @param  Number1：第一位显示的数字
  * @param  Number2：第二位显示的数字
  * @retval 无
  */
void Seg_Set(uint8_t Number1, uint8_t Number2)
{
    /* ---------- 显示第一位 ---------- */

    /* 先关闭两个数码管，防止重影 */
    GPIO_ResetBits(GPIOB, GPIO_Pin_0 | GPIO_Pin_1);

    /* 设置第一位需要显示的灯段 */
    Seg_DisplayNumber(Number1);

    /* PB0高电平，选中第一位 */
    GPIO_SetBits(GPIOB, GPIO_Pin_0);

    Delay_ms(1);

    /* 关闭第一位 */
    GPIO_ResetBits(GPIOB, GPIO_Pin_0);

    /* ---------- 显示第二位 ---------- */

    /* 设置第二位需要显示的灯段 */
    Seg_DisplayNumber(Number2);

    /* PB1高电平，选中第二位 */
    GPIO_SetBits(GPIOB, GPIO_Pin_1);

    Delay_ms(1);

    /* 关闭第二位 */
    GPIO_ResetBits(GPIOB, GPIO_Pin_1);
}