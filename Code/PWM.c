#include "code.h"
#include "stm32f2xx_gpio.h"
#include "stm32f2xx_rcc.h"
#include "stm32f2xx_tim.h"
#include "define.h"

volatile word Backlight_value[5]={150,250,350,450,550};   //{150,250,350,450,550};
volatile word Contrast_value[5]={130,150,180,200,250};    //{300,400,500,580,650};

/**
 * [PWM_GPIO_Config description]
 */
static void PWM_GPIO_Config(){
	GPIO_InitTypeDef GPIO_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure.GPIO_Pin=GPIO_Pin_6|GPIO_Pin_8;
	GPIO_InitStructure.GPIO_Mode=GPIO_Mode_AF;
	GPIO_InitStructure.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP ;
	GPIO_Init(GPIOB,&GPIO_InitStructure);
	
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_TIM4);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource8, GPIO_AF_TIM4);

}


/**
 * [PWM_Mode_Config description]
 */
static void PWM_Mode_Config(){
	TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
	TIM_OCInitTypeDef TIM_OCInitStructure;
	
	TIM_TimeBaseStructure.TIM_Period=665;
	TIM_TimeBaseStructure.TIM_Prescaler=10;
	TIM_TimeBaseStructure.TIM_ClockDivision=TIM_CKD_DIV1;
	TIM_TimeBaseStructure.TIM_CounterMode=TIM_CounterMode_Up;
	TIM_TimeBaseInit(TIM4,&TIM_TimeBaseStructure);
	
	/*对比度*/
	TIM_OCInitStructure.TIM_OCMode=TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=Contrast_value[Contrast];
	TIM_OCInitStructure.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM_OC1Init(TIM4,&TIM_OCInitStructure);
	TIM_OC1PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	/*亮度*/
	TIM_OCInitStructure.TIM_OutputState=TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse=Backlight_value[Backlight];
	TIM_OC3Init(TIM4,&TIM_OCInitStructure);
	TIM_OC3PreloadConfig(TIM4,TIM_OCPreload_Enable);
	
	TIM_ARRPreloadConfig(TIM4,ENABLE);
	TIM_Cmd(TIM4,ENABLE);
}


/**
 * [PWM_Init description]
 */
void PWM_Init(){
	PWM_GPIO_Config();
	PWM_Mode_Config();
}


/**
 * [Set_Backlight description]
 * @param Backlight [description]
 */
void Set_Backlight(char Backlight){
	TIM_SetCompare3(TIM4,Backlight_value[Backlight]);
}



/**
 * [Set_Contrast description]
 * @param Contrast [description]
 */
void Set_Contrast(char Contrast){
	TIM_SetCompare1(TIM4,Contrast_value[Contrast]);
}