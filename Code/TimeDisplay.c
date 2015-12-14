#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"
#include "lcddrive.h"
#include "ThreeDays.h"
#include "code.h"
#include "stm32f2xx_tim.h"
#include "rtc.h"

//********************************************/
/*���ܣ�ת��TODģ���мĴ���TODDAY����ֵΪ����ʱ��
��ڲ�������
���ڲ�������
/*********************************************/
void TIM3_IRQHandler(void)
{
//#pragma interrupt alignsp saveall//�����жϺ��֮ǰ�ļĴ���״̬���б���	

static	byte intlyear=0;
static	byte intlmonth=0;
static	byte intlday=0;
	char intlhour=0;
	char intlminute=0;
	char intlsecond=0;
	
	byte lyear=0;
	byte lmonth=0;
	byte lday=0;
	char lhour=0;
	char lminute=0;
	char lsecond=0;

//	TODCS&=0x7fff;			//������жϵı�־λ
//if(TIM3->SR&0x0001)  //����Ƿ�ȷʵ�������ж�
//{
    if(STATE==0)
    {
    	TimeLeft--;
    }
    else if(STATE==799)
	{
			if(LANGUAGE)		//���Ľ���
			DISASCII(26,28,TimeLeft);
			else				//Ӣ�Ľ���
			DISASCII(10,22,TimeLeft);
			
			TimeLeft--;
//			if(TimeLeft>=0)
//			TODCS|=0x0008;//	�������ж�					
	}

	else
	{

//		DaysToDates(TODDAY,&intlday,&intlmonth,&intlyear);	
		timestruct=GetTime();
		intlyear=timestruct.year;
		intlmonth=timestruct.month;
		intlday=timestruct.day;
		intlminute=timestruct.minute;              		//����ʱ���
		intlhour=timestruct.hour;                  		//����ʱ��Сʱ
		intlsecond=timestruct.second;						//����ʱ����


		if(STATE==5) //��ʱ��������TimeLocation�����µĵ���	
		{
			if(lcontrol==1)	//����ʱ�俪�����й���ʱ�䵽����ʱ���ת��
				{
					lsecond=timestruct.second;		//��ʱ����ͬ
					lminute=timestruct.minute;		//������ͬ
					lyear=intlyear;
					if (sign==1)		//signΪ1��ʾ��
					{
						lhour=intlhour+number;
						if(lhour>=24)
						{
							lhour=lhour-24;
							lday=intlday+1;
						}
						else lday=intlday;
						
						if(intlmonth==1||intlmonth==3||intlmonth==5||intlmonth==7||intlmonth==8||intlmonth==10||intlmonth==12)   //intlmonth��ʾ���ʼ���
						{
							if (lday>31 )
							{
								lday=lday-31;
								lmonth=intlmonth+1;
								if (lmonth>12)
								{
									lmonth=lmonth-12;
									lyear=intlyear+1;
								}
								else lyear=intlyear;
								
							}
							else lmonth=intlmonth;
							
						}
						if(intlmonth==4||intlmonth==6||intlmonth==9||intlmonth==11)     //��ʾ����
						{
							if (lday>30 )
							{
								lday=lday-30;
								lmonth=intlmonth+1;
								if (lmonth>12)
								{
									lmonth=lmonth-12;
									lyear=intlyear+1;
								}
								else  lyear=intlyear;
								
							}
							else lmonth=intlmonth;
							
						}
						if(intlmonth==2)
						{
							if(intlyear%4==0)                  //��ʾ����
							{
								if (lday>29 )
								{
									lday=lday-29;
									lmonth=intlmonth+1;
									if (lmonth>12)
									{
										lmonth=lmonth-12;
										lyear=intlyear+1;
									}
									else  lyear=intlyear;
								}
								else lmonth=intlmonth;
								
							}
							else
							{
								if (lday>28 )
								{
									lday=lday-28;
									lmonth=intlmonth+1;
									if (lmonth>12)
									{
										lmonth=lmonth-12;
										lyear=intlyear+1;
									}
									else  lyear=intlyear;
								}
								else lmonth=intlmonth;
							}
						}
								
					}		
				



				    if(sign==0)
					{
						lhour=intlhour-number;
						if(lhour<0)
						{
							lhour=lhour+24;
							lday=intlday-1;
						}
						else lday=intlday;
						
						if(intlmonth==2||intlmonth==4||intlmonth==6||intlmonth==8||intlmonth==9||intlmonth==11||intlmonth==1)   //intlmonth��ʾ���ʼ���
						{
							if (lday<1 )
							{
								lday=lday+31;
								lmonth=intlmonth-1;
								if (lmonth<1)
								{
									lmonth=lmonth+12;
									lyear=intlyear-1;
								}
								else lyear=intlyear;
								
							}
							else lmonth=intlmonth;
							
						}
						if(intlmonth==5||intlmonth==7||intlmonth==10||intlmonth==12)     //c��ʾ����
						{
							if (lday<1 )
							{
								lday=lday+30;
								lmonth=intlmonth-1;
								if (lmonth<1)
								{
									lmonth=lmonth+12;
									lyear=intlyear-1;
								}
								else  lyear=intlyear;
								
							}
							else lmonth=intlmonth;
							
						}
						if(intlmonth==3)
						{
							if(intlyear%4==0)                  //��ʾ����
							{
								if (lday<1 )
								{
									lday=lday+29;
									lmonth=intlmonth-1;
									if (lmonth<1)
									{
										lmonth=lmonth+12;
										lyear=intlyear-1;
									}
									else  lyear=intlyear;
								}
								else lmonth=intlmonth;
								
							}
							else
							{
								if (lday<1 )
								{
									lday=lday+28;
									lmonth=intlmonth-1;
									if (lmonth<1)
									{
										lmonth=lmonth+12;
										lyear=intlyear-1;
									}
									else  lyear=intlyear;
								}
								else lmonth=intlmonth;
							}
						}
								
					}

					DISASCII(16,15,20);	//��ʾ����ʱ�����ֵ
					DISASCII(18,15,lyear);
					CW_PR3(20,15,'/');			
					DISASCII(21,15,lmonth);
					CW_PR3(23,15,'/');
					DISASCII(24,15,lday);
					CW_PR3(26,15,'/');
					DISASCII(27,15,lhour);
					CW_PR3(29,15,':');
					DISASCII(30,15,lminute);
					CW_PR3(32,15,':');	
					DISASCII(33,15,lsecond);
				
				
				}



				DISASCII(16,11,20);		//��ʾ����ʱ�����ֵ
				DISASCII(18,11,intlyear);		
				CW_PR3(20,11,'/');
				DISASCII(21,11,intlmonth);
				CW_PR3(23,11,'/');
				DISASCII(24,11,intlday);
				CW_PR3(26,11,'/');
				DISASCII(27,11,intlhour);
				CW_PR3(29,11,':');
				DISASCII(30,11,intlminute);
				CW_PR3(32,11,':');	
				DISASCII(33,11,intlsecond);
				
				//��ʾ��γ��
				if(iec_rx.new_flag==1)
				{
					DISASCII(17,23,gpslldt[0][0]);	//��ʾγ��	

					DISASCII(20,23,gpslldt[0][1]);

					DISASCII(23,23,gpslldt[0][2]);
					DISASCII(25,23,gpslldt[0][3]);

					if(gpslldt[0][4]==1)
						CW_PR3(28,23,'N');
					else
						CW_PR3(28,23,'S');
					
					DISASCIII(16,19,gpslldt[1][0]);	//��ʾ����	

					DISASCII(20,19,gpslldt[1][1]);

					DISASCII(23,19,gpslldt[1][2]);
					DISASCII(25,19,gpslldt[1][3]);
	
					if(gpslldt[1][4]==1)
						CW_PR3(28,19,'W');
					else
						CW_PR3(28,19,'E');	
				}
                maske=0;
                maskc=0;
//				TODCS|=0x0008;//	�������ж�	
		}

		else //����Mainmenu�����µĺ�������
		{
			iyear=intlyear;                 
			imonth=intlmonth;
			iday=intlday;
			ihour=intlhour;
			iminute=intlminute;
		}
	}
// }
	TIM3->SR&=~(1<<0);   //��־����		
}


