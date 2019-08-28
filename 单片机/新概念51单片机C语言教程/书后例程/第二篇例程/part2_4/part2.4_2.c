#include <reg52.h> 
#include <intrins.h> 
#include <stdio.h>	
#define uchar unsigned char
#define uint unsigned int
sbit dula=P2^6;		//申明U1锁存器的锁存端
sbit wela=P2^7;		//申明U2锁存器的锁存端
sbit adwr=P3^6;		//定义AD的WR端口
sbit adrd=P3^7;		//定义AD的RD端口
uchar flag,a;
unsigned char flag_uart,flag_time,flag_on,a,i,t0_num,ad_val;
float ad_vo;
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
void delayms(uint xms)				
{
	uint i,j;
	for(i=xms;i>0;i--)		      //i=xms即延时约xms毫秒
		for(j=110;j>0;j--);
}
void init()
{
	TMOD=0x21;
//	SCON=0x50;
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	TH1=0xfd;
	TL1=0xfd;
	TR1=1;
	ET0=1;
	SM0=0;
	SM1=1;
	REN=1;
	EA=1;
	ES=1;

}
void display(uchar value)  //显示子函数
{
	uchar bai,shi,ge;
	bai=value/100;		//分出百，十，和个位
	shi=value%100/10;
	ge=value%10;
	dula=1;
	P0=table[bai];    //送段选数据
	dula=0;
	P0=0xff;		//送位选数据前关闭所有显示，防止打开位选锁存时
	wela=1;			//原来段选数据通过位选锁存器造成混乱
	P0=0x7e;		//送位选数据
	wela=0;
	delayms(5);	    //延时
	dula=1;
	P0=table[shi];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0x7d;
	wela=0;
	delayms(5);
	dula=1;
	P0=table[ge];
	dula=0;
	P0=0xff;
	wela=1;
	P0=0x7b;
	wela=0;
	delayms(5);
}
uchar get_ad()		
{
 	uchar adval;
	adwr=1;
	_nop_();
	adwr=0;			//启动AD转换
	_nop_();
	adwr=1;
	P1=0xff;                    //读取P1口之前先给其写全1 
	adrd=1;                   
	_nop_();	
	adrd=0;                     //AD读使能
	_nop_();
	adval=P1;			//AD数据读取
	adrd=1;
	return adval;
} 
void main()
{
	init();
	wela=1;
	P0=0x7f;           //置CSAD为0，选通ADCS 以后不必再管ADCS
	wela=0;
	while(1)
	{
		if(flag_uart==1)
		{
			flag_uart=0;
			ES=0;
			TI=1;
			switch(flag_on)
			{
				case 0: puts("Turn on ad!\n");
						TR0=1;
						break;
				case 1: printf("Turn off ad!\n");
						TR0=0;
						break;
				case 2: puts("Error!\n");
						break;
			}
			while(!TI);//必须要加
			TI=0;
			ES=1;
		}
		if(flag_time==1)
		{
			flag_time=0;
			ad_val=get_ad();
			ad_vo=(float)ad_val*5.0/256.0;
			ES=0;
			TI=1;
			printf("The voltage is %fV\n",ad_vo);
			while(!TI);
			TI=0;
			ES=1;
		}
		display(ad_val);
	}
}
void timer0() interrupt 1
{
	TH0=(65536-50000)/256;
	TL0=(65536-50000)%256;
	t0_num++;
	if(t0_num==20)
	{
		t0_num=0;
		flag_time=1;
	}
}
void ser() interrupt 4
{
	RI=0;
	a=SBUF;
	flag_uart=1;
	if(a==1)
		flag_on=0;
 	else if(a==2)
			flag_on=1;
		else
			flag_on=2;
}




