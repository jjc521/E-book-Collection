#include <reg52.h>    		//52系列单片机头文件
#define uchar unsigned char
#define uint unsigned int 
sbit led1=P1^0;
sbit led2=P1^1;
uint num1,num2;
void main()
{
	TMOD=0x03;//设置定时器0为工作方式3(0000 0011)
	TH0=6;    //装初值
	TL0=6;
	EA=1;  //开总中断
	ET0=1; //开定时器0中断
	ET1=1; //开定时器1中断
	TR0=1; //启动定时器0
	TR1=1; //启动定时器0的高8位计数器
	while(1) //程序停止在这里等待中断发生
	{
		if(num1>=3686)		//如果到了3686次，说明1秒时间到
		{
			num1=0;			//然后把num1清0重新再计3686次
			led1=~led1;	    //让发光管状态取反
		}
		if(num2>=1843)		//如果到了1843次，说明半秒时间到
		{
			num2=0;			//然后把num2清0重新再计1843次
			led2=~led2;	    //让发光管状态取反
		}
	}
}
void TL0_time() interrupt 1
{  
	TL0=6;   //重装初值
	num1++;			
}void TH0_time() interrupt 3
{
	TH0=6;    //重装初值
	num2++;			
}
