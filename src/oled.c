#include "oled.h"
#include "oledfont.h"
//延时函数

//IIC 协议函数
void IIC_Start(void)
{
    SDA_S();
    SCL_S();
    SDA_C();
    SCL_C();
}

void IIC_Stop(void)
{
    SDA_C();
    SCL_S();
    SDA_S();
    _nop_();
    SCL_C();
}

void IIC_WaitAck(void)
{
    SDA_S();
    SCL_S();
    _nop_();
    SCL_C();
}

void IIC_SendByte(u8 byte)
{
    u8 b, i;
    for (i = 0; i < 8; i++)
    {
        b = byte&0x80;
        if (b==0x80){SDA_S();}
        else SDA_C();
        SCL_S();
        byte<<=1;
        SCL_C();    
    }
}

//OLED 控制函数
void OLED_Send(u8 byte, u8 mode)
{
    u8 da=0;
    IIC_Start();
    IIC_SendByte(0x78);
    IIC_WaitAck();
    if (mode)
    {
        IIC_SendByte(0x40);
    }
    else IIC_SendByte(0x00);
    IIC_WaitAck();
    IIC_SendByte(byte);
    IIC_WaitAck();
    IIC_Stop();
}

void OLED_Pos(u8 x, u8 y)
{
    OLED_Send(0xb0+y,IIC_CMD);
    OLED_Send(x&0x0f,IIC_CMD);
    OLED_Send(((x&0xf0)>>4)|0x10,IIC_CMD);
}

void OLED_ShowChar(u8 x, u8 y, u8 chr, u8 size) //显示字符
{
    u8 i;
    chr=chr-' ';
    OLED_Pos(x,y);
    if(size==6)
    {
        for (i=0;i<6;i++) OLED_Send(S8x6[chr][i],IIC_DATA);
    }
    else if(size==8){
        for (i=0;i<8;i++) OLED_Send(S16x8[chr*16+i],IIC_DATA);
        OLED_Pos(x,y+1);
        for (i=8;i<16;i++) OLED_Send(S16x8[chr*16+i],IIC_DATA);
    }
}

void OLED_ShowStr(u8 x, u8 y, u8 *str, u8 size) //显示字符串
{
    u8 j=0;
	while (str[j]!='\0')
	{		OLED_ShowChar(x,y,str[j],size);
			x+=8;
		if(x>120){x=0;y+=2;}
			j++;
	}
}

void OLED_ShowCc(u8 x, u8 y, u8 zm)  //显示汉字
{
    u8 i;
    OLED_Pos(x,y);
    for(i=0;i<16;i++) OLED_Send(Hzk[zm][i],IIC_DATA);
    OLED_Pos(x,y+1);
    for(i=0;i<16;i++) OLED_Send(Hzk[zm][i+16],IIC_DATA);
}

void OLED_Reset(void)
{
    OLED_Send(0xae,IIC_CMD);//关闭 oled 面板
    OLED_Send(0x20,IIC_CMD);//设置寻址模式
    OLED_Send(0x02,IIC_CMD);//页面寻址模式
    OLED_Send(0xa1,IIC_CMD);//设置列重映射0-0（SEG扫描方向）[a0左右反置a1正常]
    OLED_Send(0xc8,IIC_CMD);//设置行重映射0-0（COM输出扫描方向）[c0上下反置c8正常]
    OLED_Send(0xa8,IIC_CMD);//设置单片机复用比，双字节，复用比指：COM的使用数目
    OLED_Send(0x3f,IIC_CMD);//复用比为64
    OLED_Send(0x40,IIC_CMD);//设置显示起始线，RAM0开始显示
    OLED_Send(0xd3,IIC_CMD);//设置偏移量，双字节
    OLED_Send(0x00,IIC_CMD);//偏移量为0，RAM0-COM0
    OLED_Send(0xda,IIC_CMD);//设置COM引脚，双字节
    OLED_Send(0x12,IIC_CMD);//设置COM引脚
    OLED_Send(0xd5,IIC_CMD);//设置显示时钟分频比/振荡器频率
    OLED_Send(0x80,IIC_CMD);//设置显示时钟分频比/振荡器频率
    OLED_Send(0xd9,IIC_CMD);//设置预充电周期
    OLED_Send(0xa2,IIC_CMD);//设置预充电周期
    OLED_Send(0xdb,IIC_CMD);//设置VCOMH取消选择级别
    OLED_Send(0x20,IIC_CMD);//设置VCOMH取消选择级别
    OLED_Send(0xa6,IIC_CMD);//设置正常显示（共阴）
    OLED_Send(0x81,IIC_CMD);//设置对比度
    OLED_Send(0x7f,IIC_CMD);//设置对比度
    OLED_Send(0x8d,IIC_CMD);//开启电荷泵
    OLED_Send(0x14,IIC_CMD);//开启电荷泵
    OLED_Send(0xaf,IIC_CMD);//设置正常显示（并输出RAM内容）
}

void OLED_SegSA(void)
{
    OLED_Send(0x20,IIC_CMD);//设置存储器寻址模式
    OLED_Send(0x00,IIC_CMD);//设置存储器水平寻址模式
    OLED_Send(0x21,IIC_CMD);//设置列地址范围，三字节
    OLED_Send(0x00,IIC_CMD);//起始列地址0
    OLED_Send(0x7f,IIC_CMD);//结束列地址127
    OLED_Send(0x22,IIC_CMD);//设置页地址范围，三字节
    OLED_Send(0x00,IIC_CMD);//起始页0
    OLED_Send(0x07,IIC_CMD);//结束页7
}

void OLED_C(void)
{
    u8 i,j;
    OLED_SegSA();
    for (j = 0; j < 8; j++)
    {
        for (i = 0; i < 128; i++)
        {
            OLED_Send(0x00,IIC_DATA);
        }
    }
    OLED_Send(0x20,IIC_CMD);
    OLED_Send(0x02,IIC_CMD);
}