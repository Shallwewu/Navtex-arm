#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"
#include "lcddrive.h"
#include "Eprom.h"
#include "code.h"
//********************************************/
/*	功能：SaveRankSubMenu界面的显示
入口参数：无
出口参数：无
/*********************************************/
void SaveRankSubMenu_Paintintial();
void SaveRankSubMenu_Paintintial()
{
	WFRAME();		//弹出子菜单框图显示
	if(LANGUAGE==0)	//英文菜单
	{
		CTAB[4]='*';  CTAB[5]='S';   CTAB[6]='O'; CTAB[7]='R'; 
		CTAB[8]='T';  CTAB[9]='*'; 
		CW_PR(10,14,10);//第一行显示内容"*SORT*"
		

		  
		CTAB[5]='D';  CTAB[6]='A';  CTAB[7]='T';  CTAB[8]='E';  
		CW_PR(9,15,9);	//第二行显示内容"DATE"


		  
		CTAB[5]='R';   CTAB[6]='X';   CTAB[8]='S';   CTAB[9]='T';
		CTAB[10]='A';  CTAB[11]='T';  CTAB[12]='I';  CTAB[13]='O';	CTAB[14]='N';	  
		CW_PR(9,16,15);	//第三行显示内容"RX STATION"


		  
		CTAB[5]='M';   CTAB[6]='S';   CTAB[7]='G';  CTAB[9]='T';
		CTAB[10]='Y';  CTAB[11]='P';  CTAB[12]='E'; 
		CW_PR(9,17,13);	//第四行显示内容"MSG TYPE"


		  
		CTAB[5]='U';   CTAB[6]='N';   CTAB[7]='R';  CTAB[8]='E';
		CTAB[9]='A';   CTAB[10]='D'; 
		CW_PR(9,18,11);	//第五行显示内容"UNREAD"
		

		CTAB[5]='A';  CTAB[6]='R';  CTAB[7]='E';  CTAB[8]='A'; 
		CW_PR(9,19,9);	//第六行显示内容"AREA"		
	}
	
	else
	{
 		CCW_PR1(14,92,0xcab1,1);	//第一行显示内容"时间"
 		CCW_PR1(16,92,0xbce4,1);
		
 		CCW_PR1(14,110,0xb7a2,1);	//第二行显示内容"发射台"
		CCW_PR1(16,110,0xc9e4,1);
 		CCW_PR1(18,110,0xcca8,1);

  				
   		CCW_PR1(14,128,0xd0c5,1);	//第三行显示内容"信息类别"
		CCW_PR1(16,128,0xcfa2,1);
 		CCW_PR1(18,128,0xc0e0,1);
  		CCW_PR1(20,128,0xb1f0,1);


  				
  		CCW_PR1(14,146,0xceb4,1);	//第四行显示内容"未读信息"
		CCW_PR1(16,146,0xb6c1,1);
  		CCW_PR1(18,146,0xd0c5,1);
 		CCW_PR1(20,146,0xcfa2,1);
 				
   		CCW_PR1(14,164,0xbabd,1);	//第五行显示内容"航行警告区"
		CCW_PR1(16,164,0xd0d0,1);
 		CCW_PR1(18,164,0xbeaf,1);
  		CCW_PR1(20,164,0xb8e6,1);
 		CCW_PR1(22,164,0xc7f8,1);
  	
	}  



	W_DIAMOND(12,LANGUAGE?96:15);	//选定框的显示，并对选定选项的选定框加黑
	W_HDIAMOND(12,LANGUAGE?114:16);
	W_HDIAMOND(12,LANGUAGE?132:17);
	W_HDIAMOND(12,LANGUAGE?150:18);
	W_HDIAMOND(12,LANGUAGE?168:19);
	
	if(BUFFER2[0]!=0)				//保证选定框对应BUFFER2[0]返回值
	{
		W_DIAMOND(12,LANGUAGE?(96+18*BUFFER2[0]):(BUFFER2[0]+15));
		W_HDIAMOND(12,LANGUAGE?96:15);	//选定框的显示，并对选定选项的选定框加黑
		//W_HDIAMOND(12,15);	
	}
	
}

/*********************************************/
/*	功能；上下按键处理函数，选择所需选项，存储
          于BUFFER2[0]，并在LCD中加黑选定选项 
入口参数：无
出口参数：无
/*********************************************/
void SaveRankSubMenu_Updn();
void SaveRankSubMenu_Updn()
{
	if(BUFFER2[0]>=0&&BUFFER2[0]<=4)
	{
		if(G_Key == UP)
		{
			G_Key=0;			//按键清零
			if(BUFFER2[0]>0)
			{
				BUFFER2[0]--;	//下移，减1
				W_DIAMOND(12,LANGUAGE?(96+18*BUFFER2[0]):(BUFFER2[0]+15));
				W_HDIAMOND(12,LANGUAGE?(114+18*BUFFER2[0]):(BUFFER2[0]+16));
			}
			
		}
		if(G_Key == DOWN)
		{
			G_Key=0;			//按键清零
			if(BUFFER2[0]<4)
			{			
				BUFFER2[0]++;	//上移，加1
				W_DIAMOND(12,LANGUAGE?(96+18*BUFFER2[0]):(BUFFER2[0]+15));
				W_HDIAMOND(12,LANGUAGE?(78+18*BUFFER2[0]):(BUFFER2[0]+14));				
			}			
		}
	}
}

/***************************************************************/
/*	功能；CLR按键处理函数，返回上一级菜单存储菜单
入口参数：无
出口参数：无
/***************************************************************/
void SaveRankSubMenu_Return();
void SaveRankSubMenu_Return()
{
	if(G_Key == CLR)
	{

		BUFFER2[0]=0;	//使用全局变量清零
		FLAG=0;			//结束循环
		if(Rankback==0)	//返回SaveSubMenu菜单，状态20
		{
			STATE=20;
		}
		
		else 			//返回LockSubMenu菜单，状态30
		{
			Rankback=0;
			STATE=30;
		}
		G_Key=0;		//按键清零
	}
}

//*****************************************************/
/*	功能；ENT按键处理函数，对选定选项进行操作
入口参数：无
出口参数：无
/*****************************************************/
void SaveRankSubMenu_Dealing();
void SaveRankSubMenu_Dealing()
{
	if(G_Key == ENT&&STATE==202)
	{
		LANHELP=1;		//LAMHELP恢复到初始值		
		FLAG=0;			//结束循环
		STATE=2020;		//SaveRangeChoose的状态为2020
		G_Key=0;		//按键清零
	}
}

//**************************************************************/
/*	功能；排序菜单函数，可实现按时间，发射台，信息类别，未读信息
          航行警告区排序
          全局变量Rankback,用于排序公共界面的入口参数保护
          0 存储菜单的子菜单
          1 锁定菜单的子菜单
          LANHELP=3 进行长框图的选择，一共有三种框图
入口参数：无
出口参数：无
/***************************************************************/
void RunSaveRankSubMenu(unsigned char into)
{
    maske=0;
    maskc=0;
	Rankback=into;
	LANHELP=3;
	SaveRankSubMenu_Paintintial();
	
	while(FLAG)
	{
		SaveRankSubMenu_Updn();
		SaveRankSubMenu_Return();
		SaveRankSubMenu_Dealing();
		run_tip();
	}
  	
}