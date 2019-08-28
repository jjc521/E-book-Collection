#include<STC12C5410AD.H>
#include <intrins.h>
#include "define.h"
#include<STC_EEPROM.H>
#include "ad.h"
#include "writeyejing.h"
#include "pvgz.h"
#include "init.h"

void int_t1() interrupt 3
{
	TH1=(65536-50000)/256; //定时器初始化
	TL1=(65536-50000)%256;
	t1_num++;
	t1_numgz++;
	if(t1_num==jcjg)//检测电池板周期
	{
		t1_num=0;
		flag_t1=1;		
	}
	if(t1_numgz==jcgzjg)//检测过载恢复周期
	{
		t1_numgz=0;
		flag_t1gz=1;
	}	
}
void main()
{
	init();
	while(1)
	{    
		if(flag_pv==1)
		{//当有太阳能电池板时进入这里
		   v_temp=Ad_Av(1);	
		   if(v_temp<qy)//进入欠压
			{
				qyd=0;   //欠压指示
				delay(1000);
				diqynum=3;
				P1M0=0x87; //00000111
				P1M1=0xc9; //00000111
				fz_off; //将负载关闭
				fzd=1;
				flag_fz=0;
				while(!(Ad_Av(1)>=qyhf))
				{//一直等待欠压恢复
					checkpv();//检测电池板
					if(flag_pv==1)
					{
						pwm_1();   //打开充电
						cdd=0;   //打开充电指示
					}
					fcd_z();//按键检测
					fcd_j();
					func();
					diqynum--;
					if(diqynum>0)//报警指示
					{
						didi(3);
						delay(1000);
					 }
					else
						diqynum=1;
					
				}
				didi(1);//欠压恢复时开启负载
				fz_on;
				delay(1);
				fzd=0;
				P1M0=0x8f; //00000111
				P1M1=0xc1; //00000111
				flag_fz=1;
				delay(1000);
				qyd=1;
				pwm_a=20;
			} 
			if(v_temp>=qy&&v_temp<=gygd)
			{//正常工作电压区间
				qyd=1;   //欠压指示关闭
				if(v_temp<fcdy)
				{
					cdd=0;//开充电指示灯
					//这里省去PWM控制程序
				}
				if(v_temp>fcdy&&v_temp<gddy)
				{
					cdd=0;//开充电指示灯
					//这里省去PWM控制程序
				}
				if(v_temp>gddy)
				{
					cdd=0;//开充电指示灯
					//这里省去PWM控制程序
				}			
			} 
			if(v_temp>gygd)    //判断是否过压
			{
				pwm_0();//过压后关闭充电
				cdd=1;
		 	}
		}
		else//没有太阳能电池板是进入这里
		{
		   v_temp=Ad_Av(1);	
		   if(v_temp<qy)
			{
				qyd=0;   //欠压指示
				delay(1000);
				diqynum=3;
				P1M0=0x87; //00000111
				P1M1=0xc9; //00000111
				fz_off;//欠压后关闭负载
				fzd=1;
				flag_fz=0;
				while(!(Ad_Av(1)>=qyhf))
				{  //等待欠压恢复
					checkpv();//检测电池板
					if(flag_pv==1)
					{
						pwm_1();   //打开充电
						cdd=0;   //打开充电指示
					}
					fcd_z();//检测按键
					fcd_j();
					func();
					diqynum--;
					if(diqynum>0)//报警指示
					{
						didi(3);
						delay(1000);
					 }
					else
						diqynum=1;
				}
				didi(1);
				fz_on; //欠压恢复时重新开启负载
				delay(1);
				fzd=0;
				P1M0=0x8f; //00000111
				P1M1=0xc1; //00000111
				flag_fz=1;
				delay(1000);
				qyd=1;
			} 
			if(v_temp>gygd)    //判断是否过压
			{
				digynum=3;
				gyd=0;
				P1M0=0x87; //00000111
				P1M1=0xc9; //00000111
				fz_off;   //过压后关闭负载
				fzd=1;
				flag_fz=0;
				while(!(Ad_Av(1)<=gyhf))
				{//等待过压恢复
					fcd_z();//按键检测
					fcd_j();
					func();
					digynum--;
					if(digynum>0)//报警指示
					{
						didi(3);
						delay(1000);
					 }
					else
						digynum=1;
				}	
				didi(1);
				fz_on;//过压恢复时开启负载
				delay(1);
				fzd=0;
				P1M0=0x8f; //00000111
				P1M1=0xc1; //00000111
				flag_fz=1;
				delay(1000);
				gyd=1;
		 	}
		} 
		checkpv();//检测电池板电压
		checkgz();//检测过载状态
		fcd_z();//按键检测
		fcd_j();
		func();
	 };	
}


