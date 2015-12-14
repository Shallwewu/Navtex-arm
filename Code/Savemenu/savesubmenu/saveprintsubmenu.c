#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "code.h"
/*********************************************/
/*	功能：打印子菜单SavePrintSubMenu界面的显示
入口参数：无
出口参数：无
/*********************************************/
void SavePrintSubMenu_Paintintial();
void SavePrintSubMenu_Paintintial()
{
	byte i;

	if(LANGUAGE==0)	//英文菜单
	{

		  
		CTAB[4]='*';  CTAB[5]='P';   CTAB[6]='R';  CTAB[7]='I'; 
		CTAB[8]='N';  CTAB[9]='T'; CTAB[10]='*';
		CW_PR(9,14,11);	//第一行显示内容"PRINT"

		CTAB[5]='S';  CTAB[6]='I';   CTAB[7]='N';   CTAB[8]='G'; 
		CTAB[9]='L';  CTAB[10]='E';  CTAB[12]='P';  CTAB[13]='R'; 
		CTAB[14]='I';  	 
		CW_PR(8,16,15);	//第二行显示内容"SINGLE PRI"

		CTAB[5]='S';  CTAB[6]='T';   CTAB[7]='A';   CTAB[8]='T'; 
		CTAB[9]='E';  CTAB[11]='P';  CTAB[12]='R'; 
		CTAB[13]='I'; 
		CW_PR(8,17,14);	//第三行显示内容"STATE PRI"

		CTAB[5]='P';  CTAB[6]='I';   CTAB[7]='T';   CTAB[8]='C'; 
		CTAB[9]='H';  CTAB[11]='P';  CTAB[12]='R';  CTAB[13]='I';
		CW_PR(8,18,14);	//第四行显示内容"PITCH PRI"		
	}

	else			//中文菜单
	{
		CCW_PR1(15,100,0xb4f2,1);	//第一行显示内容"打印"
		CCW_PR1(17,100,0xd3a1,1);
		
		CCW_PR1(13,118,0xb5a5,1);	//第二行显示内容"单条信息"
		CCW_PR1(15,118,0xccf5,1);
		CCW_PR1(17,118,0xd0c5,1);
		CCW_PR1(19,118,0xcfa2,1);


				
		CCW_PR1(13,136,0xd7b4,1);	//第三行显示内容"状态"
		CCW_PR1(15,136,0xccac,1);

				
		CCW_PR1(13,154,0xc5fa,1);	//第四行显示内容"批处理"
		CCW_PR1(15,154,0xb4a6,1);
		CCW_PR1(17,154,0xc0ed,1);		
	}


	WFRAME();						//弹出子菜单框图显示
	W_DIAMOND(11,LANGUAGE?122:16);	//选定框的显示
	W_HDIAMOND(11,LANGUAGE?140:17);
	W_HDIAMOND(11,LANGUAGE?158:18);
	
	if(BUFFER2[0]!=0)				//保证选定框对应BUFFER2[0]返回值
	{
		W_DIAMOND(11,LANGUAGE?(122+BUFFER2[0]*18):(16+BUFFER2[0]));
		W_HDIAMOND(11,LANGUAGE?122:16);	
	}
	
}

//********************************************/
/*	功能；上下按键处理函数，选择所需选项
入口参数：无
出口参数：无
/*********************************************/
void SavePrintSubMenu_Updn();
void SavePrintSubMenu_Updn()
{
	if(BUFFER2[0]>=0&&BUFFER2[0]<=2)
	{
		if(G_Key == UP)
		{
			G_Key=0;
			if(BUFFER2[0]>0)
			{
				BUFFER2[0]--;
				W_DIAMOND(11,LANGUAGE?(122+BUFFER2[0]*18):(16+BUFFER2[0]));	
		    	W_HDIAMOND(11,LANGUAGE?(140+BUFFER2[0]*18):(17+BUFFER2[0]));
			}
		}
		
		if(G_Key == DOWN)
		{
			G_Key=0;
			if(BUFFER2[0]<2)
			{			
				BUFFER2[0]++;
				W_DIAMOND(11,LANGUAGE?(122+BUFFER2[0]*18):(16+BUFFER2[0]));
		    	W_HDIAMOND(11,LANGUAGE?(104+BUFFER2[0]*18):(15+BUFFER2[0]));				
			}			
		}
	}

}

//**************************************************************/
/*	功能；CLR按键处理函数，返回上一级菜单存储菜单SaveSubMenu
入口参数：无
出口参数：无
/***************************************************************/
void SavePrintSubMenu_Return();
void SavePrintSubMenu_Return()
{
	if(G_Key == CLR)
	{
		G_Key=0;		//按键清零
		BUFFER2[0]=0;	//本菜单使用的全局变量清零
		FLAG=0;			//结束循环
		STATE=20;		//SaveSubMenu的状态为20
	}
}

//*****************************************************/
/*	功能；ENT按键处理函数，对选定选项进行操作
入口参数：无
出口参数：无
/*****************************************************/
void SavePrintSubMenu_Dealing();
void SavePrintSubMenu_Dealing()
{
	if(G_Key == ENT&&STATE==201)
	{

		FLAG=0;		//结束循环
		switch(BUFFER2[0])
		{
			case 0:	
			{
				STATE=13;			//进入Message_PrintSubmenu界面
				State13parameter=1;	//入口参数1，打印单条信息
				break;
			}
			case 1:
			{
				STATE=13;			//进入Message_PrintSubmenu界面
				State13parameter=2;	//入口参数2，打印状态		
				break;
			}
			default:
			{
				STATE=2010;			//进入SavePitchPrint，状态2010
				break;
			}
		}
		G_Key=0;	//按键清零
		BUFFER2[0]=0;
	}
}



/*********************************************************/
/*	功能：打印选项的选择，包括单挑，状态，批处理
          使用全局变量BUFFER2[0]:0 单挑 1 状态 2 批处理
入口参数：无
出口参数：无
/*********************************************************/
void RunSavePrintSubMenu()
{
    maske=0;
    maskc=0;
	SavePrintSubMenu_Paintintial();
	while(FLAG)
	{
		SavePrintSubMenu_Updn();
		SavePrintSubMenu_Return();
		SavePrintSubMenu_Dealing();
		run_tip();
	}
}