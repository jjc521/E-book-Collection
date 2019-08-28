#include <reg52.h>
#define uchar unsigned char
#define SLAVE  0x02
#define BN  16
uchar trbuf[16];
uchar rebuf[16];
bit tready;
bit rready;
void str(void);
void sre(void);
void main(void)
{ 
	TMOD=0x20;      /*T/C1定义为方式2*/
	TL1=0xfd;      	/*置初值*/
	TH1=0xfd;
	PCON=0x00;
	TR1=1;
	SCON=0xf0;     /*串行口为方式3*/
	ES=1;
	EA=1;         /*开串行口中断*/
	while(1)
	{
		tready=1;
		rready=1;
	}	/*假定准备好发送和接收*/
}
void ssio(void) interrupt 4
{ 
	uchar a;
	RI=0;
	ES=0;     	/*关串行口中断*/
	if(SBUF!=SLAVE)
	{
		ES=1;
		goto reti;
	}  	/*非本机地址,继续监听*/
	SM2=0;   /* 取消监听状态 */
	SBUF=SLAVE;   /* 从本地址发回 */
	while(TI!=1);
		TI=0;
	while(RI!=1);
		RI =0;
	if(RB8==1)
	{
		SM2=1;
		ES=1;
		goto reti;
	}/* 是复位信号，恢复监听 */
	a=SBUF;    /* 接收命令 */
	if(a==0x01)/* 从主机接收的数据 */
	{
		if(rready==1)
			SBUF=0x01;/* 接收准备好发状态 */
		else 
			SBUF=0x00;
		while(TI!=1);
			TI=0;
		while(RI!=1);
			RI=0;
		if(RB8==1)
		{
			SM2=1;
			ES=1;
			goto reti;
		} 
		sre();	/* 接收数据 */
	}
	else
	{
		if(a==0x02)	/* 从机向主机发送数据*/
		{
			if(tready==1)
				SBUF=0x02;	/* 发送准备好发状态 */
			else
				SBUF=0x00;
			while(TI!=1);
				TI=0;
			while(RI!=1);
				RI=0;
			if(RB8==1)
			{
				SM2=1;
				ES=1;
				goto reti;
			}
			str();/* 发送数据 */ 
		}
		else       
		{
			SBUF=0x80;  /* 命令非法 ，发状态 */
			while(TI!=1);
				TI=0;
			SM2=1;
			ES=1;  /* 恢复监听 */
		}
	}
	reti:;
}
void  str(void) 		/* 发数据块 */
{  
	uchar p,i;
	tready=0 ;
	do
	{
		p=0;/* 清校验和 */ 
	 	for(i=0;i<BN;i++) 
	 	{
			SBUF=trbuf[i];	/* 发送一数据 */
	    	p+=trbuf[i];
	    	while(TI!=1);
		    TI=0; 
	 	}
		SBUF=p;           			/* 发送校验和 */
		while(TI!=1);
			TI=0;
		while(RI!=1);
			RI=0;
	}while(SBUF!=0);/* 主机接收不正确，重新发送 */
	SM2=1;
	ES=1;
} 
void sre(void) /* 接收数据块 */
{  
	uchar p,i;
	rready=0 ;
	while(1) 
	{
		p=0;   		/* 清校验和 */ 
	    for(i=0;i<BN;i++) 
	    {
			while(RI!=1);
			RI=0;
	        rebuf[i]=SBUF;        	/* 接收数据 */
            p+=rebuf[i];
	    }
	    while(RI!=1);
		RI=0;
		if(SBUF==p)
		{
			SBUF=0x00;
			break;
		} 	/* 校验和相同发"00"*/
	  	else
		{
	    	SBUF=0xff;           		/* 校验和不同发"0FF"，重新接收 */
	    	while(TI==0);
			TI=0;
	     }
	  }
	SM2=1;
	ES=1;
} 
