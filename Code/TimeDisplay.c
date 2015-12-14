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
/*功能；转化TOD模块中寄存器TODDAY的数值为国际时间
入口参数：无
出口参数：无
/*********************************************/
void TIM3_IRQHandler(void)
{
//#pragma interrupt alignsp saveall//进入中断后对之前的寄存器状态进行保存	

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

//	TODCS&=0x7fff;			//清除秒中断的标志位
//if(TIM3->SR&0x0001)  //检测是否确实产生此中断
//{
    if(STATE==0)
    {
    	TimeLeft--;
    }
    else if(STATE==799)
	{
			if(LANGUAGE)		//中文界面
			DISASCII(26,28,TimeLeft);
			else				//英文界面
			DISASCII(10,22,TimeLeft);
			
			TimeLeft--;
//			if(TimeLeft>=0)
//			TODCS|=0x0008;//	开启秒中断					
	}

	else
	{

//		DaysToDates(TODDAY,&intlday,&intlmonth,&intlyear);	
		timestruct=GetTime();
		intlyear=timestruct.year;
		intlmonth=timestruct.month;
		intlday=timestruct.day;
		intlminute=timestruct.minute;              		//国际时间分
		intlhour=timestruct.hour;                  		//国际时间小时
		intlsecond=timestruct.second;						//国际时间秒


		if(STATE==5) //此时函数用于TimeLocation界面下的调用	
		{
			if(lcontrol==1)	//本地时间开，进行国际时间到本地时间的转换
				{
					lsecond=timestruct.second;		//秒时间相同
					lminute=timestruct.minute;		//分钟相同
					lyear=intlyear;
					if (sign==1)		//sign为1表示加
					{
						lhour=intlhour+number;
						if(lhour>=24)
						{
							lhour=lhour-24;
							lday=intlday+1;
						}
						else lday=intlday;
						
						if(intlmonth==1||intlmonth==3||intlmonth==5||intlmonth==7||intlmonth==8||intlmonth==10||intlmonth==12)   //intlmonth表示国际几月
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
						if(intlmonth==4||intlmonth==6||intlmonth==9||intlmonth==11)     //表示几月
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
							if(intlyear%4==0)                  //表示闰年
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
						
						if(intlmonth==2||intlmonth==4||intlmonth==6||intlmonth==8||intlmonth==9||intlmonth==11||intlmonth==1)   //intlmonth表示国际几月
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
						if(intlmonth==5||intlmonth==7||intlmonth==10||intlmonth==12)     //c表示几月
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
							if(intlyear%4==0)                  //表示闰年
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

					DISASCII(16,15,20);	//显示本地时间的数值
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



				DISASCII(16,11,20);		//显示国际时间的数值
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
				
				//显示经纬度
				if(iec_rx.new_flag==1)
				{
					DISASCII(17,23,gpslldt[0][0]);	//显示纬度	

					DISASCII(20,23,gpslldt[0][1]);

					DISASCII(23,23,gpslldt[0][2]);
					DISASCII(25,23,gpslldt[0][3]);

					if(gpslldt[0][4]==1)
						CW_PR3(28,23,'N');
					else
						CW_PR3(28,23,'S');
					
					DISASCIII(16,19,gpslldt[1][0]);	//显示经度	

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
//				TODCS|=0x0008;//	开启秒中断	
		}

		else //用于Mainmenu界面下的函数调用
		{
			iyear=intlyear;                 
			imonth=intlmonth;
			iday=intlday;
			ihour=intlhour;
			iminute=intlminute;
		}
	}
// }
	TIM3->SR&=~(1<<0);   //标志清零		
}


