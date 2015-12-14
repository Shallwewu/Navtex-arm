#include <stdio.h>
#include <stdlib.h>
#include  "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "MessageDeal.h"
#include "code.h"
/********************************************************/
/*功能；锁定复选或打印复选的显示
入口参数：无
出口参数：无
/********************************************************/
void SaveLockSubSure_Paintintial();
void SaveLockSubSure_Paintintial()
{
	byte i;
	WFRAME();		//弹出子菜单边框的显示
	
	if(LANGUAGE==0)	//英文界面
	{
		CTAB[2]=42;   CTAB[3]='L';   CTAB[4]='O';   CTAB[5]='C'; 	CTAB[6]='K';
	    CTAB[8]='M';  CTAB[9]='S';   CTAB[10]='G'; CTAB[11]=42;
	    CW_PR(9,15,12);	//第一行显示内容"*LOCK MSG*"
	      
	    CTAB[4]='O';  CTAB[5]='K';  
	    CW_PR(9,17,6);	//第二行显示内容"OK"
	      
	    CTAB[4]='C';  CTAB[5]='A';  CTAB[6]='N';  CTAB[7]='C';  CTAB[8]='A'; 
	    CTAB[9]='L'; 
	    CW_PR(9,18,10);	//第三行显示内容"CANCAL"
	    	
	   	if(State2000parameter==1)
		{

		   	CTAB[2]=42;   CTAB[3]='U';   CTAB[4]='N';   CTAB[5]='L'; 	CTAB[6]='O';
		    CTAB[7]='C';  CTAB[8]='K';   CTAB[10]='M';  CTAB[11]='S';   CTAB[12]='G'; CTAB[13]=42;
		    CW_PR(9,15,14);	
		}				//本界面作为解锁菜单使用时，第一行显示内容：UNLOCK MSG
	}
      
	else
	{
 		CCW_PR1(13,104,0xcbf8,1);	//第一行显示内容"锁定信息"
 		CCW_PR1(15,104,0xb6a8,1);
 		CCW_PR1(17,104,0xd0c5,1);
  		CCW_PR1(19,104,0xcfa2,1);
  				
 		CCW_PR1(13,128,0xc8b7,1);	//第二行显示内容"确认"
		CCW_PR1(15,128,0xc8cf,1);

   		CCW_PR1(13,148,0xc8a1,1);	//第三行显示内容"取消"
		CCW_PR1(15,148,0xcffb,1);
	    
	    if(State2000parameter==1)	//本界面作为解锁菜单使用时，第一行显示内容：解锁信息
	    {
 			CCW_PR1(13,128,0xbde2,1);	
			CCW_PR1(15,128,0xcbf8,1);
	    } 
 	}
    
    W_DIAMOND(11,LANGUAGE?132:17);	//选定框的显示，初始化选择选定框1
    W_HDIAMOND(11,LANGUAGE?152:18);
	
}

//********************************************/
/*	功能；上下按键处理函数，选择所需选项
入口参数：无
出口参数：无
/*********************************************/
void SaveLockSubSure_Updn();
void SaveLockSubSure_Updn()
{
	if(G_Key==UP||G_Key==DOWN)
	{

		BUFFER3[0]=(BUFFER3[0]+1)%2;
		if(BUFFER3[0]==0)		//根据BUFFER[3]中的内容，对选定选项加黑
		{
		    W_DIAMOND(11,LANGUAGE?132:17);
		    W_HDIAMOND(11,LANGUAGE?152:18);	
		}
		else		
		{
  	  		W_HDIAMOND(11,LANGUAGE?132:17);
    		W_DIAMOND(11,LANGUAGE?152:18);
		}	
		G_Key=0;				//按键清零，选择信息存储在BUFFER[3]中
	}
}

//*****************************************************/
/*	功能；ENT按键处理函数，对选定选项进行操作，即
          锁定(解锁)操作或者取消返回操作
入口参数：无
出口参数：无
/*****************************************************/
void SaveLockSubSure_Dealing();
void SaveLockSubSure_Dealing()	//执行完毕返回到存储菜单
{
	if(G_Key == ENT)
	{

		if(BUFFER3[0] == 0)  	//锁定(解锁)操作
		//按下确定键则对应复选信息在存储数组里面对应的lock置一，
								//同时把信息加到锁定数组的最后
		{
		 	int i,j;
			if(State2000parameter==0)	//锁定菜单，进行锁定
			{
				for(i=0;i<Messagenumber;i++)
				{	
					if(Messagesavetop[Messagetoprank[i]].select==1)		//对每条复选的信息，进行锁定
					{
						Messagesavetop[Messagetoprank[i]].select=0;		//复选标记清零
						MsgLock(i);						//进行锁定操作
					}
				}
			}
			
			if(State2000parameter==1)	//解锁菜单，进行解锁
			{
				for(i=0;i<Messagenumber;i++)
				{	
					if(Messagesavetop[Msglockrank[i]].select==1)
					{
						Messagesavetop[Msglockrank[i]].select=0;		//复选标记清零
						for(j=0;j<Messageinfo.savenumber[0];j++)
						{
							if(Msglockrank[i]==Messagetoprank[j]) break;
						}
						MsgUnlock(j);					//进行解锁，参数1表示锁定列表
					}
				}	
			}
			
			BUFFERSELECT[21]=0;
			BUFFER1[0]=0;	//直接跳至存储主菜单，需要对BUFFER1[0]清零		
			FLAG=0;			//结束循环
			STATE=2;		//Savemenu状态为2
			if(State2000parameter==0)
			{
				State2parameter=1;	//入口参数1，Savemenu作为存储菜单					
			}
			else 
			{
				
				State2000parameter=0;
				State2parameter=5;	//入口参数，Savemenu作为锁定菜单
			}
		}
		
		else				//取消操作
		{

			BUFFER3[0]=0;	//本菜单使用的全局变量清零
			FLAG=0;			//结束循环			
			if(State2000parameter==0)	//本菜单作为锁定复选菜单的子菜单，需返回到锁定复选菜单
			{	
				STATE=200;				//SaveLockSubmenu的状态为200
				State200parameter=10;	//入口参数10，表示从子菜单返回				
			}
			
			else						//本菜单作为解锁复选菜单的子菜单，需返回到解锁复选菜单
			{
				State2000parameter=0;	//本菜单使用的全局变量清零
				STATE=300;				//LockLockSubMenu的状态为300
				State300parameter=10;	//入口参数10，表示从子菜单返回
			} 
		}
		G_Key=0;				//按键清零		
	}
}


/*********************************************************/
/*	功能；锁定复选和解锁复选的共用子菜单，用于进行对应信息的
          锁定或解锁，本菜单使用到的全局变量如下：
          State2000parameter 入口参数的保护，1作为解锁复选
          的子菜单，0作为锁定复选的子菜单
          BUFFER3[0] 选定项信息的存储

入口参数：into  记录从何菜单进入
出口参数：无
/*********************************************************/
void RunSaveLockSubSure(byte into)
{
    maske=0;
    maskc=0;
	State2000parameter=into;



	SaveLockSubSure_Paintintial();
	
	while(FLAG)
	{
		SaveLockSubSure_Updn();
		SaveLockSubSure_Dealing();
		run_tip();
	}
  	
}