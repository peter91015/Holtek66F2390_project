#ifndef __LCD__H
#define __LCD__H

#ifndef _HT66F2390_H_
#include "HT66F2390.h"
#endif
#ifndef _UTILS_H
#include "utils.h"
#endif

#define DATA_BUS _pf

#define RS _pd4
#define RW _pd5
#define EN _pd6

void LCD_Cmd(unsigned char data);
void LCD_Reset();
void LCD_Senddata(unsigned char data);
void LCD_Print_Str(char *p);
//void delay_ms(unsigned int del);

#endif