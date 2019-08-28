#include<reg52.h>
#include<define.h>
void delay(uint z)//延时函数
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}
void di() //蜂鸣器报警声音
{
	beep=0;
	delay(100);
	beep=1;
}
void write_com(uchar com)
{//写液晶命令函数
	rs=0;
	lcden=0;
	P0=com;
	delay(3);
	lcden=1;
	delay(3);
	lcden=0;	
}
void write_date(uchar date)
{//写液晶数据函数
	rs=1;
	lcden=0;
	P0=date;
	delay(3);
	lcden=1;
	delay(3);
	lcden=0;	
}
void init()
{//初始化函数
	uchar num;
	EA=1;//打开总中断
	EX1=1;//开外部中断1
	IT1=1;//设置负跳变沿触发中断
	flag1=0;//变量初始化
	t0_num=0;
	s1num=0;
	week=1;
	dula=0;//关闭数码管显示
	wela=0;
	lcden=0;
	rd=0;
/*以下几行在首次设置DS12C887时使用，以后不必再写入
	write_ds(0x0A,0x20);//打开振荡器
	write_ds(0x0B,0x26);//设置24小时模式，数据二进制格式
						//开启闹铃中断
	set_time();//设置上电默认时间
-----------------------------------------------------*/
	write_com(0x38);//1602液晶初始化
	write_com(0x0c);
	write_com(0x06);
	write_com(0x01);
	write_com(0x80);
	for(num=0;num<15;num++)//写入液晶固定部分显示
		{
			write_date(table[num]);
			delay(1);
		}
	write_com(0x80+0x40);
	for(num=0;num<11;num++)
		{
			write_date(table1[num]);
			delay(1);
		}
}
void write_sfm(uchar add,char date)
{//1602液晶刷新时分秒函数4为时，7为分，10为秒
	char shi,ge;
	shi=date/10;
	ge=date%10;
	write_com(0x80+0x40+add);
	write_date(0x30+shi);
	write_date(0x30+ge);
}
void write_nyr(uchar add,char date)
{//1602液晶刷新年月日函数3为年，6为分，9为秒
	char shi,ge;
	shi=date/10;
	ge=date%10;
	write_com(0x80+add);
	write_date(0x30+shi);
	write_date(0x30+ge);
}
void write_week(char we)
{//写液晶星期显示函数
	write_com(0x80+12);
	switch(we)
	{
		case 1:	write_date('M');delay(5);
				write_date('O');delay(5);
				write_date('N');
				break;
		case 2:	write_date('T');delay(5);
				write_date('U');delay(5);
				write_date('E');
				break;
		case 3:	write_date('W');delay(5);
				write_date('E');delay(5);
				write_date('D');
				break;
		case 4:	write_date('T');delay(5);
				write_date('H');delay(5);
				write_date('U');
				break;
		case 5:	write_date('F');delay(5);
				write_date('R');delay(5);
				write_date('I');
				break;
		case 6:	write_date('S');delay(5);
				write_date('A');delay(5);
				write_date('T');
				break;
		case 7:	write_date('S');delay(5);
				write_date('U');delay(5);
				write_date('N');
				break;
	}
}
void keyscan()
{
	if(flag_ri==1)
	{//这里用来取消闹钟报警，任一键取消报警
		if((s1==0)||(s2==0)||(s3==0)||(s4==0))
		{	
			delay(5);
			if((s1==0)||(s2==0)||(s3==0)||(s4==0))
			{
				while(!(s1&&s2&&s3&&s4));
                di();
				flag_ri=0;//清除报警标志
			}	 	
		}
	}	
	if(s1==0)//检测S1
	{
		delay(5);
		if(s1==0)
		{	
			s1num++;//记录按下次数
			if(flag1==1)
				if(s1num==4)
					s1num=1;
			flag=1;
			while(!s1);di();
			switch(s1num)
			{//光标闪烁点定位
				case 1: write_com(0x80+0x40+10);
					    write_com(0x0f);
						break;
				case 2: write_com(0x80+0x40+7);
						break;
				case 3: write_com(0x80+0x40+4);
						break;
				case 4: write_com(0x80+12);
						break;
				case 5: write_com(0x80+9);
						break;
				case 6: write_com(0x80+6);
						break;
				case 7: write_com(0x80+3);
						break;
				case 8: s1num=0;
						write_com(0x0c);
						flag=0;
						write_ds(0,miao);
						write_ds(2,fen);
						write_ds(4,shi);
						write_ds(6,week);
						write_ds(7,day);
						write_ds(8,month);
						write_ds(9,year);
						break;
			}	
		}
	}
	if(s1num!=0)//只有当S1按下后，才检测S2和S3
	{
		if(s2==0)
		{
			delay(1);
			if(s2==0)
			{
				while(!s2);di();
				switch(s1num)
				{//根据功能键次数调节相应数值
					case 1:	miao++;
							if(miao==60)
								miao=0;
							write_sfm(10,miao);
							write_com(0x80+0x40+10); 
							break;
					case 2:	fen++;
							if(fen==60)
								fen=0;
							write_sfm(7,fen);
							write_com(0x80+0x40+7); 
							break;
					case 3:	shi++;
							if(shi==24)
								shi=0;
							write_sfm(4,shi);
							write_com(0x80+0x40+4); 
							break;
					case 4:	week++;
							if(week==8)
								week=1;
							write_week(week);
							write_com(0x80+12);
							break;
					case 5:	day++;
							if(day==32)
								day=1;
							write_nyr(9,day);
							write_com(0x80+9);
							break;
					case 6:	month++;
							if(month==13)
								month=1;
							write_nyr(6,month);
							write_com(0x80+6);
							break;
					case 7:	year++;
							if(year==100)
								year=0;
							write_nyr(3,year);
							write_com(0x80+3);
							break;
				}
			}
		}
		if(s3==0)
		{
			delay(1);
			if(s3==0)
			{
				while(!s3);di();
				switch(s1num)
				{//根据功能键次数调节相应数值
					case 1:	miao--;
							if(miao==-1)
								miao=59;
							write_sfm(10,miao);
							write_com(0x80+0x40+10);
							break; 
					case 2:	fen--;
							if(fen==-1)
								fen=59;
							write_sfm(7,fen);
							write_com(0x80+0x40+7);
							break;
					case 3:	shi--;
							if(shi==-1)
								shi=23;
							write_sfm(4,shi);
							write_com(0x80+0x40+4);
							break;
					case 4:	week--;
							if(week==0)
								week=7;
							write_week(week);
							write_com(0x80+12);
							break;
					case 5:	day--;
							if(day==0)
								day=31;
							write_nyr(9,day);
							write_com(0x80+9);
							break;
					case 6:	month--;
							if(month==0)
								month=12;
							write_nyr(6,month);
							write_com(0x80+6);
							break;
					case 7:	year--;
							if(year==-1)
								year=99;
							write_nyr(3,year);
							write_com(0x80+3);
							break;
				}
			}
		}
	}
	if(s4==0)//检测S4
	{
		delay(5);
		if(s4==0)
		{	
			flag1=~flag1;
			while(!s4);di();
			if(flag1==0)
			{//退出闹钟设置时保存数值
				flag=0;
				write_com(0x80+0x40);
				write_date(' ');
				write_date(' ');
				write_com(0x0c);
				write_ds(1,miao);
				write_ds(3,fen);
				write_ds(5,shi);				
			}
			else
			{//进入闹钟设置
				read_alarm();//读取原始数据
				miao=amiao;//重新赋值用以按键调节
				fen=afen;
				shi=ashi;
				write_com(0x80+0x40);
				write_date('R');//显示标志
				write_date('i');
				write_com(0x80+0x40+3);
				write_sfm(4,ashi);//送液晶显示闹钟时间
				write_sfm(7,afen);
				write_sfm(10,amiao);
			}			
		}
	}
}

void write_ds(uchar add,uchar date)
{//写12C887函数
	dscs=0;
	dsas=1;
	dsds=1;
	dsrw=1;
	P0=add;//先写地址
	dsas=0;
	dsrw=0;
	P0=date;//再写数据
	dsrw=1;
	dsas=1;
	dscs=1;				
}

uchar read_ds(uchar add)
{//读12C887函数
 	uchar ds_date;
	dsas=1;
	dsds=1;
	dsrw=1;
	dscs=0;
	P0=add;//先写地址
	dsas=0;
	dsds=0;
	P0=0xff;
	ds_date=P0;//再读数据
	dsds=1;
	dsas=1;
	dscs=1;
	return ds_date;	
}
/*---首次操作12C887时给予寄存器初始化---
void set_time()
{//首次上电初始化时间函数
	write_ds(0,0);
	write_ds(1,0);
	write_ds(2,0);
	write_ds(3,0);
	write_ds(4,0);
	write_ds(5,0);
	write_ds(6,0);
	write_ds(7,0);
	write_ds(8,0);
	write_ds(9,0);	
}
----------------------------------------*/
void read_alarm()
{//读取12C887闹钟值
	amiao=read_ds(1);
	afen=read_ds(3);
	ashi=read_ds(5);
}
void main()//主函数
{
	init();//调用初始化函数
	while(1)
	{
		keyscan();//按键扫描
		if(flag_ri==1)//当闹钟中断时进入这里
		{
			di();
			delay(100);
			di();
			delay(500);
		}	
		if(flag==0&&flag1==0)//正常工作时进入这里
		{
			keyscan();//按键扫描
			year=read_ds(9);//读取12C887数据
			month=read_ds(8);	
			day=read_ds(7);
			week=read_ds(6);
			shi=read_ds(4);
			fen=read_ds(2);
			miao=read_ds(0);	
			write_sfm(10,miao);//送液晶显示
			write_sfm(7,fen);
			write_sfm(4,shi);
			write_week(week);
			write_nyr(3,year);
			write_nyr(6,month);
			write_nyr(9,day);
		}
	}
}

void exter() interrupt 2//外部中断1服务程序
{	uchar c; //进入中断表示闹钟时间到，
	flag_ri=1; //设置标志位，用以大程序中报警提示
	c=read_ds(0x0c);//读取12C887的C寄存器表示响应了中断
}



