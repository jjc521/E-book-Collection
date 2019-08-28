#include <reg52.h>
#include <stdio.h>
#define  uchar unsigned char
#define  uint  unsigned int
sbit ds=P2^2;     //温度传感器信号线
sbit dula=P2^6;   //数码管段选线
sbit wela=P2^7;   //数码管位选线
sbit beep=P2^3;   //蜂鸣器

uint temp;
float f_temp;
uint warn_l1=260;
uint warn_l2=250;
uint warn_h1=300;
uint warn_h2=320;

sbit led0=P1^0;
sbit led1=P1^1;
sbit led2=P1^2;
sbit led3=P1^3;

unsigned char code table[]={
0x3f,0x06,0x5b,0x4f,
0x66,0x6d,0x7d,0x07,
0x7f,0x6f,0xbf,0x86,
0xdb,0xcf,0xe6,0xed,
0xfd,0x87,0xff,0xef};     //不带小数点的编码

void delay(uint z)//延时函数
{
	uint x,y;
	for(x=z;x>0;x--)
		for(y=110;y>0;y--);
}



void dsreset(void)    //18B20复位，初始化函数
{
  uint i;
  ds=0;
  i=103;
  while(i>0)i--;
  ds=1;
  i=4;
  while(i>0)i--;
}

bit tempreadbit(void)   //读1位函数
{
   uint i;
   bit dat;
   ds=0;i++;          //i++ 起延时作用
   ds=1;i++;i++;
   dat=ds;
   i=8;while(i>0)i--;
   return (dat);
}

uchar tempread(void)   //读1个字节
{
  uchar i,j,dat;
  dat=0;
  for(i=1;i<=8;i++)
  {
    j=tempreadbit();
    dat=(j<<7)|(dat>>1);   //读出的数据最低位在最前面，这样刚好一个字节在DAT里
  }
  return(dat);
}

void tempwritebyte(uchar dat)   //向18B20写一个字节数据
{
  uint i;
  uchar j;
  bit testb;
  for(j=1;j<=8;j++)
  {
    testb=dat&0x01;
    dat=dat>>1;
    if(testb)     //写 1
    {
      ds=0;
      i++;i++;
      ds=1;
      i=8;while(i>0)i--;
    }
    else
    {
      ds=0;       //写 0
      i=8;while(i>0)i--;
      ds=1;
      i++;i++;
    }

  }
}

void tempchange(void)  //DS18B20 开始获取温度并转换
{
  dsreset();
  delay(1);
  tempwritebyte(0xcc);  // 写跳过读ROM指令
  tempwritebyte(0x44);  // 写温度转换指令
}

uint get_temp()         //读取寄存器中存储的温度数据
{
  uchar a,b;

  dsreset();
  delay(1);
  tempwritebyte(0xcc);
  tempwritebyte(0xbe);
  a=tempread();         //读低8位
  b=tempread();         //读高8位
  temp=b;
  temp<<=8;            //两个字节组合为1个字
  temp=temp|a;
  f_temp=temp*0.0625;      //温度在寄存器中为12位 分辨率位0.0625°
  temp=f_temp*10+0.5;    //乘以10表示小数点后面只取1位，加0.5是四舍五入
  f_temp=f_temp+0.05; 
  return temp;         //temp是整型
}


////////////////////显示程序//////////////////////////
void display(uchar num,uchar dat)
{
  uchar i;
  dula=0;
  P0=table[dat];
  dula=1;
  dula=0;

  wela=0;
  i=0XFF;
  i=i&(~((0X01)<<(num)));
  P0=i;
  wela=1;
  wela=0;    
  delay(1);
}

void dis_temp(uint t)
{
  uchar i;
  i=t/100;
  display(0,i);
  i=t%100/10;
  display(1,i+10);
  i=t%100%10;
  display(2,i);
}
//////////////////////////////////////////////
void warn(uint s,uchar led)   //蜂鸣器报警声音 ,s控制音调
{
    uchar i;i=s;
    dula=0;
    wela=0;
 
	beep=0;
    P1=~(led);
    while(i--)
    {
      dis_temp(get_temp());
    }   
	beep=1;
    P1=0XFF;  
    i=s;  
     while(i--)
    {
      dis_temp(get_temp());
    }  
}
void deal(uint t)
{
  uchar i;
  if((t>warn_l2)&&(t<=warn_l1)) //大于25度小于27度
	{
       warn(40,0x01);
       
	}
  else if(t<=warn_l2)                   //小于25度 
	{
       warn(10,0x03);
	}
  else if((t<warn_h2)&&(t>=warn_h1)) //小于32度大于30度
    {
       warn(40,0x04);
	}
  else if(t>=warn_h2)                   //大于32度
	{
       warn(10,0x0c);
	}
  else
    {
       i=40;
       while(i--)
       {
        dis_temp(get_temp());
       } 
    }
}

void init_com(void)
{
     TMOD = 0x20;
     PCON = 0x00;
     SCON = 0x50;
     TH1 = 0xFd;
     TL1 = 0xFd;
     TR1 = 1;
}

void comm(char *parr)         
{
	do
	{
	 SBUF = *parr++;                                                           //发送数据                          
     while(!TI);                                                               //等待发送完成标志为1
	 TI =0;                                                                    //标志清零
	}while(*parr);                                                             //保持循环直到字符为'\0'
}

void main()
{
  uchar buff[4],i;
  dula=0;
  wela=0;
  init_com();
  while(1)
 {    
      tempchange();
      for(i=10;i>0;i--)
     {
      dis_temp(get_temp());}
      deal(temp); 

      sprintf(buff,"%f",f_temp);

    for(i=10;i>0;i--)
     {
      dis_temp(get_temp());}

      comm(buff);

     for(i=10;i>0;i--)
     {
      dis_temp(get_temp());}
    
 }
}
