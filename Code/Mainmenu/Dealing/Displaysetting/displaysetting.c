#include <stdio.h>
#include <stdlib.h>
#include  "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "Eprom.h"
#include "ThreeDays.h"
#include "code.h"
#include "rtc.h"
#include "PWM.h"

//起始时间输入在屏幕中位置 英文(13,15) 中文(15,19)
//起始时差输入在屏幕中位置 英文(14,20) 中文(15,24)

extern void TIM3_IRQHandler(void);

//********************************************/
/*	功能：显示设置菜单Displaysetting的显示
入口参数：无
出口参数：无
/*********************************************/
void Displaysetting_Con_Back();
void Displaysetting_Con_Back()
{
	
	if(LANGUAGE==0) 	//英文
	{
		CW_PR3(14,5,'1'+Contrast);		//对比度级别显示
		CW_PR3(16,23,'1'+Backlight);	//背光级别显示
	}
	
	else				//中文
	{
		CCW_PR1(13,32,0x1980+Contrast*0x20,0);
		CCW_PR1(11,208,0x1980+Backlight*0x20,0);			
	}
	
}
//********************************************/
/*	功能：显示设置菜单Displaysetting的显示
入口参数：无
出口参数：无
/*********************************************/
void Displaysetting_Paintintial();
void Displaysetting_Paintintial()
{
	byte i;

	
	if(LANGUAGE==0)	//英文界面
	{

		 /* 写入表头数据DISPLAY SET */
		CTAB[2]='D';	CTAB[3]='I';	CTAB[4]='S';	CTAB[5]='P';	CTAB[6]='L';
		CTAB[7]='A';	CTAB[8]='Y';
		CTAB[10]='S';	CTAB[11]='E';	CTAB[12]='T';
		CW_PR(0,1,13);
		
		 /* 对比度RX_CONTRAST: LEVEL */
		CTAB[5]='C';	CTAB[6]='O';	CTAB[7]='N';	CTAB[8]='T';	CTAB[9]='R';
		CTAB[10]='A';	CTAB[11]='S';	CTAB[12]='T';	CTAB[13]=':'; 	CTAB[16]='L';
		CTAB[17]='E';	CTAB[18]='V';	CTAB[19]='E';	CTAB[20]='L'; 		 
		CW_PR(0,5,21);

		 /* 蜂鸣BUZZER */
		CTAB[5]='B';	CTAB[6]='U';	CTAB[7]='Z';	CTAB[8]='Z';	CTAB[9]='E';
		CTAB[10]='R';	 
		CW_PR(0,8,11);

		 /* 蜂鸣的四个子选项ALARM MSG:ON */
		CTAB[0]='A';	CTAB[1]='L';	CTAB[2]='A';	CTAB[3]='R';	CTAB[4]='M';
		CTAB[6]='M';	CTAB[7]='S';	CTAB[8]='G';	CTAB[13]=':';	CTAB[14]='O';
		CTAB[15]='N';	 
		CW_PR(8,9,16);

		 /* 蜂鸣的四个子选项:RECEIVER MSG:ON */
		CTAB[0]='R';	CTAB[1]='E';	CTAB[2]='C';	CTAB[3]='E';	CTAB[4]='I';
		CTAB[5]='V';	CTAB[6]='E';	CTAB[7]='R';	CTAB[9]='M';	CTAB[10]='S';
		CTAB[11]='G';	CTAB[13]=':';	CTAB[14]='O';	CTAB[15]='N'; 
		CW_PR(8,10,16);
		
		 /* 蜂鸣的四个子选项 NAVTEX ALARM:ON*/
		CTAB[0]='N';	CTAB[1]='A';	CTAB[2]='V';	CTAB[3]='T';	CTAB[4]='E';
		CTAB[5]='X';	CTAB[7]='A';	CTAB[8]='L';	CTAB[9]='A';
		CTAB[10]='R';	CTAB[11]='M';	CTAB[13]=':';	CTAB[14]='O';	CTAB[15]='N'; 
		CW_PR(8,11,16);
		
		 /* 蜂鸣的四个子选项 CLICK:ON*/
		CTAB[0]='C';	CTAB[1]='L';	CTAB[2]='I';	CTAB[3]='C';	CTAB[4]='K';
		CTAB[13]=':';	CTAB[14]='O';	CTAB[15]='N';
		CW_PR(8,12,16);

		/* 本地时间LOCAL TIME:20  /  /  /  : */
		CTAB[5]='L';	CTAB[6]='O';	CTAB[7]='C';	CTAB[8]='A';	CTAB[9]='L';  CTAB[11]='T';
		CTAB[12]='I';	
		CTAB[13]='M';	CTAB[14]='E';	CTAB[15]=':';   CTAB[16]='2';	CTAB[17]='0';	CTAB[20]='/';	
		CTAB[23]='/';	
		CTAB[26]='/';	CTAB[29]=':';
		CW_PR(0,15,30);  

		/* 国际时间IT TIME:OFF */
		CTAB[0]='I';	CTAB[1]='T';	CTAB[3]='T';	CTAB[4]='I';	CTAB[5]='M';	CTAB[6]='E';
		CTAB[7]=':';
		CTAB[8]='O';	CTAB[9]='F';	CTAB[10]='F';
		CW_PR(5,18,11);
		
		
		/* 国际时间IT TIME:20  /  /  /  : */
		//CTAB[5]='I';	CTAB[6]='T';	CTAB[8]='T';	CTAB[9]='I';	CTAB[10]='M';
		//CTAB[11]='E';	CTAB[12]=':';	CTAB[13]='2';	CTAB[14]='0';
		//CTAB[17]='/';	CTAB[20]='/';	CTAB[23]='/';	CTAB[26]=':';
		//CW_PR(0,15,27);  

		/* 本地时间LOCAL TIME:OFF */
		//CTAB[0]='L';	CTAB[1]='O';	CTAB[2]='C';	CTAB[3]='A';	CTAB[4]='L';	CTAB[6]='T';
		//CTAB[7]='I';
		//CTAB[8]='M';	CTAB[9]='E';	CTAB[10]=':';	CTAB[11]='O';	CTAB[12]='F';	CTAB[13]='F';
		//CW_PR(5,18,14);

		/* 本地时间时差设置TIME DIF:+ */
		CTAB[0]='T';	CTAB[1]='I';	CTAB[2]='M';	CTAB[3]='E';	CTAB[5]='D';
		CTAB[6]='I';
		CTAB[7]='F';	CTAB[8]=':';	CTAB[9]='+';
		CW_PR(5,20,10);	
		
		/* 对比度设置BACKLIGHT: LEVEL */
		CTAB[0]='B';	CTAB[1]='A';	CTAB[2]='C';	CTAB[3]='K';	CTAB[5]='L';
		CTAB[6]='I';	CTAB[7]='G';	CTAB[8]='H';	CTAB[9]='T';
		CTAB[10]=':'; 	
		CTAB[13]='L';	CTAB[14]='E';	CTAB[15]='V';	CTAB[16]='E';	CTAB[17]='L'; 
		CW_PR(5,23,18);			
	}
	
	else //中文界面
	{
 		CCW_PR1(1,6,0xcfd4,1);		//第一行内容"显示设置"
 		CCW_PR1(3,6,0xcabe,1);
 		CCW_PR1(5,6,0xc9e8,1);
 		CCW_PR1(7,6,0xd6c3,1);
 		
 		CCW_PR1(5,32,0xb6d4,1);		//第二行内容"对比度: 级"
 		CCW_PR1(7,32,0xb1c8,1);
 		CCW_PR1(9,32,0xb6c8,1);
 		CCW_PR1(11,32,0x1aa0,0);
 		CCW_PR1(15,32,0xbcb6,1); 		
 		
  		CCW_PR1(5,56,0xb7e4,1);		//第三行内容"蜂鸣"
 		CCW_PR1(7,56,0xc3f9,1);
 			
 		CCW_PR1(8,72,0xd0c5,1);		//第四行内容"信息警报():开"
 		CCW_PR1(10,72,0xcfa2,1);
 		CCW_PR1(12,72,0xbeaf,1);
 		CCW_PR1(14,72,0xb1a8,1);
 		CCW_PR1(18,72,0x1aa0,0);
 		CCW_PR1(20,72,0xbfaa,1);  
 
 		CCW_PR1(8,88,0xbdd3,1);		//第五行内容"接收信息:开"
 		CCW_PR1(10,88,0xcad5,1);
 		CCW_PR1(12,88,0xd0c5,1);
 		CCW_PR1(14,88,0xcfa2,1);
 		CCW_PR1(18,88,0x1aa0,0);
 		CCW_PR1(20,88,0xbfaa,1); 		
 		
  		CCW_PR1(8,104,0xbdd3,1);	//第六行内容"接收机警报:开"
 		CCW_PR1(10,104,0xcad5,1);
 		CCW_PR1(12,104,0xbbfa,1);
 		CCW_PR1(14,104,0xbeaf,1);
 		CCW_PR1(16,104,0xb1a8,1);
 		CCW_PR1(18,104,0x1aa0,0);
 		CCW_PR1(20,104,0xbfaa,1);
 		
  		CCW_PR1(8,120,0xb5e3,1);	//第七行内容"点击:开"
 		CCW_PR1(10,120,0xbbf7,1);
 		CCW_PR1(18,120,0x1aa0,0);
 		CCW_PR1(20,120,0xbfaa,1); 		
 		
 		CCW_PR1(5,144,0xb1be,1);	//第八行内容"本地时间"
 		CCW_PR1(7,144,0xb5d8,1);
 		CCW_PR1(9,144,0xcab1,1);
 		CCW_PR1(11,144,0xbce4,1);
 		CCW_PR1(13,144,0x1aa0,0); 

		/* 国际时间，中文界面下时间的数值现实仍旧使用英文的字符现实 */
		CTAB[13]='2';	CTAB[14]='0';	CTAB[17]='/';CTAB[20]='/';	CTAB[23]='/';
		CTAB[26]=':';
		CW_PR(2,19,27);  		
 		
  		CCW_PR1(5,168,0xb9fa,1);	//第九行内容"国际时间:关"
 		CCW_PR1(7,168,0xbcca,1);
 		CCW_PR1(9,168,0xcab1,1);
 		CCW_PR1(11,168,0xbce4,1);
 		CCW_PR1(13,168,0x1aa0,0); 		
 		CCW_PR1(15,168,0xb9d8,1);		 		
 		
  		CCW_PR1(9,184,0xcab1,1);	//第十行内容"时差"
 		CCW_PR1(11,184,0xb2ee,1);		
 		CCW_PR1(13,184,0x1aa0,0); 
 		CW_PR3(LANGUAGE?15:14,LANGUAGE?24:20,'+'); 			//显示时差的正负号
 		
 		CCW_PR1(5,208,0xb1b3,1);		//第十一行内容"背光: 级"
 		CCW_PR1(7,208,0xb9e2,1);
 		CCW_PR1(9,208,0x1aa0,0);
 		CCW_PR1(13,208,0xbcb6,1);  		
	}
 

	DISASCII(LANGUAGE?17:18,LANGUAGE?19:15,iyear);			//显示国际时间的数值
	DISASCII(LANGUAGE?20:21,LANGUAGE?19:15,imonth);
	DISASCII(LANGUAGE?23:24,LANGUAGE?19:15,iday);
	DISASCII(LANGUAGE?26:27,LANGUAGE?19:15,ihour);
	DISASCII(LANGUAGE?29:30,LANGUAGE?19:15,iminute);
	
	W_YLINE(0,0,239);				//Y轴的两条边框
	W_YLINE(319,0,239);	
						
						
	for(i=0;i<4;i++)				//完成选定框的显示
	{
		W_HDIAMOND(6,LANGUAGE?(76+16*i):(9+i));
	}
	
	W_DIAMOND(3,LANGUAGE?36:5);	   
	W_HDIAMOND(3,LANGUAGE?60:8);
	W_HDIAMOND(3,LANGUAGE?148:15);
	W_HDIAMOND(3,LANGUAGE?172:18);
	W_HDIAMOND(3,LANGUAGE?212:23);
	
	if(sign==0) CW_PR3(LANGUAGE?15:14,LANGUAGE?24:20,'-'); 	//显示时差的正负号
	DISASCII(LANGUAGE?16:15,LANGUAGE?24:20,number);			//显示时差的数值
		
/*	if(Contrast==1)											//显示对比度
	{
		if(LANGUAGE==0) CW_PR3(14,5,'M');	
		else CCW_PR1(13,32,0xd6d0,1);
	}
	
	if(Contrast==2)	
	{
		if(LANGUAGE==0) CW_PR3(14,5,'L');					//显示对比度
		else CCW_PR1(13,32,0xb5cd,1);
	}	
	
	if(Backlight==1)										//显示背光：中
	{
		if(LANGUAGE==0) CW_PR3(16,23,'M');	
		else CCW_PR1(11,208,0xd6d0,1);		
	}
	
	if(Backlight==2)										//显示背光：弱
	{
		if(LANGUAGE==0) CW_PR3(16,23,'L');	
		else CCW_PR1(11,208,0xb5cd,1);		
	}*/
	Displaysetting_Con_Back();
	
	for(i=0;i<4;i++)										//显示蜂鸣的开关设置
	{
		if(Buzzer[i]==0&&LANGUAGE==0)
		{
			CW_PR3(23,i+9,'F');
			CW_PR3(24,i+9,'F');
		}
		
		if(Buzzer[i]==0&&LANGUAGE==1)
		CCW_PR1(20,72+i*16,0xb9d8,1); 
	}
	
	if(lcontrol==1&&LANGUAGE==0)							//显示本地时间 的开关
		{
			CW_PR3(14,18,'N');
			CW_PR3(15,18,' ');
		}
		
	if(lcontrol==1&&LANGUAGE==1)
	CCW_PR1(15,168,0xbfaa,1);
	
	W_Mode(35,6,32,1);										//手动，自动模式的显示
}
 
//********************************************/
/*	功能；上下按键处理函数，选择所需选定项，
　　　　　TOD时间设置，本地时间量设置，时差设置
入口参数：无
出口参数：无
/*********************************************/ 
void Displaysetting_Updn();
void Displaysetting_Updn()
{
	if(G_Key==UP||G_Key==DOWN)
	{
		if (G_Key==UP)
		{
			G_Key=0;		//按键清零
			if(BUFFER1[0]==1 || BUFFER1[0]==2 || BUFFER1[0]==3 || BUFFER1[0]==4 )	//非最上则上移,0 1 2 3 4为对比度、蜂鸣、国际时间和本地时间
			{
				BUFFER1[0]=BUFFER1[0]-1;
				if(BUFFER1[0]==0)
				{
					W_DIAMOND(3,LANGUAGE?36:5);	   
					W_HDIAMOND(3,LANGUAGE?60:8); 			
				}
				
				if(BUFFER1[0]==1)
				{
					W_DIAMOND(3,LANGUAGE?60:8);	   
					W_HDIAMOND(3,LANGUAGE?148:15); 			
				}
				if(BUFFER1[0]==2)
				{
					W_DIAMOND(3,LANGUAGE?148:15);	   
					W_HDIAMOND(3,LANGUAGE?172:18); 			
				}			
	
				if(BUFFER1[0]==3)
				{
					W_DIAMOND(3,LANGUAGE?172:18);	   
					W_HDIAMOND(3,LANGUAGE?212:23); 			
				}       
			}
			
			if(BUFFER1[0]>5 && BUFFER1[0]<=8 )        				//非最上则上移, 4 5 6 7为信息警报、接收信息、警报信息、点击
			{
				BUFFER1[0]=BUFFER1[0]-1;
				
				W_DIAMOND(6,LANGUAGE?(76+(BUFFER1[0]-5)*16):(BUFFER1[0]+4));	   
				W_HDIAMOND(6,LANGUAGE?(76+(BUFFER1[0]-4)*16):(BUFFER1[0]+5)); 			
				        
			}
			
		 	/*  TOD设置－时间输入－加  */

			if (BUFFER1[0]==9&&iyear<99)            //年加1 只表示后三位，初始值为08，范围08－99
			{
				iyear=iyear+1;
			}
				
			if (BUFFER1[0]==10&&imonth<12)        	//月加1,初始值为1，范围1－12,同时需要修改对应的天数，以免在某些月份出现不该有的天数
			{
				imonth=imonth+1;
				if(imonth==4||imonth==6||imonth==9||imonth==11) 
				{
					if (iday>30 )					//小月天数30,此时天数若超过30天，恢复到30天
					iday=30;
				}
				if(imonth==2)
				{
					if(iyear%4==0)                  //表示闰年，2月天数29,此时天数若超过29天，恢复到29天
					{
						if (iday>29 )
						iday=29;
					}
					else							//非闰年，2月天数28,此时天数若超过28天，恢复到28天
					{
						if (iday>28 )
						iday=28; 
					}
				}
			}
			
			if (BUFFER1[0]==11)       				//日加1,初始值为1，范围1－31,1-30,1-29,1-28
			{
				if(imonth==1||imonth==3||imonth==5||imonth==7||imonth==8||imonth==10||imonth==12)   //大月，每月天数31天
				{
					if (iday<31 )
					iday=iday+1;
				}
				
				if(imonth==4||imonth==6||imonth==9||imonth==11)     	//小月，每月天数30天
				{
					if (iday<30 )
					iday=iday+1;
				}
				if(imonth==2)
				{
					if(iyear%4==0)                  //表示闰年，2月天数29
					{
						if (iday<29 )
						iday=iday+1;
					}
					else							//非闰年，2月天数28
					{
						if (iday<28 )
						iday=iday+1; 
					}
				}
			}
				
			
			if (BUFFER1[0]==12&&ihour<23)       	//时加1,初始值为0，范围0－23
			{
				ihour=ihour+1;
			}
				
			
			if (BUFFER1[0]==13&&iminute<59)       	//分加1,初始值为0，范围0－59
			{
				
				iminute=iminute+1;
			}
			
			
	
			if (BUFFER1[0]==14)         
			{
				sign=(sign+1)%2;  					//sign=1表正，sign=0表负
			}
			
			if(BUFFER1[0]==15&&number<12)	number=number+1;	//本地时间调整量输入
			
		}
		
		if (G_Key==DOWN)
		{
			G_Key=0;								//按键清零
			if(BUFFER1[0]==0||BUFFER1[0]==1||BUFFER1[0]==2 ||BUFFER1[0]==3)        
			{
				BUFFER1[0]=BUFFER1[0]+1;			//非最下则下移,0 1 2 3为对比度、蜂鸣、国际时间和本地时间
				if(BUFFER1[0]==3)
				{
					W_DIAMOND(3,LANGUAGE?172:18);	   
					W_HDIAMOND(3,LANGUAGE?148:15); 			
				}
				
				if(BUFFER1[0]==1)
				{
					W_DIAMOND(3,LANGUAGE?60:8);	   
					W_HDIAMOND(3,LANGUAGE?36:5); 			
				}
				if(BUFFER1[0]==2)
				{
					W_DIAMOND(3,LANGUAGE?148:15);	   
					W_HDIAMOND(3,LANGUAGE?60:8); 			
				}
				
				if(BUFFER1[0]==4)
				{
					W_DIAMOND(3,LANGUAGE?212:23);	   
					W_HDIAMOND(3,LANGUAGE?172:18); 			
				}				
				        
			}
			if(BUFFER1[0]>4 && BUFFER1[0]<8 )        //非最下则下移,BUFFER1[0]= 4 5 6 7为信息警报、接收信息、警报信息、点击
			{
				BUFFER1[0]=BUFFER1[0]+1;
				W_DIAMOND(6,LANGUAGE?(76+(BUFFER1[0]-5)*16):(BUFFER1[0]+4));	   
				W_HDIAMOND(6,LANGUAGE?(76+(BUFFER1[0]-6)*16):(BUFFER1[0]+3)); 	        
			}
			

	
		 	/*  TOD设置－时间输入－减  */
	
			if (BUFFER1[0]==9&&iyear>14 )       	//年减1 只表示后三位，初始值为2008
			{
				iyear=iyear-1;
			}
				
			
			if (BUFFER1[0]==10&&imonth>1)        //月减1,初始值为1，最小为1，同时需要修改对应的天数，以免在某些月份出现不该有的天数
			{
				imonth=imonth-1;
				
				if(imonth==4||imonth==6||imonth==9||imonth==11) 
				{
					if (iday>30 )					//小月天数30,此时天数若超过30天，恢复到30天
					iday=30;
				}
				if(imonth==2)
				{
					if(iyear%4==0)                  //表示闰年，2月天数29,此时天数若超过29天，恢复到29天
					{
						if (iday>29 )
						iday=29;
					}
					else							//非闰年，2月天数28,此时天数若超过28天，恢复到28天
					{
						if (iday>28 )
						iday=28; 
					}
				}
			}
			
			if (BUFFER1[0]==11&&iday >1)       	//日减1,初始值为1，最小为1
			{
				iday=iday-1;
			}
				
			
			if (BUFFER1[0]==12&&ihour>0)       	//时减1,初始值为0，最小为0
			{
				ihour=ihour-1;
			}
				
			
			if (BUFFER1[0]==13&&iminute>0)      //分减1,初始值为0，最小为0
			{
				iminute=iminute-1;
			}
			
				
			if (BUFFER1[0]==14)
			{
				sign=(sign+1)%2;  				//sign=1表正，sign=0表负
			}
			
			if(BUFFER1[0]==15&&number>0)	number=number-1;	//本地时间调整量输入		
		}
	
		if(sign==0) CW_PR3(LANGUAGE?15:14,LANGUAGE?24:20,'-'); 	//显示时差的正负号
		if(sign==1) CW_PR3(LANGUAGE?15:14,LANGUAGE?24:20,'+');
		
		DISASCII(LANGUAGE?16:15,LANGUAGE?24:20,number);			//显示时差的数值
		
		DISASCII(LANGUAGE?17:18,LANGUAGE?19:15,iyear);			//显示国际时间的数值
		DISASCII(LANGUAGE?20:21,LANGUAGE?19:15,imonth);
		DISASCII(LANGUAGE?23:24,LANGUAGE?19:15,iday);
		DISASCII(LANGUAGE?26:27,LANGUAGE?19:15,ihour);
		DISASCII(LANGUAGE?29:30,LANGUAGE?19:15,iminute);
	}
 }
 
//**********************************************************/
/*	功能；左右按键处理函数，对比度的选择，本地时间的开启
　　　　　国际时间年月日移动，蜂鸣子选项的选择
入口参数：无
出口参数：无
/***********************************************************/ 
void Displaysetting_Leftright();
void Displaysetting_Leftright()
{
	byte i;
	if (G_Key==RIGHT||G_Key==LEFT)
    {
    
    	if(BUFFER1[0]==0||BUFFER1[0]==4)
    	{
	    	if (BUFFER1[0]==0&&G_Key==RIGHT)                //对比度选择,向右增强
			{   
			   	Contrast=(Contrast+1)%5;  
        Set_Contrast(Contrast);					
				Write_Char_Eprm(RX_CONTRAST,Contrast);			//Controst 信息写入Eprom

			}  
		
		 	if (BUFFER1[0]==0&&G_Key==LEFT)                            
			{   
			   	Contrast=(Contrast+4)%5;   
        Set_Contrast(Contrast);					
				Write_Char_Eprm(RX_CONTRAST,Contrast);			//Controst 信息写入Eprom
			
			}

	    	if (BUFFER1[0]==4&&G_Key==RIGHT)                //背光选择，向右增强
			{   
			   	Backlight=(Backlight+1)%5;   
         Set_Backlight(Backlight);					
				Write_Char_Eprm(RX_BACKLIGHT,Backlight);			//Backlight 信息写入Eprom

			}  
		
		 	if (BUFFER1[0]==4&&G_Key==LEFT)                            
			{   
			   	Backlight=(Backlight+4)%5;    
         Set_Backlight(Backlight);							
				Write_Char_Eprm(RX_BACKLIGHT,Backlight);			//Backlight 信息写入Eprom
			
			} 
				Displaysetting_Con_Back();   		
    	}

		
		if (BUFFER1[0]==3)                            	//本地时间
		{
			lcontrol=(lcontrol+1)%2;                	//左右移动转换状态				
			Write_Char_Eprm(RX_TIME+2,lcontrol);		//lcontrol 信息写入Eprom
		}
	
		for (i=0;i<=3;i++)                             	//对蜂鸣子项的选择
		{
			if(BUFFER1[0]==i+5)
			{
				Buzzer[i]=(Buzzer[i]+1)%2;	
			}
		}
		
		
		
		if(BUFFER1[0]>=9&&BUFFER1[0]<=13&&G_Key==RIGHT)
		{
			BUFFER1[0]=((BUFFER1[0]-9)+1)%5+9;
		}
		
		
		if(BUFFER1[0]>=9&&BUFFER1[0]<=13&&G_Key==LEFT)
		{
			BUFFER1[0]=((BUFFER1[0]-9)+4)%5+9;
		}
		
		
		if(BUFFER1[0]==14||BUFFER1[0]==15) BUFFER1[0]=(BUFFER1[0]-14+1)%2+14;
	
		G_Key=0;				//按键清零
		
		for(i=0;i<4;i++)		//蜂鸣开关显示
		{
			
			if(Buzzer[i]==0&&LANGUAGE==0)
			{
				CW_PR3(23,i+9,'F');
				CW_PR3(24,i+9,'F');
			}
			
			if(Buzzer[i]==0&&LANGUAGE==1)
			CCW_PR1(20,72+i*16,0xb9d8,1); 
		}
		
		
		for(i=0;i<4;i++)
		{
			if(Buzzer[i]==1&&LANGUAGE==0)
			{
				CW_PR3(23,i+9,'N');
				CW_PR3(24,i+9,' ');
			}
			
			if(Buzzer[i]==1&&LANGUAGE==1)
			CCW_PR1(20,72+i*16,0xBFAA,1); 
		}
		

		
				
		if(lcontrol==1)			//显示本地时间 的开关
		{
			if(LANGUAGE==0) 
			{
				CW_PR3(14,18,'N');
				CW_PR3(15,18,' ');	
			}
			
			else CCW_PR1(15,168,0xbfaa,1);
		}
		
		if(lcontrol==0)			//显示本地时间 的开关
		{
		
			if(LANGUAGE==0)
			{
				CW_PR3(14,18,'F');
				CW_PR3(15,18,'F');	
			}
			else CCW_PR1(15,168,0xb9d8,1);

		}
		
		
	 	if (BUFFER1[0]==9)		//国际时间底部横线的跳转
	 	{
	 	
	 		//W_XLINE(LANGUAGE?120:104,LANGUAGE?151:135,LANGUAGE?160:128);
	 		//W_CLEARXLINE(LANGUAGE?160:144,LANGUAGE?175:159,LANGUAGE?160:128);
	 		//W_CLEARXLINE(LANGUAGE?232:216,LANGUAGE?247:231,LANGUAGE?160:128);	
	 		W_XLINE(LANGUAGE?120:128,LANGUAGE?151:159,LANGUAGE?160:128);
	 		W_CLEARXLINE(LANGUAGE?160:168,LANGUAGE?175:183,LANGUAGE?160:128);
	 		W_CLEARXLINE(LANGUAGE?232:240,LANGUAGE?247:255,LANGUAGE?160:128);			 		 	
	 	}
	 	
	 	if (BUFFER1[0]==10)	
	 	{
	 	
	 		W_XLINE(LANGUAGE?160:168,LANGUAGE?175:183,LANGUAGE?160:128);
	 		W_CLEARXLINE(LANGUAGE?120:128,LANGUAGE?151:159,LANGUAGE?160:128);
	 		W_CLEARXLINE(LANGUAGE?184:192,LANGUAGE?199:207,LANGUAGE?160:128);			 		 	
	 	}
	 	if (BUFFER1[0]==11)	
	 	{
	 	
	 		W_XLINE(LANGUAGE?184:192,LANGUAGE?199:207,LANGUAGE?160:128);
	 		W_CLEARXLINE(LANGUAGE?160:168,LANGUAGE?175:183,LANGUAGE?160:128);
	 		W_CLEARXLINE(LANGUAGE?208:216,LANGUAGE?223:231,LANGUAGE?160:128);			 		 	
	 	}
	 	
	 	if (BUFFER1[0]==12)	
	 	{
	 	
	 		W_XLINE(LANGUAGE?208:216,LANGUAGE?223:231,LANGUAGE?160:128);
	 		W_CLEARXLINE(LANGUAGE?184:192,LANGUAGE?199:207,LANGUAGE?160:128);
	 		W_CLEARXLINE(LANGUAGE?232:240,LANGUAGE?247:255,LANGUAGE?160:128);			 		 	
	 	}
	 	
	 	
	 	if (BUFFER1[0]==13)	
	 	{
	 	
	 		W_XLINE(LANGUAGE?232:240,LANGUAGE?247:255,LANGUAGE?160:128);
	 		W_CLEARXLINE(LANGUAGE?208:216,LANGUAGE?223:231,LANGUAGE?160:128);
	 		W_CLEARXLINE(LANGUAGE?120:128,LANGUAGE?151:159,LANGUAGE?160:128);			 		 	
	 	}
	 	
	 	//if (BUFFER1[0]==11||BUFFER1[0]==12)	
	 	//{
	 	//	int i;
	 	//	i=(BUFFER1[0]-11)*24;
	 //		W_XLINE(LANGUAGE?(184+i):(168+i),LANGUAGE?(199+i):(183+i),LANGUAGE?160:128);
	 //		W_CLEARXLINE(LANGUAGE?(160+i):(144+i),LANGUAGE?(175+i):(159+i),LANGUAGE?160:128);
	 //		W_CLEARXLINE(LANGUAGE?(208+i):(192+i),LANGUAGE?(223+i):(207+i),LANGUAGE?160:128);			 		 	
	 //	}
	 	
	 	
	 	if (BUFFER1[0]==14)		//时差底部横线跳转
	 	{
	 	
	 		W_XLINE(LANGUAGE?120:112,LANGUAGE?127:119,LANGUAGE?200:168);
	 		W_CLEARXLINE(LANGUAGE?128:120,LANGUAGE?143:135,LANGUAGE?200:168);			 		 	
	 	}	    		
	 	if (BUFFER1[0]==15)	
	 	{
	 	
	 		W_CLEARXLINE(LANGUAGE?120:112,LANGUAGE?127:119,LANGUAGE?200:168);
	 		W_XLINE(LANGUAGE?128:120,LANGUAGE?143:135,LANGUAGE?200:168);			 		 	
	 	}
	 	
				
    }
    
 }
 
//**************************************************************/
/*	功能；CLR按键处理函数，退出本菜单，完成TOD设置，本地时间设置
　　　　　退出蜂鸣子选项
入口参数：无
出口参数：无
/***************************************************************/
 
void Displaysetting_Return();
void Displaysetting_Return()
{
	if (G_Key==CLR&&BUFFER1[0]>=5&&BUFFER1[0]<=8)                        //从蜂鸣子选项返回 
	{						
		G_Key=0;					//按键清零		
		W_DIAMOND(3,LANGUAGE?60:8);	//选项框退出到蜂鸣选项   
		W_HDIAMOND(6,LANGUAGE?(76+(BUFFER1[0]-5)*16):(BUFFER1[0]+4));
		BUFFER1[0]=1;				//修改BUFFER1[0]为1
		Eprom_Buzzer_Save();		//把修改完毕的蜂鸣设置存入Eprom
	}

	else if (G_Key==CLR&&BUFFER1[0]<5) 	//从当前菜单退出  
	{
		G_Key=0;					//按键清零
		BUFFER1[0]=0;               //本菜单使用全局变量清零		
		FLAG=0;						//结束循环
		STATE=4;					//MianMenu界面的状态4
		State4parameter=0;			//入口参数为0
	}

 	/* TOD设置－位置转移和转化 */
	else if (G_Key==CLR&&BUFFER1[0]>=9&&BUFFER1[0]<=13)                  		//在国际时间位置下按下clr返回
	{
		G_Key=0;					//按键清零
		W_CLEARXLINE(LANGUAGE?120:128,LANGUAGE?247:255,LANGUAGE?160:128);	//清除下划线
		W_DIAMOND(3,LANGUAGE?148:15);		
		
//		TODCS=TODCS&0xfffe;	            			//TODEN=0,关闭TOD模块
//		TODDAY=DatesToDays(iyear,imonth,iday);
		

//		TODHR=ihour;		//把小时置入TODHR	
//		TODMIN=iminute;		//把分钟置入TODMIN
//		TODCS|=0x0001;		//开启时钟 
		RTC_TimeRegulate(iyear,imonth,iday,ihour,iminute);
//		ReadTime();
		timestruct=GetTime();	
		SaveTime();
//		ReadTime();
//  	TIM3->CR1 |= 0x01;   //开定时器
		BUFFER1[0]=2;       //BUFFER1[0]=2表示跳回本地时间
	}
						 
	/*本地时间设置*/
	else if (G_Key==CLR&&BUFFER1[0]>=14&&BUFFER1[0]<=15)
	{
		G_Key=0;			//按键清零	
		BUFFER1[0]=3;		//跳出至本地时间选项框
		W_CLEARXLINE(LANGUAGE?120:112,LANGUAGE?143:135,LANGUAGE?200:168);
		W_DIAMOND(3,LANGUAGE?172:18);
		Write_Char_Eprm(RX_TIME,number);//number 信息写入Eprom
		Write_Char_Eprm(RX_TIME+1,sign);//sign 信息写入Eprom
	}
}
 
 
 
 
//**************************************************************/
/*	功能；ENT按键处理函数，对选定框进行选定操作
入口参数：无
出口参数：无
/***************************************************************/
 void Displaysetting_Dealing();
 void Displaysetting_Dealing()
 {
	 if(G_Key==ENT&&STATE==42)
	 {
	 	G_Key=0;
	 	if (BUFFER1[0]==1)	 	
	 	{
	 		BUFFER1[0]=5;                  	//在蜂鸣时按下ENT时可对所属子项选择	
	 		W_HDIAMOND(3,LANGUAGE?60:8);	   
			W_DIAMOND(6,LANGUAGE?76:9); 
	 	}
	 
	 	if (BUFFER1[0]==2)					//进入国际时间设置
	 	{
	 		BUFFER1[0]=9;
	 		//W_XLINE(LANGUAGE?120:104,LANGUAGE?151:135,LANGUAGE?160:128);
	 		W_XLINE(LANGUAGE?120:128,LANGUAGE?151:159,LANGUAGE?160:128);
	 		W_HDIAMOND(3,LANGUAGE?148:15);	 		 	
	 	}
	    
	 	if (BUFFER1[0]==3)					//进入本地时间的时差设置
	 	{
	 		BUFFER1[0]=14;
	 		W_XLINE(LANGUAGE?120:112,LANGUAGE?127:119,LANGUAGE?200:168);
	 		W_HDIAMOND(3,LANGUAGE?172:18);	 		 	
	 	}	      
	 }
 }

//**************************************************/
/*	功能；接收机显示设置菜单：包括对比度设置，蜂鸣设置，国际时间以及本地时间设置
          BUFFER1[0] 记录选定框
          iyear,imonth,iday,ihour,iminute开机当前时间的加载，可以显示当前时间
          同时，若修改国际时间也先通过修改以上的变量，然后用其值来初始化TOD
          

入口参数：无
出口参数：无
/***************************************************/ 
void RunDisplaySetting()
{
  maske=0;
  maskc=0;
	timestruct=GetTime();
  TIM3_IRQHandler();   		//把当前的时间加载进入iyear,imonth,iday,ihour,iminute	
	BUFFER1[0]=0;
	
	Displaysetting_Paintintial();
	while(FLAG)                         
	{
//        COPCTR=0xAAAA;
//        COPCTR=0x5555;
		Displaysetting_Updn();
		Displaysetting_Leftright();	
		Displaysetting_Return();		
		Displaysetting_Dealing();
		run_tip();		
	}
}