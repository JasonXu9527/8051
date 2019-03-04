#include <all.h>
//****************************************
unsigned char key_code=0;
unsigned char key_state=0;
unsigned char k_tem=0;
unsigned char key_temp=0;
unsigned char key_temp1=0;

unsigned char run_state=1;
unsigned char fmq_warning=1;

unsigned char rh_set;
unsigned char rh_dat=0;

//****************************************
unsigned char get_key(void);
void key_read_mainloop(void);
void key_deal_mainloop(void);

//****************************************
unsigned char get_key(void)
{
	k_tem=0;
	
	if(!KEY_BIN7) k_tem=7;
	if(!KEY_BIN6) k_tem=6;
	if(!KEY_BIN5) k_tem=5;
	if(!KEY_BIN4) k_tem=4;
	return k_tem;
}
//****************************************
void key_read_mainloop(void)
{
	
	if(f_20ms)
	{
		f_20ms=0;
		key_temp=get_key();	
		switch(key_state)
		{
			case 0: if(key_temp) key_state=1;break;
			case 1: if(key_temp) {key_code=key_temp;key_state=2;}
							else key_state=0;
							break;
			case 2: if(!key_temp) key_state=0;break;
			default:break;
		}
	}
}
//*******************************************
void key_deal_mainloop(void)
{
	switch(key_code)
	{
		case 7:
			if(run_state==1)
			{
				run_state=2;
				
			}
			else if(run_state==2)
			{
				run_state=1;
				
			}
			key_code=0;
			break;
		
		case 6:
			if(run_state==1)
			{
				run_state=3;
				rh_set=read_eeprom(0x05);
			}
			else if(run_state==3)
			{
				run_state=1;
				write_eeprom(0x05,rh_set);
			}
			else if(run_state==2)
				fmq_warning=!fmq_warning;
			
			key_code=0;
			
			break;
		case 5:
			if(run_state==2)
				jdq_on();
			else if(rh_set<99&&rh_set>=0&&run_state==3) rh_set++;
			
			key_code=0;
			
			break;
		case 4:
			if(run_state==2)
				jdq_off();
			else if(rh_set>0&&rh_set<=99&&run_state==3) rh_set--;
			
			key_code=0;
			
			break;
		
		default:break;
	}
}
