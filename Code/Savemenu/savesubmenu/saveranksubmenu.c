#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"
#include "lcddrive.h"
#include "Eprom.h"
#include "code.h"
//********************************************/
/*	���ܣ�SaveRankSubMenu�������ʾ
��ڲ�������
���ڲ�������
/*********************************************/
void SaveRankSubMenu_Paintintial();
void SaveRankSubMenu_Paintintial()
{
	WFRAME();		//�����Ӳ˵���ͼ��ʾ
	if(LANGUAGE==0)	//Ӣ�Ĳ˵�
	{
		CTAB[4]='*';  CTAB[5]='S';   CTAB[6]='O'; CTAB[7]='R'; 
		CTAB[8]='T';  CTAB[9]='*'; 
		CW_PR(10,14,10);//��һ����ʾ����"*SORT*"
		

		  
		CTAB[5]='D';  CTAB[6]='A';  CTAB[7]='T';  CTAB[8]='E';  
		CW_PR(9,15,9);	//�ڶ�����ʾ����"DATE"


		  
		CTAB[5]='R';   CTAB[6]='X';   CTAB[8]='S';   CTAB[9]='T';
		CTAB[10]='A';  CTAB[11]='T';  CTAB[12]='I';  CTAB[13]='O';	CTAB[14]='N';	  
		CW_PR(9,16,15);	//��������ʾ����"RX STATION"


		  
		CTAB[5]='M';   CTAB[6]='S';   CTAB[7]='G';  CTAB[9]='T';
		CTAB[10]='Y';  CTAB[11]='P';  CTAB[12]='E'; 
		CW_PR(9,17,13);	//��������ʾ����"MSG TYPE"


		  
		CTAB[5]='U';   CTAB[6]='N';   CTAB[7]='R';  CTAB[8]='E';
		CTAB[9]='A';   CTAB[10]='D'; 
		CW_PR(9,18,11);	//��������ʾ����"UNREAD"
		

		CTAB[5]='A';  CTAB[6]='R';  CTAB[7]='E';  CTAB[8]='A'; 
		CW_PR(9,19,9);	//��������ʾ����"AREA"		
	}
	
	else
	{
 		CCW_PR1(14,92,0xcab1,1);	//��һ����ʾ����"ʱ��"
 		CCW_PR1(16,92,0xbce4,1);
		
 		CCW_PR1(14,110,0xb7a2,1);	//�ڶ�����ʾ����"����̨"
		CCW_PR1(16,110,0xc9e4,1);
 		CCW_PR1(18,110,0xcca8,1);

  				
   		CCW_PR1(14,128,0xd0c5,1);	//��������ʾ����"��Ϣ���"
		CCW_PR1(16,128,0xcfa2,1);
 		CCW_PR1(18,128,0xc0e0,1);
  		CCW_PR1(20,128,0xb1f0,1);


  				
  		CCW_PR1(14,146,0xceb4,1);	//��������ʾ����"δ����Ϣ"
		CCW_PR1(16,146,0xb6c1,1);
  		CCW_PR1(18,146,0xd0c5,1);
 		CCW_PR1(20,146,0xcfa2,1);
 				
   		CCW_PR1(14,164,0xbabd,1);	//��������ʾ����"���о�����"
		CCW_PR1(16,164,0xd0d0,1);
 		CCW_PR1(18,164,0xbeaf,1);
  		CCW_PR1(20,164,0xb8e6,1);
 		CCW_PR1(22,164,0xc7f8,1);
  	
	}  



	W_DIAMOND(12,LANGUAGE?96:15);	//ѡ�������ʾ������ѡ��ѡ���ѡ����Ӻ�
	W_HDIAMOND(12,LANGUAGE?114:16);
	W_HDIAMOND(12,LANGUAGE?132:17);
	W_HDIAMOND(12,LANGUAGE?150:18);
	W_HDIAMOND(12,LANGUAGE?168:19);
	
	if(BUFFER2[0]!=0)				//��֤ѡ�����ӦBUFFER2[0]����ֵ
	{
		W_DIAMOND(12,LANGUAGE?(96+18*BUFFER2[0]):(BUFFER2[0]+15));
		W_HDIAMOND(12,LANGUAGE?96:15);	//ѡ�������ʾ������ѡ��ѡ���ѡ����Ӻ�
		//W_HDIAMOND(12,15);	
	}
	
}

/*********************************************/
/*	���ܣ����°�����������ѡ������ѡ��洢
          ��BUFFER2[0]������LCD�мӺ�ѡ��ѡ�� 
��ڲ�������
���ڲ�������
/*********************************************/
void SaveRankSubMenu_Updn();
void SaveRankSubMenu_Updn()
{
	if(BUFFER2[0]>=0&&BUFFER2[0]<=4)
	{
		if(G_Key == UP)
		{
			G_Key=0;			//��������
			if(BUFFER2[0]>0)
			{
				BUFFER2[0]--;	//���ƣ���1
				W_DIAMOND(12,LANGUAGE?(96+18*BUFFER2[0]):(BUFFER2[0]+15));
				W_HDIAMOND(12,LANGUAGE?(114+18*BUFFER2[0]):(BUFFER2[0]+16));
			}
			
		}
		if(G_Key == DOWN)
		{
			G_Key=0;			//��������
			if(BUFFER2[0]<4)
			{			
				BUFFER2[0]++;	//���ƣ���1
				W_DIAMOND(12,LANGUAGE?(96+18*BUFFER2[0]):(BUFFER2[0]+15));
				W_HDIAMOND(12,LANGUAGE?(78+18*BUFFER2[0]):(BUFFER2[0]+14));				
			}			
		}
	}
}

/***************************************************************/
/*	���ܣ�CLR������������������һ���˵��洢�˵�
��ڲ�������
���ڲ�������
/***************************************************************/
void SaveRankSubMenu_Return();
void SaveRankSubMenu_Return()
{
	if(G_Key == CLR)
	{

		BUFFER2[0]=0;	//ʹ��ȫ�ֱ�������
		FLAG=0;			//����ѭ��
		if(Rankback==0)	//����SaveSubMenu�˵���״̬20
		{
			STATE=20;
		}
		
		else 			//����LockSubMenu�˵���״̬30
		{
			Rankback=0;
			STATE=30;
		}
		G_Key=0;		//��������
	}
}

//*****************************************************/
/*	���ܣ�ENT��������������ѡ��ѡ����в���
��ڲ�������
���ڲ�������
/*****************************************************/
void SaveRankSubMenu_Dealing();
void SaveRankSubMenu_Dealing()
{
	if(G_Key == ENT&&STATE==202)
	{
		LANHELP=1;		//LAMHELP�ָ�����ʼֵ		
		FLAG=0;			//����ѭ��
		STATE=2020;		//SaveRangeChoose��״̬Ϊ2020
		G_Key=0;		//��������
	}
}

//**************************************************************/
/*	���ܣ�����˵���������ʵ�ְ�ʱ�䣬����̨����Ϣ���δ����Ϣ
          ���о���������
          ȫ�ֱ���Rankback,�������򹫹��������ڲ�������
          0 �洢�˵����Ӳ˵�
          1 �����˵����Ӳ˵�
          LANHELP=3 ���г���ͼ��ѡ��һ�������ֿ�ͼ
��ڲ�������
���ڲ�������
/***************************************************************/
void RunSaveRankSubMenu(unsigned char into)
{
    maske=0;
    maskc=0;
	Rankback=into;
	LANHELP=3;
	SaveRankSubMenu_Paintintial();
	
	while(FLAG)
	{
		SaveRankSubMenu_Updn();
		SaveRankSubMenu_Return();
		SaveRankSubMenu_Dealing();
		run_tip();
	}
  	
}