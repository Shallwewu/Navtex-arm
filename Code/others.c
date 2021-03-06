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
//#define FPGARW(offset)   *((volatile word *)(0x002f8000+offset))   //自己加的关于FPGA读写

//volatile char Antennaing=0;	//辅助天线自检结果存储的变量，当开始自检置1，自检完成置0


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
/*功能：接收机状态初始化
入口参数：无
出口参数：无
/**********************************************************************/
void receiver_state_init(void);
void receiver_state_init(void)
{
	unsigned char a1[41]=" RECEIVER STATE                   MANUAL";//首字节忽略
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
/*功能：信息提示菜单显示
入口参数：unsigned char use,use=1,显示提示tip;use=0,清除显示tip
出口参数：无
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
/*功能：对2进行给定参数幂次运算
入口参数：所需2的幂次数
出口参数：返回计算结果
/**********************************************************************/
word Power(sword mici)
{
	word temp1,temp2;
	temp1=0x0001;
	temp2=temp1<<mici;
	return temp2;

}


//*********************************************************************/
/*功能：TOD模块的初始化
入口参数：无
出口参数：
/**********************************************************************/
void IntialSecInterrupt();		
void IntialSecInterrupt()
{
	NVIC_InitTypeDef NVIC_InitStructure;
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3,ENABLE);	
	TIM3->ARR = 10000;
	TIM3->PSC = 2000;        //分频数，值越小，时间越短
	TIM3->DIER |= 1<<0;
	TIM3->DIER |= 1<<6;
  NVIC_InitStructure.NVIC_IRQChannel =  TIM3_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 3;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
//	TIM3->CR1 |= 0x01;   //开定时器
//	TIM3->CR1&=0xfffe;   //关定时器  
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
  
  /* 配置P[A|B|C|D|E]5为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel =  EXTI1_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	/* EXTI line gpio config(PE5) */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;    
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   	
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	 // 上拉输入
  GPIO_Init(GPIOE, &GPIO_InitStructure);

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource1);
	
	/* EXTI line(PE5) mode config */	
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
  RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOE,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG,ENABLE);
  /* Configure one bit for preemption priority */
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
  
  /* 配置P[A|B|C|D|E]5为中断源 */
  NVIC_InitStructure.NVIC_IRQChannel =  EXTI0_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);

	/* EXTI line gpio config(PE5) */	
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;       
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN;   	
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;	 // 上拉输入
  GPIO_Init(GPIOE, &GPIO_InitStructure);

	/* EXTI line(PE5) mode config */
	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOE,EXTI_PinSource0);
	
	/* EXTI line(PE5) mode config */	
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}

//*********************************************************************/
/*功能；全局变量的初始化
入口参数：无
出口参数：
/**********************************************************************/
void Intial_GlobalData();
void Intial_GlobalData()
{
	
	
	char i,j;

	sword t=0,p=0;
	LANHELP=1;			//在中文界面下，若该值为0，则弹出菜单仍为英文界面设计的弹出子菜单
	G_Key=0;			//初始化按键为0，0表示无键按下
	FLAG=1;				//用于各个界面下的循环检测标志，若为0则跳出循环
	STATE=0;			//STATE为判定进入何界面的入口参数，初始化为0
	State1parameter=0;	//信息正文界面的入口参数，0表示正常进入，而非从存储或锁定界面进入
	subback=0;			//界面返回初始化为零		


	/***********************************/
	/*  信息存储菜单界面及子界面参数   */
	/***********************************/

	Selectsubback=0; 	//用于进入复选界面的界面参数保护
	Selectreturn=0;  	//用于复选界面的出口参数保护
	Mulnownumber=0; 	//作为复选界面的当前所在信息条数
	Returnback=0;  		//用于存储界面和锁定界面公用的入口参数保护
	Messagenumber=0; 	//用于存储界面和锁定界面中总信息数的记录
	Rankback=0; 		//用于排序公共界面的入口参数保护
	
	BUFFERPRINT=0;	  	//专用于打印确定界面MessageSubmenu的参数保护
	BUFFERSELECTLOCK=0; //专用于锁定复选界面参数的保护
	
	/*******************************/	
	/*  信息菜单界面及子界面参数   */
	/*******************************/
	/*MESSAGE*/
	Returntype=0; 	//表示是从何界面进入信息内容界面，10表示子界面进入
					//1返回到存储，2返回到锁定,
	PublicReturn=0; //用于公共界面的入口参数
	PitchDAPro=0;	//批处理界面入口参数保护
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
		BUFFER[i]=0;	//第一级菜单，每级菜单在跳出后必须清零，在跳入子菜单则无需改变
		BUFFER1[i]=0;	//第二级菜单
		BUFFER2[i]=0;	//第三级菜单
		BUFFER3[i]=0;	//第四级菜单
		BUFFER4[i]=0;	//第五级菜单	
		BUFFERPRO[i]=0;	//第一级菜单的保护用于信息存储界面和信息锁定届面到信息内容菜单切换时保?
	}

	
	/*******************************/	
	/*  MAINMEUN  */
	/*******************************/	

	PrtStart=(PrtLink *)malloc(sizeof(PrtLink));	//初始化打印队列的首指针
	receiver_state_init();	
			
//	PrtStart->next=NULL;
//	PrtStart->xulie=0;	//初始化打印信息数位0	
	for(i=0;i<22;i++) 	//专用于公用复选界面Savelocksubmenu的参数保护
	{
		BUFFERSELECT[i]=0;
	}
		
	for(i=0;i<3;i++)
	{
		for(j=0;j<26;j++)
		{
			Autotemp[i][j]=0;		//初始化临时自动模式的发射台全部选定		
			Manualtemp[i][j]=0;		//初始化临时手动模式的发射台全部选定
			MSGTYPETEMP[i][j]=0;	//初始化临时信息类别选择全部接收
		}
	}
	manual_area=11;
	flag_s=0;			//信息提示标志清0
	counter_flag_se=0;	//信息提示标志计数清0
	counter_flag_sc=0;	//信息提示标志计数清0
	flag_new_message=0;	//新信息收到标志清0
	auto_area=11;
	iec_alarm_data=0;
	flag_on=0;
	now_printing=0;
	Jiemamount=0;
	falsh_error=0;
}



//*********************************************************************/
/*功能；接收机配置信息恢复出厂设置加载
入口参数：无
出口参数：
/**********************************************************************/
void Intial_Original_Receiver();
void Intial_Original_Receiver()
{

	sword i,j;

	/*******************************/
	/*  主菜单界面及子界面参数   */
	/*******************************/
	for(i=0;i<3;i++)
	{
		for(j=0;j<26;j++)
		{
			Auto[i][j]=0;		//出厂设置自动模式的发射台全部选定		
			Manual[i][j]=0;		//出厂设置自动模式的发射台全部选定
			MSGTYPE[i][j]=0;	//出厂设置信息类别选择全部接收
			
		}
	}
	manual_area=11;//初始化11区
	Eprom_AutoMode_Save();
	Eprom_ManualMsgMode_Save(RXSTATION_MANUAL );
	Eprom_ManualMsgMode_Save(RX_MSGTYPE);

	/*本地时间*/                //用来分别表示本地时间的年月日时分

	number=0;          		//本地时间调整量
	sign=1;            		//调整量的正负号
	lcontrol=0;         	//用来记录本地时间是否开

	Write_Char_Eprm(RX_TIME,number);//number 信息写入Eprom
	Write_Char_Eprm(RX_TIME+1,sign);//sign 信息写入Eprom
	Write_Char_Eprm(RX_TIME+2,lcontrol);//sign 信息写入Eprom
	
	/*接收机设置*/              //分别用来表示接收机的一些设置
	for(i=0;i<5;i++)	//依次初始化误码显示开，数据输出手动，数据格式开，波特率38kbps,打印方向竖直
	{
		Receiverset[i]=0;
		Write_Char_Eprm(PRINTER_FORMAT+i,Receiverset[i]);	//写入Eprom
	}

	for(i=0;i<4;i++)	//初始化蜂鸣全关
	{
		Buzzer[i]=0;
	}
	Contrast=0;				//表示对比度的选择
	Diaglogs=0;				//用于记录但前可写日志在Diagresult[]中位置
	Diaglogn=0;				//用于记录日志的条数

	Eprom_Buzzer_Save();
	Write_Char_Eprm(RX_CONTRAST,Contrast);	//Controst 信息写入Eprom
 	Write_Char_Eprm(DIAGLOGN,Diaglogn);		//Diaglogn存入Eprom
   	Write_Char_Eprm(DIAGLOGS,Diaglogs);		//Diaglogs存入Eprom

	Operated=0;				//初始化为0，需要进行语言选择
   	Write_Char_Eprm(OPERATED,Operated);		//Operated存入Eprom	
	

	/* Rx station*/
	Mode=1;				//记录当前处在何种模式，0表示自动，1表示手动
	Workfre=1;			//记录当前的工作频率，0选择3种，1选择518/486，2选择518/4209.5
	Write_Char_Eprm(RX_MODE,Mode);			//保存Mode至Eprom
	Write_Char_Eprm(RX_WORKFRE,Workfre);			//保存Mode至Eprom
}

/*************************************************   
	功能：打印机初始化函数
	入口参数：无
	返回参数：无
 *************************************************/
void Intial_Printer();
void Intial_Printer()
{
	/* 打印机*/
	IntialRS232();
	Checkinfo.Printerror=0; //初始化打印机不出错
	Checkinfo.Printover=1;  //初始化打印机打印完

}

/*************************************************   
	功能：COP,看门狗初始化函数，必须在2.1S内喂狗
	      否则系统软件复位
	入口参数：无
	返回参数：无
 *************************************************/
//void Intial_COP();
//void Intial_COP()
//{
//	COPTO=0XFFFF;
//	COPCTL|=COPCTL_CEN_MASK;	//COP使能
//}


/*************************************************   
	功能：FPGA初始化函数
	入口参数：无
	返回参数：无
 *************************************************/
void Intial_FPGA();
void Intial_FPGA()
{
/*	GPIO_B_PER&=0xefff;//GPIOB12,FPGA_RESET设置为普通IO口
 	GPIO_B_DDR|=0X1000;//GPIOB12,FPGA_RESET设置为输出口
  	GPIO_B_DR&=0Xefff;//输出数据0，进行初始化
  	asm(nop);
    asm(nop);
  	asm(nop);
    asm(nop);
   	asm(nop);
    asm(nop);	
 	GPIO_B_DR|=0X1000;//初始化完毕，输出数据1	*/
}

//*********************************************************************/
/*功能；正常启动加载函数
入口参数：无
出口参数：无
/**********************************************************************/
void IntialNormal()
{	
	delay_init(72);
  FSMC_GPIO_Config();
  FSMC_Config();	
	Init_Fpga();				//FPGA初始�
	Fpga_reset();	
	IIC_Init();				//EEPROM初始化
	Intial_GlobalData();		//全局变量初始化
//	Intial_Original_Receiver();	
	Intial_Normal_Receiver();	//加载接收机配置信息
	Intial_Message();			//加载接收机存储信息
	
	pinoflcdinit();
	PWM_Init();	                 //PWM INIT

	W_DOT(0,0);
	IntialLCD(0);				//LCD初始化
		//RunLanguageChoose();
  sFLASH_Init();
	IntialIRQA();				//IRQA中断开启	
	IntialSecInterrupt();		//TOD时间模块初始化		
//	asm (bfclr #$0300,sr);		//开启总中断,所有中断级别有效
//	Workfre=0;
	FPGARW(3602)=Workfre;		//通道选择
  ADC1_Init();
//	if(Operated==0)				//出厂设置时需要进行中英文菜单选择
	RunLanguageChoose();	//完成中英文菜单选择
  rtcinit();
	RunBoot();					//BOOT自检运行
	
//@wu	IntialTIMER();				//定时器0初始化
//	IntialJietiaoDataTran();	//新添解调的定时器初始化设置   是否需注释掉???
	Intial_Printer();			//打印机初始化
	IntialRS232_iec();
//	StartRS232_iec();
//	IntialTOD();				//三天定时允许开启
//	iec_send_alarm();
	IntialIRQB();				//IRQB中断开启	
}



//*********************************************************************/
/*功能；恢复出厂设置加载函数
入口参数：无
出口参数：
/**********************************************************************/

void IntialOriginal();
void IntialOriginal()
{
//    IPR2&=0xfff0;  //关中断A、B
  DISABLEIRQB();
  DISABLEIRQA();
//	TODCS&=0xfff7;  //关秒中断
	TIM3->CR1&=0xfffe;
	Reset_Flash();
  Reset_Message();
	Intial_FPGA();
	
	IIC_Init();				//EEPROM初始化
	delay_init(72);
  FSMC_GPIO_Config();
  FSMC_Config();	
		
	Intial_GlobalData();	
	Intial_Original_Receiver();
	Intial_Message();
	

	W_DOT(0,0);
	IntialLCD(0);

	ENABLEIRQA();			//IRQA中断开启
//	asm (bfclr #$0300,sr);	//开启总中断,所有中断级别有效
	
	RunLanguageChoose();	//完成中英文菜单选择	
	
	RTC_TimeRegulate(15, 8, 8, 0, 0);
	RunBoot();

//	IntialTIMER();			//定时器0的初始化，用于信息处理
//	IntialJietiaoDataTran();//DSP向FPGA传递解调数据的中断函数，定时器2的初始化

	Intial_Printer();
//	IntialTOD();
	
 	ENABLEIRQB();			//IRQB中断开启

}







//                  RS232检测          //
char RS232_Check(void);
char RS232_Check(void)
{
	
}


//                  POWER检测          //
char Power_Check(void);
char Power_Check(void)
{
	char result=0;	//0表示正常，bit0对应通道4bit1对应通道5,bit2对应通道6,bit3对应通道7
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


//	volt[6]=TLCDA(0x0001);	//通道2--模拟板486的1.28V电源
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

//                  Antenna检测          //
char Antenna_Check(void);
char Antenna_Check(void)
{
	Antennaing=1;	//天线自检开始，置1
	Antenna=1;		//开启天线自检
}

//                  518检测          //
char C1_Check(void);
char C1_Check(void)
{
	char result=0;	//0表示正常，1表示518通道有误
	u16 volt;
	u16 V1_3=53;	//1.04V对应的数字量
	
	volt=53;  //Get_Adc();	//通道1--模拟板518的1.28V电源	

	if(V1_3-volt>50) result=1;	
	return result;
}

//                  490和4209.5检测          //
char C2_Check(void);
char C2_Check(void)
{
	char result=0;	//0表示正常，1表示2、3通道有误
	u16 volt;
	u16 V1_3=65;	//1.28V对应的数字量
	
	volt=65;  //Get_Adc();	//通道2、3--模拟板518的1.28V电源	

	if((V1_3-volt)>50) result=1;
	return result;
}


//                  RAM检测          //
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
 /*功能；写参数及显示数据函数
   入口参数：所需输出的字符*/
 /**************************/
 void Selfdiag(char temp);
 void Selfdiag(char temp)
 {
 	

 	//1.rom check
 	Diaglog[Diaglogs].diagresult[0]=CFI_Query();//检测FALSH是否有效
 	
 	//2.ram check,数据Ram，方法写十个数，读出来比较结果,若相等则为0，反之为1 	

 	RAM_Check();
 	//3.serial check,包括Eprom,RS232,返回值为1则Eprom出错，2则RS232出错，3则两者同时出错
 	
 	Diaglog[Diaglogs].diagresult[2]=Eprom_Check();
 	if(RS232_Check()) Diaglog[Diaglogs].diagresult[2]+=2;
 	//4.power检测
 	Diaglog[Diaglogs].diagresult[3]=Power_Check();
 	
 	//5.antenna检测
 	AntennaResult=C1_Check();
//  	Antenna_Check();
//  	AntennaCheck();
  //	while(Antennaing){};
  	Diaglog[Diaglogs].diagresult[4]=AntennaResult;
  	
  	//6.518,490,4209.5三个通道检测	
  	Diaglog[Diaglogs].diagresult[5]=C1_Check();
  	Diaglog[Diaglogs].diagresult[6]=C2_Check(); 		 
   	Diaglog[Diaglogs].diagresult[7]=C2_Check();	
   	
   	
   	//7.存储自检的时间
   	
//   	DaysToDates(TODDAY,&Diaglog[Diaglogs].date[2],&Diaglog[Diaglogs].date[1],&Diaglog[Diaglogs].date[0]);
		timestruct=GetTime();
   	Diaglog[Diaglogs].date[0]=timestruct.year;
		Diaglog[Diaglogs].date[1]=timestruct.month;
		Diaglog[Diaglogs].date[2]=timestruct.day;
   	Diaglog[Diaglogs].time[0]=timestruct.minute;       //国际时间分
	Diaglog[Diaglogs].time[1]=timestruct.hour;       	//国际时间小时
	
   if((Diaglog[Diaglogs].diagresult[0]==1)||(Diaglog[Diaglogs].diagresult[1]==1)||(Diaglog[Diaglogs].diagresult[2]==1)||(Diaglog[Diaglogs].diagresult[3]==1)||(Diaglog[Diaglogs].diagresult[4]==1))
		iec_alarm_data|=0x10;
   if((Diaglog[Diaglogs].diagresult[5]==1)||(Diaglog[Diaglogs].diagresult[6]==1)||(Diaglog[Diaglogs].diagresult[7]==1))
   		iec_alarm_data|=0x08;
   
   if(temp)
   {
	    Eprom_Diaglog_Save(Diaglogs);		//自检结果存入Eprom
	   	
	   	if(Diaglogs>=8) Diaglogs=0;
	   	else Diaglogs++;
	   	
	   	Diaglogn++;
	   	if(Diaglogn>9) Diaglogn=9;			//最多只能存储9条
	   	
	   	Write_Char_Eprm(DIAGLOGN,Diaglogn);		//Diaglogn存入Eprom
	   	Write_Char_Eprm(DIAGLOGS,Diaglogs);		//Diaglogs存入Eprom  	
//	   	iec_send_alarm();
   }
   	iec_send_alarm();
 }
  







