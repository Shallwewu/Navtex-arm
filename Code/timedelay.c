#include "stm32f2xx.h"
#include "core_cm3.h"
u8 fac_us;
u16 fac_ms;
void delay_init(u8 SYSCLK)
{
	SysTick->CTRL&= 0xfffffffb;
	fac_us=SYSCLK/8;
	fac_ms=(u16)fac_us*1000;
}

void delay_us(u32 nus)
{
	u32 temp;
	SysTick->LOAD=nus*fac_us;
	SysTick->VAL=0X00;
	SysTick->CTRL|=0X01;
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0X01&&!(temp&(1<<16)));
	SysTick->CTRL&=~(0X01);
	SysTick->VAL=0X00;
}

void delay_ms(u16 nms)
{
	u32 temp;
	SysTick->LOAD=(u32)nms*fac_ms;
	SysTick->VAL=0X00;
	SysTick->CTRL|=0X01;
	do
	{
		temp=SysTick->CTRL;
	}
	while(temp&0X01&&!(temp&(1<<16)));
	SysTick->CTRL&=~(0X01);
	SysTick->VAL=0X00;
}
