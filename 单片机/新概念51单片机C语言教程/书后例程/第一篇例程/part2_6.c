#include <reg52.h>    		//52系列单片机头文件
#include <intrins.h>
#define uint unsigned int 		//宏定义
#define uchar unsigned char
void delayms(uint);				//声明子函数
uchar aa;
void main()		      		//主函数
{
	aa=0xfe;					//赋初值11111110 
	while(1)		 			 //大循环
	{
		P1=aa;
		delayms(500);             //延时500毫秒
		aa=_crol_(aa,1);        //将aa循环左移1位后再赋给aa
	}	
}
void delayms(uint xms)				
{
	uint i,j;
	for(i=xms;i>0;i--)		      //i=xms即延时约xms毫秒
		for(j=110;j>0;j--);
}
