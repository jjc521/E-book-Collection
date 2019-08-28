//调节舵机使之转动5个角度 0 45 90 135 180 PWM信号周期为20ms，
//控制高电平的持续时间即可控制舵机停止制动的角度，0.5ms-0度 1-45 1.5-90 2-135 2.5-180 
//程序流程是：开机时舵机角度自动转为0度，按下 P3.7则转到45度，以后就根据两个按键的按下而转动
#include "reg52.h"
unsigned char count;      //0.5ms次数标识
sbit pwm =P3^0 ;          //PWM信号输出
sbit jia =P3^7;           //角度增加按键检测IO口
sbit jan =P3^6;           //角度减少按键检测IO口
unsigned char jd;         //角度标识
void delay(unsigned char i)//延时
{
  unsigned char j,k;
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
}

void Time0_Init()          //定时器初始化
{
	TMOD = 0x01;           //定时器0工作在方式1    
	IE 	 = 0x82;
	TH0  = 0xfe;
	TL0  = 0x33;		   //11.0592MZ晶振，0.5ms
    TR0=1;                 //定时器开始
}

void Time0_Int() interrupt 1 //中断程序
{
	TH0  = 0xfe;             //重新赋值
	TL0  = 0x33;

    if(count<jd)              //判断0.5ms次数是否小于角度标识
      pwm=1;                  //确实小于，PWM输出高电平
    else
      pwm=0;                  //大于则输出低电平

    count=(count+1);          //0.5ms次数加1
    count=count%40;			  //次数始终保持为40 即保持周期为20ms
}


void keyscan()              //按键扫描
{ 
   if(jia==0)               //角度增加按键是否按下
  {
    delay(10);              //按下延时，消抖
    if(jia==0)              //确实按下
     {
      jd++;                 //角度标识加1
      count=0;              //按键按下 则20ms周期从新开始
      if(jd==6)
        jd=5;               //已经是180度，则保持
      while(jia==0);        //等待按键放开
     }
  }

  if(jan==0)                //角度减小按键是否按下
  {
    delay(10);
    if(jan==0)
     {
      jd--;                 //角度标识减1
      count=0;
      if(jd==0)
        jd=1;               //已经是0度，则保持
      while(jan==0);
     }
  }
}

void main()
{
 jd=1;
 count=0; 
 Time0_Init();              
 while(1)
 {
  keyscan();               //按键扫描
   
 }
}
