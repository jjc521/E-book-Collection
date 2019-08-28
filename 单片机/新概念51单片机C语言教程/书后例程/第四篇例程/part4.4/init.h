void didi(uchar di_num) 
{ //蜂鸣器响几次由di_num决定
	uchar a;
	for(a=di_num;a>0;a--)
	{     
		beep=1;
		delay(400);
		beep=0;
		delay(400);	
	}
}
void init()
{
	qyd=1;    //指示灯初始化
	gyd=1;
	cdd=1;
	fzd=1;
	zcd=1;
	beep=0;
	czfz=1;   //负载关闭
	czcf=0;   //关闭充电
	diqynum=0; 
	digynum=0;
	flag_pv=0;
	flag_fun=0;
	flag_t1=0;
	flag_gz=0;
	flag_t1gz=0;
	pwm_num=2;
	pwm_a=30;
	fcd=13.7;
	cwfc=13.7;
	dwfc=14.1;
	gwfc=13.3;
	gzdy=0.45; //设定负载过载电压为0.45V
	cd_off;
	t1_num=0;
	t1_numgz=0;
	P1M0=0x87;
	P1M1=0x49;
	fz_off;
	delay(1);
	P1M0=0x8f;
	P1M1=0x41;
	didi(1);
	delay(6000);
	if(byte_read(0x2e06)==1)//当改变过浮充电压点后重新读取
	{
		cwfc=read_eep(0x2e00);
		fcd=cwfc;		
	}
	if(byte_read(0x2c06)==1)//当改变过浮充电压点后重新读取
	{
		gzdy=byte_read(0x2c00)/100.0;
	} 
	TMOD=0x12;
	IP=0x08;
	TH0=(256-115); //定时器初始化周期为115US，PWM频率为34HZ
	TL0=(256-115);
	TH1=(65536-50000)/256; //定时器初始化
	TL1=(65536-50000)%256;
	ET0=1;
	ET1=1;
	TR1=1;
	TR0=1;
	EA=1;
	CMOD=0x04;                  //设置为PWM输出方式
	CCAPM0=0x42;                 //
	CL=0;                       //PWM计数器初值清0
	CH=0;
	ADC_CONTR|=0xe0;   //打开AD电源
	P1M0=0x87;
	P1M1=0x49;
	fz_on;
	delayus(5);
	flag_fz=1;
	fzd=0;
	P1M0=0x8f; //设置为AD采样模式
	P1M1=0x41;
	didi(1);	
	checkgz();
	checkpv();
}
void delay(uint x)//延时为1ms的整数倍，由x决定
{
	uint y,z;
	for(y=x;y>0;y--)
		for(z=110;z>0;z--);
}
void delayus(uchar x)//延时为1us的整数倍，由x决定
{
	uchar y;
	for(y=x;y>0;y--);
}
