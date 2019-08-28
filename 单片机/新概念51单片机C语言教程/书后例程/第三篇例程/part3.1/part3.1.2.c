#include <reg52.h>    		//52系列单片机头文件
#define uchar unsigned char
#define uint unsigned int 
sbit led1=P1^0;
uint num;
void main()
{
	TMOD=0x02;//设置定时器0为工作方式2(0000 0010)
	TH0=6;    //装初值
	TL0=6;
	EA=1;  //开总中断
	ET0=1; //开定时器0中断
	TR0=1; //启动定时器0
	while(1) //程序停止在这里等待中断发生
	{
		if(num==3686)		//如果到了3686次，说明1秒时间到
		{
			num=0;			//然后把num清0重新再计3686次
			led1=~led1;	    //让发光管状态取反
		}
	}
}

void T0_time() interrupt 1
{
	num++;			
}