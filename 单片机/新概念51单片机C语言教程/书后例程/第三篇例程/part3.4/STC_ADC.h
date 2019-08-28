sfr P1_ADC_EN=0x97;
sfr ADC_CONTR=0xc5;
sfr ADC_DATA=0xc6;


int GetAD(unsigned char channel)		//用户函数，channel为要取的通道号(0~7)
{
	unsigned char AD_finished=0;
   // AD_Init(1<<channel);
	ADC_DATA=0;
	ADC_CONTR=channel;
	delay(1000);
	ADC_CONTR|=0x08;
	AD_finished=0;
	while(AD_finished==0){
		AD_finished=(ADC_CONTR&0x10);
	}
	ADC_CONTR&=0xF7;
	return (ADC_DATA);
}


void AD_Init(unsigned char ADin)		// ADC 初始化,ADin为八位2进制数，分别对应AD7~0，置1代表打开此路
{
	P1=P1|ADin;
	P1_ADC_EN=0x63;
}
