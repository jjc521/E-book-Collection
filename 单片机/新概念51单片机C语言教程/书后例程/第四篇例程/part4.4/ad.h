float GetAD(uchar channel)//用户函数
{
	unsigned char AD_finished=0;
	float tad_val;
	tad_val=0;
	ADC_CONTR|=(channel-1); //选择AD端口号
	ADC_DATA=0;
	ADC_LOW2=0;
	ADC_CONTR|=0x08;   //启动AD转换
	while(AD_finished==0){
		AD_finished=(ADC_CONTR&0x10);
	}
	tad_val=(ADC_DATA*4+ADC_LOW2);
	ADC_CONTR&=0xe0;
	return (tad_val);
}
float Ad_Av(uchar chan)
{//求蓄电池电压平均值
	float Val_Av;
	uchar num;
	Val_Av=0;
	for(num=120;num>0;num--)
	{
		Val_Av+=GetAD(chan);
	}
	Val_Av/=120.0;
	Val_Av=Val_Av*15.0/1024;
	return (Val_Av);
}
float Ad_fu(uchar chan)
{//求其它电压平均值
	float Val_Av;
	uchar num;
	Val_Av=0;
	for(num=5;num>0;num--)
	{
		Val_Av+=GetAD(chan);
	}
	Val_Av/=5.0;
	Val_Av=Val_Av*5.0/1024;
	return (Val_Av);
}