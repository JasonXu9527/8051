#include <all.h>
//****************************************

unsigned char led_dat=0;

//****************************************
void led_block(void);
void led_on(unsigned char dis_dat);
void led_off(unsigned char dis_dat);
void led_swap(unsigned char dis_dat);

//****************************************
void led_block(void)
{
	P2|=0x80;
	P2&=0x1f;
}
//****************************************
void led_on(unsigned char dis_dat)
{
	led_dat&=~dis_dat;
	LED_PORT=led_dat;
	led_block();
}
//*****************************************
void led_off(unsigned char dis_dat)
{
	led_dat|=dis_dat;
	LED_PORT=led_dat;
	led_block();
}
//*****************************************
void led_swap(unsigned char dis_dat)
{
	led_dat^=dis_dat;
	LED_PORT=led_dat;
	led_block();
}

