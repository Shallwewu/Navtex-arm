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
	���ܣ�����ת��Ϊ����
	��ڲ�����year month day�ֱ��ʾ�� �� ��
	���ڲ������������ռ������õ�����
 *************************************************/
u16 DatesToDays(char year,char month,char day)
{
	u16 a1,b1,days;
	a1=(year-YEARINITAL)/4;    	//yearֻ��ʾ��ĺ���λ����ʼ����ʼ��Ϊ2008
	b1=(year-YEARINITAL)%4;
	if (b1==0)                	//������,�������ڵ�����
	{
		if (month==1)
		days=1461*a1+day;                 					//һ��
		if (month==2)
		days=1461*a1+31+day;             	 				//����
		if (month==3)
		days=1461*a1+31+28+day;           					//����
		if (month==4)
		days=1461*a1+31+28+31+day;        					//����
		if (month==5)
		days=1461*a1+31+28+31+30+day;     					//����
		if (month==6)
		days=1461*a1+31+28+31+30+31+day;     				//����
		if (month==7)
		days=1461*a1+31+28+31+30+31+30+day;      			//����
		if (month==8)
		days=1461*a1+31+28+31+30+31+30+31+day;    			//����
		if (month==9)
		days=1461*a1+31+28+31+30+31+30+31+31+day;    		//����
		if (month==10)
		days=1461*a1+31+28+31+30+31+30+31+31+30+day;    	//ʮ��
		if (month==11)
		days=1461*a1+31+28+31+30+31+30+31+31+30+31+day;    	//ʮһ��
		if (month==12)
		days=1461*a1+31+28+31+30+31+30+31+31+30+31+30+day;	//ʮ����
	}
						
	if (b1==1)                	//������,�������ڵڶ���
	{
		if (month==1)
		days=1461*a1+365+day;                 					//һ��
		if (month==2)
		days=1461*a1+365+31+day;             	 				//����
		if (month==3)
		days=1461*a1+365+31+28+day;           					//����
		if (month==4)
		days=1461*a1+365+31+28+31+day;        					//����
		if (month==5)
		days=1461*a1+365+31+28+31+30+day;     					//����
		if (month==6)
		days=1461*a1+365+31+28+31+30+31+day;     				//����
		if (month==7)
		days=1461*a1+365+31+28+31+30+31+30+day;      			//����
		if (month==8)
		days=1461*a1+365+31+28+31+30+31+30+31+day;    			//����
		if (month==9)
		days=1461*a1+365+31+28+31+30+31+30+31+31+day;    		//����
		if (month==10)
		days=1461*a1+365+31+28+31+30+31+30+31+31+30+day;    	//ʮ��
		if (month==11)
		days=1461*a1+365+31+28+31+30+31+30+31+31+30+31+day; 	//ʮһ��
		if (month==12)
		days=1461*a1+365+31+28+31+30+31+30+31+31+30+31+30+day;  //ʮ����
	}
	
	if (b1==2)               	//���꣬�������ڵ�һ��
	{
		if (month==1)
		days=1461*a1+365+365+day;                 					//һ��
		if (month==2)
		days=1461*a1+365+365+31+day;             	 				//����
		if (month==3)
		days=1461*a1+365+365+31+29+day;           					//����
		if (month==4)
		days=1461*a1+365+365+31+29+31+day;        					//����
		if (month==5)
		days=1461*a1+365+365+31+29+31+30+day;     					//����
		if (month==6)
		days=1461*a1+365+365+31+29+31+30+31+day;     				//����
		if (month==7)
		days=1461*a1+365+365+31+29+31+30+31+30+day;      			//����
		if (month==8)
		days=1461*a1+365+365+31+29+31+30+31+30+31+day;    			//����
		if (month==9)
		days=1461*a1+365+365+31+29+31+30+31+30+31+31+day;    		//����
		if (month==10)
		days=1461*a1+365+365+31+29+31+30+31+30+31+31+30+day;    	//ʮ��
		if (month==11)
		days=1461*a1+365+365+31+29+31+30+31+30+31+31+30+31+day;    	//ʮһ��
		if (month==12)
		days=1461*a1+365+365+31+29+31+30+31+30+31+31+30+31+30+day;  //ʮ����
	}
		
	if (b1==3)                     	//������,�������ڵ�����
	{
		if (month==1)
		days=1461*a1+366+365+365+day;                 					//һ��
		if (month==2)
		days=1461*a1+366+365+365+31+day;             	 				//����
		if (month==3)
		days=1461*a1+366+365+365+31+28+day;           					//����
		if (month==4)
		days=1461*a1+366+365+365+31+28+31+day;        					//����
		if (month==5)
		days=1461*a1+366+365+365+31+28+31+30+day;     					//����
		if (month==6)
		days=1461*a1+366+365+365+31+28+31+30+31+day;     				//����
		if (month==7)
		days=1461*a1+366+365+365+31+28+31+30+31+30+day;      			//����
		if (month==8)
		days=1461*a1+366+365+365+31+28+31+30+31+30+31+day;    			//����
		if (month==9)
		days=1461*a1+366+365+365+31+28+31+30+31+30+31+31+day;    		//����
		if (month==10)
		days=1461*a1+366+365+365+31+28+31+30+31+30+31+31+30+day;    	//ʮ��
		if (month==11)
		days=1461*a1+366+365+365+31+28+31+30+31+30+31+31+30+31+day;    	//ʮһ��
		if (month==12)
		days=1461*a1+366+365+365+31+28+31+30+31+30+31+31+30+31+30+day;	//ʮ����
	}
	
	return days;	
}

/********************************************************   
	���ܣ�����ת��Ϊ����
	��ڲ���������,�������ɼ������� �� �� �յ�char��ָ��
	���ڲ�������
 *******************************************************/
 void DaysToDates(unsigned int days,unsigned char* dayout,unsigned char* monthout,unsigned char *yearout);
 void DaysToDates(unsigned int days,unsigned char* dayout,unsigned char* monthout,unsigned char *yearout)
 {
 	int fouryears,daysafter4years,month,year,day;
 	
 	fouryears=days/1461;         		//��2014�꿪ʼ���˼�������
	daysafter4years=days%1461;        //ȥ�������껹ʣ������
	if (daysafter4years<=365)          //daysafter4years�����������ڵ�3�꣨�����꣩
	{	year=1;         							//��������3��,������ʱӦ��year-1
		if (daysafter4years<=31)
		{	month=1;   //��ʾ1�·�
			day=daysafter4years;   //��ʾ����
		}
		else if(daysafter4years<=31+28)
		{	month=2;   //��ʾ2�·�
			day=daysafter4years-31;   //��ʾ����
		}
		else if(daysafter4years<=31+28+31)
		{	month=3;   //��ʾ3�·�
			day=daysafter4years-31-28;   //��ʾ����
		}
		else if(daysafter4years<=31+28+31+30)
		{	month=4;   //��ʾ4�·�
			day=daysafter4years-31-28-31;   //��ʾ����
		}
		else if(daysafter4years<=31+28+31+30+31)
		{	month=5;   //��ʾ5�·�
			day=daysafter4years-31-28-31-30;   //��ʾ����
		}
		else if(daysafter4years<=31+28+31+30+31+30)
		{	month=6;   //��ʾ6�·�
			day=daysafter4years-31-28-31-30-31;   //��ʾ����
		}
		else if(daysafter4years<=31+28+31+30+31+30+31)
		{	month=7;   //��ʾ7�·�
			day=daysafter4years-31-28-31-30-31-30;   //��ʾ����
		}
		else if(daysafter4years<=31+28+31+30+31+30+31+31)
		{	month=8;   //��ʾ8�·�
			day=daysafter4years-31-28-31-30-31-30-31;   //��ʾ����
		}
		else if(daysafter4years<=31+28+31+30+31+30+31+31+30)
		{	month=9;   //��ʾ9�·�
			day=daysafter4years-31-28-31-30-31-30-31-31;   //��ʾ����
		}
		else if(daysafter4years<=31+28+31+30+31+30+31+31+30+31)
		{	month=10;   //��ʾ10�·�
			day=daysafter4years-31-28-31-30-31-30-31-31-30;   //��ʾ����
		}
		else if(daysafter4years<=31+28+31+30+31+30+31+31+30+31+30)
		{	month=11;   //��ʾ11�·�
			day=daysafter4years-31-28-31-30-31-30-31-31-30-31;   //��ʾ����
		}
		else if(daysafter4years<=31+28+31+30+31+30+31+31+30+31+30+31)
		{	month=12;   //��ʾ12�·�
			day=daysafter4years-31-28-31-30-31-30-31-31-30-31-30;   //��ʾ����
		}
	}
	else if (daysafter4years<=730)          //daysafter4years�����������ڵ�2�꣨�����꣩
	{	year=2 ;         						//��������2��,������ʱӦ��year-1
		if (daysafter4years-365<=31)
		{	month=1;   //��ʾ1�·�
			day=daysafter4years;   //��ʾ����
		}
		else if(daysafter4years-365<=31+28)
		{	month=2;   //��ʾ2�·�
			day=daysafter4years-31;   //��ʾ����
		}
		else if(daysafter4years-365<=31+28+31)
		{	month=3;   //��ʾ3�·�
			day=daysafter4years-31-28;   //��ʾ����
		}
		else if(daysafter4years-365<=31+28+31+30)
		{	month=4;   //��ʾ4�·�
			day=daysafter4years-31-28-31;   //��ʾ����
		}
		else if(daysafter4years-365<=31+28+31+30+31)
		{	month=5;   //��ʾ5�·�
			day=daysafter4years-31-28-31-30;   //��ʾ����
		}
		else if(daysafter4years-365<=31+28+31+30+31+30)
		{	month=6;   //��ʾ6�·�
			day=daysafter4years-31-28-31-30-31;   //��ʾ����
		}
		else if(daysafter4years-365<=31+28+31+30+31+30+31)
		{	month=7;   //��ʾ7�·�
			day=daysafter4years-31-28-31-30-31-30;   //��ʾ����
		}
		else if(daysafter4years-365<=31+28+31+30+31+30+31+31)
		{	month=8;   //��ʾ8�·�
			day=daysafter4years-31-28-31-30-31-30-31;   //��ʾ����
		}
		else if(daysafter4years-365<=31+28+31+30+31+30+31+31+30)
		{	month=9;   //��ʾ9�·�
			day=daysafter4years-31-28-31-30-31-30-31-31;   //��ʾ����
		}
		else if(daysafter4years-365<=31+28+31+30+31+30+31+31+30+31)
		{	month=10;   //��ʾ10�·�
			day=daysafter4years-31-28-31-30-31-30-31-31-30;   //��ʾ����
		}
		else if(daysafter4years-365<=31+28+31+30+31+30+31+31+30+31+30)
		{	month=11;   //��ʾ11�·�
			day=daysafter4years-31-28-31-30-31-30-31-31-30-31;   //��ʾ����
		}
		else if(daysafter4years-365<=31+28+31+30+31+30+31+31+30+31+30+31)
		{	month=12;   //��ʾ12�·�
			day=daysafter4years-31-28-31-30-31-30-31-31-30-31-30;   //��ʾ����
		}
		day=day-365;
	}
    else if (daysafter4years<=1096)           //daysafter4years�����������ڵ�һ�꣨���꣩
	{	year=3 ;         				//��������һ��,������ʱӦ��year-1
		if (daysafter4years-730<=31)
		{	month=1;   	//��ʾ1�·�
			day=daysafter4years;   //��ʾ����
		}
		else if(daysafter4years-730<=31+29)
		{	month=2;   //��ʾ2�·�
			day=daysafter4years-31;   //��ʾ����
		}
		else if(daysafter4years-730<=31+29+31)
		{	month=3;   //��ʾ3�·�
			day=daysafter4years-31-29;   //��ʾ����
		}
		else if(daysafter4years-730<=31+29+31+30)
		{	month=4;   //��ʾ4�·�
			day=daysafter4years-31-29-31;   //��ʾ����
		}
		else if(daysafter4years-730<=31+29+31+30+31)
		{	month=5;   //��ʾ5�·�
			day=daysafter4years-31-29-31-30;   //��ʾ����
		}
		else if(daysafter4years-730<=31+29+31+30+31+30)
		{	month=6;   //��ʾ6�·�
			day=daysafter4years-31-29-31-30-31;   //��ʾ����
		}
		else if(daysafter4years-730<=31+29+31+30+31+30+31)
		{	month=7;   //��ʾ7�·�
			day=daysafter4years-31-29-31-30-31-30;   //��ʾ����
		}
		else if(daysafter4years-730<=31+29+31+30+31+30+31+31)
		{	month=8;   //��ʾ8�·�
			day=daysafter4years-31-29-31-30-31-30-31;   //��ʾ����
		}
		else if(daysafter4years-730<=31+29+31+30+31+30+31+31+30)
		{	month=9;   //��ʾ9�·�
			day=daysafter4years-31-29-31-30-31-30-31-31;   //��ʾ����
		}
		else if(daysafter4years-730<=31+29+31+30+31+30+31+31+30+31)
		{	month=10;   //��ʾ10�·�
			day=daysafter4years-31-29-31-30-31-30-31-31-30;   //��ʾ����
		}
		else if(daysafter4years-730<=31+29+31+30+31+30+31+31+30+31+30)
		{	month=11;   //��ʾ11�·�
			day=daysafter4years-31-29-31-30-31-30-31-31-30-31;   //��ʾ����
		}
		else if(daysafter4years-730<=31+29+31+30+31+30+31+31+30+31+30+31)
		{	month=12;   //��ʾ12�·�
			day=daysafter4years-31-29-31-30-31-30-31-31-30-31-30;   //��ʾ����
		}
		day=day-730;
	}
//	else if (daysafter4years<=366+365+365)   			//daysafter4years�����������ڵ�3�꣨�����꣩
	else if (daysafter4years<=366+365+365+365)      //daysafter4years�����������ڵ�3�꣨�����꣩---zzy modified@2010-10-8
	{	year=4 ;       								//��������4��,������ʱӦ��year-1
		if (daysafter4years-366-365-365<=31)
		{	month=1;   //��ʾ1�·�
			day=daysafter4years;   //��ʾ����
		}
		else if(daysafter4years-366-365-365<=31+28)
		{	month=2;   //��ʾ2�·�
			day=daysafter4years-31;   //��ʾ����
		}
		else if(daysafter4years-366-365-365<=31+28+31)
		{	month=3;   //��ʾ3�·�
			day=daysafter4years-31-28;   //��ʾ����
		}
		else if(daysafter4years-366-365-365<=31+28+31+30)
		{	month=4;   //��ʾ4�·�
			day=daysafter4years-31-28-31;   //��ʾ����
		}
		else if(daysafter4years-366-365-365<=31+28+31+30+31)
		{	month=5;   //��ʾ5�·�
			day=daysafter4years-31-28-31-30;   //��ʾ����
		}
		else if(daysafter4years-366-365-365<=31+28+31+30+31+30)
		{	month=6;   //��ʾ6�·�
			day=daysafter4years-31-28-31-30-31;   //��ʾ����
		}
		else if(daysafter4years-366-365-365<=31+28+31+30+31+30+31)
		{	month=7;   //��ʾ7�·�
			day=daysafter4years-31-28-31-30-31-30;   //��ʾ����
		}
		else if(daysafter4years-366-365-365<=31+28+31+30+31+30+31+31)
		{	month=8;   //��ʾ8�·�
			day=daysafter4years-31-28-31-30-31-30-31;   //��ʾ����
		}
		else if(daysafter4years-366-365-365<=31+28+31+30+31+30+31+31+30)
		{	month=9;   //��ʾ9�·�
			day=daysafter4years-31-28-31-30-31-30-31-31;   //��ʾ����
		}
		else if(daysafter4years-366-365-365<=31+28+31+30+31+30+31+31+30+31)
		{	month=10;   //��ʾ10�·�
			day=daysafter4years-31-28-31-30-31-30-31-31-30;   //��ʾ����
		}
		else if(daysafter4years-366-365-365<=31+28+31+30+31+30+31+31+30+31+30)
		{	month=11;   //��ʾ11�·�
			day=daysafter4years-31-28-31-30-31-30-31-31-30-31;   //��ʾ����
		}
		else if(daysafter4years-366-365-365<=31+28+31+30+31+30+31+31+30+31+30+31)
		{	month=12;   //��ʾ12�·�
			day=daysafter4years-31-28-31-30-31-30-31-31-30-31-30;   //��ʾ����
		}
		day=day-366-365-365;
	}
	
	*yearout=fouryears*4+(year-1)+YEARINITAL;       	//���������λ
	*monthout=month;                       				//�����·�
	*dayout=day;                           				//����ʱ��day
	if(days==0)
	{
	*dayout=1;  		
	}
 }

/*********************************************************   
	���ܣ��ҳ�δ�������Ϣ��������յ�����Ϣ
	��ڲ�������
	���ز��������ظ���Ϣ������Ϣͷ�ļ������е�EpromAdd��Ϣ
			  ��δ�ҵ����򷵻�0xffff����ʾ����
	
 *********************************************************/
/*void FindMsg();
void FindMsg()
{
	int i=0,l,position=0,days,hours,minutes,position_temp=0;
//�ҵ���һ����������Ϣ
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
	if(Messageinfo.savenumber[0]==0) position=0xffff;		//��ʱ�޴洢��Ϣ������0xffff
	else
	{
		if(position==0xffff)
		{
			//do nothing
		}
		else
		{	
			for(l=position_temp+1;l<Messageinfo.savenumber[0];l++)		//�ҳ�δ�������Ϣ��������յ�����Ϣ������i
			{
				i=Messagetoprank[l];
				if(Messagesavetop[i].lock==1) continue;	//������Ϣ����
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
		/*�ж����ҳ�����Ϣ�Ƿ��ڵ�ǰʱ��֮ǰ��3��
		days=DatesToDays(Messagesavetop[position].date[0],Messagesavetop[position].date[1],Messagesavetop[position].date[2]);//��ȡ����
		hours=Messagesavetop[position].time[0];		//��ȡСʱ��
		minutes=Messagesavetop[position].time[1];	//��ȡ����	
			
		TODCS|=TODCS_TOD_LOCK_MASK;//����TOD_Lockλ����ȡTODģ����ʱ��ļĴ���
		/* 
		if(((days+3)<TODDAY)||(((days+3)==TODDAY)&&hours<TODHR)||
			(((days+3)==TODDAY)&&(hours==TODHR)&&(minutes<TODMIN)))
		
		if((((days+3)<TODDAY)||(((days+3)==TODDAY)&&hours<TODHR)||
			(((days+3)==TODDAY)&&(hours==TODHR)&&(minutes<=TODMIN)))||(Messagesavetop[position].lock==1))
		position=0xffff;//����ʱȡ��������Ϣ��ʱ������3��֮�⣬��3��ʱ����δ���չ���Ϣ������0xffff			
		TODCS&=~TODCS_TOD_LOCK_MASK;//�ر�TOD_Lock����λ 
	}
	
	if(position==0xffff) 
	{		
//	ThreeDayAlarm=1;	//0xffff��ʾ�����촦����Ϣ�����ThreeDayAlarm��1
	}
	else//�ҵ��´δ�����Ϣ
	{
		Messagesavetop[position].dealed=1;	//deal�����1
		WritebitDeal(position);				//��ӦEpromλ��Ҳ��1
		EpromAddNow=position;				//EpromAddNow��¼�´��账����Ϣ��epromaddֵ

		/*3.ȡ���账����Ϣ��ʱ�䣬���붨ʱ����������ʱ��
		//������ڵ�������ת��
		days=DatesToDays(Messagesavetop[position].date[0],Messagesavetop[position].date[1],Messagesavetop[position].date[2]);
		TODDAL=days+3;							//д������
		TODHAL=Messagesavetop[position].time[0];//д��Сʱ��
		TODMAL=Messagesavetop[position].time[1];//д�����
    	TODCS|=TODCS_TODAEN_MASK;				//������ʱ�����ж�	
 //   	ThreeDayAlarm=0;
	}
	
//	return position;
	
}                 */


/*************************************************   
	���ܣ��趨��ʱ��3�쵽����е���Ϣ����
	��ڲ�������
	���ز�������
 *************************************************/
/*void ThreeDaysUp(void);
void ThreeDaysUp(void)
{	
	#pragma interrupt saveall	//�����жϺ����ݱ���
	int i,position,days,hours,minutes,j,m;
	/*1.����ʱ����Ϣ���������Ϣ��dealed��
	TODCS&=~TODCS_TODAL_MASK;	//�����ʱ���жϱ�־λ
	TODCS&=~TODCS_TODAEN_MASK;	//��ʱ�رն�ʱ�����ж�
/*	
	for(i=0;i<Messageinfo.savenumber[0];i++)	//�ҳ��账����Ϣ��Messagetoprank[]��λ�ã���i��¼
	{
		if(EpromAddNow==Messagetoprank[i]) break;	
	}
	
	if(i==Messageinfo.savenumber[0])//��ǰ��Ϣͷ�ļ��Ҳ�����Ӧ��Ϣ����ʱӦ���б�����
	{
		//������
	}
	else
	{

		if(MessageProcess&0x01)
		{
			MessageProcess|=0x02;	//MessageProcess��bit1λ��1
			TMR0_SCR|=TMR0_SCR_TCFIE_MASK;	//����8K�Ķ�ʱ��0���ж�
		}
		else 
		{
//			m=Messageinfo.savenumber[0];
			for(j=0;j<Messageinfo.savenumber[0];j++)
			{
				days=DatesToDays(Messagesavetop[Messagetoprank[j]].date[0],Messagesavetop[Messagetoprank[j]].date[1],Messagesavetop[Messagetoprank[j]].date[2]);
				hours=Messagesavetop[Messagetoprank[j]].time[0];	//��ȡСʱ��
				minutes=Messagesavetop[Messagetoprank[j]].time[1];	//��ȡ����	
				TODCS|=TODCS_TOD_LOCK_MASK;//����TOD_Lockλ����ȡTODģ����ʱ��ļĴ��� 
//				if(((days+3)<TODDAY)||(((days+3)==TODDAY)&&hours<TODHR)||
//					(((days+3)==TODDAY)&&(hours==TODHR)&&(minutes<=TODMIN)))
				if(((days+3)<TODDAY)||(((days+3)==TODDAY)&&hours<TODHR)||
					(((days+3)==TODDAY)&&(hours==TODHR)&&(minutes<=TODMIN)))
				{
					if(Messagesavetop[Messagetoprank[j]].lock==0)//��������Ϣ�Ĳ���
					{
						Msgdel(j);
						j--;
					}				
				}
				TODCS&=~TODCS_TOD_LOCK_MASK;//�ر�TOD_Lock����λ 

			}
			FindMsg();
//			MesDel(i);		//�ҵ���Ӧ��Ϣ��ɾ��
//			FindMsg();		//�ҳ��´��账����Ϣλ�ã���position��¼�������д���
		}				
//	}


} */