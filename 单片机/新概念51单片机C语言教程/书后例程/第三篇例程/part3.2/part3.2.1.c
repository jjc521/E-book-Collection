#include<reg52.h>
#define uchar unsigned char
#define uint unsigned int 
void delayms(uint xms)				
{
	uint i,j;
	for(i=xms;i>0;i--)		      //i=xms¼´ÑÓÊ±Ô¼xmsºÁÃë
		for(j=110;j>0;j--);
}
void main()
{
	SCON=0;
	EA=1;
	ES=1;
	TI=0;
	while(1)
	{
		SBUF=0xaa;
		delayms(1);
	}
}

void ser0() interrupt 4
{
	TI=0;
}
