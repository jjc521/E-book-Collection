#include <reg52.h>    		//52系列单片机头文件
#define uchar unsigned char
#define uint unsigned int
#define SLAVE 0x02   		   /*从机地址*/
#define BN 16
uchar rbuf[16];
uchar code tbuf[16]={"master transmit"};

void err(void)
{ 
	SBUF=0xff;
	while(TI!=1);
	TI=0;
}
uchar master(uchar addr,uchar command)
{
	uchar aa,i,p;
	while(1)
  	{
		SBUF=SLAVE;  /* 发呼叫地址 */
   		while(TI!=1);
			TI=0;
   		while(RI!=1);
			RI=0;      	/* 等待从机回答 */
   		if(SBUF!=addr)
			err();    	/* 若地址错，发复位信号 */
     	else
		{                /* 地址相符 */
   			TB8=0;        /* 清地址标志 */
   			SBUF=command;     /* 发命令 */
  			while(TI!=1);
				TI=0;
  			while(RI!=1);
				RI=0;
			aa=SBUF;          /* 接收状态 */
  			if((aa&0x08)==0x08) /* 若命令未被接收,发复位信号 */
			{
				TB8=1;
				err();
			} 
  			else
			{
      			if(command==0x01) 	    /* 是发送命令 */
         		{
					if((aa&0x01)==0x01)  /* 从机准备好接收 */
            		{
						do
						{
                  			p=0;            /* 清校验和 */
                 			for(i=0;i<BN;i++)
                    		{
								SBUF=tbuf[i];   /* 发送一数据 */
                       			p+=tbuf[i];
								while(TI!=1);
								TI=0;
                       		}
                       		SBUF=p;      /* 发送校验和 */
                       		while(TI!=1);
								TI=0;
                       		while(RI!=1);
								RI=0;
                   		}while(SBUF!=0); /* 接收不正确，重新发送 */
                     	TB8=1;         /* 置地址标志 */
						return(0);
         			}
       				else
					{
            			if((aa&0x02)==0x02)   /* 是接收命令,从机准备好发送 */
 						{
							while(1) 
            				{
								p=0;              	/* 清校验和 */
				                for(i=0;i<BN;i++)
             					{
									while(RI!=1);
										RI=0;
				           			rbuf[i]=SBUF;  /* 接收一数据 */
					                p+=rbuf[i];
               					}
               					while(RI!=1);
									RI=0;
			                    if(SBUF==p) 
                   				{
									SBUF=0X00;   /* 校验和相同发"00" */
					                while(TI!=1);
										TI=0;
					                break;
        						}
         						else
             					{
									SBUF=0xff; 	/* 校验和不同发"0FF"，重新接收 */
					 	            while(TI!=1);
										TI=0;
         						}
       						} 
       						TB8=1;     	/* 置地址标志 */
							return(0);
     					}
    				}
   				}
  			}
 		}
	}
}		
void main()
{
	TMOD=0x20;                   /* T/C1定义为方式2 */
	TL1=0xfd;
	TH1=0xfd;                	/* 置初值 */
	PCON=0x00;
	TR1=1;
	SCON=0xf0;                  /* 串行口为方式3 */
	master(SLAVE,0x01);
	master(SLAVE,0x02);
	while(1);
}
