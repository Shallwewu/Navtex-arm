#include "code.h"
//#include "define.h"
#include "inc.h"
#include "stm32f2xx.h"
//-----------------jietiao.c----------------------------------------------------------------------------------
//int TEMP[1600];
//int JietiaoBlcok[DemodulateBuffer];	//分别存放两个通道采样数据
//volatile byte ReceiverarrayNow[9100];

//volatile unsigned char Receivearray[2][ReceiveMax], ReceivePeriod[2]={0,0};
//Receivearray为解调的存储数组，ReceivePeriod[2]表示对应两个通道当前存储字节存储了几个码元
//volatile int  Receivenm[2]={0,0},Pfirst[2]={0,0};
//Receivenm[2]表示对应通道解调存储数组的数目，Pfirst表示由于每次接收80个AD转换数据送入解调，开始解调的数据在接收缓冲区的位置

 

volatile char Dingxiang[2]={0,0};		//分别对应两个通道定向情况，0未定向，1定向
//volatile char Dingxiangmount[2]={0,0};	//分别对应两个通道定向信息中所接收的bit数

//volatile word Jietiaomount=0;		//解调的字符数，包括所有的信息
//volatile word Jietiaomounttemp=0;	//当前信息未解码的字节数
volatile short int Jiemamount=0;			//整条信息解码完毕的字节数
volatile short int Jiemamounttemp=0;		//本次解码的字节数
volatile word mesend=0;
//volatile word oldJiemamount;
//volatile word wumamount;
volatile char Antenna=0;				//0此时正常解调，1用于检测天线连接	
volatile char AntennaResult=0;		//天线检测结果，0正常，1未检测到天线
//volatile unsigned char Rxstation[16][26][14];
//-------------------lcddrive.c--------------------------------------------------------------
volatile byte SYSTAB[8]={0x30,0x87,0x07,0x28,0x42,0xf0,0x29,0x00};
volatile byte SCRTAB[10]={0x00,0x00,0xf0,0xce,0x04,0xf0,0x80,0x00,0x00,0x00};
volatile byte CTAB[40];
//-----------------boot.c-------------------------------
volatile signed char TimeLeft;
//others.c
volatile char Antennaing=0;	//辅助天线自检结果存储的变量，当开始自检置1，自检完成置0
//printer.c
volatile PrtLink *PrtStart;
//volatile int print_list[600];
volatile short int print_sum=0;
//message.c
volatile word LINE;									//统计所显示信息的总行数
/***********************************/
/****Time.c中用于定向信号判断****/
/*volatile uint32 DxRx[14]=
{
	0x67e19f86,0xcfc33f0c,0x9f867e19,0x3f0cfc33,0x7e19f867,0xfc33f0cf,0xf867e19f,0xf0cfc33f,0xe19f867e,0xc33f0cfc,0x867e19f8,0x0cfc33f0,0x19f867e1,0x33f0cfc3
};*/
//volatile uint32 DxRxReceive[2]={0x0000,0x0000};	//定向位的存储位
volatile byte flag_more_message=0;
volatile byte Flashmap[300];
//volatile int Messagetoprank[600];   
volatile byte Eprommap[75];
volatile Messageinfotype Messageinfo;	
//Messagetoptype Messagesavetop[600];	   
//Messagetoptype Messagetemptop;	
volatile byte FLAG;	
Messagetoptype Messagetemptop;
volatile short int Messagenownumber;
volatile u8 G_Key=0;
short int Messagetoprank[600];
Messagetoptype msgtop;
volatile word Unread;	
volatile word STATE;				//记录当前的状态                         
volatile byte State1parameter;  	//信息界面的入口参数
volatile byte State2parameter;  	//存储界面和锁定界面的公用入口参数
volatile byte State200parameter;	//存储菜单下打印复选和锁定复选菜单的入口参数
volatile byte State2000parameter;   //存储和锁定菜单下的锁定和解锁确认的公用全局变量
volatile byte State202parameter;	//存储界面和锁定界面下排序菜单公用界面


volatile byte State13parameter;	    //打印菜单的入口参数
volatile byte State14parameter;	    //锁定超量菜单的入口参数
volatile byte State300parameter;	//锁定菜单下锁定复选菜单状态300，全局变量
volatile byte State4parameter;  	//主菜单的入口参数
volatile byte State400parameter;	//自动模式入口参数
volatile byte State401parameter;	//手动模式入口参数
volatile byte State4000parameter;   //自动模式和手动模式的公共子界面入口参数
volatile byte State41parameter;  	//信息类别入口参数
volatile byte State44parameter; 	//维护菜单入口参数
volatile char flag_s;			//信息提示标志，当flag_s为1时，显示提示符号；否则flag_s为0时，清除提示符号
//volatile char counter_flag_s;	//信息提示标志计数
volatile char Mode;				//记录当前处在何种模式，0表示自动，1表示手动
volatile char Workfre;			//记录当前的工作频率，0选择518/4209.5，1选择518/486
volatile char LANGUAGE;			//区分中英文操作模式，1是中文，0是英文
volatile char flag_new_message;
volatile byte msgover;
volatile byte whichchannel;
//volatile word Jiemamounte=0;
//volatile word Jiemamountc=0;
volatile word BUFFER[10];   	//第一级菜单，每级菜单在跳出后必须清零，在跳入子菜单则无需改变
volatile word BUFFER1[10];	    //第二级菜单
volatile word BUFFER2[10];  	//第三级菜单
volatile word BUFFER3[10];  	//第四级菜单
volatile word BUFFER4[10];  	//第五级菜单
volatile word BUFFERPRO[10];    //第一级菜单的保护用于信息存储界面和信息锁定届面到信息内容菜单切换时保护
volatile short int BUFFERSELECT[22]; 	//专用于公用复选界面Savelocksubmenu的参数保护
volatile word BUFFERPRINT;   	//专用于打印确定界面MessageSubmenu的参数保护
volatile short int BUFFERSELECTLOCK; 	//专用于锁定复选界面参数的保护
volatile byte CTAB1[40];	//液晶中显示一行的字符
volatile byte CGTAB[2][16]; //液晶中显示一个汉字
volatile short int Selectsubback; 		//用于进入复选界面的界面参数保护
volatile char Selectreturn;  		//用于复选界面的出口参数保护
volatile short int Mulnownumber; 			//作为复选界面的当前所在信息条数
volatile short int Returnback;  			//用于存储界面和锁定界面公用的入口参数保护
volatile short int Messagenumber; 		//用于存储界面和锁定界面中总信息数的记录
volatile char Rankback; 			//用于排序公共界面的入口参数保护
volatile char Returntype;       	//表示是从何界面进入信息内容界面，10表示子界面进入
				  	                //1返回到存储，2返回到锁定,
volatile char PublicReturn;     	//用于公共界面的入口参数
volatile char PitchDAPro;       	//批处理界面入口参数保护
volatile byte subback;				//表明是否从子菜单返回，10表示弹出子菜单
volatile char number;          		//本地时间调整量
volatile char sign;            		//调整量的正负号
volatile char lcontrol;         	//用来记录本地时间是否开

byte iyear;
byte imonth;
byte iday;
volatile byte ihour;
volatile byte iminute;
volatile char Buzzer[4];			//依次表示四种蜂鸣的开关情况
volatile char Buzzerstate=0;		//表明此时蜂鸣处于何种状态，Bit0标记重要信息，Bit1标记接收机故障
volatile char Contrast;				//表示对比度的选择
volatile char Backlight;			//0表示high，1表示medim，2表示low
Diagresulttype Diaglog[10];         //用于记录自检日志的结果，共十组
volatile char Diaglogs;				//用于记录但前可写日志在Diagresult[]中位置
volatile char Diaglogn;				//用于记录日志的条数
//char *LinePoint[200];       	//一条英文信息在LCD中所显示第一行到140行内容的字符
//unsigned int *LinePoint2[200];	//一条中文信息在LCD中所显示第一行到140行内容的字符
volatile word Auto[3][26]; 			//自动配置参数，0表示接收
volatile word Autotemp[3][26];		//自动配置临时参数
volatile char Manual[3][26];		//手动配置参数，0表示接收
volatile char Manualtemp[3][26];	//手动配置临时参数
volatile char MSGTYPE[3][26];		//信息类别配置参数，0表示接收
volatile char MSGTYPETEMP[3][26];	//信息类别临时配置参数
volatile char backpage = 0;			//0表示信息正文，1表示存储，2表示锁定，3表示时间位置； 

volatile char manual_area_temp;
volatile char manual_area;
volatile short int Msglockrank[150];  	//专用于Savemenu(此时用作锁定菜单)及其子菜单，每次进入都需要更新
volatile Checkinfotype Checkinfo;				//存储自检参数
volatile char Receiverset[5];    	//0表示误码率，以下数据依次
volatile byte now_printing;         //0打印完 1正在打印 
volatile byte parameter;
volatile short int print_list[600];
volatile short int auto_area;	//自动海区
volatile short int Jiemamounte=0;			//整条信息解码完毕的字节数
volatile short int Jiemamountc=0;			//整条信息解码完毕的字节数
volatile unsigned char maske=0;
volatile unsigned char maskc=0;
volatile char counter_flag_se=0;	//信息提示标志计数
volatile char counter_flag_sc=0;	//信息提示标志计数
volatile short int readMesEnd;
volatile short int readMesMount;
volatile timetype timestruct;
