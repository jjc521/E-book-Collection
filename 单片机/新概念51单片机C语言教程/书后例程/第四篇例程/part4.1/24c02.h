bit  write=0;           //写24C02的标志；
sbit sda=P2^0;                         
sbit scl=P2^1;
void delay0()
{ ;; }
void start()  //开始信号
{	
	sda=1;
	delay0();
	scl=1;
	delay0();
	sda=0;
	delay0();
}
void stop()   //停止
{
	sda=0;
	delay0();
	scl=1;
	delay0();
	sda=1;
	delay0();
}
void respons()  //应答
{
	uchar i;
	scl=1;
	delay0();
	while((sda==1)&&(i<250))i++;
	scl=0;
	delay0();
}
void init_24c02()//IIC初始化函数
{
	sda=1;
	delay0();
	scl=1;
	delay0();
}
void write_byte(uchar date)//写一个字节函数
{
	uchar i,temp;
	temp=date;
	for(i=0;i<8;i++)
	{
		temp=temp<<1;
		scl=0;
	    delay0();
		sda=CY;
		delay0();
		scl=1;
		delay0();
	}
	scl=0;
	delay0();
	sda=1;
	delay0();
}
uchar read_byte()//读一个字节函数
{
	uchar i,k;
	scl=0;
	delay0();
	sda=1;
	delay0();
	for(i=0;i<8;i++)
	{
		scl=1;
		delay0();	
		k=(k<<1)|sda;
		scl=0;
		delay0();	
	}
	return k;
}
void write_add(uchar address,uchar date)//指定地址写一个字节
{
	start();
	write_byte(0xa0);
	respons();
	write_byte(address);
	respons();
	write_byte(date);
	respons();
	stop();
}
char read_add(uchar address)//指定地址读一个字节
{
	uchar date;
	start();
	write_byte(0xa0);
	respons();
	write_byte(address);
	respons();
	start();
	write_byte(0xa1);
	respons();
	date=read_byte();
	stop();
	return date;
}

