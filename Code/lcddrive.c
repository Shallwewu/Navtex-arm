#include <math.h>
#include "define.h"
#include <string.h>
#include "run.h"
#include "flash.h"
#include "Eprom.h"
#include "code.h"
#include "stm32f2xx.h"
#include "stm32f2xx_gpio.h"
#include "lcddrive.h"

//#include "timedelay.h"
//#include "define.h"
//#include "run.h"
//#include "flash.h"
//#include "Eprom.h"

#define DELAYTIME 10
//#define FPGARW(offset)   *((volatile word *)(0x002f8000+offset))   //自己加的关于FPGA读写

/*-------------------320240的SYSTEM SET 参数-------------------------------*/
//volatile byte SYSTAB[8]={0x30,0x87,0x07,0x28,0x42,0xf0,0x29,0x00};
//volatile byte SCRTAB[10]={0x00,0x00,0xf0,0xce,0x04,0xf0,0x80,0x00,0x00,0x00};
//volatile byte CTAB[40];
void pinoflcdinit(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); 
   
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	      //复用功能
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
}
/*************************************/
  /*功能；向LCD写指令代码
入口参数：char型，向LCD写入的字符
出口参数：无
/*************************************/
 void WriteCode(char code);
 void WriteCode(char code)
 {
 //	int uu;
 	/*1.数据的输出*/
 	GPIOC->MODER &= 0xffff0000;
 	GPIOC->MODER |= 0x00005555;					//DB7~DB0的8个管脚设置为输出口
 	GPIOC->ODR = (0x000000ff & (int)code);        //输出数据   @int =4byte
	
 	/*2.A0_LCD拉高*/
 	GPIOA->MODER &= 0xfff3ffff;  	//A0_LCD管脚设置为输出口
 	GPIOA->MODER |= 0x00040000;
 	GPIOA->ODR |= GPIO_ODR_ODR_9; 		//A0_LCD管脚输出高电平
 	 	
 	/*3./CS_LCD的片选拉低*/
 	GPIOA->MODER &= 0xfcffffff;  	// /CS_LCD管脚设置为输出口
 	GPIOA->MODER |= 0x01000000; 
	GPIOA->ODR &= ~GPIO_ODR_ODR_12; 		// /CS_LCD管脚输出低电平

 	/*4./WR_LCD拉低*/
  GPIOA->MODER &= 0xffcfffff;  	// /WR_LCD管脚设置为输出口
 	GPIOA->MODER |= 0x00100000;
	GPIOA->ODR &= ~GPIO_ODR_ODR_10;		// /WR_LCD管脚输出低电平

 	/*5.200ns时间的等待*/
  __nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();

	
  	/*6./WR_LCD拉高*/
 	GPIOA->ODR |= GPIO_ODR_ODR_10|GPIO_ODR_ODR_12;		// /WR_LCD管脚输出高电平
 	
  	/*7./CS_LCD的片选拉高*/
 	//GPIOA->ODR |= GPIO_ODR_ODR_12;		// /CS_LCD管脚输出高电平
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
 }


/******************************************/
  /*功能；向LCD写参数及显示数据
入口参数：char型，向LCD写入的参数及显示数据
出口参数：无
/******************************************/ 
void WriteData(char data);
void WriteData(char data)
 {
 //	int uu;
 	/*1.数据的输出*/
 	GPIOC->MODER &= 0xffff0000;
 	GPIOC->MODER |= 0x00005555;					//DB7~DB0的8个管脚设置为输出口
 	GPIOC->ODR = (0x000000ff & (int)data);        //输出数据   @int =4byte
	
 	/*2.A0_LCD拉低*/
 	GPIOA->MODER &= 0xfff3ffff;  	//A0_LCD管脚设置为输出口
 	GPIOA->MODER |= 0x00040000;
 	GPIOA->ODR &= ~GPIO_ODR_ODR_9; 		//A0_LCD管脚输出低电平
 	 	
 	/*3./CS_LCD的片选拉低*/
 	GPIOA->MODER &= 0xfcffffff;  	// /CS_LCD管脚设置为输出口
 	GPIOA->MODER |= 0x01000000; 
	GPIOA->ODR &= ~GPIO_ODR_ODR_12; 		// /CS_LCD管脚输出低电平

 	/*4./WR_LCD拉低*/
  GPIOA->MODER &= 0xffcfffff;  	// /WR_LCD管脚设置为输出口
 	GPIOA->MODER |= 0x00100000;
	GPIOA->ODR &= ~GPIO_ODR_ODR_10;		// /WR_LCD管脚输出低电平

 	/*5.200ns时间的等待*/
  __nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();


	
  	/*6./WR_LCD拉高*/
 	GPIOA->ODR |= GPIO_ODR_ODR_10;		// /WR_LCD管脚输出高电平
 	
  	/*7./CS_LCD的片选拉高*/
 	GPIOA->ODR |= GPIO_ODR_ODR_12;		// /CS_LCD管脚输出高电平
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
 }
 

/******************************************/
  /*功能；从LCD读参数及显示数据子程序
入口参数：无
出口参数：char型，从LCD读取的参数或显示数据
/******************************************/ 
char ReadData();
char ReadData()
 {
 	char data;         //,uu;

 	/*0.数据输入*/                          //@2014-04-22
 	GPIOC->MODER &= 0xffff0000;				//DB7~DB0的8个管脚设置为输入口
 	
 	/*2.A0_LCD拉高*/
 	GPIOA->MODER &= 0xfff3ffff;  	//A0_LCD管脚设置为输出口
 	GPIOA->MODER |= 0x00040000;
 	GPIOA->ODR |= GPIO_ODR_ODR_9; 		//A0_LCD管脚输出高电平
 	 	
 	/*3./CS_LCD的片选拉低*/
 	GPIOA->MODER &= 0xfcffffff;  	// /CS_LCD管脚设置为输出口
 	GPIOA->MODER |= 0x01000000; 
	GPIOA->ODR &= ~GPIO_ODR_ODR_12; 		// /CS_LCD管脚输出低电平

 	/*3./RD_LCD拉低*/
  GPIOA->MODER &= 0xff3fffff;  	// /RD_LCD管脚设置为输出口
 	GPIOA->MODER |= 0x00400000;
	GPIOA->ODR &= ~GPIO_ODR_ODR_11;		// /RD_LCD管脚输出低电平
 
 	/*5.200ns时间的等待*/
  __nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();

	
 	/*5.数据的读入*/
 	data = (char)(0x000000ff&(GPIOC->IDR));                   //读入数据
 	 	
  	/*6./RD_LCD拉高*/
 	GPIOA->ODR |= GPIO_ODR_ODR_11;		// /RD_LCD管脚输出高电平
 	
  	/*7./CS_LCD的片选拉高*/
 	GPIOA->ODR |= GPIO_ODR_ODR_12;		// /CS_LCD管脚输出高电平
 	
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
 	
 	return data;	
 }


/******************************************************************/
  /*功能；向LCD输出单个汉字
入口参数：char型 O_X:输入范围0~19， LCD整行可输出20个汉字
		  byte型 O_Y:输入范围0~239，LCD有240行(点阵的行数)
		  word型 code1:汉字的机内码或汉字的具体位置
		  char型 neima:1表示code1为机内码，0表示code1为字库具体位置	
出口参数：无
/******************************************************************/ 
void CCW_PR1(char O_X,byte O_Y,word code1,char neima);
void CCW_PR1(char O_X,byte O_Y,word code1,char neima)
{
	unsigned char count1;
	word i,j;
	Read_Chinese_Code(code1,neima);	//从字库读取汉字的点阵
	i = PARA;	
	j = i*O_Y+O_X+0x04ce;   		//显示一区所控制的显示屏行数 如为320240屏k=j*O_Y+O_X+0x04ce
	WriteCode(0x4f);   				//CSRDIR代码(下移)  
	
	for(i=0;i<2;i++)
	{
		WriteCode(0x46);      		//CSRW 代码
		WriteData(j%256);     		//设置光标地址CSR
		WriteData(j/256);
		WriteCode(0x42);    		//MWRITE 代码 
		
		for(count1=0;count1<16;count1++)
		{
			WriteData(CGTAB[i][count1]); //写入数据 
		}
		j=j+1;
	}
}                               

/***********************************************************************/
  /*功能；可向LCD输出0~40个字符，用以取代下面的输出40，16，8固定字符函数
入口参数：char型 O_X:输入范围0~39， LCD整行可输出40个字符
		  char型 O_Y:输入范围0~239，LCD有240行(点阵的行数)
		  char型 geshu
出口参数：无
/***********************************************************************/ 
void CW_PR(unsigned char O_X,unsigned char O_Y,unsigned char geshu);
void CW_PR(unsigned char O_X,unsigned char O_Y,unsigned char geshu)
{
	unsigned char i;
	word j;
	i=PARA;
	j=i*O_Y+O_X;
	WriteCode(0x46);   			//CSRW 代码 
	WriteData(j%256);  			//设置光标地址CSR 
	WriteData(j/256);
	WriteCode(0x4c);   			//CSRDIR 代码 
	WriteCode(0x42);   			//MWRITE 代码 
	for(i=0;i<geshu;i++)
	{
	
		WriteData(CTAB[i]);  	//写入数据 
	}
	for(i=0;i<geshu;i++)		//每次输出数据清零
	{
		CTAB[i]=0x20;  
	}
 
}	    

/******************************************************************/
  /*功能；向LCD输出一行40个字符
入口参数：char型 O_X:输入范围0~39， LCD整行可输出40个字符
		  char型 O_Y:输入范围0~29,  LCD有240行(点阵的行数)
出口参数：无
/******************************************************************/ 
/*void CW_PR1(unsigned char O_X,unsigned char O_Y);
void CW_PR1(unsigned char O_X,unsigned char O_Y)
{
	unsigned char i;
	unsigned int j;
	i=PARA;
	j=i*O_Y+O_X;
	WriteCode(0x46);   			//CSRW 代码 
	WriteData(j%256);  			//设置光标地址CSR 
	WriteData(j/256);
	WriteCode(0x4c);   			//CSRDIR 代码 
	WriteCode(0x42);   			//MWRITE 代码 
	for(i=0;i<40;i++)
	{
		WriteData(CTAB1[i]);  	//写入数据 
	}
	for(i=0;i<40;i++)			//每次输出数据清零
	{
		CTAB1[i]=0x20;  
	}
 
}
    
/******************************************************************/
  /*功能；向LCD输出一行16个字符
入口参数：char型 O_X:输入范围0~39， LCD整行可输出40个字符
		  char型 O_Y:输入范围0~29，LCD有240行(点阵的行数)
出口参数：无
/******************************************************************/ 
/*void CW_PR2(unsigned char O_X,unsigned char O_Y);
void CW_PR2(unsigned char O_X,unsigned char O_Y)
{
	unsigned char i;
	unsigned int j;
	i=PARA;
	j=i*O_Y+O_X;
	WriteCode(0x46);  			//CSRW 代码
	WriteData(j%256);  			//设置光标地址CSR 
	WriteData(j/256);
	WriteCode(0x4c);   			//CSRDIR 代码 
	WriteCode(0x42);   			//MWRITE 代码 
	for(i=0;i<16;i++)
	{
		WriteData(CTAB2[i]);  	//写入数据 
	}

	for(i=0;i<16;i++)			//每次输出完毕数据清零 
	{
		CTAB2[i]=0x20; 
	}
}
    
     
/******************************************************************/
  /*功能；向LCD输出一个字符
入口参数：char型 O_X:输入范围0~39， LCD整行可输出40个字符
		  char型 O_Y:输入范围0~29， LCD有240行(点阵的行数)
		  char型 CTAB:需显示的字符
出口参数：无
/******************************************************************/ 
void CW_PR3(unsigned char O_X,unsigned char O_Y,unsigned char character);
void CW_PR3(unsigned char O_X,unsigned char O_Y,unsigned char character)
{
	unsigned char i;
	word j;
	i=PARA;
	j=i*O_Y+O_X;
	WriteCode(0x46);   /* CSRW 代码 */
	WriteData(j%256);  /* 设置光标地址CSR */
	WriteData(j/256);

	WriteCode(0x4c);        /* CSRDIR 代码 */
	WriteCode(0x42);        /* MWRITE 代码 */ 
	WriteData(character);   /* 写入数据 */

}
    
/******************************************************************/
  /*功能；向LCD输出一行8个字符
入口参数：char型 O_X:输入范围0~39， LCD整行可输出40个字符
		  char型 O_Y:输入范围0~29，LCD有240行(点阵的行数)
出口参数：无
/******************************************************************/ 
/*void CW_PR4(unsigned char O_X,unsigned char O_Y);
void CW_PR4(unsigned char O_X,unsigned char O_Y)
{
	unsigned char i;
	unsigned int j;
	i=PARA;
	j=i*O_Y+O_X;
	WriteCode(0x46);   			// CSRW 代码 
	WriteData(j%256);  			// 设置光标地址CSR 
	WriteData(j/256);
	WriteCode(0x4c);   			// CSRDIR 代码 
	WriteCode(0x42);   			// MWRITE 代码 
	for(i=0;i<8;i++)
	{
		WriteData(CTAB[i]);  	// 写入数据 
	}
	for(i=0;i<8;i++)
	{
		CTAB[i]=0x20;  		// 每次输出数据清零 
	}     
}   
   
    

/********************************************/
  /*功能；向LCD指定位置绘一个点
入口参数：int型 O_X:输入范围0~319， 
		  int型 O_Y:输入范围0~239，
出口参数：无
/********************************************/ 
void W_DOT(sword O_X,sword O_Y)
{
	unsigned char i,j,dat;
	word k;         //,uu;
	char temp;
	j = PARA;
	i = O_X % 8;
	O_X = O_X / 8;
	k = j*O_Y+O_X+0x04ce;   /*写入位地址的表达式*/
	i = 7-i;
	O_Y = 0x01<<i;			/* 计算显示位 */                          
	WriteCode(0x4f);
	WriteCode(0x46);  		/* 设置光标地址 */
	WriteData(k%256); 		/* 计算光标地址 */
	WriteData(k/256);
	WriteCode(0x43);  		/* MREAD 代码 */
	dat=ReadData();   		/* 读取当前显示数据 */
	WriteCode(0x46);  		/* 设置光标地址 */
	WriteData(k%256);  		/* 计算光标地址 */
	WriteData(k/256);
	WriteCode(0x42);  		/* MWRITE 代码 */
	temp=(char)(dat|O_Y);
	WriteData(temp);  		/* 写入合成数据 */
}
  
/********************************************/
  /*功能；向LCD指定位置清一个点
入口参数：int型 O_X:输入范围0~319， 
		  int型 O_Y:输入范围0~239，
出口参数：无
/********************************************/ 
void W_CLEARDOT(sword O_X,sword O_Y)
{
	unsigned char i,j,dat;
	word k;
	char temp;
	j=PARA;
	i=O_X%8;
	O_X=O_X/8;
	k=j*O_Y+O_X+0x04ce;   	/*写入位地址的表达式*/
	                    
	WriteCode(0x4f);
	WriteCode(0x46);  		/* 设置光标地址 */
	WriteData(k%256); 		/* 计算光标地址 */
	WriteData(k/256);
	i=7-i;
	O_Y=0x01<<i;
	O_Y=~O_Y;				/* 计算显示位 */
	WriteCode(0x43);  		/* MREAD 代码 */
	dat=ReadData();   		/* 读取当前显示数据 */
	WriteCode(0x46);  		/* 设置光标地址 */
	WriteData(k%256);  		/* 计算光标地址 */
	WriteData(k/256);
	WriteCode(0x42);  		/* MWRITE 代码 */
	temp=(char)(dat&O_Y);
	WriteData(temp);        //(dat&O_Y); 2014-04-23 	/* 写入合成数据 */
}


/********************************************/
  /*功能；清全屏程序函数
入口参数：无
出口参数：无
/********************************************/ 
void CLEAR();
void CLEAR()
{
	word i,j;
	WriteCode(0x4c);   		/* CSRDIR 代码 */
	WriteCode(0x46);   		/* CSRW 代码 */
	WriteData(0x00);   		/* 设置参数光标指针低8位 */
	WriteData(0x00);   		/* 设置参数光标指针高8位 */
	WriteCode(0x42);   		/* MWRITE 代码 */
	for(j=6;j<2195;j++)     /*清64K的显示存储器*/
	{
		for(i=0;i<41;i++)   /*写入一行*/
		{
			WriteData(0x00);/* 写入数据 */
		}
	}
}



 
/********************************************/
  /*功能；清一区和二区程序函数
入口参数：无
出口参数：无
/********************************************/ 
void CLEAR1();
void CLEAR1()
{
	word i,j;
	W_DOT(0,0);
	if(STATE==1) IntialLCD(1);
	else IntialLCD(0);				//LCD初始化
	WriteCode(0x4c);   				/* CSRDIR 代码 */
	WriteCode(0x46);   				/* CSRW 代码 */
	WriteData(0x00);   				/* 设置参数光标指针低8位 */
	WriteData(0x00);   				/* 设置参数光标指针高8位 */
	WriteCode(0x42);   				/* MWRITE 代码 */
	for(j=0;j<270;j++)       		/*清显示区一和二的存储器*/
	{

		for(i=0;i<41;i++)     		/*写入一行*/
		{
			if(j==30||j==31||j==32||j==(LANGUAGE?52:47)||j==34||j==35||j==33||j==269||j==260) WriteData(0xff);
			else WriteData(0x00); 	/* 写入数据,中英文的区别在于中文显示第17行，英文显示22行 */
		}
	}
}


/********************************************/
  /*功能；画横线函数(点阵方法)
入口参数：O_XS:横轴起始点(0,319)
		  O_XE:横轴终止点(O_XS,319)
		  O_Y: Y轴位置(0,239) 
出口参数：无
/********************************************/ 
void W_XLINE(sword O_XS,sword O_XE,sword O_Y)
{
	sword j;
	for(j=O_XS;j<O_XE+1;j++)    /* 画一条直线，横坐标是O_X ，纵坐标是O_Y */
	{
		W_DOT(j,O_Y);          	/* 调绘点子程序  */
		if(j>319)break;         /* 如果横坐标大于屏的列宽320，则停止*/
	}
}

/********************************************/
  /*功能；取消横线函数 (点阵方法)
入口参数：O_XS:横轴起始点(0,319)
		  O_XE:横轴终止点(O_XS,319)
		  O_Y: Y轴位置(0,239) 
出口参数：无
/********************************************/ 
void W_CLEARXLINE(sword O_XS,sword O_XE,sword O_Y)
{
	sword j;
	for(j=O_XS;j<O_XE+1;j++)        /* 画一条直线，横坐标是O_X ，纵坐标是O_Y */
	{
		W_CLEARDOT(j,O_Y);          /* 调绘点子程序  */
		if(j>319)break;          	/* 如果横坐标大于屏的列宽320，则停止*/
	}
}

/********************************************/
  /*功能；画纵线函数(点阵方法)
入口参数：O_X: X轴的位置(0,319)
		  O_YS:纵轴起始点(0,239)
		  O_YE:纵轴终止点(O_YS,239) 
出口参数：无
/********************************************/ 
void W_YLINE(sword O_X,sword O_YS,sword O_YE)
{
	sword j;
	for(j=O_YS;j<O_YE+1;j++)    	/* 画一条直线，横坐标是O_X ，纵坐标是O_Y */
	{
		W_DOT(O_X,j);          		/* 调绘点子程序  */
		if(j>239)break;          	/* 如果纵坐标大于屏的列宽240，则停止*/
	}
}

/********************************************/
  /*功能；画取消纵线函数(点阵方法)
入口参数：O_X: X轴的位置(0,319)
		  O_YS:纵轴起始点(0,239)
		  O_YE:纵轴终止点(O_YS,239) 
出口参数：无
/********************************************/ 
void W_CLEARYLINE(sword O_X,sword O_YS,sword O_YE)
{
	sword j;
	for(j=O_YS;j<O_YE+1;j++)         /* 画一条直线，横坐标是O_X ，纵坐标是O_Y */
	{
		 W_CLEARDOT(O_X,j);          /* 调绘点子程序  */
		 if(j>239)break;             /* 如果纵坐标大于屏的列宽240，则停止*/
	}
}


/********************************************/
  /*功能；画横线函数(字节方法)
入口参数：O_XS:横轴起始点(0,39)
		  O_XE:横轴终止点(O_XS,39)
		  O_Y: Y轴位置(0,239) 
出口参数：无
/********************************************/ 
void XLINE(sword O_XS,sword O_XE,sword O_Y)
{
	sword j,k;
	j=PARA;
	k=j*O_Y+O_XS+0x04ce;   	/*写入位地址的表达式*/
	WriteCode(0x4c);   		/* CSRDIR 代码 */
    WriteCode(0x46);   		/* CSRW 代码 */
    WriteData(k%256);   	/* 设置参数光标指针低8位 */
    WriteData(k/256);   	/* 设置参数光标指针高8位 */
    WriteCode(0x42);   		/* MWRITE 代码 */		
	for(j=O_XS;j<O_XE+1;j++)/*画一条直线，横坐标是O_X ，纵坐标是O_Y */
	{
	 	WriteData(0xff);    /* 调绘点子程序  */      
	}
}

/********************************************/
  /*功能；画取消横线函数(字节方法)
入口参数：O_XS:横轴起始点(0,39)
		  O_XE:横轴终止点(O_XS,39)
		  O_Y: Y轴位置(0,239) 
出口参数：无
/********************************************/ 
void CLEARXLINE(sword O_XS,sword O_XE,sword O_Y)
{
	sword j,k;
	j=PARA;
	k=j*O_Y+O_XS+0x04ce;   	/*写入位地址的表达式*/
	WriteCode(0x4c);   		/* CSRDIR 代码 */
    WriteCode(0x46);   		/* CSRW 代码 */
    WriteData(k%256);   	/* 设置参数光标指针低8位 */
    WriteData(k/256);   	/* 设置参数光标指针高8位 */
    WriteCode(0x42);   		/* MWRITE 代码 */		
	for(j=O_XS;j<O_XE+1;j++)/*画一条直线，横坐标是O_X ，纵坐标是O_Y */
	{
	 	WriteData(0x00);    /* 调绘点子程序  */      
	}
}

/********************************************/
  /*功能；画弹出子菜单边框函数(包括中英文) 
入口参数：无
出口参数：无
/********************************************/   
void WFRAME();
void WFRAME()
{
    sword i;
    if(LANGUAGE==0||LANHELP==2)	//英文窗口，中文界面下当LANHELP==2仍保留英文的窗口大小
    {
	    for(i=0;i<3;i++)
	    {
			W_DOT(70,108+i);
			W_DOT(71,108+i);
			W_DOT(200,108+i);
			W_DOT(201,108+i);			
		    XLINE(9,24,108+i);
			W_DOT(70,161+i);
			W_DOT(71,161+i);
			W_DOT(200,161+i);
			W_DOT(201,161+i);				    
		    XLINE(9,24,161+i);
		    W_YLINE(68+i,108,163);
		    W_YLINE(201+i,108,163);		    	    	
	    }
    }
    else
    {
 	    if(LANHELP==3)		//中文菜单的框图加长版,//当LANHELP==3时，显示大窗口
 	    {
			for(i=0;i<3;i++)
			{
				W_DOT(70,87+i);
				W_DOT(71,87+i);
				W_DOT(200,87+i);			
				XLINE(9,24,87+i);
				W_DOT(70,180+i);
				W_DOT(71,180+i);
				W_DOT(200,180+i);				    
				XLINE(9,24,180+i);
				W_YLINE(70+i,89,180);
				W_YLINE(198+i,89,180);		    	    	
			}
 	    }
 	    else
 	    {
			for(i=0;i<3;i++)	//中文菜单的普通版
			{
				XLINE(8,25,97+i);
				XLINE(8,25,172+i);
				W_YLINE(64+i,99,172);
				W_YLINE(205+i,99,172);		    	    	
			}
 	    }
    }
}

/********************************************/
  /*功能；清弹出子菜单程序函数(包括中英文) 
入口参数：无
出口参数：无
/********************************************/   
void CLEAR2();
void CLEAR2()
{	
	unsigned char i,O_Y;
	word j;
            	unsigned char CNENYNODE=((STATE==1||STATE==11||STATE==12||((State13parameter==0)&&(STATE==13))||((State14parameter==0)&&(STATE==14)))?(LANGUAGE?98:60):(LANGUAGE?98:64));  //分别对应中英文的点阵行数
             	unsigned char CNENYLINESTART=((STATE==1||STATE==11||STATE==12||((State13parameter==0)&&(STATE==13))||((State14parameter==0)&&(STATE==14)))?(LANGUAGE? 8: 9):(LANGUAGE?10:13));	//分别对应中英文的起始行
            	unsigned char CNENYLINEEND=	((STATE==1||STATE==11||STATE==12||((State13parameter==0)&&(STATE==13))||((State14parameter==0)&&(STATE==14)))?(LANGUAGE?15:13):(LANGUAGE?22:20));
//	unsigned char CNENYNODE=(((State13parameter==0)||(State14parameter==0))?(LANGUAGE?98:60):(LANGUAGE?98:64));  //分别对应中英文的点阵行数
//	unsigned char CNENYLINESTART=(((State13parameter==0)||(State14parameter==0))?(LANGUAGE? 8: 9):(LANGUAGE?10:13));	//分别对应中英文的起始行
//	unsigned char CNENYLINEEND=	(((State13parameter==0)||(State14parameter==0))?(LANGUAGE?15:13):(LANGUAGE?22:20));



	for(O_Y=CNENYLINESTART;O_Y<=CNENYLINEEND;O_Y++) /*清显示区一的存储器*/
	{
		i=PARA;
		j=i*O_Y+8;
		WriteCode(0x46);   		/* CSRW 代码 */
		WriteData(j%256);  		/* 设置光标地址CSR */
		WriteData(j/256);
		WriteCode(0x4c);   		/* CSRDIR 代码 */
		WriteCode(0x42);   		/* MWRITE 代码 */
		for(i=0;i<18;i++)
		{
			WriteData(0x00);  	/* 写入数据 */
		}
	}

	for(i=0;i<18;i++)   		/*清显示区二的存储器*/
	{
		WriteCode(0x4f);   		/* CSRDIR 代码 */
		WriteCode(0x46);   		/* CSRW 代码 */
		if(LANGUAGE==0)
		{	
			WriteData(126+i);  	/* 设置英文的光标地址CSR */
			WriteData(0x15);	
		}
		else 
		{
			WriteData(156+i);  	/* 设置中文的光标地址CSR */
			WriteData(0x12);			
		}
		WriteCode(0x42);   		/* MWRITE 代码 */          
		for(j=0;j<=CNENYNODE;j++)	/*写入一行*/
		{
			WriteData(0x00);  	/* 写入数据 */     		
		}  
	}
}

/********************************************/
  /*功能；清弹出新信息提示菜单程序函数(包括中英文) 
入口参数：无
出口参数：无
/********************************************/   
void ClrMsgtip();
void ClrMsgtip()
{	
	unsigned char i,O_Y;
	word j;
	for(O_Y=1;O_Y<=3;O_Y++)     /*清显示区一的存储器*/
	{
		i=PARA;
		j=i*O_Y+23;
		WriteCode(0x46);   		/* CSRW 代码 */
		WriteData(j%256);  		/* 设置光标地址CSR */
		WriteData(j/256);
		WriteCode(0x4c);   		/* CSRDIR 代码 */
		WriteCode(0x42);   		/* MWRITE 代码 */
		for(i=0;i<17;i++)
		{
			WriteData(0x00);  	/* 写入数据 */
		}
	}
	for(i=8;i<32;i++)   		/*清显示区二的存储器*/
	{
		j=PARA*i+23+0x04ce;
		WriteCode(0x46);   		/* CSRW 代码 */	
		WriteData(j%256);  		/* 设置英文的光标地址CSR */
		WriteData(j/256);		
		WriteCode(0x4c);   		/* CSRDIR 代码 */
		WriteCode(0x42);   		/* MWRITE 代码 */ 
		for(j=0;j<=17;j++)     	/*写入一行*/
		{
			WriteData(0x00);  	/* 写入数据 */     		
		}  
	}
}
  



/********************************************/
  /*功能；弹出子菜单前对应区域的数据保护
  		  暂时不编写图形显示区的保护，由
  		  于图形的数据很少，只需碰到时加
  		  上即可  
入口参数：无
出口参数：无
/********************************************/     
void ProtectData();
void ProtectData()
{
	unsigned char character[18],i,O_Y,cn[98];
	word j,l;
             	unsigned char CNENYLINESTART=((STATE==1||STATE==11||STATE==12||((State13parameter==0)&&(STATE==13))||((State14parameter==0)&&(STATE==14)))?(LANGUAGE? 8: 9):(LANGUAGE?10:13));		//分别对应中英文的起始行
               	unsigned char CNENYLINEEND=((STATE==1||STATE==11||STATE==12||((State13parameter==0)&&(STATE==13))||((State14parameter==0)&&(STATE==14)))?(LANGUAGE?15:13):(LANGUAGE?22:20));
	for(O_Y=CNENYLINESTART;O_Y<=CNENYLINEEND;O_Y++)      /*完成字符显示区的数据保护*/
	{
		i=PARA;
		j=i*O_Y+8;
		WriteCode(0x46);   				/* CSRW 代码 */
		WriteData(j%256);  				/* 设置光标地址CSR */
		WriteData(j/256);
		WriteCode(0x4c);   				/* CSRDIR 代码 */
		WriteCode(0x43);   				/* MREAD 代码 */
		for(i=0;i<18;i++)
		{
			character[i]=ReadData();  	/* 读出数据 */
		}
		j=PARA*(O_Y-CNENYLINESTART)+0x5000; //存放地址从ram的20k空间开始
		WriteCode(0x46);   				/* CSRW 代码 */
		WriteData(j%256);  				/* 设置光标地址CSR */
		WriteData(j/256);
		WriteCode(0x4c);   				/* CSRDIR 代码 */
		WriteCode(0x42);   				/* MRITER 代码 */
		for(i=0;i<18;i++)
		{
			WriteData(character[i]);  	/* 写入数据 */
		}	     
	}

//	if(LANGUAGE==1)
//	{
		for(i=0;i<18;i++)   	/*中文显示区二的数据保护*/
		{
			WriteCode(0x46);   	/* CSRW 代码 */
			WriteData(156+i); 	/* 设置中文的光标地址CSR */
			WriteData(0x12);			
			WriteCode(0x4f);   	/* CSRDIR 代码 */
			WriteCode(0x43);   	/* MREAD 代码 */          
			for(j=0;j<98;j++)   /*写入一行*/
			{
				cn[j]=ReadData();  /* 读出数据 */     		
			}
			l=98*i+0x6000;		//存放地址从液晶ram的0x6000开始
			WriteCode(0x46);   	/* CSRW 代码 */
			WriteData(l%256);  	/* 设置光标地址CSR */
			WriteData(l/256);
			WriteCode(0x4c);   	/* CSRDIR 代码 */
			WriteCode(0x42);   	/* MRITER 代码 */
			for(j=0;j<98;j++)
			{
				WriteData(cn[j]);  /* 写入数据 */
			}	     	
		}		  
//	}
}



/********************************************/
  /*功能；子菜单返回后原数据重新写回原位置  
入口参数：无
出口参数：无
/********************************************/     
void RecoverData();
void RecoverData()
{

	unsigned char character[18],i,O_Y,cn[98];
   word j,l;   
                   unsigned char CNENYLINESTART=((STATE==1||STATE==11||STATE==12||((State13parameter==0)&&(STATE==13))||((State14parameter==0)&&(STATE==14)))?(LANGUAGE? 8: 9):(LANGUAGE?10:13));	//分别对应中英文的起始行
                   unsigned char CNENYLINEEND=((STATE==1||STATE==11||STATE==12||((State13parameter==0)&&(STATE==13))||((State14parameter==0)&&(STATE==14)))?(LANGUAGE?15:13):(LANGUAGE?22:20)); 
  //   CLEAR2();
    for(O_Y=CNENYLINESTART;O_Y<=CNENYLINEEND;O_Y++)     /*完成字符显示区的数据保护*/
	{

		i=PARA;

		j=PARA*(O_Y-CNENYLINESTART)+0x5000; 			//存放地址从ram的20k空间开始
		WriteCode(0x46);   				/* CSRW 代码 */
		WriteData(j%256);  				/* 设置光标地址CSR */
		WriteData(j/256);
		WriteCode(0x4c);   				/* CSRDIR 代码 */
		WriteCode(0x43);   				/* MREAD 代码 */
		for(i=0;i<18;i++)
		{
			character[i]=ReadData();  	/* 写入数据 */
		}	     

		j=PARA*O_Y+8;
		WriteCode(0x46);   				/* CSRW 代码 */
		WriteData(j%256);  				/* 设置光标地址CSR */
		WriteData(j/256);
		WriteCode(0x4c);  	 			/* CSRDIR 代码 */
		WriteCode(0x42);   				/* MRITER 代码 */
		for(i=0;i<18;i++)
		{
			WriteData(character[i]);  	/* 写入数据 */
		}	  	  
	}
	  
//	if(LANGUAGE==1)
//	{
		for(i=0;i<18;i++)   			/*中文显示区二的数据保护*/
		{
			l=98*i+0x6000;				//存放地址从液晶ram的0x6000开始
			WriteCode(0x46);   			/* CSRW 代码 */
			WriteData(l%256);  			/* 设置光标地址CSR */
			WriteData(l/256);
			WriteCode(0x4c);   			/* CSRDIR 代码 */
			WriteCode(0x43);   			/* MRead 代码 */
			for(j=0;j<98;j++)
			{
				cn[j]=ReadData();	  	/* 写入数据 */
			}
				     	
			WriteCode(0x46);   			/* CSRW 代码 */
			WriteData(156+i);  			/* 设置中文的光标地址CSR */
			WriteData(0x12);			
			WriteCode(0x4f);   			/* CSRDIR 代码 */
			WriteCode(0x42);   			/* MWRITE 代码 */          
			for(j=0;j<98;j++)     		/*写入一行*/
			{
				WriteData(cn[j]);  		/* 读出数据 */     		
			}	     	
		}		  
//	}
}


/********************************************/
  /*功能；初始化液晶函数   
入口参数：无
出口参数：无
/********************************************/ 
void IntialLCD(char ilcd)
{
	unsigned char i;
	FPGARW(1800)= 0x0001;


//  GPIO_B_DDR|=GPIO_B_DDR_DD8_MASK;		//rsto管脚设置为输出口
// 	GPIO_B_DR&=~GPIO_B_DR_D8_MASK;
// 	GPIO_B_DR|=GPIO_B_DR_D8_MASK;			//输出为1
	
	WriteCode(0x40);   		/* SYSTEM SET代码 */		
	for(i=0;i<8 && ilcd!=2;i++)
	{
	  
	  if(ilcd==1&&i==2)WriteData(0x0b);
	  else 
	  	WriteData(SYSTAB[i]); /* 写入参数 */
	}
	WriteCode(0x44);   		/* SCROLL代码 */		
	for(i=0;i<10;i++)
	{
	  WriteData(SCRTAB[i]); /* 写入参数 */
	}
	WriteCode(0x5a);   		/* HDOT SCR 代码 */
	WriteData(0x00);   		/* 设置参数P1 */
	WriteCode(0x5b);   		/* OVLAY 代码 */
	WriteData(0x00);   		/* 设置参数:显示一,三区为文本属性 */
//	if(ilcd==0)
//	CLEAR();       			/* 调清屏子程序 */
	WriteCode(0x59);   		/* 显示状态设置 */		
	WriteData(0x54);   		/* 设置参数:显示一～四区开显示 */
}


/***************************************/
/*  功能 画空心方框函数 
入口参数 O_X(0~39)
		 O_Y(0~239) LANGUAGE==0;英文
		 O_Y(0~29)  LANGUAGE==1;中文
出口参数 无
/***************************************/
void W_HDIAMOND(unsigned char O_X,unsigned char O_Y);
void W_HDIAMOND(unsigned char O_X,unsigned char O_Y)
{
	word i,j;
	i=O_X*8;
   	j=((LANGUAGE&LANHELP)? O_Y:(O_Y*((STATE==11||STATE==12||((State13parameter==0)&&(STATE==13))||((State14parameter==0)&&(STATE==14)))?12:8)));	//即使在LANGUAGE为1的情况下，若LANHELP为0，则选定框仍按英文菜单情况显示

	W_CLEARDOT(i+3,j+1); W_CLEARDOT(i+4,j+1);
	W_CLEARDOT(i+2,j+2); W_CLEARDOT(i+3,j+2); W_CLEARDOT(i+4,j+2); W_CLEARDOT(i+5,j+2); 	
	W_CLEARDOT(i+1,j+3); W_CLEARDOT(i+2,j+3); W_CLEARDOT(i+3,j+3); W_CLEARDOT(i+4,j+3); W_CLEARDOT(i+5,j+3); W_CLEARDOT(i+6,j+3); 
	W_CLEARDOT(i+1,j+4); W_CLEARDOT(i+2,j+4); W_CLEARDOT(i+3,j+4); W_CLEARDOT(i+4,j+4); W_CLEARDOT(i+5,j+4); W_CLEARDOT(i+6,j+4);	
	W_CLEARDOT(i+2,j+5); W_CLEARDOT(i+3,j+5); W_CLEARDOT(i+4,j+5); W_CLEARDOT(i+5,j+5);
	W_CLEARDOT(i+3,j+6); W_CLEARDOT(i+4,j+6);	

	W_DOT(i+3,j);	W_DOT(i+4,j);	W_DOT(i+2,j+1);		W_DOT(i+5,j+1);
	W_DOT(i+1,j+2);	W_DOT(i+6,j+2);	W_DOT(i,j+3);		W_DOT(i+7,j+3);
	W_DOT(i,j+4);	W_DOT(i+7,j+4);	W_DOT(i+1,j+5);		W_DOT(i+6,j+5);
	W_DOT(i+2,j+6);	W_DOT(i+5,j+6);	W_DOT(i+3,j+7);		W_DOT(i+4,j+7);	
}

/*************************************/
/*  功能 画实心方框函数   
入口参数 O_X(0~39)
		 O_Y(0~239) LANGUAGE==0;英文
		 O_Y(0~29)  LANGUAGE==1;中文
出口参数 无
/*************************************/
void W_DIAMOND(unsigned char O_X,unsigned char O_Y);
void W_DIAMOND(unsigned char O_X,unsigned char O_Y)
{
	word i,j;
	i=O_X*8;
   	j=((LANGUAGE&LANHELP)?O_Y:(O_Y*((STATE==11||STATE==12||((State13parameter==0)&&(STATE==13))||((State14parameter==0)&&(STATE==14)))?12:8)));
	W_DOT(i+3,j);	W_DOT(i+4,j);
	W_DOT(i+2,j+1);	W_DOT(i+3,j+1); W_DOT(i+4,j+1);	W_DOT(i+5,j+1);
	W_DOT(i+1,j+2);	W_DOT(i+2,j+2);	W_DOT(i+3,j+2); W_DOT(i+4,j+2); W_DOT(i+5,j+2); W_DOT(i+6,j+2);	
	W_DOT(i,j+3);	W_DOT(i+1,j+3); W_DOT(i+2,j+3);	W_DOT(i+3,j+3);	W_DOT(i+4,j+3); W_DOT(i+5,j+3); W_DOT(i+6,j+3); W_DOT(i+7,j+3);
	W_DOT(i,j+4);	W_DOT(i+1,j+4); W_DOT(i+2,j+4);	W_DOT(i+3,j+4);	W_DOT(i+4,j+4); W_DOT(i+5,j+4); W_DOT(i+6,j+4);	W_DOT(i+7,j+4);
	W_DOT(i+1,j+5); W_DOT(i+2,j+5);	W_DOT(i+3,j+5); W_DOT(i+4,j+5); W_DOT(i+5,j+5);	W_DOT(i+6,j+5);
	W_DOT(i+2,j+6);	W_DOT(i+3,j+6); W_DOT(i+4,j+6);	W_DOT(i+5,j+6);
	W_DOT(i+3,j+7);	W_DOT(i+4,j+7);
}


/********************************************/
  /*功能；画未读信息标记函数  
入口参数：byte型，O_X(0~39)
		  byte型，O_Y(0~29) 
出口参数：无
/********************************************/ 
void W_NEWMESSAGE(unsigned char O_X,unsigned char O_Y);
void W_NEWMESSAGE(unsigned char O_X,unsigned char O_Y)
{
	word i,j;
	unsigned char f;
	i=O_X*8;
	j=O_Y*8;
	for(f=0;f<13;f++)
	{
		W_DOT(i+f,j);	W_DOT(i+f,j+7);
	}
	for(f=0;f<7;f++)
	{
		W_DOT(i,j+f);	W_DOT(i+12,j+f);
	}
	W_DOT(i+1,j+1);  W_DOT(i+11,j+1);	
	W_DOT(i+2,j+2);  W_DOT(i+10,j+2);
	for(f=3;f<10;f++)
	{
		W_DOT(i+f,j+3);
	}
}

/********************************************/
  /*功能；清未读信息标记函数  
入口参数：byte型，O_X(0~39)
		  byte型，O_Y(0~29) 
出口参数：无
/********************************************/ 
//W_CLEARMESSAGE(unsigned char O_X,unsigned char O_Y);
void W_CLEARMESSAGE(unsigned char O_X,unsigned char O_Y)
{
	word i,j;
	unsigned char f,k;
	i=O_X*8;
	j=O_Y*8;
	for(f=0;f<13;f++)
	{
		W_CLEARDOT(i+f,j);	W_CLEARDOT(i+f,j+7);
	}
	
	for(f=0;f<7;f++)
	{
		W_CLEARDOT(i,j+f);	W_CLEARDOT(i+12,j+f);
	}

	W_CLEARDOT(i+1,j+1);  W_CLEARDOT(i+11,j+1);	
	W_CLEARDOT(i+2,j+2);  W_CLEARDOT(i+10,j+2);
	
	for(f=3;f<10;f++)
	{
		W_CLEARDOT(i+f,j+3);
	}
}

/***********************/
/*    画锁定标记函数   */
/***********************/
W_LOCK(unsigned char O_X,unsigned char O_Y);
W_LOCK(unsigned char O_X,unsigned char O_Y)
{
	word i,j;
	i=O_X*8;
	j=O_Y*8;
	
}

/***********************/
/*   画未锁定标记函数  */
/***********************/
W_UNLOCK();
W_UNLOCK()
{

}


/********************************************/
  /*功能：画上移动标记函数 
入口参数：byte型，O_X(0~39)
		  byte型，O_Y(0~29) 
出口参数：无
/********************************************/ 
void W_UPMOVE(unsigned char O_X,unsigned char O_Y);
void W_UPMOVE(unsigned char O_X,unsigned char O_Y)
{
	word i,j;
	char f;
	i=O_X*8;
	j=O_Y*8-1;
	W_DOT(i+2,j+1); 
	W_DOT(i+1,j+2);  W_DOT(i+2,j+2);  W_DOT(i+3,j+2);
	W_DOT(i+1,j+3);  W_DOT(i+2,j+3);  W_DOT(i+3,j+3);		
	W_DOT(i,j+4);	 W_DOT(i+1,j+4);  W_DOT(i+2,j+4);
	W_DOT(i+3,j+4);  W_DOT(i+4,j+4);
	for(f=0;f<7;f++)
	{
		W_DOT(i-1+f,j+5);
		W_DOT(i-1+f,j+6);
		W_DOT(i-1+f,j+7);			
	}
	
}

/********************************************/
  /*功能：画下移动标记函数 
入口参数：byte型，O_X(0~39)
		  byte型，O_Y(0~29) 
出口参数：无
/********************************************/ 
void W_DOWNMOVE(unsigned char O_X,unsigned char O_Y);
void W_DOWNMOVE(unsigned char O_X,unsigned char O_Y)
{
	word i,j;
	char f;
	i=O_X*8;
	j=O_Y*8-1;
	for(f=0;f<7;f++)
	{
		W_DOT(i-1+f,j+1);
		W_DOT(i-1+f,j+2);
		W_DOT(i-1+f,j+3);			
	}
	W_DOT(i,j+4);	 W_DOT(i+1,j+4);  W_DOT(i+2,j+4);  W_DOT(i+3,j+4); W_DOT(i+4,j+4);
	W_DOT(i+1,j+5);  W_DOT(i+2,j+5);  W_DOT(i+3,j+5);	
	W_DOT(i+1,j+6);  W_DOT(i+2,j+6);  W_DOT(i+3,j+6);
	W_DOT(i+2,j+7); 
}

/********************************************/
  /*功能：清除上下移动标记函数 
入口参数：byte型，O_X(0~39)
		  byte型，O_Y(0~29) 
出口参数：无
/********************************************/ 
void W_CLEARUPDN(unsigned char O_X,unsigned char O_Y);
void W_CLEARUPDN(unsigned char O_X,unsigned char O_Y)
{
	word i,j;
	unsigned char f,k;
	i=O_X*8;
	j=O_Y*8;
	for(f=0;f<8;f++)
	{
		for(k=0;k<7;k++)
		W_CLEARDOT(i+f-1,j+k);
	}
	
}



/********************************************/
  /*功能：画选定标记函数（就是勾） 
入口参数：byte型，O_X(0~39)
		  byte型，O_Y(0~29) 
出口参数：无
/********************************************/ 
void W_CHOOSED(unsigned char O_X,unsigned char O_Y);
void W_CHOOSED(unsigned char O_X,unsigned char O_Y)
{
	word i,j;
	i=O_X*8;
	j=O_Y*8;

	W_DOT(i+7,j);	 W_DOT(i+6,j+1);  W_DOT(i+5,j+2);  W_DOT(i+4,j+3);  W_DOT(i,j+3); 
	W_DOT(i+3,j+4);	 W_DOT(i+1,j+4);  W_DOT(i+2,j+5); 
}


/********************************************/
  /*功能：画取消选定标记函数（就是勾） 
入口参数：byte型，O_X(0~39)
		  byte型，O_Y(0~29) 
出口参数：无
/********************************************/ 
void W_CANCALCHOOSED(unsigned char O_X,unsigned char O_Y);
void W_CANCALCHOOSED(unsigned char O_X,unsigned char O_Y)
{
	word i,j;
	i=O_X*8;
	j=O_Y*8;
	W_CLEARDOT(i+7,j);	 W_CLEARDOT(i+6,j+1);  W_CLEARDOT(i+5,j+2);  W_CLEARDOT(i+4,j+3);
	W_CLEARDOT(i,j+3); 	 W_CLEARDOT(i+3,j+4);  W_CLEARDOT(i+1,j+4);  W_CLEARDOT(i+2,j+5); 
}


/********************************************/
  /*功能：十进制二位数转为两位ascii码
入口参数：byte型，O_X(0~39)
		  byte型，O_Y(0~29)
		  byte型，demical，十进制的二位数 
出口参数：无
/********************************************/ 
void DISASCII(unsigned char O_X,unsigned char O_Y,unsigned char demical);
void DISASCII(unsigned char O_X,unsigned char O_Y,unsigned char demical)//弹出子菜单的一行
{
	unsigned char i;
	word j;
	unsigned char ascii[2];
	ascii[1]=demical%10+48;		//个位数
	ascii[0]=demical/10+48;		//十位数			
	i=PARA;
	j=i*O_Y+O_X;
	WriteCode(0x46);   			/* CSRW 代码 */
	WriteData(j%256);  			/* 设置光标地址CSR */
	WriteData(j/256);
	WriteCode(0x4c);		   	/* CSRDIR 代码 */
	WriteCode(0x42);   			/* MWRITE 代码 */
	for(i=0;i<2;i++)
	{
		WriteData(ascii[i]);  	/* 写入数据 */
	}
 
}   


/********************************************/
  /*功能：十进制二位数转为三位ascii码
入口参数：byte型，O_X(0~39)
		  byte型，O_Y(0~29)
		  word型，demical，十进制的三位数 
出口参数：无
/********************************************/ 
void DISASCIII(unsigned char O_X,unsigned char O_Y,word demical);
void DISASCIII(unsigned char O_X,unsigned char O_Y,word demical)//弹出子菜单的一行
{
	unsigned char i;
	word j;
	unsigned char ascii[3];
	ascii[2]=demical%10+48;						//个位数
	ascii[0]=demical/100+48;					//百位数
	ascii[1]=(demical/10)%10+48;            	//十位数
	i=PARA;
	j=i*O_Y+O_X;
	WriteCode(0x46);   							/* CSRW 代码 */
	WriteData(j%256);  							/* 设置光标地址CSR */
	WriteData(j/256);
	WriteCode(0x4c);   							/* CSRDIR 代码 */
	WriteCode(0x42);   							/* MWRITE 代码 */
	for(i=0;i<3;i++)
	{
		WriteData(ascii[i]);  					/* 写入数据 */
	}
 
}


/********************************************/
  /*功能：画移动滑块标记函数
入口参数：byte型，O_X(0~39)
		  byte型，O_Y(0~29)
出口参数：无
/********************************************/ 
void W_BLOCK(unsigned char O_X,unsigned char O_Y);
void W_BLOCK(unsigned char O_X,unsigned char O_Y)
{
	word i,j;
	unsigned char f,k;
	i=O_X*8;
	j=O_Y*8;
	for(f=0;f<9;f++)
	{
		for(k=0;k<24;k++)
		W_DOT(i+f-2,j+k);
	}
	
}

/********************************************/
  /*功能：清除移动滑块标记函数
入口参数：byte型，O_X(0~39)
		  byte型，O_Y(0~29)
出口参数：无
/********************************************/ 
void W_CLEARBLOCK(unsigned char O_X,unsigned char O_Y);
void W_CLEARBLOCK(unsigned char O_X,unsigned char O_Y)
{
	word i,j;
	unsigned char f,k;
	i=O_X*8;
	j=O_Y*8;
	for(f=0;f<9;f++)
	{
		for(k=0;k<24;k++)
		W_CLEARDOT(i+f-2,j+k);
	}	
	
}

/********************************************/
  /*功能：画弹出信息提示菜单边框函数
入口参数：无
出口参数：无
/********************************************/ 
void WfmMsgtip();
void WfmMsgtip()
{
    sword i;
    if(LANGUAGE==0)
    {
	    for(i=0;i<3;i++)
	    {
		    XLINE(23,39,8+i);
		    XLINE(23,39,29+i);
		    W_YLINE(184+i,11,28);
		    W_YLINE(317+i,11,28);		    	    	
	    }
    }
    else
    {
	    for(i=0;i<2;i++)
	    {
		    XLINE(26,38,8+i);
		    XLINE(26,38,30+i);
		    W_YLINE(208+i,10,29);
		    W_YLINE(310+i,10,29);		    	    	
	    }
    }
	
}



/*************************************************/
  /*功能：清除信息头文件函数 
入口参数：char型 num:需删除信息头文件在LCD头行位置
出口参数：无
/************************************************/ 
void W_CLEARMSGTOP(char num);
void W_CLEARMSGTOP(char num)
{
	char i;
	/*一区即字符显示的清除*/
	for(i=0;i<40;i++)
	{
	 CTAB[i]=0x20;  
	}
	CW_PR(0,num,40);
	CW_PR(0,num+1,40);
	CW_PR(0,num+2,40);
	/*二区即点阵显示的清除*/
	W_CANCALCHOOSED(1,num+2);
	W_CLEARMESSAGE(1,num);
	CCW_PR1(3,(num+1)*8,0x1760,0);
	CCW_PR1(5,(num+1)*8,0x1760,0);
	CCW_PR1(7,(num+1)*8,0x1760,0);

	
	
	CCW_PR1(21,(num+1)*8,0x1760,0);
	CCW_PR1(23,(num+1)*8,0x1760,0);
	CCW_PR1(25,(num+1)*8,0x1760,0);
	CCW_PR1(27,(num+1)*8,0x1760,0);
 	CCW_PR1(29,(num+1)*8,0x1760,0);
	CCW_PR1(31,(num+1)*8,0x1760,0);
	CCW_PR1(33,(num+1)*8,0x1760,0);
 	CCW_PR1(35,(num+1)*8,0x1760,0); 	
	  	  
}



/*********************************************************/
  /*功能：在LCD指定位置显示工作模式(中英文公用)
入口参数：x_zhongwen(0~39)  中文菜单下显示内容在x轴起始位置
		  y_zhongwen(0~239) 中文菜单下显示内容在y轴起始位置
		  x_yingwen(0~39)   中文菜单下显示内容在x轴起始位置
		  y_yingwen(0~29)   中文菜单下显示内容在y轴起始位置			
出口参数：无
/*********************************************************/ 
void W_Mode(byte x_zhongwen,byte y_zhongwen,byte x_yingwen,byte y_yinwen);
void W_Mode(byte x_zhongwen,byte y_zhongwen,byte x_yingwen,byte y_yinwen)
{
	
	  if(LANGUAGE==1)	//中文菜单
	  {
	  	if(Mode==0)		//显示自动
	  	{
	 		CCW_PR1(x_zhongwen,y_zhongwen,0xd7d4,1);
 			CCW_PR1(x_zhongwen+2,y_zhongwen,0xb6Af,1);	  		
	  	}
	  	
	  	else			//显示手动
	  	{
	 		CCW_PR1(x_zhongwen,y_zhongwen,0xcad6,1);
 			CCW_PR1(x_zhongwen+2,y_zhongwen,0xb6Af,1);	  		
	  	}
	  }
	  
	  else				//英文菜单
	  {
	  	if(Mode==0)		//显示：AUTO
	  	{
	    	CW_PR3(x_yingwen,y_yinwen,'A');
	    	CW_PR3(x_yingwen+1,y_yinwen,'U');
	    	CW_PR3(x_yingwen+2,y_yinwen,'T');
	    	CW_PR3(x_yingwen+3,y_yinwen,'O');
	    	CW_PR3(x_yingwen+4,y_yinwen,' ');
	    	CW_PR3(x_yingwen+5,y_yinwen,' ');	  		
	  	}
	  	
	  	else
	  	{
	    	CW_PR3(x_yingwen,y_yinwen,'M');
	    	CW_PR3(x_yingwen+1,y_yinwen,'A');
	    	CW_PR3(x_yingwen+2,y_yinwen,'N');
	    	CW_PR3(x_yingwen+3,y_yinwen,'U');
	    	CW_PR3(x_yingwen+4,y_yinwen,'A');
	    	CW_PR3(x_yingwen+5,y_yinwen,'L');	  		
	  	}
	  	
	  }
}

void W_current_area(byte x_zhongwen,byte y_zhongwen,byte x_yingwen,byte y_yinwen,char current_area);
void W_current_area(byte x_zhongwen,byte y_zhongwen,byte x_yingwen,byte y_yinwen,char current_area)
{

	if(LANGUAGE==0)		//英文
	{
		CW_PR3(x_yingwen,y_yinwen,'(');
		DISASCII(x_yingwen+1,y_yinwen,current_area);
		CW_PR3(x_yingwen+3,y_yinwen,')');
	}
	else				//中文
	{
		CW_PR3(x_zhongwen,y_zhongwen,'(');
		DISASCII(x_zhongwen+1,y_zhongwen,current_area);
		CW_PR3(x_zhongwen+3,y_zhongwen,')');		
	}	
}

/*************************************************/
  /*功能：写信息头文件函数 
入口参数：int型  num:信息头文件在数组中所处位置
		  char型 pos:在LCD页面中起始行数
		  char型 mod:0表示存储信息，1表示锁定信息
出口参数：无
/************************************************/ 
void W_MSGTOP(sword num,char pos,char mod)
{
	char i,j;
	Messagetoptype * temp; 
/*	if(mod==0)	temp=&Messagesavetop[num];
	else temp=&Messagelocktop[num];*/
	if(mod==0)
	temp=&(Messagesavetop[Messagetoprank[num]]);
	else
	temp=&(Messagesavetop[Msglockrank[num]]);
	for(i=0;i<4;i++) 			//显示信息标记符号
	{
//	    if(i==0&&temp->mark[i]==0x01)CW_PR3(3+i,pos,'Q');
//		else CW_PR3(3+i,pos,temp->mark[i]);

//	    if(i==0&&temp->mark[i]==0x01)CW_PR3(3+i,1,'Q');
//		else CW_PR3(3+i,1,temp->mark[i]);
		if(i==0||i==1)
		{
			switch(temp->mark[i])
					{
						case('-'):CW_PR3(3+i,pos,'A');break;
						case('?'):CW_PR3(3+i,pos,'B');break;
						case(':'):CW_PR3(3+i,pos,'C');break;
						case('*'):CW_PR3(3+i,pos,'D');break;
						case('3'):CW_PR3(3+i,pos,'E');break;
						case('%'):CW_PR3(3+i,pos,'F');break;
						case('#'):CW_PR3(3+i,pos,'G');break;
						case(34):CW_PR3(3+i,pos,'H');break;//' "  '双引号
						case('8'):CW_PR3(3+i,pos,'I');break;
						case('@'):CW_PR3(3+i,pos,'J');break;
						case('('):CW_PR3(3+i,pos,'K');break;
						case(')'):CW_PR3(3+i,pos,'L');break;
						case('.'):CW_PR3(3+i,pos,'M');break;
						case(','):CW_PR3(3+i,pos,'N');break;
						case('9'):CW_PR3(3+i,pos,'O');break;
						case('0'):CW_PR3(3+i,pos,'P');break;
						case('1'):CW_PR3(3+i,pos,'Q');break;
						case('4'):CW_PR3(3+i,pos,'R');break;
						case(39):CW_PR3(3+i,pos,'S');break;//' ' '单引号
						case('5'):CW_PR3(3+i,pos,'T');break;
						case('7'):CW_PR3(3+i,pos,'U');break;
						case('='):CW_PR3(3+i,pos,'V');break;
						case('2'):CW_PR3(3+i,pos,'W');break;
						case('/'):CW_PR3(3+i,pos,'X');break;
						case('6'):CW_PR3(3+i,pos,'Y');break;
						case('+'):CW_PR3(3+i,pos,'Z');break;
						default:CW_PR3(3+i,pos,temp->mark[i]);break;
		}
		
	}
	else CW_PR3(3+i,pos,temp->mark[i]);
	
	}
	switch(temp->frequency)		//显示频率
	{
		case 1:					//1代表518
			{
				CW_PR3(9,pos,'5');
				CW_PR3(10,pos,'1');
				CW_PR3(11,pos,'8');
				CW_PR3(12,pos,' ');
				CW_PR3(13,pos,' ');
				CW_PR3(14,pos,' ');	
			} break;
		case 2:					//2代表490
			{
				CW_PR3(9,pos,'4');
				CW_PR3(10,pos,'8');
				CW_PR3(11,pos,'6');
				CW_PR3(12,pos,' ');
				CW_PR3(13,pos,' ');
				CW_PR3(14,pos,' ');	
			} break;
		case 3:					//3代表4209.5
			{
				CW_PR3(9,pos,'4');
				CW_PR3(10,pos,'2');
				CW_PR3(11,pos,'0');
				CW_PR3(12,pos,'9');
				CW_PR3(13,pos,'.');
				CW_PR3(14,pos,'5');	
			} break;
		default:break;
	}
//	DISASCII(17,pos,temp->length);	 //显示信息长度
	DISASCII(21,pos,temp->date[0]);  //显示年
	CW_PR3(23,pos,'/');	
	DISASCII(24,pos,temp->date[1]);  //显示月
	CW_PR3(26,pos,'/');
	DISASCII(27,pos,temp->date[2]);	 //显示日
	
	DISASCII(31,pos,temp->time[0]);	 //显示小时
	CW_PR3(33,pos,':');	
	DISASCII(34,pos,temp->time[1]);	 //显示分钟
	
	if(LANGUAGE==0)		//英文界面
	{
		CTAB[0]='S';	CTAB[1]='T';	CTAB[2]='A';	CTAB[3]='T';//暂时不考虑岸台
		CTAB[4]='I';	CTAB[5]='O';	CTAB[6]='N';	CTAB[7]=':';
		CW_PR(3,pos+1,8);
		
		if(temp->area>=1&&temp->area<=16&&temp->mark[0]>='A'&&temp->mark[0]<='Z')
		{
	 		for(i=0;i<14;i++)
	 		{
	  			CTAB[i]=Rxstation[temp->area-1][temp->mark[0]-'A'][i]; 			
	 		}
			CW_PR(11,pos+1,14);				
		}
		
		
		
		CTAB[0]='M';	CTAB[1]='S';	CTAB[2]='G';	CTAB[3]=' ';//暂时不考虑信息类别
		CTAB[4]='T';	CTAB[5]='Y';	CTAB[6]='P';	CTAB[7]='E';	CTAB[8]=':';
		CW_PR(3,pos+2,9);
 	
 		if(temp->mark[1]>='A'&&temp->mark[1]<='Z')
 		{
	  		for(i=0;i<13;i++)
	 		{
	  			CTAB[i]=MessagetypeEn[temp->mark[1]-'A'][i]; 			
	 		}
			CW_PR(12,pos+2,13);			
 		}
		
	}
	
	else 				//中文界面
	{
 		CCW_PR1(3,(pos+1)*8,0xb0b6,1);	//显示内容"岸台:"
 		CCW_PR1(5,(pos+1)*8,0xcca8,1);
 		CW_PR3(7,pos+2,':');
 
 		if(temp->area>=1&&temp->area<=16&&temp->mark[0]>='A'&&temp->mark[0]<='Z')
 		{
	  		for(i=0;i<14;i++)
	 		{
	  			CTAB[i]=Rxstation[temp->area-1][temp->mark[0]-'A'][i]; 			
	 		}
			CW_PR(8,pos+2,14);		
 		}
		
 		
  		
 //		CCW_PR1(21,(pos+1)*8,0xd0c5,1);	//第三行内容"信息类别:"
 //		CCW_PR1(23,(pos+1)*8,0xcfa2,1);
 		CCW_PR1(23,(pos+1)*8,0xc0e0,1);
 		CCW_PR1(25,(pos+1)*8,0xb1f0,1);
 	 	CW_PR3(27,pos+2,':');
  
   		if(temp->mark[1]>='A'&&temp->mark[1]<='Z')
   		{
     		CCW_PR1(28,(pos+1)*8,MessagetypeCn[temp->mark[1]-'A'][0],1);
			CCW_PR1(30,(pos+1)*8,MessagetypeCn[temp->mark[1]-'A'][1],1);	 	
			CCW_PR1(32,(pos+1)*8,MessagetypeCn[temp->mark[1]-'A'][2],1);
			CCW_PR1(34,(pos+1)*8,MessagetypeCn[temp->mark[1]-'A'][3],1);		
   		}
	 	
	}

	
	
	if(temp->read==1)	W_NEWMESSAGE(1,pos);		//新信息则画上标记，否则清除
	else W_CLEARMESSAGE(1,pos);
	
	
	if(mod==0)
	{
		if(temp->lock==1)	CW_PR3(1,pos+2,'S');	//锁定则画上锁定标记，否则清除
		else CW_PR3(1,pos+2,' ');	
	}

	
	if(temp->select==1)	W_CHOOSED(1,pos+2);			//复选则画上复选标记，反之清除
	else W_CANCALCHOOSED(1,pos+2);
}



/********************************************/
  /*功能：Automode界面中海区岸台的显示
入口参数：byte型，navarea 需显示的海区
出口参数：无
/********************************************/ 
//void Station_display(word navarea1);
void Station_display(word navarea1)
/*{
	word i,l;
	for(i=0;i<13;i++)
	{
		for(l=0;l<14;l++)
		{
			CTAB[l]=Rxstation[navarea1][i][l];
		}
		
		CW_PR(5,5+2*i,14);
		
		for(l=0;l<14;l++)
		{
			CTAB[l]=Rxstation[navarea1][i+13][l];
		}
		
		CW_PR(24,5+2*i,14);		
	}
	

}*/

{


	word j;
	char i,l;
	for(i=0;i<13;i++)				//左半部分的显示
	{
		j=PARA*(5+2*i)+5;
		WriteCode(0x46);   			// CSRW 代码 
		WriteData(j%256);  			// 设置光标地址CSR 
		WriteData(j/256);
		WriteCode(0x4c);		   	// CSRDIR 代码 
		WriteCode(0x42);   			// MWRITE 代码 
		for(l=0;l<14;l++)
		{
			WriteData(Rxstation[navarea1][i][l]);  	// 写入数据 
		}		
	}

 	for(i=13;i<26;i++)				//右半部分的显示
	{
		j=PARA*(5+2*(i-13))+24;
		WriteCode(0x46);   			// CSRW 代码 
		WriteData(j%256);  			// 设置光标地址CSR 
		WriteData(j/256);
		WriteCode(0x4c);		   	// CSRDIR 代码 
		WriteCode(0x42);   			// MWRITE 代码 
		for(l=0;l<14;l++)
		{
			WriteData(Rxstation[navarea1][i][l]);  	// 写入数据 
		}		
	}
} 


/****************************************************/	
	/*  存储信息显示程序一行(英文) */
	/*入口参数1:所在行数*/
	/*入口参数2:需显示字符串头指针*/
	/*出口参数：显示完本行字符串后所指向的下个可显示字符的地址*/	
/****************************************************/
char *MessageDisLine(byte YLine,char *Ldisads);
char *MessageDisLine(byte YLine,char *Ldisads)
{
/*	byte i;
	for(i=1;i<38;i++)	//一行显示的横轴范围从1~37
	{
		if(*Ldisads==NULL) break;	//遇到NULL，字符串显示完毕，结束显示
		if(*Ldisads==10)	
			{Ldisads++;break;}	//遇到换行符则直接结束本行显示，指针指向下个字符串	
		if(*Ldisads==9) 	
			{i+=3;Ldisads++;continue;}	//遇到TAB则直接空四个字符串的位置，结束本次循环，针指向下个字符串
	
		CW_PR3(i,YLine,*Ldisads);
		Ldisads++;	
	}
	
	return(Ldisads);*/
}				


/****************************************************/	
	/*  存储信息显示程序一页(英文)  */
	/*入口参数:需显示字符串头指针*/
	/*出口参数：所显示字符串中最后一个字符地址*/	
/****************************************************/
void MessageDis(char *DisAds);
void MessageDis(char *DisAds)
{
/*	char i,*Ldisads,j;
	Ldisads=DisAds;
	
	for(i=3;i<28;i++)
	{
		for (j=1;j<38;j++)
		{
			CW_PR3(j,i,' ');	
		}
	}	//每次显示时，先清空当前内容
	
	MesDisFir=DisAds;	//获取当前显示字符串显示的首地址
	for(i=3;i<28;i+=2)	//可显示得行数范围从3~27共13行
	{
		
		Ldisads=MessageDisLine(i,Ldisads);
		if(i==3)	MesDisDw=Ldisads;//获取当前显示页第二行的首地址
		if(*Ldisads==NULL) break;//若返回的是NULL指针，说明该字符串已显示完毕，跳出循环
				
	}
	MesDisLast=Ldisads;//获取当前显示页最后一个字符的下一个字符地址*/
}

/****************************************************/	
	/*  存储信息显示程序一页(英文)  */
	/*入口参数:需显示正文的起始行数*/
	/*出口参数：所显示字符串中最后一个字符地址*/	
/****************************************************/
void MessageDisplay(word startlen);
void MessageDisplay(word startlen)
{
	
	char rn=0,i,j,*temp,line,tt=0,l=0,num_tt=0;
	word k=0;
	word *temp2;
//	sword aa,bb;
//	CLEARXLINE();		//字节方法
//	W_CLEARXLINE();		//点阵方法
/*	for(i=3;i<28;i++)
	{
		for (j=1;j<38;j++)
		{
			CW_PR3(j,i,' ');	
		}
	}*/
//	for(aa=18;aa<226;aa++)
//		W_CLEARXLINE(3,308,aa);	//每次显示时，先清空当前内容
//	unsigned int i,j;
	if((Messagesavetop[(uint32)Messagetoprank[Messagenownumber]].frequency==2))
	{
		line=1;
		for(i=1;i<11;i++)
		{
			l=line*20+8;		//中间空3个点阵
			j=2;
			for(tt=0;tt<18;tt++)
			{
				CCW_PR1(j,l,0xa1a1,1);	
				j=j+2;		
			}
		}//每次显示时，先清空当前内容
		line=1;
		for(i=1;i<11;i++)
		{
			if(k+startlen>LINE) break;
			else
			{
				l=line*20+8;		//中间空3个点阵
				j=2;
				temp2=LinePoint2[startlen+k];
				tt=-1;                               //    ? @2014-04-23
				num_tt=0;
				while(num_tt<18)
//				for(num_tt=0;num_tt<18;num_tt++)
				{
					tt++;
					if(*(temp2+tt)==13)//遇到换行符则直接结束本行显示，指针指向下个字符串
					{
						if(*(temp2+tt-1)==13)
							continue;
						else
							break;
					}
					if(*(temp2+tt)==10)
					{
						if((*(temp2+tt-1)==13)||(*(temp2+tt-1)==10))
							continue;
						else
							break;
					}
							
		/*			if(*temp==9) 	
						{j+=3;temp++;continue;}	//遇到TAB则直接空四个字符串的位置，结束本次循环，针指向下个字符串
		*///未添加	
		
	/*				if((*(temp2+tt)==10)||(*(temp2+tt)==13))
					{
						if(rn==0)
						{
							rn=1;
							break;
						}
						else 
							continue;
							
					}*/
					if(*(temp2+tt)==NULL) break;	//到文本显示末位，直接跳出
				
					CCW_PR1(j,l,*(temp2+tt),1);
					num_tt++;
//					temp2++;	
					j=j+2;
				}
			}
			
			k++;
			line++;
		} 
	}
	else
	{
		for(i=2;i<19;i++)
		{
			for (j=1;j<38;j++)
			{
				CW_PR3(j,i,' ');	
			}
		}//每次显示时，先清空当前内容
		for(i=2;i<19;i++)
		{

			if(k+startlen>LINE) break;
			else
			{
				temp=LinePoint[startlen+k];
				for(j=1;j<38;j++)
				{
				
					if((*temp==13)||(*temp==10)) break;//遇到换行符则直接结束本行显示，指针指向下个字符串
				
					if(*temp==9) 	
						{j+=3;temp++;continue;}	//遇到TAB则直接空四个字符串的位置，结束本次循环，针指向下个字符串
					
					if(*temp==NULL) break;	//到文本显示末位，直接跳出
					
					if((j==37)&&((*temp)>='A')&&((*temp)<='Z')&&(((*(temp-1))>'Z')||((*(temp-1))<'A')))
						CW_PR3(j,i,' ');
					else if((j==37)&&((*temp)>='A')&&((*temp)<='Z')&&((*(temp+1))<='Z')&&((*(temp+1))>='A'))
						CW_PR3(j,i,'^');
					else
					{
						CW_PR3(j,i,*temp);
				    	temp++;							
					}

				}
			}
			
			k++;
		} 
//	readalleeprom();	
//	readflash();
	}

}


