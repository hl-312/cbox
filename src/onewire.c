#include "./onewire.h"

//单总线延时函数
void Delay_OneWire(u16 t)
{
    while (t--)
    {
    };
}

//初始化DS18B20
bit Init_DS18B20(void)
{
    bit initflag = 0;
    DQ = 1;
    Delay_OneWire(12);
    DQ = 0;
    Delay_OneWire(80);
    DQ = 1;
    Delay_OneWire(10);
    initflag = DQ;
    Delay_OneWire(5);

    return initflag;
}

//向DS18B20写入一个字节
void Write_DS18B20(u8 dat)
{
    u8 i;
    for (i = 0; i < 8; i++)
    {
        DQ = 0;
        DQ = dat & 0x01;
        Delay_OneWire(5);
        DQ = 1;
        dat >>= 1;
    }
    Delay_OneWire(5);
}

//从DS18B20读取一个字节
u8 Read_DS18B20(void)
{
    u8 i;
    u8 dat;
    for (i = 0; i < 8; i++)
    {
        DQ = 0;
        dat >>= 1;
        DQ = 1;
        if (DQ)
        {
            dat |= 0x80;
        }
        Delay_OneWire(5);
    }
    return dat;
}

/*
CCH：跳过ROM指令，忽略64位ROM地址，直接向DS18B20发起温度转换指令。
44H：温度转换指令，启动DS18B20进行温度转换，视所用精度转换时间随之不同，结果保存在高速RAM中。
BEH：度暂存器指令，读取高速暂存器中9个字节的内容。
标准操作流程：
复位——跳过ROM——操作指令<延时>
*/

//温度读取函数
void temperature(char *temp)
{
    Init_DS18B20();
    Write_DS18B20(0xcc);
    Write_DS18B20(0x44);
    Delay_OneWire(250);
    Delay_OneWire(250);
    Delay_OneWire(250);
    Delay_OneWire(250);
    Init_DS18B20();
    Write_DS18B20(0xcc);
    Write_DS18B20(0xbe);
    temp[1]=Read_DS18B20();
    temp[0]=Read_DS18B20();
}

//温度状态字函数
void tempstatus(char *tempD, char *tempH)
{
    u8 zs=0;
    u16 xs=0;
    if (tempH[0]>7)
    {
        tempD[0]='-';
        tempH[1]=~tempH[1]+1;
        if (tempH[1]==0)tempH[0]++;
    }
    else tempD[0]=' ';
    tempH[0]=tempH[0]&0x07;
    zs=(tempH[0]*16)+((tempH[1]&0xf0)/16);
    xs=(tempH[1]&0x0f)*625;
    tempD[1]='0'+zs/100;
    tempD[2]='0'+zs%100/10;
    tempD[3]='0'+zs%10;
    tempD[5]='0'+xs/1000;
    tempD[6]='0'+xs%1000/100;
    tempD[7]='0'+xs%100/10;
    tempD[8]='0'+xs%10;
}