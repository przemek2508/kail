#include "stm32f4xx.h"

static __IO uint32_t TimingDelay;

void Delay(__IO uint32_t nTime);
void TimingDelay_Decrement(void);
GPIO_InitTypeDef GPIO_IntStructure;


int main(void)
{
			SystemInit();
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	SysTick_Config(168000);
	
	GPIO_IntStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_IntStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_IntStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_IntStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_IntStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init (GPIOD, &GPIO_IntStructure);
	GPIO_SetBits(GPIOD, GPIO_Pin_12);
	while(1)
	{
		//GPIO_SetBits(GPIOD, GPIO_Pin_12);
		//Delay(1000);
		//GPIO_SetBits(GPIOD, GPIO_Pin_13);
		//Delay(1000);
	}

}


void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

/**
  * @brief  Zmniejszanie zmiennej TimingDelay, wykorzystywane w przerwaniu systick
  * @param  None
  * @retval None
  */
void TimingDelay_Decrement(void)
{
  if (TimingDelay != 0x00)
  { 
    TimingDelay--;
  }
}