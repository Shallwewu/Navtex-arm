#include "stm32f2xx.h"
#include "stm32f2xx_rtc.h"
#include "stm32f2xx_pwr.h"
#include <stdio.h>
#include "code.h"
#include "timedelay.h"

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
  
  /* Enable the PWR APB1 Clock Interface */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Allow access to BKP Domain */
  PWR_BackupAccessCmd(ENABLE);
  
  if (RTC_ReadBackupRegister(RTC_BKP_DR0) != 0x1222)
  {  
//    RCC_BackupResetCmd(ENABLE);
    /* RTC configuration  */
  /* Enable the PWR APB1 Clock Interface */
//    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Allow access to BKP Domain */
//    PWR_BackupAccessCmd(ENABLE);
    RTC_Config();

  } 
  else
  {   
    /* Wait for RTC APB registers synchronisation */
    RTC_WaitForSynchro();

    /* Enable BKPSRAM Clock */
    RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_BKPSRAM, ENABLE);   
    
    timestruct=GetTime();     //@wu
    
    iyear = timestruct.year;
    imonth = timestruct.month;
    iday = timestruct.day;
    ihour = timestruct.hour;
    iminute = timestruct.minute;
  } 
}

void RTC_Config(void)
{
  RTC_InitTypeDef RTC_InitStructure;
  /* Enable the PWR clock */
//  RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);

  /* Allow access to RTC */
//  PWR_BackupAccessCmd(ENABLE);

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
  
  /* Enable the RTC Clock */
  RCC_RTCCLKCmd(ENABLE);

  /* Wait for RTC APB registers synchronisation */
  RTC_WaitForSynchro();
  
  /* Write to the first RTC Backup Data Register */
  RTC_WriteBackupRegister(RTC_BKP_DR0, 0x1222);
  
    /* Configure the RTC data register and RTC prescaler */
  RTC_InitStructure.RTC_AsynchPrediv = AsynchPrediv;
  RTC_InitStructure.RTC_SynchPrediv = SynchPrediv;
  RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
  RTC_Init(&RTC_InitStructure);
  /* Configure the time register */
  RTC_TimeRegulate(15, 8, 8, 0, 0); 
  
  delay_us(10);
  
  timestruct=GetTime();     //@wu   
  iyear = timestruct.year;
  imonth = timestruct.month;
  iday = timestruct.day;
  ihour = timestruct.hour;
  iminute = timestruct.minute;  
  
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_BKPSRAM, ENABLE);
  
  /* Enable the Backup SRAM low power Regulator to retain it's content in VBAT mode */
  PWR_BackupRegulatorCmd(ENABLE);

  /* Wait until the Backup SRAM low power Regulator is ready */
  while(PWR_GetFlagStatus(PWR_FLAG_BRR) == RESET)
  {
  }

/* RTC Backup Data Registers **************************************************/
  /* Write to RTC Backup Data Registers */
  RTC_WriteBackupRegister(RTC_BKP_DR0, 0x1222);   
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
    RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure);
  
    iyear = year;
    imonth = month;
    iday = day;
    ihour = hour;
    iminute = minute;
}

timetype GetTime(void)
{
//   RTC_DateTypeDef* RTC_DateStruct;
   RTC_TimeTypeDef* RTC_TimeStruct;
   timetype timeofnow;
   u32 readdate,readtime;
//   RTC_GetDate(RTC_Format_BIN,RTC_DateStruct);
//   RTC_GetTime(RTC_Format_BIN,RTC_TimeStruct);
   readtime=RTC->TR;
   timeofnow.hour=((readtime&0x00300000)>>20)*10+((readtime&0x000f0000)>>16);
   timeofnow.minute=((readtime&0x00007000)>>12)*10+((readtime&0x00000f00)>>8);
   timeofnow.second=((readtime&0x00000070)>>4)*10+(readtime&0x0000000f);  
   readdate=RTC->DR;
   timeofnow.year=((readdate&0x00f00000)>>20)*10+((readdate&0x000f0000)>>16);
   timeofnow.month=((readdate&0x00001000)>>12)*10+((readdate&0x00000f00)>>8);
   timeofnow.day=((readdate&0x00000030)>>4)*10+(readdate&0x0000000f); 
//   timestruct.year=RTC_DateStruct->RTC_Year;
//   timestruct.month=RTC_DateStruct->RTC_Month;
//   timestruct.day=RTC_DateStruct->RTC_Date;
//   timeofnow.hour=RTC_TimeStruct->RTC_Hours;
//   timeofnow.minute=RTC_TimeStruct->RTC_Minutes;
//   timeofnow.second=RTC_TimeStruct->RTC_Seconds;
   return timeofnow;
}
  
  