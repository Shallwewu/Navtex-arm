#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"
#include "lcddrive.h"
#include "code.h"
//********************************************/
/*	功能：子菜单Message_Overcapacity界面的显示
入口参数：无
出口参数：无
/*********************************************/
void Message_Overcapacity_Paintintial();
void Message_Overcapacity_Paintintial()
{
	byte i;
	
	if(LANGUAGE==0)	//英文菜单	
	{
 
	    CTAB[0]='N';  CTAB[1]='O';  CTAB[2]='T';  CTAB[3]='E';   CTAB[4]=':';   CTAB[5]='O';
	    CTAB[6]='V';  CTAB[7]='E';  CTAB[8]='R';  CTAB[10]='M';  CTAB[11]='S';  CTAB[12]='G';
	    if(State14parameter==0)CW_PR(9,10,13);	//第一行显示内容"NOTE: OVER MSG"
	    else CW_PR(9,14,13);

	    CTAB[0]='C';  CTAB[1]='A';   	CTAB[2]='P';  CTAB[3]='A';   CTAB[4]='C';   CTAB[5]='I';
	    CTAB[6]='T';  CTAB[7]='Y';  	CTAB[8]='!';    
	    CTAB[10]='E'; CTAB[11]='N';   CTAB[12]='T';  CTAB[13]='E';   CTAB[14]='R';
	    if(State14parameter==0)CW_PR(9,11,15);	//第二行显示内容"CAPACITAY! ENTER"
	    else CW_PR(9,16,15);
	      
	    CTAB[0]='E';	CTAB[1]='N';  CTAB[2]='T';      CTAB[4]='T';  CTAB[5]='O';   CTAB[7]='R';   CTAB[8]='E';   CTAB[9]='T';
	    CTAB[10]='U';  CTAB[11]='R';  CTAB[12]='N';  CTAB[12]='.';
	    if(State14parameter==0)CW_PR(9,12,13);	//第三行显示内容"ENT TO RETURN"	
	    else CW_PR(9,18,13);
	}
	
	else			//中文菜单
	{
 		CCW_PR1(9,104,0xcce1,1);	//第一行显示内容"提示:"
 		CCW_PR1(11,104,0xcabe,1);
 		CCW_PR1(13,104,0x1aa0,0);
  
  				
 		CCW_PR1(11,128,0xb3ac,1);	//第二行显示内容"超过锁定容量"
		CCW_PR1(13,128,0xb9fd,1);
 		CCW_PR1(15,128,0xcbf8,1);
 		CCW_PR1(17,128,0xb6a8,1);
  		CCW_PR1(19,128,0xc8dd,1);
 		CCW_PR1(21,128,0xc1bf,1);
 		CCW_PR1(23,128,0x1780,0);
 		 		
 		CCW_PR1(11,148,0xb0b4,1);	//第三行显示内容"按下ent键返回"
		CCW_PR1(13,148,0xcfc2,1);
		CCW_PR1(18,148,0xbcfc,1);
 		CCW_PR1(20,148,0xb7b5,1);
 		CCW_PR1(22,148,0xbbd8,1);
  		CCW_PR1(24,148,0x1920,0);
	
		if(State14parameter==0)
		{
			CW_PR3(15,12,'E');
		    CW_PR3(16,12,'N');
	    	CW_PR3(17,12,'T');
		}
		else
		{
			CW_PR3(15,19,'E');
		    CW_PR3(16,19,'N');
	    	CW_PR3(17,19,'T');
		}
	}
	
	WFRAME(); 		//弹出子菜单框图显示   
}


//**************************************************************/
/*	功能；ENT按键处理函数，越级跳转至第一级菜单
入口参数：无
出口参数：无
/***************************************************************/
void Message_Overcapacity_Return();
void Message_Overcapacity_Return()
{
	if(G_Key == ENT)
	{
		G_Key=0;
		FLAG=0;
	
		if(BUFFER3[0]==0)			//返回MessageSubmenu菜单 
		{
			BUFFER2[0]=0;			//从第三级菜单直接跳至第一级菜单,第二级菜单必须清零
			STATE=11;				//MessageSubmenu状态为11
		}
		
		if(BUFFER3[0]==1) 			//返回锁定复选界面
		{
			STATE=200;				//SaveLockSubmenu状态为10
			State200parameter=10;	//入口参数为10,表示从子菜单返回		
		}		
	}
	
}


//**************************************************************/
/*	功能；本界面作为锁定溢出界面的公共界面，提示信息锁定容量已满
入口参数：byte 类型，记录从何菜单进入
		  0 由信息内容界面的锁定界面调用
		  1 由锁定复选界面调用
出口参数：无
/***************************************************************/

void RunMessage_OverCapacity(byte into)
{
    maske=0;
    maskc=0;
	BUFFER3[0]=into;	//第三级菜单用BUFFER3[0]来记录入口参数
	Message_Overcapacity_Paintintial();

	while(FLAG)
	{
		Message_Overcapacity_Return();
		run_tip();
	}
  	
}