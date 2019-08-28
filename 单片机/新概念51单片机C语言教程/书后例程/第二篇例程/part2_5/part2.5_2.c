#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int
uchar code table[]="Hello everyone!";
uchar code table1[]="Welcome to here!";
sbit lcden=P3^4;	//液晶使能端
sbit lcdrs=P3^5;	//液晶数据命令选择端
sbit dula=P2^6;		//申明U1锁存器的锁存端
sbit wela=P2^7;		//申明U2锁存器的锁存端
uchar num;
void delay(uint z)
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void write_com(uchar com)
{
	lcdrs=0;
	P0=com;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}
void write_data(uchar date)
{
	lcdrs=1;
	P0=date;
	delay(5);
	lcden=1;
	delay(5);
	lcden=0;
}
void init()
{
	dula=0;
	wela=0;
	lcden=0;
	write_com(0x38);//设置16X2显示,5X7点阵,8位数据接口
	write_com(0x0c);//设置开显示，不显示光标
	write_com(0x06);//写一个字符后地址指针加1
	write_com(0x01);//显示清零，数据指针清零
}
void main()
{
	init();
	write_com(0x80+0x10);
	for(num=0;num<15;num++)
	{
		write_data(table[num]);
		delay(5);
	}
	write_com(0x80+0x50);
	for(num=0;num<16;num++)
	{
		write_data(table1[num]);
		delay(5);
	}
	for(num=0;num<16;num++)
	{
		write_com(0x18);
		delay(200);
	}
	while(1);
}
