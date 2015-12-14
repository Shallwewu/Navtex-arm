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
void RecoverFactory_Diamond();
void RecoverFactory_Diamond()
{
	if(BUFFER2[0]==0)	//方框一选中
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


//********************************************/
/*	功能：RecoverFactory 界面的显示
入口参数：无
出口参数：无
/*********************************************/
void RecoverFactory_Paintintial();
void RecoverFactory_Paintintial()
{
	unsigned char i;
//	CLEAR2();		//弹出子菜单区域数据清空
	WFRAME();		//弹出子菜单框图显示
	if(LANGUAGE==0)	//英文
	{

	   	CTAB[2]='S';   CTAB[3]='U';    CTAB[4]='R';     CTAB[5]='E';
	   	CTAB[7]='R';   CTAB[8]='E'; 
	   	CTAB[9]='C';   CTAB[10]='O';   CTAB[11]='V';	CTAB[12]='E';
	   	CTAB[13]='R';  CTAB[14]='?';
	    CW_PR(9,15,15);	//表头 SETUP

	    CTAB[5]='O';  CTAB[6]='K';
	    CW_PR(9,17,15);	//第一行内容:OK
	      
	    CTAB[5]='C';  CTAB[6]='A';  CTAB[7]='N';  CTAB[8]='C';  CTAB[9]='E'; 
	    CTAB[10]='L';
	    CW_PR(9,18,14);	//第二行内容：CANCEL
	    
	}
	
	else			//中文
	{
 		CCW_PR1(13,104,0xc8b7,1);	//第一行显示内容"确认恢复"
 		CCW_PR1(15,104,0xc8cf,1);
  		CCW_PR1(17,104,0xbbd6,1);
  		CCW_PR1(19,104,0xb8b4,1);		
		
 		CCW_PR1(14,128,0xc8b7,1);	//第二行显示内容"确认"
		CCW_PR1(16,128,0xc8cf,1);

  		
   		CCW_PR1(14,148,0xc8a1,1);	//第三行显示内容"取消"
		CCW_PR1(16,148,0xcffb,1);

 	}

	RecoverFactory_Diamond();		//调用框图显示函数
	
}  

//********************************************/
/*	功能；上下按键处理函数，选择所需选定项
入口参数：无
出口参数：无
/*********************************************/
void RecoverFactory_Updn();
void RecoverFactory_Updn() 
{
	if (G_Key==UP||G_Key==DOWN)
	{
		G_Key=0;
		BUFFER2[0]=(BUFFER2[0]+1)%2;
		RecoverFactory_Diamond();	//调用框图显示函数
	}
	
} 


//**************************************************************/
/*	功能；ENT按键处理函数，对选定框进行选定操作
入口参数：无
出口参数：无
/***************************************************************/
void RecoverFactory_Dealing();
void RecoverFactory_Dealing()
{
	if (G_Key==ENT)
	{
		G_Key=0;
		FLAG=0;	
		if(BUFFER2[0]==0)		//恢复出厂设置，返回到信息正文界面	
		{
	//   	COPCTL&=~COPCTL_CEN_MASK;
			IntialOriginal();		//接收机初始化配置
	//		COPCTL|=COPCTL_CEN_MASK;
		}
		
		if(BUFFER2[0]==1)
		{
			STATE=44;				//Maintain状态为13
			State44parameter=10;	//入口参数0，表示从子菜单返回
			BUFFER2[0]=0;
		}
	}
}

//**************************************************************/
/*	功能；出厂设置
入口参数：无
出口参数：无
/***************************************************************/
void RunRecoverFactory()
{

	unsigned char first1=0;
	unsigned char first2=0;
	RecoverFactory_Paintintial();

	while(FLAG)
	{	
		RecoverFactory_Updn();
		RecoverFactory_Dealing();
		run_tip();
	}
  	
}