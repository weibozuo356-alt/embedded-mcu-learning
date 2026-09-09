#ifndef __KEY_H_
#define __KEY_H_

#include "stm32f10x.h"

void Key_Init(void);
uint8_t Key_GetFlag(void);
uint8_t Key_GetFlag2(void);

#endif
