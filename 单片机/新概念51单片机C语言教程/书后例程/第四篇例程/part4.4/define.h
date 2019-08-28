#define uint unsigned int
#define uchar unsigned char
#define qy     	     fcd-2.9//10.8   //欠压
#define qyhf   	     fcd-0.5//13.2   //欠压恢复
#define fcdy     	 fcd-0.128//13.2	//浮充电压
#define gddy     	 fcd+0.128//13.456	//关断电压
#define gyhf    	 fcd+0.9//14.6	//过压恢复
#define gygd    	 fcd+1.1//14.8	//过压关断
#define pvbt         0.5//当PV板电压大于电池1V左右时才可允许充电
#define jcjg         1200 //此数*50ms总和为检测电池板与过载恢复检测间隔时间单位（S）
#define jcgzjg       100  //过载后检测负载恢复间隔
#define fz_on		 czfz=0 //打开负载
#define fz_off       czfz=1 //关闭负载
#define cd_on		 czcf=1 //开始充电
#define cd_off       czcf=0 //关闭充电
sbit czfz=P1^3;            //控制负载
sbit czcf=P3^7;            //控制充电
sbit beep=P1^6;			   //蜂鸣器
sbit rs=P1^7;              //液晶数据命令
sbit lcden=P1^4;		   // 液晶使能
sbit qyd=P2^2;			   //欠压灯
sbit gyd=P2^3;		       //过压灯	
sbit fzd=P2^4;			   //负载灯
sbit cdd=P2^5;			   //充电灯
sbit zcd=P1^5;            //系统正常灯
sbit key1=P3^2;			 //按键定义
sbit key2=P3^3;
sbit key3=P3^4;
void delay(uint);
void delayus(uchar);
void didi(uchar);
void init();//以下为变量定义
uchar a,fz,diqynum,digynum,flag_t1gz,flag_gz;
uchar flag_t1,flag_pv,flag_fz,pwm_num,t1_numgz;
uchar pwm_a,flag_fun;
uint t1_num;
float xdata fcd,ad_val,v_temp,cwfc,dwfc,gwfc,gzdy;
