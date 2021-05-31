#ifndef _KEY_H_
#define _KEY_H_
#define u8 unsigned char
#define u16 unsigned int

#include <REG52.H>

//键盘状态字：keyx[状态，次数];key_status[key0,key1,key2,key3]
sbit key0 = P3^2;
sbit key1 = P3^3;
sbit key2 = P3^4;


void Delay10ms();		//@11.0592MHz
void key_scan(char *key_status);
#endif