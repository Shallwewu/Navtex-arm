#include <stdio.h>
#include <stdlib.h>
#include "define.h"	
#include "inc.h"
#include "MessageDeal.h"
#include "run.h"
#include "Eprom.h"
#include "code.h"

/***************************************
IRQB�жϺ���������ж�
*****************************************/
void EXTI1_IRQHandler(void);
void EXTI1_IRQHandler(void)
{
//	#pragma interrupt saveall	//�����жϺ����ݱ���
//	byte key;	
	if(EXTI_GetITStatus(EXTI_Line1) !=RESET)
	{
//	ICTL&=~ICTL_IRQB_STATE_MASK;	//����жϱ�־λ
	 byte key;
	 key=FPGARW(300);
	
   if(key&0x0f)     	
	 {		
		Dingxiang[1]=1;	
		Dingxiang[0]=0;	
		counter_flag_sc=1;
	  maskc=0;
	 }
	 else if(key&0xf0)
	 {
		Dingxiang[1]=0;	
		Dingxiang[0]=1;	
		counter_flag_se=1;
	  maske=0;
	 }
	 EXTI_ClearITPendingBit(EXTI_Line1);
 }
}
