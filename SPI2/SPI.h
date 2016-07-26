#ifndef SPI_H
#define SPI_H

#include <stm32f4xx.h>
#include <stm32f4xx_spi.h>
#include "GPIO.h"


void SPI_ini(void);
void SPI_Tx(uint8_t adress, uint8_t data);
uint8_t SPI_Rx(uint8_t adress);



#endif
