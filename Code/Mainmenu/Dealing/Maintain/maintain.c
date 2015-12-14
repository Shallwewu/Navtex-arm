#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "code.h"

//********************************************/
/*功能；维护菜单Maintain的显示函数
入口参数：无
出口参数：无
/*********************************************/
void Maintain_Paintintial();
void Maintain_Paintintial()
{
	byte i;
	if(subback==10)
	{
		RecoverData();	//若从子菜单返回，只需进行覆盖数据的恢复
	}

	else
	{
		if(LANGUAGE==0)	//英文菜单
		{

			 /* 写入表头数据MAINTAIN */
			CTAB[2]='M';	CTAB[3]='A';	CTAB[4]='I';	CTAB[5]='N';	CTAB[6]='T';
			CTAB[7]='A';	CTAB[8]='I';	CTAB[9]='N';
			CW_PR(0,1,10);

			/* 写入第一行数据SELF DIAGNISOS */
			CTAB[0]='S';	CTAB[1]='E';	CTAB[2]='L';	CTAB[3]='F';	 
			CTAB[5]='D';	CTAB[6]='I';	CTAB[7]='A';	CTAB[8]='G';	CTAB[9]='N';
			CTAB[10]='O';	CTAB[11]='S';	CTAB[12]='E'; 
			CW_PR(5,4,13);

			/* 写入第二行数据NAVTEX ALARM */
			CTAB[0]='R';	CTAB[1]='E';	CTAB[2]='C';	CTAB[3]='O';	CTAB[4]='V'; 
			CTAB[5]='E';	CTAB[6]='R';	CTAB[8]='F';	CTAB[9]='A';
			CTAB[10]='C';	CTAB[11]='T';	CTAB[12]='O';	CTAB[13]='R';  CTAB[14]='Y';
			CTAB[16]='S';	CTAB[17]='E';   CTAB[18]='T';
			CW_PR(5,8,19);  


			/* 写入第三行数据STATE */
			CTAB[0]='S';	CTAB[1]='T';	CTAB[2]='A';	CTAB[3]='T';	CTAB[4]='E';
			CW_PR(5,12,5);


			/* 写入第四行数据SOFTWARE VERSION */
			CTAB[0]='S';	CTAB[1]='O';	CTAB[2]='F';	CTAB[3]='T';	CTAB[4]='W'; 
			CTAB[5]='A';	CTAB[6]='R';	CTAB[7]='E';	CTAB[9]='V';
			CTAB[10]='E';	CTAB[11]='R';	CTAB[12]='S';	CTAB[13]='I';  	CTAB[14]='O';
			CTAB[15]='N';	CTAB[16]=':';	CTAB[17]='2';   CTAB[18]='.';	CTAB[19]='0';
			CW_PR(5,16,20);	
		}
		
		else	//中文菜单
		{

			CLEARXLINE(0,39,22);
			XLINE(0,39,23);
	 		CCW_PR1(1,7,0xceac,1);		//第一行内容"维护"
	 		CCW_PR1(3,7,0xbba4,1);
		
	 		CCW_PR1(5,40,0xd7d4,1);		//第二行内容"自检"
	 		CCW_PR1(7,40,0xbcec,1);
	  		
	 		CCW_PR1(5,72,0xbbd6,1);		//第三行内容"恢复出厂设置"
	 		CCW_PR1(7,72,0xb8b4,1);
	 		CCW_PR1(9,72,0xb3f6,1);
	 		CCW_PR1(11,72,0xb3a7,1);
	 	 	CCW_PR1(13,72,0xc9e8,1);
	  	 	CCW_PR1(15,72,0xd6c3,1);

	 		CCW_PR1(5,104,0xbdd3,1);	//第四行内容"接收机状态"
	 		CCW_PR1(7,104,0xcad5,1);
	 		CCW_PR1(9,104,0xbbfa,1);
	 		CCW_PR1(11,104,0xd7b4,1);
	 	 	CCW_PR1(13,104,0xccac,1);
	 	 	
	 		CCW_PR1(5,136,0xc8ed,1);	//第五行内容"软件版本:1.0"
	 		CCW_PR1(7,136,0xbcfe,1);
	 		CCW_PR1(9,136,0xb0e6,1);
	 		CCW_PR1(11,136,0xb1be,1);
//	  		CCW_PR1(13,136,0xa1c3,1);
	  		CCW_PR1(14,136,0xa3b2,1);
	 		CW_PR3(13,18,':');
//	 		CCW_PR1(17,136,0xa3ae,1);
	 		CCW_PR1(17,136,0xa3b0,1);
	 		CW_PR3(16,18,'.');		
		}

		W_YLINE(0,0,239);				//Y轴两条边框的显示
		W_YLINE(319,0,239);	
		W_DIAMOND(3,LANGUAGE?44:4);		//完成选定框的显示
		for(i=0;i<3;i++)
		{
			W_HDIAMOND(3,LANGUAGE?(76+32*i):(8+4*i));
		}

		if(BUFFER1[0]!=0)				//保证返回本菜单时选定框显示的一致
		{
			W_DIAMOND(3,LANGUAGE?(44+BUFFER1[0]*32):(4+BUFFER1[0]*4));
			W_HDIAMOND(3,LANGUAGE?44:4);
		}
		W_Mode(35,7,32,1);				//手动，自动模式的显示		
	}

		subback=0;
}


/*********************************************/
/*功能；上下按键处理函数，选择所需选定项
入口参数：无
出口参数：无
/*********************************************/
void Maintain_Updn();
void Maintain_Updn()
{
	 if (G_Key==UP)
	{
		if(BUFFER1[0]>0)
		{
			BUFFER1[0]=BUFFER1[0]-1;        	//非最上则上移
			G_Key=0;
			W_DIAMOND(3,LANGUAGE?(44+BUFFER1[0]*32):(4+BUFFER1[0]*4));
			W_HDIAMOND(3,LANGUAGE?(76+BUFFER1[0]*32):(8+BUFFER1[0]*4));
		}
	}
	
	if (G_Key==DOWN)
	{
		if(	BUFFER1[0] <3)
		{
			BUFFER1[0]=BUFFER1[0]+1;          	//非最下则下移
			G_Key=0;
			W_DIAMOND(3,LANGUAGE?(44+BUFFER1[0]*32):(4+BUFFER1[0]*4));
			W_HDIAMOND(3,LANGUAGE?(12+BUFFER1[0]*32):(BUFFER1[0]*4));		
		}
	}	
}

/***************************************************************/
/*	功能；CLR按键处理函数，退出本菜单,返回到MainMenu界面
入口参数：无
出口参数：无
/***************************************************************/ 
void Maintain_Return();
void Maintain_Return()
{
	if (G_Key==CLR)
	{
		G_Key=0;		//按键清零
		BUFFER1[0]=0;   //使用全局变量清零            
		FLAG=0;         //结束循环            
		STATE=4;		//MainMenu状态为4
		State4parameter=0;	//入口参数0
	}
}


/***************************************************************/
/*	功能；ENT按键处理函数，进入本菜单的子界面
入口参数：无
出口参数：无
/***************************************************************/ 
void Maintain_Dealing();
void Maintain_Dealing()
{
	if(G_Key==ENT&&STATE==44)

	{	
		G_Key=0;
		FLAG=0;
		if (BUFFER1[0]==0)          //自检函数SelfDiagnosis
		{	
			STATE=440;
		}
		
		if (BUFFER1[0]==1 )        	//恢复出厂设置子菜单
		{
		//	ProtectData(); 			//保存弹出菜单覆盖数据
			STATE=442;				
		}

		if (BUFFER1[0]==2)          //状态函数NavtexState
		{
			STATE=441;
		}

		if (BUFFER1[0]==3)          //软件版本1.0
		{

		}
	}
}

//*******************************************************************/
/*	功能；维护菜单函数，实现自检，恢复出产设置，接收机状态，软件版本查看
入口参数：无
出口参数：无
/********************************************************************/
void RunMaintain(byte into)
{
  maske=0;
  maskc=0;
	subback=into;
	Maintain_Paintintial();
	while(FLAG)                          
	{
		 Maintain_Updn();		
		 Maintain_Return();		
		 Maintain_Dealing();
	     run_tip();
	}
}