#include <reg52.h>

#define uchar unsigned char 

sbit dula=P2^6;
sbit wela=P2^7;

sbit dianji=P1^7;

sbit jia_key=P3^6;
sbit jian_key=P3^7;

uchar num=0,show_num=1,gao_num=1,di_num=3;
uchar code table[]={0x3f,0x06,0x5b,0x4f,0x66,0x6d,0x7d,
                        0x07,0x7f,0x6f,0x77,0x7c,0x39,0x5e,0x79,0x71};
void delay(uchar i)
{
  uchar j,k;
  for(j=i;j>0;j--)
    for(k=125;k>0;k--);
}
void display()
{
   dula=0;
   P0=table[show_num];
   dula=1;
   dula=0;
   
   wela=0;
   P0=0xfe;
   wela=1;
   wela=0;
   delay(5);
   
   P0=table[0];
   dula=1;
   dula=0;
   
   P0=0xfd;
   wela=1;
   wela=0;
   delay(5);

   P0=table[0];
   dula=1;
   dula=0;
   
   P0=0xfb;
   wela=1;
   wela=0;
   delay(5);

   P0=table[0];
   dula=1;
   dula=0;
   
   P0=0xf7;
   wela=1;
   wela=0;
   delay(5);
}
void key ()
{
   if(jia_key==0)
   {
     delay(5);
	 if(jia_key==0)
	 {
	   num++;
	   if(num==4)
	     num=3;	
	 	 while(jia_key==0);
	 }
   }

   if(jian_key==0)
   {
     delay(5);
	 if(jian_key==0)
	 {
        if(num!=0)	  
         num--;
		 else 
		 num=0;
		 while(jian_key==0);
	 }
   }
}

void dispose()
{
  switch(num)
  {
    case 0:
     show_num=1;
	 gao_num=1;
	 di_num=3;
	 break;
	case 1:
	 show_num=2;
	 gao_num=2;
	 di_num=2;
	break;
	case 2:
	 show_num=3;
	 gao_num=3;
	 di_num=1;
	break;
	case 3:
	 show_num=4;
	 gao_num=4;
	 di_num=0;
	break;
  }
}
void qudong()
{
  uchar i;
  if(di_num!=0)
  {
    for(i=0;i<di_num;i++)
	{
	  dianji=0;
	  display();
	}
  }

  for(i=0;i<gao_num;i++)
  {
    dianji=1;
	display();
  }
}

void main()
  {
     while(1)
       {
         dianji=0;
		 key();
		 dispose();
		 qudong();
         }

    }
 
