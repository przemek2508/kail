// Dodac biblioteki:
//	dac; dma; gpio; rcc; tim.

#include <stm32f4xx.h>

/*
#define   FREQ          1                                 // Czestotliwosc wyjsciowa
#define   SIZE_TAB          32                                  // Ilosc wartosci w tabeli
#define   COUNTER         42000000                             // TIM6 zegar licznika
#define   PERIOD        ((COUNTER)/((SIZE_TAB)*(FREQ))) // Przeliczanie okresu
*/
					
										//SIZE_TAB
const uint16_t function[32] = { 2047, 2447, 2831, 3185, 3498, 3750, 3939, 4056, 4095, 4056,
                      3939, 3750, 3495, 3185, 2831, 2447, 2047, 1647, 1263, 909, 
                      599, 344, 155, 38, 0, 38, 155, 344, 599, 909, 1263, 1647 };           

																			
																			
																			
																		
void TIM6_Config(void);			// Deklaracja funkcji TIM6_Config
void DAC1_Config(void);			// Deklaracja funkcji DAC1_Config          
void GPIO_Config(void);
																		
int main()
{
  
	// Uruchomianie zegarów dla GPIO, DAC i DMA
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);                  
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_DAC, ENABLE);
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_DMA1, ENABLE);
	
	
	
	GPIO_Config();
  TIM6_Config();  
  DAC1_Config();
 
  while (1)
  {
		
    
  }

}
void GPIO_Config(void)
{
	// Pin PA4
	GPIO_InitTypeDef GPIO_Int;
  GPIO_Int.GPIO_Pin  = GPIO_Pin_4;
  GPIO_Int.GPIO_Mode = GPIO_Mode_AN;
  GPIO_Int.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_Int);

}
void TIM6_Config(void)
{
  TIM_TimeBaseInitTypeDef TIM6_TimeBase;

  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6, ENABLE); // Zegar
 
  TIM_TimeBaseStructInit(&TIM6_TimeBase); 
  TIM6_TimeBase.TIM_Period        = 400;						//(uint16_t)PERIOD;		// Obliczona wartosc do ktorej zlicza licznik          
  TIM6_TimeBase.TIM_Prescaler     = 50;       
  TIM6_TimeBase.TIM_ClockDivision = 0;    
  TIM6_TimeBase.TIM_CounterMode   = TIM_CounterMode_Up;  // Zliczanie w gore
  TIM_TimeBaseInit(TIM6, &TIM6_TimeBase);
  TIM_SelectOutputTrigger(TIM6, TIM_TRGOSource_Update);

  TIM_Cmd(TIM6, ENABLE);	// Zalaczenie licznika
}

void DAC1_Config(void)
{
  DAC_InitTypeDef DAC_INIT;
  DMA_InitTypeDef DMA_INIT;
  
  DAC_INIT.DAC_Trigger        = DAC_Trigger_T6_TRGO;  // TIM6 jako wyzwalacz DAC
  DAC_INIT.DAC_WaveGeneration = DAC_WaveGeneration_None;	// Wylaczenie generacji flai
  DAC_INIT.DAC_OutputBuffer   = DAC_OutputBuffer_Enable;	// Bufor zalaczony
  DAC_Init(DAC_Channel_1, &DAC_INIT);

  DMA_DeInit(DMA1_Stream5);
  DMA_INIT.DMA_Channel            = DMA_Channel_7;  // Najnizszy podpriorytet DMA
  DMA_INIT.DMA_PeripheralBaseAddr = (uint32_t)&DAC->DHR12R1;		// lub 0x40007408; // DMA zapisuje wartosc do tego rejestru
  DMA_INIT.DMA_Memory0BaseAddr    = (uint32_t)&function;	// DMA pobiera dane z tego bufora
  DMA_INIT.DMA_DIR                = DMA_DIR_MemoryToPeripheral;	// Transmisja Pamiec -> Peryferium
  DMA_INIT.DMA_BufferSize         = 32;			//SIZE_TAB;	// Rozmiar bufora
  DMA_INIT.DMA_PeripheralInc      = DMA_PeripheralInc_Disable; // Wylaczenie inkrementacji adresu peryferium
  DMA_INIT.DMA_MemoryInc          = DMA_MemoryInc_Enable;	// Wlaczenie inkrementacji adresu pamieci
  DMA_INIT.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;	// 16-bit dana
  DMA_INIT.DMA_MemoryDataSize     = DMA_MemoryDataSize_HalfWord;		// 16-bit dana
  DMA_INIT.DMA_Mode               = DMA_Mode_Circular;	// Petla while dla bufora
  DMA_INIT.DMA_Priority           = DMA_Priority_High;	// Wysoki priorytet
  DMA_INIT.DMA_FIFOMode           = DMA_FIFOMode_Disable;   // Wylaczenie FIFO      
  // DMA_INIT.DMA_FIFOThreshold      = DMA_FIFOThreshold_HalfFull;
  // DMA_INIT.DMA_MemoryBurst        = DMA_MemoryBurst_Single;
  // DMA_INIT.DMA_PeripheralBurst    = DMA_PeripheralBurst_Single;
  DMA_Init(DMA1_Stream5, &DMA_INIT);

  DMA_Cmd(DMA1_Stream5, ENABLE);
  DAC_Cmd(DAC_Channel_1, ENABLE);
  DAC_DMACmd(DAC_Channel_1, ENABLE);
}
