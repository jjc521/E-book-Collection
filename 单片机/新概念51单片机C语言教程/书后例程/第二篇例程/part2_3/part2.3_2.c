#include <reg52.h>    	
#define uchar unsigned char
#define uint unsigned int
sbit dula=P2^6;		//申明U1锁存器的锁存端
sbit wela=P2^7;		//申明U2锁存器的锁存端
sbit dawr=P3^6;		//定义DA的WR端口
sbit dacs=P3^2;		//定义DA的CS端口
sbit beep=P2^3;		//定义蜂鸣器端口
void delayms(uint xms)				
{
	uint i,j;
	for(i=xms;i>0;i--)		      //i=xms即延时约xms毫秒
		for(j=110;j>0;j--);
}

void main()
{
	uchar val,flag;
	dula=0;
	wela=0;
	dacs=0;
	dawr=0;
	P0=0;
	while(1)
	{
		if(flag==0)
		{
			val+=5;
			P0=val;		//通过P0口给DA数据口赋值
			if(val==255)
			{
				flag=1;
		  		beep=0;
				delayms(100);
				beep=1;
			}
			delayms(50);
		}
		else
		{
			val-=5;
			P0=val;		//通过P0口给DA数据口赋值
			if(val==0)
			{
				flag=0;
		  		beep=0;
				delayms(100);
				beep=1;
			}
			delayms(50);
		}		
	}
}
