#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "printer.h"
#include "code.h"
//********************************************/
/*	���ܣ��Ӳ˵�Message_PrintSubmenu�������ʾ
��ڲ�������
���ڲ�������
/*********************************************/
void Message_Printsubmenu_Paintintial();
void Message_Printsubmenu_Paintintial()
{

	WFRAME();		//�����Ӳ˵���ͼ��ʾ
	if(LANGUAGE==0)	//Ӣ�Ĳ˵�
	{

	   	CTAB[2]=42;   CTAB[3]='P';   CTAB[4]='R';   CTAB[5]='I'; 	CTAB[6]='N';
	    CTAB[7]='T';  CTAB[9]='M';   CTAB[10]='S';  CTAB[11]='G';   CTAB[12]=42; 
	    if(State13parameter==0)CW_PR(9,10,13);	//��һ����ʾ����"PRINT MSG"
	    else CW_PR(9,15,13);
	    
	    CTAB[4]='O';  CTAB[5]='K';  
	    if(State13parameter==0)CW_PR(9,11,6);	//�ڶ�����ʾ����"OK"
	    else CW_PR(9,17,13);
	    
	    CTAB[4]='C';  CTAB[5]='A';  CTAB[6]='N';  CTAB[7]='C';  CTAB[8]='E'; 
	    CTAB[9]='L'; 
	    if(State13parameter==0)	CW_PR(9,12,10);//��������ʾ����"CANCEL"
	    else CW_PR(9,18,13);		
	}

	else				//���Ĳ˵�
	{
 		CCW_PR1(13,104,0xb4f2,1);	//��һ����ʾ����"��ӡ��Ϣ"
 		CCW_PR1(15,104,0xd3a1,1);
 		CCW_PR1(17,104,0xd0c5,1);
  		CCW_PR1(19,104,0xcfa2,1);
  				
 		CCW_PR1(13,128,0xc8b7,1);	//�ڶ�����ʾ����"ȷ��"
		CCW_PR1(15,128,0xc8cf,1);
  		
   		CCW_PR1(13,148,0xc8a1,1);	//��������ʾ����"ȡ��"
		CCW_PR1(15,148,0xcffb,1);
 	}
    

    W_DIAMOND(11,LANGUAGE?132:(State13parameter==0?11:17));	//ѡ������ʾ
    W_HDIAMOND(11,LANGUAGE?152:(State13parameter==0?12:18));
	
}

//********************************************/
/*	���ܣ����°�����������ѡ������ѡ����
		  ����Һ�����������ʾ
��ڲ�������
���ڲ�������
/*********************************************/
void Message_Printsubmenu_Updn();
void Message_Printsubmenu_Updn()
{
	if (G_Key==UP||G_Key==DOWN)
	{
		G_Key=0;
		BUFFERPRINT=(BUFFERPRINT+1)%2;	//BUFFERPRINT���ڼ�¼ѡ���ĸ�ѡ��
		if(BUFFERPRINT==0)				//ѡ��ѡ����һ
		{
		    W_DIAMOND(11,LANGUAGE?132:(State13parameter==0?11:17));
		    W_HDIAMOND(11,LANGUAGE?152:(State13parameter==0?12:18));	
		}
		
		else							//ѡ��ѡ�����
		{
  	  		W_HDIAMOND(11,LANGUAGE?132:(State13parameter==0?11:17));
    		W_DIAMOND(11,LANGUAGE?152:(State13parameter==0?12:18));
		}
	}
} 



//*********************************************************/
/*	���ܣ�ENT��������������ѡ���������Ӧ����
��ڲ�������
���ڲ�������
/*********************************************************/
void Message_Printsubmenu_Dealing();
void Message_Printsubmenu_Dealing()
{
	if(G_Key == ENT)
	{
		G_Key=0;			//��������
		if(BUFFERPRINT==0)	//���д�ӡ����
		{
			if(Checkinfo.Printerror == 0)	//��ӡ������������ת����ӡ����Message_Printing
			{
				BUFFERPRINT=0;				//�����ӡ���治�᷵�ر����棬BUFFERPRINT����
				FLAG=0;						//����ѭ��
				STATE=16;					//Messsage_printing����״̬Ϊ16
//				Printmessage(Messagenownumber);					//zzy��ȥ����Ϊ�����б����Ѿ��д�ӡ����		
			}
			
			else						  	//��ӡ��������ת����ӡ�������Message_PrintError
			{

				BUFFERPRINT=0;				//�����������϶�����ص������棬����ֱ������
				              				//������淵�ص��Ǳ��������һ���������Գ���������ֱ�ӷ���
				FLAG=0;						//����ѭ��
				STATE=15;					//Message_PrintError����״̬Ϊ15
			}
		
		}
			
		else				//ȡ����ӡ����
		{
			BUFFERPRINT=0;	//������һ���˵���BUFFERPRINT����
			
			switch(PublicReturn)
			{
				case 0:STATE=11;break;	//���ص���Ϣ���Ľ����Ӳ˵�	
				case 1:STATE=201;break;	//���ص��洢����Ĵ�ӡ�Ӳ˵�
				case 2:STATE=201;break;	//���ص��洢����Ĵ�ӡ�Ӳ˵�
				case 3:STATE=200;State200parameter=10;break;//���ص���ӡ��ѡ����				
				default:break;			
			}
			
			FLAG=0;			//����ѭ��
			PublicReturn=0;	//���ز�������
		
		}
	}
	
		
}


//**************************************************************/
/*	���ܣ���������Ϊ��ӡ����Ĺ������棬��PublicReturn����¼�ɺβ˵�����
		  0 ����Ϣ���ݽ������
		  1 �ɴ�ӡ������Ϣ�������
		  2 �ɴ�ӡ״̬�������
		  3 �ɴ�ӡ�˹���ѡ����ѡ����Ϣ����		  
		  BUFFERPRINT���ڼ�¼������ѡ��ѡ����
��ڲ�����byte ���ͣ���¼�Ӻβ˵�����
���ڲ�������
/***************************************************************/

void RunMessage_PrintSubmenu(byte into)
{
    maske=0;
    maskc=0;
	PublicReturn=into;
//	Checkprint();	//�����ӡ���ļ�����
	Message_Printsubmenu_Paintintial();
	
	while(FLAG)
	{
		Message_Printsubmenu_Updn();
		Message_Printsubmenu_Dealing();
		run_tip();
	}
  	
}