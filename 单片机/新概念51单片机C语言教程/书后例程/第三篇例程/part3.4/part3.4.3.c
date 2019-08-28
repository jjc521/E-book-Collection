#include <reg52.h>    		//52系列单片机头文件
#define uchar unsigned char
#define uint unsigned int 
sfr ISP_CONTR=0xe7;
sbit dula=P2^6;		//申明U1锁存器的锁存端
sbit wela=P2^7;		//申明U2锁存器的锁存端
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
uchar num;
void delayms(uint);
void display(uchar shi,uchar ge)  //显示子函数
{
    dula=1;
	P0=table[shi];    //送十位段选数据
	dula=0;
	P0=0xff;		//送位选数据前关闭所有显示，防止打开位选锁存时
	wela=1;			//原来段选数据通过位选锁存器造成混乱
	P0=0xfe;		//送位选数据
	wela=0;
	delayms(5);	//延时
	dula=1;
	P0=table[ge];  //送个位段选数据
	dula=0;
	P0=0xff;
	wela=1;
	P0=0xfd;
	wela=0;
	delayms(5);
}
void delayms(uint xms)				
{
	uint i,j;
	for(i=xms;i>0;i--)		      //i=xms即延时约xms毫秒
		for(j=110;j>0;j--);
}
void main()
{
	uchar a,b,num1;
	TMOD=0x01; //设置定时器0为工作方式1(0000 0001)
	TH0=(65536-50000)/256;     
	TL0=(65536-50000)%256;
	EA=1;
	ET0=1;
	TR0=1;
	while(1) 
	{
		if(num>=20)
		{
			num=0;
			num1++;
			if(num1==10)
			{
				ISP_CONTR=0x20;
			}
			a=num1/10;
			b=num1%10;
		}
		display(a,b);
	}
}
void timer0() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	num++;	
}
