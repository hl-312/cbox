#include "key.h"

void Delay10ms()		//@11.0592MHz
{
	unsigned char i, j;

	i = 18;
	j = 235;
	do
	{
		while (--j);
	} while (--i);
}

void key_scan(char *key_status)
{
    u8 i=0;
    if (key0|key1|key2)
    {
        Delay10ms();
        if (key0) key_status[0]=0;
        else key_status[0]=1;
        if (key1) key_status[2]=0;
        else key_status[2]=1;
        if (key2) key_status[4]=0;
        else key_status[4]=1;
    }
    for (i=0; i<4; i++)//计算按键次数，最大值255
    {
        if (key_status[i*2])
        {
            key_status[i*2+1]+=1;
        }
    }
}