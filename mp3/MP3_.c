#include "HT66F2390.h"

const unsigned char Table1[] = "YDA168electronic";
const unsigned char Table2[] = "20240101 YTCheng";
const unsigned char *Table3 = "YDA168 ELE test";
const unsigned char num[] = "0123456789";
const unsigned char *Table10 = "    Voice Up.    ";
const unsigned char *Table11 = "  Voice Down.    ";
const unsigned char *Table12 = "    Next One.    ";
const unsigned char *Table13 = "    Prei One.    ";

#define DATA_BUS _pf
#define RS _pd4
#define RW _pd5
#define EN _pd6

void LCD_Reset(void);
void LCD_Cmd(unsigned char data);
void LCD_Senddata(unsigned char data);
void LCD_Print_Str(char *p);
void delay_ms(unsigned int del);

void UART_Putch(char UART_DATA);
char UART_Getch();
volatile unsigned char RxData[32]={0x20};
volatile unsigned char RxDataLN=0;
volatile bit fgRx=0;
unsigned char Command_line[10]={0};

//MP3 Player �w�q�Ѽƪ�
#define Start_Byte 0x7E
#define Version_Byte 0xFF
#define Command_Length 0x06
#define End_Byte 0xEF
#define Acknowledge 0x00  //Returns info with command 0x41 [0x01: info, 0x00: no info]

#define ACTIVATED LOW
//�Ƶ{��
void playFirst();
void pause();
void play();
void playNext();
void playPrevious();
void voiceup();
void voicedown();
void setVolume(int volume);
void execute_CMD(unsigned char CMD, unsigned char Par1, unsigned char Par2);

unsigned int i = 200; 
volatile unsigned char T500ms_cnt=200,T100ms_cnt=40;	//200 * 2.5mS = 500mS
volatile unsigned char T250ms_cnt=100,T20ms_cnt=4;	//200 * 2.5mS = 500mS
volatile unsigned int T1s_cnt=400;	//200 * 2.5mS = 500mS
volatile bit T250ms_flag=0,T500ms_flag=0,T100ms_flag=0,T1s_flag=0;	//200 * 2.5mS = 500mS
volatile bit flash = 0;


void main()
{
	_wdtc=0b10101111;							//�����ݪ����p�ɾ�
	unsigned char i;
//***LCD �}�쪬�A�]�w
	_pfc = 0x00;
	_pdc4 = 0;
	_pdc5 = 0;
	_pdc6 = 0;	
//***
//***UART�ѼƳ]�w
	_pas1=0b11110000;							//�]�mTX0->PA7 RX0->PA6
	_u0cr1=0b10000000;							//UARTEN0/8-Bit/No_parity//1 Stop Bit///
	_u0cr2=0b11100100;							//TXEN0/RXEN0/BRGH0/RIE0//		
//UnCR2 ��BRGHn �M�w BaudRate �έ��@�Ӥ���
//BaudRate = fsys / [64*(N+1)] => N = [fsys/(BaudRate*64)]-1
//BaudRate = fsys / [16*(N+1)] => N = [fsys/(BaudRate*16)]-1
	_brg0=51;		//BRGH0=1
	_mf5e=1; _ur0e=1;							//�P��UART0���_
//***�ɶ����_�]�w
	_stm0c0 = 0x00;
	_stm0c1 = 0xc1;//0b11000001;
	_stm0ah = 10000/256;
	_stm0al = 10000%256;
	_mf0e = 1;	_stm0ae = 1;	
	
	_emi=1;										//�P���`���_EMI
	
	LCD_Reset();
	delay_ms(1);
	LCD_Cmd(0x80);
	delay_ms(1);
	for(i=0;i<16;i++)
		LCD_Senddata(Table1[i]);
		
	LCD_Cmd(0xc0);
	delay_ms(1);
	for(i=0;i<16;i++)
		LCD_Senddata(Table2[i]);
	delay_ms(3000);
	
	LCD_Cmd(0x01); //�M����ܹ�
	delay_ms(1);
	LCD_Cmd(0x80);
	LCD_Print_Str(Table3);
	LCD_Cmd(0xC0);
	
	playFirst();
	delay_ms(2000);
	play();
	delay_ms(2000);
	playNext();
	_st0on = 1;		//
	while(1)
	{
	
	}
}
DEFINE_ISR(ISR_STM0,0x14)	//2.5ms
{ 
	if(--T100ms_cnt==0)
	{
		T100ms_cnt=40;
		T100ms_flag=1;
	}
	if(--T250ms_cnt==0)
	{
		T250ms_cnt=100;
		T250ms_flag=1;
	}
	if(--T500ms_cnt==0)
	{
		T500ms_cnt=200;
		T500ms_flag=1;
	}
	if(--T1s_cnt==0)
	{
		T1s_cnt=400;
		T1s_flag=1;
	}
	if(--T20ms_cnt==0)
	{
		T20ms_cnt = 8;

	}
	_stm0af = 0;
}

DEFINE_ISR(UART0,0x3C)
{	
	RxData[RxDataLN++]=_txr_rxr0;	//���o�������
	if(_txr_rxr0 == '=')
	{
		fgRx=1;										//�]�m�����X��
		RxData[RxDataLN] ='\0';
	}
	_ur0f=0;									//�M��UR0F�X��(�@�ɫ�)	
}
void playFirst()
{
	setVolume(15);  						//�]�w���q
  	delay_ms(500);
}
void pause()
{
	execute_CMD(0x0E,0,0); 
    delay_ms(500);
}
void play()
{
	execute_CMD(0x0D,0,0);  
	delay_ms(500);
}
void playNext()
{
  execute_CMD(0x01,0,1);  
	delay_ms(500);
}

void playPrevious()
{
	execute_CMD(0x02,0,1);  
	delay_ms(500);
}

void voiceup()
{
	execute_CMD(0x04,0,1);  
	delay_ms(500);
}

void voicedown()
{
	execute_CMD(0x05,0,1); 
	delay_ms(500);
}

void setVolume(int volume)
{
  execute_CMD(0x06, 0, volume); // Set the volume (0x00~0x30)
  delay_ms(500);
}
// ������O�P�N���O�ǰe��mp3�Ҳ�
void execute_CMD(unsigned char CMD, unsigned char Par1, unsigned char Par2)
{
	unsigned char k;
    int checksum = 0;
	
	Command_line[0] = Start_Byte;
	Command_line[1] = Version_Byte;
	Command_line[2] = Command_Length;
	Command_line[3] = CMD;
	Command_line[4] = Acknowledge;
	Command_line[5] = Par1;
	Command_line[6] = Par2;
//	Command_line[7] = End_Byte;	//* ���echecksum ����EndByte�]�i�H����
//	�ݴ���
	for(k=1; k<=6; k++)
	{
		checksum = checksum + Command_line[k];
	}	
	checksum = 0xffff - checksum + 1; // 2's complement
//	checksum = 0 - checksum ; // 2's complement
	//
	Command_line[7] = checksum >> 8;
	Command_line[8] = checksum ;
	Command_line[9] = End_Byte;

  	for (k=0; k<10; k++)
	{
    	UART_Putch(Command_line[k]);
  	}
}
void UART_Putch(char UART_DATA)
{  
	_txr_rxr0 = UART_DATA;	//�N�ݵo�e����x�s��UART buffer��
	while( _txif0 == 0 ) ;  //�Y_txif0=0��ܥ��o�g�����A�A�~���ˬd 
							//���ݵo�e���� 
							                    
}
char UART_Getch()
{  
	char UART_DATA;
	while( _rxif0 == 0 ) ;  //�Y_rxif0=0��ܥ��o�g�����A�A�~���ˬd 
							//���ݱ�������
	UART_DATA = _txr_rxr0;	//�N�ݵo�e����x�s��UART buffer��						
	return UART_DATA;                       
}
void LCD_Reset() //LCD���ҩl�{��
{
	//DL=1�G8bit�ǿ�,N=1�G���2��,F=0�G5*7�r��
	LCD_Cmd(0x38);
	//D=1�G��ܹ�ON,C=0�G����ܴ��,B=0�G��Ф��{�{
	LCD_Cmd(0x0c);
	LCD_Cmd(0x06); //I/D=1�G��ܧ���Хk��,S=0�G��в���T��
	LCD_Cmd(0x01); //�M����ܹ�
	LCD_Cmd(0x02); //��Ц^���
}
void LCD_Print_Str(char *p)
{
	while(*p)
		LCD_Senddata(*p++);
}
//�ǰe��ƨ�LCD
void LCD_Senddata(unsigned char data)
{
	DATA_BUS = data; //��ưe��BUS
	RS=1; RW=0; EN=1; //��ƨ�LCD��
	delay_ms(3);
	EN=0; //�T��LCD
}
//�ǰe�R�O��LCD
void LCD_Cmd(unsigned char data)
{
	DATA_BUS = data; //�R�O�e��BUS
	RS=0; RW=0; EN=1; //�R�O��LCD��
	delay_ms(3);
	EN=0; //�T��LCD
}

/*void delay_ms(unsigned int del)					
{	
	unsigned int i;								
	for(i=0;i<del;i++) 
		GCC_DELAY(2000);
}*/