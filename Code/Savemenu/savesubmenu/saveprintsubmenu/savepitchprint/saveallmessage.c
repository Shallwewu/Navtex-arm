#include <stdio.h>
#include <stdlib.h>
#include  "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "printer.h"
#include "code.h"



void SaveAllMessage_Paintintial();
void SaveAllMessage_Paintintial()
{
	byte i;
	WFRAME();
	
	if(LANGUAGE==0)		//Ӣ�Ĳ˵�
	{
		CTAB[4]='*';  CTAB[5]='P';   CTAB[6]='I'; CTAB[7]='T'; 
		CTAB[8]='C';  CTAB[9]='H';   CTAB[10]='*';
		CW_PR(9,14,11);	//��һ����ʾ����"PITCH"
		  
		CTAB[3]='C';  CTAB[4]='H';    CTAB[5]='A';  CTAB[6]='N';
		CTAB[7]='N';  CTAB[8]='E';    CTAB[9]='L';  CTAB[10]=':';  
		CTAB[11]='0'; 
		CW_PR(9,15,12);	//�ڶ�����ʾ����"CHANNEL:0"

	    CTAB[3]='M';  CTAB[4]='S';  CTAB[5]='G';  
		CTAB[7]='T';  CTAB[8]='Y';  CTAB[9]='P';  CTAB[10]=':';	  
		CTAB[11]='0'; 
		CW_PR(9,16,12);	//��������ʾ����"MSG TYP:0"
		  
	    CTAB[3]='S';  CTAB[4]='T';  CTAB[5]='A';  CTAB[6]='T';
		CTAB[7]='I';  CTAB[8]='O';  CTAB[9]='N';  CTAB[10]=':'; 
		CTAB[11]='0'; 
		CW_PR(9,17,12);	//��������ʾ����"STATION:0"
		  
		CTAB[3]='P';   CTAB[4]='R';  CTAB[5]='I';  CTAB[6]='N';
		CTAB[7]='T'; 	CTAB[9]='M';  CTAB[10]='S';  CTAB[11]='G';
		CW_PR(9,18,12);	//��������ʾ����"PRINT MSG"
		  
		CTAB[3]='C';   CTAB[4]='A';  CTAB[5]='N';  CTAB[6]='C'; 
		CTAB[7]='A';   CTAB[8]='L';	
		CW_PR(9,19,9);	//��������ʾ����"CANCAL"		
	}
	  

	else				//���Ĳ˵�
	{
 		CCW_PR1(12,92,0xcda8,1);	//��һ����ʾ����"ͨ��"
 		CCW_PR1(14,92,0xb5c0,1);
		CW_PR3(20,12,':');
		CW_PR3(21,12,'0');
		
 		CCW_PR1(12,108,0xd0c5,1);	//�ڶ�����ʾ����"��Ϣ����"
		CCW_PR1(14,108,0xcfa2,1);
 		CCW_PR1(16,108,0xc0e0,1);
		CCW_PR1(18,108,0xd0cd,1);
 		CW_PR3(20,14,':');
		CW_PR3(21,14,'0');
		 				
   		CCW_PR1(12,124,0xb7a2,1);	//��������ʾ����"����̨"
		CCW_PR1(14,124,0xc9e4,1);
 		CCW_PR1(16,124,0xcca8,1);
   		CW_PR3(20,16,':');
		CW_PR3(21,16,'0');	
		
  		CCW_PR1(12,148,0xc8b7,1);	//��������ʾ����"ȷ��"
		CCW_PR1(14,148,0xc8cf,1);

 				
   		CCW_PR1(12,164,0xc8a1,1);	//��������ʾ����"ȡ��"
		CCW_PR1(14,164,0xcffb,1);

	} 

	W_DIAMOND(10,LANGUAGE?96:15);	//ѡ������ʾ
	W_HDIAMOND(10,LANGUAGE?112:16);
	W_HDIAMOND(10,LANGUAGE?128:17);
	W_HDIAMOND(10,LANGUAGE?152:18);
	W_HDIAMOND(10,LANGUAGE?168:19);
	
}

/*********************************************/
/*	���ܣ����°�����������ѡ������ѡ��
��ڲ�������
���ڲ�������
/*********************************************/
void SaveAllMessage_Updn();
void SaveAllMessage_Updn()
{
	if(BUFFER4[0]>=0&&BUFFER4[0]<=4)
	{
		if(G_Key == UP)	//����
		{
			G_Key=0;	//��������
			if(BUFFER4[0]>0)
			{
				BUFFER4[0]--;	//ѡ�����޸�
				if(LANGUAGE==0)	//Ӣ�Ĳ˵�ѡ������ʾ
				{
					W_DIAMOND(10,BUFFER4[0]+15);
					W_HDIAMOND(10,BUFFER4[0]+16);	
				}	
				
				else			//���Ĳ˵�ѡ������ʾ
				{
					if(BUFFER4[0]==3)
					{
						W_DIAMOND(10,LANGUAGE?152:18);
						W_HDIAMOND(10,LANGUAGE?168:19);
					}
					
					if(BUFFER4[0]==2)
					{
						W_DIAMOND(10,LANGUAGE?128:17);
						W_HDIAMOND(10,LANGUAGE?152:18);	
					}
					
					if(BUFFER4[0]==0||BUFFER4[0]==1)
					{
						W_DIAMOND(10,BUFFER4[0]*16+96);
						W_HDIAMOND(10,BUFFER4[0]*16+112);						
					}
				}
			}
		}
		if(G_Key == DOWN)	//����
		{
			G_Key=0;		//��������
			if(BUFFER4[0]<4)
			{			
				BUFFER4[0]++;		//ѡ�����һ
				if(LANGUAGE==0)		//Ӣ�Ĳ˵���LCDҳ������ʾ�޸���ϵ�ѡ����
				{
					W_DIAMOND(10,BUFFER4[0]+15);
					W_HDIAMOND(10,BUFFER4[0]+14);				
				}

				
				else				//���Ĳ˵���LCDҳ������ʾ�޸���ϵ�ѡ����
				{
					if(BUFFER4[0]==4)
					{
						W_HDIAMOND(10,LANGUAGE?152:18);
						W_DIAMOND(10,LANGUAGE?168:19);
					}
					
					if(BUFFER4[0]==3)
					{
						W_HDIAMOND(10,LANGUAGE?128:17);
						W_DIAMOND(10,LANGUAGE?152:18);	
					}
					
					if(BUFFER4[0]==2||BUFFER4[0]==1)
					{
						W_DIAMOND(10,BUFFER4[0]*16+96);
						W_HDIAMOND(10,BUFFER4[0]*16+80);						
					}
				}				
			}			
		}
	}

}

/*****************************************************/
/*	���ܣ����Ұ�����������ѡ��ͨ������Ϣ���ͣ�����̨
��ڲ�������
���ڲ�������
/*****************************************************/
void SaveAllMessage_Leftright();
void SaveAllMessage_Leftright()
{
	if(BUFFER4[0] == 0)		//��ͨ������ѡ��
	{
		if(G_Key == LEFT)	
		{
			G_Key=0;		//��������
			BUFFER4[1]=(BUFFER4[1]+3)%4;	//BUFFER4[1]��¼��Ӧͨ��
			CW_PR3(LANGUAGE?21:20,LANGUAGE?12:15,48+BUFFER4[1]);	//��ʾ��ǰѡ��ͨ��
		}
		if(G_Key == RIGHT)
		{
			G_Key=0;		//��������
			BUFFER4[1]=(BUFFER4[1]+1)%4;	//BUFFER4[1]��¼��Ӧͨ��
			CW_PR3(LANGUAGE?21:20,LANGUAGE?12:15,48+BUFFER4[1]);	//��ʾ��ǰѡ��ͨ��
		}
		
	}
	
	if(BUFFER4[0] == 1)		//����Ϣ������ѡ��
	{
		if(G_Key == LEFT)
		{
			G_Key=0;		//��������
			BUFFER4[2]=(BUFFER4[2]+26)%27;	//�޸Ķ�ӦBUFFER4[2]
			if(BUFFER4[2]==0) 	CW_PR3(LANGUAGE?21:20,LANGUAGE?14:16,'0');	//��ʾ�޸���ϵ���Ϣ���	
			else CW_PR3(LANGUAGE?21:20,LANGUAGE?14:16,64+BUFFER4[2]);
		}
		if(G_Key == RIGHT)
		{
			G_Key=0;
			BUFFER4[2]=(BUFFER4[2]+1)%27;
			if(BUFFER4[2]==0) 	CW_PR3(LANGUAGE?21:20,LANGUAGE?14:16,'0');	
			else CW_PR3(LANGUAGE?21:20,LANGUAGE?14:16,64+BUFFER4[2]);	
		}
		

	}
	
	if(BUFFER4[0] == 2)		//�Է���̨����ѡ��
	{
		if(G_Key == LEFT)
		{
			G_Key=0;		//��������
			BUFFER4[3]=(BUFFER4[3]+26)%27;	//�޸Ķ�ӦBUFFER4[3]
			if(BUFFER4[3]==0) 	CW_PR3(LANGUAGE?21:20,LANGUAGE?16:17,'0');	//��ʾ�޸���ϵ���Ϣ���	
			else CW_PR3(LANGUAGE?21:20,LANGUAGE?16:17,64+BUFFER4[3]);
		}
		
		if(G_Key == RIGHT)
		{
			G_Key=0;
			BUFFER4[3]=(BUFFER4[3]+1)%27;
			if(BUFFER4[3]==0) 	CW_PR3(LANGUAGE?21:20,LANGUAGE?16:17,'0');	
			else CW_PR3(LANGUAGE?21:20,LANGUAGE?16:17,64+BUFFER4[3]);
		}

	}
}


//*********************************************************/
/*	���ܣ�ENT����������������ȷ�ϻ���ȡ���������������˵�
��ڲ�������
���ڲ�������
/**********************************************************/
void SaveAllMessage_Dealing();
void SaveAllMessage_Dealing()
{
	if(G_Key == ENT)
	{
		LANHELP=1;	//�ָ�LANHELP�ĳ�ʼֵ
		G_Key=0;	//��������
		if(BUFFER4[0] == 3)	//ѡ��ȷ��
		{
			FLAG=0;			//����ѭ��
			if(Checkinfo.Printerror == 0)	//��ӡ������
			{
				PublicReturn=4;//���빫�ô�ӡ���棬����4�����ӱ��˵�����
				STATE=16;		//Message_Printing��״̬Ϊ16			
			}
			else
			{
				BUFFER4[0]=0; 	//�����ӡ������治�᷵�ر����棬�����ȶԱ������������
				BUFFER4[1]=0;
				BUFFER4[2]=0;
				BUFFER4[3]=0;
				PublicReturn=4;	//���빫�ó�����棬����4�����ӱ��˵�����
				STATE=15;		//Message_PrintError��״̬Ϊ15
			}
		}
		
		if(BUFFER4[0] == 4)	//ȡ�����ز���
		{
			BUFFER4[0]=0;	//������ʹ�õ�ȫ�ֱ�������
			BUFFER4[1]=0;
			BUFFER4[2]=0;
			BUFFER4[3]=0;
			FLAG=0;			//����ѭ��
			STATE=2010;		//SavePitchPrint��״̬Ϊ2010
		}
	}
}









/*******************************************************************/
/*	���ܣ���ӡ��Χ��ѡ�񣬰���ͨ������Ϣ��𣬷���̨
		  BUFFER4[0] ѡ����
          BUFFER4[1] ͨ��,0��ʾȫѡ��1��ʾ518��2��ʾ490��3��ʾ4209.5
          BUFFER4[2] ��Ϣ���ͣA0��ʾȫѡ��1��26�ֱ��ʾA~Z
          BUFFER4[3] ����̨,0��ʾȫѡ��1��26�ֱ��ʾA~Z
��ڲ�������
���ڲ�������
/*******************************************************************/
void RunSaveAllMessage()
{
    maske=0;
    maskc=0;
	LANHELP=3;		//��LANHELP==3ʱ����ʾ�󴰿�
//	Checkprint();	//��ӡ��������
	BUFFER4[0]=0;	//������ʹ�õ�ȫ�ֱ�������
			BUFFER4[1]=0;
			BUFFER4[2]=0;
			BUFFER4[3]=0;
	SaveAllMessage_Paintintial();
	
	while(FLAG)
	{
		SaveAllMessage_Updn();
		SaveAllMessage_Leftright();
		SaveAllMessage_Dealing();
		run_tip();
	}
}