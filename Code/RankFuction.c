#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"	
#include "Eprom.h"
#include "code.h"
#include "MessageDeal.h"

//***************************************/
  /*功能；Messagetoprank[]的互换
入口参数：两需互换信息的地址
出口参数：无
/****************************************/
//void Msgtoprankchange(int num1,int num2); 							 
#define Msgtoprankchange(num1,num2) {   \
	sword temp;                           \
	temp=Messagetoprank[num1];          \
	Messagetoprank[num1]=Messagetoprank[num2];  \
	Messagetoprank[num2]=temp; }





//*****************************************/
  /*功能；按580khz通道排列 以3 2 1显示排列
入口参数：mode：1表示存储列表，0表示锁定列表
出口参数：无
/******************************************/
void Rankfrequency1();
void Rankfrequency1()
{
	sword j=0,i=0;
	for(j=0;j<Messageinfo.savenumber[0]-1;j++)
	{
		for (i=0;i<(Messageinfo.savenumber[0]-1-j);i++)
		{
			if(Messagesavetop[Messagetoprank[i]].frequency<Messagesavetop[Messagetoprank[i+1]].frequency)	
			{
				Msgtoprankchange(i,i+1);
			}
		}
	}
		
}

//*****************************************/
  /*功能；按4209.5khz通道排列 以1 2 3显示排列
入口参数：mode：1表示存储列表，0表示锁定列表
出口参数：无
/******************************************/
void Rankfrequency3();
void Rankfrequency3()	
{
	sword j=0,i=0;
	for(j=0;j<Messageinfo.savenumber[0]-1;j++)
	{
		for (i=0;i<(Messageinfo.savenumber[0]-1-j);i++)
		{
			if(Messagesavetop[Messagetoprank[i]].frequency>Messagesavetop[Messagetoprank[i+1]].frequency)	
			{
				Msgtoprankchange(i,i+1);
			}
		}
	}
		
}

//*****************************************/
  /*功能；按490khz通道排列,以1 3 2显示排列
入口参数：mode：1表示存储列表，0表示锁定列表
出口参数：无
/******************************************/
void Rankfrequency2();
void Rankfrequency2()	
{
	sword j=0,i=0,t;

	for(j=0;j<Messageinfo.savenumber[0]-1;j++)	//此时已按1 2 3顺序排列
	{
		for (i=0;i<(Messageinfo.savenumber[0]-1-j);i++)
		{
			if(Messagesavetop[Messagetoprank[i]].frequency>Messagesavetop[Messagetoprank[i+1]].frequency)	
			{
				Msgtoprankchange(i,i+1);
			}
		}
	}
	
	for(i=0;i<Messageinfo.savenumber[0];i++)
	{
		if(Messagesavetop[Messagetoprank[i]].frequency==2)	//得到第一个指向通道2的Messagtoprank[]位置	
		{
			t=i;
			break;
		}
	}

	
	if(t<(Messageinfo.savenumber[0]-1))
	{
			for(j=t;j<(Messageinfo.savenumber[0]-1);j++)
		
			for (i=t;i<(Messageinfo.savenumber[0]-1-j+t);i++)
			{
				if(Messagesavetop[Messagetoprank[i]].frequency<Messagesavetop[Messagetoprank[i+1]].frequency)	
				{
					Msgtoprankchange(i,i+1);
				}
			}
	}
		
}

//*****************************************/
  /*功能；发射台排列
入口参数：mode：1表示存储列表，0表示锁定列表
出口参数：无
/******************************************/
void Rankrxstaion();
void Rankrxstaion()	
{
	sword j=0,i=0;
	for(j=0;j<Messageinfo.savenumber[0]-1;j++)
	{
		for (i=0;i<(Messageinfo.savenumber[0]-1-j);i++)
		{
			if(Messagesavetop[Messagetoprank[i]].mark[0]<Messagesavetop[Messagetoprank[i+1]].mark[0])	
			{
				Msgtoprankchange(i,i+1);
			}
		}
	}
}


//*****************************************/
  /*功能；按发射信息所在海区排列，从大到小
入口参数：mode：1表示存储列表，0表示锁定列表
出口参数：无
/******************************************/
void Rankarea();
void Rankarea()
{
	sword j=0,i=0;
	for(j=0;j<Messageinfo.savenumber[0]-1;j++)
	{
		for (i=0;i<(Messageinfo.savenumber[0]-1-j);i++)
		{
			if(Messagesavetop[Messagetoprank[i]].area<Messagesavetop[Messagetoprank[i+1]].area)	
			{
				Msgtoprankchange(i,i+1);
			}
		}
	}
}

//*****************************************/
  /*功能；按信息类别排列，从大到小
入口参数：mode：1表示存储列表，0表示锁定列表
出口参数：无
/******************************************/
void Rankmessagetype();
void Rankmessagetype()	
{
	sword j=0,i=0;
	for(j=0;j<Messageinfo.savenumber[0]-1;j++)
	{
		for (i=0;i<(Messageinfo.savenumber[0]-1-j);i++)
		{
			if(Messagesavetop[Messagetoprank[i]].mark[1]<Messagesavetop[Messagetoprank[i+1]].mark[1])	
			{
				Msgtoprankchange(i,i+1);
			}
		}
	}		
}

//*****************************************/
  /*功能；按未读信息排列，从大到小
入口参数：mode：1表示存储列表，0表示锁定列表
出口参数：无
/******************************************/
void Ranklockread();
void Ranklockread()	
{
	sword j=0,i=0;
	for(j=0;j<Messageinfo.savenumber[0]-1;j++)
	{
		for (i=0;i<(Messageinfo.savenumber[0]-1-j);i++)
		{
			if(Messagesavetop[Messagetoprank[i]].read<Messagesavetop[Messagetoprank[i+1]].read)	
			{
				Msgtoprankchange(i,i+1);
			}
		}
	}
	
}


//*****************************************/
  /*功能；按时间排列(冒泡法)
入口参数：mode：1表示存储列表，0表示锁定列表
出口参数：无
/******************************************/
void Ranktime();
void Ranktime()
{
	sword j=0,i=0;

	for(j=0;j<Messageinfo.savenumber[0]-1;j++)
	{
		for (i=0;i<(Messageinfo.savenumber[0]-1-j);i++)
		{

		 if(Messagesavetop[Messagetoprank[i]].date[0]>Messagesavetop[Messagetoprank[i+1]].date[0])
			{
				Msgtoprankchange(i,i+1); 
			}
			else if(Messagesavetop[Messagetoprank[i]].date[0]==Messagesavetop[Messagetoprank[i+1]].date[0])
			{
				if(Messagesavetop[Messagetoprank[i]].date[1]>Messagesavetop[Messagetoprank[i+1]].date[1])
				{
					Msgtoprankchange(i,i+1);
					
				}
				
				else if(Messagesavetop[Messagetoprank[i]].date[1]==Messagesavetop[Messagetoprank[i+1]].date[1])
				{
					if(Messagesavetop[Messagetoprank[i]].date[2]>Messagesavetop[Messagetoprank[i+1]].date[2])
					{
						Msgtoprankchange(i,i+1);
						
					}
					
					else if(Messagesavetop[Messagetoprank[i]].date[2]==Messagesavetop[Messagetoprank[i+1]].date[2])
					{
						if(Messagesavetop[Messagetoprank[i]].time[0]>Messagesavetop[Messagetoprank[i+1]].time[0])
						{
							Msgtoprankchange(i,i+1);
					
						}
						
						else if(Messagesavetop[Messagetoprank[i]].time[0]==Messagesavetop[Messagetoprank[i+1]].time[0])
						{
							if(Messagesavetop[Messagetoprank[i]].time[1]>Messagesavetop[Messagetoprank[i+1]].time[1])
							{
								Msgtoprankchange(i,i+1);
						
							}		
						}
					}
				}
			}
		}
//        COPCTR=0xAAAA;
//        COPCTR=0x5555;		
	}
}

/*******************************************************************/
  /*功能；结合频率，类型对存储信息或锁定信息进行排序
入口参数：frequency char型:0对所有频率，1对通道1，2对通道2，3对通道3
		  type char型: 类型中0表示时间，1表示发射台，2表示信息类别
					   3表示未读信息,4表示航行警告区
		  出口参数：无
/*******************************************************************/
void Rankfuction(char frequency,char type);
void Rankfuction(char frequency,char type)
{
//	MessageProcess|=0x01;		//此时在进行信息处理操作
	DISABLEIRQA();		
	Messageinfo.rankmode=BUFFER2[0];	//把当前的排序状态写入信息记录结构体
	Write_Char_Eprm(MESSAGEINFO+20,Messageinfo.rankmode);//把信息记录结构体写入Eprom
	
	Ranktime();						//进行时间排序
	if(type==1) Rankrxstaion();		//发射台排序
	if(type==2) Rankmessagetype();     //信息类别排序
	if(type==3) Ranklockread();        //未读信息排序
	if(type==4) Rankarea();            //航行警告去排序
	if(frequency==1) Rankfrequency1(); //通道1 518
	if(frequency==2) Rankfrequency2(); //通道2 490
	if(frequency==3) Rankfrequency3();	//通道3 4029.5
//	MessageProcess&=0xfe;		//信息处理操作完毕，bit1位置0
	ENABLEIRQA();	
}


