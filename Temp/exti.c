#include "exti.h"

/***************syschronization mask*************/
void IntialIRQB()
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	/* config the extiline(PE0) clock and AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO,ENABLE);
												
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置P[A|B|C|D|E]5为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel =  EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	/* EXTI line gpio config(PE5) */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 // 上拉输入
  GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* EXTI line(PE5) mode config */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource1); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}


/***************decode interrupt and key interrupt*************/
void IntialIRQA()
{
	GPIO_InitTypeDef GPIO_InitStructure; 
	EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	/* config the extiline(PE0) clock and AFIO clock */
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOE | RCC_APB2Periph_AFIO,ENABLE);
												
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置P[A|B|C|D|E]5为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel =  EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	/* EXTI line gpio config(PE5) */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPD;	 // 上拉输入
  GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* EXTI line(PE5) mode config */
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOE, GPIO_PinSource0); 
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}

