#include <stdio.h>
#include <stdlib.h>
#include "define.h"	
#include  "run.h"
#include "lcddrive.h"
#include "code.h"
#if 0
volatile byte MessagetypeEn[26][13]=
{
	/*****************A~Z��Ӧ��26z����Ϣ���********************/
	
		{'N','A','V',' ','W','A','R','N','I','N','G','S',' '},
		{'M','E','T',' ','W','A','R','N','I','N','G','S',' '},		
		{'I','C','E',' ','R','E','P','O','R','T',' ',' ',' '},
		{'S','E','A','R','C','H','&','R','E','S','C','U','E'},
		{'M','E','T',' ','F','O','R','E','C','A','S','T',' '},		
		{'P','I','L','O','T',' ','S','E','R','V','E','C','E'},
		{'A','I','S',' ',' ',' ',' ',' ',' ',' ',' ',' ',' '},
		{'L','O','R','A','N',' ',' ',' ',' ',' ',' ',' ',' '},		
		{'S','P','A','R','E',' ',' ',' ',' ',' ',' ',' ',' '},
		{'S','A','T','N','A','V',' ',' ',' ',' ',' ',' ',' '},
		{'O','T','H','E','R',' ','N','A','V','A','I','D',' '},
		{'N','A','V',' ','W','A','R','N','I','N','G','S',' '},		
		{'S','P','A','R','E',' ',' ',' ',' ',' ',' ',' ',' '},	//A~M,ȫΪ��
		
		{'S','P','A','R','E',' ',' ',' ',' ',' ',' ',' ',' '},
		{'S','P','A','R','E',' ',' ',' ',' ',' ',' ',' ',' '},	
		{'S','P','A','R','E',' ',' ',' ',' ',' ',' ',' ',' '},
		{'S','P','A','R','E',' ',' ',' ',' ',' ',' ',' ',' '},
		{'S','P','A','R','E',' ',' ',' ',' ',' ',' ',' ',' '},		
		{'S','P','A','R','E',' ',' ',' ',' ',' ',' ',' ',' '},
		{'S','P','A','R','E',' ',' ',' ',' ',' ',' ',' ',' '},
		{'S','P','A','R','E',' ',' ',' ',' ',' ',' ',' ',' '},
		{'S','P','E','C','I','A','L',' ',' ',' ',' ',' ',' '},	
		{'S','P','E','C','I','A','L',' ',' ',' ',' ',' ',' '},
		{'S','P','E','C','I','A','L',' ',' ',' ',' ',' ',' '},
		{'S','P','E','C','I','A','L',' ',' ',' ',' ',' ',' '},		
		{'N','O',' ','M','E','S','S','A','G','E','S',' ',' '}	//N~Z��ȫΪ��
	
};	//Ӣ��

volatile word MessagetypeCn[26][4]=
{
	{0xBABD,0xD0D0,0xBEAF,0xB8E6},	//A ���о���
	{0xC6F8,0xCFF3,0xBEAF,0xB8E6},	//B ���󾯸�
	{0xB1F9,0xC7E9,0xBEAF,0xB8E6},	//C ���徯��
	{0xCBD1,0xBEC8,0xBEAF,0xB8E6},	//D �ѾȾ���
	{0xC6F8,0xCFF3,0xD4A4,0xB8E6},	//E ����Ԥ�� 
	{0xD2FD,0xBABD,0xD4A4,0xB8E6},	//F ����Ԥ��
	{0xCCA8,0xBFA8,0xB5BC,0xB1A8},	//G ̨������
	{0xC2DE,0xC0BC,0xB5BC,0xB1A8},	//H ��������
	{0xCEB4,0xB1BB,0xC6F4,0xD3C3},	//I δ������
	{0xCEC0,0xD0C7,0xB5BC,0xB1A8},	//J ���ǵ���	
	{0xC6E4,0xCBF8,0xB5BC,0xB1A8},	//K ��������
	{0xBABD,0xD0D0,0xBEAF,0xB8E6},	//L ���о���
	{0xCEB4,0xB1BB,0xC6F4,0xD3C3},	//M δ������
	{0xCEB4,0xB1BB,0xC6F4,0xD3C3},	//N δ������	
	{0xCEB4,0xB1BB,0xC6F4,0xD3C3},	//O δ������
	{0xCEB4,0xB1BB,0xC6F4,0xD3C3},	//P δ������
	{0xCEB4,0xB1BB,0xC6F4,0xD3C3},	//Q δ������	
	{0xCEB4,0xB1BB,0xC6F4,0xD3C3},	//R δ������	
	{0xCEB4,0xB1BB,0xC6F4,0xD3C3},	//S δ������
	{0xCEB4,0xB1BB,0xC6F4,0xD3C3},	//T δ������
	{0xCEB4,0xB1BB,0xC6F4,0xD3C3},	//U δ������
	{0xCCD8,0xB1F0,0xD2B5,0xCEF1},	//V �ر�ҵ��	
	{0xCCD8,0xB1F0,0xD2B5,0xCEF1},	//W �ر�ҵ��
	{0xCCD8,0xB1F0,0xD2B5,0xCEF1},	//X �ر�ҵ��
	{0xCCD8,0xB1F0,0xD2B5,0xCEF1},	//Y �ر�ҵ��
	{0xC3BB,0xD3D0,0xB7D6,0xC5E4}
};	//����
#endif
//*****************************************************/
/*	���ܣ���Ϣ�������Messagetypemenu����ʾ
��ڲ�������
���ڲ�������
/*******************************************************/
void Messagetypemenu_Paintintial();
void Messagetypemenu_Paintintial()
{
	byte i,j;
	if(subback==10) RecoverData();	//�����Ӳ˵����أ�ֻ����и������ݵĻָ�
	else
	{

		CLEARXLINE(0,39,4);
		CLEARXLINE(0,39,5);
		
		if(LANGUAGE==0)	
		{
			/* д��Ӣ�ı�ͷ����MSGTYPE CHOOSE */
			CTAB[2]='M';	CTAB[3]='S';	CTAB[4]='G';	CTAB[5]='T';	CTAB[6]='Y';	CTAB[7]='P';
			CTAB[8]='E';	CTAB[10]='C';	CTAB[11]='H';	CTAB[12]='O';  CTAB[13]='O';  CTAB[14]='S';
			CTAB[15]='E';
			CW_PR(0,1,16);	
		}
		
		else
		{
			CCW_PR1(1,4,0xd0c5,1);	//д�����ı�ͷ����"��Ϣ�������"
			CCW_PR1(3,4,0xcfa2,1);
			CCW_PR1(5,4,0xc0e0,1);
			CCW_PR1(7,4,0xb1f0,1);
		 	CCW_PR1(9,4,0xc9e8,1);
			CCW_PR1(11,4,0xd6c3,1);
		}

		/* Ƶ��ѡ��FREQUENCY:*/
		CTAB[3]='F';   CTAB[4]='R';	CTAB[5]='E';	CTAB[6]='Q';	CTAB[7]='U';	CTAB[8]='E';
		CTAB[9]='N';	CTAB[10]='C';	CTAB[11]='Y';	CTAB[12]=':';	CTAB[13]='5';	CTAB[14]='1';
		CTAB[15]='8';	CTAB[16]='K';	CTAB[17]='H';	CTAB[18]='Z';
		CW_PR(0,3,19);  



		for(i=0;i<13;i++)		//A~Z����ʾ
		{

			CTAB[0]='A'+i; CTAB[1]=':';
			for(j=0;j<13;j++)
			{
				CTAB[2+j]=MessagetypeEn[i][j];
			}
			
			CTAB[20]='N'+i; CTAB[21]=':';
			for(j=0;j<11;j++)
			{
				CTAB[22+j]=MessagetypeEn[i+13][j];
			}
			CW_PR(5,4+i*2,33); 					
		
		}




		CLEARXLINE(0,39,230);	//��ͼ����ʾ
		W_YLINE(0,0,239);
		W_YLINE(319,0,239);


		W_DIAMOND(1,3);    		//���ѡ�������ʾ
		for(i=0;i<13;i++)
		{
			W_HDIAMOND(3,4+2*i);   	
			W_HDIAMOND(23,4+2*i);   	
		}
		
		if(BUFFER1[1]==1)		//Ƶ����ʾ
		{
			CTAB[0]='4';   CTAB[1]='8';	CTAB[2]='6';	CTAB[3]='K';	CTAB[4]='H';
			CTAB[5]='Z';
			CW_PR(13,3,6); 
		}
		
		if(BUFFER1[1]==2)
		{
			CTAB[0]='4';   CTAB[1]='2';	CTAB[2]='0';	CTAB[3]='9';	CTAB[4]='.';
			CTAB[5]='5';	CTAB[6]='K';	CTAB[7]='H';	CTAB[8]='Z';
			CW_PR(13,3,9); 
		}
		
		W_Mode(35,4,32,1);	//�ֶ����Զ�ģʽ����ʾ
	}

	W_HDIAMOND(23,14);	//�Ӳ˵�����ʱ�����ǵ�ѡ����������ʾ
	W_HDIAMOND(23,16);
	W_HDIAMOND(23,18);
	W_HDIAMOND(23,20);

	if(BUFFER1[0]!=0)
	{
		if(BUFFER1[0]>13) W_DIAMOND(23,(BUFFER1[0]-13)*2+2);
		else  	W_DIAMOND(3,2+2*BUFFER1[0]);
		W_HDIAMOND(1,3);
		
	}
	subback=0;

	for(i=0;i<13;i++)	//��ʾ��Ϣ������ý��������0�򹴣�1����ʾ
	{
		if(MSGTYPETEMP[BUFFER1[1]][i]==0) W_CHOOSED(20,i*2+4);
		else  W_CANCALCHOOSED(20,i*2+4);
	}

	for(i=13;i<26;i++)
	{
		if(MSGTYPETEMP[BUFFER1[1]][i]==0) W_CHOOSED(38,(i-13)*2+4);
		else  W_CANCALCHOOSED(38,(i-13)*2+4);
	}
}

//********************************************/
/*	���ܣ����°�����������ѡ������ѡ����
��ڲ�������
���ڲ�������
/*********************************************/ 
void Messagetypemenu_Updn();
void Messagetypemenu_Updn()
{
	if (G_Key==UP)
	{

		G_Key=0;								//��������
		BUFFER1[0]=(BUFFER1[0]+26)%27;      	//�����������ƶ�        
		if(BUFFER1[0]>13) 						//ѡ������ʾ
		{
			W_DIAMOND(23,(BUFFER1[0]-13)*2+2);	
			W_HDIAMOND(23,(BUFFER1[0]-13)*2+4);		
		}
		
		if(BUFFER1[0]>0&&BUFFER1[0]<13) 
		{
			W_DIAMOND(3,BUFFER1[0]*2+2);	
			W_HDIAMOND(3,BUFFER1[0]*2+4);		
		}
		
		if(BUFFER1[0]==0)
		{
			W_DIAMOND(1,3);
			W_HDIAMOND(3,4);
		}
		
		if(BUFFER1[0]==13)
		{
			W_DIAMOND(3,28);
			W_HDIAMOND(23,4);
		}
		
		if(BUFFER1[0]==26)
		{
			W_DIAMOND(23,28);
			W_HDIAMOND(1,3);
		}

	}

	if (G_Key==DOWN&&BUFFER1[0]<27)
	{
		G_Key=0;								//��������
		BUFFER1[0]=(BUFFER1[0]+1)%27;           //����
		if(BUFFER1[0]>14&&BUFFER1[0]<27) 		//ѡ������ʾ
		{
			W_DIAMOND(23,(BUFFER1[0]-13)*2+2);	
			W_HDIAMOND(23,(BUFFER1[0]-13)*2);		
		}
		
		if(BUFFER1[0]>1&&BUFFER1[0]<14) 
		{
			W_DIAMOND(3,BUFFER1[0]*2+2);	
			W_HDIAMOND(3,BUFFER1[0]*2);		
		}
		
		if(BUFFER1[0]==1)
		{
			W_HDIAMOND(1,3);
			W_DIAMOND(3,4);
		}
		
		if(BUFFER1[0]==14)
		{
			W_HDIAMOND(3,28);
			W_DIAMOND(23,4);
		}
		
		if(BUFFER1[0]==0)
		{
			W_HDIAMOND(23,28);
			W_DIAMOND(1,3);
		}		

	}

}

//****************************************************/
/*	���ܣ����Ұ��������������й���Ƶ��ѡ��
��ڲ�������
���ڲ�������
/*****************************************************/
void Messagetypemenu_Leftright();
void Messagetypemenu_Leftright()
{
	if (G_Key==RIGHT||G_Key==LEFT)
	{
		byte i;	
		if (G_Key==RIGHT&&BUFFER1[0]==0)	//�����ƶ���BUFFER[1]��Ƶ�� 
		{
			BUFFER1[1]=(BUFFER1[1]+1)%3;              
		}

		if (G_Key==LEFT&&BUFFER1[0]==0)
		{
			BUFFER1[1]=(BUFFER1[1]+2)%3;             
		}

		G_Key=0;							//��������

		if(BUFFER1[1]==0)					//��ʾ��ѡ����Ƶ��
		{

			CTAB[0]='5';   CTAB[1]='1';	CTAB[2]='8';	CTAB[3]='K';	CTAB[4]='H';
			CTAB[5]='Z';	CTAB[6]=' ';	CTAB[7]=' ';	CTAB[8]=' ';
			CW_PR(13,3,9);
		}

		if(BUFFER1[1]==1)
		{

			CTAB[0]='4';   CTAB[1]='8';	CTAB[2]='6';	CTAB[3]='K';	CTAB[4]='H';
			CTAB[5]='Z';	CTAB[6]=' ';	CTAB[7]=' ';	CTAB[8]=' ';
			CW_PR(13,3,9); 
		}

		if(BUFFER1[1]==2)
		{

			CTAB[0]='4';   CTAB[1]='2';	CTAB[2]='0';	CTAB[3]='9';	CTAB[4]='.';
			CTAB[5]='5';	CTAB[6]='K';	CTAB[7]='H';	CTAB[8]=' ';
			CW_PR(13,3,9); 
		}

		for(i=0;i<13;i++)
		{
			if(MSGTYPETEMP[BUFFER1[1]][i]==0) W_CHOOSED(20,i*2+4);
			else  W_CANCALCHOOSED(20,i*2+4);
		}

		for(i=13;i<26;i++)
		{
			if(MSGTYPETEMP[BUFFER1[1]][i]==0) W_CHOOSED(38,(i-13)*2+4);
			else  W_CANCALCHOOSED(38,(i-13)*2+4);
		}			

	}
}

//************************************************/
/*	���ܣ�CLR���������������ص��ϼ��˵�MainMenu
��ڲ�������
���ڲ�������
/*************************************************/  
void Messagetypemenu_Return();
void Messagetypemenu_Return()
{
	if (G_Key==CLR)         //���ص�ԭ������  
	{
		byte i,j;
		G_Key=0;			//��������
		BUFFER1[1]=0;		//���õ�2��ȫ�ֱ�������
		BUFFER1[0]=0;
		LANHELP=1;			//����LANHELP�ָ�Ϊ1
		for(j=0;j<3;j++)	//MSGTYPETEMP�ָ�MSGTYPE��ֵ
		{
			for(i=0;i<26;i++)
			{
				MSGTYPETEMP[j][i]=MSGTYPE[j][i];
			}
		}
		FLAG=0;				//����ѭ��
		STATE=4;			//MainMenu״̬Ϊ40
		State4parameter=0;	//��ڲ���Ϊ0
	}
}
 
//**********************************************************/
/*	���ܣ�ENT��������������ʱ������Ϣ����ѡ����
          ����MSGTYPETEMP��
��ڲ�������
���ڲ�������
/***********************************************************/  
void Messagetypemenu_Dealing();
void Messagetypemenu_Dealing()
{   
	if (G_Key==ENT&&BUFFER1[0]!=0&&BUFFER1[0]!=1&&BUFFER1[0]!=2&&BUFFER1[0]!=4&&BUFFER1[0]!=12)
	{
		G_Key=0;
		if(BUFFER1[0]<14)
		{
			MSGTYPETEMP[BUFFER1[1]][BUFFER1[0]-1]=(MSGTYPETEMP[BUFFER1[1]][BUFFER1[0]-1]+1)%2;           //����һ��ENT�ı�BUFFER[i+1]��ֵ���Ƿ����	
			if(MSGTYPETEMP[BUFFER1[1]][BUFFER1[0]-1]==0) W_CHOOSED(20,(BUFFER1[0]-1)*2+4);
			else  W_CANCALCHOOSED(20,(BUFFER1[0]-1)*2+4);
		}

		if(BUFFER1[0]>13)
		{
			MSGTYPETEMP[BUFFER1[1]][BUFFER1[0]-1]=(MSGTYPETEMP[BUFFER1[1]][BUFFER1[0]-1]+1)%2;           //����һ��ENT�ı�BUFFER[i+1]��ֵ���Ƿ����	
			if(MSGTYPETEMP[BUFFER1[1]][BUFFER1[0]-1]==0) W_CHOOSED(38,(BUFFER1[0]-14)*2+4);
			else  W_CANCALCHOOSED(38,(BUFFER1[0]-14)*2+4);
		}	
	}
}
 
 
//****************************************************/
/*	���ܣ�STAR�����������������Ӳ˵�AutomodeSubmenu
��ڲ�������
���ڲ�������
/*****************************************************/  
void Messagetypemenu_Submenu();
void Messagetypemenu_Submenu()
{
	if (G_Key==STAR&&STATE==41)	
	{
		G_Key=0;				//��������
		ProtectData(); 			//���浯���˵���������
		LANHELP=1;    			//�ָ�LANHELPֵΪ1
		FLAG=0;					//����ѭ��
		STATE=4000;				//AutomodeSubmenu״̬Ϊ4000
		State4000parameter=2;	//��ڲ���Ϊ2����ʾ��MessageType�˵�����
	}
}

//**************************************************/
/*	���ܣ��Զ�ģʽ�£����Ե�������ÿ��������ÿ����̨
          ������񣬽�������ڰ�̨��򹴣���������
          BUFFER1[0] ��¼ѡ����
          BUFFER1[1] ��¼��������Ƶ��(0~2)
          subback    ��¼�Ӻβ˵�����
��ڲ�����into char�� ��¼�Ӻβ˵�����
���ڲ�������
/***************************************************/ 
void RunMessagetypemenu(unsigned char into)
{
    maske=0;
    maskc=0;
	subback=into;
	LANHELP=0;
	Messagetypemenu_Paintintial();
	while(FLAG)                                     
	{
		Messagetypemenu_Updn();
		Messagetypemenu_Leftright();		
		Messagetypemenu_Return();		
		Messagetypemenu_Dealing();
		Messagetypemenu_Submenu();
		run_tip();
	}
}