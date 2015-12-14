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
//#define FPGARW(offset)   *((volatile word *)(0x002f8000+offset))   //×Ô¼º¼ÓµÄ¹ØÓÚFPGA¶ÁĞ´

//volatile char Antennaing=0;	//¸¨ÖúÌìÏß×Ô¼ì½á¹û´æ´¢µÄ±äÁ¿£¬µ±¿ªÊ¼×Ô¼ìÖÃ1£¬×Ô¼ìÍê³ÉÖÃ0


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
/*¹¦ÄÜ£º½ÓÊÕ»ú×´Ì¬³õÊ¼»¯
Èë¿Ú²ÎÊı£ºÎŞ
³ö¿Ú²ÎÊı£ºÎŞ
/**********************************************************************/
void receiver_state_init(void);
void receiver_state_init(void)
{
	unsigned char a1[41]=" RECEIVER STATE                   MANUAL";//Ê××Ö½ÚºöÂÔ
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
/*¹¦ÄÜ£ºĞÅÏ¢ÌáÊ¾²Ëµ¥ÏÔÊ¾
Èë¿Ú²ÎÊı£ºunsigned char use,use=1,ÏÔÊ¾ÌáÊ¾tip;use=0,Çå³ıÏÔÊ¾tip
³ö¿Ú²ÎÊı£ºÎŞ
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
/*¹¦ÄÜ£º¶Ô2½øĞĞ¸ø¶¨²ÎÊıÃİ´ÎÔËËã
Èë¿Ú²ÎÊı£ºËùĞè2µÄÃİ´ÎÊı
³ö¿Ú²ÎÊı£º·µ»Ø¼ÆËã½á¹û
/**********************************************************************/
word Power(sword mici)
{
	word temp1,temp2;
	temp1=0x0001;
	temp2=temp1<<mici;
	return temp2;

}


//*********************************************************************/
/*¹¦ÄÜ£ºTODÄ£¿éµÄ³õÊ¼»¯
Èë¿Ú²ÎÊı£ºÎŞ
³ö¿Ú²ÎÊı£º
/**********************************************************************/
void IntialSecInterrupt();		
void IntialSecInterrupt()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	
	TIM3->ARR = 10000;
	TIM3->PSC = 2000;        //·ÖÆµÊı£¬ÖµÔ½Ğ¡£¬Ê±¼äÔ½¶Ì
	TIM3->DIER |= 1<<0;
	TIM3->DIER |= 1<<6;
  NVIC_InitStructure.NVIC_IRQChannel =  TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
//	TIM3->CR1 |= 0x01;   //¿ª¶¨Ê±Æ÷
//	TIM3->CR1&=0xfffe;   //¹Ø¶¨Ê±Æ÷  
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
  
  /* ÅäÖÃP[A|B|C|D|E]5ÎªÖĞ¶ÏÔ´ */
  NVIC_InitStructure.NVIC_IRQChannel =  EXTI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	/* EXTI line gpio config(PE5) */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;    
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   	
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	 // ÉÏÀ­ÊäÈë
  GPIO_Init(GPIOE, &GPIO_InitStructure);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource1);
	
	/* EXTI line(PE5) mode config */	
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //ÏÂ½µÑØÖĞ¶Ï
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
  
  /* ÅäÖÃP[A|B|C|D|E]5ÎªÖĞ¶ÏÔ´ */
  NVIC_InitStructure.NVIC_IRQChannel =  EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	/* EXTI line gpio config(PE5) */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   	
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	 // ÉÏÀ­ÊäÈë
  GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* EXTI line(PE5) mode config */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource0);
	
	/* EXTI line(PE5) mode config */	
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //ÏÂ½µÑØÖĞ¶Ï
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}

//*********************************************************************/
/*¹¦ÄÜ£»È«¾Ö±äÁ¿µÄ³õÊ¼»¯
Èë¿Ú²ÎÊı£ºÎŞ
³ö¿Ú²ÎÊı£º
/**********************************************************************/
void Intial_GlobalData();
void Intial_GlobalData()
{
	
	
	char i,j;

	sword t=0,p=0;
	LANHELP=1;			//ÔÚÖĞÎÄ½çÃæÏÂ£¬Èô¸ÃÖµÎª0£¬Ôòµ¯³ö²Ëµ¥ÈÔÎªÓ¢ÎÄ½çÃæÉè¼ÆµÄµ¯³ö×Ó²Ëµ¥
	G_Key=0;			//³õÊ¼»¯°´¼üÎª0£¬0±íÊ¾ÎŞ¼ü°´ÏÂ
	FLAG=1;				//ÓÃÓÚ¸÷¸ö½çÃæÏÂµÄÑ­»·¼ì²â±êÖ¾£¬ÈôÎª0ÔòÌø³öÑ­»·
	STATE=0;			//STATEÎªÅĞ¶¨½øÈëºÎ½çÃæµÄÈë¿Ú²ÎÊı£¬³õÊ¼»¯Îª0
	State1parameter=0;	//ĞÅÏ¢ÕıÎÄ½çÃæµÄÈë¿Ú²ÎÊı£¬0±íÊ¾Õı³£½øÈë£¬¶ø·Ç´Ó´æ´¢»òËø¶¨½çÃæ½øÈë
	subback=0;			//½çÃæ·µ»Ø³õÊ¼»¯ÎªÁã		


	/***********************************/
	/*  ĞÅÏ¢´æ´¢²Ëµ¥½çÃæ¼°×Ó½çÃæ²ÎÊı   */
	/***********************************/

	Selectsubback=0; 	//ÓÃÓÚ½øÈë¸´Ñ¡½çÃæµÄ½çÃæ²ÎÊı±£»¤
	Selectreturn=0;  	//ÓÃÓÚ¸´Ñ¡½çÃæµÄ³ö¿Ú²ÎÊı±£»¤
	Mulnownumber=0; 	//×÷Îª¸´Ñ¡½çÃæµÄµ±Ç°ËùÔÚĞÅÏ¢ÌõÊı
	Returnback=0;  		//ÓÃÓÚ´æ´¢½çÃæºÍËø¶¨½çÃæ¹«ÓÃµÄÈë¿Ú²ÎÊı±£»¤
	Messagenumber=0; 	//ÓÃÓÚ´æ´¢½çÃæºÍËø¶¨½çÃæÖĞ×ÜĞÅÏ¢ÊıµÄ¼ÇÂ¼
	Rankback=0; 		//ÓÃÓÚÅÅĞò¹«¹²½çÃæµÄÈë¿Ú²ÎÊı±£»¤
	
	BUFFERPRINT=0;	  	//×¨ÓÃÓÚ´òÓ¡È·¶¨½çÃæMessageSubmenuµÄ²ÎÊı±£»¤
	BUFFERSELECTLOCK=0; //×¨ÓÃÓÚËø¶¨¸´Ñ¡½çÃæ²ÎÊıµÄ±£»¤
	
	/*******************************/	
	/*  ĞÅÏ¢²Ëµ¥½çÃæ¼°×Ó½çÃæ²ÎÊı   */
	/*******************************/
	/*MESSAGE*/
	Returntype=0; 	//±íÊ¾ÊÇ´ÓºÎ½çÃæ½øÈëĞÅÏ¢ÄÚÈİ½çÃæ£¬10±íÊ¾×Ó½çÃæ½øÈë
					//1·µ»Øµ½´æ´¢£¬2·µ»Øµ½Ëø¶¨,
	PublicReturn=0; //ÓÃÓÚ¹«¹²½çÃæµÄÈë¿Ú²ÎÊı
	PitchDAPro=0;	//Åú´¦Àí½çÃæÈë¿Ú²ÎÊı±£»¤
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
		BUFFER[i]=0;	//µÚÒ»¼¶²Ëµ¥£¬Ã¿¼¶²Ëµ¥ÔÚÌø³öºó±ØĞëÇåÁã£¬ÔÚÌøÈë×Ó²Ëµ¥ÔòÎŞĞè¸Ä±ä
		BUFFER1[i]=0;	//µÚ¶ş¼¶²Ëµ¥
		BUFFER2[i]=0;	//µÚÈı¼¶²Ëµ¥
		BUFFER3[i]=0;	//µÚËÄ¼¶²Ëµ¥
		BUFFER4[i]=0;	//µÚÎå¼¶²Ëµ¥	
		BUFFERPRO[i]=0;	//µÚÒ»¼¶²Ëµ¥µÄ±£»¤ÓÃÓÚĞÅÏ¢´æ´¢½çÃæºÍĞÅÏ¢Ëø¶¨½ìÃæµ½ĞÅÏ¢ÄÚÈİ²Ëµ¥ÇĞ»»Ê±±£?
	}

	
	/*******************************/	
	/*  MAINMEUN  */
	/*******************************/	

	PrtStart=(PrtLink *)malloc(sizeof(PrtLink));	//³õÊ¼»¯´òÓ¡¶ÓÁĞµÄÊ×Ö¸Õë
	receiver_state_init();	
			
//	PrtStart->next=NULL;
//	PrtStart->xulie=0;	//³õÊ¼»¯´òÓ¡ĞÅÏ¢ÊıÎ»0	
	for(i=0;i<22;i++) 	//×¨ÓÃÓÚ¹«ÓÃ¸´Ñ¡½çÃæSavelocksubmenuµÄ²ÎÊı±£»¤
	{
		BUFFERSELECT[i]=0;
	}
		
	for(i=0;i<3;i++)
	{
		for(j=0;j<26;j++)
		{
			Autotemp[i][j]=0;		//³õÊ¼»¯ÁÙÊ±×Ô¶¯Ä£Ê½µÄ·¢ÉäÌ¨È«²¿Ñ¡¶¨		
			Manualtemp[i][j]=0;		//³õÊ¼»¯ÁÙÊ±ÊÖ¶¯Ä£Ê½µÄ·¢ÉäÌ¨È«²¿Ñ¡¶¨
			MSGTYPETEMP[i][j]=0;	//³õÊ¼»¯ÁÙÊ±ĞÅÏ¢Àà±ğÑ¡ÔñÈ«²¿½ÓÊÕ
		}
	}
	manual_area=11;
	flag_s=0;			//ĞÅÏ¢ÌáÊ¾±êÖ¾Çå0
	counter_flag_se=0;	//ĞÅÏ¢ÌáÊ¾±êÖ¾¼ÆÊıÇå0
	counter_flag_sc=0;	//ĞÅÏ¢ÌáÊ¾±êÖ¾¼ÆÊıÇå0
	flag_new_message=0;	//ĞÂĞÅÏ¢ÊÕµ½±êÖ¾Çå0
	auto_area=11;
	iec_alarm_data=0;
	flag_on=0;
	now_printing=0;
	Jiemamount=0;
	falsh_error=0;
}



//*********************************************************************/
/*¹¦ÄÜ£»½ÓÊÕ»úÅäÖÃĞÅÏ¢»Ö¸´³ö³§ÉèÖÃ¼ÓÔØ
Èë¿Ú²ÎÊı£ºÎŞ
³ö¿Ú²ÎÊı£º
/**********************************************************************/
void Intial_Original_Receiver();
void Intial_Original_Receiver()
{

	sword i,j;

	/*******************************/
	/*  Ö÷²Ëµ¥½çÃæ¼°×Ó½çÃæ²ÎÊı   */
	/*******************************/
	for(i=0;i<3;i++)
	{
		for(j=0;j<26;j++)
		{
			Auto[i][j]=0;		//³ö³§ÉèÖÃ×Ô¶¯Ä£Ê½µÄ·¢ÉäÌ¨È«²¿Ñ¡¶¨		
			Manual[i][j]=0;		//³ö³§ÉèÖÃ×Ô¶¯Ä£Ê½µÄ·¢ÉäÌ¨È«²¿Ñ¡¶¨
			MSGTYPE[i][j]=0;	//³ö³§ÉèÖÃĞÅÏ¢Àà±ğÑ¡ÔñÈ«²¿½ÓÊÕ
			
		}
	}
	manual_area=11;//³õÊ¼»¯11Çø
	Eprom_AutoMode_Save();
	Eprom_ManualMsgMode_Save(RXSTATION_MANUAL );
	Eprom_ManualMsgMode_Save(RX_MSGTYPE);

	/*±¾µØÊ±¼ä*/                //ÓÃÀ´·Ö±ğ±íÊ¾±¾µØÊ±¼äµÄÄêÔÂÈÕÊ±·Ö

	number=0;          		//±¾µØÊ±¼äµ÷ÕûÁ¿
	sign=1;            		//µ÷ÕûÁ¿µÄÕı¸ººÅ
	lcontrol=0;         	//ÓÃÀ´¼ÇÂ¼±¾µØÊ±¼äÊÇ·ñ¿ª

	Write_Char_Eprm(RX_TIME,number);//number ĞÅÏ¢Ğ´ÈëEprom
	Write_Char_Eprm(RX_TIME+1,sign);//sign ĞÅÏ¢Ğ´ÈëEprom
	Write_Char_Eprm(RX_TIME+2,lcontrol);//sign ĞÅÏ¢Ğ´ÈëEprom
	
	/*½ÓÊÕ»úÉèÖÃ*/              //·Ö±ğÓÃÀ´±íÊ¾½ÓÊÕ»úµÄÒ»Ğ©ÉèÖÃ
	for(i=0;i<5;i++)	//ÒÀ´Î³õÊ¼»¯ÎóÂëÏÔÊ¾¿ª£¬Êı¾İÊä³öÊÖ¶¯£¬Êı¾İ¸ñÊ½¿ª£¬²¨ÌØÂÊ38kbps,´òÓ¡·½ÏòÊúÖ±
	{
		Receiverset[i]=0;
		Write_Char_Eprm(PRINTER_FORMAT+i,Receiverset[i]);	//Ğ´ÈëEprom
	}

	for(i=0;i<4;i++)	//³õÊ¼»¯·äÃùÈ«¹Ø
	{
		Buzzer[i]=0;
	}
	Contrast=0;				//±íÊ¾¶Ô±È¶ÈµÄÑ¡Ôñ
	Diaglogs=0;				//ÓÃÓÚ¼ÇÂ¼µ«Ç°¿ÉĞ´ÈÕÖ¾ÔÚDiagresult[]ÖĞÎ»ÖÃ
	Diaglogn=0;				//ÓÃÓÚ¼ÇÂ¼ÈÕÖ¾µÄÌõÊı

	Eprom_Buzzer_Save();
	Write_Char_Eprm(RX_CONTRAST,Contrast);	//Controst ĞÅÏ¢Ğ´ÈëEprom
 	Write_Char_Eprm(DIAGLOGN,Diaglogn);		//Diaglogn´æÈëEprom
   	Write_Char_Eprm(DIAGLOGS,Diaglogs);		//Diaglogs´æÈëEprom

	Operated=0;				//³õÊ¼»¯Îª0£¬ĞèÒª½øĞĞÓïÑÔÑ¡Ôñ
   	Write_Char_Eprm(OPERATED,Operated);		//Operated´æÈëEprom	
	

	/* Rx station*/
	Mode=1;				//¼ÇÂ¼µ±Ç°´¦ÔÚºÎÖÖÄ£Ê½£¬0±íÊ¾×Ô¶¯£¬1±íÊ¾ÊÖ¶¯
	Workfre=1;			//¼ÇÂ¼µ±Ç°µÄ¹¤×÷ÆµÂÊ£¬0Ñ¡Ôñ3ÖÖ£¬1Ñ¡Ôñ518/486£¬2Ñ¡Ôñ518/4209.5
	Write_Char_Eprm(RX_MODE,Mode);			//±£´æModeÖÁEprom
	Write_Char_Eprm(RX_WORKFRE,Workfre);			//±£´æModeÖÁEprom
}

/*************************************************   
	¹¦ÄÜ£º´òÓ¡»ú³õÊ¼»¯º¯Êı
	Èë¿Ú²ÎÊı£ºÎŞ
	·µ»Ø²ÎÊı£ºÎŞ
 *************************************************/
void Intial_Printer();
void Intial_Printer()
{
	/* ´òÓ¡»ú*/
	IntialRS232();
	Checkinfo.Printerror=0; //³õÊ¼»¯´òÓ¡»ú²»³ö´í
	Checkinfo.Printover=1;  //³õÊ¼»¯´òÓ¡»ú´òÓ¡Íê

}

/*************************************************   
	¹¦ÄÜ£ºCOP,¿´ÃÅ¹·³õÊ¼»¯º¯Êı£¬±ØĞëÔÚ2.1SÄÚÎ¹¹·
	      ·ñÔòÏµÍ³Èí¼ş¸´Î»
	Èë¿Ú²ÎÊı£ºÎŞ
	·µ»Ø²ÎÊı£ºÎŞ
 *************************************************/
//void Intial_COP();
//void Intial_COP()
//{
//	COPTO=0XFFFF;
//	COPCTL|=COPCTL_CEN_MASK;	//COPÊ¹ÄÜ
//}


/*************************************************   
	¹¦ÄÜ£ºFPGA³õÊ¼»¯º¯Êı
	Èë¿Ú²ÎÊı£ºÎŞ
	·µ»Ø²ÎÊı£ºÎŞ
 *************************************************/
void Intial_FPGA();
void Intial_FPGA()
{
/*	GPIO_B_PER&=0xefff;//GPIOB12,FPGA_RESETÉèÖÃÎªÆÕÍ¨IO¿Ú
 	GPIO_B_DDR|=0X1000;//GPIOB12,FPGA_RESETÉèÖÃÎªÊä³ö¿Ú
  	GPIO_B_DR&=0Xefff;//Êä³öÊı¾İ0£¬½øĞĞ³õÊ¼»¯
  	asm(nop);
    asm(nop);
  	asm(nop);
    asm(nop);
   	asm(nop);
    asm(nop);	
 	GPIO_B_DR|=0X1000;//³õÊ¼»¯Íê±Ï£¬Êä³öÊı¾İ1	*/
}

//*********************************************************************/
/*¹¦ÄÜ£»Õı³£Æô¶¯¼ÓÔØº¯Êı
Èë¿Ú²ÎÊı£ºÎŞ
³ö¿Ú²ÎÊı£ºÎŞ
/**********************************************************************/
void IntialNormal()
{	
	delay_init(72);
  FSMC_GPIO_Config();
  FSMC_Config();	
	Init_Fpga();				//FPGA³õÊ¼»
	Fpga_reset();	
	IIC_Init();				//EEPROM³õÊ¼»¯
	Intial_GlobalData();		//È«¾Ö±äÁ¿³õÊ¼»¯
//	Intial_Original_Receiver();	
	Intial_Normal_Receiver();	//¼ÓÔØ½ÓÊÕ»úÅäÖÃĞÅÏ¢
	Intial_Message();			//¼ÓÔØ½ÓÊÕ»ú´æ´¢ĞÅÏ¢
	
	pinoflcdinit();
	PWM_Init();	                 //PWM INIT

	W_DOT(0,0);
	IntialLCD(0);				//LCD³õÊ¼»¯
		//RunLanguageChoose();
  sFLASH_Init();
	IntialIRQA();				//IRQAÖĞ¶Ï¿ªÆô	
	IntialSecInterrupt();		//TODÊ±¼äÄ£¿é³õÊ¼»¯		
//	asm (bfclr #$0300,sr);		//¿ªÆô×ÜÖĞ¶Ï,ËùÓĞÖĞ¶Ï¼¶±ğÓĞĞ§
//	Workfre=0;
	FPGARW(3602)=Workfre;		//Í¨µÀÑ¡Ôñ
  ADC1_Init();
//	if(Operated==0)				//³ö³§ÉèÖÃÊ±ĞèÒª½øĞĞÖĞÓ¢ÎÄ²Ëµ¥Ñ¡Ôñ
	RunLanguageChoose();	//Íê³ÉÖĞÓ¢ÎÄ²Ëµ¥Ñ¡Ôñ
	RunBoot();					//BOOT×Ô¼ìÔËĞĞ
	
//@wu	IntialTIMER();				//¶¨Ê±Æ÷0³õÊ¼»¯
//	IntialJietiaoDataTran();	//ĞÂÌí½âµ÷µÄ¶¨Ê±Æ÷³õÊ¼»¯ÉèÖÃ   ÊÇ·ñĞè×¢ÊÍµô???
	Intial_Printer();			//´òÓ¡»ú³õÊ¼»¯
	IntialRS232_iec();
//	StartRS232_iec();
//	IntialTOD();				//ÈıÌì¶¨Ê±ÔÊĞí¿ªÆô
//	iec_send_alarm();
	IntialIRQB();				//IRQBÖĞ¶Ï¿ªÆô	
}



//*********************************************************************/
/*¹¦ÄÜ£»»Ö¸´³ö³§ÉèÖÃ¼ÓÔØº¯Êı
Èë¿Ú²ÎÊı£ºÎŞ
³ö¿Ú²ÎÊı£º
/**********************************************************************/

void IntialOriginal();
void IntialOriginal()
{
//    IPR2&=0xfff0;  //¹ØÖĞ¶ÏA¡¢B
  DISABLEIRQB();
  DISABLEIRQA();
//	TODCS&=0xfff7;  //¹ØÃëÖĞ¶Ï
	TIM3->CR1&=0xfffe;
	Reset_Flash();
  Reset_Message();
	Intial_FPGA();
	
	IIC_Init();				//EEPROM³õÊ¼»¯
	delay_init(72);
  FSMC_GPIO_Config();
  FSMC_Config();	
		
	Intial_GlobalData();	
	Intial_Original_Receiver();
	Intial_Message();
	

	W_DOT(0,0);
	IntialLCD(0);

	ENABLEIRQA();			//IRQAÖĞ¶Ï¿ªÆô
//	asm (bfclr #$0300,sr);	//¿ªÆô×ÜÖĞ¶Ï,ËùÓĞÖĞ¶Ï¼¶±ğÓĞĞ§
	
	RunLanguageChoose();	//Íê³ÉÖĞÓ¢ÎÄ²Ëµ¥Ñ¡Ôñ	
	RunBoot();

//	IntialTIMER();			//¶¨Ê±Æ÷0µÄ³õÊ¼»¯£¬ÓÃÓÚĞÅÏ¢´¦Àí
//	IntialJietiaoDataTran();//DSPÏòFPGA´«µİ½âµ÷Êı¾İµÄÖĞ¶Ïº¯Êı£¬¶¨Ê±Æ÷2µÄ³õÊ¼»¯

	Intial_Printer();
//	IntialTOD();
	
 	ENABLEIRQB();			//IRQBÖĞ¶Ï¿ªÆô

}







//                  RS232¼ì²â          //
char RS232_Check(void);
char RS232_Check(void)
{
	
}


//                  POWER¼ì²â          //
char Power_Check(void);
char Power_Check(void)
{
	char result=0;	//0±íÊ¾Õı³££¬bit0¶ÔÓ¦Í¨µÀ4£bbit1¶ÔÓ¦Í¨µÀ5,bit2¶ÔÓ¦Í¨µÀ6,bit3¶ÔÓ¦Í¨µÀ7
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


//	volt[6]=TLCDA(0x0001);	//Í¨µÀ2--Ä£Äâ°å486µÄ1.28VµçÔ´
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

//                  Antenna¼ì²â          //
char Antenna_Check(void);
char Antenna_Check(void)
{
	Antennaing=1;	//ÌìÏß×Ô¼ì¿ªÊ¼£¬ÖÃ1
	Antenna=1;		//¿ªÆôÌìÏß×Ô¼ì
}

//                  518¼ì²â          //
char C1_Check(void);
char C1_Check(void)
{
	char result=0;	//0±íÊ¾Õı³££¬1±íÊ¾518Í¨µÀÓĞÎó
	u16 volt;
	u16 V1_3=53;	//1.04V¶ÔÓ¦µÄÊı×ÖÁ¿
	
	volt=53;  //Get_Adc();	//Í¨µÀ1--Ä£Äâ°å518µÄ1.28VµçÔ´	

	if(V1_3-volt>50) result=1;	
	return result;
}

//                  490ºÍ4209.5¼ì²â          //
char C2_Check(void);
char C2_Check(void)
{
	char result=0;	//0±íÊ¾Õı³££¬1±íÊ¾2¡¢3Í¨µÀÓĞÎó
	u16 volt;
	u16 V1_3=65;	//1.28V¶ÔÓ¦µÄÊı×ÖÁ¿
	
	volt=65;  //Get_Adc();	//Í¨µÀ2¡¢3--Ä£Äâ°å518µÄ1.28VµçÔ´	

	if((V1_3-volt)>50) result=1;
	return result;
}


//                  RAM¼ì²â          //
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
 /*¹¦ÄÜ£»Ğ´²ÎÊı¼°ÏÔÊ¾Êı¾İº¯Êı
   Èë¿Ú²ÎÊı£ºËùĞèÊä³öµÄ×Ö·û*/
 /**************************/
 void Selfdiag(char temp);
 void Selfdiag(char temp)
 {
 	

 	//1.rom check
 	Diaglog[Diaglogs].diagresult[0]=CFI_Query();//¼ì²âFALSHÊÇ·ñÓĞĞ§
 	
 	//2.ram check,Êı¾İRam£¬·½·¨Ğ´Ê®¸öÊı£¬¶Á³öÀ´±È½Ï½á¹û,ÈôÏàµÈÔòÎª0£¬·´Ö®Îª1 	

 	RAM_Check();
 	//3.serial check,°üÀ¨Eprom,RS232,·µ»ØÖµÎª1ÔòEprom³ö´í£¬2ÔòRS232³ö´í£¬3ÔòÁ½ÕßÍ¬Ê±³ö´í
 	
 	Diaglog[Diaglogs].diagresult[2]=Eprom_Check();
 	if(RS232_Check()) Diaglog[Diaglogs].diagresult[2]+=2;
 	//4.power¼ì²â
 	Diaglog[Diaglogs].diagresult[3]=Power_Check();
 	
 	//5.antenna¼ì²â
 	AntennaResult=C1_Check();
//  	Antenna_Check();
//  	AntennaCheck();
  //	while(Antennaing){};
  	Diaglog[Diaglogs].diagresult[4]=AntennaResult;
  	
  	//6.518,490,4209.5Èı¸öÍ¨µÀ¼ì²â	
  	Diaglog[Diaglogs].diagresult[5]=C1_Check();
  	Diaglog[Diaglogs].diagresult[6]=C2_Check(); 		 
   	Diaglog[Diaglogs].diagresult[7]=C2_Check();	
   	
   	
   	//7.´æ´¢×Ô¼ìµÄÊ±¼ä
   	
//   	DaysToDates(TODDAY,&Diaglog[Diaglogs].date[2],&Diaglog[Diaglogs].date[1],&Diaglog[Diaglogs].date[0]);
		timestruct=GetTime();
   	Diaglog[Diaglogs].date[0]=timestruct.year;
		Diaglog[Diaglogs].date[1]=timestruct.month;
		Diaglog[Diaglogs].date[2]=timestruct.day;
   	Diaglog[Diaglogs].time[0]=timestruct.minute;       //¹ú¼ÊÊ±¼ä·Ö
	Diaglog[Diaglogs].time[1]=timestruct.hour;       	//¹ú¼ÊÊ±¼äĞ¡Ê±
	
   if((Diaglog[Diaglogs].diagresult[0]==1)||(Diaglog[Diaglogs].diagresult[1]==1)||(Diaglog[Diaglogs].diagresult[2]==1)||(Diaglog[Diaglogs].diagresult[3]==1)||(Diaglog[Diaglogs].diagresult[4]==1))
		iec_alarm_data|=0x10;
   if((Diaglog[Diaglogs].diagresult[5]==1)||(Diaglog[Diaglogs].diagresult[6]==1)||(Diaglog[Diaglogs].diagresult[7]==1))
   		iec_alarm_data|=0x08;
   
   if(temp)
   {
	    Eprom_Diaglog_Save(Diaglogs);		//×Ô¼ì½á¹û´æÈëEprom
	   	
	   	if(Diaglogs>=8) Diaglogs=0;
	   	else Diaglogs++;
	   	
	   	Diaglogn++;
	   	if(Diaglogn>9) Diaglogn=9;			//×î¶àÖ»ÄÜ´æ´¢9Ìõ
	   	
	   	Write_Char_Eprm(DIAGLOGN,Diaglogn);		//Diaglogn´æÈëEprom
	   	Write_Char_Eprm(DIAGLOGS,Diaglogs);		//Diaglogs´æÈëEprom  	
//	   	iec_send_alarm();
   }
   	iec_send_alarm();
 }
  







