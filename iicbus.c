#include <all.h>

//***************************************

void init_pcf8591(void);
unsigned char adc_pcf8591(void);
//***************************************

void init_pcf8591(void)
{
	IIC_Start();
	IIC_SendByte(0x90);
	IIC_WaitAck();
	IIC_SendByte(0x43);
	IIC_WaitAck();
	IIC_Stop();
}

unsigned char adc_pcf8591(void)
{
	unsigned char temp=0;
	IIC_Start();
	IIC_SendByte(0x91);
	IIC_WaitAck();
	temp=IIC_RecByte();
	IIC_Ack(0);
	IIC_Stop();
	
	return temp;
}

//*****************************************
void write_eeprom(unsigned char add,unsigned char val)
{
	unsigned char i;
	IIC_Start();
	IIC_SendByte(0xa0);
	IIC_WaitAck();
	IIC_SendByte(add);
	IIC_WaitAck();
	IIC_SendByte(val);
	IIC_WaitAck();
	IIC_Stop();
	
	for(i=0;i<10;i++)
	{
		_nop_();
	}
	
	
}

unsigned char read_eeprom(unsigned char add)
{
	unsigned char da;
	IIC_Start();
	IIC_SendByte(0xa0);
	IIC_WaitAck();
	IIC_SendByte(add);
	IIC_WaitAck();
	
	IIC_Start();
	IIC_SendByte(0xa1);
	IIC_WaitAck();
	da=IIC_RecByte();
	IIC_Ack(0);
	IIC_Stop();
	
	return da;
}
