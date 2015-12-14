#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "MessageDeal.h"
#include "Eprom.h"
#include "code.h"
//********************************************/
/*	功能：子菜单Message_Locksubmenu界面的显示
入口参数：无
出口参数：无
/*********************************************/
void Message_Locksubmenu_Paintintial();
void Message_Locksubmenu_Paintintial()
{
	byte i;
	WFRAME();		//弹出子菜单框图显示
	if(LANGUAGE==0)	//英文界面
	{

	    CTAB[4]='*';	CTAB[3]='U';   CTAB[4]='N';   CTAB[5]='L'; 	CTAB[6]='O';
	    CTAB[7]='C';   CTAB[8]='K';   CTAB[10]='M';  CTAB[11]='S';   CTAB[12]='G'; CTAB[13]='*';
	    CW_PR(9,10,14);		//第一行显示内容"UNLOCK MSG"
	    

	      
	    CTAB[4]='O';  CTAB[5]='K';  
	    CW_PR(9,11,6);		//第二行显示内容"OK"
	    

	      
	    CTAB[4]='C';  CTAB[5]='A';  CTAB[6]='N';  CTAB[7]='C';  CTAB[8]='E'; 
	    CTAB[9]='L'; 
	    CW_PR(9,12,10);		//第三行显示内容"CANCEL"
	    
	    if(Messagesavetop[Messagetoprank[Messagenownumber]].lock==0)
	    {
		    CTAB[4]='*';   CTAB[5]='L'; 	CTAB[6]='O';
			CTAB[7]='C';  CTAB[8]='K';   CTAB[10]='M';  CTAB[11]='S';   CTAB[12]='G'; CTAB[13]='*';
			CW_PR(9,10,14);	//子菜单从属信息非锁定，第一行内容：LOCK MSG	
	    }		
	}
	
	else			//中文界面
	{
 		CCW_PR1(13,104,0xbde2,1);		//第一行显示内容"解锁信息"
 		CCW_PR1(15,104,0xcbf8,1);
 		CCW_PR1(17,104,0xd0c5,1);
  		CCW_PR1(19,104,0xcfa2,1);
  				
 

 		CCW_PR1(13,128,0xc8b7,1);		//第二行显示内容"确认"
		CCW_PR1(15,128,0xc8cf,1);

  		
   		CCW_PR1(13,148,0xc8a1,1);		//第三行显示内容"取消"
		CCW_PR1(15,148,0xcffb,1);
			    
	    if(Messagesavetop[Messagetoprank[Messagenownumber]].lock==0)
	    {
 			CCW_PR1(13,104,0xcbf8,1);	//子菜单从属信息非锁定,第一行显示内容"锁定信息"
			CCW_PR1(15,104,0xb6a8,1);
	    } 
 	}
    
    W_DIAMOND(11,LANGUAGE?132:11);	//选定框显示	
    W_HDIAMOND(11,LANGUAGE?152:12);
}

//********************************************/
/*	功能；上下按键处理函数，选择所需选定项
		  并在液晶界面进行显示
入口参数：无
出口参数：无
/*********************************************/

void Message_Locksubmenu_Updn();
void Message_Locksubmenu_Updn()
{
	if (G_Key==UP||G_Key==DOWN)
	{
		G_Key=0;
		BUFFER2[0]=(BUFFER2[0]+1)%2;//BUFFERP[2]用于记录选定哪个选项
		if(BUFFER2[0]==0)			//选择选定框一
		{
		    W_DIAMOND(11,LANGUAGE?132:11);
		    W_HDIAMOND(11,LANGUAGE?152:12);	
		}
		
		else						//选择选定框二	
		{
  	  		W_HDIAMOND(11,LANGUAGE?132:11);
    		W_DIAMOND(11,LANGUAGE?152:12);
		}
	}
}


//*********************************************************/
/*	功能；ENT按键处理函数，对选定框进行相应操作
入口参数：无
出口参数：无
/*********************************************************/
void Message_Locksubmenu_Dealing();
void Message_Locksubmenu_Dealing()
{
	byte channel=0;
	if (G_Key==ENT)
	{
		G_Key=0;
	
		if(BUFFER2[0]==0)	//进行解锁或锁定操作
		{
			if(Messagesavetop[Messagetoprank[Messagenownumber]].lock==0)//信息的锁定
			{
				channel=Messagesavetop[Messagetoprank[Messagenownumber]].frequency;	//存储值1,2,3分别代表通道518,490,4209.5
			
				if(Messageinfo.locknumber[channel]<50) 				//当前信息所在通道锁定条数仍可继续锁定
				{
					MsgLock(Messagenownumber);	//对当前信息进行锁定
					BUFFER1[0]=0;				//越级跳出，前一级别菜单使用BUFFER1[0]置零
					STATE=1;					//Message菜单状态为1
					State1parameter=10;			//入口参数为10，表明从子菜单返回
				}										
															
				else 							//超过当前通道的锁定条数50，进入超出容量界面Message_OverCapacity
				{
					STATE=14;					//Message_OverCapacity菜单状态为14
					State14parameter=0;			//入口参数为0，表示由信息内容界面的锁定界面调用				
				}										
			}
	
		
		    else //信息的解锁
			{
				MsgUnlock(Messagenownumber);	//存储菜单中对应信息的解锁	
				BUFFER1[0]=0;					//越级跳出，前一级别菜单使用BUFFER1[0]置零
				STATE=1;						//Message菜单状态为1
//				State1parameter=10;				//入口参数为10或3，以在MsgUnlock()函数中改变
			}
			
/*			if(Returntype==2) //针对于锁定菜单
			{
						
				MsgUnlock(Messagenownumber);	//存储菜单中对应信息的解锁		
				BUFFER1[0]=0;					//越级跳出，前一级别菜单使用BUFFER1[0]置零
				STATE=1;						//Message菜单状态为1
//				State1parameter=10;				//入口参数为10，表明从子菜单返回				
			}	*/
			
		}
		

		if(BUFFER2[0]==1)	//返回前一级菜单MessageSubmenu
		{
			STATE=11;		//MessageSubmenu的状态为11
		}
		BUFFER2[0]=0;		//按下ENT键必将跳出本界面所以BUFFER2[0]和FLAG清零
		FLAG=0;				//结束循环				
	}
}










//**************************************************************/
/*	功能：本界面实现信息的解锁或锁定，用全局变量Returntype来
		  区别锁定界面和存储界面。若是存储界面，根据lock位判断，
		  进行解锁和锁定，若是锁定界面则只能进行解锁。进入本界面
		  后，若跳出则不会返回到本界面，即每次进入该界面都是新状
		  态，即要么直接返回上级界面，若进入子界面，子界面就越级
		  返回，不会返回本界面
入口参数：byte 类型，记录从何菜单进入
出口参数：无
/***************************************************************/
void RunMessage_LockSubmenu()
{
    maske=0;
    maskc=0;
 	Message_Locksubmenu_Paintintial();

	while(FLAG)
	{
		Message_Locksubmenu_Updn();
		Message_Locksubmenu_Dealing();
		run_tip();
	}
  	
}