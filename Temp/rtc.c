#include "stm32f2xx.h"
#include <stdio.h>

#define RTC_CLOCK_SOURCE_LSE  

RTC_DateTypeDef RTC_DateStructure;
RTC_TimeTypeDef RTC_TimeStructure;
RTC_InitTypeDef RTC_InitStructure;

__IO uint32_t AsynchPrediv = 0, SynchPrediv = 0;

void rtcconfig(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f2xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f2xx.c file
     */     
  if (RTC_ReadBackupRegister(RTC_BKP_DR0) != 0x32F2)
  {  
    /* RTC configuration  */
    RTC_Config();

    /* Configure the RTC data register and RTC prescaler */
    RTC_InitStructure.RTC_AsynchPrediv = AsynchPrediv;
    RTC_InitStructure.RTC_SynchPrediv = SynchPrediv;
    RTC_InitStructure.RTC_HourFormat = RTC_HourFormat_24;
    RTC_Init(&RTC_InitStructure);
    /* Configure the time register */
    RTC_TimeRegulate(); 
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
void RTC_TimeRegulate(void)
{
  uint32_t tmp_hh = 0xFF, tmp_mm = 0xFF, tmp_ss = 0xFF;
  RTC_TimeStructure.RTC_H12     = RTC_H12_PM;
  RTC_TimeStructure.RTC_Hours = 0;
  RTC_TimeStructure.RTC_Minutes = 0;
  RTC_TimeStructure.RTC_Seconds = 0;
  }
  /* Configure the RTC time register */
  RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure)
  RTC_DateStructure.RTC_WeekDay = RTC_Weekday_Saturday;
  RTC_DateStructure.RTC_Date = 1;
  RTC_DateStructure.RTC_Month = RTC_Month_March;
  RTC_DateStructure.RTC_Year = 15;
	RTC_SetDate(RTC_Format_BIN, &RTC_DateStructure)
  if((RTC_SetTime(RTC_Format_BIN, &RTC_TimeStructure)!== ERROR)&&(RTC_SetDate(RTC_Format_BIN, &RTC_DateStructure)!== ERROR))
  {
    RTC_WriteBackupRegister(RTC_BKP_DR0, 0x32F2);		
  } 
}
