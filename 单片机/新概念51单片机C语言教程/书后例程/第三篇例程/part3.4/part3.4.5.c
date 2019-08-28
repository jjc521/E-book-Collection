#include <reg52.H>
#include <intrins.H>
// 定义与 ADC 有关的特殊功能寄存器
sfr P1_ADC_EN = 0x97; //A/D转换功能允许寄存器
sfr ADC_CONTR = 0xC5; //A/D转换控制寄存器
sfr ADC_DATA = 0xC6;  //A/D转换结果寄存器
typedef unsigned char INT8U;
typedef unsigned int INT16U;
void delay(INT8U delay_time) // 延时函数
{
	INT8U n;
	INT16U m;
	for (n=0;n<delay_time;n++)
		{
			for(m=0;m<10000;m++);
		}
}
void initiate_RS232(void)  //串口初始化
{
	ES = 0;   	   // 禁止串口中断
	SCON = 0x50;   // 0101,0000 8 位数据位， 无奇偶校验
	T2CON = 0x34;  // 0011，0100， 由T2 作为波特率发生器
	RCAP2H = 0xFF; // 时钟11.0592MHz, 9600 波特率
	RCAP2L = 0xDB;
	ES = 1;        // 允许串口中断
}
void Send_Byte(INT8U one_byte) // 发送一个字节
{
	TI = 0; 	// 清零串口发送中断标志
	SBUF = one_byte;
	while (TI == 0);
	TI = 0; 	// 清零串口发送中断标志
}
INT8U get_AD_result(INT8U channel)
{
	INT8U AD_finished = 0; // 存储 A/D 转换标志
	ADC_DATA = 0;
	ADC_CONTR = channel; // 选择 A/D 当前通道
	delay(1); 			//使输入电压达到稳定
	ADC_CONTR |= 0x08; //0000,1000 令 ADC_START = 1, 启动A/D 转换
	AD_finished = 0;
	while ( AD_finished == 0 ) // 等待A/D 转换结束
	{
		AD_finished = (ADC_CONTR & 0x10); //0001,0000, ADC_FLAG ==1 测试A/D 转换结束否
	}
	ADC_CONTR &= 0xF7; //1111,0111 令 ADC_START = 0, 关闭A/D 转换,
	return (ADC_DATA); // 返回 A/D 转换结果
}
void main()
{
	initiate_RS232();
	P1 = P1 | 0x63; // 0110,0011,要设置为 A/D 转换的P1.x 口,先设为高
	P1_ADC_EN = 0x63; //0110,0011, P1 的P1.0,P1.1,P1.5,P1.6 设置为 A/D 转换输入脚
	// 断开P1.0,P1.1,P1.5,P1.6 内部上拉电阻
	while(1)
	{
		Send_Byte(get_AD_result(0)); //P1.0 为 A/D 当前通道, 测量并发送结果
		delay(0x200);
		Send_Byte(get_AD_result(1)); //P1.1 为 A/D 当前通道, 测量并发送结果
		delay(0x200);
		Send_Byte(get_AD_result(5)); //P1.5 为 A/D 当前通道, 测量并发送结果
		delay(0x200);
		Send_Byte(get_AD_result(6)); //P1.6 为 A/D 当前通道, 测量并发送结果
		delay(0x200);
		Send_Byte(0); // 连续发送 4 个 00H, 便于观察输出显示
		Send_Byte(0);
		Send_Byte(0);
		Send_Byte(0);
		delay(0x200); // 延时
		delay(0x200);
		delay(0x200);
		delay(0x200);
		delay(0x200);
		delay(0x200);
	}
}