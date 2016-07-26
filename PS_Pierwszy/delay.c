#include "delay.h"

static __IO uint32_t sysTickCounter;

void SysTick_Init(void) {
	/****************************************
	 *SystemFrequency/1000      1ms         *
	 *SystemFrequency/100000    10us        *
	 *SystemFrequency/1000000   1us         *
	 *****************************************/
	while (SysTick_Config(SystemCoreClock / 100000 ) != 0) {
	} // One SysTick interrupt now equals 1us

}


/**
 * This method needs to be called in the SysTick_Handler
 */
	void TimeTick_Decrement(void) {
	if (sysTickCounter != 0x00) {
		sysTickCounter--;
	}
}

void delay_1ms(void) {
	SysTick_Init();
	sysTickCounter = 100;
	while (sysTickCounter != 0) {
	}
}

void delay_ms(u32 n) {
	SysTick_Init();
	sysTickCounter = 100*n;
	while (sysTickCounter != 0) {
	}
}
void SysTick_Handler(void) {
	TimeTick_Decrement();
}