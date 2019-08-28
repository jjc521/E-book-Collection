#include"STC12C5410AD.H"   	//STC12C54系列单片机头文件
#define uchar unsigned char
#define uint unsigned int 
void delayms(uint xms)				
{
	uint i,j;
	for(i=xms;i>0;i--)		      //i=xms即延时约xms毫秒
		for(j=110;j>0;j--);
}
void AD_Init()
{
	P1M0=0x0f;//0000 1111 设置P1口低4位为开漏模式，用来AD采集
	P1M1=0x0f;//0000 1111
	ADC_CONTR=0xe0;//1110 0000 开启AD转换器电源，设置最高转换速度
	delayms(100);
}
int GetAD(unsigned char channel) //channel为要取的通道号(0~7)
{
	unsigned char AD_finished=0;
	int result;
	ADC_CONTR|=channel;   //选择AD通道号
	ADC_CONTR|=0x08;      //启动AD转换
	while(AD_finished==0) //等待AD转换结束
	{
		AD_finished=(ADC_CONTR&0x10);//查询ADC_FLAG位是否置1
	}
	result=ADC_DATA*4+ADC_LOW2;//读走AD转换结果，由于ADC_DATA中存储12位中的
	//高8位，当要转换成10进制时，需将ADC_DATA中的数左移2位，即相当于*4
	ADC_CONTR&=0xf7;     //清除转换结束标志
	return (result);    //返回结果给函数
}
float Ad_Av(uchar channel)    //求100次采集电压的平均值
{
	float Val_Av=0;
	uchar num;
	for(num=100;num>0;num--)
	{
		Val_Av+=GetAD(channel);//100次采集求和
	}
	Val_Av/=100.0;            //求平均值
	Val_Av=Val_Av*5.0/1024;  //单片机电源为5V，求的真实电压值
	return (Val_Av);          //返回给函数
}
void main()
{
	float ad1,ad2,ad3,ad4;
	AD_Init();
	ad1=Ad_Av(1);
	ad2=Ad_Av(2);
	ad3=Ad_Av(3);
	ad4=Ad_Av(4);
	while(1);
}
