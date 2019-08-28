#include <reg52.h>    		//52系列单片机头文件
#include <intrins.h>
#define uchar unsigned char
#define uint unsigned int 
sbit dula=P2^6;		//申明U1锁存器的锁存端
sbit wela=P2^7;		//申明U2锁存器的锁存端
sbit adwr=P3^6;		//定义AD的WR端口
sbit adrd=P3^7;		//定义AD的RD端口
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

void display(uchar bai,uchar shi,uchar ge)  //显示子函数
{
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


void main()		//	主程序
{

 	uchar a,A1,A2,A3,adval;
	wela=1;
	P0=0x7f;           //置CSAD为0，选通ADCS 以后不必再管ADCS
	wela=0;
    while(1)
	{
		adwr=1;
		_nop_();
		adwr=0;			//启动AD转换
		_nop_();
		adwr=1;
		for(a=10;a>0;a--)        //TX-1C实验板AD工作频率较低，所以启动转换后要多留点时间用来转换
		{                        //这里把显示部分放这里的原因也是为了延长转换时间                                                                                                                                                                                                                           
			display(A1,A2,A3);
		}
		P1=0xff;                    //读取P1口之前先给其写全1 
		adrd=1;                    //选通ADCS
		_nop_();	
		adrd=0;                     //AD读使能
		_nop_();
		adval=P1;			//AD数据读取赋给P1口
		adrd=1;
		A1=adval/100;		//分出百，十，和个位
		A2=adval%100/10;
		A3=adval%10;
	 }
}