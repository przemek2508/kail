#include "stm32f4xx.h"
#include "stm32f4xx_usart.h"
#include "stm32f4xx_sdio.h"

GPIO_InitTypeDef  GPIO_Init_Button;   // Definicja funkcji przycisku
GPIO_InitTypeDef  GPIO_Init_USART;		// .....usart

int l = 0;
int k = 0;
volatile char zmienna[30];
char str[30];


void Delay (__IO uint32_t time); //Deklaracja naszej funkcji opozniajacej
extern __IO uint32_t TimeDelay; //Zmienna volatile (__IO)
//volatile uint16_t zmienna=0;
uint16_t i=0;

__IO uint32_t TimeDelay;

void SysTick_Handler(void)
{
	if (TimeDelay!=0){
	TimeDelay--;
	}
}

void SendStr(char* str_p){

	while(str_p[i] !=0){
		while(USART_GetFlagStatus(USART2, USART_FLAG_TC)==RESET){}
		USART_SendData(USART2, str_p[i]);
		i++;
	}}

void inicializacia_GPIO (void)
{
 SystemInit();
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);		//Port A wlaczony
	
	GPIO_Init_Button.GPIO_Pin = GPIO_Pin_0;
	GPIO_Init_Button.GPIO_Mode = GPIO_Mode_IN;		//wejscie
	GPIO_Init_Button.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_Button.GPIO_Speed = GPIO_Speed_2MHz;
	GPIO_Init_Button.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_Init_Button);
}


void USART_ini(void)
{
	GPIO_InitTypeDef  GPIO_Init_USART;
	USART_InitTypeDef USART_Init_User;
	
	SystemInit();
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	
	GPIO_Init_USART.GPIO_Pin = GPIO_Pin_2 | GPIO_Pin_3;
	GPIO_Init_USART.GPIO_Mode = GPIO_Mode_AF;
	GPIO_Init_USART.GPIO_OType = GPIO_OType_PP;
	GPIO_Init_USART.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init_USART.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOA, &GPIO_Init_USART);
	
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource2, GPIO_AF_USART2);
	GPIO_PinAFConfig(GPIOA, GPIO_PinSource3, GPIO_AF_USART2);
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
	
	USART_Init_User.USART_BaudRate=9600;
	USART_Init_User.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_Init_User.USART_Mode=USART_Mode_Tx | USART_Mode_Rx;
	USART_Init_User.USART_Parity=USART_Parity_No;
	USART_Init_User.USART_StopBits=USART_StopBits_1;
	USART_Init_User.USART_WordLength=USART_WordLength_8b;
	
	USART_Init(USART2, &USART_Init_User);
	USART_Cmd(USART2, ENABLE);
}

void NVIC_USART2_ini(void)
{
	NVIC_InitTypeDef NVIC_USART_InitStruct;
	
	NVIC_USART_InitStruct.NVIC_IRQChannel=USART2_IRQn;
	NVIC_USART_InitStruct.NVIC_IRQChannelCmd=ENABLE;
	NVIC_USART_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
	NVIC_USART_InitStruct.NVIC_IRQChannelSubPriority=0;
	
	NVIC_Init(&NVIC_USART_InitStruct);
}



int main(void){
	//inicjalizacja peryferiow
	SysTick_Config(SystemCoreClock/1000);
	USART_ini();
	NVIC_USART2_ini();
	for (l=0; l<=29; l++)
	{
		zmienna[l]=0;
		str[l]=0;
	}
	sprintf(str,"Elo Przemek\n");
	Delay(500);
	SendStr(str); 
	USART_SendData(USART2, i++);
	
	while(1){

		
			
			
	/*while((USART2->SR&USART_SR_RXNE)==0){};
	zmienna[k] = USART_ReceiveData(USART2);
	k++;
		if(k==29){k=0;}
	*/
	} 
	}

void Delay (__IO uint32_t time){
	TimeDelay=time;
	while (TimeDelay!=0){
	}
}

