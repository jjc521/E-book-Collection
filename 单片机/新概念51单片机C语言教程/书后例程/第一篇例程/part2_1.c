#include <reg52.h> //52系列单片机头文件
sbit led1=P1^0;	   //声明单片机P1口的第一位
void main()		   //主函数
{
	led1=0;       /*点亮第一个发光二极管*/	
} 
