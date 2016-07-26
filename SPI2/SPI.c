#include "SPI.h"

int i;

void SPI_ini(void)
{
	SPI_InitTypeDef SPI_InitStruct;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);

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

	
	for( i =0; i < 100000 ; i++){};

}


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
