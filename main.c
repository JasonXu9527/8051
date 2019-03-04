#include <all.h>

//**************************************

unsigned char cnt_5ms=0;
bit f_5ms=0;

unsigned char cnt_20ms=0;
bit f_20ms=0;


unsigned char cnt_200ms=0;
bit f_200ms=0;

unsigned int cnt_500ms=0;
bit f_500ms=0;

unsigned int cnt_1s=0;
bit f_1s=0;

unsigned long temp;
unsigned int adc_value;

//**************************************

void time_flag_loop(void);
void deal_mainloop(void);

//**************************************

void main(void)
{
	
	port_init();
	Timer0Init();
	ET0=1;
	EA=1;	
	disp_buf[0]=11;
	disp_buf[1]=11;
	disp_buf[2]=11;
	disp_buf[3]=11;
	disp_buf[4]=11;
	disp_buf[5]=11;
	disp_buf[6]=11;
	disp_buf[7]=11;
	
	
	

	
	Write_Ds1302(0x8e,0x00);
	Write_Ds1302(0x84,0x08);
	Write_Ds1302(0x82,0x30);
	Write_Ds1302(0x80,0x00);
	Write_Ds1302(0x8e,0x80);
	
	UartInit();
	
	jdq_off();
	
	fmq_off();
	
	led_off(0xff);
	
	init_pcf8591();
	
	adc_pcf8591();
	adc_pcf8591();
	
	rh_set=read_eeprom(0x05);
	if(rh_set<0||rh_set>99)
		write_eeprom(0x05,50);
	
	
	while(1)
	{
		
		time_flag_loop();
		key_read_mainloop();
		key_deal_mainloop();
		deal_mainloop();
		
	}
	
}



//**************************************
void time_flag_loop(void)
{
	if(f_1ms)
	{
		f_1ms=0;
		Display_Scan();
		if(++cnt_5ms==5)
		{
			f_5ms=1;
			cnt_5ms=0;
		}
		
		if(++cnt_20ms==20)
		{
			f_20ms=1;
			cnt_20ms=0;
		}
		
		if(++cnt_200ms==200)
		{
			f_200ms=1;
			cnt_200ms=0;
		}
		if(++cnt_500ms==500)
		{
			f_500ms=1;
			cnt_500ms=0;
		}
		if(++cnt_1s==1000)
		{
			f_1s=1;
			cnt_1s=0;
		}
	}
}
//***********************************
void deal_mainloop(void)
{
	
	if(f_5ms)
		{
			f_5ms=0;
			
			Display_Scan();
			
			if(run_state==3)
			{
				disp_buf[0]=10;
				disp_buf[1]=10;
				disp_buf[2]=11;
				disp_buf[3]=11;
				disp_buf[4]=11;
				disp_buf[5]=11;
				disp_buf[6]=rh_set/10;
				disp_buf[7]=rh_set%10;
			}
			else
			{
				temp=Read_Ds1302(0x85);
				disp_buf[0]=(temp>>4);
				disp_buf[1]=(temp&0x0f);
			
				temp=Read_Ds1302(0x83);
				disp_buf[3]=(temp>>4);
				disp_buf[4]=(temp&0x0f);
				
				adc_value=adc_pcf8591();
				temp=1000*(unsigned long)adc_value/256;
				if(temp%10>4) temp+=10;
					temp=temp/10;
				if(temp>99) temp=99;
				rh_dat=temp;
				disp_buf[6]=temp/10;
				disp_buf[7]=temp%10;
			}
			
		}
			
		switch(run_state)
		{
			case 1:
				fmq_off();
				led_off(0xff);
				led_on(0x01);
				if(rh_set>rh_dat)
					jdq_on();
				else jdq_off();
				
				
				
				break;
			case 2:
				led_off(0xff);
				led_on(0x02);
				if((rh_set>rh_dat)&&fmq_warning)
					fmq_on();
				else fmq_off();
				
				
			case 3:
				
				break;
			default:break;
			
		}
			
		
		if(f_500ms)
		{
			f_500ms=0;
			Uart_send8(run_state);
		}
		
		
}
