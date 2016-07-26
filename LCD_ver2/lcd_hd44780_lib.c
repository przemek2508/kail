//******************************************************************************
//    THE SOFTWARE INCLUDED IN THIS FILE IS FOR GUIDANCE ONLY.
//    AUTHOR SHALL NOT BE HELD LIABLE FOR ANY DIRECT, INDIRECT
//    OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
//    FROM USE OF THIS SOFTWARE.
//
//    PROGRAM ZAWARTY W TYM PLIKU PRZEZNACZONY JEST WYLACZNIE
//    DO CELOW SZKOLENIOWYCH. AUTOR NIE PONOSI ODPOWIEDZIALNOSCI
//    ZA ZADNE EWENTUALNE, BEZPOSREDNIE I POSREDNIE SZKODY
//    WYNIKLE Z JEGO WYKORZYSTANIA.
//******************************************************************************

//##############################################################################
// lcd_hd44780.c
// Dopasowane do zestawu uruchomieniowego STM32F0DISCOVERY by Mesho
// 
// Zajrzyj na: atmegan.blogspot.com
//##############################################################################


#include "lcd_hd44780_lib.h"
#include "stm32f4xx_gpio.h"
//#include <stdio.h>
//#include <stdlib.h>

GPIO_InitTypeDef GPIO_IntStructure;

//-----------------------------------------------------------------------------
void lcd_writenibble(unsigned char nibbleToWrite)
{
  GPIO_WriteBit(LCD_GPIO, LCD_EN, Bit_SET);
  GPIO_WriteBit(LCD_GPIO, LCD_D4, (nibbleToWrite & 0x01));
  GPIO_WriteBit(LCD_GPIO, LCD_D5, (nibbleToWrite & 0x02));
  GPIO_WriteBit(LCD_GPIO, LCD_D6, (nibbleToWrite & 0x04));
  GPIO_WriteBit(LCD_GPIO, LCD_D7, (nibbleToWrite & 0x08));
  GPIO_WriteBit(LCD_GPIO, LCD_EN, Bit_RESET);
}


//-----------------------------------------------------------------------------
unsigned char LCD_ReadNibble(void)
{
  unsigned char tmp = 0;
  GPIO_WriteBit(LCD_GPIO, LCD_EN, Bit_SET);
  tmp |= (GPIO_ReadInputDataBit(LCD_GPIO, LCD_D4) << 0);
  tmp |= (GPIO_ReadInputDataBit(LCD_GPIO, LCD_D5) << 1);
  tmp |= (GPIO_ReadInputDataBit(LCD_GPIO, LCD_D6) << 2);
  tmp |= (GPIO_ReadInputDataBit(LCD_GPIO, LCD_D7) << 3);
  GPIO_WriteBit(LCD_GPIO, LCD_EN, Bit_RESET);
  return tmp;
}


//-----------------------------------------------------------------------------
unsigned char LCD_ReadStatus(void)
{
  unsigned char status = 0;
  
    GPIO_IntStructure.GPIO_Pin   =  LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7;
    GPIO_IntStructure.GPIO_Mode  =  GPIO_Mode_IN;
    GPIO_IntStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(LCD_GPIO, &GPIO_IntStructure);
     
    GPIO_WriteBit(LCD_GPIO, LCD_RW, Bit_SET);
    GPIO_WriteBit(LCD_GPIO, LCD_RS, Bit_RESET);
     
    status |= (LCD_ReadNibble() << 4);
    status |= LCD_ReadNibble();
     
    GPIO_IntStructure.GPIO_Pin   =  LCD_D4 | LCD_D5 | LCD_D6 | LCD_D7;
    GPIO_IntStructure.GPIO_Mode = GPIO_Mode_OUT;
    GPIO_IntStructure.GPIO_OType = GPIO_OType_PP;
    GPIO_Init(LCD_GPIO, &GPIO_IntStructure);
  
  return status;
}


//-----------------------------------------------------------------------------
void lcd_writedata(unsigned char dataToWrite)
{
  GPIO_WriteBit(LCD_GPIO, LCD_RW, Bit_RESET);
  GPIO_WriteBit(LCD_GPIO, LCD_RS, Bit_SET);
  
  lcd_writenibble(dataToWrite >> 4);
  lcd_writenibble(dataToWrite & 0x0F);
  
  while(LCD_ReadStatus() & 0x80);
}


//-----------------------------------------------------------------------------
void lcd_writecommand(unsigned char commandToWrite)
{
  GPIO_WriteBit(LCD_GPIO, LCD_RW | LCD_RS, Bit_RESET);
  lcd_writenibble(commandToWrite >> 4);
  lcd_writenibble(commandToWrite & 0x0F);
  
  while(LCD_ReadStatus() & 0x80);
}


//-----------------------------------------------------------------------------
void lcd_str(unsigned char * text)
{
  while(*text)
    lcd_writedata(*text++);
}


//-----------------------------------------------------------------------------
void lcd_locate(unsigned char x, unsigned char y)
{
  lcd_writecommand(HD44780_DDRAM_SET | (x + (0x40 * y)));
}


//-----------------------------------------------------------------------------
void lcd_strxy(unsigned char * text, unsigned char x, unsigned char y)
{
  lcd_locate(x,y);
  while(*text)
    lcd_writedata(*text++);
}


//-----------------------------------------------------------------------------
void lcd_writebinary(unsigned int var, unsigned char bitCount)
{
  signed char i;
  
  for(i = (bitCount - 1); i >= 0; i--)
     {
     lcd_writedata((var & (1 << i))?'1':'0');
     }
}


//-----------------------------------------------------------------------------
void LCD_ShiftLeft(void)
{
  lcd_writecommand(HD44780_DISPLAY_CURSOR_SHIFT | HD44780_SHIFT_LEFT | HD44780_SHIFT_DISPLAY);
}


//-----------------------------------------------------------------------------
void LCD_ShiftRight(void)
{
  lcd_writecommand(HD44780_DISPLAY_CURSOR_SHIFT | HD44780_SHIFT_RIGHT | HD44780_SHIFT_DISPLAY);
}


//-----------------------------------------------------------------------------
void lcd_init(void)
{
  volatile unsigned char i = 0;
  volatile unsigned int delayCnt = 0;
	RCC_AHB1PeriphClockCmd(LCD_CLK_LINE, ENABLE);
  GPIO_IntStructure.GPIO_Pin = LCD_D4|LCD_D5|LCD_D6|LCD_D7|LCD_RS|LCD_RW|LCD_EN;
  GPIO_IntStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_IntStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_IntStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_IntStructure.GPIO_Mode = GPIO_Mode_OUT; 
  
  GPIO_Init(LCD_GPIO, &GPIO_IntStructure);
  
  GPIO_ResetBits(LCD_GPIO, LCD_RS | LCD_EN | LCD_RW);
  
  for(delayCnt = 0; delayCnt < 300000; delayCnt++);
  
  for(i = 0; i < 3; i++) {
    lcd_writenibble(0x03);            
    for(delayCnt = 0; delayCnt < 30000; delayCnt++);
  }
  
  lcd_writenibble(0x02);             
  
  for(delayCnt = 0; delayCnt < 6000; delayCnt++);
     
  lcd_writecommand(HD44780_FUNCTION_SET | 
                   HD44780_FONT5x7 | 
                   HD44780_TWO_LINE | 
                   HD44780_4_BIT);
  
  lcd_writecommand(HD44780_DISPLAY_ONOFF | 
                   HD44780_DISPLAY_OFF); 
  
  lcd_writecommand(HD44780_CLEAR); 
  
  lcd_writecommand(HD44780_ENTRY_MODE | 
                   HD44780_EM_SHIFT_CURSOR | 
                   HD44780_EM_INCREMENT);
  
  lcd_writecommand(HD44780_DISPLAY_ONOFF | 
                   HD44780_DISPLAY_ON |
                   HD44780_CURSOR_OFF | 
                   HD44780_CURSOR_NOBLINK);
}


//-----------------------------------------------------------------------------
void lcd_addchar (unsigned char chrNum, unsigned char n, const unsigned char *p)
{         //chrNum  - character number (code) to be registered (0..7)
          //n       - number of characters to register
          //*p      - pointer to the character pattern (8 * n bytes)
	lcd_writecommand(HD44780_CGRAM_SET | chrNum * 8);
	n *= 8;
	do
		lcd_writedata(*p++);
	while (--n);
}


//-----------------------------------------------------------------------------
void lcd_cls(void){
	lcd_writecommand(HD44780_CLEAR);
}



unsigned char* intToStr(int n) //prymitywny przetwornik int to string
	{
     int i = 0;
     char *tmp = (char*)malloc(12); // stdlib
     char *ret = (char*)malloc(12);
     if(n < 0) {
          *ret = '-';
          i++;
          n = -n;
     }
     do {
          *tmp = n % 10 + 48;
          n -= n % 10;
          if(n > 9) *tmp++;
     }
     while(n /= 10);
     while(ret[i++] = *tmp--);
     return ret;
}

void lcd_int(int n){
	
	lcd_str(intToStr(n));
}

void lcd_intxy(int n, unsigned char x, unsigned char y){
	lcd_locate(x,y);
	lcd_str(intToStr(n));
}