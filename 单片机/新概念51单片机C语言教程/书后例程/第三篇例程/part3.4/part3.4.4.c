#include <intrins.h>
#include <reg52.h>    		//52系列单片机头文件
#define uchar unsigned char
#define uint unsigned int 
#define RdCommand 0x01	//定义ISP的操作命令
#define PrgCommand 0x02
#define EraseCommand 0x03	
#define Error 1
#define Ok 0
#define WaitTime 0x01 //定义CPU的等待时间
sfr ISP_DATA=0xe2;  //寄存器申明
sfr ISP_ADDRH=0xe3;
sfr ISP_ADDRL=0xe4;
sfr ISP_CMD=0xe5;
sfr ISP_TRIG=0xe6;
sfr ISP_CONTR=0xe7;
sbit dula=P2^6;		//申明U1锁存器的锁存端
sbit wela=P2^7;		//申明U2锁存器的锁存端
uchar code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0x77,0x7c,
0x39,0x5e,0x79,0x71};
uchar num;
void delayms(uint xms)				
{
	uint i,j;
	for(i=xms;i>0;i--)		      //i=xms即延时约xms毫秒
		for(j=110;j>0;j--);
}
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
/* ================ 打开 ISP,IAP 功能 ================= */
void ISP_IAP_enable(void)
{
	EA	=	0;							/* 关中断 		*/
	ISP_CONTR =	ISP_CONTR & 0x18;       /* 0001,1000	*/
	ISP_CONTR =	ISP_CONTR | WaitTime;	/* 写入硬件延时	*/
	ISP_CONTR =	ISP_CONTR | 0x80;       /* ISPEN=1		*/
}
/* =============== 关闭 ISP,IAP 功能 ================== */
void ISP_IAP_disable(void)
{
	ISP_CONTR	=	ISP_CONTR & 0x7f;	/* ISPEN = 0 */
	ISP_TRIG	=	0x00;
	EA			=   1;			/* 开中断 */
}
/* ================ 公用的触发代码 ==================== */
void ISPgoon(void)
{
	ISP_IAP_enable();			/* 打开 ISP,IAP 功能	*/
	ISP_TRIG	=	0x46;		/* 触发ISP_IAP命令字节1	*/
	ISP_TRIG	=	0xb9;		/* 触发ISP_IAP命令字节2	*/
	_nop_();
}
/* ==================== 字节读 ======================== */
unsigned char byte_read(unsigned int byte_addr)
{
	ISP_ADDRH = (unsigned char)(byte_addr >> 8);/* 地址赋值	*/
	ISP_ADDRL = (unsigned char)(byte_addr & 0x00ff);
	ISP_CMD   = ISP_CMD	& 0xf8;			/* 清除低3位 	*/
	ISP_CMD   = ISP_CMD	| RdCommand;	/* 写入读命令	*/
	ISPgoon();							/* 触发执行		*/
	ISP_IAP_disable();				/* 关闭ISP,IAP功能	*/
	return (ISP_DATA);				/* 返回读到的数据	*/
}
/* ================== 扇区擦除 ======================== */
void SectorErase(unsigned int sector_addr)
{
	unsigned int iSectorAddr;
	iSectorAddr = (sector_addr & 0xfe00); /* 取扇区地址 */
	ISP_ADDRH = (unsigned char)(iSectorAddr >> 8);
	ISP_ADDRL = 0x00;
	ISP_CMD	= ISP_CMD & 0xf8;			/* 清空低3位 	*/
	ISP_CMD	= ISP_CMD | EraseCommand;	/* 擦除命令3 	*/
	ISPgoon();							/* 触发执行		*/
	ISP_IAP_disable();				/* 关闭ISP,IAP功能	*/
}
/* ==================== 字节写 ======================== */
void byte_write(unsigned int byte_addr, unsigned char original_data)
{
	ISP_ADDRH =	(unsigned char)(byte_addr >> 8); 	/* 取地址 	*/
	ISP_ADDRL =	(unsigned char)(byte_addr & 0x00ff);
	ISP_CMD	 = ISP_CMD & 0xf8;				/* 清低3位	*/
	ISP_CMD  = ISP_CMD | PrgCommand;		/* 写命令2	*/
	ISP_DATA = original_data;			/* 写入数据准备	*/
	ISPgoon();							/* 触发执行		*/
	ISP_IAP_disable();					/* 关闭IAP功能	*/
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
	num1=byte_read(0x2000);//程序开始时读取EEPROM中数据
	if(num1>=60)	//防止首次上电时读取出错
		num1=0;
	while(1) 
	{
		if(num>=20)
		{
			num=0;
			num1++;
			SectorErase(0x2000);//擦除扇区
			byte_write(0x2000,num1);//重新写入数据
			if(num1==60)
			{
				num1=0;
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
