#include "LCD.h"



void LCD_Cmd(unsigned char data)
{
	DATA_BUS = data;
	RS = 0;
	RW = 0;
	EN = 1;
	delay_ms(3);
	EN = 0;
}
void LCD_Reset()
{
	LCD_Cmd(0x38);
	LCD_Cmd(0x0c);
	LCD_Cmd(0x06);
	LCD_Cmd(0x01);
	LCD_Cmd(0x02);
}
void LCD_Senddata(unsigned char data)
{
	DATA_BUS = data;
	RS = 1;
	RW = 0;
	EN = 1;
	delay_ms(3);
	EN = 0;
}

void LCD_Print_Str(char *p)
{
	while(*p)
		LCD_Senddata(*p++);
}
//void delay_ms(unsigned int del)
//{
//	 unsigned int i;
//	 for (i=0;i<del;i++)
//	 	GCC_DELAY(2000);
//}