#include <stdio.h>
#include <stdlib.h>
#include  "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "code.h"


/*********************************************/
/*	���ܣ����������Ӳ˵�LockSubMenu����ʾ
��ڲ�������
���ڲ�������
/*********************************************/
void LockSubMenu_Paintintial();
void LockSubMenu_Paintintial()
{


	WFRAME();

	if(LANGUAGE==0)	//Ӣ�Ĳ˵�
	{
		CTAB[4]='*';  CTAB[5]='S';   CTAB[6]='E';  CTAB[7]='T'; 
		CTAB[9]='U';  CTAB[10]='P'; CTAB[11]='*';
		CW_PR(9,15,12);	//��һ����ʾ����"SETUP"

		CTAB[5]='S';  CTAB[6]='O';  CTAB[7]='R';  CTAB[8]='T';  
		CW_PR(9,17,9);	//�ڶ�����ʾ����"SORT"
		  
		CTAB[5]='U';  CTAB[6]='N';  CTAB[7]='L';  CTAB[8]='O';  CTAB[9]='C';
		CTAB[10]='K';	//��������ʾ����"UNLOCK"
		CW_PR(9,18,11);		
	}

	else			//���Ĳ˵�
	{
 		CCW_PR1(15,104,0xc9e8,1);	//��һ����ʾ����"����"
 		CCW_PR1(18,104,0xd6c3,1);
  		
   		CCW_PR1(14,128,0xc5c5,1);	//�ڶ�����ʾ����"����"
		CCW_PR1(16,128,0xd0f2,1);
				
 		CCW_PR1(14,148,0xbde2,1);	//��������ʾ����"����"
		CCW_PR1(16,148,0xcbf8,1);
 
 	}

	if(BUFFER1[0]==0)	//����һѡ��
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

/*********************************************/
/*	���ܣ����°�����������ѡ������ѡ��
��ڲ�������
���ڲ�������
/*********************************************/
void LockSubMenu_Updn();
void LockSubMenu_Updn()
{
	if(G_Key == UP||G_Key == DOWN)
	{

		BUFFER1[0]=(BUFFER1[0]+1)%2;	//BUFFER1[0]��¼ѡ��ѡ����
		if(BUFFER1[0] == 0)
		{
		    W_DIAMOND(12,LANGUAGE?132:17);
		    W_HDIAMOND(12,LANGUAGE?152:18);
		}
		if(BUFFER1[0] ==1)
		{	
			W_DIAMOND(12,LANGUAGE?152:18);
	    	W_HDIAMOND(12,LANGUAGE?132:17);				
		}
		G_Key=0;						//��������	
	}
}


/***************************************************************/
/*	���ܣ�CLR������������������һ���˵������˵�SaveMenu
��ڲ�������
���ڲ�������
/***************************************************************/
void LockSubMenu_Return();
void LockSubMenu_Return()
{
	if(G_Key == CLR)
	{

		BUFFER1[0]=0;		//���˵�ʹ��ȫ�ֱ�������
		FLAG=0;				//����ѭ��
		STATE=2;			//SaveMenu״̬Ϊ2
		State2parameter=10;	//��ڲ���10�����Ӳ˵�����
		G_Key=0;			//��������
	}
}

/*****************************************************/
/*	���ܣ�ENT�����������������������������
��ڲ�������
���ڲ�������
/*****************************************************/
void LockSubMenu_Dealing();
void LockSubMenu_Dealing()

{
	if(G_Key == ENT&&STATE==30)
	{

		FLAG=0;				//����ѭ��
		switch(BUFFER1[0])
		{
			case 0:
			{
				STATE=202;	//SaveRankSubMenu��״̬Ϊ202
				State202parameter=1;	//��ڲ���Ϊ1�������������˵�����
				break;
			}
			case 1:
			{
				STATE=300;	//LockLockSubMenu��״̬Ϊ300
				State300parameter=0;	//��ڲ���0
				break;
			}			
		}
		G_Key=0;			//��������	
	}
}

/***************************************************************/
/*	���ܣ������˵�SaveMenu������Ӳ˵����������򣬽���
		  ȫ�ֱ���BUFFER1[0]��¼��ǰ��ѡ����ѡ��
��ڲ�������
���ڲ�������
/***************************************************************/
void RunLockSubMenu()
{
    maske=0;
    maskc=0;
	LockSubMenu_Paintintial();
	
	while(FLAG)
	{
 //       COPCTR=0xAAAA;
 //       COPCTR=0x5555;
		LockSubMenu_Updn();
		LockSubMenu_Return();
		LockSubMenu_Dealing();
		run_tip();
	}
}