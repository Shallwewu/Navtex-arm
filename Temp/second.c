#include "stm32f2xx.h"
#include "misc.h"
#include "stm32f2xx_rcc.h"
#include "stm32f2xx_tim.h"
#include "stm32f2xx_exti.h"

u8 a=0;

void Timer3_Init()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	
	TIM3->ARR = 10000;
	TIM3->PSC = 2000;        //��Ƶ����ֵԽС��ʱ��Խ��
	TIM3->DIER |= 1<<0;
	TIM3->DIER |= 1<<6;
  NVIC_InitStructure.NVIC_IRQChannel =  TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
	TIM3->CR1 |= 0x01;
}  	

void TIM3_IRQHandler(void)
{
	if(TIM3->SR&0x0001)  //����Ƿ�ȷʵ�������ж�
	{
		a++;
		if(a==20)
		{
			a=0;
		}
	}
	TIM3->SR&=~(1<<0);   //��־����
}



	