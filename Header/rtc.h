#ifndef	_RTC_H
#define _RTC_H
#include "stm32f2xx.h"
#include "define.h"
void rtcinit(void);
void RTC_Config(void);
void RTC_TimeRegulate(u8 year,u8 month,u8 day,u8 hour,u8 minute);
timetype GetTime(void);
#endif
