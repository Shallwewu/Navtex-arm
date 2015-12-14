#include <stdio.h>
#include <stdlib.h>
#include "lcddrive.h"
#include "run.h"
#include "define.h"
#include "code.h"
/*********************************************/
/*	功能：排序中显示函数
入口参数：无
出口参数：无
/*********************************************/
void SaveRanking_Paintintial();
void SaveRanking_Paintintial()
{
	unsigned char i;
	WFRAME();		//弹出子菜单框图显示
	
    if(LANGUAGE==0)	//英文菜单
    {
	    CTAB[4]='R';  CTAB[5]='A';   CTAB[6]='N';   CTAB[7]='K';   CTAB[8]='I';
	    CTAB[9]='N';  CTAB[10]='G';         
	    CW_PR(8,17,11);  
	 	CCW_PR1(19,132,0xa1ad,1);
		CCW_PR1(21,132,0xa1ad,1);     	
    }
    
    else			//中文菜单
    {
  		CCW_PR1(13,128,0xc5c5,1);	//第一行显示内容"排序中。　。"
		CCW_PR1(15,128,0xd0f2,1);
		CCW_PR1(17,128,0xd6d0,1);
		CCW_PR1(19,128,0xa1ad,1);
		CCW_PR1(21,128,0xa1ad,1);
    }

}

//**************************************************************/
/*	功能；自动退出本菜单函数
入口参数：无
出口参数：无
/***************************************************************/
void SaveRanking_Return();
void SaveRanking_Return()	//排序完毕后自动返回到信息存储界面
{

	BUFFER[0]=0;		//使用的全局变量全部清零
	BUFFER1[0]=0;		
	BUFFER2[0]=0;
	BUFFER3[0]=0;	
	LANHELP=1;			//LANHELP恢复初始值
	STATE=2;			//Savemenu状态为2
	if(Rankback==0)	State2parameter=0;	//入口参数0，Savemenu作为存储界面
	else State2parameter=5;				//入口参数2，Savemenu作为锁定界面
	Rankback=0;
	CLEAR1();
}


/***************************************************************/
/*	功能；排序函数，排序提示：排序中。。。
		  BUFFER2[0]:全部	518khz	490khz	4209.5khz
		  BUFFER3[0]:时间	发射台	信息类别	未读信息	航行警告区
入口参数：无
出口参数：无
/***************************************************************/
void RunSaveRanking()
{

	LANHELP=2;	//在中文菜单下，弹出菜单边框仍旧使用英文边框
	SaveRanking_Paintintial();
	Rankfuction(BUFFER3[0],BUFFER2[0]);
	SaveRanking_Return();
  	
}