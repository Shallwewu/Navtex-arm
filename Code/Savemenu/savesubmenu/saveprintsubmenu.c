#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "code.h"
/*********************************************/
/*	���ܣ���ӡ�Ӳ˵�SavePrintSubMenu�������ʾ
��ڲ�������
���ڲ�������
/*********************************************/
void SavePrintSubMenu_Paintintial();
void SavePrintSubMenu_Paintintial()
{
	byte i;

	if(LANGUAGE==0)	//Ӣ�Ĳ˵�
	{

		  
		CTAB[4]='*';  CTAB[5]='P';   CTAB[6]='R';  CTAB[7]='I'; 
		CTAB[8]='N';  CTAB[9]='T'; CTAB[10]='*';
		CW_PR(9,14,11);	//��һ����ʾ����"PRINT"

		CTAB[5]='S';  CTAB[6]='I';   CTAB[7]='N';   CTAB[8]='G'; 
		CTAB[9]='L';  CTAB[10]='E';  CTAB[12]='P';  CTAB[13]='R'; 
		CTAB[14]='I';  	 
		CW_PR(8,16,15);	//�ڶ�����ʾ����"SINGLE PRI"

		CTAB[5]='S';  CTAB[6]='T';   CTAB[7]='A';   CTAB[8]='T'; 
		CTAB[9]='E';  CTAB[11]='P';  CTAB[12]='R'; 
		CTAB[13]='I'; 
		CW_PR(8,17,14);	//��������ʾ����"STATE PRI"

		CTAB[5]='P';  CTAB[6]='I';   CTAB[7]='T';   CTAB[8]='C'; 
		CTAB[9]='H';  CTAB[11]='P';  CTAB[12]='R';  CTAB[13]='I';
		CW_PR(8,18,14);	//��������ʾ����"PITCH PRI"		
	}

	else			//���Ĳ˵�
	{
		CCW_PR1(15,100,0xb4f2,1);	//��һ����ʾ����"��ӡ"
		CCW_PR1(17,100,0xd3a1,1);
		
		CCW_PR1(13,118,0xb5a5,1);	//�ڶ�����ʾ����"������Ϣ"
		CCW_PR1(15,118,0xccf5,1);
		CCW_PR1(17,118,0xd0c5,1);
		CCW_PR1(19,118,0xcfa2,1);


				
		CCW_PR1(13,136,0xd7b4,1);	//��������ʾ����"״̬"
		CCW_PR1(15,136,0xccac,1);

				
		CCW_PR1(13,154,0xc5fa,1);	//��������ʾ����"������"
		CCW_PR1(15,154,0xb4a6,1);
		CCW_PR1(17,154,0xc0ed,1);		
	}


	WFRAME();						//�����Ӳ˵���ͼ��ʾ
	W_DIAMOND(11,LANGUAGE?122:16);	//ѡ�������ʾ
	W_HDIAMOND(11,LANGUAGE?140:17);
	W_HDIAMOND(11,LANGUAGE?158:18);
	
	if(BUFFER2[0]!=0)				//��֤ѡ�����ӦBUFFER2[0]����ֵ
	{
		W_DIAMOND(11,LANGUAGE?(122+BUFFER2[0]*18):(16+BUFFER2[0]));
		W_HDIAMOND(11,LANGUAGE?122:16);	
	}
	
}

//********************************************/
/*	���ܣ����°�����������ѡ������ѡ��
��ڲ�������
���ڲ�������
/*********************************************/
void SavePrintSubMenu_Updn();
void SavePrintSubMenu_Updn()
{
	if(BUFFER2[0]>=0&&BUFFER2[0]<=2)
	{
		if(G_Key == UP)
		{
			G_Key=0;
			if(BUFFER2[0]>0)
			{
				BUFFER2[0]--;
				W_DIAMOND(11,LANGUAGE?(122+BUFFER2[0]*18):(16+BUFFER2[0]));	
		    	W_HDIAMOND(11,LANGUAGE?(140+BUFFER2[0]*18):(17+BUFFER2[0]));
			}
		}
		
		if(G_Key == DOWN)
		{
			G_Key=0;
			if(BUFFER2[0]<2)
			{			
				BUFFER2[0]++;
				W_DIAMOND(11,LANGUAGE?(122+BUFFER2[0]*18):(16+BUFFER2[0]));
		    	W_HDIAMOND(11,LANGUAGE?(104+BUFFER2[0]*18):(15+BUFFER2[0]));				
			}			
		}
	}

}

//**************************************************************/
/*	���ܣ�CLR������������������һ���˵��洢�˵�SaveSubMenu
��ڲ�������
���ڲ�������
/***************************************************************/
void SavePrintSubMenu_Return();
void SavePrintSubMenu_Return()
{
	if(G_Key == CLR)
	{
		G_Key=0;		//��������
		BUFFER2[0]=0;	//���˵�ʹ�õ�ȫ�ֱ�������
		FLAG=0;			//����ѭ��
		STATE=20;		//SaveSubMenu��״̬Ϊ20
	}
}

//*****************************************************/
/*	���ܣ�ENT��������������ѡ��ѡ����в���
��ڲ�������
���ڲ�������
/*****************************************************/
void SavePrintSubMenu_Dealing();
void SavePrintSubMenu_Dealing()
{
	if(G_Key == ENT&&STATE==201)
	{

		FLAG=0;		//����ѭ��
		switch(BUFFER2[0])
		{
			case 0:	
			{
				STATE=13;			//����Message_PrintSubmenu����
				State13parameter=1;	//��ڲ���1����ӡ������Ϣ
				break;
			}
			case 1:
			{
				STATE=13;			//����Message_PrintSubmenu����
				State13parameter=2;	//��ڲ���2����ӡ״̬		
				break;
			}
			default:
			{
				STATE=2010;			//����SavePitchPrint��״̬2010
				break;
			}
		}
		G_Key=0;	//��������
		BUFFER2[0]=0;
	}
}



/*********************************************************/
/*	���ܣ���ӡѡ���ѡ�񣬰���������״̬��������
          ʹ��ȫ�ֱ���BUFFER2[0]:0 ���� 1 ״̬ 2 ������
��ڲ�������
���ڲ�������
/*********************************************************/
void RunSavePrintSubMenu()
{
    maske=0;
    maskc=0;
	SavePrintSubMenu_Paintintial();
	while(FLAG)
	{
		SavePrintSubMenu_Updn();
		SavePrintSubMenu_Return();
		SavePrintSubMenu_Dealing();
		run_tip();
	}
}