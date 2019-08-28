#include <reg52.h>    //52系列单片机头文件
#define uint unsigned int //宏定义
sbit led1=P1^0;	      //声明单片机P1口的第一位
uint i,j;
void main()		      //主函数
{
	while(1)		  //大循环
	{
		led1=0;					/*点亮第一个发光二极管*/	
		for(i=1;i>0;i--)		//延时
			for(j=110;j>0;j--);
		led1=1;					/*关闭第一个发光二极管*/	
		for(i=1000;i>0;i--)		//延时
			for(j=110;j>0;j--);		
	}	
} 