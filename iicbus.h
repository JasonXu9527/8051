#ifndef __IICBUS_H__
#define __IICBUS_H__

extern void init_pcf8591(void);
extern unsigned char adc_pcf8591(void);
extern unsigned char read_eeprom(unsigned char add);
extern void write_eeprom(unsigned char add,unsigned char val);

#endif
