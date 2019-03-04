#ifndef __PORT_H__
#define __PORT_H__

#define LED_PORT P0
#define LED8_PORT P0
#define CONTROL_PORT P0

sbit KEY_BIN7 =P3^0;
sbit KEY_BIN6 =P3^1;
sbit KEY_BIN5 =P3^2;
sbit KEY_BIN4 =P3^3;


extern void port_init(void);


#endif
