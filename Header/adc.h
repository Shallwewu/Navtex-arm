#ifndef __adc_h
#define __adc_h
static void ADC1_GPIO_Config(void);
static void ADC1_Mode_Config(void);
void ADC1_Init(void);
u16 Get_Adc(u8 ch);
#endif
