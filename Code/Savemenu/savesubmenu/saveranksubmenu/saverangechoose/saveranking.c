#include <stdio.h>
#include <stdlib.h>
#include "lcddrive.h"
#include "run.h"
#include "define.h"
#include "code.h"
/*********************************************/
/*	���ܣ���������ʾ����
��ڲ�������
���ڲ�������
/*********************************************/
void SaveRanking_Paintintial();
void SaveRanking_Paintintial()
{
	unsigned char i;
	WFRAME();		//�����Ӳ˵���ͼ��ʾ
	
    if(LANGUAGE==0)	//Ӣ�Ĳ˵�
    {
	    CTAB[4]='R';  CTAB[5]='A';   CTAB[6]='N';   CTAB[7]='K';   CTAB[8]='I';
	    CTAB[9]='N';  CTAB[10]='G';         
	    CW_PR(8,17,11);  
	 	CCW_PR1(19,132,0xa1ad,1);
		CCW_PR1(21,132,0xa1ad,1);     	
    }
    
    else			//���Ĳ˵�
    {
  		CCW_PR1(13,128,0xc5c5,1);	//��һ����ʾ����"�����С�����"
		CCW_PR1(15,128,0xd0f2,1);
		CCW_PR1(17,128,0xd6d0,1);
		CCW_PR1(19,128,0xa1ad,1);
		CCW_PR1(21,128,0xa1ad,1);
    }

}

//**************************************************************/
/*	���ܣ��Զ��˳����˵�����
��ڲ�������
���ڲ�������
/***************************************************************/
void SaveRanking_Return();
void SaveRanking_Return()	//������Ϻ��Զ����ص���Ϣ�洢����
{

	BUFFER[0]=0;		//ʹ�õ�ȫ�ֱ���ȫ������
	BUFFER1[0]=0;		
	BUFFER2[0]=0;
	BUFFER3[0]=0;	
	LANHELP=1;			//LANHELP�ָ���ʼֵ
	STATE=2;			//Savemenu״̬Ϊ2
	if(Rankback==0)	State2parameter=0;	//��ڲ���0��Savemenu��Ϊ�洢����
	else State2parameter=5;				//��ڲ���2��Savemenu��Ϊ��������
	Rankback=0;
	CLEAR1();
}


/***************************************************************/
/*	���ܣ���������������ʾ�������С�����
		  BUFFER2[0]:ȫ��	518khz	490khz	4209.5khz
		  BUFFER3[0]:ʱ��	����̨	��Ϣ���	δ����Ϣ	���о�����
��ڲ�������
���ڲ�������
/***************************************************************/
void RunSaveRanking()
{

	LANHELP=2;	//�����Ĳ˵��£������˵��߿��Ծ�ʹ��Ӣ�ı߿�
	SaveRanking_Paintintial();
	Rankfuction(BUFFER3[0],BUFFER2[0]);
	SaveRanking_Return();
  	
}