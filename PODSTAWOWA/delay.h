#ifndef __DELAY_H
#define __DELAY_H
#include "stm32f4xx.h"

void SysTick_Init(void);
void TimeTick_Decrement(void);
void SysTick_Handler(void);
void delay_1ms(void);
void delay_ms(u32 n);

#endif