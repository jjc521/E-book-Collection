#include <reg52.h> 
#include <stdlib.h>
#define uint unsigned int 
#define uchar unsigned char
sbit CS=P1^2; 
sbit SID=P1^1; 
sbit SCLK=P1^0;
uchar disps[10];
uchar code dispx[]={"我爱单片机!"};

void delay_1ms(uint x) 
{ 
uint i,j; 
for(j=0;j<x;j++)  
	for(i=0;i<110;i++); 
}
void send_command(uchar command_data) 
{ 
	uchar i; 
	uchar i_data;
	i_data=0xf8; 
	CS=1; 
	SCLK=0; 
	for(i=0;i<8;i++) 
		{ 
			SID=(bit)(i_data&0x80); 
			SCLK=0; 
			SCLK=1; 
			i_data=i_data<<1; 
		} 
	i_data=command_data; 
	i_data&=0xf0;
	for(i=0;i<8;i++) 
		{ 
			SID=(bit)(i_data&0x80); 
			SCLK=0; 
			SCLK=1; 
			i_data=i_data<<1; 
		} 
	i_data=command_data; 
	i_data<<=4;
	for(i=0;i<8;i++) 
		{ 
			SID=(bit)(i_data&0x80); 
			SCLK=0; 
			SCLK=1; 
			i_data=i_data<<1; 
		} 
	CS=0; 
	delay_1ms(10); 
} 
void send_data(uchar command_data) 
{ 
	uchar i; 
	uchar i_data;
	i_data=0xfa;  
	CS=1; 
	for(i=0;i<8;i++) 
		{ 
			SID=(bit)(i_data&0x80); 
			SCLK=0; 
			SCLK=1; 
			i_data=i_data<<1;  
		} 
	i_data=command_data; 
	i_data&=0xf0; 
	for(i=0;i<8;i++) 
		{ 
			SID=(bit)(i_data&0x80); 
			SCLK=0; 
			SCLK=1; 
			i_data=i_data<<1; 
		} 
	i_data=command_data;
	i_data<<=4; 
	for(i=0;i<8;i++) 
		{ 
			SID=(bit)(i_data&0x80); 
			SCLK=0; 
			SCLK=1; 
			i_data=i_data<<1; 
		} 
	CS=0; 
	delay_1ms(10);  
}
void lcd_init() 
{ 
	delay_1ms(100); 
	send_command(0x30); /*设置8位数据接口，基本指令模式。*/ 
	send_command(0x02); /*清DDRAM*/ 
	send_command(0x06); /*游标及显示右移一位*/  
	send_command(0x0c); /*整体显示开，游标关，反白关*/ 
	send_command(0x01); /*写入空格清屏幕*/ 
	send_command(0x80); /*设定首次显示位置*/ 

}
void display_s()
{
	uchar a;
	send_command(0x80);
	for(a=0;a<10;a++)
	{
		send_data(disps[a]);		
	}
}
void display_x() 
{ 
	uchar a;
	send_command(0x92);
	for(a=0;a<11;a++)
	{
		send_data(dispx[a]);		
	} 
}
void makerand()
{
	uint ran;
	ran=rand();
	disps[0]=ran/10000+0x30;	
	disps[1]=ran%10000/1000+0x30;
	disps[2]=ran%1000/100+0x30;
	disps[3]=ran%100/10+0x30;
	disps[4]=ran%10+0x30;
	ran=rand();
	disps[5]=ran/10000+0x30;	
	disps[6]=ran%10000/1000+0x30;
	disps[7]=ran%1000/100+0x30;
	disps[8]=ran%100/10+0x30;
	disps[9]=ran%10+0x30;

}
main() 
{ 
	lcd_init(); 
	display_x();
	while(1)
	{
		makerand();
		display_s();
		delay_1ms(100); 
	}
	while(1); 
}