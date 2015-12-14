#include <stdio.h>
#include <stdlib.h>
#include "define.h"	
#include "inc.h"
#include "MessageDeal.h"
#include "run.h"
#include "Eprom.h"
#include "code.h"
#include "stm32f2xx_exti.h"
#include "stm32f2xx.h"
#include "PWM.h"
#include "timedelay.h"

#define  KEYADD 298	//按键位置读取地址

//**********************************/
/*功能；按键中断或者信息解码完成函数
入口参数：无
出口参数：无
/***********************************/
void EXTI0_IRQHandler(void)
{
//	#pragma interrupt saveall	//进入中断后数据保护
 EXTI_InitTypeDef EXTI_InitStructure; 
// EXTI_InitStruct->EXTI_Line = EXTI_Line0;
// EXTI_InitStruct->EXTI_Mode = EXTI_Mode_Interrupt;
 static byte h=0,f=0;
// ++f;
// if(f==5)
// {
//	 h=1;
// }
 if(EXTI_GetITStatus(EXTI_Line0) !=RESET)        //assure having a interrupt
 {
//  uint32_t tmp = 0;
//	byte key;
//	int t;
	static sword i=0; 
//  tmp = (uint32_t)EXTI_BASE;
//  tmp += EXTI_InitStruct->EXTI_Mode;
    /* Disable the selected external lines */
//  *(__IO uint32_t *) tmp &= ~EXTI_InitStruct->EXTI_Line;     //disable this interrupt
	 
//	IPR2&=0xfffc;				//关闭IRQA的中断
//	ICTL&=~ICTL_IRQA_STATE_MASK;	
//	key=G_Key;
//	t=IRQP1;
//  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
//  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
//  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
//  EXTI_InitStructure.EXTI_LineCmd = DISABLE;
//  EXTI_Init(&EXTI_InitStructure); 
	EXTI_ClearITPendingBit(EXTI_Line0);
	 
	G_Key=FPGARW(KEYADD);		//读取来自FPGA，用于判断是按键或是信息
	if(G_Key&0x80)     			//产生中断的是解码结束
	
	{
	/*	counter_flag_s=1;
		if(G_Key&0x20)
		{		
			Dingxiang[1]=1;	
			Dingxiang[0]=0;	
		}
		else
		{
			Dingxiang[1]=0;	
			Dingxiang[0]=1;		
		}*/
		MsgFromFpga();			//调用解码接收函数
	}
	else    					//产生中断的是键盘     
	{
		if(G_Key==BACKLIGHT)
		{
		  G_Key=0;
		  Backlight=(Backlight+1)%5;      
      Set_Backlight(Backlight);			
			Write_Char_Eprm(RX_BACKLIGHT,Backlight);			//Controst 信息写入Eprom	
		}
		
		if(G_Key==CONTRAST)
		{
		  G_Key=0;
		  Contrast=(Contrast+1)%5;    
      Set_Contrast(Contrast);				
			Write_Char_Eprm(RX_CONTRAST,Contrast);			//Controst 信息写入Eprom	
		}
		
		if(G_Key==PW)
		{
				i++;
				if(i>5)
				{
					SaveTime();
					FPGARW(3600)=0X01;
					delay_ms(5);
					FPGARW(3608)=0x02;						
			  }
			 else					//不满足，则
			 {
			 	
			 }			 	
		}
		if(Buzzer[3]&&G_Key!=PW) FPGARW(3600)=0X01;	//若有按键触发，且按键蜂鸣开，则输出0x01;

		if(G_Key==ENT&&(Buzzerstate&0x01))
		{
			Buzzerstate&=0xfe;
	//		G_Key=0;	
		}
		if(G_Key==CLR&&(Buzzerstate&0x02))
		{
			Buzzerstate&=0xfd;
	//		G_Key=0;		
		}
//		if(((IPR6&0X0010)&&(G_Key==MENU||G_Key==DISP)&&STATE==5)||(STATE==0&&BUFFER[0]==2&&G_Key==ENT))
//		{
//			IPR6&=0xFFCF;			//关闭TOD的秒中断,设置中断级别为01
//			TODCS&=0xfff7;//	开启秒中断				
//		}
		LcdDisplay();
	}	
//	*(__IO uint32_t *) tmp |= EXTI_InitStruct->EXTI_Line;    //enable this interrupt
//	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
//  EXTI_Init(&EXTI_InitStructure); 
 }
}


