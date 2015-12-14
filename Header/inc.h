#ifndef	_INC_H
#define _INC_H


#include <stdio.h>
#include <stdlib.h>

#define FPGARW(offset)   *((volatile u16 *)(0x60000000+(offset)))

#define Window 80     //用于sin和cos函数中的N
#define DemodulateBuffer  1600	//行一次解调的AD采样总数
#define ReceiveMax        10000  //一条消息的码流，发送给FPGA解码用
#define TongbuPeriod      100	//定向完毕之后所接收的信息，每经过100个点就进行一次同步
#define SingleJietiaomount 400 	//单次传输给FPGA的字节数

extern volatile unsigned char Receivearray[2][ReceiveMax],ReceivePeriod[2];
extern volatile short int  Receivenm[2],Pfirst[2];
extern short int xxxx;

//extern int DxRx[14][2];
//extern int DxRxReceive[2];
//extern uint32 DxRxReceive[2];
extern volatile unsigned short int DxRxReceive[2];
extern volatile char Dingxiang[2];
extern volatile char Dingxiangmount[2];

//extern volatile unsigned short int Jietiaomount;		//解调的字符数，包括所有的信息
//extern volatile unsigned short int Jietiaomounttemp;	//当前信息未解码的字节数
extern volatile char TempBlock;
extern volatile short int Jiemamount;			//整条信息解码完毕的字节数
extern volatile short int Jiemamounttemp;		//本次解码的字节数
extern volatile unsigned short int mesend;
extern volatile unsigned short int oldJiemamount;
extern volatile unsigned short int wumamount;
//static unsigned char flow1[2]={51,120};//修改于3月10
//static unsigned char flow2[60]={99,120,92,120,99,99,92,92,29,99,113,92,113,29,54,113,58,113,90,54,15,58,27,90,45,15,78,27,53,45,105,78,105,53,113,105,86,105,53,113,77,86,77,53,77,77,77,77,15,77,27,77,15,15,27,27,120,15,120,27};//z1c1zzcc空 zb1cb2空转 b1b3b2b4转回 b3换b4转回 m换e转 smseasgseangnennnn回n换n回回换换@回@换          b3b1b4b2回b3换b4m回e换smseasgseangnennnn@n@n
//static unsigned char flow2[58]={99,120,92,120,99,99,92,92,29,99,58,92,53,29,54,58,58,53,90,54,15,58,27,90,45,15,78,27,53,45,105,78,105,53,113,105,86,105,53,113,77,86,77,53,77,77,77,77,15,77,27,77,27,15,120,27,120,27};//z1c1zzcc空 zb1cb2空转 b1b3b2b4转回 b3换b4转回 m换e转 smseasgseangnennnn回n换n  换回@换@换      //修改于3月10
/*static unsigned char flow1[7]=
{
	0x67,0xe1,0x9f,0x86,0x7e,0x19,0xf8
};
static unsigned char flow2[56]=
{
	0xc7,0xe2,0xe7,0x8c,0x78,0xee,0x5c,0x3b,0x8b,0xd5,0xc6,0x57,0x5b,0x3a,0x74,0xd6,0xd3,0x61,0xee,0x8d,0xda,0x5a,0x3e,0x71,0xb6,0xab,0x74,0xce,0xd2,0xd7,0x8e,0x9a,0xda,0x5a,0xf1,0x9b,0x5a,0x6b,0x59,0xb3,0x66,0xcd,0x1f,0x34,0xdc,0xd3,0x63,0xfc,0x1b,0xf0,0x6f,0xff,0xff,0xff,0xff,0xff
};*/
/*static unsigned char flow1[7]=
{
	207,195,63,12,252,51,240
};
static unsigned char flow2[]=
{
	207,195,63,12,252,99,241,115,198,60,119,46,29,198,234,227,83,173,157,58,107,105,176,247,70,237,45,31,51,219,85,186,103,105,107,199,77,109,45,120,205,173,53,172,217,179,102,143,154,110,105,177,254,13,248,55,227,199,143,30,60,120,241,227
};*/

#endif
