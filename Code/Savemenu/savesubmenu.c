#include <stdio.h>
#include <stdlib.h>
#include  "run.h"
#include "define.h"
#include "lcddrive.h"	
#include "code.h"
/*********************************************/
/*	���ܣ�SaveSubMenu�������ʾ
��ڲ�������
���ڲ�������
/*********************************************/
void SaveSubMenu_Paintintial();
void SaveSubMenu_Paintintial()
{
	byte i;


	if(LANGUAGE==0)	//Ӣ�Ľ���
	{

		  
		CTAB[4]='*';  CTAB[5]='S';   CTAB[6]='E';  CTAB[7]='T'; 
		CTAB[9]='U';  CTAB[10]='P'; CTAB[11]='*';
		CW_PR(8,14,12);	//��һ����ʾ����"*SET UP*"

		  
		CTAB[5]='S';  CTAB[6]='O';  CTAB[7]='R';  CTAB[8]='T';  
		CW_PR(8,16,9);	//�ڶ�����ʾ����"SORT"

		  
		CTAB[5]='L';  CTAB[6]='O';  CTAB[7]='C';  CTAB[8]='K'; 
		CW_PR(8,17,9);	//��������ʾ����"LOCK"
		  
		CTAB[5]='P';  CTAB[6]='R';  CTAB[7]='I';  CTAB[8]='N';  CTAB[9]='T';
		CW_PR(8,18,10);	//��������ʾ����"PRINT"		
	}
	
	else			//���Ĳ˵�
	{

		CCW_PR1(13,104,0xc5c5,1);	//��һ����ʾ����"����"
		CCW_PR1(15,104,0xd0f2,1);
				
		CCW_PR1(13,124,0xcbf8,1);	//�ڶ�����ʾ����"����"
		CCW_PR1(15,124,0xb6a8,1);
				
		CCW_PR1(13,144,0xb4f2,1);	//��������ʾ����"��ӡ"
		CCW_PR1(15,144,0xbd3a1,1);		
	}
	
	WFRAME();						//�����Ӳ˵���ͼ��ʾ
	
	for(i=1;i<3;i++)				//ѡ�������ʾ������ѡ��ѡ���ѡ����Ӻ�
	{
		W_HDIAMOND(11,LANGUAGE?(108+20*i):(16+i));
	}

	W_DIAMOND(11,LANGUAGE?108:16);

	
	if(BUFFER1[0]==1)				//��֤ѡ�����ӦBUFFER1[0]����ֵ
	{
		W_HDIAMOND(11,LANGUAGE?108:16);
		W_DIAMOND(11,LANGUAGE?128:17);	
	}
	
	if(BUFFER1[0]==2) 
	{
		W_DIAMOND(11,LANGUAGE?148:18);
		W_HDIAMOND(11,LANGUAGE?108:16);
	}

}

//********************************************/
/*	���ܣ����°�����������ѡ������ѡ��洢
          ��BUFFER1[0]������LCD����ʾ 
��ڲ�������
���ڲ�������
/*********************************************/
void SaveSubMenu_Updn();
void SaveSubMenu_Updn()
{
	
		if(G_Key == UP||G_Key == DOWN)
		{
			if(G_Key == UP)	BUFFER1[0]=(BUFFER1[0]+2)%3;	
			else BUFFER1[0]=(BUFFER1[0]+1)%3;	
			
			if(BUFFER1[0]==0)
			{
				W_DIAMOND(11,LANGUAGE?108:16);
				W_HDIAMOND(11,LANGUAGE?128:17);
				W_HDIAMOND(11,LANGUAGE?148:18);	
			}

			if(BUFFER1[0]==1)
			{
				W_HDIAMOND(11,LANGUAGE?108:16);
				W_DIAMOND(11,LANGUAGE?128:17);
				W_HDIAMOND(11,LANGUAGE?148:18);
			}
			
			if(BUFFER1[0]==2) 
			{
				W_HDIAMOND(11,LANGUAGE?108:16);
				W_HDIAMOND(11,LANGUAGE?128:17);
				W_DIAMOND(11,LANGUAGE?148:18);
			}
			
			G_Key=0;	//��������			
		}
}

//**************************************************************/
/*	���ܣ�CLR������������������һ���˵��洢�˵� SaveMenu
��ڲ�������
���ڲ�������
/***************************************************************/
void SaveSubMenu_Return();
void SaveSubMenu_Return()
{
	if(G_Key == CLR)
	{
		BUFFER1[0]=0;		//���˵�ʹ��ȫ�ֱ�������
		FLAG=0;				//����ѭ��
		STATE=2;			//SaveMenu״̬Ϊ2
		State2parameter=10;	//��ڲ���10����ʾ���Ӳ˵�����
		G_Key=0;			//��������
	}
}

//*****************************************************/
/*	���ܣ�ENT��������������ѡ��ѡ����в���
��ڲ�������
���ڲ�������
/*****************************************************/
void SaveSubMenu_Dealing();
void SaveSubMenu_Dealing()
{
	if(G_Key == ENT&&STATE==20)
	{

		FLAG=0;			//����ѭ��
		switch(BUFFER1[0])
		{
			case 0:					//�����������
			{
				STATE=202;			//SaveRankMenu״̬Ϊ202	
				State202parameter=0;//��ڲ���Ϊ0����Ϊ�洢�˵����Ӳ˵�	
				break;
			}
			case 1:					//������������
			{
				STATE=200;			//SaveLockMenu״̬Ϊ200	
				State200parameter=0;//��ڲ���0����Ϊ������ѡ����ʹ��	
				break;
			}
			default:				//���д�ӡ����
			{
				STATE=201;			//SavePrintSubMenu״̬Ϊ201
				break;
			}
		}

		G_Key=0;		//��������	
	}
}

//**************************************************************/
/*	���ܣ��洢�˵�SaveMenu������Ӳ˵�������������������ӡ
		  ȫ�ֱ���BUFFER1[0]��¼��ǰ��ѡ����ѡ��
��ڲ�������
���ڲ�������
/***************************************************************/
void RunSaveSubMenu()
{
    maske=0;
    maskc=0;
	SaveSubMenu_Paintintial();
	while(FLAG)
	{
		SaveSubMenu_Updn();
		SaveSubMenu_Return();
		SaveSubMenu_Dealing();
		run_tip();
	}
}