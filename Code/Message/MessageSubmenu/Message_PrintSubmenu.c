#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "printer.h"
#include "code.h"
//********************************************/
/*	功能：子菜单Message_PrintSubmenu界面的显示
入口参数：无
出口参数：无
/*********************************************/
void Message_Printsubmenu_Paintintial();
void Message_Printsubmenu_Paintintial()
{

	WFRAME();		//弹出子菜单框图显示
	if(LANGUAGE==0)	//英文菜单
	{

	   	CTAB[2]=42;   CTAB[3]='P';   CTAB[4]='R';   CTAB[5]='I'; 	CTAB[6]='N';
	    CTAB[7]='T';  CTAB[9]='M';   CTAB[10]='S';  CTAB[11]='G';   CTAB[12]=42; 
	    if(State13parameter==0)CW_PR(9,10,13);	//第一行显示内容"PRINT MSG"
	    else CW_PR(9,15,13);
	    
	    CTAB[4]='O';  CTAB[5]='K';  
	    if(State13parameter==0)CW_PR(9,11,6);	//第二行显示内容"OK"
	    else CW_PR(9,17,13);
	    
	    CTAB[4]='C';  CTAB[5]='A';  CTAB[6]='N';  CTAB[7]='C';  CTAB[8]='E'; 
	    CTAB[9]='L'; 
	    if(State13parameter==0)	CW_PR(9,12,10);//第三行显示内容"CANCEL"
	    else CW_PR(9,18,13);		
	}

	else				//中文菜单
	{
 		CCW_PR1(13,104,0xb4f2,1);	//第一行显示内容"打印信息"
 		CCW_PR1(15,104,0xd3a1,1);
 		CCW_PR1(17,104,0xd0c5,1);
  		CCW_PR1(19,104,0xcfa2,1);
  				
 		CCW_PR1(13,128,0xc8b7,1);	//第二行显示内容"确认"
		CCW_PR1(15,128,0xc8cf,1);
  		
   		CCW_PR1(13,148,0xc8a1,1);	//第三行显示内容"取消"
		CCW_PR1(15,148,0xcffb,1);
 	}
    

    W_DIAMOND(11,LANGUAGE?132:(State13parameter==0?11:17));	//选定框显示
    W_HDIAMOND(11,LANGUAGE?152:(State13parameter==0?12:18));
	
}

//********************************************/
/*	功能；上下按键处理函数，选择所需选定项
		  并在液晶界面进行显示
入口参数：无
出口参数：无
/*********************************************/
void Message_Printsubmenu_Updn();
void Message_Printsubmenu_Updn()
{
	if (G_Key==UP||G_Key==DOWN)
	{
		G_Key=0;
		BUFFERPRINT=(BUFFERPRINT+1)%2;	//BUFFERPRINT用于记录选定哪个选项
		if(BUFFERPRINT==0)				//选择选定框一
		{
		    W_DIAMOND(11,LANGUAGE?132:(State13parameter==0?11:17));
		    W_HDIAMOND(11,LANGUAGE?152:(State13parameter==0?12:18));	
		}
		
		else							//选择选定框二
		{
  	  		W_HDIAMOND(11,LANGUAGE?132:(State13parameter==0?11:17));
    		W_DIAMOND(11,LANGUAGE?152:(State13parameter==0?12:18));
		}
	}
} 



//*********************************************************/
/*	功能；ENT按键处理函数，对选定框进行相应操作
入口参数：无
出口参数：无
/*********************************************************/
void Message_Printsubmenu_Dealing();
void Message_Printsubmenu_Dealing()
{
	if(G_Key == ENT)
	{
		G_Key=0;			//按键清零
		if(BUFFERPRINT==0)	//进行打印操作
		{
			if(Checkinfo.Printerror == 0)	//打印机正常工作跳转至打印界面Message_Printing
			{
				BUFFERPRINT=0;				//进入打印界面不会返回本界面，BUFFERPRINT清零
				FLAG=0;						//结束循环
				STATE=16;					//Messsage_printing界面状态为16
//				Printmessage(Messagenownumber);					//zzy隐去，因为界面中本身已经有打印函数		
			}
			
			else						  	//打印机故障跳转至打印出错界面Message_PrintError
			{

				BUFFERPRINT=0;				//进入出错界面后肯定不会回到本届面，所以直接清零
				              				//出错界面返回的是本届面的上一级界面所以出错界面可以直接返回
				FLAG=0;						//结束循环
				STATE=15;					//Message_PrintError界面状态为15
			}
		
		}
			
		else				//取消打印操作
		{
			BUFFERPRINT=0;	//返回上一级菜单，BUFFERPRINT清零
			
			switch(PublicReturn)
			{
				case 0:STATE=11;break;	//返回到信息正文界面子菜单	
				case 1:STATE=201;break;	//返回到存储界面的打印子菜单
				case 2:STATE=201;break;	//返回到存储界面的打印子菜单
				case 3:STATE=200;State200parameter=10;break;//返回到打印复选界面				
				default:break;			
			}
			
			FLAG=0;			//结束循环
			PublicReturn=0;	//返回参数清零
		
		}
	}
	
		
}


//**************************************************************/
/*	功能；本界面作为打印界面的公共界面，用PublicReturn来记录由何菜单调入
		  0 由信息内容界面调用
		  1 由打印单条信息界面调用
		  2 由打印状态界面调用
		  3 由打印人工复选界面选定信息调用		  
		  BUFFERPRINT用于记录本界面选择选定框
入口参数：byte 类型，记录从何菜单进入
出口参数：无
/***************************************************************/

void RunMessage_PrintSubmenu(byte into)
{
    maske=0;
    maskc=0;
	PublicReturn=into;
//	Checkprint();	//调入打印机的检测程序
	Message_Printsubmenu_Paintintial();
	
	while(FLAG)
	{
		Message_Printsubmenu_Updn();
		Message_Printsubmenu_Dealing();
		run_tip();
	}
  	
}