#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"
#include "MessageDeal.h"
#include "Eprom.h"
#include "code.h"
#include "stm32f2xx.h"

#define  YEARINITAL 14



/*************************************************   
	功能：日期转换为天数
	入口参数：year month day分别表示年 月 日
	出口参数：由年月日计算所得的天数
 *************************************************/
u16 DatesToDays(char year,char month,char day)
{
	u16 a1,b1,days;
	a1=(year-YEARINITAL)/4;    	//year只表示年的后三位，初始化起始年为2008
	b1=(year-YEARINITAL)%4;
	if (b1==0)                	//非闰年,四年周期第三年
	{
		if (month==1)
		days=1461*a1+day;                 					//一月
		if (month==2)
		days=1461*a1+31+day;             	 				//二月
		if (month==3)
		days=1461*a1+31+28+day;           					//三月
		if (month==4)
		days=1461*a1+31+28+31+day;        					//四月
		if (month==5)
		days=1461*a1+31+28+31+30+day;     					//五月
		if (month==6)
		days=1461*a1+31+28+31+30+31+day;     				//六月
		if (month==7)
		days=1461*a1+31+28+31+30+31+30+day;      			//七月
		if (month==8)
		days=1461*a1+31+28+31+30+31+30+31+day;    			//八月
		if (month==9)
		days=1461*a1+31+28+31+30+31+30+31+31+day;    		//九月
		if (month==10)
		days=1461*a1+31+28+31+30+31+30+31+31+30+day;    	//十月
		if (month==11)
		days=1461*a1+31+28+31+30+31+30+31+31+30+31+day;    	//十一月
		if (month==12)
		days=1461*a1+31+28+31+30+31+30+31+31+30+31+30+day;	//十二月
	}
						
	if (b1==1)                	//非闰年,四年周期第二年
	{
		if (month==1)
		days=1461*a1+365+day;                 					//一月
		if (month==2)
		days=1461*a1+365+31+day;             	 				//二月
		if (month==3)
		days=1461*a1+365+31+28+day;           					//三月
		if (month==4)
		days=1461*a1+365+31+28+31+day;        					//四月
		if (month==5)
		days=1461*a1+365+31+28+31+30+day;     					//五月
		if (month==6)
		days=1461*a1+365+31+28+31+30+31+day;     				//六月
		if (month==7)
		days=1461*a1+365+31+28+31+30+31+30+day;      			//七月
		if (month==8)
		days=1461*a1+365+31+28+31+30+31+30+31+day;    			//八月
		if (month==9)
		days=1461*a1+365+31+28+31+30+31+30+31+31+day;    		//九月
		if (month==10)
		days=1461*a1+365+31+28+31+30+31+30+31+31+30+day;    	//十月
		if (month==11)
		days=1461*a1+365+31+28+31+30+31+30+31+31+30+31+day; 	//十一月
		if (month==12)
		days=1461*a1+365+31+28+31+30+31+30+31+31+30+31+30+day;  //十二月
	}
	
	if (b1==2)               	//闰年，四年周期第一年
	{
		if (month==1)
		days=1461*a1+365+365+day;                 					//一月
		if (month==2)
		days=1461*a1+365+365+31+day;             	 				//二月
		if (month==3)
		days=1461*a1+365+365+31+29+day;           					//三月
		if (month==4)
		days=1461*a1+365+365+31+29+31+day;        					//四月
		if (month==5)
		days=1461*a1+365+365+31+29+31+30+day;     					//五月
		if (month==6)
		days=1461*a1+365+365+31+29+31+30+31+day;     				//六月
		if (month==7)
		days=1461*a1+365+365+31+29+31+30+31+30+day;      			//七月
		if (month==8)
		days=1461*a1+365+365+31+29+31+30+31+30+31+day;    			//八月
		if (month==9)
		days=1461*a1+365+365+31+29+31+30+31+30+31+31+day;    		//九月
		if (month==10)
		days=1461*a1+365+365+31+29+31+30+31+30+31+31+30+day;    	//十月
		if (month==11)
		days=1461*a1+365+365+31+29+31+30+31+30+31+31+30+31+day;    	//十一月
		if (month==12)
		days=1461*a1+365+365+31+29+31+30+31+30+31+31+30+31+30+day;  //十二月
	}
		
	if (b1==3)                     	//非闰年,四年周期第四年
	{
		if (month==1)
		days=1461*a1+366+365+365+day;                 					//一月
		if (month==2)
		days=1461*a1+366+365+365+31+day;             	 				//二月
		if (month==3)
		days=1461*a1+366+365+365+31+28+day;           					//三月
		if (month==4)
		days=1461*a1+366+365+365+31+28+31+day;        					//四月
		if (month==5)
		days=1461*a1+366+365+365+31+28+31+30+day;     					//五月
		if (month==6)
		days=1461*a1+366+365+365+31+28+31+30+31+day;     				//六月
		if (month==7)
		days=1461*a1+366+365+365+31+28+31+30+31+30+day;      			//七月
		if (month==8)
		days=1461*a1+366+365+365+31+28+31+30+31+30+31+day;    			//八月
		if (month==9)
		days=1461*a1+366+365+365+31+28+31+30+31+30+31+31+day;    		//九月
		if (month==10)
		days=1461*a1+366+365+365+31+28+31+30+31+30+31+31+30+day;    	//十月
		if (month==11)
		days=1461*a1+366+365+365+31+28+31+30+31+30+31+31+30+31+day;    	//十一月
		if (month==12)
		days=1461*a1+366+365+365+31+28+31+30+31+30+31+31+30+31+30+day;	//十二月
	}
	
	return days;	
}

/********************************************************   
	功能：天数转换为日期
	入口参数：天数,由天数可计算所得 年 月 日的char型指针
	出口参数：无
 *******************************************************/
 void DaysToDates(unsigned int days,unsigned char* dayout,unsigned char* monthout,unsigned char *yearout);
 void DaysToDates(unsigned int days,unsigned char* dayout,unsigned char* monthout,unsigned char *yearout)
 {
 	int fouryears,daysafter4years,month,year,day;
 	
 	fouryears=days/1461;         		//从2014年开始过了几个四年
	daysafter4years=days%1461;        //去除整四年还剩多少天
	if (daysafter4years<=365)          //daysafter4years处在四年周期第3年（非闰年）
	{	year=1;         							//整四年多出3年,年数加时应加year-1
		if (daysafter4years<=31)
		{	month=1;   //表示1月份
			day=daysafter4years;   //表示几号
		}
		else if(daysafter4years<=31+28)
		{	month=2;   //表示2月份
			day=daysafter4years-31;   //表示几号
		}
		else if(daysafter4years<=31+28+31)
		{	month=3;   //表示3月份
			day=daysafter4years-31-28;   //表示几号
		}
		else if(daysafter4years<=31+28+31+30)
		{	month=4;   //表示4月份
			day=daysafter4years-31-28-31;   //表示几号
		}
		else if(daysafter4years<=31+28+31+30+31)
		{	month=5;   //表示5月份
			day=daysafter4years-31-28-31-30;   //表示几号
		}
		else if(daysafter4years<=31+28+31+30+31+30)
		{	month=6;   //表示6月份
			day=daysafter4years-31-28-31-30-31;   //表示几号
		}
		else if(daysafter4years<=31+28+31+30+31+30+31)
		{	month=7;   //表示7月份
			day=daysafter4years-31-28-31-30-31-30;   //表示几号
		}
		else if(daysafter4years<=31+28+31+30+31+30+31+31)
		{	month=8;   //表示8月份
			day=daysafter4years-31-28-31-30-31-30-31;   //表示几号
		}
		else if(daysafter4years<=31+28+31+30+31+30+31+31+30)
		{	month=9;   //表示9月份
			day=daysafter4years-31-28-31-30-31-30-31-31;   //表示几号
		}
		else if(daysafter4years<=31+28+31+30+31+30+31+31+30+31)
		{	month=10;   //表示10月份
			day=daysafter4years-31-28-31-30-31-30-31-31-30;   //表示几号
		}
		else if(daysafter4years<=31+28+31+30+31+30+31+31+30+31+30)
		{	month=11;   //表示11月份
			day=daysafter4years-31-28-31-30-31-30-31-31-30-31;   //表示几号
		}
		else if(daysafter4years<=31+28+31+30+31+30+31+31+30+31+30+31)
		{	month=12;   //表示12月份
			day=daysafter4years-31-28-31-30-31-30-31-31-30-31-30;   //表示几号
		}
	}
	else if (daysafter4years<=730)          //daysafter4years处在四年周期第2年（非闰年）
	{	year=2 ;         						//整四年多出2年,年数加时应加year-1
		if (daysafter4years-365<=31)
		{	month=1;   //表示1月份
			day=daysafter4years;   //表示几号
		}
		else if(daysafter4years-365<=31+28)
		{	month=2;   //表示2月份
			day=daysafter4years-31;   //表示几号
		}
		else if(daysafter4years-365<=31+28+31)
		{	month=3;   //表示3月份
			day=daysafter4years-31-28;   //表示几号
		}
		else if(daysafter4years-365<=31+28+31+30)
		{	month=4;   //表示4月份
			day=daysafter4years-31-28-31;   //表示几号
		}
		else if(daysafter4years-365<=31+28+31+30+31)
		{	month=5;   //表示5月份
			day=daysafter4years-31-28-31-30;   //表示几号
		}
		else if(daysafter4years-365<=31+28+31+30+31+30)
		{	month=6;   //表示6月份
			day=daysafter4years-31-28-31-30-31;   //表示几号
		}
		else if(daysafter4years-365<=31+28+31+30+31+30+31)
		{	month=7;   //表示7月份
			day=daysafter4years-31-28-31-30-31-30;   //表示几号
		}
		else if(daysafter4years-365<=31+28+31+30+31+30+31+31)
		{	month=8;   //表示8月份
			day=daysafter4years-31-28-31-30-31-30-31;   //表示几号
		}
		else if(daysafter4years-365<=31+28+31+30+31+30+31+31+30)
		{	month=9;   //表示9月份
			day=daysafter4years-31-28-31-30-31-30-31-31;   //表示几号
		}
		else if(daysafter4years-365<=31+28+31+30+31+30+31+31+30+31)
		{	month=10;   //表示10月份
			day=daysafter4years-31-28-31-30-31-30-31-31-30;   //表示几号
		}
		else if(daysafter4years-365<=31+28+31+30+31+30+31+31+30+31+30)
		{	month=11;   //表示11月份
			day=daysafter4years-31-28-31-30-31-30-31-31-30-31;   //表示几号
		}
		else if(daysafter4years-365<=31+28+31+30+31+30+31+31+30+31+30+31)
		{	month=12;   //表示12月份
			day=daysafter4years-31-28-31-30-31-30-31-31-30-31-30;   //表示几号
		}
		day=day-365;
	}
    else if (daysafter4years<=1096)           //daysafter4years处在四年周期第一年（闰年）
	{	year=3 ;         				//整四年多出一年,年数加时应加year-1
		if (daysafter4years-730<=31)
		{	month=1;   	//表示1月份
			day=daysafter4years;   //表示几号
		}
		else if(daysafter4years-730<=31+29)
		{	month=2;   //表示2月份
			day=daysafter4years-31;   //表示几号
		}
		else if(daysafter4years-730<=31+29+31)
		{	month=3;   //表示3月份
			day=daysafter4years-31-29;   //表示几号
		}
		else if(daysafter4years-730<=31+29+31+30)
		{	month=4;   //表示4月份
			day=daysafter4years-31-29-31;   //表示几号
		}
		else if(daysafter4years-730<=31+29+31+30+31)
		{	month=5;   //表示5月份
			day=daysafter4years-31-29-31-30;   //表示几号
		}
		else if(daysafter4years-730<=31+29+31+30+31+30)
		{	month=6;   //表示6月份
			day=daysafter4years-31-29-31-30-31;   //表示几号
		}
		else if(daysafter4years-730<=31+29+31+30+31+30+31)
		{	month=7;   //表示7月份
			day=daysafter4years-31-29-31-30-31-30;   //表示几号
		}
		else if(daysafter4years-730<=31+29+31+30+31+30+31+31)
		{	month=8;   //表示8月份
			day=daysafter4years-31-29-31-30-31-30-31;   //表示几号
		}
		else if(daysafter4years-730<=31+29+31+30+31+30+31+31+30)
		{	month=9;   //表示9月份
			day=daysafter4years-31-29-31-30-31-30-31-31;   //表示几号
		}
		else if(daysafter4years-730<=31+29+31+30+31+30+31+31+30+31)
		{	month=10;   //表示10月份
			day=daysafter4years-31-29-31-30-31-30-31-31-30;   //表示几号
		}
		else if(daysafter4years-730<=31+29+31+30+31+30+31+31+30+31+30)
		{	month=11;   //表示11月份
			day=daysafter4years-31-29-31-30-31-30-31-31-30-31;   //表示几号
		}
		else if(daysafter4years-730<=31+29+31+30+31+30+31+31+30+31+30+31)
		{	month=12;   //表示12月份
			day=daysafter4years-31-29-31-30-31-30-31-31-30-31-30;   //表示几号
		}
		day=day-730;
	}
//	else if (daysafter4years<=366+365+365)   			//daysafter4years处在四年周期第3年（非闰年）
	else if (daysafter4years<=366+365+365+365)      //daysafter4years处在四年周期第3年（非闰年）---zzy modified@2010-10-8
	{	year=4 ;       								//整四年多出4年,年数加时应加year-1
		if (daysafter4years-366-365-365<=31)
		{	month=1;   //表示1月份
			day=daysafter4years;   //表示几号
		}
		else if(daysafter4years-366-365-365<=31+28)
		{	month=2;   //表示2月份
			day=daysafter4years-31;   //表示几号
		}
		else if(daysafter4years-366-365-365<=31+28+31)
		{	month=3;   //表示3月份
			day=daysafter4years-31-28;   //表示几号
		}
		else if(daysafter4years-366-365-365<=31+28+31+30)
		{	month=4;   //表示4月份
			day=daysafter4years-31-28-31;   //表示几号
		}
		else if(daysafter4years-366-365-365<=31+28+31+30+31)
		{	month=5;   //表示5月份
			day=daysafter4years-31-28-31-30;   //表示几号
		}
		else if(daysafter4years-366-365-365<=31+28+31+30+31+30)
		{	month=6;   //表示6月份
			day=daysafter4years-31-28-31-30-31;   //表示几号
		}
		else if(daysafter4years-366-365-365<=31+28+31+30+31+30+31)
		{	month=7;   //表示7月份
			day=daysafter4years-31-28-31-30-31-30;   //表示几号
		}
		else if(daysafter4years-366-365-365<=31+28+31+30+31+30+31+31)
		{	month=8;   //表示8月份
			day=daysafter4years-31-28-31-30-31-30-31;   //表示几号
		}
		else if(daysafter4years-366-365-365<=31+28+31+30+31+30+31+31+30)
		{	month=9;   //表示9月份
			day=daysafter4years-31-28-31-30-31-30-31-31;   //表示几号
		}
		else if(daysafter4years-366-365-365<=31+28+31+30+31+30+31+31+30+31)
		{	month=10;   //表示10月份
			day=daysafter4years-31-28-31-30-31-30-31-31-30;   //表示几号
		}
		else if(daysafter4years-366-365-365<=31+28+31+30+31+30+31+31+30+31+30)
		{	month=11;   //表示11月份
			day=daysafter4years-31-28-31-30-31-30-31-31-30-31;   //表示几号
		}
		else if(daysafter4years-366-365-365<=31+28+31+30+31+30+31+31+30+31+30+31)
		{	month=12;   //表示12月份
			day=daysafter4years-31-28-31-30-31-30-31-31-30-31-30;   //表示几号
		}
		day=day-366-365-365;
	}
	
	*yearout=fouryears*4+(year-1)+YEARINITAL;       	//国际年后三位
	*monthout=month;                       				//国际月份
	*dayout=day;                           				//国际时间day
	if(days==0)
	{
	*dayout=1;  		
	}
 }

/*********************************************************   
	功能：找出未处理过信息中最早接收到的信息
	入口参数：无
	返回参数：返回该信息所在信息头文件数组中的EpromAdd信息
			  若未找到，则返回0xffff，表示出错
	
 *********************************************************/
/*void FindMsg();
void FindMsg()
{
	int i=0,l,position=0,days,hours,minutes,position_temp=0;
//找到第一条非锁定信息
	for(i=0;i<Messageinfo.savenumber[0];i++)
	{
		if(Messagesavetop[Messagetoprank[i]].lock==0)
			break;
	}
	if(i!=Messageinfo.savenumber[0])
	{
		position=Messagetoprank[i];
		position_temp=i;
	}
	else
	{	
		position=0xffff;
		position_temp=Messageinfo.savenumber[0]-1;
	}
	if(Messageinfo.savenumber[0]==0) position=0xffff;		//此时无存储信息，返回0xffff
	else
	{
		if(position==0xffff)
		{
			//do nothing
		}
		else
		{	
			for(l=position_temp+1;l<Messageinfo.savenumber[0];l++)		//找出未处理过信息中最早接收到的信息，存入i
			{
				i=Messagetoprank[l];
				if(Messagesavetop[i].lock==1) continue;	//若此信息锁定
				if(Messagesavetop[i].date[0]<Messagesavetop[position].date[0])
				{
					position=i;
					continue;	
				}
				
				if(Messagesavetop[i].date[0]==Messagesavetop[position].date[0])
				{
					if(Messagesavetop[i].date[1]<Messagesavetop[position].date[1])
					{
						position=i;
						continue;
					}
					
					if(Messagesavetop[i].date[1]==Messagesavetop[position].date[1])
					{
						if(Messagesavetop[i].date[2]<Messagesavetop[position].date[2])
						{
							position=i;
							continue;
						}
						
						if(Messagesavetop[i].date[2]==Messagesavetop[position].date[2])
						{
							if(Messagesavetop[i].time[0]<Messagesavetop[position].time[0])
							{
								position=i;
								continue;
							}
							
						    if(Messagesavetop[i].time[0]==Messagesavetop[position].time[0])
							{
								if(Messagesavetop[i].time[1]<Messagesavetop[position].time[1])
								{
									position=i;
									continue;
								}		
							}
						}
					}
				}
			}
		}
		/*判断所找出的信息是否处在当前时间之前的3天
		days=DatesToDays(Messagesavetop[position].date[0],Messagesavetop[position].date[1],Messagesavetop[position].date[2]);//获取天数
		hours=Messagesavetop[position].time[0];		//获取小时数
		minutes=Messagesavetop[position].time[1];	//获取分钟	
			
		TODCS|=TODCS_TOD_LOCK_MASK;//开启TOD_Lock位，读取TOD模块中时间的寄存器
		/* 
		if(((days+3)<TODDAY)||(((days+3)==TODDAY)&&hours<TODHR)||
			(((days+3)==TODDAY)&&(hours==TODHR)&&(minutes<TODMIN)))
		
		if((((days+3)<TODDAY)||(((days+3)==TODDAY)&&hours<TODHR)||
			(((days+3)==TODDAY)&&(hours==TODHR)&&(minutes<=TODMIN)))||(Messagesavetop[position].lock==1))
		position=0xffff;//若此时取得最早信息的时间落在3天之外，即3天时间内未接收过信息，返回0xffff			
		TODCS&=~TODCS_TOD_LOCK_MASK;//关闭TOD_Lock锁定位 
	}
	
	if(position==0xffff) 
	{		
//	ThreeDayAlarm=1;	//0xffff表示无三天处理信息，标记ThreeDayAlarm置1
	}
	else//找到下次处理信息
	{
		Messagesavetop[position].dealed=1;	//deal标记置1
		WritebitDeal(position);				//对应Eprom位置也置1
		EpromAddNow=position;				//EpromAddNow记录下次需处理信息的epromadd值

		/*3.取出需处理信息的时间，置入定时器，开启定时器
		//完成日期到天数的转换
		days=DatesToDays(Messagesavetop[position].date[0],Messagesavetop[position].date[1],Messagesavetop[position].date[2]);
		TODDAL=days+3;							//写入天数
		TODHAL=Messagesavetop[position].time[0];//写入小时数
		TODMAL=Messagesavetop[position].time[1];//写入分钟
    	TODCS|=TODCS_TODAEN_MASK;				//开启定时器的中断	
 //   	ThreeDayAlarm=0;
	}
	
//	return position;
	
}                 */


/*************************************************   
	功能：设定定时器3天到后进行的信息处理
	入口参数：无
	返回参数：无
 *************************************************/
/*void ThreeDaysUp(void);
void ThreeDaysUp(void)
{	
	#pragma interrupt saveall	//进入中断后数据保护
	int i,position,days,hours,minutes,j,m;
	/*1.处理到时的信息，处理该信息的dealed，
	TODCS&=~TODCS_TODAL_MASK;	//清除定时器中断标志位
	TODCS&=~TODCS_TODAEN_MASK;	//暂时关闭定时器的中断
/*	
	for(i=0;i<Messageinfo.savenumber[0];i++)	//找出需处理信息在Messagetoprank[]中位置，用i记录
	{
		if(EpromAddNow==Messagetoprank[i]) break;	
	}
	
	if(i==Messageinfo.savenumber[0])//当前信息头文件找不到对应信息，此时应进行报错处理
	{
		//报错处理
	}
	else
	{

		if(MessageProcess&0x01)
		{
			MessageProcess|=0x02;	//MessageProcess的bit1位置1
			TMR0_SCR|=TMR0_SCR_TCFIE_MASK;	//开启8K的定时器0的中断
		}
		else 
		{
//			m=Messageinfo.savenumber[0];
			for(j=0;j<Messageinfo.savenumber[0];j++)
			{
				days=DatesToDays(Messagesavetop[Messagetoprank[j]].date[0],Messagesavetop[Messagetoprank[j]].date[1],Messagesavetop[Messagetoprank[j]].date[2]);
				hours=Messagesavetop[Messagetoprank[j]].time[0];	//获取小时数
				minutes=Messagesavetop[Messagetoprank[j]].time[1];	//获取分钟	
				TODCS|=TODCS_TOD_LOCK_MASK;//开启TOD_Lock位，读取TOD模块中时间的寄存器 
//				if(((days+3)<TODDAY)||(((days+3)==TODDAY)&&hours<TODHR)||
//					(((days+3)==TODDAY)&&(hours==TODHR)&&(minutes<=TODMIN)))
				if(((days+3)<TODDAY)||(((days+3)==TODDAY)&&hours<TODHR)||
					(((days+3)==TODDAY)&&(hours==TODHR)&&(minutes<=TODMIN)))
				{
					if(Messagesavetop[Messagetoprank[j]].lock==0)//非锁定信息的步骤
					{
						Msgdel(j);
						j--;
					}				
				}
				TODCS&=~TODCS_TOD_LOCK_MASK;//关闭TOD_Lock锁定位 

			}
			FindMsg();
//			MesDel(i);		//找到对应信息，删除
//			FindMsg();		//找出下次需处理信息位置，用position记录，并进行处理
		}				
//	}


} */