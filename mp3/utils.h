#ifndef _UTILS_H
#define _UTILS_H

#ifndef _HT66F2390_H_
#include "HT66F2390.h"
#endif
#define key_port _pg
#define key_portc _pgc
void delay_ms(unsigned int del);
unsigned char getkey(unsigned char k);
unsigned char getkey2(unsigned char raw_key);
unsigned char getkey3(unsigned char raw_key);
#endif