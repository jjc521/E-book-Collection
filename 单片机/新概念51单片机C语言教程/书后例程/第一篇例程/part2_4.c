#include <reg52.h>    		//52系列单片机头文件
#define uint unsigned int 		//宏定义
sbit led1=P1^0;	     		 //声明单片机P1口的第一位
void delay1s();				//声明子函数
void main()		      		//主函数
{
	while(1)		 			 //大循环
	{
		led1=0;					/*点亮第一个发光二极管*/	
		delay1s();				//调用延时子函数
		led1=1;					/*关闭第一个发光二极管*/	
		delay1s();				//调用延时子函数
	}	
}
void delay1s()						//子函数体
{
	uint i,j;
	for(i=500;i>0;i--)		
		for(j=110;j>0;j--);
}

