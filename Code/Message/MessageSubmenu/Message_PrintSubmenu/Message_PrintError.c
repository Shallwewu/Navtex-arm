#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"
#include "lcddrive.h"
#include "code.h"
//********************************************/
/*	���ܣ��Ӳ˵�Message_Printerror�������ʾ
��ڲ�������
���ڲ�������
/*********************************************/
void Message_Printerror_Paintintial();
void Message_Printerror_Paintintial()
{
	byte i;
	
	if(LANGUAGE==0)	//Ӣ�Ĳ˵�
	{
	    CTAB[0]='*';  CTAB[1]='P';  CTAB[2]='R';   CTAB[3]='I';   CTAB[4]='N';   CTAB[5]='T';
	    CTAB[6]='E';  CTAB[7]='R';  CTAB[9]='E';   CTAB[10]='R';  CTAB[11]='R';  CTAB[12]='O'; CTAB[13]='R'; CTAB[14]='*';
	    if(State13parameter==0)CW_PR(10,10,15);	//��һ����ʾ����"PRINTER ERROR"
	    else CW_PR(10,15,15);	
//	    CTAB[1]='P';  CTAB[2]='L';   CTAB[3]='E';   CTAB[4]='A';  CTAB[5]='S';   CTAB[6]='E';   CTAB[8]='C';
//	    CTAB[9]='H';  CTAB[10]='E';  CTAB[11]='C';  CTAB[12]='K';
//	    CW_PR(11,15,13);	//�ڶ�����ʾ����"PLEASE CHECK"
		
//	    CTAB[0]='T'; 	CTAB[1]='H';  CTAB[2]='E';  CTAB[4]='P';   CTAB[5]='R';   CTAB[6]='I';   CTAB[7]='N';
//	    CTAB[8]='T';   CTAB[9]='E';  CTAB[10]='R';  CTAB[11]='!'; 
//	    CW_PR(10,16,12);	//��������ʾ����"THE PRINTER!"

	    CTAB[2]='E';  CTAB[3]='N';   CTAB[4]='T';  CTAB[5]='E';   CTAB[6]='R';   CTAB[8]='E';
	    CTAB[9]='N';  CTAB[10]='T';  CTAB[12]='T';  CTAB[13]='O'; 
	    if(State13parameter==0)CW_PR(10,11,14);	//��������ʾ����"ENTER ENT TO"
	    else CW_PR(10,17,14);
		
	    CTAB[0]='R';   CTAB[1]='E';   CTAB[2]='T';
	    CTAB[3]='U';   CTAB[4]='R';   CTAB[5]='N';  CTAB[6]='.';
	    if(State13parameter==0)CW_PR(10,12,7);	//��������ʾ����"RETURN."
	    else CW_PR(10,18,7);
	 	
	}
      
  	else
	{
 		CCW_PR1(9,104,0xb4f2,1);	//��һ����ʾ����"��ӡ����:"
 		CCW_PR1(11,104,0xd3a1,1);
  		CCW_PR1(13,104,0xb3f6,1);
 		CCW_PR1(15,104,0xb4ed,1);
		CCW_PR1(17,104,0x1aa0,0);
  				
 		CCW_PR1(11,128,0xc7eB,1);	//�ڶ�����ʾ����"�����ӡ��"
		CCW_PR1(13,128,0xbcec,1);
 		CCW_PR1(15,128,0xb2e9,1);
 		CCW_PR1(17,128,0xb4f2,1);
  		CCW_PR1(19,128,0xd3a1,1);
 		CCW_PR1(21,128,0xbbfa,1);
 		CCW_PR1(23,128,0x1780,0);
 		 		
 		CCW_PR1(11,148,0xb0b4,1);	//��������ʾ����"����ent������"
		CCW_PR1(13,148,0xcfc2,1);
		CCW_PR1(18,148,0xbcfc,1);
 		CCW_PR1(20,148,0xb7b5,1);
 		CCW_PR1(22,148,0xbbd8,1);
  		CCW_PR1(24,148,0x1920,0);
	
		if(State13parameter==0&&PublicReturn!=4)
		{
			CW_PR3(15,11,'E');
		    CW_PR3(16,11,'N');
	    	CW_PR3(17,11,'T');
		}
		else
		{
			CW_PR3(15,19,'E');
		    CW_PR3(16,19,'N');
	    	CW_PR3(17,19,'T');
		}
	}
	
	WFRAME();	//�����Ӳ˵���ͼ��ʾ 
}

//**************************************************************/
/*	���ܣ�ENT�������������������˵�
��ڲ�������
���ڲ�������
/***************************************************************/
void Message_Printerror_Dealing();
void Message_Printerror_Dealing()
{
	if(G_Key == ENT) 
	{
		G_Key=0;						//��������
		FLAG=0;							//����ѭ��
		switch(PublicReturn)
		{
			case 0:{STATE=11;}break;	//���ص���Ϣ���Ľ����Ӳ˵� MessageSubmenu	
			case 1:{STATE=201;}break;	//���ص��洢����Ĵ�ӡ�Ӳ˵� SavePrintSubmenu
			case 2:{STATE=201;}break;	//���ص��洢����Ĵ�ӡ�Ӳ˵� SavePrintSubmenu
			case 3:{STATE=200;State200parameter=10;}break;//���ص���ӡ��ѡ����SavelockSubmenu
			case 4:{STATE=2010;}break;	//Խ��������һ���渴ѡ��ӡ����SavePitchPrint
			default:break;
		}
		PublicReturn=0;
	}
}


//**************************************************************/
/*	���ܣ���������Ϊ��ӡ�����ӽ���Ĺ�������
��ڲ�����byte ���ͣ���¼�Ӻβ˵�����,��PublicReturn����¼
	      0 ����Ϣ���ݽ������
		  1 �ɴ�ӡ������Ϣ�������
		  2 �ɴ�ӡ״̬�������
		  3 �ɴ�ӡ�˹���ѡ����ѡ����Ϣ����
		  4 ��������Ϣ�Ĵ�ӡ
���ڲ�������
/***************************************************************/
void RunMessage_PrintError()
{
    maske=0;
    maskc=0;
	Message_Printerror_Paintintial();
	while(FLAG)
	{
		Message_Printerror_Dealing();
		run_tip();	
	}
}