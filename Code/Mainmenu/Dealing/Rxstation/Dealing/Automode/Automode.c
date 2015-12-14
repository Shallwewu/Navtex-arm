#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "code.h"

/******************************************************/
/*	功能：自动模式菜单Automode的显示
入口参数：无
出口参数：无
/*******************************************************/
void Automode_Paintintial();
void Automode_Paintintial()
{
	unsigned char i;
	if(subback==10) RecoverData();	//若从子菜单返回，只需进行覆盖数据的恢复
	else
	{			
//		CLEAR1();					//清一区和二区的存储空间
		W_CLEARXLINE(0,319,230);
		W_CLEARXLINE(0,319,4);
		W_CLEARXLINE(0,319,5);
		
		if(LANGUAGE==0)			//英文表头：AUTOMODE SET
		{
			CTAB[1]='A';	CTAB[2]='U';	CTAB[3]='T';	CTAB[4]='O';	CTAB[5]='M';
			CTAB[6]='O';	CTAB[7]='D';	CTAB[8]='E';	CTAB[10]='S';	CTAB[11]='E';
			CTAB[12]='T';	
			CW_PR(0,1,13);			
		}
		else 					//写入中文表头数据"自动模式"
		{
			CCW_PR1(1,4,0xd7d4,1);
			CCW_PR1(3,4,0xb6af,1);
			CCW_PR1(5,4,0xc4a3,1);
			CCW_PR1(7,4,0xcabd,1);
		}


		/* 航行区选择,初始化在十一区 */
		CTAB[0]='N';	CTAB[1]='A';	CTAB[2]='V';	CTAB[3]='A';
		CTAB[4]='R';	CTAB[5]='E';	CTAB[6]='A';	CTAB[7]=':';	
		CW_PR(2,3,8);

		/* 频率选择，初始化为518khz */
		CTAB[2]='F';   CTAB[3]='R';	CTAB[4]='E';	CTAB[5]='Q';	CTAB[6]='U';	CTAB[7]='E';
		CTAB[8]='N';   CTAB[9]='C';	CTAB[10]='Y';	CTAB[11]=':';	
		CTAB[12]='5';  CTAB[13]='1';	CTAB[14]='8';	CTAB[15]='K';	CTAB[16]='H';	CTAB[17]='Z';
		CW_PR(0,4,19);  

		for(i=0;i<13;i++)		//岸台A~Z的显示
		{
			W_HDIAMOND(2,5+2*i); 
			CW_PR3(3,5+2*i,'A'+i);
			CW_PR3(4,5+2*i,':');	
				  
			W_HDIAMOND(21,5+2*i); 
			CW_PR3(22,5+2*i,'N'+i);
			CW_PR3(23,5+2*i,':');		
		}

		W_YLINE(0,0,239);		//Y轴的两条边框显示
		W_YLINE(319,0,239);	

		W_DIAMOND(1,3);			//完成选定框的显示
		W_HDIAMOND(1,4);

		if(BUFFER2[2]==1)		//此时选定的为490khz
		{
			CTAB[0]='4';   CTAB[1]='8';	CTAB[2]='6';	CTAB[3]='K';	CTAB[4]='H';
			CTAB[5]='Z';	
			CW_PR(12,4,6); 
		}
		
		if(BUFFER2[2]==2)		//此时选定的是4209.5khz
		{
		
			CTAB[0]='4';   CTAB[1]='2';		CTAB[2]='0';	CTAB[3]='9';	CTAB[4]='.';
			CTAB[5]='5';	CTAB[6]='K';	CTAB[7]='H';	CTAB[8]='Z';
			CW_PR(12,4,9); 
		}
		
		BUFFER2[1]=11; 			//初始化海区是11区
		Station_display(10);
	}
	
	for(i=0;i<5;i++)			//还原被弹出子菜单覆盖点阵显示区
	{
		W_HDIAMOND(21,13+2*i);		
	}
	
	DISASCII(10,3,BUFFER2[1]);	//海区的显示，调用函数DISASCII
	
	for(i=0;i<26;i++)			//显示岸台设置接收情况，0打勾，1不显示
	{
		word temp,temp1;
		temp1=Power(BUFFER2[1]-1);
//		temp1=(word)(pow(2,BUFFER2[1]-1));
		temp=Autotemp[BUFFER2[2]][i]&temp1;
		if(temp)
		{				
			if(i<13)	W_CANCALCHOOSED(19,5+2*i);
			else W_CANCALCHOOSED(38,5+2*(i-13));			
		}
		
		else
		{
			if(i<13)	W_CHOOSED(19,5+2*i);		
			else W_CHOOSED(38,5+2*(i-13));			
		}

 	}
		
	if(BUFFER2[0]>1&&BUFFER2[0]<15) //保证返回时所处选定框不变
	{
		W_DIAMOND(2,(BUFFER2[0]-2)*2+5);
		W_HDIAMOND(1,3);
	}
	
	if(BUFFER2[0]==1)
	{
		W_DIAMOND(1,4);
		W_HDIAMOND(1,3);		
	}			
	if(BUFFER2[0]>14&&BUFFER2[0]<28)
	{
		W_DIAMOND(21,(BUFFER2[0]-15)*2+5);
		W_HDIAMOND(1,3);
	}
	subback=0;

 }
 
//********************************************/
/*	功能；上下按键处理函数，选择所需选定项
入口参数：无
出口参数：无
/*********************************************/ 
void Automode_Updn();
void Automode_Updn()
{
	if (G_Key==UP)
	{
		G_Key=0;							//按键清零
		BUFFER2[0]=(BUFFER2[0]+27)%28;      //无条件上下移动    
		if(BUFFER2[0]==0)					//移动完毕之后给选定框加黑
		{
			W_DIAMOND(1,3);	
			W_HDIAMOND(1,4);	
		}
		
		if(BUFFER2[0]==1)
		{
			W_DIAMOND(1,4);	
			W_HDIAMOND(2,5);	
		}

		if(BUFFER2[0]==14)
		{
			W_DIAMOND(2,29);	
			W_HDIAMOND(21,5);	
		}
		if(BUFFER2[0]==27)
		{
			W_DIAMOND(21,29);	
			W_HDIAMOND(1,3);
		}
		
		if(BUFFER2[0]>1&&BUFFER2[0]<14)
		{
			W_DIAMOND(2,(BUFFER2[0]-2)*2+5);
			W_HDIAMOND(2,(BUFFER2[0]-2)*2+7);
		}
		
		if(BUFFER2[0]>14&&BUFFER2[0]<27)
		{
			W_DIAMOND(21,(BUFFER2[0]-15)*2+5);
			W_HDIAMOND(21,(BUFFER2[0]-15)*2+7);
		}  
		
	}

	if (G_Key==DOWN)
	{
		G_Key=0;							//按键清零
		BUFFER2[0]=(BUFFER2[0]+1)%28;       //无条件上下移动  
		if(BUFFER2[0]==0)					//移动完毕之后给选定框加黑
		{
			W_DIAMOND(1,3);	
			W_HDIAMOND(21,29);	
		}
		
		if(BUFFER2[0]==1)
		{
			W_DIAMOND(1,4);	
			W_HDIAMOND(1,3);	
		}

		if(BUFFER2[0]==15)
		{
			W_HDIAMOND(2,29);	
			W_DIAMOND(21,5);	
		}
		if(BUFFER2[0]==2)
		{
			W_DIAMOND(2,5);	
			W_HDIAMOND(1,4);
		}
		
		if(BUFFER2[0]>2&&BUFFER2[0]<15)
		{
			W_DIAMOND(2,(BUFFER2[0]-2)*2+5);
			W_HDIAMOND(2,(BUFFER2[0]-2)*2+3);
		}
		
		if(BUFFER2[0]>15&&BUFFER2[0]<28)
		{
			W_DIAMOND(21,(BUFFER2[0]-15)*2+5);
			W_HDIAMOND(21,(BUFFER2[0]-15)*2+3);
		} 		     	

	}

}

//****************************************************/
/*	功能；左右按键处理函数，进行航行警告区选择和工作频率选择
入口参数：无
出口参数：无
/*****************************************************/
void Automode_Leftright();
void Automode_Leftright()
{
	char i,j;
	if (G_Key==RIGHT||G_Key==LEFT)
	{
		if (BUFFER2[0]==0)                         	//航行警告区选择
		{   
		    if (G_Key==RIGHT)
			{
		        BUFFER2[1]=BUFFER2[1]%16+1;         //左右移动，BUFFER2[1]表警告区 
			}
			if (G_Key==LEFT)
			{
		       	BUFFER2[1]=(BUFFER2[1]+14)%16+1;             
			}
			
			DISASCII(10,3,BUFFER2[1]);				//海区的显示，调用函数DISASCII	
	
			Station_display(BUFFER2[1]-1);			
		}  
		
		if (BUFFER2[0]==1)                         	//频率选择
		{   
	    	if (G_Key==RIGHT) BUFFER2[2]=(BUFFER2[2]+1)%3;     //左右移动，BUFFER2[2]表频率 
	       	else BUFFER2[2]=(BUFFER2[2]+2)%3;             
			
			
			if(BUFFER2[2]==0)						//显示所选定的频率
			{			
				CTAB[0]='5';   CTAB[1]='1'; 	CTAB[2]='8';	CTAB[3]='K';	CTAB[4]='H';
				CTAB[5]='Z';   CTAB[6]=0x20;	CTAB[7]=0x20;	CTAB[8]=0x20;
				CW_PR(12,4,9); 	
			}
			
			else if(BUFFER2[2]==1)
			{			
				CTAB[0]='4';   CTAB[1]='8';	CTAB[2]='6';	CTAB[3]='K';	CTAB[4]='H';
				CTAB[5]='Z';	CTAB[6]=0x20;	CTAB[7]=0x20;	CTAB[8]=0x20;
				CW_PR(12,4,9);
			}
			
			else if(BUFFER2[2]==2)
			{			
				CTAB[0]='4';   CTAB[1]='2';		CTAB[2]='0';	CTAB[3]='9';	CTAB[4]='.';
				CTAB[5]='5';	CTAB[6]='K';	CTAB[7]='H';	CTAB[8]='Z';
				CW_PR(12,4,9); 
			}
		}

		if(BUFFER2[0]==0||BUFFER2[0]==1)
		{
			for(i=0;i<26;i++)
			{
				word temp,temp1;
				temp1=Power(BUFFER2[1]-1);
//				temp1=(word)(pow(2,BUFFER2[1]-1));
				temp=Autotemp[BUFFER2[2]][i]&temp1;
				if(temp!=0)
				{
						
					if(i<13)	W_CANCALCHOOSED(19,5+2*i);
					else W_CANCALCHOOSED(38,5+2*(i-13));
							
						
				}
				
				if(temp==0)
				{
			    
					if(i<13)	W_CHOOSED(19,5+2*i);		
					else W_CHOOSED(38,5+2*(i-13));
				}

		 	}			
		}					
		G_Key=0;	//按键清零
	}
}

/*************************************************/
/*	功能；CLR按键处理函数，返回到上级菜单Rxstation
入口参数：无
出口参数：无
/*************************************************/ 
void Automode_Return();
void Automode_Return()
{
	if (G_Key==CLR)  
	{
		byte i,j;
		G_Key=0;			//按键清零
		BUFFER2[1]=0;		//所用到3个全局变量清零
		BUFFER2[2]=0;
		BUFFER2[0]=0;			
		for(j=0;j<3;j++)	//Autotemp恢复Auto的值
		{
			for(i=0;i<26;i++)
				{
					Autotemp[j][i]=Auto[j][i];
				}
		}
		LANHELP=1;			//附加LANHELP恢复为1
		FLAG=0;				//结束循环
		STATE=40;			//Rxstation状态为40
	}
}

//**********************************************************/
/*	功能；ENT按键处理函数，暂时处理岸台的选定，存入Autotemp中
入口参数：无
出口参数：无
/***********************************************************/  
void Automode_Dealing();
void Automode_Dealing()
{
	byte i;                          
	word temp,temp1,temp2;    
	if (G_Key==ENT)
	{     
		G_Key=0;
		i=BUFFER2[0]-2;				//表示BUFFER2[0]的值                     	 	
		if (BUFFER2[0]>=2)          //按下ent为选中与否切换
		{
			temp2=0x0001;
			temp1=temp2<<(BUFFER2[1]-1);
/*			temp1=(word)(pow(2,BUFFER2[1]-1));
			temp2=pow(2,BUFFER2[1]-1);
			temp3=pow(2,15);*/
			temp=Autotemp[BUFFER2[2]][i]&temp1;
			if(temp==0)	//0表示之前接收
			{
				Autotemp[BUFFER2[2]][i]=Autotemp[BUFFER2[2]][i]+temp1;
					
					if(i<13)	W_CANCALCHOOSED(19,5+2*i);
					else W_CANCALCHOOSED(38,5+2*(i-13));
			}			
			if(temp!=0)	//1表示拒收
			{
				Autotemp[BUFFER2[2]][i]=Autotemp[BUFFER2[2]][i]-temp1;
			
				if(i<13)	W_CHOOSED(19,5+2*i);		
				else W_CHOOSED(38,5+2*(i-13));
			}
		}
	}
}
 
//****************************************************/
/*	功能；STAR按键处理函数，进入子菜单AutomodeSubmenu
入口参数：无
出口参数：无
/*****************************************************/ 
 void Automode_Submenu();
 void Automode_Submenu()
 {
     if (G_Key==STAR&&STATE==400)	
     {
		G_Key=0;				//按键清零
//		ProtectData(); 			//保存弹出菜单覆盖数据
		LANHELP=1;    			//恢复LANHELP值为1
		FLAG=0;					//结束循环
		STATE=4000;				//AutomodeSubmenu状态为4000
		State4000parameter=0;	//入口参数为0，表示有Automode菜单调用

     }
 }
 
 

//**************************************************/
/*	功能；自动模式下，可以单独设置每个海区下每个岸台
          接收与否，接收则会在岸台后打勾，拒收则无
          BUFFER2[0] 记录选定框
          BUFFER2[1] 记录所在航行警告区取值范围(1~16)
          BUFFER2[2] 记录所处工作频率(0~2)
          subback    记录从何菜单进入
入口参数：无
出口参数：无
/***************************************************/ 
void RunAutomode(unsigned char into)
{
    maske=0;
    maskc=0;
	subback=into;  
	LANHELP=0;
	Automode_Paintintial();

	while(FLAG)                          
	{	
		Automode_Updn();
		Automode_Leftright();		
		Automode_Return();		
		Automode_Dealing();
		Automode_Submenu();
		run_tip();        
	}
	
}