#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_dac.h"
#include "stm32f4xx_it.h"
#include "lcd4bit.h"
#include "stm32f4_delay.h"
// -----Zmienne----
	int k = 2300;
	int z = 1;
	int l=0;
	int i;
	
///-----Deklaracja struktur----
EXTI_InitTypeDef   EXTI_InitStructure;
DAC_InitTypeDef DAC_InitStructure;
GPIO_InitTypeDef   GPIO_InitStructure;

///-----Deklaracja funkcji----
void Zmianaplus(void);
void DAC_Conf(void);
void EXTILine0_Config(void);
void EXTILine3_Config(void);
void Plus(void);
void Minus(void);
void Timer(uint16_t z);


int main(void) {
///-----Inicjalizacja funkcji----
	SystemInit();
	DELAY_Init();
	LCD_Init();
	DAC_Conf();
  EXTILine0_Config();
	EXTILine3_Config();
	
	
	LCD_Clear();
	LCD_GoTo(0,0);
	LCD_SendText("Probkowanie co:");
	LCD_GoTo(1,0);
	LCD_SendInt(z);
	


	DAC_Cmd(DAC_Channel_1, ENABLE);  //wlacz przetwornik

    while (1) {
			DAC_SetChannel1Data(DAC_Align_12b_R, k);
			k++;
			Delayms(z);
				if(k >= 4096) 
				{
				k=2300;
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
		if (z >= 2000) z=2000;
		else z++;
		LCD_Clear();
		LCD_SendText("Probkowanie co:");
		LCD_GoTo(1,0);
		LCD_SendInt(z);
	  
 }
 
 void Minus(void)
 {
	 if (z <=0) z=0;
		else z--;
		LCD_Clear();
		LCD_SendText("Probkowanie co:");
		LCD_GoTo(1,0);
		LCD_SendInt(z);
	
 }
 
 void Timer(uint16_t z)
 {
	 
	 
	 
	 
	 
	 
 }