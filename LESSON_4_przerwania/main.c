#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "misc.h"

GPIO_InitTypeDef  GPIO_InitStructure;
TIM_TimeBaseInitTypeDef timerInitStructure;
NVIC_InitTypeDef nvicStructure; // inicjalizacja

int main(void){
	 SystemInit();
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); //wybór peryferium na szynie "dioda"
	
	
	nvicStructure.NVIC_IRQChannel = TIM2_IRQn; //co przerywa
	nvicStructure.NVIC_IRQChannelPreemptionPriority = 0; //priorytet 
	nvicStructure.NVIC_IRQChannelSubPriority = 1; //podpriorytet
	nvicStructure.NVIC_IRQChannelCmd = ENABLE; //wlaczenie
	NVIC_Init(&nvicStructure);
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure); //Przygotowanie diód do [wiecenia
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //wybór peryferium "timer"
	
	
	timerInitStructure.TIM_Prescaler = 80000; //konfiguracja
	timerInitStructure.TIM_CounterMode =
	TIM_CounterMode_Up;											
	timerInitStructure.TIM_Period = 5000;    
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	timerInitStructure.TIM_RepetitionCounter = 5;
	TIM_TimeBaseInit(TIM2, &timerInitStructure);	
	TIM_Cmd(TIM2, ENABLE);

	 
		for(;;) //petla mrygania
		{
			int timerValue = TIM_GetCounter(TIM2); //sprawdzanie wartosci timera
			if(timerValue <=2500)
				GPIO_WriteBit(GPIOD, GPIO_Pin_13, Bit_SET); //zapal diode
			else if (timerValue > 2500) 
				GPIO_WriteBit(GPIOD, GPIO_Pin_13, Bit_RESET); //zgas diode
		}
	 
		
	}


	
