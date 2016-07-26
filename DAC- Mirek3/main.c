#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_it.h"
#include "lcd4bit.h"
#include "stm32f4_delay.h"
// -----Zmienne----
	int k =0;
	int z = 1000;

	
///-----Deklaracja struktur----
EXTI_InitTypeDef   EXTI_InitStructure;
DAC_InitTypeDef DAC_InitStructure;
GPIO_InitTypeDef   GPIO_InitStructure;
TIM_TimeBaseInitTypeDef timerInitStructure;

///-----Deklaracja funkcji----
void Zmianaplus(void);
void DAC_Conf(void);
void EXTILine0_Config(void);
void EXTILine3_Config(void);
void Plus(void);
void Minus(void);
void Timer(void);


int main(void) {
///-----Inicjalizacja funkcji----
	SystemInit();
	DELAY_Init();
	LCD_Init();
	DAC_Conf();
  EXTILine0_Config();
	EXTILine3_Config();
	Timer();
	
	LCD_Clear();
	LCD_GoTo(0,0);
	LCD_SendText("Probkowanie co:");
	LCD_GoTo(1,0);
	LCD_SendInt(z);
	


	DAC_Cmd(DAC_Channel_1, ENABLE);  //wlacz przetwornik

    while (1) {
			
			int timerValue = TIM_GetCounter(TIM2); //sprawdzanie wartosci timera
			if(timerValue >=z-1)
				{
        TIM_ClearITPendingBit(TIM3, TIM_IT_Update);
				DAC_SetChannel1Data(DAC_Align_12b_R, k);
			  k++;
				if(k >= 4000) 
					{
					k=0;
					}	
		
	}
}
		}
	
	void EXTILine0_Config(void)
	{		
  GPIO_InitTypeDef   GPIO_InitStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;
		/* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
		
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
   
		/* Enable and set EXTI Line0 Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x00;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
		
  /* Enable GPIOA clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
		/* Configure PA0 pin as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
		
  /* Connect EXTI Line0 to PA0 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

  /* Configure EXTI Line0 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;  
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);


	
}	
void EXTILine3_Config(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;
	/* Enable SYSCFG clock */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);
	
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_1);
	/* Enable and set EXTI Line3 Interrupt to the lowest priority */
  NVIC_InitStructure.NVIC_IRQChannel = EXTI3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x01;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
	/* Enable GPIOA clock */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
  /* Configure PA3 pin as input floating */
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_DOWN;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
 
  /* Connect EXTI Line3 to PA3 pin */
  SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource3);
 
  /* Configure EXTI Line3 */
  EXTI_InitStructure.EXTI_Line = EXTI_Line3;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising; 
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure);
 
  
}

 void DAC_Conf(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
 RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
	GPIO_InitStructure.GPIO_Pin  = GPIO_Pin_4;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	


//wylacz zewnetrzne wyzwalanie
 DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
//bufor dolaczony na wyjscie
 DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
//konfiguracja przetwornika
	DAC_Init(DAC_Channel_1, &DAC_InitStructure);
  
}


void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}

 void Plus(void)
 {
		if (z >= 1000) z=1000;
		else z+=10;
		timerInitStructure.TIM_Period = z-1;
		LCD_Clear();
		LCD_SendText("Probkowanie co:");
		LCD_GoTo(1,0);
		LCD_SendInt(z);
	  
 }
 
 void Minus(void)
 {
	 if (z <=10) z=10;
		else z-=10;
		timerInitStructure.TIM_Period = z-1;
		LCD_Clear();
		LCD_SendText("Probkowanie co:");
		LCD_GoTo(1,0);
		LCD_SendInt(z);
	
 }
 
 void Timer(void)
 {
	 	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE); //wybór peryferium "timer"
	
	timerInitStructure.TIM_Period = z-1; 
	timerInitStructure.TIM_Prescaler = 63;
	timerInitStructure.TIM_CounterMode = TIM_CounterMode_Up;											   
	timerInitStructure.TIM_ClockDivision = TIM_CKD_DIV1; 
	timerInitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &timerInitStructure);	
	TIM_Cmd(TIM2, ENABLE);
	 
 }