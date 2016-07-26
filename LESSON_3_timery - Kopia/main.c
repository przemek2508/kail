#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_adc.h"
#include "misc.h"
#include "stm32f4xx_tim.h"

GPIO_InitTypeDef  GPIO_InitStructure;
TIM_TimeBaseInitTypeDef timerInitStructure;
NVIC_InitTypeDef nvicStructure; 
__IO uint32_t TimeDelay;

void Delay(__IO uint32_t time){
	TimeDelay = time;
	while(TimeDelay != 0){	
	}
}

int main(void){
	//----------------ustawienie zegarow---------------------
	SystemInit();
	//------------wlaczenie zegarow peryferiow---------------
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE); //wybór peryferium na szynie "dioda"
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC, ENABLE); //wybór peryferium na szynie "dioda"
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //wybór peryferium "timer"
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1,ENABLE); //wybór peryferium "timer"
	
	nvicStructure.NVIC_IRQChannel = TIM2_IRQn; 							//co przerwie
	nvicStructure.NVIC_IRQChannelPreemptionPriority = 2; 		//piorytet (0 najwiekszy) -3 jest dla resetu; -1, -2 bledy systemowe
	nvicStructure.NVIC_IRQChannelSubPriority = 3; 					//podpriorytet
	nvicStructure.NVIC_IRQChannelCmd = ENABLE; 			// wlaczenie

	NVIC_Init(&nvicStructure); 
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD, &GPIO_InitStructure); //Przygotowanie diód 

	
	timerInitStructure.TIM_Prescaler = 84; 				 						//dzielenie szyny zegarowej
	timerInitStructure.TIM_CounterMode =	TIM_CounterMode_Up;			//zliczanie od 0 do góry								
	timerInitStructure.TIM_Period = 50000;    											//okres
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 					//
	timerInitStructure.TIM_RepetitionCounter = 0;									//po ilu zliczeniach ma strzelac - opóznienie o cale okresy
	TIM_TimeBaseInit(TIM2, &timerInitStructure);									//
	TIM_Cmd(TIM2, ENABLE);
	TIM_ITConfig(TIM2, TIM_IT_Update , ENABLE);
	
	SysTick_Config(168000);
	
	while(1){
		
		Delay(100);
		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
		
		Delay(100);
		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
		
		Delay(100);
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
		
		Delay(100);
		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
		
	}
}
