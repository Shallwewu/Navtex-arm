#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "run.h"
#include "lcddrive.h"
#include "Eprom.h"
#include "code.h"

/*****************************************/
/*	���ܣ�����ѡ��˵�Languagesetting����ʾ
��ڲ�������
���ڲ�������
/*****************************************/ 
void Languagesetting_Paintintial();
void Languagesetting_Paintintial()
{
	byte i;
//	CLEAR1();			//��һ���Ͷ����Ĵ洢�ռ�
	
	if(LANGUAGE==0)		//Ӣ�Ĳ˵�
	{
		/* ��ͷ LANGUAGE MENU*/
		CTAB[1]='L';	CTAB[2]='A';	CTAB[3]='N';	CTAB[4]='G';	CTAB[5]='U';	CTAB[6]='A';
		CTAB[7]='G';	CTAB[8]='E';	CTAB[10]='M';	CTAB[11]='E';	CTAB[12]='N';	CTAB[13]='U';
		CW_PR(0,1,14);
		

	     /* ����ѡ����ʾ��PLEASE CHOOSE LANGUAGE VERSION */
		CTAB[2]='P';	CTAB[3]='L';	CTAB[4]='E';	CTAB[5]='A';	CTAB[6]='S';	CTAB[7]='E';
		CTAB[9]='C';	CTAB[10]='H';	CTAB[11]='O';	CTAB[12]='O';	CTAB[13]='S';  CTAB[14]='E';
		CTAB[16]='L';  CTAB[17]='A';  CTAB[18]='N';  CTAB[19]='G';  CTAB[20]='U';  CTAB[21]='A'; 
		CTAB[22]='G';  CTAB[23]='E';  CTAB[25]='V';  CTAB[26]='E';  CTAB[27]='R';  CTAB[28]='S';
	    CTAB[29]='I';  CTAB[30]='O';  CTAB[31]='N';	CTAB[32]=':';
		CW_PR(0,5,33);
		
		/* Ӣ�� ENGLISH */
	   	CTAB[6]='E';	CTAB[7]='N';	CTAB[8]='G';	CTAB[9]='L';	CTAB[10]='I';	CTAB[11]='S';	CTAB[12]='H';	
		CW_PR(10,9,13);
		
		/* ���� CHINESE*/
	   	CTAB[6]='C';	CTAB[7]='H';	CTAB[8]='I';	CTAB[9]='N';	CTAB[10]='E';	CTAB[11]='S';	CTAB[12]='E';	
		CW_PR(10,12,13);	
	}
	
	else 				//���Ĳ˵�
	{
		
		CLEARXLINE(0,39,22);
		CLEARXLINE(0,39,17);
		XLINE(0,39,24);
		XLINE(0,39,25);
 		
 		CCW_PR1(1,7,0xd3ef,1);	//��һ������"����ѡ��"
 		CCW_PR1(3,7,0xd1d4,1);
 		CCW_PR1(5,7,0xd1a1,1);
 		CCW_PR1(7,7,0xd4f1,1);	
 		
 		CCW_PR1(4,56,0xc7eb,1);	//�ڶ�������"��ѡ��ϵͳ����"
 		CCW_PR1(6,56,0xd1a1,1);
 		CCW_PR1(8,56,0xd4f1,1);
 		CCW_PR1(10,56,0xcfb5,1);
 	 	CCW_PR1(12,56,0xcdb3,1);
  		CCW_PR1(14,56,0xd3ef,1);	
 		CCW_PR1(16,56,0xd1d4,1);		
   		CCW_PR1(18,56,0x1aa0,0);
   		
 		CCW_PR1(14,88,0xd3a2,1);	//����������"Ӣ��"
 		CCW_PR1(16,88,0xcec4,1);

 		CCW_PR1(14,112,0xd6d0,1);	//����������"����"
 		CCW_PR1(16,112,0xcec4,1);		
	}
	

	XLINE(0,39,0);
	XLINE(0,39,239);
	
	W_YLINE(0,0,239);
	W_YLINE(319,0,239);				//ѡ�������ʾ
	W_DIAMOND(LANGUAGE?12:14,LANGUAGE?92:9);
	W_HDIAMOND(LANGUAGE?12:14,LANGUAGE?116:12);
	
	W_Mode(35,7,32,1);			//�ֶ����Զ�ģʽ����ʾ	
}
 
/**************************************/
/*	���ܣ�ѡ������ѡ��
��ڲ�������
���ڲ�������
/**************************************/ 
void Languagesetting_Updn();
void Languagesetting_Updn()
{
	if (G_Key==UP||G_Key==DOWN)
	{
		G_Key=0;						//��������
		BUFFER1[0]=(BUFFER1[0]+1)%2;	//ѡ��ѡ�ʹ���BUFFER1[0]
		if(BUFFER1[0]==0)				//��ʾѡ����ѡ���
		{
			W_DIAMOND(LANGUAGE?12:14,LANGUAGE?92:9);
			W_HDIAMOND(LANGUAGE?12:14,LANGUAGE?116:12);		
		}
		else		
		{
			W_HDIAMOND(LANGUAGE?12:14,LANGUAGE?92:9);
			W_DIAMOND(LANGUAGE?12:14,LANGUAGE?116:12);		
		}	
	}
}
 
/**************************************/
/*	���ܣ�������һ���˵�ManiMenu
��ڲ�������
���ڲ�������
/**************************************/ 
 void Languagesetting_Return();
 void Languagesetting_Return()
 {
	if (G_Key==CLR) 
	{
		G_Key=0;			//��������
		BUFFER1[0]=0;      	//���˵�ʹ��ȫ�ֱ�������
	    FLAG=0;             //����ѭ��      
		STATE=4;			//MainMenu״̬Ϊ4
		State4parameter=0;	//��ڲ���Ϊ0
	}
 }
 
/**************************************/
/*	���ܣ�ѡ��ѡ������ڵ�ѡ��
��ڲ�������
���ڲ�������
/**************************************/ 
void Languagesetting_Dealing();
void Languagesetting_Dealing()
{
	if(G_Key==ENT&&STATE==45)
	{
		G_Key=0;								//��������
		if (BUFFER1[0]==0)   LANGUAGE=0;		//ѡ����������
		else	LANGUAGE=1;				
		BUFFER1[0]=0;							//���˵�ȫ�ֱ�������
		FLAG=0;                   				//�������˵�ѭ��
		STATE=45;								//�ٴν��뱾�˵���״̬Ϊ45
		Write_Char_Eprm(RX_LANGUAGE,LANGUAGE);	//��LANGUAGE��Ϣд��Eprom
	}
}



/**************************************/
/*	���ܣ�����ѡ��˵�
��ڲ�������
���ڲ�������
/**************************************/ 
void RunLanguageSetting()
{
    maske=0;
    maskc=0;
	Languagesetting_Paintintial();

	while(FLAG)
	{
		Languagesetting_Updn();			
		Languagesetting_Return();		
		Languagesetting_Dealing();
		run_tip();
	}
}