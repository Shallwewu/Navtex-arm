#include "stm32f2xx.h"
#include "stm32f2xx_adc.h"
#include "stm32f2xx_gpio.h"
#include "stm32f2xx_rcc.h"

static void ADC1_GPIO_Config(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;
	
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB,ENABLE);	
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1| GPIO_Pin_6| GPIO_Pin_7;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0| GPIO_Pin_1;
  GPIO_Init(GPIOB, &GPIO_InitStructure);		
}

static void ADC1_Mode_Config(void)
{
  ADC_CommonInitTypeDef ADC_CommonInitStructure;
  ADC_InitTypeDef ADC_InitStructure;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;
  ADC_CommonInitStructure.ADC_Prescaler = ADC_Prescaler_Div2;
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = ADC_TwoSamplingDelay_5Cycles;
  ADC_CommonInit(&ADC_CommonInitStructure);
	
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ScanConvMode = DISABLE;    //@wu
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;  
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_NbrOfConversion = 1;
  ADC_Init(ADC1, &ADC_InitStructure);
	ADC1->SMPR2 &= 0xc003ffc0;
	ADC1->SMPR2 |= 4<<0;
	ADC1->SMPR2 |= 4<<3;
	ADC1->SMPR2 |= 4<<18;
	ADC1->SMPR2 |= 4<<21;
	ADC1->SMPR2 |= 4<<24;
	ADC1->SMPR2 |= 4<<27;	
}

void ADC1_Init(void)
{
	ADC1_GPIO_Config();
	ADC1_Mode_Config();
	ADC1->CR2|=1<<0;
}

u16 Get_Adc(u8 ch)
{
	ADC1->SQR3 &= 0xffffffe0;
	ADC1->SQR3 |= ch;
	ADC1->CR2|= 0x40000000;
	while(!(ADC1->SR&1<<1));
	return ADC1->DR;
}

/*
void test(void)
{
	u16 adcvalue0=0,adcvalue1=0,adcvalue6=0,adcvalue7=0,adcvalue8=0,adcvalue9=0,b=1;
  ADC1_Init();
  adcvalue0 = Get_Adc(0);
	adcvalue1 = Get_Adc(1);
  adcvalue6 = Get_Adc(6);
  adcvalue7 = Get_Adc(7);
  adcvalue8 = Get_Adc(8);
  adcvalue9 = Get_Adc(9);
	b=2;
}  */
	