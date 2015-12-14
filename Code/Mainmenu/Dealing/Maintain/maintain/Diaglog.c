#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "Eprom.h"
#include "code.h"


/***************************************************/
/*	功能；完成上下移动标记和左上角信息的显示数
入口参数：无
出口参数：无
/***************************************************/ 
void Diaglog_biaoji();
void Diaglog_biaoji()
{
	if(Diaglogn-(char)BUFFER3[0]>1) W_DOWNMOVE(39,27);	//上移动标记处理
	else W_CLEARUPDN(39,27);	
	
	if(BUFFER3[0]) W_UPMOVE(39,LANGUAGE?4:3);			//下移动标记处理
	else W_CLEARUPDN(39,LANGUAGE?4:3);
	
	if(BUFFER3[0]==9)									//显示自检日志所处位置
	{
		if(LANGUAGE==0)
		DISASCII(3,6,BUFFER3[0]+1);
		else
		{
			CCW_PR1(2,48,0x1980,0);
			CCW_PR1(4,48,0x1960,0);
		}
		
	}
	else 
	{
		if(LANGUAGE==0)
		CW_PR3(4,6,BUFFER3[0]+49);
		else
		{
			CCW_PR1(4,48,0x1980+BUFFER3[0]*32,0);
		}		
	}
		
}
/***************************************************/
/*	功能；自检日志结果显示函数
入口参数：无
出口参数：无
/***************************************************/ 
void Diaglog_Paint(char list);
void Diaglog_Paint(char list)
{
	char i;
	if(LANGUAGE)	//中文菜单
	{
		for(i=0;i<8;i++)
		{
			if(Diaglog[list].diagresult[i])
			{
				if(i==2) CW_PR3(21,13,Diaglog[list].diagresult[i]+48);
				else 			//自检出错显示：故障
				{
			 		CCW_PR1(21,72+16*i,0xb9ca,1);
			 		CCW_PR1(23,72+16*i,0xd5cf,1);
				}
			}
			
			else				//自检成功显示：正常
			{
		 		CCW_PR1(21,72+16*i,0xd5fd,1);
		 		CCW_PR1(23,72+16*i,0xb3a3,1);
			}
		}	
		
	}
	
	else			//英文菜单
	{
		for(i=0;i<8;i++)
		{
			if(Diaglog[list].diagresult[i])
			{
				if(i==2) CW_PR3(20,6,Diaglog[list].diagresult[i]+48);
				else 			//自检出错显示：BAD
				{
					CTAB[0]='B';	CTAB[1]='A';	CTAB[2]='D';		
					CW_PR(20,8+2*i,4);	
				}
			}
			
			else				//自检成功显示：GOOD
			{
				CTAB[0]='G';	CTAB[1]='O';	CTAB[2]='O';	CTAB[3]='D';	
				CW_PR(20,8+2*i,4);
			}
		}	
	}
}
/***************************************************/
/*	功能；自检日志自检时间显示函数
入口参数：无
出口参数：无
/***************************************************/ 
void Diaglogtime_Paint(char list);
void Diaglogtime_Paint(char list)
{
	DISASCII(LANGUAGE?17:15,LANGUAGE?7:6,Diaglog[list].date[0]);			//显示国际时间的数值
	DISASCII(LANGUAGE?20:18,LANGUAGE?7:6,Diaglog[list].date[1]);
	DISASCII(LANGUAGE?23:21,LANGUAGE?7:6,Diaglog[list].date[2]);
	DISASCII(LANGUAGE?26:24,LANGUAGE?7:6,Diaglog[list].time[1]);
	DISASCII(LANGUAGE?29:27,LANGUAGE?7:6,Diaglog[list].time[0]);
}

/***************************************************/
/*	功能；自检日志Diaglog显示函数
入口参数：无
出口参数：无
/***************************************************/ 
void Diaglog_Paintintial();
void Diaglog_Paintintial()
 {
	char i;
	if(Diaglogn) 	//存在自检日志，进行日志加载
	{
		BUFFER3[1]=(Diaglogs-Diaglogn+10)%10;				//存储起始存储数组的位置	
		Eprom_Diaglog_Read(&Diaglog[BUFFER3[1]],BUFFER3[1]);//加载需读取的日志
	}
	
	if(LANGUAGE==0)	//此时为英文界面
	{
		/* 表头 */
		CTAB[2]='S';	CTAB[3]='E';	CTAB[4]='L';	CTAB[5]='F';
		CTAB[7]='D';	CTAB[8]='I';	CTAB[9]='A';	CTAB[10]='G';
		CTAB[11]='N';	CTAB[12]='O';	CTAB[13]='S';	CTAB[14]='I';	CTAB[15]='S';
		CTAB[17]='L';	CTAB[18]='O';	CTAB[19]='G';	
		CW_PR(0,1,20);
		
		if(Diaglogn) //存在自检日志
		{
		/* 写入第一行数据 RESULT*/
			CTAB[5]='.';
			CTAB[6]='R';	CTAB[7]='E';	CTAB[8]='S';	CTAB[9]='U';	
			CTAB[10]='L';	CTAB[11]='T';
			
			CTAB[13]='2';	CTAB[14]='0';	CTAB[17]='/';CTAB[20]='/';	CTAB[23]='/';
			CTAB[26]=':';
			CW_PR(0,6,27);
			


		/* 写入第二行数据 ROM*/
			CTAB[0]='R';	CTAB[1]='O';	CTAB[2]='M';		
			CW_PR(8,8,3); 
			 

		/* 写入第三行数据 RAM*/
			CTAB[0]='R';	CTAB[1]='A';	CTAB[2]='M';	
			CW_PR(8,10,3);

		/* 写入第四行数据 SERIAL PORT*/
			CTAB[0]='S';	CTAB[1]='E';	CTAB[2]='R';	CTAB[3]='I';	CTAB[4]='A';	CTAB[5]='L';
			CTAB[7]='P';	CTAB[8]='O';	CTAB[9]='R';	CTAB[10]='T';	;	
			CW_PR(8,12,11);
			

		/* 写入第五行数据 POWER*/
			CTAB[0]='P';	CTAB[1]='O';	CTAB[2]='W';	CTAB[3]='E';	CTAB[4]='R';
			CW_PR(8,14,5);

		/* 写入第六行数据 ANTENNA*/
			CTAB[0]='A';	CTAB[1]='N';	CTAB[2]='T';	CTAB[3]='E';	CTAB[4]='N';
			CTAB[5]='N';	CTAB[6]='A';	;
			CW_PR(8,16,7);
			
		/* 写入第七行数据 518KHZ*/
			CTAB[0]='5';	CTAB[1]='1';	CTAB[2]='8';	CTAB[3]='K';	CTAB[4]='H';
			CTAB[5]='Z';	;
			CW_PR(8,18,6);
				
		/* 写入第八行数据 490KHZ*/
			CTAB[0]='4';	CTAB[1]='9';	CTAB[2]='0';	CTAB[3]='K';	CTAB[4]='H';
			CTAB[5]='Z';	;
			CW_PR(8,20,6);
			

		/* 写入第九行数据 4209.5KHZ*/
			CTAB[0]='4';	CTAB[1]='2';	CTAB[2]='0';	CTAB[3]='9';	CTAB[4]='.';	CTAB[5]='5';
			CTAB[6]='K';	CTAB[7]='H';	CTAB[8]='Z';	;	
			CW_PR(8,22,9);
			
			for(i=0;i<8;i++)
			{
				CW_PR3(19,8+2*i,':');
			}		
	
			Diaglog_Paint(BUFFER3[1]);				//显示日志结果
		    Diaglogtime_Paint(BUFFER3[1]);			//显示日志自检时间
		    Diaglog_biaoji();						//显示上下可翻看标记	
		}

		else 	//若无自检日志
		{
			CTAB[0]='N';	CTAB[1]='O';	CTAB[3]='D';	CTAB[4]='I';	CTAB[5]='A';				
			CTAB[6]='G';	CTAB[7]='N';	CTAB[8]='O';	CTAB[9]='S';	CTAB[11]='L';		
			CTAB[12]='O';  CTAB[13]='G';  CTAB[14]='!';	
			CW_PR(8,10,15);
		}
		
	}
	
	else
	{
		
		W_XLINE(0,319,25);	
		W_CLEARXLINE(0,319,22);

		if(Diaglogn) //存在自检日志
		{
	 		CCW_PR1(1,7,0xd7d4,1);	//第一行内容"自检日志"
	 		CCW_PR1(3,7,0xbcec,1);
	 		CCW_PR1(5,7,0xc8d5,1);
	  		CCW_PR1(7,7,0xd6be,1);

	 		
	 		CCW_PR1(6,48,0xd7d4,1);		//第二行内容"自检结果"
	 		CCW_PR1(8,48,0xbcec,1);
	  		CCW_PR1(10,48,0xbde1,1);
	 		CCW_PR1(12,48,0xb9fb,1);		
	  		CTAB[13]='2';	CTAB[14]='0';	CTAB[17]='/';CTAB[20]='/';	CTAB[23]='/';
			CTAB[26]=':';
			CW_PR(2,7,27);
					
	 		
	 		CCW_PR1(10,72,0xd6bb,1);	//第三行内容"只读存储器"
	 		CCW_PR1(12,72,0xb6c1,1);
	 		CCW_PR1(14,72,0xb4e6,1);
	 		CCW_PR1(16,72,0xb4a2,1);
	 		CCW_PR1(18,72,0xc6f7,1);
	 		
	  		
	 		CCW_PR1(10,88,0xcbe6,1);	//第四行内容"随机存储器"
	 		CCW_PR1(12,88,0xbbfa,1);
	 		CCW_PR1(14,88,0xb4e6,1);
	  		CCW_PR1(16,88,0xb4a2,1);
	 		CCW_PR1(18,88,0xc6f7,1);
	 		
	 		CCW_PR1(10,104,0xb4ae,1);	//第五行内容"串口"
	 		CCW_PR1(12,104,0xbfda,1);
		
	 		
	 		CCW_PR1(10,120,0xb5e7,1);	//第六行内容"电源"
	 		CCW_PR1(12,120,0xd4b4,1);
	 	
	 		
	 		CCW_PR1(10,136,0xccec,1);	//第七行内容"天线"
	 		CCW_PR1(12,136,0xcfdf,1);
	 		
	  		CCW_PR1(10,152,0xcda8,1);	//第八行内容"通道一"
	 		CCW_PR1(12,152,0xb5c0,1);
	 	 	CCW_PR1(14,152,0xd2bb,1);
	 	 	
	  		CCW_PR1(10,168,0xcda8,1);	//第九行内容"通道二"
	 		CCW_PR1(12,168,0xb5c0,1);
	 	 	CCW_PR1(14,168,0xb6fe,1);		 
	 
	   		CCW_PR1(10,184,0xcda8,1);	//第十行内容"通道三"
	 		CCW_PR1(12,184,0xb5c0,1);
	 	 	CCW_PR1(14,184,0xc8fd,1);
	 	 	
			
	 	 
	 	 	for(i=0;i<8;i++)
			{
			
			
				CW_PR3(20,10+2*i,':');
				
			}	
			
			Diaglog_Paint(BUFFER3[1]);					//显示日志结果
		    Diaglogtime_Paint(BUFFER3[1]);				//显示日志自检时间
		    Diaglog_biaoji();							//显示上下可翻看标记		
		}
		
		else	//无自检日志
		{
	
			CCW_PR1(10,88,0xcede,1);	//第四行内容"无自检日志！"
	 		CCW_PR1(12,88,0xd7d4,1);
	 		CCW_PR1(14,88,0xbcec,1);
	  		CCW_PR1(16,88,0xc8d5,1);
	 		CCW_PR1(18,88,0xd6be,1);
	 		CCW_PR1(20,88,0x1780,0);	 		
	 		
		}
	
	}

	W_Mode(35,7,32,1);			//手动，自动模式的显示	
	
	W_YLINE(0,0,239);
	W_YLINE(319,0,239);	


 }
/************************************************/
/*	功能；上下翻动自检日志结果
入口参数：无
出口参数：无
/************************************************/ 
void Diaglog_Updn();
void Diaglog_Updn()
{
	char list;
	if (G_Key==UP)
	{
		G_Key=0;
		if(BUFFER3[0]>0)							//存在上一条日志
		{
			BUFFER3[0]=BUFFER3[0]-1;			
			list=(BUFFER3[1]+BUFFER3[0])%10;
			Eprom_Diaglog_Read(&Diaglog[list],list);//加载需读取的日志
			Diaglog_Paint(list);					//显示日志结果
		    Diaglogtime_Paint(list);				//显示日志自检时间
		    Diaglog_biaoji();						//显示上下可翻看标记
		
		}
	}

	else if (G_Key==DOWN)
	{
		
		G_Key=0;
		if(Diaglogn-(char)BUFFER3[0]>1)				//存在下条日志
		{
			BUFFER3[0]=BUFFER3[0]+1;       			
			list=(BUFFER3[1]+BUFFER3[0])%10;
			Eprom_Diaglog_Read(&Diaglog[list],list);//加载需读取的日志
			Diaglog_Paint(list);					//显示日志结果
		    Diaglogtime_Paint(list);				//显示日志自检时间
		    Diaglog_biaoji();						//显示上下可翻看标记			
	   	}
	}	
}


/***************************************************/
/*	功能；返回上级菜单SelfDiagnosis
入口参数：无
出口参数：无
/***************************************************/ 
void Diaglog_Return();
void Diaglog_Return()
{
	if (G_Key==CLR)     
	{
		G_Key=0;		//按键清零
		BUFFER3[0]=0;	//本菜单使用的全局变量清零
		BUFFER3[1]=0;   
		FLAG=0;			//结束循环
		STATE=440;		//SelfDiagnosis状态为440
	}
}

/***************************************************/
/*	功能；自检日志函数，显示最近的10次自检结果
入口参数：无
出口参数：无
/***************************************************/ 
void RunDiaglog();
void RunDiaglog()
{
    maske=0;
    maskc=0;
	Diaglog_Paintintial();
	while(FLAG)
	{
		Diaglog_Updn();		
		Diaglog_Return();
		run_tip();		
	}
}
	
