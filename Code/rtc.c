#include "stm32f2xx.h"
#include "stm32f2xx_rtc.h"
#include "stm32f2xx_pwr.h"
#include <stdio.h>
#include "code.h"

#define RTC_CLOCK_SOURCE_LSE  

void RTC_Config(void);
void RTC_TimeRegulate(u8 year,u8 month,u8 day,u8 hour,u8 minute);
timetype GetTime(void);

__IO uint32_t AsynchPrediv = 0, SynchPrediv = 0;

void rtcinit(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f2xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f2xx.c file
     */     
	RTC_InitTypeDef RTC_InitStructure;
  if (RTC_ReadBackupRegister(RTC_BKP_DR0) != 0x1234)
  {  
    /* RTC configuration  */
    RTC_Config();

    /* Configure the RTC data register and RTC prescaler */
    RTC_InitStructure.RTC_AsynchPrediv = AsynchPrediv;
    RTC_InitStructure.RTC_SynchPrediv = SynchPrediv;
    RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
    RTC_Init(&RTC_InitStructure);
    /* Configure the time register */
    RTC_TimeRegulate(iyear,imonth,iday,ihour,iminute); 
  }
  else
  {   
    /* Enable the PWR clock */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

    /* Allow access to RTC */
    PWR_BackupAccessCmd(ENABLE);

    /* Wait for RTC APB registers synchronisation */
    RTC_WaitForSynchro();

  }
}

void RTC_Config(void)
{
  /* Enable the PWR clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Allow access to RTC */
  PWR_BackupAccessCmd(ENABLE);
    
#if defined (RTC_CLOCK_SOURCE_LSI)  /* LSI used as RTC source clock*/
/* The RTC Clock may varies due to LSI frequency dispersion. */   
  /* Enable the LSI OSC */ 
  RCC_LSICmd(ENABLE);

  /* Wait till LSI is ready */  
  while(RCC_GetFlagStatus(RCC_FLAG_LSIRDY) == RESET)
  {
  }

  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSI);
  
  SynchPrediv = 0xFF;
  AsynchPrediv = 0x7F;

#elif defined (RTC_CLOCK_SOURCE_LSE) /* LSE used as RTC source clock */
  /* Enable the LSE OSC */
  RCC_LSEConfig(RCC_LSE_ON);

  /* Wait till LSE is ready */  
  while(RCC_GetFlagStatus(RCC_FLAG_LSERDY) == RESET)
  {
  }

  /* Select the RTC Clock Source */
  RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
  
  SynchPrediv = 0xFF;
  AsynchPrediv = 0x7F;

#else
  #error Please select the RTC Clock source inside the rtc.c file
#endif /* RTC_CLOCK_SOURCE_LSI */
  
  /* Enable the RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  /* Wait for RTC APB registers synchronisation */
  RTC_WaitForSynchro();
}

/********Time set************/
void RTC_TimeRegulate(u8 year,u8 month,u8 day,u8 hour,u8 minute)
{
  	RTC_TimeTypeDef RTC_TimeStructure;
  	RTC_DateTypeDef RTC_DateStructure;
    RTC_TimeStructure.RTC_H12     = RTC_H12_PM;
    RTC_TimeStructure.RTC_Hours = hour;
    RTC_TimeStructure.RTC_Minutes = minute;
    RTC_TimeStructure.RTC_Seconds = 0;
 
  /* Configure the RTC time register */
    RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure);
    RTC_DateStructure.RTC_WeekDay = RTC_Weekday_Monday;
    RTC_DateStructure.RTC_Date = day;
    RTC_DateStructure.RTC_Month = month;
    RTC_DateStructure.RTC_Year = year;
  	RTC_SetDate(RTC_Format_BIN, &RTC_DateStructure);
  if((RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure)!= ERROR)&&(RTC_SetDate(RTC_Format_BIN, &RTC_DateStructure)!= ERROR))
  {
    RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);		
  } 
}

timetype GetTime(void)
{
//	 RTC_DateTypeDef* RTC_DateStruct;
	 RTC_TimeTypeDef* RTC_TimeStruct;
	 timetype timeofnow;
	 u32 readdate,readtime;
//	 RTC_GetDate(RTC_Format_BIN,RTC_DateStruct);
//   RTC_GetTime(RTC_Format_BIN,RTC_TimeStruct);
	 readtime=RTC->TR;
	 timeofnow.hour=((readtime&0x00300000)>>20)*10+((readtime&0x000f0000)>>16);
	 timeofnow.minute=((readtime&0x00007000)>>12)*10+((readtime&0x00000f00)>>8);
	 timeofnow.second=((readtime&0x00000070)>>4)*10+(readtime&0x0000000f);	
	 readdate=RTC->DR;
	 timeofnow.year=((readdate&0x00f00000)>>20)*10+((readdate&0x000f0000)>>16);
	 timeofnow.month=((readdate&0x00001000)>>12)*10+((readdate&0x00000f00)>>8);
	 timeofnow.day=((readdate&0x00000030)>>4)*10+(readdate&0x0000000f);	
//	 timestruct.year=RTC_DateStruct->RTC_Year;
//	 timestruct.month=RTC_DateStruct->RTC_Month;
//	 timestruct.day=RTC_DateStruct->RTC_Date;
//	 timeofnow.hour=RTC_TimeStruct->RTC_Hours;
//   timeofnow.minute=RTC_TimeStruct->RTC_Minutes;
//   timeofnow.second=RTC_TimeStruct->RTC_Seconds;
	 return timeofnow;
}
	
	