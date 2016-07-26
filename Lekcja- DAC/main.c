
#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_dac.h"

GPIO_InitTypeDef GPIO_IntStructure;

 
 void GPIO(void)
 {
 SystemInit();
 RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE); //wlaczenie taktowania GPIOA
 GPIO_IntStructure.GPIO_Pin  = GPIO_Pin_4;
 GPIO_IntStructure.GPIO_Mode = GPIO_Mode_AIN;
 GPIO_Init(GPIOA, &GPIO_IntStructure);
	 
 }
 void DACInit(void)
{
 DAC_InitTypeDef DAC_InitStructure;
//wylacz zewnetrzne wyzwalanie
 DAC_InitStructure.DAC_Trigger = DAC_Trigger_None;
//bufor dolaczony na wyjscie
 DAC_InitStructure.DAC_OutputBuffer = DAC_OutputBuffer_Enable;
//konfiguracja przetwornika
 DAC_Init(DAC_Channel_1, &DAC_InitStructure);
}

int main(void) {
	int j=0;
	int i;
	//taktowanie z magistrali APB1
RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
DAC_Cmd(DAC_Channel_1, ENABLE);//wlacz przetwornik

    while (1) {
			int k =2300;
			i= 2300;
			for(i=2300; i<=4095; i++)
			{
			DAC_SetChannel1Data(DAC_Align_12b_R, k);
			for(j=0; j<=5000; j++){}
			k++;
			}
    } 
	}

	
