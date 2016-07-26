/**
 *	Keil project example for HD44780 LCD driver
 *
 *	@author 	Tilen Majerle
 *	@email		tilen@majerle.eu
 *	@website	http://stm32f4-discovery.com
 *	@ide		Keil uVision 5
 */
#include "defines.h"
#include "stm32f4xx.h"
#include "tm_stm32f4_delay.h"
#include "tm_stm32f4_hd44780.h"
int i;
int j=0;
int k=0;
int x = 500;
int main(void) {
	//Rectangle for custom character
    //xxx means doesn't care, lower 5 bits are important for LCD
    uint8_t customChar[] = {
      0x10, // 10000
			0x8,  // 01000
			0x4,  // 00100
			0x2,  // 00010
			0x4,  // 00100
			0x8,  // 01000
			0x10, // 10000
    };
		
		uint8_t customChar1[] = {
      0x1, // 00001
			0x2,  // 00010
			0x4,  // 00100
			0x8,  // 01000
			0x4,  // 00100
			0x2,  // 00010
			0x1, // 00001
    };
	//Initialize system
	SystemInit();
	
	//Initialize LCD 16 cols x 2 rows
	TM_HD44780_Init(16, 2);
	
//Save custom character on location 0 in LCD
    TM_HD44780_CreateChar(0, &customChar[0]);
		TM_HD44780_CreateChar(1, &customChar1[0]);
		TM_HD44780_PutCustom(0, 0, 0);
		TM_HD44780_PutCustom(0, 1, 1);
		Delayms(2000);
		

		
	//Put string to LCD
	TM_HD44780_Puts(0, 0, "STM32F4 Discovery");


	//Wait a little
	Delayms(1000);

	//Show cursor
	TM_HD44780_CursorOff();
	
	//Clear LCD
	TM_HD44780_Clear();
	

	
	//Write new text
	TM_HD44780_Puts(6, 0, "CLEARED!");

	for (i= 1; i<=5; i++) {
	TM_HD44780_ScrollLeft();
		Delayms(x);
		if (i==5) TM_HD44780_PutCustom(5, 0, 0);
}
			Delayms(x);
	TM_HD44780_Puts(0, 0, " ");
		
	while (1) {

for (j; j<=6; j++) {
	TM_HD44780_ScrollRight();
		Delayms(x);
	if (j==6) TM_HD44780_PutCustom(14, 0, 1);
}
		Delayms(x);

		
for (k; k<=6; k++) {
	TM_HD44780_ScrollLeft();
		Delayms(x); 
		if (k==5) TM_HD44780_PutCustom(1, 0, 0);
}
			Delayms(x);
	}
	j=j-5;
	k=k-5;
	j++;
	k++;
}