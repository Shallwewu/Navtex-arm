#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "MessageDeal.h"
#include "Eprom.h"
#include "code.h"
//********************************************/
/*	���ܣ��Ӳ˵�Message_Locksubmenu�������ʾ
��ڲ�������
���ڲ�������
/*********************************************/
void Message_Locksubmenu_Paintintial();
void Message_Locksubmenu_Paintintial()
{
	byte i;
	WFRAME();		//�����Ӳ˵���ͼ��ʾ
	if(LANGUAGE==0)	//Ӣ�Ľ���
	{

	    CTAB[4]='*';	CTAB[3]='U';   CTAB[4]='N';   CTAB[5]='L'; 	CTAB[6]='O';
	    CTAB[7]='C';   CTAB[8]='K';   CTAB[10]='M';  CTAB[11]='S';   CTAB[12]='G'; CTAB[13]='*';
	    CW_PR(9,10,14);		//��һ����ʾ����"UNLOCK MSG"
	    

	      
	    CTAB[4]='O';  CTAB[5]='K';  
	    CW_PR(9,11,6);		//�ڶ�����ʾ����"OK"
	    

	      
	    CTAB[4]='C';  CTAB[5]='A';  CTAB[6]='N';  CTAB[7]='C';  CTAB[8]='E'; 
	    CTAB[9]='L'; 
	    CW_PR(9,12,10);		//��������ʾ����"CANCEL"
	    
	    if(Messagesavetop[Messagetoprank[Messagenownumber]].lock==0)
	    {
		    CTAB[4]='*';   CTAB[5]='L'; 	CTAB[6]='O';
			CTAB[7]='C';  CTAB[8]='K';   CTAB[10]='M';  CTAB[11]='S';   CTAB[12]='G'; CTAB[13]='*';
			CW_PR(9,10,14);	//�Ӳ˵�������Ϣ����������һ�����ݣ�LOCK MSG	
	    }		
	}
	
	else			//���Ľ���
	{
 		CCW_PR1(13,104,0xbde2,1);		//��һ����ʾ����"������Ϣ"
 		CCW_PR1(15,104,0xcbf8,1);
 		CCW_PR1(17,104,0xd0c5,1);
  		CCW_PR1(19,104,0xcfa2,1);
  				
 

 		CCW_PR1(13,128,0xc8b7,1);		//�ڶ�����ʾ����"ȷ��"
		CCW_PR1(15,128,0xc8cf,1);

  		
   		CCW_PR1(13,148,0xc8a1,1);		//��������ʾ����"ȡ��"
		CCW_PR1(15,148,0xcffb,1);
			    
	    if(Messagesavetop[Messagetoprank[Messagenownumber]].lock==0)
	    {
 			CCW_PR1(13,104,0xcbf8,1);	//�Ӳ˵�������Ϣ������,��һ����ʾ����"������Ϣ"
			CCW_PR1(15,104,0xb6a8,1);
	    } 
 	}
    
    W_DIAMOND(11,LANGUAGE?132:11);	//ѡ������ʾ	
    W_HDIAMOND(11,LANGUAGE?152:12);
}

//********************************************/
/*	���ܣ����°�����������ѡ������ѡ����
		  ����Һ�����������ʾ
��ڲ�������
���ڲ�������
/*********************************************/

void Message_Locksubmenu_Updn();
void Message_Locksubmenu_Updn()
{
	if (G_Key==UP||G_Key==DOWN)
	{
		G_Key=0;
		BUFFER2[0]=(BUFFER2[0]+1)%2;//BUFFERP[2]���ڼ�¼ѡ���ĸ�ѡ��
		if(BUFFER2[0]==0)			//ѡ��ѡ����һ
		{
		    W_DIAMOND(11,LANGUAGE?132:11);
		    W_HDIAMOND(11,LANGUAGE?152:12);	
		}
		
		else						//ѡ��ѡ�����	
		{
  	  		W_HDIAMOND(11,LANGUAGE?132:11);
    		W_DIAMOND(11,LANGUAGE?152:12);
		}
	}
}


//*********************************************************/
/*	���ܣ�ENT��������������ѡ���������Ӧ����
��ڲ�������
���ڲ�������
/*********************************************************/
void Message_Locksubmenu_Dealing();
void Message_Locksubmenu_Dealing()
{
	byte channel=0;
	if (G_Key==ENT)
	{
		G_Key=0;
	
		if(BUFFER2[0]==0)	//���н�������������
		{
			if(Messagesavetop[Messagetoprank[Messagenownumber]].lock==0)//��Ϣ������
			{
				channel=Messagesavetop[Messagetoprank[Messagenownumber]].frequency;	//�洢ֵ1,2,3�ֱ����ͨ��518,490,4209.5
			
				if(Messageinfo.locknumber[channel]<50) 				//��ǰ��Ϣ����ͨ�����������Կɼ�������
				{
					MsgLock(Messagenownumber);	//�Ե�ǰ��Ϣ��������
					BUFFER1[0]=0;				//Խ��������ǰһ����˵�ʹ��BUFFER1[0]����
					STATE=1;					//Message�˵�״̬Ϊ1
					State1parameter=10;			//��ڲ���Ϊ10���������Ӳ˵�����
				}										
															
				else 							//������ǰͨ������������50�����볬����������Message_OverCapacity
				{
					STATE=14;					//Message_OverCapacity�˵�״̬Ϊ14
					State14parameter=0;			//��ڲ���Ϊ0����ʾ����Ϣ���ݽ���������������				
				}										
			}
	
		
		    else //��Ϣ�Ľ���
			{
				MsgUnlock(Messagenownumber);	//�洢�˵��ж�Ӧ��Ϣ�Ľ���	
				BUFFER1[0]=0;					//Խ��������ǰһ����˵�ʹ��BUFFER1[0]����
				STATE=1;						//Message�˵�״̬Ϊ1
//				State1parameter=10;				//��ڲ���Ϊ10��3������MsgUnlock()�����иı�
			}
			
/*			if(Returntype==2) //����������˵�
			{
						
				MsgUnlock(Messagenownumber);	//�洢�˵��ж�Ӧ��Ϣ�Ľ���		
				BUFFER1[0]=0;					//Խ��������ǰһ����˵�ʹ��BUFFER1[0]����
				STATE=1;						//Message�˵�״̬Ϊ1
//				State1parameter=10;				//��ڲ���Ϊ10���������Ӳ˵�����				
			}	*/
			
		}
		

		if(BUFFER2[0]==1)	//����ǰһ���˵�MessageSubmenu
		{
			STATE=11;		//MessageSubmenu��״̬Ϊ11
		}
		BUFFER2[0]=0;		//����ENT���ؽ���������������BUFFER2[0]��FLAG����
		FLAG=0;				//����ѭ��				
	}
}










//**************************************************************/
/*	���ܣ�������ʵ����Ϣ�Ľ�������������ȫ�ֱ���Returntype��
		  ������������ʹ洢���档���Ǵ洢���棬����lockλ�жϣ�
		  ���н�������������������������ֻ�ܽ��н��������뱾����
		  ���������򲻻᷵�ص������棬��ÿ�ν���ý��涼����״
		  ̬����Ҫôֱ�ӷ����ϼ����棬�������ӽ��棬�ӽ����Խ��
		  ���أ����᷵�ر�����
��ڲ�����byte ���ͣ���¼�Ӻβ˵�����
���ڲ�������
/***************************************************************/
void RunMessage_LockSubmenu()
{
    maske=0;
    maskc=0;
 	Message_Locksubmenu_Paintintial();

	while(FLAG)
	{
		Message_Locksubmenu_Updn();
		Message_Locksubmenu_Dealing();
		run_tip();
	}
  	
}