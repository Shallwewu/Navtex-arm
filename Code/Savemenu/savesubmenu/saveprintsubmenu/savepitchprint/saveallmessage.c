#include <stdio.h>
#include <stdlib.h>
#include  "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "printer.h"
#include "code.h"



void SaveAllMessage_Paintintial();
void SaveAllMessage_Paintintial()
{
	byte i;
	WFRAME();
	
	if(LANGUAGE==0)		//英文菜单
	{
		CTAB[4]='*';  CTAB[5]='P';   CTAB[6]='I'; CTAB[7]='T'; 
		CTAB[8]='C';  CTAB[9]='H';   CTAB[10]='*';
		CW_PR(9,14,11);	//第一行显示内容"PITCH"
		  
		CTAB[3]='C';  CTAB[4]='H';    CTAB[5]='A';  CTAB[6]='N';
		CTAB[7]='N';  CTAB[8]='E';    CTAB[9]='L';  CTAB[10]=':';  
		CTAB[11]='0'; 
		CW_PR(9,15,12);	//第二行显示内容"CHANNEL:0"

	    CTAB[3]='M';  CTAB[4]='S';  CTAB[5]='G';  
		CTAB[7]='T';  CTAB[8]='Y';  CTAB[9]='P';  CTAB[10]=':';	  
		CTAB[11]='0'; 
		CW_PR(9,16,12);	//第三行显示内容"MSG TYP:0"
		  
	    CTAB[3]='S';  CTAB[4]='T';  CTAB[5]='A';  CTAB[6]='T';
		CTAB[7]='I';  CTAB[8]='O';  CTAB[9]='N';  CTAB[10]=':'; 
		CTAB[11]='0'; 
		CW_PR(9,17,12);	//第四行显示内容"STATION:0"
		  
		CTAB[3]='P';   CTAB[4]='R';  CTAB[5]='I';  CTAB[6]='N';
		CTAB[7]='T'; 	CTAB[9]='M';  CTAB[10]='S';  CTAB[11]='G';
		CW_PR(9,18,12);	//第五行显示内容"PRINT MSG"
		  
		CTAB[3]='C';   CTAB[4]='A';  CTAB[5]='N';  CTAB[6]='C'; 
		CTAB[7]='A';   CTAB[8]='L';	
		CW_PR(9,19,9);	//第六行显示内容"CANCAL"		
	}
	  

	else				//中文菜单
	{
 		CCW_PR1(12,92,0xcda8,1);	//第一行显示内容"通道"
 		CCW_PR1(14,92,0xb5c0,1);
		CW_PR3(20,12,':');
		CW_PR3(21,12,'0');
		
 		CCW_PR1(12,108,0xd0c5,1);	//第二行显示内容"信息类型"
		CCW_PR1(14,108,0xcfa2,1);
 		CCW_PR1(16,108,0xc0e0,1);
		CCW_PR1(18,108,0xd0cd,1);
 		CW_PR3(20,14,':');
		CW_PR3(21,14,'0');
		 				
   		CCW_PR1(12,124,0xb7a2,1);	//第三行显示内容"发射台"
		CCW_PR1(14,124,0xc9e4,1);
 		CCW_PR1(16,124,0xcca8,1);
   		CW_PR3(20,16,':');
		CW_PR3(21,16,'0');	
		
  		CCW_PR1(12,148,0xc8b7,1);	//第四行显示内容"确定"
		CCW_PR1(14,148,0xc8cf,1);

 				
   		CCW_PR1(12,164,0xc8a1,1);	//第五行显示内容"取消"
		CCW_PR1(14,164,0xcffb,1);

	} 

	W_DIAMOND(10,LANGUAGE?96:15);	//选项框的显示
	W_HDIAMOND(10,LANGUAGE?112:16);
	W_HDIAMOND(10,LANGUAGE?128:17);
	W_HDIAMOND(10,LANGUAGE?152:18);
	W_HDIAMOND(10,LANGUAGE?168:19);
	
}

/*********************************************/
/*	功能；上下按键处理函数，选择所需选项
入口参数：无
出口参数：无
/*********************************************/
void SaveAllMessage_Updn();
void SaveAllMessage_Updn()
{
	if(BUFFER4[0]>=0&&BUFFER4[0]<=4)
	{
		if(G_Key == UP)	//上移
		{
			G_Key=0;	//按键清零
			if(BUFFER4[0]>0)
			{
				BUFFER4[0]--;	//选定项修改
				if(LANGUAGE==0)	//英文菜单选定项显示
				{
					W_DIAMOND(10,BUFFER4[0]+15);
					W_HDIAMOND(10,BUFFER4[0]+16);	
				}	
				
				else			//中文菜单选定项显示
				{
					if(BUFFER4[0]==3)
					{
						W_DIAMOND(10,LANGUAGE?152:18);
						W_HDIAMOND(10,LANGUAGE?168:19);
					}
					
					if(BUFFER4[0]==2)
					{
						W_DIAMOND(10,LANGUAGE?128:17);
						W_HDIAMOND(10,LANGUAGE?152:18);	
					}
					
					if(BUFFER4[0]==0||BUFFER4[0]==1)
					{
						W_DIAMOND(10,BUFFER4[0]*16+96);
						W_HDIAMOND(10,BUFFER4[0]*16+112);						
					}
				}
			}
		}
		if(G_Key == DOWN)	//下移
		{
			G_Key=0;		//按键清零
			if(BUFFER4[0]<4)
			{			
				BUFFER4[0]++;		//选定项加一
				if(LANGUAGE==0)		//英文菜单，LCD页面中显示修改完毕的选定项
				{
					W_DIAMOND(10,BUFFER4[0]+15);
					W_HDIAMOND(10,BUFFER4[0]+14);				
				}

				
				else				//中文菜单，LCD页面中显示修改完毕的选定项
				{
					if(BUFFER4[0]==4)
					{
						W_HDIAMOND(10,LANGUAGE?152:18);
						W_DIAMOND(10,LANGUAGE?168:19);
					}
					
					if(BUFFER4[0]==3)
					{
						W_HDIAMOND(10,LANGUAGE?128:17);
						W_DIAMOND(10,LANGUAGE?152:18);	
					}
					
					if(BUFFER4[0]==2||BUFFER4[0]==1)
					{
						W_DIAMOND(10,BUFFER4[0]*16+96);
						W_HDIAMOND(10,BUFFER4[0]*16+80);						
					}
				}				
			}			
		}
	}

}

/*****************************************************/
/*	功能；左右按键处理函数，选择通道，信息类型，发射台
入口参数：无
出口参数：无
/*****************************************************/
void SaveAllMessage_Leftright();
void SaveAllMessage_Leftright()
{
	if(BUFFER4[0] == 0)		//对通道进行选择
	{
		if(G_Key == LEFT)	
		{
			G_Key=0;		//按键清零
			BUFFER4[1]=(BUFFER4[1]+3)%4;	//BUFFER4[1]记录对应通道
			CW_PR3(LANGUAGE?21:20,LANGUAGE?12:15,48+BUFFER4[1]);	//显示当前选定通道
		}
		if(G_Key == RIGHT)
		{
			G_Key=0;		//按键清零
			BUFFER4[1]=(BUFFER4[1]+1)%4;	//BUFFER4[1]记录对应通道
			CW_PR3(LANGUAGE?21:20,LANGUAGE?12:15,48+BUFFER4[1]);	//显示当前选定通道
		}
		
	}
	
	if(BUFFER4[0] == 1)		//对信息类别进行选择
	{
		if(G_Key == LEFT)
		{
			G_Key=0;		//按键清零
			BUFFER4[2]=(BUFFER4[2]+26)%27;	//修改对应BUFFER4[2]
			if(BUFFER4[2]==0) 	CW_PR3(LANGUAGE?21:20,LANGUAGE?14:16,'0');	//显示修改完毕的信息类别	
			else CW_PR3(LANGUAGE?21:20,LANGUAGE?14:16,64+BUFFER4[2]);
		}
		if(G_Key == RIGHT)
		{
			G_Key=0;
			BUFFER4[2]=(BUFFER4[2]+1)%27;
			if(BUFFER4[2]==0) 	CW_PR3(LANGUAGE?21:20,LANGUAGE?14:16,'0');	
			else CW_PR3(LANGUAGE?21:20,LANGUAGE?14:16,64+BUFFER4[2]);	
		}
		

	}
	
	if(BUFFER4[0] == 2)		//对发射台进行选择
	{
		if(G_Key == LEFT)
		{
			G_Key=0;		//按键清零
			BUFFER4[3]=(BUFFER4[3]+26)%27;	//修改对应BUFFER4[3]
			if(BUFFER4[3]==0) 	CW_PR3(LANGUAGE?21:20,LANGUAGE?16:17,'0');	//显示修改完毕的信息类别	
			else CW_PR3(LANGUAGE?21:20,LANGUAGE?16:17,64+BUFFER4[3]);
		}
		
		if(G_Key == RIGHT)
		{
			G_Key=0;
			BUFFER4[3]=(BUFFER4[3]+1)%27;
			if(BUFFER4[3]==0) 	CW_PR3(LANGUAGE?21:20,LANGUAGE?16:17,'0');	
			else CW_PR3(LANGUAGE?21:20,LANGUAGE?16:17,64+BUFFER4[3]);
		}

	}
}


//*********************************************************/
/*	功能；ENT按键处理函数，进行确认或者取消操作，跳出本菜单
入口参数：无
出口参数：无
/**********************************************************/
void SaveAllMessage_Dealing();
void SaveAllMessage_Dealing()
{
	if(G_Key == ENT)
	{
		LANHELP=1;	//恢复LANHELP的初始值
		G_Key=0;	//按键清零
		if(BUFFER4[0] == 3)	//选择确认
		{
			FLAG=0;			//结束循环
			if(Checkinfo.Printerror == 0)	//打印机正常
			{
				PublicReturn=4;//进入公用打印界面，且用4表明从本菜单进入
				STATE=16;		//Message_Printing的状态为16			
			}
			else
			{
				BUFFER4[0]=0; 	//进入打印出错界面不会返回本届面，所以先对本届面参数清零
				BUFFER4[1]=0;
				BUFFER4[2]=0;
				BUFFER4[3]=0;
				PublicReturn=4;	//进入公用出错界面，且用4表明从本菜单进入
				STATE=15;		//Message_PrintError的状态为15
			}
		}
		
		if(BUFFER4[0] == 4)	//取消返回操作
		{
			BUFFER4[0]=0;	//本界面使用的全局变量清零
			BUFFER4[1]=0;
			BUFFER4[2]=0;
			BUFFER4[3]=0;
			FLAG=0;			//结束循环
			STATE=2010;		//SavePitchPrint的状态为2010
		}
	}
}









/*******************************************************************/
/*	功能：打印范围的选择，包括通道，信息类别，发射台
		  BUFFER4[0] 选项编号
          BUFFER4[1] 通道,0表示全选，1表示518，2表示490，3表示4209.5
          BUFFER4[2] 信息类型0表示全选，1到26分别表示A~Z
          BUFFER4[3] 发射台,0表示全选，1到26分别表示A~Z
入口参数：无
出口参数：无
/*******************************************************************/
void RunSaveAllMessage()
{
    maske=0;
    maskc=0;
	LANHELP=3;		//当LANHELP==3时，显示大窗口
//	Checkprint();	//打印机检测程序
	BUFFER4[0]=0;	//本界面使用的全局变量清零
			BUFFER4[1]=0;
			BUFFER4[2]=0;
			BUFFER4[3]=0;
	SaveAllMessage_Paintintial();
	
	while(FLAG)
	{
		SaveAllMessage_Updn();
		SaveAllMessage_Leftright();
		SaveAllMessage_Dealing();
		run_tip();
	}
}