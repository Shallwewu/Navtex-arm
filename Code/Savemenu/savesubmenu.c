#include <stdio.h>
#include <stdlib.h>
#include  "run.h"
#include "define.h"
#include "lcddrive.h"	
#include "code.h"
/*********************************************/
/*	功能：SaveSubMenu界面的显示
入口参数：无
出口参数：无
/*********************************************/
void SaveSubMenu_Paintintial();
void SaveSubMenu_Paintintial()
{
	byte i;


	if(LANGUAGE==0)	//英文界面
	{

		  
		CTAB[4]='*';  CTAB[5]='S';   CTAB[6]='E';  CTAB[7]='T'; 
		CTAB[9]='U';  CTAB[10]='P'; CTAB[11]='*';
		CW_PR(8,14,12);	//第一行显示内容"*SET UP*"

		  
		CTAB[5]='S';  CTAB[6]='O';  CTAB[7]='R';  CTAB[8]='T';  
		CW_PR(8,16,9);	//第二行显示内容"SORT"

		  
		CTAB[5]='L';  CTAB[6]='O';  CTAB[7]='C';  CTAB[8]='K'; 
		CW_PR(8,17,9);	//第三行显示内容"LOCK"
		  
		CTAB[5]='P';  CTAB[6]='R';  CTAB[7]='I';  CTAB[8]='N';  CTAB[9]='T';
		CW_PR(8,18,10);	//第三行显示内容"PRINT"		
	}
	
	else			//中文菜单
	{

		CCW_PR1(13,104,0xc5c5,1);	//第一行显示内容"排序"
		CCW_PR1(15,104,0xd0f2,1);
				
		CCW_PR1(13,124,0xcbf8,1);	//第二行显示内容"锁定"
		CCW_PR1(15,124,0xb6a8,1);
				
		CCW_PR1(13,144,0xb4f2,1);	//第三行显示内容"打印"
		CCW_PR1(15,144,0xbd3a1,1);		
	}
	
	WFRAME();						//弹出子菜单框图显示
	
	for(i=1;i<3;i++)				//选定框的显示，并对选定选项的选定框加黑
	{
		W_HDIAMOND(11,LANGUAGE?(108+20*i):(16+i));
	}

	W_DIAMOND(11,LANGUAGE?108:16);

	
	if(BUFFER1[0]==1)				//保证选定框对应BUFFER1[0]返回值
	{
		W_HDIAMOND(11,LANGUAGE?108:16);
		W_DIAMOND(11,LANGUAGE?128:17);	
	}
	
	if(BUFFER1[0]==2) 
	{
		W_DIAMOND(11,LANGUAGE?148:18);
		W_HDIAMOND(11,LANGUAGE?108:16);
	}

}

//********************************************/
/*	功能；上下按键处理函数，选择所需选项，存储
          于BUFFER1[0]，并在LCD中显示 
入口参数：无
出口参数：无
/*********************************************/
void SaveSubMenu_Updn();
void SaveSubMenu_Updn()
{
	
		if(G_Key == UP||G_Key == DOWN)
		{
			if(G_Key == UP)	BUFFER1[0]=(BUFFER1[0]+2)%3;	
			else BUFFER1[0]=(BUFFER1[0]+1)%3;	
			
			if(BUFFER1[0]==0)
			{
				W_DIAMOND(11,LANGUAGE?108:16);
				W_HDIAMOND(11,LANGUAGE?128:17);
				W_HDIAMOND(11,LANGUAGE?148:18);	
			}

			if(BUFFER1[0]==1)
			{
				W_HDIAMOND(11,LANGUAGE?108:16);
				W_DIAMOND(11,LANGUAGE?128:17);
				W_HDIAMOND(11,LANGUAGE?148:18);
			}
			
			if(BUFFER1[0]==2) 
			{
				W_HDIAMOND(11,LANGUAGE?108:16);
				W_HDIAMOND(11,LANGUAGE?128:17);
				W_DIAMOND(11,LANGUAGE?148:18);
			}
			
			G_Key=0;	//按键清零			
		}
}

//**************************************************************/
/*	功能；CLR按键处理函数，返回上一级菜单存储菜单 SaveMenu
入口参数：无
出口参数：无
/***************************************************************/
void SaveSubMenu_Return();
void SaveSubMenu_Return()
{
	if(G_Key == CLR)
	{
		BUFFER1[0]=0;		//本菜单使用全局变量清零
		FLAG=0;				//结束循环
		STATE=2;			//SaveMenu状态为2
		State2parameter=10;	//入口参数10，表示从子菜单返回
		G_Key=0;			//按键清零
	}
}

//*****************************************************/
/*	功能；ENT按键处理函数，对选定选项进行操作
入口参数：无
出口参数：无
/*****************************************************/
void SaveSubMenu_Dealing();
void SaveSubMenu_Dealing()
{
	if(G_Key == ENT&&STATE==20)
	{

		FLAG=0;			//结束循环
		switch(BUFFER1[0])
		{
			case 0:					//进行排序操作
			{
				STATE=202;			//SaveRankMenu状态为202	
				State202parameter=0;//入口参数为0，作为存储菜单的子菜单	
				break;
			}
			case 1:					//进行锁定操作
			{
				STATE=200;			//SaveLockMenu状态为200	
				State200parameter=0;//入口参数0，作为锁定复选界面使用	
				break;
			}
			default:				//进行打印操作
			{
				STATE=201;			//SavePrintSubMenu状态为201
				break;
			}
		}

		G_Key=0;		//按键清零	
	}
}

//**************************************************************/
/*	功能；存储菜单SaveMenu界面的子菜单，包括排序，锁定，打印
		  全局变量BUFFER1[0]记录当前所选定的选项
入口参数：无
出口参数：无
/***************************************************************/
void RunSaveSubMenu()
{
    maske=0;
    maskc=0;
	SaveSubMenu_Paintintial();
	while(FLAG)
	{
		SaveSubMenu_Updn();
		SaveSubMenu_Return();
		SaveSubMenu_Dealing();
		run_tip();
	}
}