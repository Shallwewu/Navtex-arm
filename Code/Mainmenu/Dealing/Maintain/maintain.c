#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "code.h"

//********************************************/
/*���ܣ�ά���˵�Maintain����ʾ����
��ڲ�������
���ڲ�������
/*********************************************/
void Maintain_Paintintial();
void Maintain_Paintintial()
{
	byte i;
	if(subback==10)
	{
		RecoverData();	//�����Ӳ˵����أ�ֻ����и������ݵĻָ�
	}

	else
	{
		if(LANGUAGE==0)	//Ӣ�Ĳ˵�
		{

			 /* д���ͷ����MAINTAIN */
			CTAB[2]='M';	CTAB[3]='A';	CTAB[4]='I';	CTAB[5]='N';	CTAB[6]='T';
			CTAB[7]='A';	CTAB[8]='I';	CTAB[9]='N';
			CW_PR(0,1,10);

			/* д���һ������SELF DIAGNISOS */
			CTAB[0]='S';	CTAB[1]='E';	CTAB[2]='L';	CTAB[3]='F';	 
			CTAB[5]='D';	CTAB[6]='I';	CTAB[7]='A';	CTAB[8]='G';	CTAB[9]='N';
			CTAB[10]='O';	CTAB[11]='S';	CTAB[12]='E'; 
			CW_PR(5,4,13);

			/* д��ڶ�������NAVTEX ALARM */
			CTAB[0]='R';	CTAB[1]='E';	CTAB[2]='C';	CTAB[3]='O';	CTAB[4]='V'; 
			CTAB[5]='E';	CTAB[6]='R';	CTAB[8]='F';	CTAB[9]='A';
			CTAB[10]='C';	CTAB[11]='T';	CTAB[12]='O';	CTAB[13]='R';  CTAB[14]='Y';
			CTAB[16]='S';	CTAB[17]='E';   CTAB[18]='T';
			CW_PR(5,8,19);  


			/* д�����������STATE */
			CTAB[0]='S';	CTAB[1]='T';	CTAB[2]='A';	CTAB[3]='T';	CTAB[4]='E';
			CW_PR(5,12,5);


			/* д�����������SOFTWARE VERSION */
			CTAB[0]='S';	CTAB[1]='O';	CTAB[2]='F';	CTAB[3]='T';	CTAB[4]='W'; 
			CTAB[5]='A';	CTAB[6]='R';	CTAB[7]='E';	CTAB[9]='V';
			CTAB[10]='E';	CTAB[11]='R';	CTAB[12]='S';	CTAB[13]='I';  	CTAB[14]='O';
			CTAB[15]='N';	CTAB[16]=':';	CTAB[17]='2';   CTAB[18]='.';	CTAB[19]='0';
			CW_PR(5,16,20);	
		}
		
		else	//���Ĳ˵�
		{

			CLEARXLINE(0,39,22);
			XLINE(0,39,23);
	 		CCW_PR1(1,7,0xceac,1);		//��һ������"ά��"
	 		CCW_PR1(3,7,0xbba4,1);
		
	 		CCW_PR1(5,40,0xd7d4,1);		//�ڶ�������"�Լ�"
	 		CCW_PR1(7,40,0xbcec,1);
	  		
	 		CCW_PR1(5,72,0xbbd6,1);		//����������"�ָ���������"
	 		CCW_PR1(7,72,0xb8b4,1);
	 		CCW_PR1(9,72,0xb3f6,1);
	 		CCW_PR1(11,72,0xb3a7,1);
	 	 	CCW_PR1(13,72,0xc9e8,1);
	  	 	CCW_PR1(15,72,0xd6c3,1);

	 		CCW_PR1(5,104,0xbdd3,1);	//����������"���ջ�״̬"
	 		CCW_PR1(7,104,0xcad5,1);
	 		CCW_PR1(9,104,0xbbfa,1);
	 		CCW_PR1(11,104,0xd7b4,1);
	 	 	CCW_PR1(13,104,0xccac,1);
	 	 	
	 		CCW_PR1(5,136,0xc8ed,1);	//����������"����汾:1.0"
	 		CCW_PR1(7,136,0xbcfe,1);
	 		CCW_PR1(9,136,0xb0e6,1);
	 		CCW_PR1(11,136,0xb1be,1);
//	  		CCW_PR1(13,136,0xa1c3,1);
	  		CCW_PR1(14,136,0xa3b2,1);
	 		CW_PR3(13,18,':');
//	 		CCW_PR1(17,136,0xa3ae,1);
	 		CCW_PR1(17,136,0xa3b0,1);
	 		CW_PR3(16,18,'.');		
		}

		W_YLINE(0,0,239);				//Y�������߿����ʾ
		W_YLINE(319,0,239);	
		W_DIAMOND(3,LANGUAGE?44:4);		//���ѡ�������ʾ
		for(i=0;i<3;i++)
		{
			W_HDIAMOND(3,LANGUAGE?(76+32*i):(8+4*i));
		}

		if(BUFFER1[0]!=0)				//��֤���ر��˵�ʱѡ������ʾ��һ��
		{
			W_DIAMOND(3,LANGUAGE?(44+BUFFER1[0]*32):(4+BUFFER1[0]*4));
			W_HDIAMOND(3,LANGUAGE?44:4);
		}
		W_Mode(35,7,32,1);				//�ֶ����Զ�ģʽ����ʾ		
	}

		subback=0;
}


/*********************************************/
/*���ܣ����°�����������ѡ������ѡ����
��ڲ�������
���ڲ�������
/*********************************************/
void Maintain_Updn();
void Maintain_Updn()
{
	 if (G_Key==UP)
	{
		if(BUFFER1[0]>0)
		{
			BUFFER1[0]=BUFFER1[0]-1;        	//������������
			G_Key=0;
			W_DIAMOND(3,LANGUAGE?(44+BUFFER1[0]*32):(4+BUFFER1[0]*4));
			W_HDIAMOND(3,LANGUAGE?(76+BUFFER1[0]*32):(8+BUFFER1[0]*4));
		}
	}
	
	if (G_Key==DOWN)
	{
		if(	BUFFER1[0] <3)
		{
			BUFFER1[0]=BUFFER1[0]+1;          	//������������
			G_Key=0;
			W_DIAMOND(3,LANGUAGE?(44+BUFFER1[0]*32):(4+BUFFER1[0]*4));
			W_HDIAMOND(3,LANGUAGE?(12+BUFFER1[0]*32):(BUFFER1[0]*4));		
		}
	}	
}

/***************************************************************/
/*	���ܣ�CLR�������������˳����˵�,���ص�MainMenu����
��ڲ�������
���ڲ�������
/***************************************************************/ 
void Maintain_Return();
void Maintain_Return()
{
	if (G_Key==CLR)
	{
		G_Key=0;		//��������
		BUFFER1[0]=0;   //ʹ��ȫ�ֱ�������            
		FLAG=0;         //����ѭ��            
		STATE=4;		//MainMenu״̬Ϊ4
		State4parameter=0;	//��ڲ���0
	}
}


/***************************************************************/
/*	���ܣ�ENT���������������뱾�˵����ӽ���
��ڲ�������
���ڲ�������
/***************************************************************/ 
void Maintain_Dealing();
void Maintain_Dealing()
{
	if(G_Key==ENT&&STATE==44)

	{	
		G_Key=0;
		FLAG=0;
		if (BUFFER1[0]==0)          //�Լ캯��SelfDiagnosis
		{	
			STATE=440;
		}
		
		if (BUFFER1[0]==1 )        	//�ָ����������Ӳ˵�
		{
		//	ProtectData(); 			//���浯���˵���������
			STATE=442;				
		}

		if (BUFFER1[0]==2)          //״̬����NavtexState
		{
			STATE=441;
		}

		if (BUFFER1[0]==3)          //����汾1.0
		{

		}
	}
}

//*******************************************************************/
/*	���ܣ�ά���˵�������ʵ���Լ죬�ָ��������ã����ջ�״̬������汾�鿴
��ڲ�������
���ڲ�������
/********************************************************************/
void RunMaintain(byte into)
{
  maske=0;
  maskc=0;
	subback=into;
	Maintain_Paintintial();
	while(FLAG)                          
	{
		 Maintain_Updn();		
		 Maintain_Return();		
		 Maintain_Dealing();
	     run_tip();
	}
}