#include "stm32f4xx.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_spi.h"
int8_t x,y;
int i;

GPIO_InitTypeDef GPIO_InitStruct;
SPI_InitTypeDef SPI_InitStruct;
 
//Tx SPI param: adress, data
void SPI_Tx(uint8_t adress, uint8_t data)
{
  GPIO_ResetBits(GPIOE,GPIO_Pin_3);
  while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE));
  SPI_I2S_SendData(SPI1,adress);
  while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE));
  SPI_I2S_ReceiveData(SPI1);
  while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE));
  SPI_I2S_SendData(SPI1,data);
  while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE));
  SPI_I2S_ReceiveData(SPI1);
  GPIO_SetBits(GPIOE,GPIO_Pin_3);
   
}
 
//Rx SPI param: adress, return data
 uint8_t SPI_Rx(uint8_t adress)
{
  GPIO_ResetBits(GPIOE,GPIO_Pin_3);
  adress=0x80|adress;
  while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE));
  SPI_I2S_SendData(SPI1,adress);
  while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE));
  SPI_I2S_ReceiveData(SPI1);
  while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE));
  SPI_I2S_SendData(SPI1,0x00);
  while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE));
   
  GPIO_SetBits(GPIOE,GPIO_Pin_3);
  return SPI_I2S_ReceiveData(SPI1);
}
 
int main()
{
RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA|RCC_AHB1Periph_GPIOE|RCC_AHB1Periph_GPIOD, ENABLE);
RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
 

GPIO_InitStruct.GPIO_Pin=GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
GPIO_InitStruct.GPIO_Mode=GPIO_Mode_AF;
GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
GPIO_Init(GPIOA, &GPIO_InitStruct);
 
GPIO_InitStruct.GPIO_Pin=GPIO_Pin_3;
GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
GPIO_Init(GPIOE, &GPIO_InitStruct);
 
GPIO_InitStruct.GPIO_Pin=GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14|GPIO_Pin_15;
GPIO_InitStruct.GPIO_Mode=GPIO_Mode_OUT;
GPIO_InitStruct.GPIO_OType=GPIO_OType_PP;
GPIO_Init(GPIOD, &GPIO_InitStruct);
 
GPIO_PinAFConfig(GPIOA,GPIO_PinSource5,GPIO_AF_SPI1);
GPIO_PinAFConfig(GPIOA,GPIO_PinSource6,GPIO_AF_SPI1);
GPIO_PinAFConfig(GPIOA,GPIO_PinSource7,GPIO_AF_SPI1);
 

SPI_InitStruct.SPI_BaudRatePrescaler=SPI_BaudRatePrescaler_2;
SPI_InitStruct.SPI_Direction=SPI_Direction_2Lines_FullDuplex;
SPI_InitStruct.SPI_Mode=SPI_Mode_Master;
SPI_InitStruct.SPI_DataSize=SPI_DataSize_8b;
SPI_InitStruct.SPI_FirstBit=SPI_FirstBit_MSB;
SPI_InitStruct.SPI_CPOL=SPI_CPOL_High;
SPI_InitStruct.SPI_CPHA=SPI_CPHA_2Edge;
SPI_InitStruct.SPI_NSS=SPI_NSS_Soft|SPI_NSSInternalSoft_Set;
SPI_Init(SPI1,&SPI_InitStruct);
 
 
GPIO_SetBits(GPIOE,GPIO_Pin_3);
SPI_Cmd(SPI1,ENABLE);
 
 
for(i=0;i<1000000;i++);
 
//Tx SPI param1, param2, ...
SPI_Tx(0x20,0x67);
SPI_Tx(0x24,0x48);

while(1)
 {
  //Rx SPI data
  x=SPI_Rx(0x29);
  y=SPI_Rx(0x2B);
  //use data
  if (x<-20) GPIO_SetBits(GPIOD,GPIO_Pin_12);
  else GPIO_ResetBits(GPIOD,GPIO_Pin_12);
  if (x>20) GPIO_SetBits(GPIOD,GPIO_Pin_14);
  else GPIO_ResetBits(GPIOD,GPIO_Pin_14);
  if (y<-20) GPIO_SetBits(GPIOD,GPIO_Pin_15);
  else GPIO_ResetBits(GPIOD,GPIO_Pin_15);
  if (y>20) GPIO_SetBits(GPIOD,GPIO_Pin_13);
  else GPIO_ResetBits(GPIOD,GPIO_Pin_13);
 }
}
