#include <reg52.h>    		//52系列单片机头文件
#define uchar unsigned char
#define uint unsigned int 
sbit dula=P2^6;		//申明U1锁存器的锁存端
sbit wela=P2^7;		//申明U2锁存器的锁存端
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
void display(uchar num)
{
	P0=table[num]; //显示函数只送段选数据
	dula=1;
	dula=0;
}
void main()
{
	TMOD=0x20;
	TH1=0xfd;
	TL1=0xfd;
	TR1=1;
	REN=1;
	SM0=0;
	SM1=1;	
	EA=1;
	ES=1;
	P0=0xc0;//位选中所有数码管
	wela=1;
	wela=0;
	while(1);//等待串口中断产生，然后更新显示
}
void ser() interrupt 4
{
	uchar a;
	RI=0;
	a=SBUF;
	display(a);
}