#include "stm32f2xx.h"
#include "misc.h"
#include "stm32f2xx_rcc.h"
#include "stm32f2xx_tim.h"
#include "stm32f2xx_exti.h"
#include "stm32f2xx_syscfg.h"
#include "stm32f2xx_gpio.h"
#include "adc.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "ThreeDays.h"
#include "Eprom.h"
#include "flash.h"
#include "code.h"
#include "printer.h"
#include "iec.h"
#include "MessageDeal.h"
#include "timedelay.h"
#include "fsmc.h"
#include "rtc.h"
#include "PWM.h"
//#define FPGARW(offset)   *((volatile word *)(0x002f8000+offset))   //�Լ��ӵĹ���FPGA��д

//volatile char Antennaing=0;	//���������Լ����洢�ı���������ʼ�Լ���1���Լ������0


//extern unsigned char receiver_state[500];
extern void sFLASH_Init(void);

void Init_Fpga(void)
{
	GPIO_InitTypeDef GPIO_InitStructure;                   
	EXTI_InitTypeDef EXTI_InitStructure;

	/* config the extiline(PE0) clock and  */
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);

	/* EXTI line gpio config(PE5) */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;    
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;  
	GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	 
  GPIO_Init(GPIOC, &GPIO_InitStructure);
}

void Fpga_reset(void)
{
  GPIOC->ODR &=0xffffdfff;
  delay_us(10);
	GPIOC->ODR |=0x00002000;	
}

/*********************************************************************/
/*���ܣ����ջ�״̬��ʼ��
��ڲ�������
���ڲ�������
/**********************************************************************/
void receiver_state_init(void);
void receiver_state_init(void)
{
	unsigned char a1[41]=" RECEIVER STATE                   MANUAL";//���ֽں���
	unsigned char a2[13]="  NAVAREA:11";
	unsigned char a3[27]="      518KHZ DISABLED AREA";
	unsigned char a4[35]="        --------------------------";
	unsigned char a5[27]="      486KHZ DISABLED AREA";
	unsigned char a6[30]="      4209.5KHZ DISABLED AREA";
	
	unsigned char a7[31]="      518KHZ DISABLED MSG TYPE";
	unsigned char a8[31]="      486KHZ DISABLED MSG TYPE";
	unsigned char a9[34]="      4209.5KHZ DISABLED MSG TYPE";
	
	unsigned char a10[23]="  SAVE MSG:000;000;000";
	unsigned char a11[23]="  LOCK MSG:000;000;000";
	
	u16 i=0,j=0;
//
//line 1---0-40
	for(i=0;i<40;i++)
	{
		receiver_state[i]=a1[i];
	}
	receiver_state[i++]='\n';
//line2---41
	receiver_state[i++]='\n';
//line3---42-54
	for(j=0;j<12;j++)
	{
		receiver_state[i++]=a2[j];
	}
	receiver_state[i++]='\n';
//line4---55-81
	for(j=0;j<26;j++)
	{
		receiver_state[i++]=a3[j];
	}
	receiver_state[i++]='\n';
//line5---82-116
	for(j=0;j<34;j++)
	{
		receiver_state[i++]=a4[j];
	}
	receiver_state[i++]='\n';
//line6---117-143
	for(j=0;j<26;j++)
	{
		receiver_state[i++]=a5[j];
	}
	receiver_state[i++]='\n';
//line7---144-178
	for(j=0;j<34;j++)
	{
		receiver_state[i++]=a4[j];
	}
	receiver_state[i++]='\n';
//line8---179-208
	for(j=0;j<29;j++)
	{
		receiver_state[i++]=a6[j];
	}
	receiver_state[i++]='\n';
//line9---209-243
	for(j=0;j<34;j++)
	{
		receiver_state[i++]=a4[j];
	}
	receiver_state[i++]='\n';
//line10---244-274
	for(j=0;j<30;j++)
	{
		receiver_state[i++]=a7[j];
	}
	receiver_state[i++]='\n';
//line11---275-309
	for(j=0;j<34;j++)
	{
		receiver_state[i++]=a4[j];
	}
	receiver_state[i++]='\n';
//line12---310-340
	for(j=0;j<30;j++)
	{
		receiver_state[i++]=a8[j];
	}
	receiver_state[i++]='\n';
//line13---341-375
	for(j=0;j<34;j++)
	{
		receiver_state[i++]=a4[j];
	}
	receiver_state[i++]='\n';
//line14---376-409
	for(j=0;j<33;j++)
	{
		receiver_state[i++]=a9[j];
	}
	receiver_state[i++]='\n';
//line15---410-444
	for(j=0;j<34;j++)
	{
		receiver_state[i++]=a4[j];
	}
	receiver_state[i++]='\n';
//line16---445
	receiver_state[i++]='\n';
//line17---446-468
	for(j=0;j<22;j++)
	{
		receiver_state[i++]=a10[j];
	}
	receiver_state[i++]='\n';
//line18---469-490
	for(j=0;j<22;j++)
	{
		receiver_state[i++]=a11[j];
	}
	receiver_state[i++]='\n';
	
}

/*********************************************************************/
/*���ܣ���Ϣ��ʾ�˵���ʾ
��ڲ�����unsigned char use,use=1,��ʾ��ʾtip;use=0,�����ʾtip
���ڲ�������
/**********************************************************************/
void run_tip()
{
    sword i,j; 
    if(maske==0)
	  {
       if(counter_flag_se!=0)
       {
		     for(i=0;i<5;i++)
			    for(j=0;j<7;j++)
				    W_DOT(288+i,232+j);	
		     for(j=0;j<5;j++)
		     	W_CLEARDOT(290,233+j);			//channel 1	
       }
       else
       {
		     for(i=0;i<5;i++)
		     	for(j=0;j<7;j++)
			    	W_CLEARDOT(288+i,232+j);       	
       }
       maske=1;
	  }
 	  if(maskc==0)
 	  {
 	    if(counter_flag_sc!=0)
 	    {
        if(Workfre==1)	//channel 2
	      {
	      	for(i=0;i<5;i++)
		    	 for(j=0;j<7;j++)
			    	W_DOT(294+i,232+j);	

		    	for(i=0;i<3;i++)
				   W_CLEARDOT(295+i,233);
		     	W_CLEARDOT(297,234);
			    for(i=0;i<3;i++)
				   W_CLEARDOT(295+i,235);
			    W_CLEARDOT(295,236);
			    for(i=0;i<3;i++)
			     W_CLEARDOT(295+i,237);			
        }
	      else if(Workfre==0)	//channel 3
	      {
	    	  for(i=0;i<5;i++)
		    	 for(j=0;j<7;j++)
			    	W_DOT(300+i,232+j);	
			    for(i=0;i<3;i++)
				   W_CLEARDOT(301+i,233);
		   	  W_CLEARDOT(303,234);
			    for(i=0;i<3;i++)
				   W_CLEARDOT(301+i,235);
			    W_CLEARDOT(303,236);
			    for(i=0;i<3;i++)
  			   W_CLEARDOT(301+i,237);		
        }	
		  }
		  else
	   	{
	      for(i=0;i<11;i++)
		  	 for(j=0;j<7;j++)
			    W_CLEARDOT(294+i,232+j);	  				
	   	}
		maskc=1;
 	 }
}


//void run_tip1()
//{
	/*
    sword i,j;
    if(maske==0)
	  {
       if(counter_flag_se!=0)
       {
		     for(i=0;i<5;i++)
			    for(j=0;j<7;j++)
				    W_DOT(288+i,232+j);	
		     for(j=0;j<5;j++)
		     	W_CLEARDOT(290,233+j);			//channel 1	
       }
       else
       {
		     for(i=0;i<5;i++)
		     	for(j=0;j<7;j++)
			    	W_CLEARDOT(288+i,232+j);       	
       }
       maske=1;
	  }
 	  if(maskc==0)
 	  {
 	    if(counter_flag_sc!=0)
 	    {
        if(Workfre==1)	//channel 2
	      {
	      	for(i=0;i<5;i++)
		    	 for(j=0;j<7;j++)
			    	W_DOT(294+i,232+j);	

		    	for(i=0;i<3;i++)
				   W_CLEARDOT(295+i,233);
		     	W_CLEARDOT(297,234);
			    for(i=0;i<3;i++)
				   W_CLEARDOT(295+i,235);
			    W_CLEARDOT(295,236);
			    for(i=0;i<3;i++)
			     W_CLEARDOT(295+i,237);			
        }
	      else if(Workfre==0)	//channel 3
	      {
	    	  for(i=0;i<5;i++)
		    	 for(j=0;j<7;j++)
			    	W_DOT(300+i,232+j);	
			    for(i=0;i<3;i++)
				   W_CLEARDOT(301+i,233);
		   	  W_CLEARDOT(303,234);
			    for(i=0;i<3;i++)
				   W_CLEARDOT(301+i,235);
			    W_CLEARDOT(303,236);
			    for(i=0;i<3;i++)
  			   W_CLEARDOT(301+i,237);		
        }	
		  }
		  else
	   	{
	      for(i=0;i<11;i++)
		  	 for(j=0;j<7;j++)
			    W_CLEARDOT(294+i,232+j);	  				
	   	}
		maskc=1;
 	 }   */    //@wu
//}
//*********************************************************************/
/*���ܣ���2���и��������ݴ�����
��ڲ���������2���ݴ���
���ڲ��������ؼ�����
/**********************************************************************/
word Power(sword mici)
{
	word temp1,temp2;
	temp1=0x0001;
	temp2=temp1<<mici;
	return temp2;

}


//*********************************************************************/
/*���ܣ�TODģ��ĳ�ʼ��
��ڲ�������
���ڲ�����
/**********************************************************************/
void IntialSecInterrupt();		
void IntialSecInterrupt()
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
//	TIM3->CR1 |= 0x01;   //����ʱ��
//	TIM3->CR1&=0xfffe;   //�ض�ʱ��  
}

/***************syschronization mask*************/
void IntialIRQB()
{
	GPIO_InitTypeDef GPIO_InitStructure;                   
	EXTI_InitTypeDef EXTI_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
	/* config the extiline(PE0) clock and  */
//  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
//	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
												
  /* Configure one bit for preemption priority */
//  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* ����P[A|B|C|D|E]5Ϊ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel =  EXTI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	/* EXTI line gpio config(PE5) */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;    
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   	
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	 // ��������
  GPIO_Init(GPIOE, &GPIO_InitStructure);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource1);
	
	/* EXTI line(PE5) mode config */	
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½����ж�
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
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* ����P[A|B|C|D|E]5Ϊ�ж�Դ */
  NVIC_InitStructure.NVIC_IRQChannel =  EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	/* EXTI line gpio config(PE5) */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   	
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	 // ��������
  GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* EXTI line(PE5) mode config */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource0);
	
	/* EXTI line(PE5) mode config */	
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½����ж�
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}

//*********************************************************************/
/*���ܣ�ȫ�ֱ����ĳ�ʼ��
��ڲ�������
���ڲ�����
/**********************************************************************/
void Intial_GlobalData();
void Intial_GlobalData()
{
	
	
	char i,j;

	sword t=0,p=0;
	LANHELP=1;			//�����Ľ����£�����ֵΪ0���򵯳��˵���ΪӢ�Ľ�����Ƶĵ����Ӳ˵�
	G_Key=0;			//��ʼ������Ϊ0��0��ʾ�޼�����
	FLAG=1;				//���ڸ��������µ�ѭ������־����Ϊ0������ѭ��
	STATE=0;			//STATEΪ�ж�����ν������ڲ�������ʼ��Ϊ0
	State1parameter=0;	//��Ϣ���Ľ������ڲ�����0��ʾ�������룬���ǴӴ洢�������������
	subback=0;			//���淵�س�ʼ��Ϊ��		


	/***********************************/
	/*  ��Ϣ�洢�˵����漰�ӽ������   */
	/***********************************/

	Selectsubback=0; 	//���ڽ��븴ѡ����Ľ����������
	Selectreturn=0;  	//���ڸ�ѡ����ĳ��ڲ�������
	Mulnownumber=0; 	//��Ϊ��ѡ����ĵ�ǰ������Ϣ����
	Returnback=0;  		//���ڴ洢������������湫�õ���ڲ�������
	Messagenumber=0; 	//���ڴ洢�������������������Ϣ���ļ�¼
	Rankback=0; 		//�������򹫹��������ڲ�������
	
	BUFFERPRINT=0;	  	//ר���ڴ�ӡȷ������MessageSubmenu�Ĳ�������
	BUFFERSELECTLOCK=0; //ר����������ѡ��������ı���
	
	/*******************************/	
	/*  ��Ϣ�˵����漰�ӽ������   */
	/*******************************/
	/*MESSAGE*/
	Returntype=0; 	//��ʾ�ǴӺν��������Ϣ���ݽ��棬10��ʾ�ӽ������
					//1���ص��洢��2���ص�����,
	PublicReturn=0; //���ڹ����������ڲ���
	PitchDAPro=0;	//�����������ڲ�������
	Messagenownumber=0;
	

	/*******************************/	
	/*  LCD   */
	/*******************************/		


  	for(i=0;i<40;i++)
	{
		CTAB1[i]=0x20;  
	}

	
	for(i=0;i<10;i++)
	{
		BUFFER[i]=0;	//��һ���˵���ÿ���˵���������������㣬�������Ӳ˵�������ı�
		BUFFER1[i]=0;	//�ڶ����˵�
		BUFFER2[i]=0;	//�������˵�
		BUFFER3[i]=0;	//���ļ��˵�
		BUFFER4[i]=0;	//���弶�˵�	
		BUFFERPRO[i]=0;	//��һ���˵��ı���������Ϣ�洢�������Ϣ�������浽��Ϣ���ݲ˵��л�ʱ��?
	}

	
	/*******************************/	
	/*  MAINMEUN  */
	/*******************************/	

	PrtStart=(PrtLink *)malloc(sizeof(PrtLink));	//��ʼ����ӡ���е���ָ��
	receiver_state_init();	
			
//	PrtStart->next=NULL;
//	PrtStart->xulie=0;	//��ʼ����ӡ��Ϣ��λ0	
	for(i=0;i<22;i++) 	//ר���ڹ��ø�ѡ����Savelocksubmenu�Ĳ�������
	{
		BUFFERSELECT[i]=0;
	}
		
	for(i=0;i<3;i++)
	{
		for(j=0;j<26;j++)
		{
			Autotemp[i][j]=0;		//��ʼ����ʱ�Զ�ģʽ�ķ���̨ȫ��ѡ��		
			Manualtemp[i][j]=0;		//��ʼ����ʱ�ֶ�ģʽ�ķ���̨ȫ��ѡ��
			MSGTYPETEMP[i][j]=0;	//��ʼ����ʱ��Ϣ���ѡ��ȫ������
		}
	}
	manual_area=11;
	flag_s=0;			//��Ϣ��ʾ��־��0
	counter_flag_se=0;	//��Ϣ��ʾ��־������0
	counter_flag_sc=0;	//��Ϣ��ʾ��־������0
	flag_new_message=0;	//����Ϣ�յ���־��0
	auto_area=11;
	iec_alarm_data=0;
	flag_on=0;
	now_printing=0;
	Jiemamount=0;
	falsh_error=0;
}



//*********************************************************************/
/*���ܣ����ջ�������Ϣ�ָ��������ü���
��ڲ�������
���ڲ�����
/**********************************************************************/
void Intial_Original_Receiver();
void Intial_Original_Receiver()
{

	sword i,j;

	/*******************************/
	/*  ���˵����漰�ӽ������   */
	/*******************************/
	for(i=0;i<3;i++)
	{
		for(j=0;j<26;j++)
		{
			Auto[i][j]=0;		//���������Զ�ģʽ�ķ���̨ȫ��ѡ��		
			Manual[i][j]=0;		//���������Զ�ģʽ�ķ���̨ȫ��ѡ��
			MSGTYPE[i][j]=0;	//����������Ϣ���ѡ��ȫ������
			
		}
	}
	manual_area=11;//��ʼ��11��
	Eprom_AutoMode_Save();
	Eprom_ManualMsgMode_Save(RXSTATION_MANUAL );
	Eprom_ManualMsgMode_Save(RX_MSGTYPE);

	/*����ʱ��*/                //�����ֱ��ʾ����ʱ���������ʱ��

	number=0;          		//����ʱ�������
	sign=1;            		//��������������
	lcontrol=0;         	//������¼����ʱ���Ƿ�

	Write_Char_Eprm(RX_TIME,number);//number ��Ϣд��Eprom
	Write_Char_Eprm(RX_TIME+1,sign);//sign ��Ϣд��Eprom
	Write_Char_Eprm(RX_TIME+2,lcontrol);//sign ��Ϣд��Eprom
	
	/*���ջ�����*/              //�ֱ�������ʾ���ջ���һЩ����
	for(i=0;i<5;i++)	//���γ�ʼ��������ʾ������������ֶ������ݸ�ʽ����������38kbps,��ӡ������ֱ
	{
		Receiverset[i]=0;
		Write_Char_Eprm(PRINTER_FORMAT+i,Receiverset[i]);	//д��Eprom
	}

	for(i=0;i<4;i++)	//��ʼ������ȫ��
	{
		Buzzer[i]=0;
	}
	Contrast=0;				//��ʾ�Աȶȵ�ѡ��
	Diaglogs=0;				//���ڼ�¼��ǰ��д��־��Diagresult[]��λ��
	Diaglogn=0;				//���ڼ�¼��־������

	Eprom_Buzzer_Save();
	Write_Char_Eprm(RX_CONTRAST,Contrast);	//Controst ��Ϣд��Eprom
 	Write_Char_Eprm(DIAGLOGN,Diaglogn);		//Diaglogn����Eprom
   	Write_Char_Eprm(DIAGLOGS,Diaglogs);		//Diaglogs����Eprom

	Operated=0;				//��ʼ��Ϊ0����Ҫ��������ѡ��
   	Write_Char_Eprm(OPERATED,Operated);		//Operated����Eprom	
	

	/* Rx station*/
	Mode=1;				//��¼��ǰ���ں���ģʽ��0��ʾ�Զ���1��ʾ�ֶ�
	Workfre=1;			//��¼��ǰ�Ĺ���Ƶ�ʣ�0ѡ��3�֣�1ѡ��518/486��2ѡ��518/4209.5
	Write_Char_Eprm(RX_MODE,Mode);			//����Mode��Eprom
	Write_Char_Eprm(RX_WORKFRE,Workfre);			//����Mode��Eprom
}

/*************************************************   
	���ܣ���ӡ����ʼ������
	��ڲ�������
	���ز�������
 *************************************************/
void Intial_Printer();
void Intial_Printer()
{
	/* ��ӡ��*/
	IntialRS232();
	Checkinfo.Printerror=0; //��ʼ����ӡ��������
	Checkinfo.Printover=1;  //��ʼ����ӡ����ӡ��

}

/*************************************************   
	���ܣ�COP,���Ź���ʼ��������������2.1S��ι��
	      ����ϵͳ�����λ
	��ڲ�������
	���ز�������
 *************************************************/
//void Intial_COP();
//void Intial_COP()
//{
//	COPTO=0XFFFF;
//	COPCTL|=COPCTL_CEN_MASK;	//COPʹ��
//}


/*************************************************   
	���ܣ�FPGA��ʼ������
	��ڲ�������
	���ز�������
 *************************************************/
void Intial_FPGA();
void Intial_FPGA()
{
/*	GPIO_B_PER&=0xefff;//GPIOB12,FPGA_RESET����Ϊ��ͨIO��
 	GPIO_B_DDR|=0X1000;//GPIOB12,FPGA_RESET����Ϊ�����
  	GPIO_B_DR&=0Xefff;//�������0�����г�ʼ��
  	asm(nop);
    asm(nop);
  	asm(nop);
    asm(nop);
   	asm(nop);
    asm(nop);	
 	GPIO_B_DR|=0X1000;//��ʼ����ϣ��������1	*/
}

//*********************************************************************/
/*���ܣ������������غ���
��ڲ�������
���ڲ�������
/**********************************************************************/
void IntialNormal()
{	
	delay_init(72);
  FSMC_GPIO_Config();
  FSMC_Config();	
	Init_Fpga();				//FPGA��ʼ�
	Fpga_reset();	
	IIC_Init();				//EEPROM��ʼ��
	Intial_GlobalData();		//ȫ�ֱ�����ʼ��
//	Intial_Original_Receiver();	
	Intial_Normal_Receiver();	//���ؽ��ջ�������Ϣ
	Intial_Message();			//���ؽ��ջ��洢��Ϣ
	
	pinoflcdinit();
	PWM_Init();	                 //PWM INIT

	W_DOT(0,0);
	IntialLCD(0);				//LCD��ʼ��
		//RunLanguageChoose();
  sFLASH_Init();
	IntialIRQA();				//IRQA�жϿ���	
	IntialSecInterrupt();		//TODʱ��ģ���ʼ��		
//	asm (bfclr #$0300,sr);		//�������ж�,�����жϼ�����Ч
//	Workfre=0;
	FPGARW(3602)=Workfre;		//ͨ��ѡ��
  ADC1_Init();
//	if(Operated==0)				//��������ʱ��Ҫ������Ӣ�Ĳ˵�ѡ��
	RunLanguageChoose();	//�����Ӣ�Ĳ˵�ѡ��
	RunBoot();					//BOOT�Լ�����
	
//@wu	IntialTIMER();				//��ʱ��0��ʼ��
//	IntialJietiaoDataTran();	//�������Ķ�ʱ����ʼ������   �Ƿ���ע�͵�???
	Intial_Printer();			//��ӡ����ʼ��
	IntialRS232_iec();
//	StartRS232_iec();
//	IntialTOD();				//���춨ʱ������
//	iec_send_alarm();
	IntialIRQB();				//IRQB�жϿ���	
}



//*********************************************************************/
/*���ܣ��ָ��������ü��غ���
��ڲ�������
���ڲ�����
/**********************************************************************/

void IntialOriginal();
void IntialOriginal()
{
//    IPR2&=0xfff0;  //���ж�A��B
  DISABLEIRQB();
  DISABLEIRQA();
//	TODCS&=0xfff7;  //�����ж�
	TIM3->CR1&=0xfffe;
	Reset_Flash();
  Reset_Message();
	Intial_FPGA();
	
	IIC_Init();				//EEPROM��ʼ��
	delay_init(72);
  FSMC_GPIO_Config();
  FSMC_Config();	
		
	Intial_GlobalData();	
	Intial_Original_Receiver();
	Intial_Message();
	

	W_DOT(0,0);
	IntialLCD(0);

	ENABLEIRQA();			//IRQA�жϿ���
//	asm (bfclr #$0300,sr);	//�������ж�,�����жϼ�����Ч
	
	RunLanguageChoose();	//�����Ӣ�Ĳ˵�ѡ��	
	RunBoot();

//	IntialTIMER();			//��ʱ��0�ĳ�ʼ����������Ϣ����
//	IntialJietiaoDataTran();//DSP��FPGA���ݽ�����ݵ��жϺ�������ʱ��2�ĳ�ʼ��

	Intial_Printer();
//	IntialTOD();
	
 	ENABLEIRQB();			//IRQB�жϿ���

}







//                  RS232���          //
char RS232_Check(void);
char RS232_Check(void)
{
	
}


//                  POWER���          //
char Power_Check(void);
char Power_Check(void)
{
	char result=0;	//0��ʾ������bit0��Ӧͨ��4�bbit1��Ӧͨ��5,bit2��Ӧͨ��6,bit3��Ӧͨ��7
	u16 volt[7]; 	
	u16 V2_5=3103;	
	u16 V1_68=2085;	
	u16 V1_65=2048;	
	u16 V2_08=2582;	
	u16 V1_5=1862;	
	u16 V1_9=2358;

  volt[0] = Get_Adc(0);    //2.5V
	volt[1] = Get_Adc(1);    //1.9V
  volt[2] = Get_Adc(6);    //1.65V
  volt[3] = Get_Adc(7);    //2.08V
  volt[4] = Get_Adc(8);    //1.5V
  volt[5] = Get_Adc(9);    //2.5V


//	volt[6]=TLCDA(0x0001);	//ͨ��2--ģ���486��1.28V��Դ
	if(V2_5>=volt[0])
	{
		if(fabs(V2_5-volt[0])>155) 
			result|=0x01;
	}
	else
	{
		if(fabs(volt[0]-V2_5)>155) 
			result|=0x01;		
	}
	
	if(V1_9>=volt[1])
	{
		if(fabs(V1_9-volt[1])>236) 
			result|=0x02;
	}
	else
	{
		if(fabs(volt[1]-V1_9)>236) 
			result|=0x02;		
	}
	
	if(V1_65>=volt[2])
	{
		if(fabs(V1_65-volt[2])>102) 
			result|=0x04;
	}
	else
	{
		if(fabs(volt[2]-V1_65)>102) 
			result|=0x04;
	}
	
	if(V2_08>=volt[3])
	{
		if(fabs(V2_08-volt[3])>129) 
			result|=0x08;
	}
	else
	{
		if(fabs(volt[3]-V2_08)>129) 
			result|=0x08;
	}
	
	if(V1_5>=volt[4])
	{
		if(fabs(V1_5-volt[4])>93) 
			result|=0x10;
	}
	else
	{
		if(fabs(volt[4]-V1_5)>93) 
			result|=0x10;
	}
	
	if(V2_5>=volt[5])
	{
		if(fabs(V2_5-volt[5])>155) 
			result|=0x20;
	}
	else
	{
		if(fabs(volt[5]-V2_5)>155) 
			result|=0x20;
	}	
//	if(fabs(V2_5-volt[0])>390) result|=0x01;
//	if(fabs(V1_68-volt[1])>180) result|=0x02; 
////	if(fabs(V1_65-volt[2])>170) result|=0x04;
//	if(fabs(V1_5-volt[2])>140) result|=0x04;
//	if(fabs(V2_08-volt[3])>270) result|=0x08;
//	if(fabs(V1_5-volt[4])>140) result|=0x10; 
////	if(fabs(V1_65-volt[5])>170) result|=0x20; 
//	if(fabs(V2_5-volt[5])>390) result|=0x20; 
////	if(fabs(V1_3-volt[6])>25) result|=0x40;	
	
	return result;		
}

//                  Antenna���          //
char Antenna_Check(void);
char Antenna_Check(void)
{
	Antennaing=1;	//�����Լ쿪ʼ����1
	Antenna=1;		//���������Լ�
}

//                  518���          //
char C1_Check(void);
char C1_Check(void)
{
	char result=0;	//0��ʾ������1��ʾ518ͨ������
	u16 volt;
	u16 V1_3=53;	//1.04V��Ӧ��������
	
	volt=53;  //Get_Adc();	//ͨ��1--ģ���518��1.28V��Դ	

	if(V1_3-volt>50) result=1;	
	return result;
}

//                  490��4209.5���          //
char C2_Check(void);
char C2_Check(void)
{
	char result=0;	//0��ʾ������1��ʾ2��3ͨ������
	u16 volt;
	u16 V1_3=65;	//1.28V��Ӧ��������
	
	volt=65;  //Get_Adc();	//ͨ��2��3--ģ���518��1.28V��Դ	

	if((V1_3-volt)>50) result=1;
	return result;
}


//                  RAM���          //
void RAM_Check(void);
void RAM_Check(void)
{
	 
	char i;
 	sword datacheck[6]=
 	{
 		0x1234,0x4567,0x89ab,0xcdef,0x5555,0xaaaa
 	};
	Diaglog[Diaglogs].diagresult[1]=0;
 	
/* 	for(i=0;i<6;i++)
 	{
 		*((int*)(0x3EEEE + i))=datacheck[i];
 	}
 	
 	
 	for(i=0;i<6;i++)
 	{
 		if(datacheck[i]!=*((int*)(0x3EEEE +i)))
 		
 		Diaglog[Diaglogs].diagresult[1]=1 ;
 	}     */   //@wu
}


 /**************************/
 /*���ܣ�д��������ʾ���ݺ���
   ��ڲ���������������ַ�*/
 /**************************/
 void Selfdiag(char temp);
 void Selfdiag(char temp)
 {
 	

 	//1.rom check
 	Diaglog[Diaglogs].diagresult[0]=CFI_Query();//���FALSH�Ƿ���Ч
 	
 	//2.ram check,����Ram������дʮ�������������ȽϽ��,�������Ϊ0����֮Ϊ1 	

 	RAM_Check();
 	//3.serial check,����Eprom,RS232,����ֵΪ1��Eprom����2��RS232����3������ͬʱ����
 	
 	Diaglog[Diaglogs].diagresult[2]=Eprom_Check();
 	if(RS232_Check()) Diaglog[Diaglogs].diagresult[2]+=2;
 	//4.power���
 	Diaglog[Diaglogs].diagresult[3]=Power_Check();
 	
 	//5.antenna���
 	AntennaResult=C1_Check();
//  	Antenna_Check();
//  	AntennaCheck();
  //	while(Antennaing){};
  	Diaglog[Diaglogs].diagresult[4]=AntennaResult;
  	
  	//6.518,490,4209.5����ͨ�����	
  	Diaglog[Diaglogs].diagresult[5]=C1_Check();
  	Diaglog[Diaglogs].diagresult[6]=C2_Check(); 		 
   	Diaglog[Diaglogs].diagresult[7]=C2_Check();	
   	
   	
   	//7.�洢�Լ��ʱ��
   	
//   	DaysToDates(TODDAY,&Diaglog[Diaglogs].date[2],&Diaglog[Diaglogs].date[1],&Diaglog[Diaglogs].date[0]);
		timestruct=GetTime();
   	Diaglog[Diaglogs].date[0]=timestruct.year;
		Diaglog[Diaglogs].date[1]=timestruct.month;
		Diaglog[Diaglogs].date[2]=timestruct.day;
   	Diaglog[Diaglogs].time[0]=timestruct.minute;       //����ʱ���
	Diaglog[Diaglogs].time[1]=timestruct.hour;       	//����ʱ��Сʱ
	
   if((Diaglog[Diaglogs].diagresult[0]==1)||(Diaglog[Diaglogs].diagresult[1]==1)||(Diaglog[Diaglogs].diagresult[2]==1)||(Diaglog[Diaglogs].diagresult[3]==1)||(Diaglog[Diaglogs].diagresult[4]==1))
		iec_alarm_data|=0x10;
   if((Diaglog[Diaglogs].diagresult[5]==1)||(Diaglog[Diaglogs].diagresult[6]==1)||(Diaglog[Diaglogs].diagresult[7]==1))
   		iec_alarm_data|=0x08;
   
   if(temp)
   {
	    Eprom_Diaglog_Save(Diaglogs);		//�Լ�������Eprom
	   	
	   	if(Diaglogs>=8) Diaglogs=0;
	   	else Diaglogs++;
	   	
	   	Diaglogn++;
	   	if(Diaglogn>9) Diaglogn=9;			//���ֻ�ܴ洢9��
	   	
	   	Write_Char_Eprm(DIAGLOGN,Diaglogn);		//Diaglogn����Eprom
	   	Write_Char_Eprm(DIAGLOGS,Diaglogs);		//Diaglogs����Eprom  	
//	   	iec_send_alarm();
   }
   	iec_send_alarm();
 }
  







