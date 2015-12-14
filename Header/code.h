#ifndef __code_H
#define __code_H

#include "define.h"
#include "inc.h"
extern volatile char MessageProcess;	/*用于记录信息处理的状态，当进行信息锁定或者信息解锁操作时，MessageProcess的bit0为1
此时若信息删除中断到来，则不进行信息删除操作，开启定时器0中断，并置MessageProcess的bit1为1，若解码完毕中断到来
则也不进行新信息添加操作，开启定时器0，并置MessageProcess的bit2为1,若同时接收信息需要进行替换则MessageProcess的
bit3位置1，若正在进行信息删除或者信息添加操作，则MessageProcess的bit4为1*/
/*       bit7	bit6	bit5	bit4	bit3	bit2	bit1	bit0
          |		 |		 |		 |		 |		 |		 |		 |-----当进行信息锁定或者信息解锁操作时，MessageProcess的bit0为1
          |		 |		 |		 |		 |		 |		 |-------------此时若信息删除中断到来，则不进行信息删除操作，开启定时器0中断，并置MessageProcess的bit1为1
          |		 |		 |		 |		 |		 |---------------------若解码完毕中断到来则也不进行新信息添加操作，开启定时器0，并置MessageProcess的bit2为1
          |		 |		 |		 |		 |-----------------------------若同时接收信息需要进行替换则MessageProcess的bit3位置1
          |		 |		 |		 |-------------------------------------若正在进行信息删除或者信息添加操作，则MessageProcess的bit4为1
          |		 |		 |---------------------------------------------未定义
          |		 |-----------------------------------------------------未定义
          |------------------------------------------------------------未定义  

bit[1]+bit[0]    一起组成信息删除中断跟信息锁定的处理
bit[4 3 2]+bit[0]一起组成解码中断跟信息锁定的处理
*/ 

//extern volatile int  EpromAddNow;		//用于记录当3天时间间距到时所应该处理的信息的EpromAdd的信息
//extern volatile char ThreeDayAlarm;		//用于记录当新信息存储是否需要设置3天时间的中断,1表示需要


/***********************************/
/****FILE SYSTEM****/
/***********************************/
extern volatile byte Flashmap[300]; 	//加载到内存的Flashmap使用情况，一个字节管4个块，2个bit管一个块，按从从右到左的顺序
						//空闲分区用00表示，已分配分区用11表示，非空闲但未分配分区用10表示
extern short int Messagetoprank[600];//存储信息的位置，排序的时候只需改动Messagetoprank即可，无需改动结构体Messagsavetop
extern volatile byte Eprommap[75];		//加载到内存的Eprommap使用情况，一个字节管8个块，1个bit管一个块，按从右到左的顺序
						//空闲分区用0表示，已分配分区用1表示
extern volatile Messageinfotype Messageinfo;			//存储接收机中信息相关参数
extern Messagetoptype Messagesavetop[600];		//存储信息头

extern Messagetoptype Messagetemptop;			//暂时存储信息头
extern volatile Checkinfotype Checkinfo;				//存储自检参数

/***********************************/
/****LCD for MessageDisplay****/
/***********************************/


extern char *LinePoint[300];	//一条英文信息在LCD中所显示第一行到140行内容的字符
extern unsigned short int *LinePoint2[300];	//一条中文信息在LCD中所显示第一行到140行内容的字符
/***********************************/
/****Demodulate.c****/
/***********************************/
extern char Block1[4500];			//接收存储来自FPGA的解码信息的动态Memory的首地址
extern volatile short int flag_valid;			//左右移位有效标志
extern char MessagePoint[4500];	//信息内容数组的指针
extern unsigned short int chinese[2000]; //存储中文LCD字库机内码
extern char PrtMsg[4500];			//所需打印信息内容数组
extern char PrtMsgChn[4000];
extern char receiver_state[500];
extern char receiver_alarm[100];
extern volatile char TempBlock;	//当前使用缓冲块的标志，1表示720~1439满，数据存入0~719，反之相同
extern volatile short int Stop[2];			//同步方法的标志位，2使用连续同步，1阈值方法同步（此时已进入定向），0不同步
extern volatile short int Num[2];			//在stop为1的情况下，间隔固定个数需要重新同步
extern volatile word Unread;				//总未读信息数
extern volatile JietiaoResulttype JietiaoResult[4];		//存储所需处理存储解调结果的结构体数组序列
//extern volatile char JietiaoState[4];			//依次存储所需处理结构体数组的序列，若无则为0
/***********************************/
/****Time.c中用于定向信号判断****/
//extern volatile uint32 DxRx[14];
//extern volatile uint32 DxRxReceive[2];	//定向位的存储位
/***********************************/
/****Public Parameters****/
/***********************************/

extern volatile word STATE;				//记录当前的状态                         
extern volatile byte State1parameter;	//信息界面的入口参数
extern volatile byte State2parameter;	//存储界面和锁定界面的公用入口参数
extern volatile byte State200parameter;	//存储菜单下打印复选和锁定复选菜单的入口参数
extern volatile byte State2000parameter;//存储和锁定菜单下的锁定和解锁确认的公用全局变量
extern volatile byte State202parameter;	//存储界面和锁定界面下排序菜单公用界面


extern volatile byte State13parameter;	//打印菜单的入口参数
extern volatile byte State14parameter;	//锁定超量菜单的入口参数
extern volatile byte State300parameter;	//锁定菜单下锁定复选菜单状态300，全局变量
extern volatile byte State4parameter;	//主菜单的入口参数
extern volatile byte State400parameter;	//自动模式入口参数
extern volatile byte State401parameter;	//手动模式入口参数
extern volatile byte State4000parameter;//自动模式和手动模式的公共子界面入口参数
extern volatile byte State41parameter;	//信息类别入口参数
extern volatile byte State44parameter;	//维护菜单入口参数
extern volatile byte FLAG;				//用于各界面内while循环内的标志位


extern volatile word BUFFER[10];	//第一级菜单，每级菜单在跳出后必须清零，在跳入子菜单则无需改变
extern volatile word BUFFER1[10];	//第二级菜单
extern volatile word BUFFER2[10];	//第三级菜单
extern volatile word BUFFER3[10];	//第四级菜单
extern volatile word BUFFER4[10];	//第五级菜单
extern volatile word BUFFERPRO[10]; //第一级菜单的保护用于信息存储界面和信息锁定届面到信息内容菜单切换时保护
extern volatile short int BUFFERSELECT[22]; 		//专用于公用复选界面Savelocksubmenu的参数保护
extern volatile word BUFFERPRINT;	//专用于打印确定界面MessageSubmenu的参数保护
extern volatile short int BUFFERSELECTLOCK; 		//专用于锁定复选界面参数的保护



extern volatile short int Messagenownumber; //信息正文当前显示条数位置


extern volatile char LANHELP;		//用于画框图函数的辅助选择，
					//即在LANGUAGE为1的情况下，框图函数仍旧可能使用英文模式,若为0则可继续使用英文框图
					 
					 
/***********************************/
/****LCD****/
/***********************************/					 

extern volatile byte CTAB1[40];	//液晶中显示一行的字符
extern volatile byte CGTAB[2][16]; //液晶中显示一个汉字
extern volatile byte G_Key;

/***********************************/
/****FLASH****/
/***********************************/	

/***********************************/
/*  信息存储菜单界面及子界面参数   */
/***********************************/

extern volatile short int Selectsubback; 			//用于进入复选界面的界面参数保护
extern volatile char Selectreturn;  		//用于复选界面的出口参数保护
extern volatile short int Mulnownumber; 			//作为复选界面的当前所在信息条数
extern volatile short int Returnback;  			//用于存储界面和锁定界面公用的入口参数保护
extern volatile short int Messagenumber; 			//用于存储界面和锁定界面中总信息数的记录
extern volatile char Rankback; 				//用于排序公共界面的入口参数保护
extern volatile short int Msglockrank[150];	//专用于Savemenu(此时用作锁定菜单)及其子菜单，每次进入都需要更新


/*******************************/
/*  信息菜单界面及子界面参数   */
/*******************************/
/*MESSAGE*/
extern volatile char Returntype; 	//表示是从何界面进入信息内容界面，10表示子界面进入
				  	//1返回到存储，2返回到锁定,
extern volatile char PublicReturn; 	//用于公共界面的入口参数
extern volatile char PitchDAPro;	//批处理界面入口参数保护
extern volatile byte subback;								//表明是否从子菜单返回，10表示弹出子菜单
/*******************************/
/*  主菜单界面及子界面参数   */
/*******************************/
extern volatile word Auto[3][26]; 			//自动配置参数，0表示接收
extern volatile word Autotemp[3][26];		//自动配置临时参数
extern volatile char Manual[3][26];			//手动配置参数，0表示接收
extern volatile char Manualtemp[3][26];		//手动配置临时参数
extern volatile char MSGTYPE[3][26];		//信息类别配置参数，0表示接收
extern volatile char MSGTYPETEMP[3][26];	//信息类别临时配置参数
extern volatile char backpage;			//0表示信息正文，1表示存储，2表示锁定，3表示时间位置； 

extern volatile char manual_area_temp;
extern volatile char manual_area;

/*本地时间*/                //用来分别表示本地时间的年月日时分

extern volatile char number;          		//本地时间调整量
extern volatile char sign;            		//调整量的正负号
extern volatile char lcontrol;         		//用来记录本地时间是否开

extern byte iyear;
extern byte imonth;
extern byte iday;
extern volatile byte ihour;
extern volatile byte iminute;
/*接收机设置*/              //分别用来表示接收机的一些设置
extern volatile char Receiverset[5];    	//0表示误码率，以下数据依次


extern volatile char Buzzer[4];			//依次表示四种蜂鸣的开关情况
extern volatile char Buzzerstate;		//表明此时蜂鸣处于何种状态，Bit0标记重要信息，Bit1标记接收机故障
extern volatile char Contrast;				//表示对比度的选择
extern volatile char Backlight;				//0表示high，1表示medim，2表示low
extern Diagresulttype Diaglog[10];//用于记录自检日志的结果，共十组
extern volatile char Diaglogs;				//用于记录但前可写日志在Diagresult[]中位置
extern volatile char Diaglogn;				//用于记录日志的条数

/* Rx station*/
extern volatile char Mode;				//记录当前处在何种模式，0表示自动，1表示手动
extern volatile char Workfre;			//记录当前的工作频率，0选择518/4209.5，1选择518/486

extern volatile char LANGUAGE;			//区分中英文操作模式，1是中文，0是英文
extern volatile char Operated;			//用于判断是否需要加载语言选择界面

/*信息提示标志*/
extern volatile char flag_s;			//信息提示标志，当flag_s为1时，显示提示符号；否则flag_s为0时，清除提示符号
extern volatile char counter_flag_se;	//信息提示标志计数
extern volatile char counter_flag_sc;	//信息提示标志计数
/*新信息收到标志，当有新收到信息后置位，所有新信息处理完毕后清0*/
extern volatile char flag_new_message;
/*IEC61162接收结构体*/
extern volatile iec_tx_type iec_rx;
/*GPS转化后数据，包括经度、纬度以及日历信息*/
extern volatile short int gpslldt[3][5];//gpslldt[0][]:纬度  gpslldt[1][]:经度  gpslldt[2][]:日历(年月日时分) 
/*自动海区*/
extern volatile short int auto_area;	//自动海区
/*自动传输标志，0--手动，1自动*/
extern volatile char flag_auto_iec;
//extern volatile char Ham[1000];

//extern volatile char Cos[1000];
//extern volatile char Sin[1000];

//extern volatile char Ham1[250];

//extern volatile char Cos1[250];
//extern volatile char Sin1[250];
//-----------------jietiao.c----------------------------------------------------------------------------------
//extern int JietiaoBlcok[DemodulateBuffer];	//分别存放两个通道采样数据
//extern volatile byte ReceiverarrayNow[9100];

//extern volatile unsigned char Receivearray[2][ReceiveMax], ReceivePeriod[2];
//Receivearray为解调的存储数组，ReceivePeriod[2]表示对应两个通道当前存储字节存储了几个码元
//extern volatile int  Receivenm[2],Pfirst[2];
//Receivenm[2]表示对应通道解调存储数组的数目，Pfirst表示由于每次接收80个AD转换数据送入解调，开始解调的数据在接收缓冲区的位置

 

extern volatile char Dingxiang[2];		//分别对应两个通道定向情况，0未定向，1定向
//extern volatile char Dingxiangmount[2];	//分别对应两个通道定向信息中所接收的bit数

//extern volatile word Jietiaomount;		//解调的字符数，包括所有的信息
//extern volatile word Jietiaomounttemp;	//当前信息未解码的字节数
extern volatile short int Jiemamount;			//整条信息解码完毕的字节数
extern volatile short int Jiemamounttemp;		//本次解码的字节数

extern volatile char Antenna;				//0此时正常解调，1用于检测天线连接	
extern volatile char AntennaResult;		//天线检测结果，0正常，1未检测到天线
//------------------automode.c------------------------------------------------------------------------------------------
extern volatile unsigned char Rxstation[16][26][14];
//automodesubmenu.c
extern volatile byte parameter;
//-------------------lcddrive.c--------------------------------------------------------------
extern volatile byte SYSTAB[8];
extern volatile byte SCRTAB[10];
extern volatile byte CTAB[40];
//-----------------boot.c-------------------------------
extern volatile signed char TimeLeft;
//others.c
extern volatile char Antennaing;	//辅助天线自检结果存储的变量，当开始自检置1，自检完成置0
extern volatile char flag_on;				//开机自检标志
//printer.c
extern int TEMP[1600];

extern volatile PrtLink *PrtStart;
extern volatile short int print_list[600];
extern volatile short int print_sum;
//iec.c
extern volatile short int iec_send_list[600];
extern volatile short int iec_send_sum;
extern char bice[75][82];
extern volatile  char nrmareamk[26];
extern volatile char nrmtypemk[26];
extern volatile  char nrmflag_on;
extern volatile  char nrmfre;
extern volatile char checkdata[6];
extern char iec_rx_data[70];		//有效数据存储
extern volatile unsigned char iec_rx_array[500];//接收数据缓冲区
extern volatile unsigned char iec_alarm_data;
//messagetype.c
extern volatile byte MessagetypeEn[26][13];
extern volatile word MessagetypeCn[26][4];
//message.c
extern volatile word LINE;									//统计所显示信息的总行数
extern volatile byte now_printing;
extern volatile byte flag_more_message;
extern volatile byte falsh_error;
//extern volatile byte eepromdata[33000];            //@wuxianwei
//extern volatile byte flashdata[40000];
extern volatile short int recenum;
extern volatile byte msgover;
//extern volatile word Jiemamounttempa;
extern Messagetoptype msgtop;
//extern volatile word wrongmessage;
extern volatile byte whichchannel;
extern volatile short int Jiemamounte;
extern volatile short int Jiemamountc;
extern char Blocke[4500];
extern char Blockc[4500];
extern volatile unsigned char maske;
extern volatile unsigned char maskc;
extern volatile short int readMesEnd;
extern volatile short int readMesMount;
extern volatile timetype timestruct;
#endif
