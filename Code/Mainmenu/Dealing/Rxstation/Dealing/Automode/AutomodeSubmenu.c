#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "run.h"
#include "define.h"	
#include "Eprom.h"
#include "lcddrive.h"
#include "code.h"

//volatile byte parameter;

//********************************************/
/*	功能：Automodesubmenu界面的显示
入口参数：无
出口参数：无
/*********************************************/
void Automodesubmenu_Paintintial();
void Automodesubmenu_Paintintial()
{
	byte i;
//	CLEAR2();		//弹出子菜单区域数据清空
	WFRAME();		//弹出子菜单框图显示
	if(LANGUAGE==0)	//英文菜单
	{
		CTAB[4]='*';  CTAB[5]='S';   CTAB[6]='E';  CTAB[7]='T'; 
		CTAB[9]='U';  CTAB[10]='P'; CTAB[11]='*';
		CW_PR(9,14,12);	//第一行显示内容"*SET UP*"


		  
		CTAB[5]='S';  CTAB[6]='A';  CTAB[7]='V';  CTAB[8]='E';  
		CW_PR(8,16,9);	//第二行显示内容"SAVE"

		  
		CTAB[5]='C';  CTAB[6]='L';  CTAB[7]='E';  CTAB[9]='C'; CTAB[10]='U';
		CTAB[11]='R'; CTAB[12]='S'; CTAB[13]='E'; CTAB[14]='T';
		CW_PR(8,17,15);	//第三行显示内容"CLE CUR SET"

		  
		CTAB[5]='C';  CTAB[6]='L';  CTAB[7]='E';  CTAB[9]='A';  CTAB[10]='L';
		CTAB[11]='L'; CTAB[12]='S'; CTAB[13]='E'; CTAB[14]='T'; 
		CW_PR(8,18,15);	//第四行显示内容"CLE ALL SET"


		CTAB[5]='C';  CTAB[6]='A';  CTAB[7]='N';  CTAB[8]='C';  CTAB[9]='E';
		CTAB[10]='L';  
		CW_PR(8,19,11);	//第五行显示内容"CLNCEL"		
	}
	else				//中文菜单
	{
		CCW_PR1(13,100,0xb1a3,1);	//第一行显示内容"保存"
		CCW_PR1(15,100,0xb4e6,1);
		
		CCW_PR1(13,118,0xc8a1,1);	//第二行显示内容"取消当前操作"
		CCW_PR1(15,118,0xcffb,1);
		CCW_PR1(17,118,0xb5b1,1);
		CCW_PR1(19,118,0xc7b0,1);
		CCW_PR1(21,118,0xb2d9,1);
		CCW_PR1(23,118,0xd7f7,1);  
				
		CCW_PR1(13,136,0xc8a1,1);	//第三行显示内容"取消所有操作"
		CCW_PR1(15,136,0xcffb,1);
		CCW_PR1(17,136,0xcbf9,1);
		CCW_PR1(19,136,0xd3d0,1);
		CCW_PR1(21,136,0xb2d9,1);
		CCW_PR1(23,136,0xd7f7,1);  
				
		CCW_PR1(13,154,0xb7b5,1);	//第四行显示内容"返回"
		CCW_PR1(15,154,0xbbd8,1);		
	}

	W_DIAMOND(11,LANGUAGE?104:16);	//画选定框
	W_HDIAMOND(11,LANGUAGE?122:17);
	W_HDIAMOND(11,LANGUAGE?140:18);
	W_HDIAMOND(11,LANGUAGE?158:19);
}

//********************************************/
/*	功能；上下按键处理函数，选择所需选定项
入口参数：无
出口参数：无
/*********************************************/
void Automodesubmenu_Updn();
void Automodesubmenu_Updn()
{
	if(parameter==2)	//此时选择的是信息类型子菜单，所用的参数是BUFFER2[]
	{
		if (G_Key==UP&&BUFFER2[0]>0)
		{
			BUFFER2[0]=BUFFER2[0]-1;        //非最上则上移
			G_Key=0;						//按键清零
			W_DIAMOND(11,LANGUAGE?(104+BUFFER2[0]*18):(BUFFER2[0]+16));	
			W_HDIAMOND(11,LANGUAGE?(122+BUFFER2[0]*18):(BUFFER2[0]+17));	
		}
		
		if (G_Key==DOWN&&BUFFER2[0]<3)
		{
			BUFFER2[0]=BUFFER2[0]+1;       	//非最下则下移
			G_Key=0;						//按键清零
			W_DIAMOND(11,LANGUAGE?(104+BUFFER2[0]*18):(BUFFER2[0]+16));	
			W_HDIAMOND(11,LANGUAGE?(86+BUFFER2[0]*18):(BUFFER2[0]+15));		
		}	
	}
	
	else				//当parameter不等于2选择参数类型为BUFFER3[]
	{
		if (G_Key==UP&&BUFFER3[0]>0)
		{
			BUFFER3[0]=BUFFER3[0]-1;        //非最上则上移
			G_Key=0;						//按键清零			
			W_DIAMOND(11,LANGUAGE?(104+BUFFER3[0]*18):(BUFFER3[0]+16));	
			W_HDIAMOND(11,LANGUAGE?(122+BUFFER3[0]*18):(BUFFER3[0]+17));	
		}
		
		if (G_Key==DOWN&&BUFFER3[0]<3)
		{
			BUFFER3[0]=BUFFER3[0]+1;       	//非最下则下移
			G_Key=0;						//按键清零
			W_DIAMOND(11,LANGUAGE?(104+BUFFER3[0]*18):(BUFFER3[0]+16));	
			W_HDIAMOND(11,LANGUAGE?(86+BUFFER3[0]*18):(BUFFER3[0]+15));			
		}	
	}
}


//**************************************************************/
/*	功能；ENT按键处理函数，进行保存，取消当前操作，取消所以操作
          或者返回上一级菜单处理
入口参数：无
出口参数：无
/***************************************************************/
void Automodesubmenu_Dealing();
void Automodesubmenu_Dealing()
{		
 	if(parameter==0)		//自动模式菜单的子菜单
 	{
		if(G_Key==ENT)
		{
			G_Key=0;				//按键清零
			FLAG=0;         		//结束循环
			STATE=400;      		//Automode的状态为400
			State400parameter=10; 	//入口参数为10，表明从子菜单返回
			
			if (BUFFER3[0]==0)                         	//保存当前
			{
				unsigned char i,j;
				for(j=0;j<3;j++)
				{
					for(i=0;i<26;i++)
						{
							Auto[j][i]=Autotemp[j][i];	//把临时设置Autotemp复制入Auto
						}
				}
				Eprom_AutoMode_Save();					//配置信息存入Eprom	
				BUFFER3[0]=0;							//全局变量清零
			}
						
		        
			if (BUFFER3[0]==1)                         	//取消当前设置，只对当前海区和频率下进行设置取消
			{   
				word i,temp,t,p,temp1,temp2;
				temp2=Power(BUFFER2[1]-1);
				t=~temp2;
//				t=(word)(pow(2,16))-1-(word)(pow(2,BUFFER2[1]-1));
				p=temp2;
				for(i=0;i<26;i++)
				{
					temp1=Power(BUFFER2[1]-1);
				//	temp1=(word)(pow(2,BUFFER2[1]-1));
					temp=Auto[BUFFER2[2]][i]&temp1;
					if(temp==0) 
					Autotemp[BUFFER2[2]][i]=Autotemp[BUFFER2[2]][i]&t;
					else
					Autotemp[BUFFER2[2]][i]=Autotemp[BUFFER2[2]][i]|p;	
				}
				BUFFER3[0]=0;
			}
			
			if (BUFFER3[0]==2)                         	//取消所有
			{   
				unsigned char i,j;

				for(j=0;j<3;j++)
				{
					for(i=0;i<26;i++)
						{
							Autotemp[j][i]=Auto[j][i];	//Autotemp恢复为Auto的值
						}
				}			
				BUFFER3[0]=0;
			}
	    
	    	if (BUFFER3[0]==3)                         	//退出
			{   
		        	BUFFER3[0]=0;                       //不进行其它任何操作
 			}
		} 	
	}

	if(parameter==1)		//手动模式菜单的子菜单
	{
 		unsigned char i,j;
	 	if(G_Key==ENT)									
		{	
			G_Key=0;				//按键清零
			FLAG=0;         		//结束循环
			STATE=401;      		//Manualmode的状态为400
			State400parameter=10; 	//入口参数为10，表明从子菜单返回
		
			if (BUFFER3[0]==0)                         		//保存
			{
				for(j=0;j<3;j++)
				{
					for(i=0;i<26;i++)
					{
						Manual[j][i]=Manualtemp[j][i];		//把临时设置Autotemp复制入Auto
					}
				}
				manual_area=manual_area_temp;
				BUFFER3[0]=0;
				Eprom_ManualMsgMode_Save(RXSTATION_MANUAL);	//配置信息存入Eprom
			}
			
			
			if (BUFFER3[0]==1)                         		//取消当前记录
			{   
								
				for(i=0;i<26;i++)							
					{
						Manualtemp[BUFFER2[1]][i]=Manual[BUFFER2[1]][i];
					}
				manual_area_temp=manual_area;
				BUFFER3[0]=0;	
			}
			
			if (BUFFER3[0]==2)                         		//取消设置（包括全部）不分频率
			{   
				for(j=0;j<3;j++)
				{
					for(i=0;i<26;i++)
					{
						Manualtemp[j][i]=Manual[j][i];
					}
				}
				manual_area_temp=manual_area;
				BUFFER3[0]=0;
			}
			    
	    	if (BUFFER3[0]==3)                         		//退出
			{   
		 			BUFFER3[0]=0;                     
			}
 		}		
	}
 		
 	if(parameter==2)						//信息类别菜单的子菜单												
 	{
	 	if(G_Key==ENT)						//运行Messagetypemenu菜单;
		{
			unsigned char i=0,j;		
			G_Key=0;				//按键清零
			FLAG=0;         		//结束循环
			STATE=41;      			//Messagetypemenu的状态为400
			State400parameter=10; 	//入口参数为10，表明从子菜单返回								
			if (BUFFER2[0]==0)                         	//保存当前
			{
				for(j=0;j<3;j++)
				{
					for(i=0;i<26;i++)
					{
						MSGTYPE[j][i]=MSGTYPETEMP[j][i];	
					}
					Eprom_ManualMsgMode_Save(RX_MSGTYPE);//配置信息存入Eprom
				}
				BUFFER2[0]=0;
			}
			
			if (BUFFER2[0]==1)                         	//取消设置（包包括全部）只是在某频率前提下
			{   
				for(i=0;i<26;i++)
				{
					MSGTYPETEMP[BUFFER1[1]][i]=MSGTYPE[BUFFER1[1]][i];
				}
				BUFFER2[0]=0;		
			}
			
			if (BUFFER2[0]==2)                         	//取消设置（包括全部）不分频率
			{   
				for(j=0;j<3;j++)
				{
					for(i=0;i<26;i++)
					{
						MSGTYPETEMP[j][i]=MSGTYPE[j][i];
					}
				}
				BUFFER2[0]=0;
			}
			
	    	if (BUFFER2[0]==3)                         	//退出
			{   
		    	{
	   				BUFFER2[0]=0;                    
				}
			}
		}
 	}
 }


//**********************************************************/
/*	功能；自动模式菜单，手动模式菜单和信息类别菜单那的子菜单，
          用于确认所选定的岸台或信息类别 	
          BUFFER2[0] 记录选定框
          BUFFER3[0] 用于信息类别菜单选定框的记录
          parameter  记录从何菜单进入
入口参数：into 记录从何菜单进入
          0表示自动模式菜单，
          1表示手动模式菜单，
          2表示信息类别菜单
出口参数：无
/***********************************************************/ 
void RunAutomodeSubmenu(byte into)
{
    maske=0;
    maskc=0;
	parameter=into;
	Automodesubmenu_Paintintial();
	
	while(FLAG)
	{
		Automodesubmenu_Updn();		
		Automodesubmenu_Dealing();
		run_tip();
	}	
}