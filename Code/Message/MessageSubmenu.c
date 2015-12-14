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
void Messagesubmenu_Diamond();
void Messagesubmenu_Diamond()
{
	if(BUFFER1[0]==0)	//����һѡ��
	{
	    W_DIAMOND(12,LANGUAGE?132:11);
	    W_HDIAMOND(12,LANGUAGE?152:12);
	}
	
	else				//�����ѡ��
	{
		W_DIAMOND(12,LANGUAGE?152:12);
    	W_HDIAMOND(12,LANGUAGE?132:11);	
	}	
}


//********************************************/
/*	���ܣ�Messagesubmenu �������ʾ
��ڲ�������
���ڲ�������
/*********************************************/
void Messagesubmenu_Paintintial();
void Messagesubmenu_Paintintial()
{
	byte i;
	WFRAME();		//�����Ӳ˵���ͼ��ʾ
    IntialLCD(1);
	if(LANGUAGE==0)	//Ӣ��
	{

	    
	   	CTAB[4]=42;  CTAB[5]='S';   CTAB[6]='E';  CTAB[7]='T'; 
	   	CTAB[9]='U';  CTAB[10]='P'; CTAB[11]=42;
	    CW_PR(9,10,12);	//��ͷ SETUP
	    

	      
	    CTAB[5]='U';  CTAB[6]='N';  CTAB[7]='L';  CTAB[8]='O';  CTAB[9]='C'; 
	    CTAB[10]='K'; CTAB[12]='M'; CTAB[13]='S'; CTAB[14]='G';
	    CW_PR(9,11,15);	//��һ�����ݣ�UNLOCK MSG
	    

	      
	    CTAB[5]='P';  CTAB[6]='R';  CTAB[7]='I';  CTAB[8]='N';  CTAB[9]='T'; 
	    CTAB[11]='M'; CTAB[12]='S'; CTAB[13]='G';
	    CW_PR(9,12,14);	//�ڶ������ݣ�PRINT MSG
	    
	    if(Messagesavetop[Messagetoprank[Messagenownumber]].lock==0)
	    {
			CTAB[5]='L';  CTAB[6]='O';  CTAB[7]='C'; 
			CTAB[8]='K';  CTAB[10]='M';  CTAB[11]='S'; CTAB[12]='G';
			CW_PR(9,11,13);
	    }   			//�Ӳ˵�������Ϣ����������һ�����ݣ�LOCK MSG
	    	
	}
	
	else			//����
	{
 		CCW_PR1(15,104,0xc9e8,1);	//��һ����ʾ����"����"
 		CCW_PR1(18,104,0xd6c3,1);
		
 		CCW_PR1(14,128,0xbde2,1);	//�ڶ�����ʾ����"������Ϣ"
		CCW_PR1(16,128,0xcbf8,1);
 		CCW_PR1(18,128,0xd0c5,1);
  		CCW_PR1(20,128,0xcfa2,1);
  		
   		CCW_PR1(14,148,0xb4f2,1);	//��������ʾ����"��ӡ��Ϣ"
		CCW_PR1(16,148,0xd3a1,1);
 		CCW_PR1(18,148,0xd0c5,1);
  		CCW_PR1(20,148,0xcfa2,1);
	    
	    if(Messagesavetop[Messagetoprank[Messagenownumber]].lock==0)
	    {
 			CCW_PR1(14,128,0xcbf8,1);
			CCW_PR1(16,128,0xb6a8,1);
	    } 							//�Ӳ˵�������Ϣ���������ڶ�����ʾ����"������Ϣ"
 	}

	Messagesubmenu_Diamond();		//���ÿ�ͼ��ʾ����
	
}  

//********************************************/
/*	���ܣ����°�����������ѡ������ѡ����
��ڲ�������
���ڲ�������
/*********************************************/
void Messagesubmenu_Updn();
void Messagesubmenu_Updn() 
{
	if (G_Key==UP||G_Key==DOWN)
	{
		G_Key=0;
		BUFFER1[0]=(BUFFER1[0]+1)%2;
		Messagesubmenu_Diamond();	//���ÿ�ͼ��ʾ����
	}
	
} 

//**************************************************************/
/*	���ܣ�CLR������������������һ���˵���Ϣ���ݲ˵� Message
��ڲ�������
���ڲ�������
/***************************************************************/
void Messagesubmenu_Return();
void Messagesubmenu_Return()	
{
	if (G_Key==CLR)
	{
		BUFFER1[0]=0;		//����
		G_Key=0;			//��������
		FLAG=0;				//����ѭ��
		STATE=1;			//״̬1�� Message ����
		State1parameter=10;	//��ڲ���10����ʾ���Ӳ˵�����
	}
	
}
//**************************************************************/
/*	���ܣ�ENT��������������ѡ�������ѡ������
��ڲ�������
���ڲ�������
/***************************************************************/
void Messagesubmenu_Dealing();
void Messagesubmenu_Dealing()
{
	if (G_Key==ENT&&STATE==11)
	{
		G_Key=0;
		FLAG=0;	
		if(BUFFER1[0]==0)		//������Ϣ���������������ת��Message_LockSubmenu����	
		{
			STATE=12;			//Message_LockSubmenu״̬Ϊ12		
		}
		
		if(BUFFER1[0]==1)		//������Ϣ�Ĵ�ӡ����ת��Message_PrintSubmenu����
		{
			STATE=13;			//Message_PrintSubmenu״̬Ϊ13
			State13parameter=0;	//��ڲ���0����ʾ����Ϣ���Ľ������
		}
	}
}

//**************************************************************/
/*	���ܣ�Message�����һ���Ӳ˵���ʵ�ֶ���Ϣ���ĵĴ�ӡ
		  ���������������ز���
��ڲ�������
���ڲ�������
/***************************************************************/
void RunMessageSubmenu()
{
    maske=0;
    maskc=0;
	Messagesubmenu_Paintintial();

	while(FLAG)
	{	
		Messagesubmenu_Updn();
		Messagesubmenu_Return();
		Messagesubmenu_Dealing();
		run_tip();
	}
  	
}