#include <all.h>

unsigned char control_dat=0xff;

void control_lock(void);
void fmq_on(void);//低电平on P06
void fmq_off(void);//高电平off P06
void jdq_on(void);//低电平on P05
void jdq_off(void);

void control_block(void)
{
	P2|=0xa0;
	P2&=0x1f;                   
}

void fmq_off(void)
{
	control_dat&=0xbf;
	CONTROL_PORT=control_dat;
	control_block();
	
}

void fmq_on(void)
{
	control_dat|=~0xbf;
	CONTROL_PORT=control_dat;
	control_block();
	
}

void jdq_off(void)
{
	control_dat&=0xef;
	CONTROL_PORT=control_dat;
	control_block();
	
}

void jdq_on(void)
{
	control_dat|=~0xef;
	CONTROL_PORT=control_dat;
	control_block();
	
}
