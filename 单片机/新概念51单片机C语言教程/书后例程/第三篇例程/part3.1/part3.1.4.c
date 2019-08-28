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
uint read()
{
	uchar tl,th1,th2;
	uint val;
	while(1)
	{
		th1=TH0;
		tl=TL0;
		th2=TH0;
		if(th1==th2)
			break;
	}
	val=th1*256+tl;
	return val;	
}
void main()
{
	uchar a,b;
	uint num;
	TMOD=0x05; //设置计数器0为工作方式1(0000 0101)
	TH0=0;     //将计数器寄存器初值清零
	TL0=0;
	TR0=1;
	while(1) 
	{
		num=read();
		if(num>=100)
		{
			num=0;
			TH0=0;   //将计数器寄存器值清零
			TL0=0;
		}
		a=num/10;
		b=num%10;
		display(a,b);
	}
}


