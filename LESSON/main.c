#include "lcd4bit.h"

void RCC_Conf(void);
void GPIO_Conf(void);
void NVIC_Conf(void);

uint8_t *menu[8] = 	{	
				"LED1\0","LED2\0","LED3\0", "LED4\0", 
				"LED5\0", "LED6\0", "LED7\0", "LED8\0"
				};
uint8_t pozycja = 0;

int main(void)
{
#ifdef DEBUG
  debug();
#endif	 
  	RCC_Conf();   
  	NVIC_Conf();
  	GPIO_Conf();

	LCD_Init();
	LCD_Clear();

  	while (1)
	{
		// Zamiana pozycji w menu
		if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_0) && (pozycja < 7))
			pozycja++;
		if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_1) && (pozycja > 0))
			pozycja--;

		// Zapalenie odpowiedniej diody
		if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3))
			GPIO_SetBits(GPIOB, GPIO_Pin_8 << pozycja);

		// Zgaszenie odpowiedniej diody
		if(!GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2))
			GPIO_ResetBits(GPIOB, GPIO_Pin_8 << pozycja);

		// Wyswietlenie aktualnej pozycji w menu
		LCD_Clear();
		LCD_SendText(menu[pozycja]);
		delay_ms(200);
	}
}

void RCC_Conf(void)
{  
  ErrorStatus HSEStartUpStatus; 
  // Reset ustawien RCC
  RCC_DeInit();
  // Wlacz HSE
  RCC_HSEConfig(RCC_HSE_ON);
  // Czekaj za HSE bedzie gotowy
  HSEStartUpStatus = RCC_WaitForHSEStartUp();
  if(HSEStartUpStatus == SUCCESS)
  {
    FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);
    // zwloka dla pamieci Flash
    FLASH_SetLatency(FLASH_Latency_2);
    // HCLK = SYSCLK
    RCC_HCLKConfig(RCC_SYSCLK_Div1); 
    // PCLK2 = HCLK
    RCC_PCLK2Config(RCC_HCLK_Div1); 
    // PCLK1 = HCLK/2
    RCC_PCLK1Config(RCC_HCLK_Div2);
    // PLLCLK = 8MHz * 9 = 72 MHz
    RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);
    // Wlacz PLL 
    RCC_PLLCmd(ENABLE);
    // Czekaj az PLL poprawnie sie uruchomi
    while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET);
    // PLL bedzie zrodlem sygnalu zegarowego
    RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);
    // Czekaj az PLL bedzie sygnalem zegarowym systemu
    while(RCC_GetSYSCLKSource() != 0x08);
  }
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
}

void GPIO_Conf(void)
{
  	GPIO_InitTypeDef GPIO_InitStructure;

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_1 | GPIO_Pin_2 | GPIO_Pin_3;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOA, &GPIO_InitStructure);	 

  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOC, &GPIO_InitStructure);	 

  	// Wlacz obsluge wszyskich diod LED (LD1 do LD8)
  	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15;
  	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
  	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  	GPIO_Init(GPIOB, &GPIO_InitStructure);

  	GPIO_ResetBits(GPIOB, GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 | GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
}

void NVIC_Conf(void)
{


	#ifdef  VECT_TAB_RAM  
  		// Jezeli tablica wektorow w RAM, to ustaw jej adres na 0x20000000
  		NVIC_SetVectorTable(NVIC_VectTab_RAM, 0x0); 
	#else  // VECT_TAB_FLASH
  		// W przeciwnym wypadku ustaw na 0x08000000
  		NVIC_SetVectorTable(NVIC_VectTab_FLASH, 0x0);   
	#endif
}

#ifdef  DEBUG
void assert_failed(uint8_t* file, uint32_t line)
{ 
  	while (1);
}
#endif
