#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_it.h"
#include "delay.h"


void GPIO(void); 

int main(void) {
	SystemInit();
	GPIO();

    while (1) {

 
		delay_ms(1000);
		GPIO_SetBits(GPIOD, GPIO_Pin_15);
		delay_ms(1000);
		GPIO_SetBits(GPIOD, GPIO_Pin_14);
		delay_ms(1000);
		GPIO_SetBits(GPIOD, GPIO_Pin_13);
		delay_ms(1000);
		GPIO_SetBits(GPIOD, GPIO_Pin_12);
		delay_ms(1000);
		GPIO_ResetBits(GPIOD, GPIO_Pin_15);
		delay_ms(1000);
		GPIO_ResetBits(GPIOD, GPIO_Pin_14);
		delay_ms(1000);
		GPIO_ResetBits(GPIOD, GPIO_Pin_13);
		delay_ms(1000);
		GPIO_ResetBits(GPIOD, GPIO_Pin_12);
	}
}
 
void GPIO(void)
 {
	GPIO_InitTypeDef GPIO_IntStructure;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
  GPIO_IntStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_IntStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_IntStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_IntStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_IntStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init (GPIOD, &GPIO_IntStructure);
 }
