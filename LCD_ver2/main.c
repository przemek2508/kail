#include <stdbool.h>
#include <stm32f4xx.h>
#include "stm32f4_delay.h"
#include "hd44780.h"


#define UDG	0

int main(void)
{

	
	hd44780_init(GPIOE, GPIO_Pin_7, GPIO_Pin_8, GPIO_Pin_9, GPIO_Pin_10,
			GPIO_Pin_11, GPIO_Pin_12, GPIO_Pin_13, HD44780_LINES_2,
			HD44780_FONT_5x8);

	hd44780_init_brightness();
	hd44780_brightness(85);
	hd44780_init_contrast();
	hd44780_contrast(50);

	hd44780_position(0, 1);
	hd44780_print("Hello World! ");
	hd44780_put(UDG);
	hd44780_display(true, false, false);
  while (1)
  {

		
	}
}
