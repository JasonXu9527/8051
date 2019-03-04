#include <all.h>
//*************************************************************************************
unsigned char disp_buf[8]={0,0,0,0,0,0,0,0};
unsigned char wei[9]={0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80,0xff};
unsigned char duan[12]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xff};
//*************************************************************************************
void led8_wei_block(void);
void led8_duan_block(void);
void Display_Scan(void);
//*************************************************************************************
void led8_wei_block(void)
{
	P2|=0xc0;
	P2&=0x1f;
}
//**************************************
void led8_duan_block(void)
{
	P2|=0xe0;
	P2&=0x1f;
}
//**************************************
void Display_Scan(void)
{
	static unsigned char displayindex=0;
	LED8_PORT=0x00;
	led8_wei_block();	
	led8_duan_block();
		
	LED8_PORT=duan[disp_buf[displayindex]];
	led8_duan_block();
	
	LED8_PORT=wei[displayindex];
	led8_wei_block();
	
	if(++displayindex==8) displayindex=0;
	
}
