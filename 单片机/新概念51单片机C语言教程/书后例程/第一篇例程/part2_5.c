#include <reg52.h>    		//52系列单片机头文件
#define uint unsigned int 		//宏定义
sbit led1=P1^0;	     		 //声明单片机P1口的第一位
void delayms(uint);				//声明子函数
void main()		      		//主函数
{
	while(1)		 			 //大循环
	{
		led1=0;					/*点亮第一个发光二极管*/	
		delayms(200);				//延时200毫秒
		led1=1;					/*关闭第一个发光二极管*/	
		delayms(800);				//延时800毫秒
	}	
}
void delayms(uint xms)				
{
	uint i,j;
	for(i=xms;i>0;i--)		      //i=xms即延时约xms毫秒
		for(j=110;j>0;j--);
}
