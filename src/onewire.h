#ifndef _ONEWIRE_H_
#define _ONEWIRE_H_
#include <REG52.H>

//总线状态字
sbit DQ = P2^7;



#define u8 unsigned char
#define u16 unsigned int

//基本函数声明
void Delay_OneWire(u16 t);
bit Init_DS18B20(void);
void Write_DS18B20(u8 dat);
u8 Read_DS18B20(void);
void temperature(char *temp_H);
void tempstatus(char *temp_D, char *temp_H);

#endif