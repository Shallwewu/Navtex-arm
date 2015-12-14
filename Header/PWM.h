#ifndef _PWM_H
#define _PWM_H
static void PWM_GPIO_Config(void);
static void PWM_Mode_Config(void);
void PWM_Init(void);
void Set_Backlight(char Backlight);
void Set_Contrast(char Contrast);
#endif
