#ifndef __define_H
#define __define_H
#include "stm32f2xx.h"
#define UP 		7
#define DOWN 	5
#define LEFT 	6
#define RIGHT 	8
#define MENU	3//11
#define DISP	2
#define STAR 	10
#define ENT 	4
#define PW  	1
#define CLR 	9
#define BACKLIGHT 12
#define CONTRAST 11//3

#define Maxpagenum 6		//存储列表一页中所能存储的信息条数
#define MessagePageNum 7 	//存储列表数据
#define Maxlocknum 50 		//单通道最大锁定条数 
#define PARA 0x29  	    	//同SYSTEM SET中的P6设置，用来计算光标地址的


typedef unsigned char byte;
typedef unsigned short int  word;
typedef short int sword;
typedef unsigned int uint32;
typedef unsigned char bool;


typedef struct
{
	char diagresult[8];//数组依次用于记录ROM,RAM,SERIAL PORT,POWER,ANTENNA,518,490,4209.5是否正常工作
	byte date[3];//date[2],date[1],date[0]分别用于记录年月日，
	byte time[2];//time[1],time[0]用于记录小时和分钟
} Diagresulttype;

typedef struct
{
	short int nownumber[2];//在接收到新的信息是先改变nownumber这个变量,0表示存储，1表示锁定
	short int savenumber[4];
	short int locknumber[4];
	byte rankmode;//?表示存储菜单和锁定菜单中信息的排列顺序(公用)
			   	 //类型中0表示时间，1表示发射台，2表示信息类别，3表示未读信息,4表示航行警告区				
} Messageinfotype;	//savenumber[1] 580khz savenumber[2] 490khz savenumber[3] 4209.5khz
					//savenumber[0] 3个通道的存储信息量locknumber[4]同savenumber[4]
typedef struct
{
	char Printerror;//打印机状态 0:正常 1:不正常
	char Printover;  //打印状态   0:未打印 1:打印完
} Checkinfotype;

typedef struct
{
	short int jietiaomount;	//解调总信息数
	volatile byte *p;            //解调数据存储数组首地址
	char useing;		//判断本结构体是否在使用中，1使用，0空闲
	char frequency;		//存储通道		
}JietiaoResulttype;		//存储解调结果的结构体


							
typedef struct
{
	byte mark[4];
	byte frequency;	//1:518khz 2:486khz 3:4209.5khz
	byte date[3];	//日期,date[0],date[1],date[2]分别用于记录年月日
	byte time[2];  	//时间time[0],time[1]用于记录小时和分钟,存储的数据不是字符形式
	byte lock; 		//锁定为1，解锁为0
	byte read; 		//0:已读  1:未读
	word flashadd;	    // 文件分配分区信息,0~1199
    byte flashmount;	// 文件分配分区信息
	byte select;		//表示是否复选，进行完一次复选操作该项必须清零，1表示选定,无需存储在eprom中
	byte area;			//表示16个海区中其中的一个,取值1~16
	char dealed;		//信息是否超过三天，1表示经过，0表示无
	char cer;			//存储误码率的百分比
	word amount;       //@信息总字节数
} Messagetoptype;				//存储信息头文件

typedef struct
{
	char rx_data;					//当前接收字节
	short int nownum;//
	short int allnum;//	
	unsigned char start_flag;		//信息头接收完毕标志
	unsigned char end_flag;			//信息尾接收完毕标志
	unsigned char data_valid_flag;	//接收到有效GPS数据标志
	unsigned char time;				//超时次数
	unsigned char new_flag;		//新收到数据,0未收到，1有收到
} iec_tx_type;

typedef struct node
{
	short int xulie;
//	char *start;
	char *nowprint;
	char *end;
//	struct node *next;			
}PrtLink;

typedef struct
{
	u8 year;
	u8 month;
	u8 day;
	u8 hour;
	u8 minute;
	u8 second;
} timetype;

#endif
