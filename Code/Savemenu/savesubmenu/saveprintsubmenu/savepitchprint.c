#include <stdio.h>
#include <stdlib.h>
#include  "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "code.h"
/********************************************************/
/*功能；锁定复选或打印复选的显示
入口参数：无
出口参数：无
/********************************************************/
void SavePitchPrint_Paintintial();
void SavePitchPrint_Paintintial()
{
	byte i;
//	CLEAR2();		//弹出子菜单区域数据清空
	WFRAME();		//弹出子菜单边框的显示

	if(LANGUAGE==0)
	{
		CTAB[4]='*';  CTAB[5]='P';   CTAB[6]='I';  CTAB[7]='T'; 
		CTAB[8]='C';  CTAB[9]='H'; CTAB[10]='*';
		CW_PR(9,14,11);	//第一行显示内容"PITCH"


		  
		CTAB[3]='A';  CTAB[4]='L';   CTAB[5]='L';   CTAB[6]='S'; 
		CTAB[7]='A';  CTAB[8]='V';   CTAB[9]='E';   CTAB[11]='M'; 
		CTAB[12]='S'; CTAB[13]='G'; 	 
		CW_PR(9,16,14);	//第二行显示内容"ALLSAVE MSG"

		  
		CTAB[3]='A';  CTAB[4]='L';   CTAB[5]='L';   CTAB[6]='L'; 
		CTAB[7]='O';  CTAB[8]='C';   CTAB[9]='K';   CTAB[11]='M'; 
		CTAB[12]='S'; CTAB[13]='G'; 
		CW_PR(9,17,14);	//第三行显示内容"ALLLOCK MSG"


		  
		CTAB[3]='M';  CTAB[4]='A';   CTAB[5]='N';   CTAB[6]='U'; 
		CTAB[7]='A';  CTAB[8]='L';   
		CW_PR(9,18,9);	//第四行显示内容"MANUAL"		
	}

	else
	{
		CCW_PR1(14,100,0xc5fa,1);	//第一行显示内容"批处理"
		CCW_PR1(16,100,0xb4a6,1);
		CCW_PR1(18,100,0xc0ed,1);
				
		CCW_PR1(12,118,0xb4e6,1);	//第二行显示内容"存储信息"
		CCW_PR1(14,118,0xb4A2,1);
		CCW_PR1(16,118,0xd0c5,1);
		CCW_PR1(18,118,0xcfa2,1);


				
		CCW_PR1(12,136,0xcbf8,1);	//第三行显示内容"锁定信息"
		CCW_PR1(14,136,0xb6a8,1);
		CCW_PR1(16,136,0xd0c5,1);
		CCW_PR1(18,136,0xcfa2,1);
				
		CCW_PR1(12,154,0xc8cb,1);	//第四行显示内容"人工复选"
		CCW_PR1(14,154,0xb9a4,1);
		CCW_PR1(16,154,0xb8b4,1);
		CCW_PR1(18,154,0xd1a1,1);		
	}


	W_DIAMOND(10,LANGUAGE?122:16);	//选定框的显示
	W_HDIAMOND(10,LANGUAGE?140:17);
	W_HDIAMOND(10,LANGUAGE?158:18);	
	if(BUFFER3[0]!=0)			//保证选定框对应BUFFER3[0]返回值
	{
	
		W_DIAMOND(10,LANGUAGE?(122+BUFFER3[0]*18):(16+BUFFER3[0]));
		W_HDIAMOND(10,LANGUAGE?122:16);	
	}
	
}

/*********************************************/
/*	功能；上下按键处理函数，选择所需选项
入口参数：无
出口参数：无
/*********************************************/
void SavePitchPrint_Updn();
void SavePitchPrint_Updn()
{
	if(BUFFER3[0]>=0&&BUFFER3[0]<=2)
	{
		if(G_Key == UP)
		{
			G_Key=0;
			if(BUFFER3[0]>0)
			{
				BUFFER3[0]--;
				W_DIAMOND(10,LANGUAGE?(122+BUFFER3[0]*18):(16+BUFFER3[0]));	
		    	W_HDIAMOND(10,LANGUAGE?(140+BUFFER3[0]*18):(17+BUFFER3[0]));	
			}
		}
		if(G_Key == DOWN)
		{
			G_Key=0;
			if(BUFFER3[0]<2)
			{			
				BUFFER3[0]++;
				W_DIAMOND(10,LANGUAGE?(122+BUFFER3[0]*18):(16+BUFFER3[0]));
		    	W_HDIAMOND(10,LANGUAGE?(104+BUFFER3[0]*18):(15+BUFFER3[0]));
			}			
		}
	}
}

/***************************************************************/
/*	功能；CLR按键处理函数，返回上一级菜单存储菜单SavePrintSubMenu
入口参数：无
出口参数：无
/***************************************************************/
void SavePitchPrint_Return();
void SavePitchPrint_Return()
{
	if(/*G_Key == LEFT || */G_Key == CLR)
	{
		G_Key=0;		//按键清零
		BUFFER3[0]=0;	//本菜单使用的全局变量清零
		STATE=201;		//SavePrintSubMenu的状态为201
		FLAG=0;			//结束循环
	}
}

/*****************************************************/
/*	功能；ENT按键处理函数，对选定选项进行操作
入口参数：无
出口参数：无
/*****************************************************/
void SavePitchPrint_Dealing();
void SavePitchPrint_Dealing()
{
	if(G_Key == ENT)
	{
		G_Key=0;	//按键清零
		FLAG=0;		//结束循环
		switch(BUFFER3[0])
		{
			case 0:
			{
				STATE=2011;				//SaveAllMessage的状态为2011
				break;
			}
			
			case 1:
			{
				STATE=2011;				//SaveAllMessage的状态为2011
				break;
			}
			
			default:
			{
				STATE=200;				//SaveLockSubMenu的状态为200
				State200parameter=1;	//入口参数1表示此时SaveLockSubMenu作为打印复选界面
				break;
			}
		}
	}
}


/*********************************************************/
/*	功能：打印范围的选择：存储信息，锁定信息，复选打印
          使用全局变量BUFFER3[0]:0存储信息 1 锁定信息
          2 复选打印
入口参数：无
出口参数：无
/*********************************************************/
void RunSavePitchPrint()
{

    maske=0;
    maskc=0;
	SavePitchPrint_Paintintial();
	while(FLAG)
	{
		SavePitchPrint_Updn();
		SavePitchPrint_Return();
		SavePitchPrint_Dealing();
		run_tip();
	}
  	
}