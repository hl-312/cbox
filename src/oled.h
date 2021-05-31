#ifndef OLED_H_
#define OLED_H_
#include <REG52.H>
#include <INTRINS.H>
//引脚声明
sbit SCL = P2^1;
sbit SDA = P2^2;
//常量声明
#define IIC_CMD 0
#define IIC_DATA 1
//符号定义
#define u8 unsigned char //一字节的无符号字符整数 0~255
#define u16 unsigned int //两字节的无符号整型整数 0~65535
#define u32 unsigned int //三字节的无符号整型整数 0~16777215
//简单函数定义
#define SCL_S() SCL = 1 //SCL Set
#define SDA_S() SDA = 1 //SDA Set
#define SCL_C() SCL = 0 //SCL Clear
#define SDA_C() SDA = 0 //SCL Clear
//延时函数声明
void OLED_delay(u8 n);
//IIC 协议函数声明
void IIC_Start(void);
void IIC_Stop(void);
void IIC_WaitAck(void);
void IIC_SendByte(u8 byte);
//OLED 控制函数声明
void OLED_Send(u8 byte, u8 mode);
void OLED_Reset(void);
void OLED_C(void);
void OLED_SegSA(void);//设置水平寻址模式，适合一帧写入
void OLED_Pos(u8 x, u8 y);
void OLED_ShowChar(u8 x, u8 y, u8 chr, u8 size); //显示字符
void OLED_ShowStr(u8 x, u8 y, u8 *str, u8 size); //显示字符串
void OLED_ShowCc(u8 x, u8 y, u8 zm);  //显示汉字
#endif