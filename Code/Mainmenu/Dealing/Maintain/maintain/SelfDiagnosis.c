#include <stdio.h>
#include <stdlib.h>
#include "Eprom.h"
#include "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "code.h"
#include "MessageDeal.h"
//#define FPGARW(offset)   *((volatile word *)(0x002f8000+offset))   //�Լ��ӵĹ���FPGA��д


/************************************************/
/*	���ܣ��Լ캯��SelfDiagnosis���ֽ�����ʾ����
��ڲ�������
���ڲ�������
/************************************************/
void SelfDiagnosis_Partpaint();
void SelfDiagnosis_Partpaint()
{

	char i;
	if(LANGUAGE)
	{
			CCW_PR1(10,52,0xd6bb,1);	//����������"ֻ���洢��"
	 		CCW_PR1(12,52,0xb6c1,1);
	 		CCW_PR1(14,52,0xb4e6,1);
	 		CCW_PR1(16,52,0xb4a2,1);
	 		CCW_PR1(18,52,0xc6f7,1);
	 		
	  		
	 		CCW_PR1(10,68,0xcbe6,1);	//����������"����洢��"
	 		CCW_PR1(12,68,0xbbfa,1);
	 		CCW_PR1(14,68,0xb4e6,1);
	  		CCW_PR1(16,68,0xb4a2,1);
	 		CCW_PR1(18,68,0xc6f7,1);
	 		
	 		CCW_PR1(10,84,0xb4ae,1);	//����������"����"
	 		CCW_PR1(12,84,0xbfda,1);
		
	 		
	 		CCW_PR1(10,100,0xb5e7,1);	//����������"��Դ"
	 		CCW_PR1(12,100,0xd4b4,1);
	 	
	 		
	 		CCW_PR1(10,116,0xccec,1);	//����������"����"
	 		CCW_PR1(12,116,0xcfdf,1);
	 		
	  		CCW_PR1(10,132,0xcda8,1);	//�ڰ�������"ͨ��һ"
	 		CCW_PR1(12,132,0xb5c0,1);
	 	 	CCW_PR1(14,132,0xd2bb,1);
	 	 	
	  		CCW_PR1(10,148,0xcda8,1);	//�ھ�������"ͨ����"
	 		CCW_PR1(12,148,0xb5c0,1);
	 	 	CCW_PR1(14,148,0xb6fe,1);		 
	 
	   		CCW_PR1(10,164,0xcda8,1);	//��ʮ������"ͨ����"
	 		CCW_PR1(12,164,0xb5c0,1);
	 	 	CCW_PR1(14,164,0xc8fd,1);	

	 	 	for(i=0;i<8;i++)
			{
				CW_PR3(20,7+2*i,':');
			}
	}

	else
	{
			/* д��ڶ������� ROM */
			CTAB[0]='R';	CTAB[1]='O';	CTAB[2]='M';		
			CW_PR(8,5,3); 
			 

			/* д����������� RAM*/
			CTAB[0]='R';	CTAB[1]='A';	CTAB[2]='M';	
			CW_PR(8,7,3);

			/* д����������� SERIAL PORT*/
			CTAB[0]='S';	CTAB[1]='E';	CTAB[2]='R';	CTAB[3]='I';	CTAB[4]='A';	CTAB[5]='L';
			CTAB[7]='P';	CTAB[8]='O';	CTAB[9]='R';	CTAB[10]='T';	;	
			CW_PR(8,9,11);
			

			/* д����������� POWER*/
			CTAB[0]='P';	CTAB[1]='O';	CTAB[2]='W';	CTAB[3]='E';	CTAB[4]='R';
			CW_PR(8,11,5);

			/* д����������� ANTENNA*/
			CTAB[0]='A';	CTAB[1]='N';	CTAB[2]='T';	CTAB[3]='E';	CTAB[4]='N';
			CTAB[5]='N';	CTAB[6]='A';	;
			CW_PR(8,13,7);
			
			/* д����������� 518KHZ*/
			CTAB[0]='5';	CTAB[1]='1';	CTAB[2]='8';	CTAB[3]='K';	CTAB[4]='H';
			CTAB[5]='Z';	;
			CW_PR(8,15,6);
				
			/* д��ڰ������� 490KHZ*/
			CTAB[0]='4';	CTAB[1]='9';	CTAB[2]='0';	CTAB[3]='K';	CTAB[4]='H';
			CTAB[5]='Z';	;
			CW_PR(8,17,6);
			

			/* д��ھ������� 4209.5KHZ*/
			CTAB[0]='4';	CTAB[1]='2';	CTAB[2]='0';	CTAB[3]='9';	CTAB[4]='.';	CTAB[5]='5';
			CTAB[6]='K';	CTAB[7]='H';	CTAB[8]='Z';	;	
			CW_PR(8,19,9);

			for(i=0;i<8;i++)
			{
				CW_PR3(19,5+2*i,':');
			}	
	}
	
}


/************************************************/
/*	���ܣ��Լ�����ʾ����
��ڲ�������
���ڲ�������
/************************************************/
void Diagresult_Paint(char list);
void Diagresult_Paint(char list)
{
	char i,temp=0;
	if(LANGUAGE)	//���Ĳ˵�
	{
		for(i=0;i<8;i++)
		{
			if(Diaglog[list].diagresult[i])
			{
				if(i==2) CW_PR3(21,11,Diaglog[list].diagresult[i]+48);
				else 			//�Լ������ʾ������
				{
			 		CCW_PR1(21,52+16*i,0xb9ca,1);
			 		CCW_PR1(23,52+16*i,0xd5cf,1);
				}
				temp=1;
			}
			
			else				//�Լ�ɹ���ʾ������
			{
		 		CCW_PR1(21,52+16*i,0xd5fd,1);
		 		CCW_PR1(23,52+16*i,0xb3a3,1);
			}
		}	
		
	}
	
	else
	{
		for(i=0;i<8;i++)
		{
			if(Diaglog[list].diagresult[i])
			{
				if(i==2) CW_PR3(20,6,Diaglog[list].diagresult[i]+48);
				else 			//�Լ������ʾ��BAD
				{
					CTAB[0]='B';	CTAB[1]='A';	CTAB[2]='D';		
					CW_PR(20,5+2*i,3);	
				}
				temp=1;
			}
			
			else				//�Լ�ɹ���ʾ��GOOD
			{
				CTAB[0]='G';	CTAB[1]='O';	CTAB[2]='O';	CTAB[3]='D';	
				CW_PR(20,5+2*i,4);
			}
		}	
	}
	
		if(temp&&Buzzer[2])
		{
			FPGARW(3600)=0X08;
			Buzzerstate|=0x02;
		}
}

/************************************************/
/*	���ܣ��Լ캯��SelfDiagnosis��ʾ����
��ڲ�������
���ڲ�������
/************************************************/
void SelfDiagnosis_Paintintial();
void SelfDiagnosis_Paintintial()
{
	char i;
//	CLEAR1();	//��һ���Ͷ����Ĵ洢�ռ�
	
	if(LANGUAGE==0)	//Ӣ�Ľ���
	{

		/* ��ͷSELF DIAGNOSIS MENU */
		CTAB[2]='S';	CTAB[3]='E';	CTAB[4]='L';	CTAB[5]='F';
		CTAB[7]='D';	CTAB[8]='I';	CTAB[9]='A';	CTAB[10]='G';
		CTAB[11]='N';	CTAB[12]='O';	CTAB[13]='S';	CTAB[14]='I';	CTAB[15]='S';
		CTAB[17]='M';	CTAB[18]='E';	CTAB[19]='N';	CTAB[20]='U';		
		CW_PR(0,1,21);
		
		/* д���һ������SELF DIGANOSIS */
		CTAB[0]='S';	CTAB[1]='E';	CTAB[2]='L';	CTAB[3]='F';	
		CTAB[5]='D';	CTAB[6]='I';	CTAB[7]='A';	CTAB[8]='G';	CTAB[9]='N';
		CTAB[10]='O';	CTAB[11]='S';	CTAB[12]='I';	CTAB[13]='S';
		CW_PR(5,3,14);

		SelfDiagnosis_Partpaint();


		
		/* д���ʮ������ LCD DIAGNOSIS*/
		CTAB[0]='L';	CTAB[1]='C';	CTAB[2]='D';		
		CTAB[4]='D';	CTAB[5]='I';	CTAB[6]='A';	CTAB[7]='G';	CTAB[8]='N';
		CTAB[9]='O';	CTAB[10]='S';	CTAB[11]='I';	CTAB[12]='S';	CTAB[13]=':';
		CW_PR(5,22,14);
		
		CTAB[0]='O';	CTAB[1]='F';	CTAB[2]='F';//��ʼ��Һ���Լ��
		CW_PR(19,22,3);
		
		/* д���ʮ������ DIAGNOSIS LOG*/				
		CTAB[0]='D';	CTAB[1]='I';	CTAB[2]='A';	CTAB[3]='G';	CTAB[4]='N';
		CTAB[5]='O';	CTAB[6]='S';	CTAB[7]='I';	CTAB[8]='S';	CTAB[10]='L';
		CTAB[11]='O';	CTAB[12]='G';	
		CW_PR(5,26,13);
		
		W_DIAMOND(3,3);		//���ѡ�������ʾ
		W_HDIAMOND(3,22);
		W_HDIAMOND(3,26);
		if(BUFFER2[0]!=0)	
		{
			W_DIAMOND(3,BUFFER2[0]*4+18);	
			W_HDIAMOND(3,3);	
		}	
	}
 	
 	else	//���Ľ���
 	{
 		W_XLINE(0,319,25);	
		W_CLEARXLINE(0,319,22);
		W_CLEARXLINE(0,319,230);
		
 		CCW_PR1(1,7,0xd7d4,1);		//��һ������"�Լ�˵� �Զ�"
 		CCW_PR1(3,7,0xbcec,1);
 		CCW_PR1(5,7,0xb2cb,1);
  		CCW_PR1(7,7,0xb5a5,1);
  				
 		CCW_PR1(35,7,0xcad6,1);
 		CCW_PR1(37,7,0xb6Af,1);
 		
 		CCW_PR1(6,32,0xd7d4,1);		//�ڶ�������"�Լ�"
 		CCW_PR1(8,32,0xbcec,1);
 		
 	
 		SelfDiagnosis_Partpaint();	 	
		
   		CCW_PR1(6,192,0xd2ba,1);	//��ʮһ������"Һ�����:�ر�"
 		CCW_PR1(8,192,0xbea7,1);
 	 	CCW_PR1(10,192,0xbcec,1);
 	 	CCW_PR1(12,192,0xb2e2,1);
 	 	CW_PR3(14,25,':');
  	 	CCW_PR1(15,192,0xb9d8,1);
 	 	CCW_PR1(17,192,0xb1d5,1);
 	 		 			 
 
   		CCW_PR1(6,216,0xd7d4,1);	//��ʮ��������"�Լ���־"
 		CCW_PR1(8,216,0xbcec,1);
 	 	CCW_PR1(10,216,0xc8d5,1);
 	 	CCW_PR1(12,216,0xd6be,1);	
 	 
	
		
	 	W_DIAMOND(3,36);
		W_HDIAMOND(3,196);
		W_HDIAMOND(3,220);
		if(BUFFER2[0]!=0)	//���ѡ�������ʾ
		{
			W_DIAMOND(3,BUFFER2[0]*24+172);	
			W_HDIAMOND(3,36);	
		}
 
 	}

	W_YLINE(0,0,239);
	W_YLINE(319,0,239);	

	W_Mode(35,7,32,1);			//�ֶ����Զ�ģʽ����ʾ	

 }
 
 
/************************************************/
/*	���ܣ����°�����������ѡ������ѡ��
��ڲ�������
���ڲ�������
/************************************************/
void SelfDiagnosis_Updn();
void SelfDiagnosis_Updn()
 {
	if (G_Key==UP)
	{
		if(BUFFER2[0]>0)
		{
			BUFFER2[0]=BUFFER2[0]-1;        //������������
			G_Key=0;
			
			if(BUFFER2[0]==0)				//��ʾѡ����ѡ����
			{
				W_DIAMOND(3,LANGUAGE?36:3);	
				W_HDIAMOND(3,LANGUAGE?196:22);	
			}
			
			if(BUFFER2[0]==1)
			{
				W_DIAMOND(3,LANGUAGE?196:22);	
				W_HDIAMOND(3,LANGUAGE?220:26);	
			}

		
		}
	}
	
	if (G_Key==DOWN)
	{
		if(BUFFER2[0]<3)
		{
			BUFFER2[0]=BUFFER2[0]+1;       	//������������
			G_Key=0;
			
			if(BUFFER2[0]==1)				//��ʾѡ����ѡ����
			{
				W_DIAMOND(3,LANGUAGE?196:22);	
				W_HDIAMOND(3,LANGUAGE?36:3);	
			}
			
			if(BUFFER2[0]==2)
			{
				W_DIAMOND(3,LANGUAGE?220:26);	
				W_HDIAMOND(3,LANGUAGE?196:22);	
			}
			
       	}
	}	
}
/************************************************/
/*	���ܣ����Ұ�����������Һ����⺯��
��ڲ�������
���ڲ�������
/************************************************/
void SelfDiagnosis_Leftright() ;
void SelfDiagnosis_Leftright()                
{
    if ((G_Key==LEFT||G_Key==RIGHT)&&BUFFER2[0]==1)
    {
  	sword i;
	 	G_Key=0; 			//��������                
		BUFFER2[1]=(BUFFER2[1]+1)%2;
		
  		if(BUFFER2[1])		//�Լ쿪
		{
			if(LANGUAGE)	//������ʾ������
			{
			  	CCW_PR1(15,192,0xbfaa,1);
 	 			CCW_PR1(17,192,0xc6f4,1);	
			}
			
			else			//Ӣ����ʾ��ON
			{
				CTAB[0]='O';	CTAB[1]='N';
				CW_PR(19,22,3);			
			}
			WriteCode(0x59);//��겻��ʾ��һ������������32Hz��˸
			WriteData(0xa8); 
		}
		

		else				//�Լ쿪
		{
		
			if(LANGUAGE)	//������ʾ���ر�
			{
		  	 	CCW_PR1(15,192,0xb9d8,1);
		 	 	CCW_PR1(17,192,0xb1d5,1);
			}
			else			//Ӣ����ʾ��OFF
			{
				CTAB[0]='O';	CTAB[1]='F'; CTAB[2]='F';	
				CW_PR(19,22,4);		
			}
			
			WriteCode(0x59);//�ر���Ļ����˸ 
			WriteData(0x54);
		} 
    
 	}
}
 
/***************************************************************/
/*	���ܣ�CLR���������������ص��ϲ����ά���˵�
��ڲ�������
���ڲ�������
/***************************************************************/
void SelfDiagnosis_Return();
void SelfDiagnosis_Return()
 {
	if (G_Key==CLR&&STATE==440)      
	{
		G_Key=0;		//��������
		BUFFER2[0]=0;	//���˵�ʹ��ȫ�ֱ�������
		BUFFER2[1]=0;     
		FLAG=0;			//����ѭ��
		STATE=44;		//�ϼ��˵�Maintain״̬Ϊ44
		State44parameter=0;
	}
 }
 
/***************************************************************/
/*	���ܣ�ENT�����������������Լ���������߲鿴�Լ���־
��ڲ�������
���ڲ�������
/***************************************************************/
void SelfDiagnosis_Dealing();
void SelfDiagnosis_Dealing()
{
	 if(G_Key==ENT&&BUFFER2[0]==0)
	 {
	 	char i;
	 	char list;
	 	if(LANGUAGE)		//�����һ�ε��Լ���
	 	{
	 	 	for(i=0;i<8;i++)
			{
				CCW_PR1(21,52+16*i,0x1760,0);
		 		CCW_PR1(23,52+16*i,0x1760,0);	
			}	
	 	}
	 	
	 	else
	 	{
		 	for(i=0;i<8;i++)
		 	{
				CW_PR(20,5+2*i,8);
			}	 		
	 	}

	 	list=Diaglogs;
	 	G_Key=0;				//��������
//	 	IPR2&=0xfffc;			//��IRQA���жϣ��Լ�����а�����Ч
		DISABLEIRQA();
	    Selfdiag(1);				//�����Լ캯��
	    Diagresult_Paint(list);	//���Լ�����ʾ��LCD
//	    IPR2|=0x0002;			//���ж�
		ENABLEIRQA();
	 }
    
    else if (G_Key==ENT&&BUFFER2[0]==2) 	//�����Լ���־�˵�                        
	{   
		G_Key=0;				//��������
		FLAG=0;					//����ѭ��
		STATE=4400;	         	//�Լ���־�˵�״̬4400		
	}
}

/***************************************************/
/*	���ܣ��Լ�˵������н��ջ��Լ죬Һ���Լ죬����
          �鿴�Լ���־
          
��ڲ�������
���ڲ�������
/***************************************************/ 
void RunSelfDiagnosis()
{
    maske=0;
    maskc=0;
	SelfDiagnosis_Paintintial();
	while(FLAG)
	{
		SelfDiagnosis_Updn();
		SelfDiagnosis_Leftright();		
		SelfDiagnosis_Dealing();
		SelfDiagnosis_Return();
		run_tip();	
	}

}
	
