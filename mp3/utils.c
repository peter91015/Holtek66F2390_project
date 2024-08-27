#include "utils.h"
static char test = 0;
unsigned char getkey(unsigned char k)
{
	unsigned char tmp1, tmp2;
	tmp1 = key_port&0x0f;
	//delay_ms(10);
	if (tmp1 != 0x0f){
		if (test)
			return k;
		tmp2 = key_port;
		test = 1;
			return (tmp1==tmp2)? tmp2 & 0x0f: k;
	}
	else
		test = 0;
	return k;
}
void delay_ms(unsigned int del)
{
	 unsigned int i;
	 for (i=0;i<del;i++)
	 	GCC_DELAY(2000);
}

unsigned char key_hold = 0x0f, key_hold2 = 0x0f;
char hold = 0, hold_3 = 0;
unsigned char getkey2(unsigned char raw_key)
{
	unsigned char key_in = raw_key, key = 0x0f;
	if (key_hold == 0x0f){
		key = 0x0f;
		hold = 0;
		key_hold = key_in;
	}
	else if (key_in == key_hold){
		if (!hold){
			hold = 1;
			key = key_hold;
		}
		else {
			key = 0x0f;
		}
				//key = (key_in == key_hold)? key_hold: 0x0f;
	}
	else {
		key_hold = key_in;
		key = 0x0f;
	}
	
	return key;
}

unsigned hold_times = 0;
unsigned char getkey3(unsigned char raw_key)//hold_key
{
	unsigned char key_in = raw_key; unsigned char key = 0x0f;
	if (key_in != 0x0f){
		if (!hold_3){
			hold_3 = 1;
			hold_times = 0;
			key_hold2 = key_in;
		}
		else if (hold_times == 50){
			return (key_in << 4|0);
		}
		else if (hold_times == 0){
			if (key_hold2 != key_in){
				hold_3 = 0;
				hold_times = 0;
			}
			else 
				hold_times++;
		}
		else			
			hold_times = hold_times>50? hold_times:hold_times+1;		
	}
	else {
		if (hold_3 && hold_times < 50){
			hold_3 = 0;
			hold_times = 0;
			return key_hold2;
		}
		else {
			hold_3 = 0;
			hold_times = 0;
		}
		
	}
	return 0x0f;
}
unsigned key_hold4 = 0x0f, hold_4 = 0, hold_times_4 = 0;
unsigned char getkey4(unsigned raw_key)
{
	static unsigned release_count = 0;
	unsigned char key_in = raw_key;
	if (key_in != 0x0f){
		if (!hold_4){
			hold_4 = 1;
			hold_times_4 = 0;
			key_hold4 = key_in;
		}
		else if (hold_4 == 2){
			if (key_hold4 != key_in)
				return 0x0f;
			else
				hold_4 = 3;
		}
		else if (hold_4 == 3){
			hold_4 = 0;
			return key_hold4 << 5; 
		}
		else if (hold_times_4 == 50){
			return (key_in << 4|0);
		}
		else if (hold_times_4 == 0){
			if (key_hold4 != key_in){
				hold_4 = 0;
				hold_times_4 = 0;
			}
			else 
				hold_times_4++;
		}
		else			
			hold_times_4 = hold_times_4>50? hold_times_4:hold_times_4+1;	
	}
	else {
		if (hold_4 == 1 && hold_times_4 < 50){
			hold_4 = 2;
			hold_times_4 = 0;
			release_count = 0;
			//return key_hold2;
		}
		else if (hold_4 == 2){
			if (++release_count >5){
				hold_4 = 0;
				return key_hold4;
			}
		}
		else {
			hold_4 = 0;
			hold_times_4 = 0;
		}
		
	}
	return 0x0f;
}