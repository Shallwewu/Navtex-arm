#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "run.h"
#include "lcddrive.h"
#include "Eprom.h"
#include "code.h"
#include "start.h"

//********************************************/
/*	功能：菜单LanguageChoose的液晶显示
入口参数：无
出口参数：无
/*********************************************/
/*void LanguageChoose_Paintintial();
void LanguageChoose_Paintintial()
{	
	byte i;
	LANGUAGE=1;
	CLEAR1();		//清一区和二区的存储空间
  	CLEARXLINE(0,39,22);
	XLINE(0,39,26);
	XLINE(0,39,27);
  
	

	CCW_PR1(1,8,0xd3ef,1);
	CCW_PR1(3,8,0xd1d4,1);
	CCW_PR1(5,8,0xd1a1,1);
	CCW_PR1(7,8,0xd4f1,1);
	
	CTAB[0]='(';  CTAB[1]='L';  CTAB[2]='A';  CTAB[3]='N';
	CTAB[4]='G';  CTAB[5]='U';  CTAB[6]='A'; 
	CTAB[7]='G';  CTAB[8]='E'; CTAB[10]='C';  CTAB[11]='H';  
	CTAB[12]='O';  CTAB[13]='O';  CTAB[14]='S'; CTAB[15]='E'; CTAB[16]=')';
	CW_PR(9,2,17);	//表头：语言选择(LANGUAGE CHOOSE)
	
	CCW_PR1(4,54,0xc7eb,1);	//第二行内容"请选择系统语言"
	CCW_PR1(6,54,0xd1a1,1);
	CCW_PR1(8,54,0xd4f1,1);
	CCW_PR1(10,54,0xcfb5,1);
 	CCW_PR1(12,54,0xcdb3,1);
	CCW_PR1(14,54,0xd3ef,1);	
	CCW_PR1(16,54,0xd1d4,1);		
//	CCW_PR1(18,56,0x1aa0,0);

	CTAB[0]='P';	CTAB[1]='L';	CTAB[2]='E';	CTAB[3]='A';	CTAB[4]='S';	CTAB[5]='E';
	CTAB[7]='C';	CTAB[8]='H';	CTAB[9]='O';	CTAB[10]='O';	CTAB[11]='S';   CTAB[12]='E';
	CTAB[14]='L';  CTAB[15]='A';  CTAB[16]='N';  CTAB[17]='G';  CTAB[18]='U';  CTAB[19]='A'; 
	CTAB[20]='G';  CTAB[21]='E';  CTAB[23]='V';  CTAB[24]='E';  CTAB[25]='R';  CTAB[26]='S';
    CTAB[27]='I';  CTAB[28]='O';  CTAB[29]='N'; // CTAB[30]=':';
	CW_PR(4,9,30);	//第二行内容：请选择系统语言，PLEASE CHOOSE LANGUAGE  VERSION:


	CCW_PR1(14,88,0xd3a2,1);	//第三行内容"英文"
	CCW_PR1(16,88,0xcec4,1);
		
   	CTAB[0]='(';	CTAB[1]='E';	CTAB[2]='N';	CTAB[3]='G';	CTAB[4]='L';
   	CTAB[5]='I';	CTAB[6]='S';	CTAB[7]='H';	CTAB[8]=')';	
	CW_PR(18,12,9);	//第三行内容：选项一 英语 ENGLISH


	CCW_PR1(14,112,0xd6d0,1);	//第四行内容"中文"
	CCW_PR1(16,112,0xcec4,1);
		
   	CTAB[0]='(';   	CTAB[1]='C';	CTAB[2]='H';	CTAB[3]='I';	CTAB[4]='N';
   	CTAB[5]='E';	CTAB[6]='S';	CTAB[7]='E';   	CTAB[8]=')';	
	CW_PR(18,15,9);	//第四行内容：选项二 中文 CHINESE

	W_YLINE(0,0,239);	//完成边框图形区显示
	W_YLINE(319,0,239);	

	W_DIAMOND(12,92);		//选项框的显示
	W_HDIAMOND(12,116);

}    */

//********************************************/
/*	功能；上下按键处理函数，选择所需选定项
		  并在液晶界面进行显示
入口参数：无
出口参数：无
/*********************************************/
/*void LanguageChoose_Updn();
void LanguageChoose_Updn()
{
	if (G_Key==UP||G_Key==DOWN)
	{
		G_Key=0;			//按键清零
		BUFFER[0]=(BUFFER[0]+1)%2;
		if(BUFFER[0]==0)	//选择选定框一
		{
			W_DIAMOND(12,92);
        	W_HDIAMOND(12,116);		
		}
		else				//选择选定框二
		{
			W_DIAMOND(12,116);
       		W_HDIAMOND(12,92);	
		}
	//	SCR|=SCR_SW_RESET_MASK;
	}
}   */

//***************************************************/
/*	功能；ENT按键处理函数，语言选定功能
入口参数：无
出口参数：无
/****************************************************/
/*void LanguageChoose_Dealing();
void LanguageChoose_Dealing()
{
	if(G_Key == ENT)
	{
		G_Key=0;			//按键清零
		if(BUFFER[0]==0)
		LANGUAGE=0;			//选择英语
		else LANGUAGE=1;	//选择中文
		

		BUFFER[0]=0;		//全局变量生存周期结束，清零
		FLAG=0;				//结束循环，循环标记清零
        STATE=799;
		Write_Char_Eprm(RX_LANGUAGE,LANGUAGE);	//把LANGUAGE信息写入Eprom
		Write_Char_Eprm(OPERATED,1);			//把OPERATED信息写入Eprom
	//	TODCS&=0xfff7;
		TIM3->CR1&=0xfffe;   //关定时器
	}
}   */



//***************************************************/
/*	功能；进入操作系统，语言选择界面
入口参数：无
出口参数：无
/****************************************************/

void RunLanguageChoose()
{
	TimeLeft=3;	
//	IPR6|=0x0010;
//	TODCS|=0x0008;
	TIM3->CR1 |= 0x01;   //开定时器
	start_Paintintial();
	
	
	while(FLAG)
	{
        if(TimeLeft<0)
        {
        TIM3->CR1&=0xfffe;  // 关定时器
        STATE=799;
        LANGUAGE=1;	//选择中文		
		BUFFER[0]=0;		//全局变量生存周期结束，清零
		FLAG=0;				//结束循环，循环标记清零
		Write_Char_Eprm(RX_LANGUAGE,LANGUAGE);	//把LANGUAGE信息写入Eprom
		Write_Char_Eprm(OPERATED,1);			//把OPERATED信息写入Eprom
        }
        else
        {
//		LanguageChoose_Updn();
//		LanguageChoose_Dealing();
        }
	}
	TIM3->CR1&=0xfffe;   //关定时器
}