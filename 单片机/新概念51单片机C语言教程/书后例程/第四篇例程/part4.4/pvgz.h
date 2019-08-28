void pwm_zk(uchar gao)  
{//脉宽调制 gao为高电平持续时间最大255，最小1
	PCA_PWM0=0;
	CCAP0H=(256-gao);
	CR=1;		
}
void pwm_1()  // PWM端固定高电平
{
	PCA_PWM0=0;
	CCAP0H=0;
}
void pwm_0()  //PWM端固定低电平
{
	PCA_PWM0=0x03;
	CCAP0H=0xff;
}
void checkpv()//检测电池板电压
{
	//省去检测电池板程序	
}
void checkgz()
{
	float temp_gz;
	if(flag_fz==1)
	{
		temp_gz=Ad_fu(4);
		if(temp_gz>gzdy)    
		{ //判断是否过载 注意：只有在前面过程负载打开的情况下  
          //方可判断负载是否过载，否则将不做判断。
			P1M0=0x87; //00000111
			P1M1=0x49;
			fz_off;
			didi(1);
			flag_fz=0;
			fzd=1;
			flag_gz=1;
			flag_t1gz=0;		
	 	}
		if(temp_gz>(gzdy-0.02))
		{//快过载前的报警提示
			didi(1);
		}
	}
	//这里省去过载恢复检测程序	
}
