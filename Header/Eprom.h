#ifndef __Eprom_H
#define __Eprom_H
#include "define.h"
#include "stm32f2xx.h"
#define SDA_IN()  {GPIOC->MODER&=0xfff3ffff;}
#define SDA_OUT()  {GPIOC->MODER&=0xfff3ffff;GPIOC->MODER|=0x00040000;}

void Save_A_Message_Eprom(sword position);
void WriteMesinfo(void); 
void LockAMessageHeader(sword position);
void UnlockAMessageHeader(sword position);
void WritebitDeal(sword position);
char Eprom_Check(void);
void Eprom_AutoMode_Save(void);
void Eprom_ManualMsgMode_Save(word address);
void Eprom_Buzzer_Save(void);
void Eprom_Diaglog_Save(char diaglogs);
void Eprom_Diaglog_Read(Diagresulttype *temp,char diaglogs);
void Intial_Normal_Receiver(void);
void Intial_Message(void);
void Reset_Message(void);
void ReadTime(void);
void SaveTime(void);
void IIC_Init(void);
void IICStart(void);
void IICStop(void);
void InI2C_OutputACK(u8 mAck);
void IICWrite_ONE_BYTE(u8 txd);
u8 IICRead_ONE_BYTE(void);
void Write_Char_Eprm(u16 WriteAddr,u8 data);
u16 Read_Int_Eprm(u16 address);
void Write_Int_Eprm(u16 address,u16 data);
void IICWrite_ONE_MEHE(Messagetoptype * messagetop,u16 address);
void IICRead_ONE_MEHE(u16 address,Messagetoptype * messagetop);
//void cleareeprom();
//void readalleeprom();
/*Eprom总大小为32k字节，0x0000~0x7fff*/


#define MESSTYPELENGTH  	32   //一个struct Messagetoptype共有19个字节，select无需存储，为了避免页写问题，每个分配32字节 
								 //	32*600=19200,0x0000~0x4aff


#define FlashmapStart		19337	//19337(0x4b89)~19636 占用300个字节，一个字节管4个块，Flash中分配1200个块的使用情况，每个块大小为1K字节
#define EprommapStart		19637	//19637~19711 占用75个字节，一个字节管8个块，Eprom中分配600个块的使用情况，每个块大小为19字节
#define MESSAGEINFO 		19712	//19712(4d00)存储Messageinfo的起始位置，共需21个字节

//#define DIAGRESULT			19840//(0x4d80)存储9组自检结果结构体的起始位置，每组13个字节，共117

#define DIAGLOGS			19968//(0x4e00)自检日志的可写日志指向数组,1个字节
#define DIAGLOGN			19969//自检日志的数量,1个字节
#define RX_BUZZER 			19970//蜂鸣类型控制，共4个字节
#define PRINTER_FORMAT		19974//打印格式参数，5个char型
#define RX_MODE			    19979//接收机模式参数，一个字节	
#define RX_WORKFRE			19980//接收机工作频率参数，一个字节
#define RX_TIME				19981//接收机本地时间设置，3个字节
#define RX_LANGUAGE			19984//接收机语言参数，一个字节
#define UNREAD_MSG			19985//未读信息数量，int型，2个字节
#define RX_CONTRAST			19987//接收机的对比度，一个字节
#define OPERATED			19988//接收机是否需进行语言选择，1不需，0需，一个字节
#define RX_BACKLIGHT		19989//接收机的背光，一个字节

#define YEAR        0x5900
#define MONTH       0x5902
#define DAY 				0x6000//接收机日历--天保存，2个字节
#define HOUR				0x6002//接收机日历--小时保存，2个字节
#define MINUTE 				0x6004//接收机日历--分钟保存，2个字节



#define RXSTATION_AUTO  	0x5000//20480(0x5000)自动模式发射台的选择，int型，3*26*2=156字节，分配3页64*3=192字节0x5000---0x50bf
//#define RXSTATION_MANUAL 	0x5180//手动模式发射台的选择，char型，3*26=78字节,加上一个字节的当前区信息,分配一页128字节
//#define RX_MSGTYPE		0x5200//接收机接收信息类别选择，char型，3*26=78字节,分配一页字节
//revised@2010-7-1
#define RXSTATION_MANUAL 	0x50c0//手动模式发射台的选择，char型，3*26=78字节,加上一个字节的当前区信息共79个字节,分配3页192字节
#define RX_MSGTYPE			0x5180//接收机接收信息类别选择，char型，3*26=78字节,分配3页192字节

#define IEC_MODE			0x6006//IEC输出模式，一个字节
#define DIAGRESULT			0x6040//(0x24640)存储9组自检结果结构体的起始位置，每组13个字节，共117,分9页写
#endif
