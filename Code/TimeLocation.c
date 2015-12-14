#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"
#include "lcddrive.h"
#include "code.h"
#include "stm32f2xx.h"
#include "rtc.h"

extern void TIM3_IRQHandler(void);
//****************************************************/
/*���ܣ�MENU��DISP������������ʵ��һ���˵�����ת
��ڲ�������
���ڲ�������
/*****************************************************/
void Timelocation_Menuchange();
void Timelocation_Menuchange()
{
	if(G_Key == MENU) 
	{
		G_Key=0;			//��������	
		BUFFER[0]=0;		//���˵�ʹ��ȫ�ֱ�������
		FLAG=0;				//����ѭ��
		STATE=4;			//MainMenu״̬Ϊ4
		State4parameter=3;	//��ڲ���Ϊ3����ʾ��TimeLocation����
	}
	
	if(G_Key == DISP&&STATE==5) 
	{
		G_Key=0;			//��������
		BUFFER[0]=0;		//���˵�ʹ��ȫ�ֱ�������
		FLAG=0;				//����ѭ��
		STATE=1;			//Message״̬Ϊ1
		State1parameter=0;	//��ڲ���Ϊ0
	}
}

//************************************************************************/
/*���ܣ�����ʱ����ʾ��������������ʱ��͹���ʱ�䣬��ʱ����߶�
��ڲ�������
���ڲ�������
/*************************************************************************/
void RunTimeLocation();
void RunTimeLocation()
{
	sword i;
  static word abouttime=0;

	if(LANGUAGE==0)		//Ӣ�Ľ���
	{
	     /* д������TIME MENU */
		CTAB[0]='T';	CTAB[1]='I';	CTAB[2]='M';	CTAB[3]='E';	CTAB[5]='M';
		CTAB[6]='E';	CTAB[7]='N';	CTAB[8]='U';
		CW_PR(1,1,9);	

		/* ����ʱ�� LOCAL TIME:*/
		CTAB[0]='L';	CTAB[1]='O';	CTAB[2]='C';	CTAB[3]='A';	CTAB[4]='L';	CTAB[6]='T';
		CTAB[7]='I';
		CTAB[8]='M';	CTAB[9]='E';	CTAB[10]=':';
		CW_PR(5,11,11);
		
		
		/* ����ʱ�� IT TIME:*/
		CTAB[0]='I';	CTAB[1]='T';	CTAB[3]='T';	CTAB[4]='I';	CTAB[5]='M';
		CTAB[6]='E';	CTAB[7]=':';
		CW_PR(5,15,8); 
		
		
		if(lcontrol==0)	//lcontrolΪ0������ʱ���
		{
			CW_PR3(16,15,'O');
			CW_PR3(17,15,'F');	
			CW_PR3(18,15,'F');	
		}
		
		CTAB[0]='L';	CTAB[1]='O';	CTAB[2]='N';	CTAB[3]='G';	CTAB[4]='T';	CTAB[5]='I';
		CTAB[6]='T';
		CTAB[7]='U';	CTAB[8]='D';	CTAB[9]='E';	CTAB[10]=':';
		CW_PR(5,19,11);
		CCW_PR1(18,148,0xa1e3,1);		//��
		CW_PR3(22,19,'.');				//.
		CW_PR3(27,19,'\'');				//'
		
		CTAB[0]='L';	CTAB[1]='A';	CTAB[2]='T';	CTAB[3]='I';	CTAB[4]='T';	CTAB[5]='U';
		CTAB[6]='D';
		CTAB[7]='E';	CTAB[8]=':';	
		CW_PR(5,23,9);
		CCW_PR1(18,180,0xa1e3,1);		//��
		CW_PR3(22,23,'.');				//.
		CW_PR3(27,23,'\'');				//'
	}
 	
 	else				//���Ľ���
 	{
 		
 	 	W_XLINE(0,319,25);		//�����߿�	
		W_CLEARXLINE(0,319,22);	
 								
 		CCW_PR1(1,8,0xcab1,1);	//��һ������"���˵� �Զ�"
 		CCW_PR1(3,8,0xbce4,1);
 		CCW_PR1(5,8,0xb2cb,1);
 		CCW_PR1(7,8,0xb5a5,1);
 		
 		CCW_PR1(7,84,0xb1be,1);//�ڶ�����"����ʱ��"
 		CCW_PR1(9,84,0xb5d8,1);
 		CCW_PR1(11,84,0xcab1,1);
 		CCW_PR1(13,84,0xbce4,1);
 		CW_PR3(15,11,':');
 		
 		CCW_PR1(7,116,0xb9fa,1);	//��������"����ʱ��:��"
 		CCW_PR1(9,116,0xbcca,1);
 		CCW_PR1(11,116,0xcab1,1);
 		CCW_PR1(13,116,0xbce4,1);
 		CW_PR3(15,15,':');
 		if(lcontrol==0) 				
 			CCW_PR1(16,116,0xb9d8,1);
 		
 		CCW_PR1(7,148,0xbead,1);//����������"���ȣ�"
 		CCW_PR1(9,148,0xb6c8,1);
 		CW_PR3(15,19,':');
 		CCW_PR1(18,148,0xa1e3,1);		//��
 		CW_PR3(22,19,'.');
		CW_PR3(27,19,'\'');
 		
 		CCW_PR1(7,180,0xceb3,1);//����������"γ�ȣ�"
 		CCW_PR1(9,180,0xb6c8,1);
 		CW_PR3(15,23,':');
 		CCW_PR1(18,180,0xa1e3,1);		//��
 		CW_PR3(22,23,'.');
		CW_PR3(27,23,'\'');
 		
 	}
 	
	if(iec_rx.new_flag!=1)
	{
		CW_PR3(16,19,'-');				//����
		CW_PR3(17,19,'-');
		CW_PR3(18,19,'-');
		
		CW_PR3(20,19,'-');
		CW_PR3(21,19,'-');

		CW_PR3(23,19,'-');
		CW_PR3(24,19,'-');
		CW_PR3(25,19,'-');
		CW_PR3(26,19,'-');

		CW_PR3(28,19,'-');	
		

		CW_PR3(17,23,'-');				//γ��
		CW_PR3(18,23,'-');		

		CW_PR3(20,23,'-');
		CW_PR3(21,23,'-');

		CW_PR3(23,23,'-');
		CW_PR3(24,23,'-');
		CW_PR3(25,23,'-');
		CW_PR3(26,23,'-');

		CW_PR3(28,23,'-');
	}
 	
 	W_YLINE(0,0,239);		
	W_YLINE(319,0,239);		//���ͼ������ʾ
	if(Mode==1)
	{
		W_current_area(31,2,28,1,manual_area);	//�ֶ�ģʽ����ʾ��ǰ����	
	}
	W_Mode(35,8,32,1);		//�ֶ����Զ�ģʽ����ʾ	

	
//	IPR6|=0x0010;			//����TOD�����жϵ��жϼ���Ϊ01
//    TODCS|=0x0008;
	timestruct=GetTime();
	TIM3_IRQHandler();			//��ʾ��ǰʱ�䣬��Ϻ������ж�
	TIM3->CR1 |= 0x01;   //����ʱ��
	while(FLAG)
	{
     run_tip();
	Timelocation_Menuchange();
	}
//	TODCS&=0xfff7;	
	TIM3->CR1&=0xfffe;   //�ض�ʱ�� 
}