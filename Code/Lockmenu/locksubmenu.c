#include <stdio.h>
#include <stdlib.h>
#include  "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "code.h"


/*********************************************/
/*	功能：锁定界面子菜单LockSubMenu的显示
入口参数：无
出口参数：无
/*********************************************/
void LockSubMenu_Paintintial();
void LockSubMenu_Paintintial()
{


	WFRAME();

	if(LANGUAGE==0)	//英文菜单
	{
		CTAB[4]='*';  CTAB[5]='S';   CTAB[6]='E';  CTAB[7]='T'; 
		CTAB[9]='U';  CTAB[10]='P'; CTAB[11]='*';
		CW_PR(9,15,12);	//第一行显示内容"SETUP"

		CTAB[5]='S';  CTAB[6]='O';  CTAB[7]='R';  CTAB[8]='T';  
		CW_PR(9,17,9);	//第二行显示内容"SORT"
		  
		CTAB[5]='U';  CTAB[6]='N';  CTAB[7]='L';  CTAB[8]='O';  CTAB[9]='C';
		CTAB[10]='K';	//第三行显示内容"UNLOCK"
		CW_PR(9,18,11);		
	}

	else			//中文菜单
	{
 		CCW_PR1(15,104,0xc9e8,1);	//第一行显示内容"设置"
 		CCW_PR1(18,104,0xd6c3,1);
  		
   		CCW_PR1(14,128,0xc5c5,1);	//第二行显示内容"排序"
		CCW_PR1(16,128,0xd0f2,1);
				
 		CCW_PR1(14,148,0xbde2,1);	//第三行显示内容"解锁"
		CCW_PR1(16,148,0xcbf8,1);
 
 	}

	if(BUFFER1[0]==0)	//方框一选中
	{
	    W_DIAMOND(12,LANGUAGE?132:17);
	    W_HDIAMOND(12,LANGUAGE?152:18);
	}
	
	else				//方框二选中
	{
		W_DIAMOND(12,LANGUAGE?152:18);
    	W_HDIAMOND(12,LANGUAGE?132:17);	
	}
}

/*********************************************/
/*	功能；上下按键处理函数，选择所需选项
入口参数：无
出口参数：无
/*********************************************/
void LockSubMenu_Updn();
void LockSubMenu_Updn()
{
	if(G_Key == UP||G_Key == DOWN)
	{

		BUFFER1[0]=(BUFFER1[0]+1)%2;	//BUFFER1[0]记录选择选定项
		if(BUFFER1[0] == 0)
		{
		    W_DIAMOND(12,LANGUAGE?132:17);
		    W_HDIAMOND(12,LANGUAGE?152:18);
		}
		if(BUFFER1[0] ==1)
		{	
			W_DIAMOND(12,LANGUAGE?152:18);
	    	W_HDIAMOND(12,LANGUAGE?132:17);				
		}
		G_Key=0;						//按键清零	
	}
}


/***************************************************************/
/*	功能；CLR按键处理函数，返回上一级菜单锁定菜单SaveMenu
入口参数：无
出口参数：无
/***************************************************************/
void LockSubMenu_Return();
void LockSubMenu_Return()
{
	if(G_Key == CLR)
	{

		BUFFER1[0]=0;		//本菜单使用全局变量清零
		FLAG=0;				//结束循环
		STATE=2;			//SaveMenu状态为2
		State2parameter=10;	//入口参数10，从子菜单返回
		G_Key=0;			//按键清零
	}
}

/*****************************************************/
/*	功能；ENT按键处理函数，进行排序或锁定操作
入口参数：无
出口参数：无
/*****************************************************/
void LockSubMenu_Dealing();
void LockSubMenu_Dealing()

{
	if(G_Key == ENT&&STATE==30)
	{

		FLAG=0;				//结束循环
		switch(BUFFER1[0])
		{
			case 0:
			{
				STATE=202;	//SaveRankSubMenu的状态为202
				State202parameter=1;	//入口参数为1，表明由锁定菜单调用
				break;
			}
			case 1:
			{
				STATE=300;	//LockLockSubMenu的状态为300
				State300parameter=0;	//入口参数0
				break;
			}			
		}
		G_Key=0;			//按键清零	
	}
}

/***************************************************************/
/*	功能；锁定菜单SaveMenu界面的子菜单，包括排序，解锁
		  全局变量BUFFER1[0]记录当前所选定的选项
入口参数：无
出口参数：无
/***************************************************************/
void RunLockSubMenu()
{
    maske=0;
    maskc=0;
	LockSubMenu_Paintintial();
	
	while(FLAG)
	{
 //       COPCTR=0xAAAA;
 //       COPCTR=0x5555;
		LockSubMenu_Updn();
		LockSubMenu_Return();
		LockSubMenu_Dealing();
		run_tip();
	}
}