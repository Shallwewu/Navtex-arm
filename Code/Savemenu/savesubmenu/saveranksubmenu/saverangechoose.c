#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "Eprom.h"
#include "code.h"

/*********************************************/
/*	功能：SaveRangeChoose界面的显示
入口参数：无
出口参数：无
/*********************************************/
void SaveRangeChoose_Paintintial();
void SaveRangeChoose_Paintintial()
{
	byte i;
	WFRAME();		//弹出子菜单框图显示
	if(LANGUAGE==0)	//英文菜单，表头显示RANGE SET
	{
		CTAB[3]='*';  CTAB[4]='R';   CTAB[5]='A'; CTAB[6]='N'; 
		CTAB[7]='G';  CTAB[8]='E';  CTAB[10]='S';  CTAB[11]='E'; CTAB[12]='T';	CTAB[13]='*'; 
		CW_PR(8,14,14);	
	}
	  
	else			//中文菜单，表头显示：范围选择
	{
		CCW_PR1(13,104,0xb7b6,1);
		CCW_PR1(15,104,0xcea7,1);
		CCW_PR1(17,104,0xd1a1,1);
		CCW_PR1(19,104,0xd4f1,1);		
	}
	  
	CTAB[5]='A';  CTAB[6]='L';  CTAB[7]='L';  
	CW_PR(8,16,8);	//选项一 ALL

	CTAB[5]='5';   CTAB[6]='1';   CTAB[7]='8';   CTAB[8]='K';
	CTAB[9]='H';   CTAB[10]='Z';  
	CW_PR(8,17,11);	//选项二 518KHZ
	  
	CTAB[5]='4';   CTAB[6]='8';   CTAB[7]='6';  CTAB[8]='K';
	CTAB[9]='H';  	CTAB[10]='Z';  
	CW_PR(8,18,11);	//选项三 490KHZ

	CTAB[5]='4';   CTAB[6]='2';   CTAB[7]='0';  CTAB[8]='9';
	CTAB[9]='.';   CTAB[10]='5';  CTAB[11]='K'; CTAB[12]='H'; CTAB[13]='Z'; 
	CW_PR(8,19,14);	//选项四 4209.5KHZ

	W_DIAMOND(11,16);	//选定框的显示，并对选定选项的选定框加黑
	W_HDIAMOND(11,17);
	W_HDIAMOND(11,18);
	W_HDIAMOND(11,19);
}
/*********************************************/
/*	功能；上下按键处理函数，选择所需选项，存储
          于BUFFER3[0]，并在LCD中显示 
入口参数：无
出口参数：无
/*********************************************/
void SaveRangeChoose_Updn();
void SaveRangeChoose_Updn()
{
	if(BUFFER3[0]>=0&&BUFFER3[0]<=3)
	{
		if(G_Key == UP)
		{
			G_Key=0;
			if(BUFFER3[0]>0)
			{
				BUFFER3[0]--;
				W_DIAMOND(11,BUFFER3[0]+16);
				W_HDIAMOND(11,BUFFER3[0]+17);
			}
		}
		else if(G_Key == DOWN)
		{
			if(BUFFER3[0]<3)
			{			
				BUFFER3[0]++;
				W_DIAMOND(11,BUFFER3[0]+16);
				W_HDIAMOND(11,BUFFER3[0]+15);
			}			
			G_Key=0;
		}
	}
}
//*******************************************/
/*	功能；CLR按键处理函数，返回上一级菜单
入口参数：无
出口参数：无
/********************************************/
void SaveRangeChoose_Return();
void SaveRangeChoose_Return()
{
	if(G_Key == CLR)
	{
		LANHELP=1;		//LANHELP恢复到初始值
		BUFFER3[0]=0;	//本界面使用全局变量清零
		FLAG=0;			//结束循环
		STATE=202;		//SaveRankSubmenu状态为202
		State202parameter=Rankback;
		G_Key=0;		//按键清零		
/*		if(Rankback==0)	State202parameter=0;	//SaveRankSubmenu作为存储菜单的子界面
		else State202parameter=1;				//SaveRankSubmenu作为锁定菜单的子界面*/
	}
}


//*****************************************************/
/*	功能；ENT按键处理函数，对选定选项进行排序操作
入口参数：无
出口参数：无
/*****************************************************/
void SaveRangeChoose_Dealing();
void SaveRangeChoose_Dealing()
{
	if(G_Key == ENT&&STATE==2020)
	{

		LANHELP=1;		//LANHELP恢复初始值
		FLAG=0;			//结束循环
		STATE=2021;		//SaveRanking状态为2021
		G_Key=0;		//按键清零
/*		Messageinfo.rankmode=BUFFER2[0];	//把当前的排序状态写入信息记录结构体
		Write_Char_Eprm(MESSAGEINFO+20,Messageinfo.rankmode);//把信息记录结构体写入Eprom*/	
	}
}


//**************************************************************/
/*	功能；排序范围的选择，全局变量BUFFER3[0]用来记录排序范围
          0 表示ALL 1表示518 2表示490 3表示4209.5
          LANHELP设为0表示选定框在中文菜单下也用英文的显示
          
入口参数：无
出口参数：无
/***************************************************************/
void RunSaveRangeChoose()
{
    maske=0;
    maskc=0;
	LANHELP=0;
	SaveRangeChoose_Paintintial();
	while(FLAG)
	{
		SaveRangeChoose_Updn();
		SaveRangeChoose_Return();
		SaveRangeChoose_Dealing();
		run_tip();
	}
}