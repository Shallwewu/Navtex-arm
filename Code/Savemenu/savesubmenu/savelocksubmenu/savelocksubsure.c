#include <stdio.h>
#include <stdlib.h>
#include  "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "MessageDeal.h"
#include "code.h"
/********************************************************/
/*���ܣ�������ѡ���ӡ��ѡ����ʾ
��ڲ�������
���ڲ�������
/********************************************************/
void SaveLockSubSure_Paintintial();
void SaveLockSubSure_Paintintial()
{
	byte i;
	WFRAME();		//�����Ӳ˵��߿����ʾ
	
	if(LANGUAGE==0)	//Ӣ�Ľ���
	{
		CTAB[2]=42;   CTAB[3]='L';   CTAB[4]='O';   CTAB[5]='C'; 	CTAB[6]='K';
	    CTAB[8]='M';  CTAB[9]='S';   CTAB[10]='G'; CTAB[11]=42;
	    CW_PR(9,15,12);	//��һ����ʾ����"*LOCK MSG*"
	      
	    CTAB[4]='O';  CTAB[5]='K';  
	    CW_PR(9,17,6);	//�ڶ�����ʾ����"OK"
	      
	    CTAB[4]='C';  CTAB[5]='A';  CTAB[6]='N';  CTAB[7]='C';  CTAB[8]='A'; 
	    CTAB[9]='L'; 
	    CW_PR(9,18,10);	//��������ʾ����"CANCAL"
	    	
	   	if(State2000parameter==1)
		{

		   	CTAB[2]=42;   CTAB[3]='U';   CTAB[4]='N';   CTAB[5]='L'; 	CTAB[6]='O';
		    CTAB[7]='C';  CTAB[8]='K';   CTAB[10]='M';  CTAB[11]='S';   CTAB[12]='G'; CTAB[13]=42;
		    CW_PR(9,15,14);	
		}				//��������Ϊ�����˵�ʹ��ʱ����һ����ʾ���ݣ�UNLOCK MSG
	}
      
	else
	{
 		CCW_PR1(13,104,0xcbf8,1);	//��һ����ʾ����"������Ϣ"
 		CCW_PR1(15,104,0xb6a8,1);
 		CCW_PR1(17,104,0xd0c5,1);
  		CCW_PR1(19,104,0xcfa2,1);
  				
 		CCW_PR1(13,128,0xc8b7,1);	//�ڶ�����ʾ����"ȷ��"
		CCW_PR1(15,128,0xc8cf,1);

   		CCW_PR1(13,148,0xc8a1,1);	//��������ʾ����"ȡ��"
		CCW_PR1(15,148,0xcffb,1);
	    
	    if(State2000parameter==1)	//��������Ϊ�����˵�ʹ��ʱ����һ����ʾ���ݣ�������Ϣ
	    {
 			CCW_PR1(13,128,0xbde2,1);	
			CCW_PR1(15,128,0xcbf8,1);
	    } 
 	}
    
    W_DIAMOND(11,LANGUAGE?132:17);	//ѡ�������ʾ����ʼ��ѡ��ѡ����1
    W_HDIAMOND(11,LANGUAGE?152:18);
	
}

//********************************************/
/*	���ܣ����°�����������ѡ������ѡ��
��ڲ�������
���ڲ�������
/*********************************************/
void SaveLockSubSure_Updn();
void SaveLockSubSure_Updn()
{
	if(G_Key==UP||G_Key==DOWN)
	{

		BUFFER3[0]=(BUFFER3[0]+1)%2;
		if(BUFFER3[0]==0)		//����BUFFER[3]�е����ݣ���ѡ��ѡ��Ӻ�
		{
		    W_DIAMOND(11,LANGUAGE?132:17);
		    W_HDIAMOND(11,LANGUAGE?152:18);	
		}
		else		
		{
  	  		W_HDIAMOND(11,LANGUAGE?132:17);
    		W_DIAMOND(11,LANGUAGE?152:18);
		}	
		G_Key=0;				//�������㣬ѡ����Ϣ�洢��BUFFER[3]��
	}
}

//*****************************************************/
/*	���ܣ�ENT��������������ѡ��ѡ����в�������
          ����(����)��������ȡ�����ز���
��ڲ�������
���ڲ�������
/*****************************************************/
void SaveLockSubSure_Dealing();
void SaveLockSubSure_Dealing()	//ִ����Ϸ��ص��洢�˵�
{
	if(G_Key == ENT)
	{

		if(BUFFER3[0] == 0)  	//����(����)����
		//����ȷ�������Ӧ��ѡ��Ϣ�ڴ洢���������Ӧ��lock��һ��
								//ͬʱ����Ϣ�ӵ�������������
		{
		 	int i,j;
			if(State2000parameter==0)	//�����˵�����������
			{
				for(i=0;i<Messagenumber;i++)
				{	
					if(Messagesavetop[Messagetoprank[i]].select==1)		//��ÿ����ѡ����Ϣ����������
					{
						Messagesavetop[Messagetoprank[i]].select=0;		//��ѡ�������
						MsgLock(i);						//������������
					}
				}
			}
			
			if(State2000parameter==1)	//�����˵������н���
			{
				for(i=0;i<Messagenumber;i++)
				{	
					if(Messagesavetop[Msglockrank[i]].select==1)
					{
						Messagesavetop[Msglockrank[i]].select=0;		//��ѡ�������
						for(j=0;j<Messageinfo.savenumber[0];j++)
						{
							if(Msglockrank[i]==Messagetoprank[j]) break;
						}
						MsgUnlock(j);					//���н���������1��ʾ�����б�
					}
				}	
			}
			
			BUFFERSELECT[21]=0;
			BUFFER1[0]=0;	//ֱ�������洢���˵�����Ҫ��BUFFER1[0]����		
			FLAG=0;			//����ѭ��
			STATE=2;		//Savemenu״̬Ϊ2
			if(State2000parameter==0)
			{
				State2parameter=1;	//��ڲ���1��Savemenu��Ϊ�洢�˵�					
			}
			else 
			{
				
				State2000parameter=0;
				State2parameter=5;	//��ڲ�����Savemenu��Ϊ�����˵�
			}
		}
		
		else				//ȡ������
		{

			BUFFER3[0]=0;	//���˵�ʹ�õ�ȫ�ֱ�������
			FLAG=0;			//����ѭ��			
			if(State2000parameter==0)	//���˵���Ϊ������ѡ�˵����Ӳ˵����践�ص�������ѡ�˵�
			{	
				STATE=200;				//SaveLockSubmenu��״̬Ϊ200
				State200parameter=10;	//��ڲ���10����ʾ���Ӳ˵�����				
			}
			
			else						//���˵���Ϊ������ѡ�˵����Ӳ˵����践�ص�������ѡ�˵�
			{
				State2000parameter=0;	//���˵�ʹ�õ�ȫ�ֱ�������
				STATE=300;				//LockLockSubMenu��״̬Ϊ300
				State300parameter=10;	//��ڲ���10����ʾ���Ӳ˵�����
			} 
		}
		G_Key=0;				//��������		
	}
}


/*********************************************************/
/*	���ܣ�������ѡ�ͽ�����ѡ�Ĺ����Ӳ˵������ڽ��ж�Ӧ��Ϣ��
          ��������������˵�ʹ�õ���ȫ�ֱ������£�
          State2000parameter ��ڲ����ı�����1��Ϊ������ѡ
          ���Ӳ˵���0��Ϊ������ѡ���Ӳ˵�
          BUFFER3[0] ѡ������Ϣ�Ĵ洢

��ڲ�����into  ��¼�Ӻβ˵�����
���ڲ�������
/*********************************************************/
void RunSaveLockSubSure(byte into)
{
    maske=0;
    maskc=0;
	State2000parameter=into;



	SaveLockSubSure_Paintintial();
	
	while(FLAG)
	{
		SaveLockSubSure_Updn();
		SaveLockSubSure_Dealing();
		run_tip();
	}
  	
}