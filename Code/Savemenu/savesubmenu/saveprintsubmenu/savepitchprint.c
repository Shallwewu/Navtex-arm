#include <stdio.h>
#include <stdlib.h>
#include  "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "code.h"
/********************************************************/
/*���ܣ�������ѡ���ӡ��ѡ����ʾ
��ڲ�������
���ڲ�������
/********************************************************/
void SavePitchPrint_Paintintial();
void SavePitchPrint_Paintintial()
{
	byte i;
//	CLEAR2();		//�����Ӳ˵������������
	WFRAME();		//�����Ӳ˵��߿����ʾ

	if(LANGUAGE==0)
	{
		CTAB[4]='*';  CTAB[5]='P';   CTAB[6]='I';  CTAB[7]='T'; 
		CTAB[8]='C';  CTAB[9]='H'; CTAB[10]='*';
		CW_PR(9,14,11);	//��һ����ʾ����"PITCH"


		  
		CTAB[3]='A';  CTAB[4]='L';   CTAB[5]='L';   CTAB[6]='S'; 
		CTAB[7]='A';  CTAB[8]='V';   CTAB[9]='E';   CTAB[11]='M'; 
		CTAB[12]='S'; CTAB[13]='G'; 	 
		CW_PR(9,16,14);	//�ڶ�����ʾ����"ALLSAVE MSG"

		  
		CTAB[3]='A';  CTAB[4]='L';   CTAB[5]='L';   CTAB[6]='L'; 
		CTAB[7]='O';  CTAB[8]='C';   CTAB[9]='K';   CTAB[11]='M'; 
		CTAB[12]='S'; CTAB[13]='G'; 
		CW_PR(9,17,14);	//��������ʾ����"ALLLOCK MSG"


		  
		CTAB[3]='M';  CTAB[4]='A';   CTAB[5]='N';   CTAB[6]='U'; 
		CTAB[7]='A';  CTAB[8]='L';   
		CW_PR(9,18,9);	//��������ʾ����"MANUAL"		
	}

	else
	{
		CCW_PR1(14,100,0xc5fa,1);	//��һ����ʾ����"������"
		CCW_PR1(16,100,0xb4a6,1);
		CCW_PR1(18,100,0xc0ed,1);
				
		CCW_PR1(12,118,0xb4e6,1);	//�ڶ�����ʾ����"�洢��Ϣ"
		CCW_PR1(14,118,0xb4A2,1);
		CCW_PR1(16,118,0xd0c5,1);
		CCW_PR1(18,118,0xcfa2,1);


				
		CCW_PR1(12,136,0xcbf8,1);	//��������ʾ����"������Ϣ"
		CCW_PR1(14,136,0xb6a8,1);
		CCW_PR1(16,136,0xd0c5,1);
		CCW_PR1(18,136,0xcfa2,1);
				
		CCW_PR1(12,154,0xc8cb,1);	//��������ʾ����"�˹���ѡ"
		CCW_PR1(14,154,0xb9a4,1);
		CCW_PR1(16,154,0xb8b4,1);
		CCW_PR1(18,154,0xd1a1,1);		
	}


	W_DIAMOND(10,LANGUAGE?122:16);	//ѡ�������ʾ
	W_HDIAMOND(10,LANGUAGE?140:17);
	W_HDIAMOND(10,LANGUAGE?158:18);	
	if(BUFFER3[0]!=0)			//��֤ѡ�����ӦBUFFER3[0]����ֵ
	{
	
		W_DIAMOND(10,LANGUAGE?(122+BUFFER3[0]*18):(16+BUFFER3[0]));
		W_HDIAMOND(10,LANGUAGE?122:16);	
	}
	
}

/*********************************************/
/*	���ܣ����°�����������ѡ������ѡ��
��ڲ�������
���ڲ�������
/*********************************************/
void SavePitchPrint_Updn();
void SavePitchPrint_Updn()
{
	if(BUFFER3[0]>=0&&BUFFER3[0]<=2)
	{
		if(G_Key == UP)
		{
			G_Key=0;
			if(BUFFER3[0]>0)
			{
				BUFFER3[0]--;
				W_DIAMOND(10,LANGUAGE?(122+BUFFER3[0]*18):(16+BUFFER3[0]));	
		    	W_HDIAMOND(10,LANGUAGE?(140+BUFFER3[0]*18):(17+BUFFER3[0]));	
			}
		}
		if(G_Key == DOWN)
		{
			G_Key=0;
			if(BUFFER3[0]<2)
			{			
				BUFFER3[0]++;
				W_DIAMOND(10,LANGUAGE?(122+BUFFER3[0]*18):(16+BUFFER3[0]));
		    	W_HDIAMOND(10,LANGUAGE?(104+BUFFER3[0]*18):(15+BUFFER3[0]));
			}			
		}
	}
}

/***************************************************************/
/*	���ܣ�CLR������������������һ���˵��洢�˵�SavePrintSubMenu
��ڲ�������
���ڲ�������
/***************************************************************/
void SavePitchPrint_Return();
void SavePitchPrint_Return()
{
	if(/*G_Key == LEFT || */G_Key == CLR)
	{
		G_Key=0;		//��������
		BUFFER3[0]=0;	//���˵�ʹ�õ�ȫ�ֱ�������
		STATE=201;		//SavePrintSubMenu��״̬Ϊ201
		FLAG=0;			//����ѭ��
	}
}

/*****************************************************/
/*	���ܣ�ENT��������������ѡ��ѡ����в���
��ڲ�������
���ڲ�������
/*****************************************************/
void SavePitchPrint_Dealing();
void SavePitchPrint_Dealing()
{
	if(G_Key == ENT)
	{
		G_Key=0;	//��������
		FLAG=0;		//����ѭ��
		switch(BUFFER3[0])
		{
			case 0:
			{
				STATE=2011;				//SaveAllMessage��״̬Ϊ2011
				break;
			}
			
			case 1:
			{
				STATE=2011;				//SaveAllMessage��״̬Ϊ2011
				break;
			}
			
			default:
			{
				STATE=200;				//SaveLockSubMenu��״̬Ϊ200
				State200parameter=1;	//��ڲ���1��ʾ��ʱSaveLockSubMenu��Ϊ��ӡ��ѡ����
				break;
			}
		}
	}
}


/*********************************************************/
/*	���ܣ���ӡ��Χ��ѡ�񣺴洢��Ϣ��������Ϣ����ѡ��ӡ
          ʹ��ȫ�ֱ���BUFFER3[0]:0�洢��Ϣ 1 ������Ϣ
          2 ��ѡ��ӡ
��ڲ�������
���ڲ�������
/*********************************************************/
void RunSavePitchPrint()
{

    maske=0;
    maskc=0;
	SavePitchPrint_Paintintial();
	while(FLAG)
	{
		SavePitchPrint_Updn();
		SavePitchPrint_Return();
		SavePitchPrint_Dealing();
		run_tip();
	}
  	
}