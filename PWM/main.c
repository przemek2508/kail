#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx.h"
#include "stm32f4xx_tim.h"

int D1 = 1, D2 = 40, D3 = 80, D4 = 100;
int main(void)
{
	TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  TIM_OCInitTypeDef  TIM_OCInitStructure;

  /* TIM4 konfiguracja */

  GPIO_InitTypeDef GPIO_InitStructure;


  /* TIM4 wlaczenie zegara */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);


  /* ustawienie portu/pinów */
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_100MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
  GPIO_Init(GPIOD, &GPIO_InitStructure);


  GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource13, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource14, GPIO_AF_TIM4);
  GPIO_PinAFConfig(GPIOD, GPIO_PinSource15, GPIO_AF_TIM4);



  /* konfiguracja czasu "bazy" */
  TIM_TimeBaseStructure.TIM_Period = 50 - 1;
  TIM_TimeBaseStructure.TIM_Prescaler = 230 - 1;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;


  TIM_TimeBaseInit(TIM4, &TIM_TimeBaseStructure);


  /* PWM1 konfiguracja: kanal 1 */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;


  TIM_OC1Init(TIM4, &TIM_OCInitStructure);


  TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);


  /* PWM1 konfiguracja: kanal 2 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;


  TIM_OC2Init(TIM4, &TIM_OCInitStructure);


  TIM_OC2PreloadConfig(TIM4, TIM_OCPreload_Enable);


  /* PWM1 konfiguracja: kanal 3 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;


  TIM_OC3Init(TIM4, &TIM_OCInitStructure);


  TIM_OC3PreloadConfig(TIM4, TIM_OCPreload_Enable);


  /* PWM1 konfiguracja: kanal 4 */
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0;


  TIM_OC4Init(TIM4, &TIM_OCInitStructure);


  TIM_OC4PreloadConfig(TIM4, TIM_OCPreload_Enable);


  TIM_ARRPreloadConfig(TIM4, ENABLE);


  /* TIM4 - wlaczenie */
  TIM_Cmd(TIM4, ENABLE);

   
	        TIM4->CCR3 = 25;
          TIM4->CCR4 = 25;
          TIM4->CCR1 = 25;
          TIM4->CCR2 = 25;
	
	 while(1) 
    {
			int i, j;
			for (i=0; i<=1000; i++)
			{
				for (j=0; j<=1000; j++) {}
			}
    }
}