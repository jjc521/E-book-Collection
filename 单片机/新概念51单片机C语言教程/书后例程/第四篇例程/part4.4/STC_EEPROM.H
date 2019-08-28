/*
extern void SectorErase(uint sector_addr);	// 扇区擦除
extern uchar byte_read(uint byte_addr);		// byte读
extern void byte_write(uint byte_addr, uchar original_data);	// byte写
extern uchar byte_write_verify(uint byte_addr, uchar original_data);// byte写并校验
extern uchar ArrayWrite(uint begin_addr, uint len, uchar code *array);	// byte数组写并校验
extern void ArrayRead(uint begin_addr, uchar len);		// 读出, 保存在Ttotal[]中
*/
#define RdCommand		0x01
#define PrgCommand		0x02
#define EraseCommand     	0x03
#define Error   1
#define Ok      0
#define WaitTime	0x01
#define PerSector		512
/* ================ 打开 ISP,IAP 功能 ================= */
void ISP_IAP_enable(void)
{
	EA	=	0;							/* 关中断 		*/
	ISP_CONTR =	ISP_CONTR & 0x18;       /* 0001,1000	*/
	ISP_CONTR =	ISP_CONTR | WaitTime;	/* 写入硬件延时	*/
	ISP_CONTR =	ISP_CONTR | 0x80;       /* ISPEN=1		*/
}
/* =============== 关闭 ISP,IAP 功能 ================== */
void ISP_IAP_disable(void)
{
	ISP_CONTR	=	ISP_CONTR & 0x7f;	/* ISPEN = 0 */
	ISP_TRIG	=	0x00;
	EA			=   1;			/* 开中断 */
}
/* ================ 公用的触发代码 ==================== */
void ISPgoon(void)
{
	ISP_IAP_enable();			/* 打开 ISP,IAP 功能	*/
	ISP_TRIG	=	0x46;		/* 触发ISP_IAP命令字节1	*/
	ISP_TRIG	=	0xb9;		/* 触发ISP_IAP命令字节2	*/
	_nop_();
}
/* ==================== 字节读 ======================== */
unsigned char byte_read(unsigned int byte_addr)
{
	ISP_ADDRH = (unsigned char)(byte_addr >> 8);	/* 地址赋值	*/
	ISP_ADDRL = (unsigned char)(byte_addr & 0x00ff);

	ISP_CMD   = ISP_CMD	& 0xf8;			/* 清除低3位 	*/
	ISP_CMD   = ISP_CMD	| RdCommand;	/* 写入读命令	*/

	ISPgoon();							/* 触发执行		*/
	ISP_IAP_disable();				/* 关闭ISP,IAP功能	*/

	return (ISP_DATA);				/* 返回读到的数据	*/
}
/* ================== 扇区擦除 ======================== */
void sectorerase(unsigned int sector_addr)
{
	unsigned int iSectorAddr;
	iSectorAddr = (sector_addr & 0xfe00); /* 取扇区地址 */
	ISP_ADDRH = (unsigned char)(iSectorAddr >> 8);
	ISP_ADDRL = 0x00;

	ISP_CMD	= ISP_CMD & 0xf8;			/* 清空低3位 	*/
	ISP_CMD	= ISP_CMD | EraseCommand;	/* 擦除命令3 	*/

	ISPgoon();							/* 触发执行		*/
	ISP_IAP_disable();				/* 关闭ISP,IAP功能	*/

}
/* ==================== 字节写 ======================== */
void byte_write(unsigned int byte_addr, unsigned char original_data)
{
	ISP_ADDRH =	(unsigned char)(byte_addr >> 8); 	/* 取地址 	*/
	ISP_ADDRL =	(unsigned char)(byte_addr & 0x00ff);

	ISP_CMD	 = ISP_CMD & 0xf8;				/* 清低3位	*/
	ISP_CMD  = ISP_CMD | PrgCommand;		/* 写命令2	*/
	ISP_DATA = original_data;			/* 写入数据准备	*/

	ISPgoon();							/* 触发执行		*/
	ISP_IAP_disable();					/* 关闭IAP功能	*/
}
void write_eep(float eep_data,uint add)
{
	uchar fcdh,fcdl;
	fcdh=(uint)(eep_data*100)/256;
	fcdl=(uint)(eep_data*100)%256;
	byte_write(add,fcdh);//写入浮充电电压高8位
	byte_write(add+1,fcdl);//写入浮充电电压低8位
}
float read_eep(uint add)
{
	float date_re;
	uchar dateh,datel;
	dateh=byte_read(add);
	datel=byte_read(add+1);
	date_re=(dateh*256+datel)/100.0;
	return date_re;
}

