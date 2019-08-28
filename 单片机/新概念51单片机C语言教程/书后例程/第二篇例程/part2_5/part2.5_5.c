#include <reg51.h>
#include <intrins.h>
#include <stdlib.h>	
#define uchar unsigned char
#define uint  unsigned int
/* 端口定义*/
#define LCD_data  P0             //数据口
sbit LCD_RS  =  P3^5;            //寄存器选择输入 
sbit LCD_RW  =  P3^6;            //液晶读/写控制
sbit LCD_EN  =  P3^4;            //液晶使能控制
sbit LCD_PSB =  P3^7;            //串/并方式控制
sbit wela    =  P2^6;
sbit dula    =  P2^7;
uchar dis1[10]; 
uchar code dis2[] = {"www.txmcu.com"};
uchar code dis3[] = {"天祥电子"};
uchar code dis4[] = {"--------"};
void delay_1ms(uint x) 
{ 
uint i,j; 
for(j=0;j<x;j++)  
	for(i=0;i<110;i++); 
}		
/*******************************************************************/
/*                                                                 */
/*写指令数据到LCD                                                  */
/*RS=L，RW=L，E=高脉冲，D0-D7=指令码。                             */
/*                                                                 */
/*******************************************************************/
void write_cmd(uchar cmd)
{                          
    LCD_RS = 0;
    LCD_RW = 0;
    LCD_EN = 0;
    P0 = cmd;
	delay_1ms(5);
    LCD_EN = 1;
	delay_1ms(5);
    LCD_EN = 0;  
}
/*******************************************************************/
/*                                                                 */
/*写显示数据到LCD                                                  */
/*RS=H，RW=L，E=高脉冲，D0-D7=数据。                               */
/*                                                                 */
/*******************************************************************/
void write_dat(uchar dat)
{                          
    LCD_RS = 1;
    LCD_RW = 0;
    LCD_EN = 0;
    P0 = dat;
	delay_1ms(5);
    LCD_EN = 1;
	delay_1ms(5);
    LCD_EN = 0;  
}
/*********************************************************/
/*                                                       */
/* 设定显示位置                                          */
/*                                                       */
/*********************************************************/
void lcd_pos(uchar X,uchar Y)
{                          
   uchar  pos;
   if (X==0)
     {X=0x80;}
   else if (X==1)
     {X=0x90;}
   else if (X==2)
     {X=0x88;}
   else if (X==3)
     {X=0x98;}
   pos = X+Y ;  
   write_cmd(pos);     //显示地址
}
void makerand()
{
	uint ran;
	ran=rand();
	dis1[0]=ran/10000+0x30;	
	dis1[1]=ran%10000/1000+0x30;
	dis1[2]=ran%1000/100+0x30;
	dis1[3]=ran%100/10+0x30;
	dis1[4]=ran%10+0x30;
	ran=rand();
	dis1[5]=ran/10000+0x30;	
	dis1[6]=ran%10000/1000+0x30;
	dis1[7]=ran%1000/100+0x30;
	dis1[8]=ran%100/10+0x30;
	dis1[9]=ran%10+0x30;

}
/*******************************************************************/
/*                                                                 */
/*  LCD初始化设定                                                  */
/*                                                                 */
/*******************************************************************/
void lcd_init()
{ 
    LCD_PSB = 1;         //并口方式  
    write_cmd(0x30);      //基本指令操作
    delay_1ms(5);
    write_cmd(0x0C);      //显示开，关光标
    delay_1ms(5);
    write_cmd(0x01);      //清除LCD的显示内容
    delay_1ms(5);
}
/*********************************************************/
/*														 */
/* 主程序           									 */
/*                                                       */
/*********************************************************/
main()
{
    uchar i;
    wela=0;
	dula=0;
    delay_1ms(10);                 //延时
    lcd_init();                 //初始化LCD             
    lcd_pos(1,0);             //设置显示位置为第二行的第1个字符
    i = 0;
    while(dis2[i] != '\0')
    {
       write_dat(dis2[i]);      //显示字符
       i++;
    }
 	lcd_pos(2,0);             //设置显示位置为第三行的第1个字符
    i = 0;
    while(dis3[i] != '\0')
    {
       write_dat(dis3[i]);      //显示字符
       i++;
    }
	lcd_pos(3,0);             //设置显示位置为第四行的第1个字符
    i = 0;
    while(dis4[i] != '\0')
    {
       write_dat(dis4[i]);      //显示字符
       i++;
    }
    while(1)
	{
		lcd_pos(0,0);   //设置显示位置为第一行的第1个字符
		makerand();
		for(i=0;i<10;i++)
		{
		    write_dat(dis1[i]);
		}
	}
}
