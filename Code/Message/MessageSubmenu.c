#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "Eprom.h"
#include "code.h"
//********************************************/
/*	功能：完成上下选定框的显示
入口参数：无
出口参数：无
/*********************************************/
void Messagesubmenu_Diamond();
void Messagesubmenu_Diamond()
{
	if(BUFFER1[0]==0)	//方框一选中
	{
	    W_DIAMOND(12,LANGUAGE?132:11);
	    W_HDIAMOND(12,LANGUAGE?152:12);
	}
	
	else				//方框二选中
	{
		W_DIAMOND(12,LANGUAGE?152:12);
    	W_HDIAMOND(12,LANGUAGE?132:11);	
	}	
}


//********************************************/
/*	功能：Messagesubmenu 界面的显示
入口参数：无
出口参数：无
/*********************************************/
void Messagesubmenu_Paintintial();
void Messagesubmenu_Paintintial()
{
	byte i;
	WFRAME();		//弹出子菜单框图显示
    IntialLCD(1);
	if(LANGUAGE==0)	//英文
	{

	    
	   	CTAB[4]=42;  CTAB[5]='S';   CTAB[6]='E';  CTAB[7]='T'; 
	   	CTAB[9]='U';  CTAB[10]='P'; CTAB[11]=42;
	    CW_PR(9,10,12);	//表头 SETUP
	    

	      
	    CTAB[5]='U';  CTAB[6]='N';  CTAB[7]='L';  CTAB[8]='O';  CTAB[9]='C'; 
	    CTAB[10]='K'; CTAB[12]='M'; CTAB[13]='S'; CTAB[14]='G';
	    CW_PR(9,11,15);	//第一行内容：UNLOCK MSG
	    

	      
	    CTAB[5]='P';  CTAB[6]='R';  CTAB[7]='I';  CTAB[8]='N';  CTAB[9]='T'; 
	    CTAB[11]='M'; CTAB[12]='S'; CTAB[13]='G';
	    CW_PR(9,12,14);	//第二行内容：PRINT MSG
	    
	    if(Messagesavetop[Messagetoprank[Messagenownumber]].lock==0)
	    {
			CTAB[5]='L';  CTAB[6]='O';  CTAB[7]='C'; 
			CTAB[8]='K';  CTAB[10]='M';  CTAB[11]='S'; CTAB[12]='G';
			CW_PR(9,11,13);
	    }   			//子菜单从属信息非锁定，第一行内容：LOCK MSG
	    	
	}
	
	else			//中文
	{
 		CCW_PR1(15,104,0xc9e8,1);	//第一行显示内容"设置"
 		CCW_PR1(18,104,0xd6c3,1);
		
 		CCW_PR1(14,128,0xbde2,1);	//第二行显示内容"解锁信息"
		CCW_PR1(16,128,0xcbf8,1);
 		CCW_PR1(18,128,0xd0c5,1);
  		CCW_PR1(20,128,0xcfa2,1);
  		
   		CCW_PR1(14,148,0xb4f2,1);	//第三行显示内容"打印信息"
		CCW_PR1(16,148,0xd3a1,1);
 		CCW_PR1(18,148,0xd0c5,1);
  		CCW_PR1(20,148,0xcfa2,1);
	    
	    if(Messagesavetop[Messagetoprank[Messagenownumber]].lock==0)
	    {
 			CCW_PR1(14,128,0xcbf8,1);
			CCW_PR1(16,128,0xb6a8,1);
	    } 							//子菜单从属信息非锁定，第二行显示内容"锁定信息"
 	}

	Messagesubmenu_Diamond();		//调用框图显示函数
	
}  

//********************************************/
/*	功能；上下按键处理函数，选择所需选定项
入口参数：无
出口参数：无
/*********************************************/
void Messagesubmenu_Updn();
void Messagesubmenu_Updn() 
{
	if (G_Key==UP||G_Key==DOWN)
	{
		G_Key=0;
		BUFFER1[0]=(BUFFER1[0]+1)%2;
		Messagesubmenu_Diamond();	//调用框图显示函数
	}
	
} 

//**************************************************************/
/*	功能；CLR按键处理函数，返回上一级菜单信息内容菜单 Message
入口参数：无
出口参数：无
/***************************************************************/
void Messagesubmenu_Return();
void Messagesubmenu_Return()	
{
	if (G_Key==CLR)
	{
		BUFFER1[0]=0;		//清零
		G_Key=0;			//按键清零
		FLAG=0;				//结束循环
		STATE=1;			//状态1是 Message 界面
		State1parameter=10;	//入口参数10，表示从子菜单返回
	}
	
}
//**************************************************************/
/*	功能；ENT按键处理函数，对选定框进行选定操作
入口参数：无
出口参数：无
/***************************************************************/
void Messagesubmenu_Dealing();
void Messagesubmenu_Dealing()
{
	if (G_Key==ENT&&STATE==11)
	{
		G_Key=0;
		FLAG=0;	
		if(BUFFER1[0]==0)		//进行信息的锁定或解锁，跳转至Message_LockSubmenu界面	
		{
			STATE=12;			//Message_LockSubmenu状态为12		
		}
		
		if(BUFFER1[0]==1)		//进行信息的打印，跳转至Message_PrintSubmenu界面
		{
			STATE=13;			//Message_PrintSubmenu状态为13
			State13parameter=0;	//入口参数0，表示由信息正文界面调用
		}
	}
}

//**************************************************************/
/*	功能；Message界面第一级子菜单，实现对信息正文的打印
		  或解锁，锁定的相关操作
入口参数：无
出口参数：无
/***************************************************************/
void RunMessageSubmenu()
{
    maske=0;
    maskc=0;
	Messagesubmenu_Paintintial();

	while(FLAG)
	{	
		Messagesubmenu_Updn();
		Messagesubmenu_Return();
		Messagesubmenu_Dealing();
		run_tip();
	}
  	
}