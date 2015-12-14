#include <stdio.h>
#include <stdlib.h>
#include "define.h"	
#include "run.h"
#include "lcddrive.h"
#include "code.h"

//********************************************/
/*功能；主菜单MainMenu的显示函数
入口参数：无
出口参数：无
/*********************************************/
void Mainmenu_Paintintial();
void Mainmenu_Paintintial()
{
	unsigned char i;
	CLEAR1();

	if(LANGUAGE == 0)	//英文界面
	{
	    /* 表头：MAINMENU */
		CTAB[1] = 'M';		CTAB[2] = 'A';		CTAB[3] = 'I';		CTAB[4] = 'N';	
		CTAB[5] = 'M';		CTAB[6] = 'E';		CTAB[7] = 'N';		CTAB[8] = 'U';
		CW_PR(0,1,9);	
		

		/* 写入第一行数据:RX STATION */
		CTAB[5] = 'R';		CTAB[6] = 'X';		CTAB[8] = 'S';		CTAB[9] = 'T';	
		CTAB[10] = 'A';		CTAB[11] = 'T';		CTAB[12] = 'I';	CTAB[13] = 'O';	
		CTAB[14] = 'N';  
		CW_PR(0,4,15);


		/* 写入第二行数据:MESSAGE TYPE */
		CTAB[5] = 'M';		CTAB[6] = 'E';		CTAB[7] = 'S';		CTAB[8] = 'S';
		CTAB[9] = 'A';		CTAB[10] = 'G';		CTAB[11] = 'E';	CTAB[13] = 'T';
		CTAB[14] = 'Y';		CTAB[15] = 'P';		CTAB[16] = 'E';
		CW_PR(0,7,17);  


		/* 写入第三行数据:DISPLAY */
		CTAB[5] = 'D';		CTAB[6] = 'I';		CTAB[7] = 'S';		CTAB[8] = 'P';
		CTAB[9] = 'L';		CTAB[10] = 'A';		CTAB[11] = 'Y';
		CW_PR(0,10,12);


		/* 写入第四行数据:NAVTEX */
		CTAB[5] = 'N';		CTAB[6] = 'A';		CTAB[7] = 'V';		CTAB[8] = 'T';
		CTAB[9] = 'E';		CTAB[10] = 'X';
		CW_PR(0,13,11);


		/* 写入第五行数据:MAINTENANCE */
		CTAB[5] = 'M';		CTAB[6] = 'A';		CTAB[7] = 'I';		CTAB[8] = 'N';
		CTAB[9] = 'T';		CTAB[10] = 'E';		CTAB[11] = 'N';  	CTAB[12] = 'A';
		CTAB[13] = 'N';		CTAB[14] = 'C';		CTAB[15] = 'E';
		CW_PR(0,16,16);


		/* 写入第六行数据:LANGUAGE */
		CTAB[5] = 'L';		CTAB[6] = 'A';		CTAB[7] = 'N';		CTAB[8] = 'G';	
		CTAB[9] = 'U';		CTAB[10] = 'A';		CTAB[11] = 'G';		CTAB[12] = 'E';
		CW_PR(0,19,13);	
	}
 	
 	else		//中文界面
 	{
 		W_XLINE(0,319,25);	
		W_CLEARXLINE(0,319,22);
  	
 		CCW_PR1(1,7,0xb9a6,1);		//表头"功能菜单"
 		CCW_PR1(3,7,0xc4dc,1);
 		CCW_PR1(5,7,0xb2cb,1);
 		CCW_PR1(7,7,0xb5a5,1);
 		
 		CCW_PR1(6,40,0xb1a8,1);		//第二行内容"报文发射台设置"
 		CCW_PR1(8,40,0xcec4,1);
 		CCW_PR1(10,40,0xb7a2,1);
 		CCW_PR1(12,40,0xc9e4,1);
 		CCW_PR1(14,40,0xcca8,1);
 	 	CCW_PR1(16,40,0xc9e8,1);
 		CCW_PR1(18,40,0xd6c3,1);
 		
  		
 		CCW_PR1(6,64,0xd0c5,1);		//第三行内容"信息类别设置"
 		CCW_PR1(8,64,0xcfa2,1);
 		CCW_PR1(10,64,0xc0e0,1);
 		CCW_PR1(12,64,0xb1f0,1);
 	 	CCW_PR1(14,64,0xc9e8,1);
 		CCW_PR1(16,64,0xd6c3,1);
 		
 		CCW_PR1(6,88,0xcfd4,1);		//第四行内容"显示设置"
 		CCW_PR1(8,88,0xcabe,1);
 	 	CCW_PR1(10,88,0xc9e8,1);
 		CCW_PR1(12,88,0xd6c3,1); 	
 		
 		CCW_PR1(6,112,0xbdd3,1);	//第五行内容"接收机设置"
 		CCW_PR1(8,112,0xcad5,1);
 		CCW_PR1(10,112,0xbbfa,1);
 	 	CCW_PR1(12,112,0xc9e8,1);
 		CCW_PR1(14,112,0xd6c3,1); 	
 		
 		CCW_PR1(6,136,0xceac,1);	//第六行内容"维护"
 		CCW_PR1(8,136,0xbba4,1);
 		
  		CCW_PR1(6,160,0xd3ef,1);	//第七行内容"语言选择"
 		CCW_PR1(8,160,0xd1D4,1);
 	 	CCW_PR1(10,160,0xd1a1,1);
 		CCW_PR1(12,160,0xd4f1,1); 		 
 	}


	W_YLINE(0,0,239);
	W_YLINE(319,0,239);	

	W_DIAMOND(LANGUAGE?4:3,LANGUAGE?44:4);	//中文时选择框位于汉字的中间

	for(i = 0;i<5;i++)						//选定框的显示
	{
		W_HDIAMOND(LANGUAGE?4:3,LANGUAGE?(68+24*i):(7+3*i));		
	}
		
	if(BUFFER[0] != 0)
	{
		W_DIAMOND(LANGUAGE?4:3,LANGUAGE?(44+24*BUFFER[0]):(4+BUFFER[0]*3));	
		W_HDIAMOND(LANGUAGE?4:3,LANGUAGE?44:4);
	}
	
	W_Mode(35,7,32,1);	//手动，自动模式的显示

}
//********************************************/
/*功能；上下按键处理函数，选择所需选定项
入口参数：无
出口参数：无
/*********************************************/
void Mainmenu_Updn();
void Mainmenu_Updn()
{
                     
	if (G_Key == UP)		
	{	
		G_Key = 0;
		if(BUFFER[0]>0)		//非最上则上移
		{
			BUFFER[0] = BUFFER[0]-1;        		
			W_DIAMOND(LANGUAGE?4:3,LANGUAGE?(44+24*BUFFER[0]):(4+BUFFER[0]*3));	
			W_HDIAMOND(LANGUAGE?4:3,LANGUAGE?(68+24*BUFFER[0]):(7+BUFFER[0]*3));

		}
	}
	
	if (G_Key == DOWN)
	{
        G_Key = 0;
		if(	BUFFER[0] <5)	//非最下则下移
		{			
			BUFFER[0] = BUFFER[0]+1;       
			W_DIAMOND(LANGUAGE?4:3,LANGUAGE?(44+24*BUFFER[0]):(4+BUFFER[0]*3));	
			W_HDIAMOND(LANGUAGE?4:3,LANGUAGE?(20+24*BUFFER[0]):(1+BUFFER[0]*3));	
		}
	}	
}

//****************************************************/
/*功能；CLR和DISP按键处理函数，实现顶级菜单间跳转
入口参数：无
出口参数：无
/*****************************************************/
void Mainmenu_Menuchange() ;
void Mainmenu_Menuchange()             
{
	if(G_Key == DISP)   	//切换到信息界面
	{
		BUFFER[0] = 0;		//本界面使用全局变量清零
		G_Key = 0;			//按键清零
		FLAG = 0;			//结束循环
		STATE = 1;			//Message界面状态为1
		State1parameter = 0;//入口参数为0
		backpage = 0;		//全局变量清零	
	}
	
	else if (G_Key == CLR)     	//返回到原来界面  无Leftright,全放Menuchange里
	{
		G_Key = 0;			//按键清零
		BUFFER[0] = 0;		//本界面使用全局变量清零
		FLAG = 0;			//按键清零
		if(backpage == 0)   	//返回信息正文菜单Message         
		{
			STATE = 1;			//Message状态为1
			State1parameter = 0;//入口参数0	
		}
		if(backpage == 1)   	//返回存储菜单SaveMenu           
		{
			STATE = 2;			//Savemenu状态为2
			State2parameter = 0;//入口参数为0			

		}
		if(backpage == 2)    	//返回锁定菜单SaveMenu
		{
			STATE = 2;			//Savemenu状态为2
			State2parameter = 5;//入口参数为2，用于区别锁定菜单和存储菜单	
		}
		if(backpage == 3)    	//返回时间菜单TimeLocation         
		{
			STATE = 5;			//TimeLocation界面状态为5
		}
		backpage = 0;			//全局变量清零
	}
}

//**************************************************************/
/*	功能；ENT按键处理函数，进入选定框所选定的子菜单
入口参数：无
出口参数：无
/***************************************************************/
void Mainmenu_Dealing();
void Mainmenu_Dealing()             
{                                   
    if (G_Key == ENT&&STATE==4)
	{   
		G_Key = 0;				//按键清零
	 	FLAG = 0;				//结束本界面循环
		if(BUFFER[0] == 0)		//进入Rxstation menu，状态40 
		{
			STATE = 40;		
		}
		
        if(BUFFER[0] == 1)		//进入Messagetype menu，状态41		
        {
      		STATE = 41;
      		State41parameter = 0; 	
        } 
		
        if(BUFFER[0] == 2)     	//进入DisplaySetting menu，状态42 
        {
			STATE = 42;
        }			  
		
        if(BUFFER[0] == 3)		//进入ReceiveSetting menu，状态43 
        {
        	STATE = 43;		
        }
		
        if(BUFFER[0]  ==  4)	//进入Maintain menu	，状态44	
        {
			STATE = 44;
			State44parameter=0;	//入口参数0 		
        }
		
        if(BUFFER[0]  ==  5)    //进入LanguageSetting menu，状态45		
        {
			STATE = 45;
        }
	}
}
		
//**************************************************************/
/*	功能；主菜单函数，用于进入主菜单的各子菜单
入口参数：byte into:记录从何菜单进入，用全局变量backpage存储，
          生存周期同BUFFER[0],本菜单和其子菜单
出口参数：无
/***************************************************************/
void RunMainMenu(byte into)
{
    maske=0;
    maskc=0;
	backpage = into;  //记录从何界面进入，用于Mainmenu界面返回确定                        
	Mainmenu_Paintintial();
	while(FLAG)
	{
		Mainmenu_Updn();
		Mainmenu_Menuchange();
		Mainmenu_Dealing();
		run_tip();
	}
  	
}