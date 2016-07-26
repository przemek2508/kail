#include "stm32f4_discovery.h"


void Delay(__IO uint32_t nCount) {
  while(nCount--) {
  }
}
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
	
	while(1)
	{
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
	}

}