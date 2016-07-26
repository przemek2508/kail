#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "lcd4bit.h"

GPIO_InitTypeDef GPIO_IntStructure;
void Delay (__IO uint32_t time); //Deklaracja naszej funkcji opozniajacej
extern __IO uint32_t TimeDelay; //Zmienna volatile (__IO)
__IO uint32_t TimeDelay;
int i;
int liczba = 999;
				
void SysTick_Handler(void)
{
	if (TimeDelay!=0){
	TimeDelay--;
	}
}
int main(void) {
	LCD_Init();
	LCD_Clear();
	LCD_GoTo(0,0);
	SystemInit();
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	
	SysTick_Config(168000);
	
	GPIO_IntStructure.GPIO_Pin = GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
	GPIO_IntStructure.GPIO_Mode = GPIO_Mode_OUT;
	GPIO_IntStructure.GPIO_OType = GPIO_OType_PP;
	GPIO_IntStructure.GPIO_Speed = GPIO_Speed_100MHz;
	GPIO_IntStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init (GPIOD, &GPIO_IntStructure);

	
	
	
LCD_Clear();
LCD_SendTextyx(0,0, "Hello");
LCD_GoTo(1,0);

LCD_SendInt(liczba);
LCD_MoveCursorRight();
LCD_MoveCursorRight();

	while(1)
	{
	GPIO_SetBits(GPIOD, GPIO_Pin_15);
	Delay(1000);
	GPIO_ResetBits(GPIOD, GPIO_Pin_15);
	Delay(1000);


		
		
		
		
	}
	}

	void Delay (__IO uint32_t time){
	TimeDelay=time;
	while (TimeDelay!=0){
	}
}


