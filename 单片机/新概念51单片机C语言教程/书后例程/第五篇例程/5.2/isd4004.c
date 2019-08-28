#include <reg52.h>
#include <intrins.h> 
sbit cs_4004 = P0^0;
sbit sclk_4004= P0^3;
sbit mosi_4004= P0^1;
sbit miso_4004= P0^2;
sbit rac_4004 = P0^4;
sbit int_4004 = P0^5;
void delay(unsigned int i) //延时程序
{
	while(i--);
}
void stopmode() //停止
{
	unsigned char m,i,j;
	cs_4004=1;
	sclk_4004=0;
	cs_4004=0;
	m=0x30;
	for(i=0;i<8;i++)
	{
		m=_cror_(m,1);
		j=m<<1;
		mosi_4004=CY;
		sclk_4004=0;
		sclk_4004=1;
	}
	cs_4004=1;
}
void powerdown() //下电
{
	unsigned char m,i,j;
	cs_4004=1;
	sclk_4004=0;
	cs_4004=0;
	m=0x10;
	for(i=0;i<8;i++)
	{
		m=_cror_(m,1);
		j=m<<1;
		mosi_4004=CY;
		sclk_4004=0;
		sclk_4004=1;
	}
	cs_4004=1;
}
void powerup()// 上电
{
	unsigned char m,i,j;
	cs_4004=1;
	sclk_4004=0;
	cs_4004=0;
	m=0x20;
	for(i=0;i<8;i )
	{
		m=_cror_(m,1);
		j=m<<1;
		mosi_4004=CY;
		sclk_4004=0;
		sclk_4004=1;
	}
	cs_4004=1;
}
void record4004(unsigned int address)
{// 录音 address--录音地址 0---2400
	unsigned char i,m,j;
	unsigned int datasoute=0;	
	powerup();
	delay(5118);//上电延时
	powerup();
	delay(5118);//上电延时
	delay(5118);//上电延时
	cs_4004=1;
	sclk_4004=0;
	m=0xa0;
	cs_4004=0;
	for(i=0;i<16;i++)
	{
		address=_iror_(address,1);
		datasoute=address<<1;
		mosi_4004=CY;
		sclk_4004=0;
		sclk_4004=1;
	}
	for(i=0;i<8;i++)
	{
		m=_cror_(m,1);
		j=m<<1;
		mosi_4004=CY;
		sclk_4004=0;
		sclk_4004=1;
	}
	cs_4004=1;
	sclk_4004=0;
	m=0xb0;
	cs_4004=0;
	for(i=0;i<8;i++)
	{
		m=_cror_(m,1);
		j=m<<1;
		mosi_4004=CY;
		sclk_4004=0;
		sclk_4004=1;
	}
	cs_4004=1;
	P0=0xff;
	datasoute=0;
	while(int_4004==1) //存储地址换行标志
	{
		if(rac_4004)//记录本次录音所占的行数(也就是本次录音有多大)
		{
			delay(20000);
			datasoute++; 
		}
// 在这里应该加上自己的程序，就是录音退出程序
	}
}//while end;
void audioout(unsigned int address) //放音程序
{
	unsigned char i,m,j;
	unsigned int datasoute;
	powerup();
	cs_4004=1;
	sclk_4004=0;
	cs_4004=0;
	m=0xe0;
	for(i=0;i<16;i++)
	{
		address=_iror_(address,1);
		datasoute=address<<1;
		sclk_4004=0;
		mosi_4004=CY;
		sclk_4004=1;
	}
	for(i=0;i<8;i++)
	{
		m=_cror_(m,1);
		j=m<<1;
		sclk_4004=0;
		mosi_4004=CY;
		sclk_4004=1;
	}
	cs_4004=1;
	sclk_4004=0;
	m=0xf0;
	cs_4004=0;
	for(i=0;i<8;i )
	{
		m=_cror_(m,1);
		j=m<<1;
		sclk_4004=0;
		mosi_4004=CY;
		sclk_4004=1;
	}
	cs_4004=1;
	P0=0xff;
	while(int_4004==1)
	{
	}
}
void main()
{
	record4004(0);
	audioout(0);
	while(1);
}