#include "./src/oled.h"
#include "./src/onewire.h"
#include "./src/key.h"
//N是小数位数，最高四位，默认一位
#define N 1

//温度数组H {high,low}
char temp_H[]={0,0};
//温度数组D
char temp_D[]={' ','0','2','5','.','0','0','0','0'};
char key_status[]={0,'0',0,'0',0,'0'};

void main()
{
  u8 i;
  OLED_Reset();//OLED 初始化
  OLED_C();//OLED 清屏
  Init_DS18B20();
  while(1)
  {
    OLED_ShowCc(0,0,4);
    OLED_ShowCc(16,0,5);
    OLED_ShowCc(64,2,0);
    key_scan(key_status);
    OLED_ShowChar(80,2,key_status[1],8);
    temperature(temp_H);
    tempstatus(temp_D, temp_H);
    for ( i = 0; i < 5+N; i++)
    {
      OLED_ShowChar(i*8,2,temp_D[i],8);
    }
  }
}