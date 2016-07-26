#include "stm32f4xx.h"
int main(void){


	RCC->AHB1ENR|=RCC_AHB1ENR_GPIODEN;
	GPIOD->MODER=0x55000000;
	GPIOD->OTYPER = 0;
	GPIOD->OSPEEDR = 0;



while(1){
	
	GPIOD->ODR = 0xF000;
}


}