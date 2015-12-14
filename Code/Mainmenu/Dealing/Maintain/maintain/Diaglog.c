#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "Eprom.h"
#include "code.h"


/***************************************************/
/*	���ܣ���������ƶ���Ǻ����Ͻ���Ϣ����ʾ��
��ڲ�������
���ڲ�������
/***************************************************/ 
void Diaglog_biaoji();
void Diaglog_biaoji()
{
	if(Diaglogn-(char)BUFFER3[0]>1) W_DOWNMOVE(39,27);	//���ƶ���Ǵ���
	else W_CLEARUPDN(39,27);	
	
	if(BUFFER3[0]) W_UPMOVE(39,LANGUAGE?4:3);			//���ƶ���Ǵ���
	else W_CLEARUPDN(39,LANGUAGE?4:3);
	
	if(BUFFER3[0]==9)									//��ʾ�Լ���־����λ��
	{
		if(LANGUAGE==0)
		DISASCII(3,6,BUFFER3[0]+1);
		else
		{
			CCW_PR1(2,48,0x1980,0);
			CCW_PR1(4,48,0x1960,0);
		}
		
	}
	else 
	{
		if(LANGUAGE==0)
		CW_PR3(4,6,BUFFER3[0]+49);
		else
		{
			CCW_PR1(4,48,0x1980+BUFFER3[0]*32,0);
		}		
	}
		
}
/***************************************************/
/*	���ܣ��Լ���־�����ʾ����
��ڲ�������
���ڲ�������
/***************************************************/ 
void Diaglog_Paint(char list);
void Diaglog_Paint(char list)
{
	char i;
	if(LANGUAGE)	//���Ĳ˵�
	{
		for(i=0;i<8;i++)
		{
			if(Diaglog[list].diagresult[i])
			{
				if(i==2) CW_PR3(21,13,Diaglog[list].diagresult[i]+48);
				else 			//�Լ������ʾ������
				{
			 		CCW_PR1(21,72+16*i,0xb9ca,1);
			 		CCW_PR1(23,72+16*i,0xd5cf,1);
				}
			}
			
			else				//�Լ�ɹ���ʾ������
			{
		 		CCW_PR1(21,72+16*i,0xd5fd,1);
		 		CCW_PR1(23,72+16*i,0xb3a3,1);
			}
		}	
		
	}
	
	else			//Ӣ�Ĳ˵�
	{
		for(i=0;i<8;i++)
		{
			if(Diaglog[list].diagresult[i])
			{
				if(i==2) CW_PR3(20,6,Diaglog[list].diagresult[i]+48);
				else 			//�Լ������ʾ��BAD
				{
					CTAB[0]='B';	CTAB[1]='A';	CTAB[2]='D';		
					CW_PR(20,8+2*i,4);	
				}
			}
			
			else				//�Լ�ɹ���ʾ��GOOD
			{
				CTAB[0]='G';	CTAB[1]='O';	CTAB[2]='O';	CTAB[3]='D';	
				CW_PR(20,8+2*i,4);
			}
		}	
	}
}
/***************************************************/
/*	���ܣ��Լ���־�Լ�ʱ����ʾ����
��ڲ�������
���ڲ�������
/***************************************************/ 
void Diaglogtime_Paint(char list);
void Diaglogtime_Paint(char list)
{
	DISASCII(LANGUAGE?17:15,LANGUAGE?7:6,Diaglog[list].date[0]);			//��ʾ����ʱ�����ֵ
	DISASCII(LANGUAGE?20:18,LANGUAGE?7:6,Diaglog[list].date[1]);
	DISASCII(LANGUAGE?23:21,LANGUAGE?7:6,Diaglog[list].date[2]);
	DISASCII(LANGUAGE?26:24,LANGUAGE?7:6,Diaglog[list].time[1]);
	DISASCII(LANGUAGE?29:27,LANGUAGE?7:6,Diaglog[list].time[0]);
}

/***************************************************/
/*	���ܣ��Լ���־Diaglog��ʾ����
��ڲ�������
���ڲ�������
/***************************************************/ 
void Diaglog_Paintintial();
void Diaglog_Paintintial()
 {
	char i;
	if(Diaglogn) 	//�����Լ���־��������־����
	{
		BUFFER3[1]=(Diaglogs-Diaglogn+10)%10;				//�洢��ʼ�洢�����λ��	
		Eprom_Diaglog_Read(&Diaglog[BUFFER3[1]],BUFFER3[1]);//�������ȡ����־
	}
	
	if(LANGUAGE==0)	//��ʱΪӢ�Ľ���
	{
		/* ��ͷ */
		CTAB[2]='S';	CTAB[3]='E';	CTAB[4]='L';	CTAB[5]='F';
		CTAB[7]='D';	CTAB[8]='I';	CTAB[9]='A';	CTAB[10]='G';
		CTAB[11]='N';	CTAB[12]='O';	CTAB[13]='S';	CTAB[14]='I';	CTAB[15]='S';
		CTAB[17]='L';	CTAB[18]='O';	CTAB[19]='G';	
		CW_PR(0,1,20);
		
		if(Diaglogn) //�����Լ���־
		{
		/* д���һ������ RESULT*/
			CTAB[5]='.';
			CTAB[6]='R';	CTAB[7]='E';	CTAB[8]='S';	CTAB[9]='U';	
			CTAB[10]='L';	CTAB[11]='T';
			
			CTAB[13]='2';	CTAB[14]='0';	CTAB[17]='/';CTAB[20]='/';	CTAB[23]='/';
			CTAB[26]=':';
			CW_PR(0,6,27);
			


		/* д��ڶ������� ROM*/
			CTAB[0]='R';	CTAB[1]='O';	CTAB[2]='M';		
			CW_PR(8,8,3); 
			 

		/* д����������� RAM*/
			CTAB[0]='R';	CTAB[1]='A';	CTAB[2]='M';	
			CW_PR(8,10,3);

		/* д����������� SERIAL PORT*/
			CTAB[0]='S';	CTAB[1]='E';	CTAB[2]='R';	CTAB[3]='I';	CTAB[4]='A';	CTAB[5]='L';
			CTAB[7]='P';	CTAB[8]='O';	CTAB[9]='R';	CTAB[10]='T';	;	
			CW_PR(8,12,11);
			

		/* д����������� POWER*/
			CTAB[0]='P';	CTAB[1]='O';	CTAB[2]='W';	CTAB[3]='E';	CTAB[4]='R';
			CW_PR(8,14,5);

		/* д����������� ANTENNA*/
			CTAB[0]='A';	CTAB[1]='N';	CTAB[2]='T';	CTAB[3]='E';	CTAB[4]='N';
			CTAB[5]='N';	CTAB[6]='A';	;
			CW_PR(8,16,7);
			
		/* д����������� 518KHZ*/
			CTAB[0]='5';	CTAB[1]='1';	CTAB[2]='8';	CTAB[3]='K';	CTAB[4]='H';
			CTAB[5]='Z';	;
			CW_PR(8,18,6);
				
		/* д��ڰ������� 490KHZ*/
			CTAB[0]='4';	CTAB[1]='9';	CTAB[2]='0';	CTAB[3]='K';	CTAB[4]='H';
			CTAB[5]='Z';	;
			CW_PR(8,20,6);
			

		/* д��ھ������� 4209.5KHZ*/
			CTAB[0]='4';	CTAB[1]='2';	CTAB[2]='0';	CTAB[3]='9';	CTAB[4]='.';	CTAB[5]='5';
			CTAB[6]='K';	CTAB[7]='H';	CTAB[8]='Z';	;	
			CW_PR(8,22,9);
			
			for(i=0;i<8;i++)
			{
				CW_PR3(19,8+2*i,':');
			}		
	
			Diaglog_Paint(BUFFER3[1]);				//��ʾ��־���
		    Diaglogtime_Paint(BUFFER3[1]);			//��ʾ��־�Լ�ʱ��
		    Diaglog_biaoji();						//��ʾ���¿ɷ������	
		}

		else 	//�����Լ���־
		{
			CTAB[0]='N';	CTAB[1]='O';	CTAB[3]='D';	CTAB[4]='I';	CTAB[5]='A';				
			CTAB[6]='G';	CTAB[7]='N';	CTAB[8]='O';	CTAB[9]='S';	CTAB[11]='L';		
			CTAB[12]='O';  CTAB[13]='G';  CTAB[14]='!';	
			CW_PR(8,10,15);
		}
		
	}
	
	else
	{
		
		W_XLINE(0,319,25);	
		W_CLEARXLINE(0,319,22);

		if(Diaglogn) //�����Լ���־
		{
	 		CCW_PR1(1,7,0xd7d4,1);	//��һ������"�Լ���־"
	 		CCW_PR1(3,7,0xbcec,1);
	 		CCW_PR1(5,7,0xc8d5,1);
	  		CCW_PR1(7,7,0xd6be,1);

	 		
	 		CCW_PR1(6,48,0xd7d4,1);		//�ڶ�������"�Լ���"
	 		CCW_PR1(8,48,0xbcec,1);
	  		CCW_PR1(10,48,0xbde1,1);
	 		CCW_PR1(12,48,0xb9fb,1);		
	  		CTAB[13]='2';	CTAB[14]='0';	CTAB[17]='/';CTAB[20]='/';	CTAB[23]='/';
			CTAB[26]=':';
			CW_PR(2,7,27);
					
	 		
	 		CCW_PR1(10,72,0xd6bb,1);	//����������"ֻ���洢��"
	 		CCW_PR1(12,72,0xb6c1,1);
	 		CCW_PR1(14,72,0xb4e6,1);
	 		CCW_PR1(16,72,0xb4a2,1);
	 		CCW_PR1(18,72,0xc6f7,1);
	 		
	  		
	 		CCW_PR1(10,88,0xcbe6,1);	//����������"����洢��"
	 		CCW_PR1(12,88,0xbbfa,1);
	 		CCW_PR1(14,88,0xb4e6,1);
	  		CCW_PR1(16,88,0xb4a2,1);
	 		CCW_PR1(18,88,0xc6f7,1);
	 		
	 		CCW_PR1(10,104,0xb4ae,1);	//����������"����"
	 		CCW_PR1(12,104,0xbfda,1);
		
	 		
	 		CCW_PR1(10,120,0xb5e7,1);	//����������"��Դ"
	 		CCW_PR1(12,120,0xd4b4,1);
	 	
	 		
	 		CCW_PR1(10,136,0xccec,1);	//����������"����"
	 		CCW_PR1(12,136,0xcfdf,1);
	 		
	  		CCW_PR1(10,152,0xcda8,1);	//�ڰ�������"ͨ��һ"
	 		CCW_PR1(12,152,0xb5c0,1);
	 	 	CCW_PR1(14,152,0xd2bb,1);
	 	 	
	  		CCW_PR1(10,168,0xcda8,1);	//�ھ�������"ͨ����"
	 		CCW_PR1(12,168,0xb5c0,1);
	 	 	CCW_PR1(14,168,0xb6fe,1);		 
	 
	   		CCW_PR1(10,184,0xcda8,1);	//��ʮ������"ͨ����"
	 		CCW_PR1(12,184,0xb5c0,1);
	 	 	CCW_PR1(14,184,0xc8fd,1);
	 	 	
			
	 	 
	 	 	for(i=0;i<8;i++)
			{
			
			
				CW_PR3(20,10+2*i,':');
				
			}	
			
			Diaglog_Paint(BUFFER3[1]);					//��ʾ��־���
		    Diaglogtime_Paint(BUFFER3[1]);				//��ʾ��־�Լ�ʱ��
		    Diaglog_biaoji();							//��ʾ���¿ɷ������		
		}
		
		else	//���Լ���־
		{
	
			CCW_PR1(10,88,0xcede,1);	//����������"���Լ���־��"
	 		CCW_PR1(12,88,0xd7d4,1);
	 		CCW_PR1(14,88,0xbcec,1);
	  		CCW_PR1(16,88,0xc8d5,1);
	 		CCW_PR1(18,88,0xd6be,1);
	 		CCW_PR1(20,88,0x1780,0);	 		
	 		
		}
	
	}

	W_Mode(35,7,32,1);			//�ֶ����Զ�ģʽ����ʾ	
	
	W_YLINE(0,0,239);
	W_YLINE(319,0,239);	


 }
/************************************************/
/*	���ܣ����·����Լ���־���
��ڲ�������
���ڲ�������
/************************************************/ 
void Diaglog_Updn();
void Diaglog_Updn()
{
	char list;
	if (G_Key==UP)
	{
		G_Key=0;
		if(BUFFER3[0]>0)							//������һ����־
		{
			BUFFER3[0]=BUFFER3[0]-1;			
			list=(BUFFER3[1]+BUFFER3[0])%10;
			Eprom_Diaglog_Read(&Diaglog[list],list);//�������ȡ����־
			Diaglog_Paint(list);					//��ʾ��־���
		    Diaglogtime_Paint(list);				//��ʾ��־�Լ�ʱ��
		    Diaglog_biaoji();						//��ʾ���¿ɷ������
		
		}
	}

	else if (G_Key==DOWN)
	{
		
		G_Key=0;
		if(Diaglogn-(char)BUFFER3[0]>1)				//����������־
		{
			BUFFER3[0]=BUFFER3[0]+1;       			
			list=(BUFFER3[1]+BUFFER3[0])%10;
			Eprom_Diaglog_Read(&Diaglog[list],list);//�������ȡ����־
			Diaglog_Paint(list);					//��ʾ��־���
		    Diaglogtime_Paint(list);				//��ʾ��־�Լ�ʱ��
		    Diaglog_biaoji();						//��ʾ���¿ɷ������			
	   	}
	}	
}


/***************************************************/
/*	���ܣ������ϼ��˵�SelfDiagnosis
��ڲ�������
���ڲ�������
/***************************************************/ 
void Diaglog_Return();
void Diaglog_Return()
{
	if (G_Key==CLR)     
	{
		G_Key=0;		//��������
		BUFFER3[0]=0;	//���˵�ʹ�õ�ȫ�ֱ�������
		BUFFER3[1]=0;   
		FLAG=0;			//����ѭ��
		STATE=440;		//SelfDiagnosis״̬Ϊ440
	}
}

/***************************************************/
/*	���ܣ��Լ���־��������ʾ�����10���Լ���
��ڲ�������
���ڲ�������
/***************************************************/ 
void RunDiaglog();
void RunDiaglog()
{
    maske=0;
    maskc=0;
	Diaglog_Paintintial();
	while(FLAG)
	{
		Diaglog_Updn();		
		Diaglog_Return();
		run_tip();		
	}
}
	
