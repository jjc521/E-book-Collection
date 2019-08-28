#include <reg52.h>    		//52系列单片机头文件
#define uchar unsigned char
#define uint unsigned int 
sbit key1=P3^4;
sbit key2=P3^5;
sbit key3=P3^6;
sbit key4=P3^7;
sbit dula=P2^6;		//申明U1锁存器的锁存端
sbit wela=P2^7;		//申明U2锁存器的锁存端
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
void delayms(uint);
uchar numt0,num;
void display(uchar numdis)  //显示子函数
{
	uchar shi,ge;         //分离两个分别要显示的数
	shi=numdis/10;
	ge=numdis%10;

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
void init()    //初始化函数
{
	TMOD=0x01;//设置定时器0为工作方式1(0000 0001)
	TH0=(65536-45872)/256;//装初值50ms一次中断
	TL0=(65536-45872)%256;
	EA=1;  //开总中断
	ET0=1; //开定时器0中断	
}
void keyscan()
{
	if(key1==0)
	{
		delayms(10);
		if(key1==0)
		{
			num++;
			if(num==60)//当到60时重新归0
				num=0;
			while(!key1);//等待按键释放	
		}
	}
	if(key2==0)
	{
		delayms(10);
		if(key2==0)
		{
			if(num==0)//当到0时重新归60
				num=60;
			num--;	
			while(!key2);
		}
	}
	if(key3==0)
	{
		delayms(10);
		if(key3==0)
		{
			num=0;  //清0
			while(!key3);	
		}
	}
	if(key4==0)
	{
		delayms(10);
		if(key4==0)
		{
			while(!key4);
			TR0=~TR0;//启动或停止定时器0	
		}
	}
}
void main()
{
	init();//初始化函数
	while(1) 
	{
		keyscan();
		display(num);
	}
}
void T0_time() interrupt 1
{
	TH0=(65536-45872)/256;//重装初值
	TL0=(65536-45872)%256;	
	numt0++;	
	if(numt0==20)		//如果到了20次，说明1秒时间到
	{
		numt0=0;		//然后把num清0重新再计20次
		num++;
		if(num==60)
			num=0;
	}		
}


