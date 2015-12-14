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
//#define FPGARW(offset)   *((volatile word *)(0x002f8000+offset))   //�Լ��ӵĹ���FPGA��д

/*-------------------320240��SYSTEM SET ����-------------------------------*/
//volatile byte SYSTAB[8]={0x30,0x87,0x07,0x28,0x42,0xf0,0x29,0x00};
//volatile byte SCRTAB[10]={0x00,0x00,0xf0,0xce,0x04,0xf0,0x80,0x00,0x00,0x00};
//volatile byte CTAB[40];
void pinoflcdinit(void)
{
  GPIO_InitTypeDef  GPIO_InitStructure; 

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA,ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOC,ENABLE); 
   
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;	      //���ù���
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;		
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
  GPIO_Init(GPIOC, &GPIO_InitStructure);

  GPIO_InitStructure.GPIO_Pin = 	GPIO_Pin_9|GPIO_Pin_10|GPIO_Pin_11|GPIO_Pin_12;
  GPIO_Init(GPIOA, &GPIO_InitStructure);	
}
/*************************************/
  /*���ܣ���LCDдָ�����
��ڲ�����char�ͣ���LCDд����ַ�
���ڲ�������
/*************************************/
 void WriteCode(char code);
 void WriteCode(char code)
 {
 //	int uu;
 	/*1.���ݵ����*/
 	GPIOC->MODER &= 0xffff0000;
 	GPIOC->MODER |= 0x00005555;					//DB7~DB0��8���ܽ�����Ϊ�����
 	GPIOC->ODR = (0x000000ff & (int)code);        //�������   @int =4byte
	
 	/*2.A0_LCD����*/
 	GPIOA->MODER &= 0xfff3ffff;  	//A0_LCD�ܽ�����Ϊ�����
 	GPIOA->MODER |= 0x00040000;
 	GPIOA->ODR |= GPIO_ODR_ODR_9; 		//A0_LCD�ܽ�����ߵ�ƽ
 	 	
 	/*3./CS_LCD��Ƭѡ����*/
 	GPIOA->MODER &= 0xfcffffff;  	// /CS_LCD�ܽ�����Ϊ�����
 	GPIOA->MODER |= 0x01000000; 
	GPIOA->ODR &= ~GPIO_ODR_ODR_12; 		// /CS_LCD�ܽ�����͵�ƽ

 	/*4./WR_LCD����*/
  GPIOA->MODER &= 0xffcfffff;  	// /WR_LCD�ܽ�����Ϊ�����
 	GPIOA->MODER |= 0x00100000;
	GPIOA->ODR &= ~GPIO_ODR_ODR_10;		// /WR_LCD�ܽ�����͵�ƽ

 	/*5.200nsʱ��ĵȴ�*/
  __nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();

	
  	/*6./WR_LCD����*/
 	GPIOA->ODR |= GPIO_ODR_ODR_10|GPIO_ODR_ODR_12;		// /WR_LCD�ܽ�����ߵ�ƽ
 	
  	/*7./CS_LCD��Ƭѡ����*/
 	//GPIOA->ODR |= GPIO_ODR_ODR_12;		// /CS_LCD�ܽ�����ߵ�ƽ
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
 }


/******************************************/
  /*���ܣ���LCDд��������ʾ����
��ڲ�����char�ͣ���LCDд��Ĳ�������ʾ����
���ڲ�������
/******************************************/ 
void WriteData(char data);
void WriteData(char data)
 {
 //	int uu;
 	/*1.���ݵ����*/
 	GPIOC->MODER &= 0xffff0000;
 	GPIOC->MODER |= 0x00005555;					//DB7~DB0��8���ܽ�����Ϊ�����
 	GPIOC->ODR = (0x000000ff & (int)data);        //�������   @int =4byte
	
 	/*2.A0_LCD����*/
 	GPIOA->MODER &= 0xfff3ffff;  	//A0_LCD�ܽ�����Ϊ�����
 	GPIOA->MODER |= 0x00040000;
 	GPIOA->ODR &= ~GPIO_ODR_ODR_9; 		//A0_LCD�ܽ�����͵�ƽ
 	 	
 	/*3./CS_LCD��Ƭѡ����*/
 	GPIOA->MODER &= 0xfcffffff;  	// /CS_LCD�ܽ�����Ϊ�����
 	GPIOA->MODER |= 0x01000000; 
	GPIOA->ODR &= ~GPIO_ODR_ODR_12; 		// /CS_LCD�ܽ�����͵�ƽ

 	/*4./WR_LCD����*/
  GPIOA->MODER &= 0xffcfffff;  	// /WR_LCD�ܽ�����Ϊ�����
 	GPIOA->MODER |= 0x00100000;
	GPIOA->ODR &= ~GPIO_ODR_ODR_10;		// /WR_LCD�ܽ�����͵�ƽ

 	/*5.200nsʱ��ĵȴ�*/
  __nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();


	
  	/*6./WR_LCD����*/
 	GPIOA->ODR |= GPIO_ODR_ODR_10;		// /WR_LCD�ܽ�����ߵ�ƽ
 	
  	/*7./CS_LCD��Ƭѡ����*/
 	GPIOA->ODR |= GPIO_ODR_ODR_12;		// /CS_LCD�ܽ�����ߵ�ƽ
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();
 }
 

/******************************************/
  /*���ܣ���LCD����������ʾ�����ӳ���
��ڲ�������
���ڲ�����char�ͣ���LCD��ȡ�Ĳ�������ʾ����
/******************************************/ 
char ReadData();
char ReadData()
 {
 	char data;         //,uu;

 	/*0.��������*/                          //@2014-04-22
 	GPIOC->MODER &= 0xffff0000;				//DB7~DB0��8���ܽ�����Ϊ�����
 	
 	/*2.A0_LCD����*/
 	GPIOA->MODER &= 0xfff3ffff;  	//A0_LCD�ܽ�����Ϊ�����
 	GPIOA->MODER |= 0x00040000;
 	GPIOA->ODR |= GPIO_ODR_ODR_9; 		//A0_LCD�ܽ�����ߵ�ƽ
 	 	
 	/*3./CS_LCD��Ƭѡ����*/
 	GPIOA->MODER &= 0xfcffffff;  	// /CS_LCD�ܽ�����Ϊ�����
 	GPIOA->MODER |= 0x01000000; 
	GPIOA->ODR &= ~GPIO_ODR_ODR_12; 		// /CS_LCD�ܽ�����͵�ƽ

 	/*3./RD_LCD����*/
  GPIOA->MODER &= 0xff3fffff;  	// /RD_LCD�ܽ�����Ϊ�����
 	GPIOA->MODER |= 0x00400000;
	GPIOA->ODR &= ~GPIO_ODR_ODR_11;		// /RD_LCD�ܽ�����͵�ƽ
 
 	/*5.200nsʱ��ĵȴ�*/
  __nop();
	__nop();
	__nop();
	__nop();
	__nop();
	__nop();

	
 	/*5.���ݵĶ���*/
 	data = (char)(0x000000ff&(GPIOC->IDR));                   //��������
 	 	
  	/*6./RD_LCD����*/
 	GPIOA->ODR |= GPIO_ODR_ODR_11;		// /RD_LCD�ܽ�����ߵ�ƽ
 	
  	/*7./CS_LCD��Ƭѡ����*/
 	GPIOA->ODR |= GPIO_ODR_ODR_12;		// /CS_LCD�ܽ�����ߵ�ƽ
 	
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
  /*���ܣ���LCD�����������
��ڲ�����char�� O_X:���뷶Χ0~19�� LCD���п����20������
		  byte�� O_Y:���뷶Χ0~239��LCD��240��(���������)
		  word�� code1:���ֵĻ�������ֵľ���λ��
		  char�� neima:1��ʾcode1Ϊ�����룬0��ʾcode1Ϊ�ֿ����λ��	
���ڲ�������
/******************************************************************/ 
void CCW_PR1(char O_X,byte O_Y,word code1,char neima);
void CCW_PR1(char O_X,byte O_Y,word code1,char neima)
{
	unsigned char count1;
	word i,j;
	Read_Chinese_Code(code1,neima);	//���ֿ��ȡ���ֵĵ���
	i = PARA;	
	j = i*O_Y+O_X+0x04ce;   		//��ʾһ�������Ƶ���ʾ������ ��Ϊ320240��k=j*O_Y+O_X+0x04ce
	WriteCode(0x4f);   				//CSRDIR����(����)  
	
	for(i=0;i<2;i++)
	{
		WriteCode(0x46);      		//CSRW ����
		WriteData(j%256);     		//���ù���ַCSR
		WriteData(j/256);
		WriteCode(0x42);    		//MWRITE ���� 
		
		for(count1=0;count1<16;count1++)
		{
			WriteData(CGTAB[i][count1]); //д������ 
		}
		j=j+1;
	}
}                               

/***********************************************************************/
  /*���ܣ�����LCD���0~40���ַ�������ȡ����������40��16��8�̶��ַ�����
��ڲ�����char�� O_X:���뷶Χ0~39�� LCD���п����40���ַ�
		  char�� O_Y:���뷶Χ0~239��LCD��240��(���������)
		  char�� geshu
���ڲ�������
/***********************************************************************/ 
void CW_PR(unsigned char O_X,unsigned char O_Y,unsigned char geshu);
void CW_PR(unsigned char O_X,unsigned char O_Y,unsigned char geshu)
{
	unsigned char i;
	word j;
	i=PARA;
	j=i*O_Y+O_X;
	WriteCode(0x46);   			//CSRW ���� 
	WriteData(j%256);  			//���ù���ַCSR 
	WriteData(j/256);
	WriteCode(0x4c);   			//CSRDIR ���� 
	WriteCode(0x42);   			//MWRITE ���� 
	for(i=0;i<geshu;i++)
	{
	
		WriteData(CTAB[i]);  	//д������ 
	}
	for(i=0;i<geshu;i++)		//ÿ�������������
	{
		CTAB[i]=0x20;  
	}
 
}	    

/******************************************************************/
  /*���ܣ���LCD���һ��40���ַ�
��ڲ�����char�� O_X:���뷶Χ0~39�� LCD���п����40���ַ�
		  char�� O_Y:���뷶Χ0~29,  LCD��240��(���������)
���ڲ�������
/******************************************************************/ 
/*void CW_PR1(unsigned char O_X,unsigned char O_Y);
void CW_PR1(unsigned char O_X,unsigned char O_Y)
{
	unsigned char i;
	unsigned int j;
	i=PARA;
	j=i*O_Y+O_X;
	WriteCode(0x46);   			//CSRW ���� 
	WriteData(j%256);  			//���ù���ַCSR 
	WriteData(j/256);
	WriteCode(0x4c);   			//CSRDIR ���� 
	WriteCode(0x42);   			//MWRITE ���� 
	for(i=0;i<40;i++)
	{
		WriteData(CTAB1[i]);  	//д������ 
	}
	for(i=0;i<40;i++)			//ÿ�������������
	{
		CTAB1[i]=0x20;  
	}
 
}
    
/******************************************************************/
  /*���ܣ���LCD���һ��16���ַ�
��ڲ�����char�� O_X:���뷶Χ0~39�� LCD���п����40���ַ�
		  char�� O_Y:���뷶Χ0~29��LCD��240��(���������)
���ڲ�������
/******************************************************************/ 
/*void CW_PR2(unsigned char O_X,unsigned char O_Y);
void CW_PR2(unsigned char O_X,unsigned char O_Y)
{
	unsigned char i;
	unsigned int j;
	i=PARA;
	j=i*O_Y+O_X;
	WriteCode(0x46);  			//CSRW ����
	WriteData(j%256);  			//���ù���ַCSR 
	WriteData(j/256);
	WriteCode(0x4c);   			//CSRDIR ���� 
	WriteCode(0x42);   			//MWRITE ���� 
	for(i=0;i<16;i++)
	{
		WriteData(CTAB2[i]);  	//д������ 
	}

	for(i=0;i<16;i++)			//ÿ���������������� 
	{
		CTAB2[i]=0x20; 
	}
}
    
     
/******************************************************************/
  /*���ܣ���LCD���һ���ַ�
��ڲ�����char�� O_X:���뷶Χ0~39�� LCD���п����40���ַ�
		  char�� O_Y:���뷶Χ0~29�� LCD��240��(���������)
		  char�� CTAB:����ʾ���ַ�
���ڲ�������
/******************************************************************/ 
void CW_PR3(unsigned char O_X,unsigned char O_Y,unsigned char character);
void CW_PR3(unsigned char O_X,unsigned char O_Y,unsigned char character)
{
	unsigned char i;
	word j;
	i=PARA;
	j=i*O_Y+O_X;
	WriteCode(0x46);   /* CSRW ���� */
	WriteData(j%256);  /* ���ù���ַCSR */
	WriteData(j/256);

	WriteCode(0x4c);        /* CSRDIR ���� */
	WriteCode(0x42);        /* MWRITE ���� */ 
	WriteData(character);   /* д������ */

}
    
/******************************************************************/
  /*���ܣ���LCD���һ��8���ַ�
��ڲ�����char�� O_X:���뷶Χ0~39�� LCD���п����40���ַ�
		  char�� O_Y:���뷶Χ0~29��LCD��240��(���������)
���ڲ�������
/******************************************************************/ 
/*void CW_PR4(unsigned char O_X,unsigned char O_Y);
void CW_PR4(unsigned char O_X,unsigned char O_Y)
{
	unsigned char i;
	unsigned int j;
	i=PARA;
	j=i*O_Y+O_X;
	WriteCode(0x46);   			// CSRW ���� 
	WriteData(j%256);  			// ���ù���ַCSR 
	WriteData(j/256);
	WriteCode(0x4c);   			// CSRDIR ���� 
	WriteCode(0x42);   			// MWRITE ���� 
	for(i=0;i<8;i++)
	{
		WriteData(CTAB[i]);  	// д������ 
	}
	for(i=0;i<8;i++)
	{
		CTAB[i]=0x20;  		// ÿ������������� 
	}     
}   
   
    

/********************************************/
  /*���ܣ���LCDָ��λ�û�һ����
��ڲ�����int�� O_X:���뷶Χ0~319�� 
		  int�� O_Y:���뷶Χ0~239��
���ڲ�������
/********************************************/ 
void W_DOT(sword O_X,sword O_Y)
{
	unsigned char i,j,dat;
	word k;         //,uu;
	char temp;
	j = PARA;
	i = O_X % 8;
	O_X = O_X / 8;
	k = j*O_Y+O_X+0x04ce;   /*д��λ��ַ�ı��ʽ*/
	i = 7-i;
	O_Y = 0x01<<i;			/* ������ʾλ */                          
	WriteCode(0x4f);
	WriteCode(0x46);  		/* ���ù���ַ */
	WriteData(k%256); 		/* �������ַ */
	WriteData(k/256);
	WriteCode(0x43);  		/* MREAD ���� */
	dat=ReadData();   		/* ��ȡ��ǰ��ʾ���� */
	WriteCode(0x46);  		/* ���ù���ַ */
	WriteData(k%256);  		/* �������ַ */
	WriteData(k/256);
	WriteCode(0x42);  		/* MWRITE ���� */
	temp=(char)(dat|O_Y);
	WriteData(temp);  		/* д��ϳ����� */
}
  
/********************************************/
  /*���ܣ���LCDָ��λ����һ����
��ڲ�����int�� O_X:���뷶Χ0~319�� 
		  int�� O_Y:���뷶Χ0~239��
���ڲ�������
/********************************************/ 
void W_CLEARDOT(sword O_X,sword O_Y)
{
	unsigned char i,j,dat;
	word k;
	char temp;
	j=PARA;
	i=O_X%8;
	O_X=O_X/8;
	k=j*O_Y+O_X+0x04ce;   	/*д��λ��ַ�ı��ʽ*/
	                    
	WriteCode(0x4f);
	WriteCode(0x46);  		/* ���ù���ַ */
	WriteData(k%256); 		/* �������ַ */
	WriteData(k/256);
	i=7-i;
	O_Y=0x01<<i;
	O_Y=~O_Y;				/* ������ʾλ */
	WriteCode(0x43);  		/* MREAD ���� */
	dat=ReadData();   		/* ��ȡ��ǰ��ʾ���� */
	WriteCode(0x46);  		/* ���ù���ַ */
	WriteData(k%256);  		/* �������ַ */
	WriteData(k/256);
	WriteCode(0x42);  		/* MWRITE ���� */
	temp=(char)(dat&O_Y);
	WriteData(temp);        //(dat&O_Y); 2014-04-23 	/* д��ϳ����� */
}


/********************************************/
  /*���ܣ���ȫ��������
��ڲ�������
���ڲ�������
/********************************************/ 
void CLEAR();
void CLEAR()
{
	word i,j;
	WriteCode(0x4c);   		/* CSRDIR ���� */
	WriteCode(0x46);   		/* CSRW ���� */
	WriteData(0x00);   		/* ���ò������ָ���8λ */
	WriteData(0x00);   		/* ���ò������ָ���8λ */
	WriteCode(0x42);   		/* MWRITE ���� */
	for(j=6;j<2195;j++)     /*��64K����ʾ�洢��*/
	{
		for(i=0;i<41;i++)   /*д��һ��*/
		{
			WriteData(0x00);/* д������ */
		}
	}
}



 
/********************************************/
  /*���ܣ���һ���Ͷ���������
��ڲ�������
���ڲ�������
/********************************************/ 
void CLEAR1();
void CLEAR1()
{
	word i,j;
	W_DOT(0,0);
	if(STATE==1) IntialLCD(1);
	else IntialLCD(0);				//LCD��ʼ��
	WriteCode(0x4c);   				/* CSRDIR ���� */
	WriteCode(0x46);   				/* CSRW ���� */
	WriteData(0x00);   				/* ���ò������ָ���8λ */
	WriteData(0x00);   				/* ���ò������ָ���8λ */
	WriteCode(0x42);   				/* MWRITE ���� */
	for(j=0;j<270;j++)       		/*����ʾ��һ�Ͷ��Ĵ洢��*/
	{

		for(i=0;i<41;i++)     		/*д��һ��*/
		{
			if(j==30||j==31||j==32||j==(LANGUAGE?52:47)||j==34||j==35||j==33||j==269||j==260) WriteData(0xff);
			else WriteData(0x00); 	/* д������,��Ӣ�ĵ���������������ʾ��17�У�Ӣ����ʾ22�� */
		}
	}
}


/********************************************/
  /*���ܣ������ߺ���(���󷽷�)
��ڲ�����O_XS:������ʼ��(0,319)
		  O_XE:������ֹ��(O_XS,319)
		  O_Y: Y��λ��(0,239) 
���ڲ�������
/********************************************/ 
void W_XLINE(sword O_XS,sword O_XE,sword O_Y)
{
	sword j;
	for(j=O_XS;j<O_XE+1;j++)    /* ��һ��ֱ�ߣ���������O_X ����������O_Y */
	{
		W_DOT(j,O_Y);          	/* ������ӳ���  */
		if(j>319)break;         /* �����������������п�320����ֹͣ*/
	}
}

/********************************************/
  /*���ܣ�ȡ�����ߺ��� (���󷽷�)
��ڲ�����O_XS:������ʼ��(0,319)
		  O_XE:������ֹ��(O_XS,319)
		  O_Y: Y��λ��(0,239) 
���ڲ�������
/********************************************/ 
void W_CLEARXLINE(sword O_XS,sword O_XE,sword O_Y)
{
	sword j;
	for(j=O_XS;j<O_XE+1;j++)        /* ��һ��ֱ�ߣ���������O_X ����������O_Y */
	{
		W_CLEARDOT(j,O_Y);          /* ������ӳ���  */
		if(j>319)break;          	/* �����������������п�320����ֹͣ*/
	}
}

/********************************************/
  /*���ܣ������ߺ���(���󷽷�)
��ڲ�����O_X: X���λ��(0,319)
		  O_YS:������ʼ��(0,239)
		  O_YE:������ֹ��(O_YS,239) 
���ڲ�������
/********************************************/ 
void W_YLINE(sword O_X,sword O_YS,sword O_YE)
{
	sword j;
	for(j=O_YS;j<O_YE+1;j++)    	/* ��һ��ֱ�ߣ���������O_X ����������O_Y */
	{
		W_DOT(O_X,j);          		/* ������ӳ���  */
		if(j>239)break;          	/* �����������������п�240����ֹͣ*/
	}
}

/********************************************/
  /*���ܣ���ȡ�����ߺ���(���󷽷�)
��ڲ�����O_X: X���λ��(0,319)
		  O_YS:������ʼ��(0,239)
		  O_YE:������ֹ��(O_YS,239) 
���ڲ�������
/********************************************/ 
void W_CLEARYLINE(sword O_X,sword O_YS,sword O_YE)
{
	sword j;
	for(j=O_YS;j<O_YE+1;j++)         /* ��һ��ֱ�ߣ���������O_X ����������O_Y */
	{
		 W_CLEARDOT(O_X,j);          /* ������ӳ���  */
		 if(j>239)break;             /* �����������������п�240����ֹͣ*/
	}
}


/********************************************/
  /*���ܣ������ߺ���(�ֽڷ���)
��ڲ�����O_XS:������ʼ��(0,39)
		  O_XE:������ֹ��(O_XS,39)
		  O_Y: Y��λ��(0,239) 
���ڲ�������
/********************************************/ 
void XLINE(sword O_XS,sword O_XE,sword O_Y)
{
	sword j,k;
	j=PARA;
	k=j*O_Y+O_XS+0x04ce;   	/*д��λ��ַ�ı��ʽ*/
	WriteCode(0x4c);   		/* CSRDIR ���� */
    WriteCode(0x46);   		/* CSRW ���� */
    WriteData(k%256);   	/* ���ò������ָ���8λ */
    WriteData(k/256);   	/* ���ò������ָ���8λ */
    WriteCode(0x42);   		/* MWRITE ���� */		
	for(j=O_XS;j<O_XE+1;j++)/*��һ��ֱ�ߣ���������O_X ����������O_Y */
	{
	 	WriteData(0xff);    /* ������ӳ���  */      
	}
}

/********************************************/
  /*���ܣ���ȡ�����ߺ���(�ֽڷ���)
��ڲ�����O_XS:������ʼ��(0,39)
		  O_XE:������ֹ��(O_XS,39)
		  O_Y: Y��λ��(0,239) 
���ڲ�������
/********************************************/ 
void CLEARXLINE(sword O_XS,sword O_XE,sword O_Y)
{
	sword j,k;
	j=PARA;
	k=j*O_Y+O_XS+0x04ce;   	/*д��λ��ַ�ı��ʽ*/
	WriteCode(0x4c);   		/* CSRDIR ���� */
    WriteCode(0x46);   		/* CSRW ���� */
    WriteData(k%256);   	/* ���ò������ָ���8λ */
    WriteData(k/256);   	/* ���ò������ָ���8λ */
    WriteCode(0x42);   		/* MWRITE ���� */		
	for(j=O_XS;j<O_XE+1;j++)/*��һ��ֱ�ߣ���������O_X ����������O_Y */
	{
	 	WriteData(0x00);    /* ������ӳ���  */      
	}
}

/********************************************/
  /*���ܣ��������Ӳ˵��߿���(������Ӣ��) 
��ڲ�������
���ڲ�������
/********************************************/   
void WFRAME();
void WFRAME()
{
    sword i;
    if(LANGUAGE==0||LANHELP==2)	//Ӣ�Ĵ��ڣ����Ľ����µ�LANHELP==2�Ա���Ӣ�ĵĴ��ڴ�С
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
 	    if(LANHELP==3)		//���Ĳ˵��Ŀ�ͼ�ӳ���,//��LANHELP==3ʱ����ʾ�󴰿�
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
			for(i=0;i<3;i++)	//���Ĳ˵�����ͨ��
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
  /*���ܣ��嵯���Ӳ˵�������(������Ӣ��) 
��ڲ�������
���ڲ�������
/********************************************/   
void CLEAR2();
void CLEAR2()
{	
	unsigned char i,O_Y;
	word j;
            	unsigned char CNENYNODE=((STATE==1||STATE==11||STATE==12||((State13parameter==0)&&(STATE==13))||((State14parameter==0)&&(STATE==14)))?(LANGUAGE?98:60):(LANGUAGE?98:64));  //�ֱ��Ӧ��Ӣ�ĵĵ�������
             	unsigned char CNENYLINESTART=((STATE==1||STATE==11||STATE==12||((State13parameter==0)&&(STATE==13))||((State14parameter==0)&&(STATE==14)))?(LANGUAGE? 8: 9):(LANGUAGE?10:13));	//�ֱ��Ӧ��Ӣ�ĵ���ʼ��
            	unsigned char CNENYLINEEND=	((STATE==1||STATE==11||STATE==12||((State13parameter==0)&&(STATE==13))||((State14parameter==0)&&(STATE==14)))?(LANGUAGE?15:13):(LANGUAGE?22:20));
//	unsigned char CNENYNODE=(((State13parameter==0)||(State14parameter==0))?(LANGUAGE?98:60):(LANGUAGE?98:64));  //�ֱ��Ӧ��Ӣ�ĵĵ�������
//	unsigned char CNENYLINESTART=(((State13parameter==0)||(State14parameter==0))?(LANGUAGE? 8: 9):(LANGUAGE?10:13));	//�ֱ��Ӧ��Ӣ�ĵ���ʼ��
//	unsigned char CNENYLINEEND=	(((State13parameter==0)||(State14parameter==0))?(LANGUAGE?15:13):(LANGUAGE?22:20));



	for(O_Y=CNENYLINESTART;O_Y<=CNENYLINEEND;O_Y++) /*����ʾ��һ�Ĵ洢��*/
	{
		i=PARA;
		j=i*O_Y+8;
		WriteCode(0x46);   		/* CSRW ���� */
		WriteData(j%256);  		/* ���ù���ַCSR */
		WriteData(j/256);
		WriteCode(0x4c);   		/* CSRDIR ���� */
		WriteCode(0x42);   		/* MWRITE ���� */
		for(i=0;i<18;i++)
		{
			WriteData(0x00);  	/* д������ */
		}
	}

	for(i=0;i<18;i++)   		/*����ʾ�����Ĵ洢��*/
	{
		WriteCode(0x4f);   		/* CSRDIR ���� */
		WriteCode(0x46);   		/* CSRW ���� */
		if(LANGUAGE==0)
		{	
			WriteData(126+i);  	/* ����Ӣ�ĵĹ���ַCSR */
			WriteData(0x15);	
		}
		else 
		{
			WriteData(156+i);  	/* �������ĵĹ���ַCSR */
			WriteData(0x12);			
		}
		WriteCode(0x42);   		/* MWRITE ���� */          
		for(j=0;j<=CNENYNODE;j++)	/*д��һ��*/
		{
			WriteData(0x00);  	/* д������ */     		
		}  
	}
}

/********************************************/
  /*���ܣ��嵯������Ϣ��ʾ�˵�������(������Ӣ��) 
��ڲ�������
���ڲ�������
/********************************************/   
void ClrMsgtip();
void ClrMsgtip()
{	
	unsigned char i,O_Y;
	word j;
	for(O_Y=1;O_Y<=3;O_Y++)     /*����ʾ��һ�Ĵ洢��*/
	{
		i=PARA;
		j=i*O_Y+23;
		WriteCode(0x46);   		/* CSRW ���� */
		WriteData(j%256);  		/* ���ù���ַCSR */
		WriteData(j/256);
		WriteCode(0x4c);   		/* CSRDIR ���� */
		WriteCode(0x42);   		/* MWRITE ���� */
		for(i=0;i<17;i++)
		{
			WriteData(0x00);  	/* д������ */
		}
	}
	for(i=8;i<32;i++)   		/*����ʾ�����Ĵ洢��*/
	{
		j=PARA*i+23+0x04ce;
		WriteCode(0x46);   		/* CSRW ���� */	
		WriteData(j%256);  		/* ����Ӣ�ĵĹ���ַCSR */
		WriteData(j/256);		
		WriteCode(0x4c);   		/* CSRDIR ���� */
		WriteCode(0x42);   		/* MWRITE ���� */ 
		for(j=0;j<=17;j++)     	/*д��һ��*/
		{
			WriteData(0x00);  	/* д������ */     		
		}  
	}
}
  



/********************************************/
  /*���ܣ������Ӳ˵�ǰ��Ӧ��������ݱ���
  		  ��ʱ����дͼ����ʾ���ı�������
  		  ��ͼ�ε����ݺ��٣�ֻ������ʱ��
  		  �ϼ���  
��ڲ�������
���ڲ�������
/********************************************/     
void ProtectData();
void ProtectData()
{
	unsigned char character[18],i,O_Y,cn[98];
	word j,l;
             	unsigned char CNENYLINESTART=((STATE==1||STATE==11||STATE==12||((State13parameter==0)&&(STATE==13))||((State14parameter==0)&&(STATE==14)))?(LANGUAGE? 8: 9):(LANGUAGE?10:13));		//�ֱ��Ӧ��Ӣ�ĵ���ʼ��
               	unsigned char CNENYLINEEND=((STATE==1||STATE==11||STATE==12||((State13parameter==0)&&(STATE==13))||((State14parameter==0)&&(STATE==14)))?(LANGUAGE?15:13):(LANGUAGE?22:20));
	for(O_Y=CNENYLINESTART;O_Y<=CNENYLINEEND;O_Y++)      /*����ַ���ʾ�������ݱ���*/
	{
		i=PARA;
		j=i*O_Y+8;
		WriteCode(0x46);   				/* CSRW ���� */
		WriteData(j%256);  				/* ���ù���ַCSR */
		WriteData(j/256);
		WriteCode(0x4c);   				/* CSRDIR ���� */
		WriteCode(0x43);   				/* MREAD ���� */
		for(i=0;i<18;i++)
		{
			character[i]=ReadData();  	/* �������� */
		}
		j=PARA*(O_Y-CNENYLINESTART)+0x5000; //��ŵ�ַ��ram��20k�ռ俪ʼ
		WriteCode(0x46);   				/* CSRW ���� */
		WriteData(j%256);  				/* ���ù���ַCSR */
		WriteData(j/256);
		WriteCode(0x4c);   				/* CSRDIR ���� */
		WriteCode(0x42);   				/* MRITER ���� */
		for(i=0;i<18;i++)
		{
			WriteData(character[i]);  	/* д������ */
		}	     
	}

//	if(LANGUAGE==1)
//	{
		for(i=0;i<18;i++)   	/*������ʾ���������ݱ���*/
		{
			WriteCode(0x46);   	/* CSRW ���� */
			WriteData(156+i); 	/* �������ĵĹ���ַCSR */
			WriteData(0x12);			
			WriteCode(0x4f);   	/* CSRDIR ���� */
			WriteCode(0x43);   	/* MREAD ���� */          
			for(j=0;j<98;j++)   /*д��һ��*/
			{
				cn[j]=ReadData();  /* �������� */     		
			}
			l=98*i+0x6000;		//��ŵ�ַ��Һ��ram��0x6000��ʼ
			WriteCode(0x46);   	/* CSRW ���� */
			WriteData(l%256);  	/* ���ù���ַCSR */
			WriteData(l/256);
			WriteCode(0x4c);   	/* CSRDIR ���� */
			WriteCode(0x42);   	/* MRITER ���� */
			for(j=0;j<98;j++)
			{
				WriteData(cn[j]);  /* д������ */
			}	     	
		}		  
//	}
}



/********************************************/
  /*���ܣ��Ӳ˵����غ�ԭ��������д��ԭλ��  
��ڲ�������
���ڲ�������
/********************************************/     
void RecoverData();
void RecoverData()
{

	unsigned char character[18],i,O_Y,cn[98];
   word j,l;   
                   unsigned char CNENYLINESTART=((STATE==1||STATE==11||STATE==12||((State13parameter==0)&&(STATE==13))||((State14parameter==0)&&(STATE==14)))?(LANGUAGE? 8: 9):(LANGUAGE?10:13));	//�ֱ��Ӧ��Ӣ�ĵ���ʼ��
                   unsigned char CNENYLINEEND=((STATE==1||STATE==11||STATE==12||((State13parameter==0)&&(STATE==13))||((State14parameter==0)&&(STATE==14)))?(LANGUAGE?15:13):(LANGUAGE?22:20)); 
  //   CLEAR2();
    for(O_Y=CNENYLINESTART;O_Y<=CNENYLINEEND;O_Y++)     /*����ַ���ʾ�������ݱ���*/
	{

		i=PARA;

		j=PARA*(O_Y-CNENYLINESTART)+0x5000; 			//��ŵ�ַ��ram��20k�ռ俪ʼ
		WriteCode(0x46);   				/* CSRW ���� */
		WriteData(j%256);  				/* ���ù���ַCSR */
		WriteData(j/256);
		WriteCode(0x4c);   				/* CSRDIR ���� */
		WriteCode(0x43);   				/* MREAD ���� */
		for(i=0;i<18;i++)
		{
			character[i]=ReadData();  	/* д������ */
		}	     

		j=PARA*O_Y+8;
		WriteCode(0x46);   				/* CSRW ���� */
		WriteData(j%256);  				/* ���ù���ַCSR */
		WriteData(j/256);
		WriteCode(0x4c);  	 			/* CSRDIR ���� */
		WriteCode(0x42);   				/* MRITER ���� */
		for(i=0;i<18;i++)
		{
			WriteData(character[i]);  	/* д������ */
		}	  	  
	}
	  
//	if(LANGUAGE==1)
//	{
		for(i=0;i<18;i++)   			/*������ʾ���������ݱ���*/
		{
			l=98*i+0x6000;				//��ŵ�ַ��Һ��ram��0x6000��ʼ
			WriteCode(0x46);   			/* CSRW ���� */
			WriteData(l%256);  			/* ���ù���ַCSR */
			WriteData(l/256);
			WriteCode(0x4c);   			/* CSRDIR ���� */
			WriteCode(0x43);   			/* MRead ���� */
			for(j=0;j<98;j++)
			{
				cn[j]=ReadData();	  	/* д������ */
			}
				     	
			WriteCode(0x46);   			/* CSRW ���� */
			WriteData(156+i);  			/* �������ĵĹ���ַCSR */
			WriteData(0x12);			
			WriteCode(0x4f);   			/* CSRDIR ���� */
			WriteCode(0x42);   			/* MWRITE ���� */          
			for(j=0;j<98;j++)     		/*д��һ��*/
			{
				WriteData(cn[j]);  		/* �������� */     		
			}	     	
		}		  
//	}
}


/********************************************/
  /*���ܣ���ʼ��Һ������   
��ڲ�������
���ڲ�������
/********************************************/ 
void IntialLCD(char ilcd)
{
	unsigned char i;
	FPGARW(1800)= 0x0001;


//  GPIO_B_DDR|=GPIO_B_DDR_DD8_MASK;		//rsto�ܽ�����Ϊ�����
// 	GPIO_B_DR&=~GPIO_B_DR_D8_MASK;
// 	GPIO_B_DR|=GPIO_B_DR_D8_MASK;			//���Ϊ1
	
	WriteCode(0x40);   		/* SYSTEM SET���� */		
	for(i=0;i<8 && ilcd!=2;i++)
	{
	  
	  if(ilcd==1&&i==2)WriteData(0x0b);
	  else 
	  	WriteData(SYSTAB[i]); /* д����� */
	}
	WriteCode(0x44);   		/* SCROLL���� */		
	for(i=0;i<10;i++)
	{
	  WriteData(SCRTAB[i]); /* д����� */
	}
	WriteCode(0x5a);   		/* HDOT SCR ���� */
	WriteData(0x00);   		/* ���ò���P1 */
	WriteCode(0x5b);   		/* OVLAY ���� */
	WriteData(0x00);   		/* ���ò���:��ʾһ,����Ϊ�ı����� */
//	if(ilcd==0)
//	CLEAR();       			/* �������ӳ��� */
	WriteCode(0x59);   		/* ��ʾ״̬���� */		
	WriteData(0x54);   		/* ���ò���:��ʾһ����������ʾ */
}


/***************************************/
/*  ���� �����ķ����� 
��ڲ��� O_X(0~39)
		 O_Y(0~239) LANGUAGE==0;Ӣ��
		 O_Y(0~29)  LANGUAGE==1;����
���ڲ��� ��
/***************************************/
void W_HDIAMOND(unsigned char O_X,unsigned char O_Y);
void W_HDIAMOND(unsigned char O_X,unsigned char O_Y)
{
	word i,j;
	i=O_X*8;
   	j=((LANGUAGE&LANHELP)? O_Y:(O_Y*((STATE==11||STATE==12||((State13parameter==0)&&(STATE==13))||((State14parameter==0)&&(STATE==14)))?12:8)));	//��ʹ��LANGUAGEΪ1������£���LANHELPΪ0����ѡ�����԰�Ӣ�Ĳ˵������ʾ

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
/*  ���� ��ʵ�ķ�����   
��ڲ��� O_X(0~39)
		 O_Y(0~239) LANGUAGE==0;Ӣ��
		 O_Y(0~29)  LANGUAGE==1;����
���ڲ��� ��
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
  /*���ܣ���δ����Ϣ��Ǻ���  
��ڲ�����byte�ͣ�O_X(0~39)
		  byte�ͣ�O_Y(0~29) 
���ڲ�������
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
  /*���ܣ���δ����Ϣ��Ǻ���  
��ڲ�����byte�ͣ�O_X(0~39)
		  byte�ͣ�O_Y(0~29) 
���ڲ�������
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
/*    ��������Ǻ���   */
/***********************/
W_LOCK(unsigned char O_X,unsigned char O_Y);
W_LOCK(unsigned char O_X,unsigned char O_Y)
{
	word i,j;
	i=O_X*8;
	j=O_Y*8;
	
}

/***********************/
/*   ��δ������Ǻ���  */
/***********************/
W_UNLOCK();
W_UNLOCK()
{

}


/********************************************/
  /*���ܣ������ƶ���Ǻ��� 
��ڲ�����byte�ͣ�O_X(0~39)
		  byte�ͣ�O_Y(0~29) 
���ڲ�������
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
  /*���ܣ������ƶ���Ǻ��� 
��ڲ�����byte�ͣ�O_X(0~39)
		  byte�ͣ�O_Y(0~29) 
���ڲ�������
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
  /*���ܣ���������ƶ���Ǻ��� 
��ڲ�����byte�ͣ�O_X(0~39)
		  byte�ͣ�O_Y(0~29) 
���ڲ�������
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
  /*���ܣ���ѡ����Ǻ��������ǹ��� 
��ڲ�����byte�ͣ�O_X(0~39)
		  byte�ͣ�O_Y(0~29) 
���ڲ�������
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
  /*���ܣ���ȡ��ѡ����Ǻ��������ǹ��� 
��ڲ�����byte�ͣ�O_X(0~39)
		  byte�ͣ�O_Y(0~29) 
���ڲ�������
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
  /*���ܣ�ʮ���ƶ�λ��תΪ��λascii��
��ڲ�����byte�ͣ�O_X(0~39)
		  byte�ͣ�O_Y(0~29)
		  byte�ͣ�demical��ʮ���ƵĶ�λ�� 
���ڲ�������
/********************************************/ 
void DISASCII(unsigned char O_X,unsigned char O_Y,unsigned char demical);
void DISASCII(unsigned char O_X,unsigned char O_Y,unsigned char demical)//�����Ӳ˵���һ��
{
	unsigned char i;
	word j;
	unsigned char ascii[2];
	ascii[1]=demical%10+48;		//��λ��
	ascii[0]=demical/10+48;		//ʮλ��			
	i=PARA;
	j=i*O_Y+O_X;
	WriteCode(0x46);   			/* CSRW ���� */
	WriteData(j%256);  			/* ���ù���ַCSR */
	WriteData(j/256);
	WriteCode(0x4c);		   	/* CSRDIR ���� */
	WriteCode(0x42);   			/* MWRITE ���� */
	for(i=0;i<2;i++)
	{
		WriteData(ascii[i]);  	/* д������ */
	}
 
}   


/********************************************/
  /*���ܣ�ʮ���ƶ�λ��תΪ��λascii��
��ڲ�����byte�ͣ�O_X(0~39)
		  byte�ͣ�O_Y(0~29)
		  word�ͣ�demical��ʮ���Ƶ���λ�� 
���ڲ�������
/********************************************/ 
void DISASCIII(unsigned char O_X,unsigned char O_Y,word demical);
void DISASCIII(unsigned char O_X,unsigned char O_Y,word demical)//�����Ӳ˵���һ��
{
	unsigned char i;
	word j;
	unsigned char ascii[3];
	ascii[2]=demical%10+48;						//��λ��
	ascii[0]=demical/100+48;					//��λ��
	ascii[1]=(demical/10)%10+48;            	//ʮλ��
	i=PARA;
	j=i*O_Y+O_X;
	WriteCode(0x46);   							/* CSRW ���� */
	WriteData(j%256);  							/* ���ù���ַCSR */
	WriteData(j/256);
	WriteCode(0x4c);   							/* CSRDIR ���� */
	WriteCode(0x42);   							/* MWRITE ���� */
	for(i=0;i<3;i++)
	{
		WriteData(ascii[i]);  					/* д������ */
	}
 
}


/********************************************/
  /*���ܣ����ƶ������Ǻ���
��ڲ�����byte�ͣ�O_X(0~39)
		  byte�ͣ�O_Y(0~29)
���ڲ�������
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
  /*���ܣ�����ƶ������Ǻ���
��ڲ�����byte�ͣ�O_X(0~39)
		  byte�ͣ�O_Y(0~29)
���ڲ�������
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
  /*���ܣ���������Ϣ��ʾ�˵��߿���
��ڲ�������
���ڲ�������
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
  /*���ܣ������Ϣͷ�ļ����� 
��ڲ�����char�� num:��ɾ����Ϣͷ�ļ���LCDͷ��λ��
���ڲ�������
/************************************************/ 
void W_CLEARMSGTOP(char num);
void W_CLEARMSGTOP(char num)
{
	char i;
	/*һ�����ַ���ʾ�����*/
	for(i=0;i<40;i++)
	{
	 CTAB[i]=0x20;  
	}
	CW_PR(0,num,40);
	CW_PR(0,num+1,40);
	CW_PR(0,num+2,40);
	/*������������ʾ�����*/
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
  /*���ܣ���LCDָ��λ����ʾ����ģʽ(��Ӣ�Ĺ���)
��ڲ�����x_zhongwen(0~39)  ���Ĳ˵�����ʾ������x����ʼλ��
		  y_zhongwen(0~239) ���Ĳ˵�����ʾ������y����ʼλ��
		  x_yingwen(0~39)   ���Ĳ˵�����ʾ������x����ʼλ��
		  y_yingwen(0~29)   ���Ĳ˵�����ʾ������y����ʼλ��			
���ڲ�������
/*********************************************************/ 
void W_Mode(byte x_zhongwen,byte y_zhongwen,byte x_yingwen,byte y_yinwen);
void W_Mode(byte x_zhongwen,byte y_zhongwen,byte x_yingwen,byte y_yinwen)
{
	
	  if(LANGUAGE==1)	//���Ĳ˵�
	  {
	  	if(Mode==0)		//��ʾ�Զ�
	  	{
	 		CCW_PR1(x_zhongwen,y_zhongwen,0xd7d4,1);
 			CCW_PR1(x_zhongwen+2,y_zhongwen,0xb6Af,1);	  		
	  	}
	  	
	  	else			//��ʾ�ֶ�
	  	{
	 		CCW_PR1(x_zhongwen,y_zhongwen,0xcad6,1);
 			CCW_PR1(x_zhongwen+2,y_zhongwen,0xb6Af,1);	  		
	  	}
	  }
	  
	  else				//Ӣ�Ĳ˵�
	  {
	  	if(Mode==0)		//��ʾ��AUTO
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

	if(LANGUAGE==0)		//Ӣ��
	{
		CW_PR3(x_yingwen,y_yinwen,'(');
		DISASCII(x_yingwen+1,y_yinwen,current_area);
		CW_PR3(x_yingwen+3,y_yinwen,')');
	}
	else				//����
	{
		CW_PR3(x_zhongwen,y_zhongwen,'(');
		DISASCII(x_zhongwen+1,y_zhongwen,current_area);
		CW_PR3(x_zhongwen+3,y_zhongwen,')');		
	}	
}

/*************************************************/
  /*���ܣ�д��Ϣͷ�ļ����� 
��ڲ�����int��  num:��Ϣͷ�ļ�������������λ��
		  char�� pos:��LCDҳ������ʼ����
		  char�� mod:0��ʾ�洢��Ϣ��1��ʾ������Ϣ
���ڲ�������
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
	for(i=0;i<4;i++) 			//��ʾ��Ϣ��Ƿ���
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
						case(34):CW_PR3(3+i,pos,'H');break;//' "  '˫����
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
						case(39):CW_PR3(3+i,pos,'S');break;//' ' '������
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
	switch(temp->frequency)		//��ʾƵ��
	{
		case 1:					//1����518
			{
				CW_PR3(9,pos,'5');
				CW_PR3(10,pos,'1');
				CW_PR3(11,pos,'8');
				CW_PR3(12,pos,' ');
				CW_PR3(13,pos,' ');
				CW_PR3(14,pos,' ');	
			} break;
		case 2:					//2����490
			{
				CW_PR3(9,pos,'4');
				CW_PR3(10,pos,'8');
				CW_PR3(11,pos,'6');
				CW_PR3(12,pos,' ');
				CW_PR3(13,pos,' ');
				CW_PR3(14,pos,' ');	
			} break;
		case 3:					//3����4209.5
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
//	DISASCII(17,pos,temp->length);	 //��ʾ��Ϣ����
	DISASCII(21,pos,temp->date[0]);  //��ʾ��
	CW_PR3(23,pos,'/');	
	DISASCII(24,pos,temp->date[1]);  //��ʾ��
	CW_PR3(26,pos,'/');
	DISASCII(27,pos,temp->date[2]);	 //��ʾ��
	
	DISASCII(31,pos,temp->time[0]);	 //��ʾСʱ
	CW_PR3(33,pos,':');	
	DISASCII(34,pos,temp->time[1]);	 //��ʾ����
	
	if(LANGUAGE==0)		//Ӣ�Ľ���
	{
		CTAB[0]='S';	CTAB[1]='T';	CTAB[2]='A';	CTAB[3]='T';//��ʱ�����ǰ�̨
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
		
		
		
		CTAB[0]='M';	CTAB[1]='S';	CTAB[2]='G';	CTAB[3]=' ';//��ʱ��������Ϣ���
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
	
	else 				//���Ľ���
	{
 		CCW_PR1(3,(pos+1)*8,0xb0b6,1);	//��ʾ����"��̨:"
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
		
 		
  		
 //		CCW_PR1(21,(pos+1)*8,0xd0c5,1);	//����������"��Ϣ���:"
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

	
	
	if(temp->read==1)	W_NEWMESSAGE(1,pos);		//����Ϣ���ϱ�ǣ��������
	else W_CLEARMESSAGE(1,pos);
	
	
	if(mod==0)
	{
		if(temp->lock==1)	CW_PR3(1,pos+2,'S');	//��������������ǣ��������
		else CW_PR3(1,pos+2,' ');	
	}

	
	if(temp->select==1)	W_CHOOSED(1,pos+2);			//��ѡ���ϸ�ѡ��ǣ���֮���
	else W_CANCALCHOOSED(1,pos+2);
}



/********************************************/
  /*���ܣ�Automode�����к�����̨����ʾ
��ڲ�����byte�ͣ�navarea ����ʾ�ĺ���
���ڲ�������
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
	for(i=0;i<13;i++)				//��벿�ֵ���ʾ
	{
		j=PARA*(5+2*i)+5;
		WriteCode(0x46);   			// CSRW ���� 
		WriteData(j%256);  			// ���ù���ַCSR 
		WriteData(j/256);
		WriteCode(0x4c);		   	// CSRDIR ���� 
		WriteCode(0x42);   			// MWRITE ���� 
		for(l=0;l<14;l++)
		{
			WriteData(Rxstation[navarea1][i][l]);  	// д������ 
		}		
	}

 	for(i=13;i<26;i++)				//�Ұ벿�ֵ���ʾ
	{
		j=PARA*(5+2*(i-13))+24;
		WriteCode(0x46);   			// CSRW ���� 
		WriteData(j%256);  			// ���ù���ַCSR 
		WriteData(j/256);
		WriteCode(0x4c);		   	// CSRDIR ���� 
		WriteCode(0x42);   			// MWRITE ���� 
		for(l=0;l<14;l++)
		{
			WriteData(Rxstation[navarea1][i][l]);  	// д������ 
		}		
	}
} 


/****************************************************/	
	/*  �洢��Ϣ��ʾ����һ��(Ӣ��) */
	/*��ڲ���1:��������*/
	/*��ڲ���2:����ʾ�ַ���ͷָ��*/
	/*���ڲ�������ʾ�걾���ַ�������ָ����¸�����ʾ�ַ��ĵ�ַ*/	
/****************************************************/
char *MessageDisLine(byte YLine,char *Ldisads);
char *MessageDisLine(byte YLine,char *Ldisads)
{
/*	byte i;
	for(i=1;i<38;i++)	//һ����ʾ�ĺ��᷶Χ��1~37
	{
		if(*Ldisads==NULL) break;	//����NULL���ַ�����ʾ��ϣ�������ʾ
		if(*Ldisads==10)	
			{Ldisads++;break;}	//�������з���ֱ�ӽ���������ʾ��ָ��ָ���¸��ַ���	
		if(*Ldisads==9) 	
			{i+=3;Ldisads++;continue;}	//����TAB��ֱ�ӿ��ĸ��ַ�����λ�ã���������ѭ������ָ���¸��ַ���
	
		CW_PR3(i,YLine,*Ldisads);
		Ldisads++;	
	}
	
	return(Ldisads);*/
}				


/****************************************************/	
	/*  �洢��Ϣ��ʾ����һҳ(Ӣ��)  */
	/*��ڲ���:����ʾ�ַ���ͷָ��*/
	/*���ڲ���������ʾ�ַ��������һ���ַ���ַ*/	
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
	}	//ÿ����ʾʱ������յ�ǰ����
	
	MesDisFir=DisAds;	//��ȡ��ǰ��ʾ�ַ�����ʾ���׵�ַ
	for(i=3;i<28;i+=2)	//����ʾ��������Χ��3~27��13��
	{
		
		Ldisads=MessageDisLine(i,Ldisads);
		if(i==3)	MesDisDw=Ldisads;//��ȡ��ǰ��ʾҳ�ڶ��е��׵�ַ
		if(*Ldisads==NULL) break;//�����ص���NULLָ�룬˵�����ַ�������ʾ��ϣ�����ѭ��
				
	}
	MesDisLast=Ldisads;//��ȡ��ǰ��ʾҳ���һ���ַ�����һ���ַ���ַ*/
}

/****************************************************/	
	/*  �洢��Ϣ��ʾ����һҳ(Ӣ��)  */
	/*��ڲ���:����ʾ���ĵ���ʼ����*/
	/*���ڲ���������ʾ�ַ��������һ���ַ���ַ*/	
/****************************************************/
void MessageDisplay(word startlen);
void MessageDisplay(word startlen)
{
	
	char rn=0,i,j,*temp,line,tt=0,l=0,num_tt=0;
	word k=0;
	word *temp2;
//	sword aa,bb;
//	CLEARXLINE();		//�ֽڷ���
//	W_CLEARXLINE();		//���󷽷�
/*	for(i=3;i<28;i++)
	{
		for (j=1;j<38;j++)
		{
			CW_PR3(j,i,' ');	
		}
	}*/
//	for(aa=18;aa<226;aa++)
//		W_CLEARXLINE(3,308,aa);	//ÿ����ʾʱ������յ�ǰ����
//	unsigned int i,j;
	if((Messagesavetop[(uint32)Messagetoprank[Messagenownumber]].frequency==2))
	{
		line=1;
		for(i=1;i<11;i++)
		{
			l=line*20+8;		//�м��3������
			j=2;
			for(tt=0;tt<18;tt++)
			{
				CCW_PR1(j,l,0xa1a1,1);	
				j=j+2;		
			}
		}//ÿ����ʾʱ������յ�ǰ����
		line=1;
		for(i=1;i<11;i++)
		{
			if(k+startlen>LINE) break;
			else
			{
				l=line*20+8;		//�м��3������
				j=2;
				temp2=LinePoint2[startlen+k];
				tt=-1;                               //    ? @2014-04-23
				num_tt=0;
				while(num_tt<18)
//				for(num_tt=0;num_tt<18;num_tt++)
				{
					tt++;
					if(*(temp2+tt)==13)//�������з���ֱ�ӽ���������ʾ��ָ��ָ���¸��ַ���
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
						{j+=3;temp++;continue;}	//����TAB��ֱ�ӿ��ĸ��ַ�����λ�ã���������ѭ������ָ���¸��ַ���
		*///δ���	
		
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
					if(*(temp2+tt)==NULL) break;	//���ı���ʾĩλ��ֱ������
				
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
		}//ÿ����ʾʱ������յ�ǰ����
		for(i=2;i<19;i++)
		{

			if(k+startlen>LINE) break;
			else
			{
				temp=LinePoint[startlen+k];
				for(j=1;j<38;j++)
				{
				
					if((*temp==13)||(*temp==10)) break;//�������з���ֱ�ӽ���������ʾ��ָ��ָ���¸��ַ���
				
					if(*temp==9) 	
						{j+=3;temp++;continue;}	//����TAB��ֱ�ӿ��ĸ��ַ�����λ�ã���������ѭ������ָ���¸��ַ���
					
					if(*temp==NULL) break;	//���ı���ʾĩλ��ֱ������
					
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


