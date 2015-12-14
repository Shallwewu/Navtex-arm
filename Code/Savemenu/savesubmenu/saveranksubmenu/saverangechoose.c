#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "Eprom.h"
#include "code.h"

/*********************************************/
/*	���ܣ�SaveRangeChoose�������ʾ
��ڲ�������
���ڲ�������
/*********************************************/
void SaveRangeChoose_Paintintial();
void SaveRangeChoose_Paintintial()
{
	byte i;
	WFRAME();		//�����Ӳ˵���ͼ��ʾ
	if(LANGUAGE==0)	//Ӣ�Ĳ˵�����ͷ��ʾRANGE SET
	{
		CTAB[3]='*';  CTAB[4]='R';   CTAB[5]='A'; CTAB[6]='N'; 
		CTAB[7]='G';  CTAB[8]='E';  CTAB[10]='S';  CTAB[11]='E'; CTAB[12]='T';	CTAB[13]='*'; 
		CW_PR(8,14,14);	
	}
	  
	else			//���Ĳ˵�����ͷ��ʾ����Χѡ��
	{
		CCW_PR1(13,104,0xb7b6,1);
		CCW_PR1(15,104,0xcea7,1);
		CCW_PR1(17,104,0xd1a1,1);
		CCW_PR1(19,104,0xd4f1,1);		
	}
	  
	CTAB[5]='A';  CTAB[6]='L';  CTAB[7]='L';  
	CW_PR(8,16,8);	//ѡ��һ ALL

	CTAB[5]='5';   CTAB[6]='1';   CTAB[7]='8';   CTAB[8]='K';
	CTAB[9]='H';   CTAB[10]='Z';  
	CW_PR(8,17,11);	//ѡ��� 518KHZ
	  
	CTAB[5]='4';   CTAB[6]='8';   CTAB[7]='6';  CTAB[8]='K';
	CTAB[9]='H';  	CTAB[10]='Z';  
	CW_PR(8,18,11);	//ѡ���� 490KHZ

	CTAB[5]='4';   CTAB[6]='2';   CTAB[7]='0';  CTAB[8]='9';
	CTAB[9]='.';   CTAB[10]='5';  CTAB[11]='K'; CTAB[12]='H'; CTAB[13]='Z'; 
	CW_PR(8,19,14);	//ѡ���� 4209.5KHZ

	W_DIAMOND(11,16);	//ѡ�������ʾ������ѡ��ѡ���ѡ����Ӻ�
	W_HDIAMOND(11,17);
	W_HDIAMOND(11,18);
	W_HDIAMOND(11,19);
}
/*********************************************/
/*	���ܣ����°�����������ѡ������ѡ��洢
          ��BUFFER3[0]������LCD����ʾ 
��ڲ�������
���ڲ�������
/*********************************************/
void SaveRangeChoose_Updn();
void SaveRangeChoose_Updn()
{
	if(BUFFER3[0]>=0&&BUFFER3[0]<=3)
	{
		if(G_Key == UP)
		{
			G_Key=0;
			if(BUFFER3[0]>0)
			{
				BUFFER3[0]--;
				W_DIAMOND(11,BUFFER3[0]+16);
				W_HDIAMOND(11,BUFFER3[0]+17);
			}
		}
		else if(G_Key == DOWN)
		{
			if(BUFFER3[0]<3)
			{			
				BUFFER3[0]++;
				W_DIAMOND(11,BUFFER3[0]+16);
				W_HDIAMOND(11,BUFFER3[0]+15);
			}			
			G_Key=0;
		}
	}
}
//*******************************************/
/*	���ܣ�CLR������������������һ���˵�
��ڲ�������
���ڲ�������
/********************************************/
void SaveRangeChoose_Return();
void SaveRangeChoose_Return()
{
	if(G_Key == CLR)
	{
		LANHELP=1;		//LANHELP�ָ�����ʼֵ
		BUFFER3[0]=0;	//������ʹ��ȫ�ֱ�������
		FLAG=0;			//����ѭ��
		STATE=202;		//SaveRankSubmenu״̬Ϊ202
		State202parameter=Rankback;
		G_Key=0;		//��������		
/*		if(Rankback==0)	State202parameter=0;	//SaveRankSubmenu��Ϊ�洢�˵����ӽ���
		else State202parameter=1;				//SaveRankSubmenu��Ϊ�����˵����ӽ���*/
	}
}


//*****************************************************/
/*	���ܣ�ENT��������������ѡ��ѡ������������
��ڲ�������
���ڲ�������
/*****************************************************/
void SaveRangeChoose_Dealing();
void SaveRangeChoose_Dealing()
{
	if(G_Key == ENT&&STATE==2020)
	{

		LANHELP=1;		//LANHELP�ָ���ʼֵ
		FLAG=0;			//����ѭ��
		STATE=2021;		//SaveRanking״̬Ϊ2021
		G_Key=0;		//��������
/*		Messageinfo.rankmode=BUFFER2[0];	//�ѵ�ǰ������״̬д����Ϣ��¼�ṹ��
		Write_Char_Eprm(MESSAGEINFO+20,Messageinfo.rankmode);//����Ϣ��¼�ṹ��д��Eprom*/	
	}
}


//**************************************************************/
/*	���ܣ�����Χ��ѡ��ȫ�ֱ���BUFFER3[0]������¼����Χ
          0 ��ʾALL 1��ʾ518 2��ʾ490 3��ʾ4209.5
          LANHELP��Ϊ0��ʾѡ���������Ĳ˵���Ҳ��Ӣ�ĵ���ʾ
          
��ڲ�������
���ڲ�������
/***************************************************************/
void RunSaveRangeChoose()
{
    maske=0;
    maskc=0;
	LANHELP=0;
	SaveRangeChoose_Paintintial();
	while(FLAG)
	{
		SaveRangeChoose_Updn();
		SaveRangeChoose_Return();
		SaveRangeChoose_Dealing();
		run_tip();
	}
}