#ifndef __lcddrive_H
#define __lcddrive_H
#include "define.h"
void CLEAR(void);
void CLEAR1(void);
void CLEAR2(void);

void WFRAME(void);
void W_DOT(short int O_X,short int O_Y);
void W_CLEARDOT(short int O_X,short int O_Y);

void CW_PR3(unsigned char O_X,unsigned char O_Y,unsigned char CATB);

void CW_PR(unsigned char O_X,unsigned char O_Y,unsigned char geshu);
void IntialLCD(char ilcd);
void IntialLCD1(char ilcd);
void ProtectData(void);
void RecoverData(void);
void DISASCII(unsigned char O_X,unsigned char O_Y,unsigned char demical);

void W_UPMOVE(unsigned char O_X,unsigned char O_Y);
void W_DOWNMOVE(unsigned char O_X,unsigned char O_Y);
void W_CLEARUPDN(unsigned char O_X,unsigned char O_Y);

void W_BLOCK(unsigned char O_X,unsigned char O_Y);
void W_CLEARBLOCK(unsigned char O_X,unsigned char O_Y);

void W_YLINE(short int O_X,short int O_YS,short int O_YE);
void W_XLINE(short int O_XS,short int O_XE,short int O_Y);
void W_CLEARXLINE(short int O_XS,short int O_XE,short int O_Y);
void W_CLEARYLINE(short int O_X,short int O_YS,short int O_YE);

void W_HDIAMOND(unsigned char O_X,unsigned char O_Y);
void W_DIAMOND(unsigned char O_X,unsigned char O_Y);

void W_CLEARMESSAGE(unsigned char O_X,unsigned char O_Y);
void W_NEWMESSAGE(unsigned char O_X,unsigned char O_Y);

void W_CHOOSED(unsigned char O_X,unsigned char O_Y);
void W_CANCALCHOOSED(unsigned char O_X,unsigned char O_Y);

void W_MSGTOP(short int num,char pos,char mod); //num表示信息头文件在数组中所处位置
void W_CLEARMSGTOP(char num);

void CCW_PR1(char O_X,byte O_Y,word code1,char neima);

void MessageDis(char *DisAds);
char *MessageDisLine(byte YLine,char *Ldisads);
void MessageDisplay(word startlen);

void XLINE(short int,short int,short int);
void CLEARXLINE(short int,short int,short int);
void ClrMsgtip(void);
void WfmMsgtip(void);
void WriteData(char);
void WriteCode(char);
char ReadData(void);
void DISASCIII(unsigned char O_X,unsigned char O_Y,word demical);
void W_Mode(byte x_zhongwen,byte y_zhongwen,byte x_yingwen,byte y_yinwen);
void W_current_area(byte x_zhongwen,byte y_zhongwen,byte x_yingwen,byte y_yinwen,char current_area);
void Station_display(unsigned short int navarea);
void pinoflcdinit(void);
//extern byte CTAB[40];
/****************************/
/*  类似存储界面的公共函数  */
/****************************/

#endif
