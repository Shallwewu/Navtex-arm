#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "Eprom.h"
#include "code.h"

//********************************************/
/*	���ܣ��������ѡ�������ʾ
��ڲ�������
���ڲ�������
/*********************************************/
void RecoverFactory_Diamond();
void RecoverFactory_Diamond()
{
	if(BUFFER2[0]==0)	//����һѡ��
	{
	    W_DIAMOND(12,LANGUAGE?132:17);
	    W_HDIAMOND(12,LANGUAGE?152:18);
	}
	
	else				//�����ѡ��
	{
		W_DIAMOND(12,LANGUAGE?152:18);
    	W_HDIAMOND(12,LANGUAGE?132:17);	
	}	
}


//********************************************/
/*	���ܣ�RecoverFactory �������ʾ
��ڲ�������
���ڲ�������
/*********************************************/
void RecoverFactory_Paintintial();
void RecoverFactory_Paintintial()
{
	unsigned char i;
//	CLEAR2();		//�����Ӳ˵������������
	WFRAME();		//�����Ӳ˵���ͼ��ʾ
	if(LANGUAGE==0)	//Ӣ��
	{

	   	CTAB[2]='S';   CTAB[3]='U';    CTAB[4]='R';     CTAB[5]='E';
	   	CTAB[7]='R';   CTAB[8]='E'; 
	   	CTAB[9]='C';   CTAB[10]='O';   CTAB[11]='V';	CTAB[12]='E';
	   	CTAB[13]='R';  CTAB[14]='?';
	    CW_PR(9,15,15);	//��ͷ SETUP

	    CTAB[5]='O';  CTAB[6]='K';
	    CW_PR(9,17,15);	//��һ������:OK
	      
	    CTAB[5]='C';  CTAB[6]='A';  CTAB[7]='N';  CTAB[8]='C';  CTAB[9]='E'; 
	    CTAB[10]='L';
	    CW_PR(9,18,14);	//�ڶ������ݣ�CANCEL
	    
	}
	
	else			//����
	{
 		CCW_PR1(13,104,0xc8b7,1);	//��һ����ʾ����"ȷ�ϻָ�"
 		CCW_PR1(15,104,0xc8cf,1);
  		CCW_PR1(17,104,0xbbd6,1);
  		CCW_PR1(19,104,0xb8b4,1);		
		
 		CCW_PR1(14,128,0xc8b7,1);	//�ڶ�����ʾ����"ȷ��"
		CCW_PR1(16,128,0xc8cf,1);

  		
   		CCW_PR1(14,148,0xc8a1,1);	//��������ʾ����"ȡ��"
		CCW_PR1(16,148,0xcffb,1);

 	}

	RecoverFactory_Diamond();		//���ÿ�ͼ��ʾ����
	
}  

//********************************************/
/*	���ܣ����°�����������ѡ������ѡ����
��ڲ�������
���ڲ�������
/*********************************************/
void RecoverFactory_Updn();
void RecoverFactory_Updn() 
{
	if (G_Key==UP||G_Key==DOWN)
	{
		G_Key=0;
		BUFFER2[0]=(BUFFER2[0]+1)%2;
		RecoverFactory_Diamond();	//���ÿ�ͼ��ʾ����
	}
	
} 


//**************************************************************/
/*	���ܣ�ENT��������������ѡ�������ѡ������
��ڲ�������
���ڲ�������
/***************************************************************/
void RecoverFactory_Dealing();
void RecoverFactory_Dealing()
{
	if (G_Key==ENT)
	{
		G_Key=0;
		FLAG=0;	
		if(BUFFER2[0]==0)		//�ָ��������ã����ص���Ϣ���Ľ���	
		{
	//   	COPCTL&=~COPCTL_CEN_MASK;
			IntialOriginal();		//���ջ���ʼ������
	//		COPCTL|=COPCTL_CEN_MASK;
		}
		
		if(BUFFER2[0]==1)
		{
			STATE=44;				//Maintain״̬Ϊ13
			State44parameter=10;	//��ڲ���0����ʾ���Ӳ˵�����
			BUFFER2[0]=0;
		}
	}
}

//**************************************************************/
/*	���ܣ���������
��ڲ�������
���ڲ�������
/***************************************************************/
void RunRecoverFactory()
{

	unsigned char first1=0;
	unsigned char first2=0;
	RecoverFactory_Paintintial();

	while(FLAG)
	{	
		RecoverFactory_Updn();
		RecoverFactory_Dealing();
		run_tip();
	}
  	
}