#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "code.h"

/******************************************************/
/*	���ܣ��Զ�ģʽ�˵�Automode����ʾ
��ڲ�������
���ڲ�������
/*******************************************************/
void Automode_Paintintial();
void Automode_Paintintial()
{
	unsigned char i;
	if(subback==10) RecoverData();	//�����Ӳ˵����أ�ֻ����и������ݵĻָ�
	else
	{			
//		CLEAR1();					//��һ���Ͷ����Ĵ洢�ռ�
		W_CLEARXLINE(0,319,230);
		W_CLEARXLINE(0,319,4);
		W_CLEARXLINE(0,319,5);
		
		if(LANGUAGE==0)			//Ӣ�ı�ͷ��AUTOMODE SET
		{
			CTAB[1]='A';	CTAB[2]='U';	CTAB[3]='T';	CTAB[4]='O';	CTAB[5]='M';
			CTAB[6]='O';	CTAB[7]='D';	CTAB[8]='E';	CTAB[10]='S';	CTAB[11]='E';
			CTAB[12]='T';	
			CW_PR(0,1,13);			
		}
		else 					//д�����ı�ͷ����"�Զ�ģʽ"
		{
			CCW_PR1(1,4,0xd7d4,1);
			CCW_PR1(3,4,0xb6af,1);
			CCW_PR1(5,4,0xc4a3,1);
			CCW_PR1(7,4,0xcabd,1);
		}


		/* ������ѡ��,��ʼ����ʮһ�� */
		CTAB[0]='N';	CTAB[1]='A';	CTAB[2]='V';	CTAB[3]='A';
		CTAB[4]='R';	CTAB[5]='E';	CTAB[6]='A';	CTAB[7]=':';	
		CW_PR(2,3,8);

		/* Ƶ��ѡ�񣬳�ʼ��Ϊ518khz */
		CTAB[2]='F';   CTAB[3]='R';	CTAB[4]='E';	CTAB[5]='Q';	CTAB[6]='U';	CTAB[7]='E';
		CTAB[8]='N';   CTAB[9]='C';	CTAB[10]='Y';	CTAB[11]=':';	
		CTAB[12]='5';  CTAB[13]='1';	CTAB[14]='8';	CTAB[15]='K';	CTAB[16]='H';	CTAB[17]='Z';
		CW_PR(0,4,19);  

		for(i=0;i<13;i++)		//��̨A~Z����ʾ
		{
			W_HDIAMOND(2,5+2*i); 
			CW_PR3(3,5+2*i,'A'+i);
			CW_PR3(4,5+2*i,':');	
				  
			W_HDIAMOND(21,5+2*i); 
			CW_PR3(22,5+2*i,'N'+i);
			CW_PR3(23,5+2*i,':');		
		}

		W_YLINE(0,0,239);		//Y��������߿���ʾ
		W_YLINE(319,0,239);	

		W_DIAMOND(1,3);			//���ѡ�������ʾ
		W_HDIAMOND(1,4);

		if(BUFFER2[2]==1)		//��ʱѡ����Ϊ490khz
		{
			CTAB[0]='4';   CTAB[1]='8';	CTAB[2]='6';	CTAB[3]='K';	CTAB[4]='H';
			CTAB[5]='Z';	
			CW_PR(12,4,6); 
		}
		
		if(BUFFER2[2]==2)		//��ʱѡ������4209.5khz
		{
		
			CTAB[0]='4';   CTAB[1]='2';		CTAB[2]='0';	CTAB[3]='9';	CTAB[4]='.';
			CTAB[5]='5';	CTAB[6]='K';	CTAB[7]='H';	CTAB[8]='Z';
			CW_PR(12,4,9); 
		}
		
		BUFFER2[1]=11; 			//��ʼ��������11��
		Station_display(10);
	}
	
	for(i=0;i<5;i++)			//��ԭ�������Ӳ˵����ǵ�����ʾ��
	{
		W_HDIAMOND(21,13+2*i);		
	}
	
	DISASCII(10,3,BUFFER2[1]);	//��������ʾ�����ú���DISASCII
	
	for(i=0;i<26;i++)			//��ʾ��̨���ý��������0�򹴣�1����ʾ
	{
		word temp,temp1;
		temp1=Power(BUFFER2[1]-1);
//		temp1=(word)(pow(2,BUFFER2[1]-1));
		temp=Autotemp[BUFFER2[2]][i]&temp1;
		if(temp)
		{				
			if(i<13)	W_CANCALCHOOSED(19,5+2*i);
			else W_CANCALCHOOSED(38,5+2*(i-13));			
		}
		
		else
		{
			if(i<13)	W_CHOOSED(19,5+2*i);		
			else W_CHOOSED(38,5+2*(i-13));			
		}

 	}
		
	if(BUFFER2[0]>1&&BUFFER2[0]<15) //��֤����ʱ����ѡ���򲻱�
	{
		W_DIAMOND(2,(BUFFER2[0]-2)*2+5);
		W_HDIAMOND(1,3);
	}
	
	if(BUFFER2[0]==1)
	{
		W_DIAMOND(1,4);
		W_HDIAMOND(1,3);		
	}			
	if(BUFFER2[0]>14&&BUFFER2[0]<28)
	{
		W_DIAMOND(21,(BUFFER2[0]-15)*2+5);
		W_HDIAMOND(1,3);
	}
	subback=0;

 }
 
//********************************************/
/*	���ܣ����°�����������ѡ������ѡ����
��ڲ�������
���ڲ�������
/*********************************************/ 
void Automode_Updn();
void Automode_Updn()
{
	if (G_Key==UP)
	{
		G_Key=0;							//��������
		BUFFER2[0]=(BUFFER2[0]+27)%28;      //�����������ƶ�    
		if(BUFFER2[0]==0)					//�ƶ����֮���ѡ����Ӻ�
		{
			W_DIAMOND(1,3);	
			W_HDIAMOND(1,4);	
		}
		
		if(BUFFER2[0]==1)
		{
			W_DIAMOND(1,4);	
			W_HDIAMOND(2,5);	
		}

		if(BUFFER2[0]==14)
		{
			W_DIAMOND(2,29);	
			W_HDIAMOND(21,5);	
		}
		if(BUFFER2[0]==27)
		{
			W_DIAMOND(21,29);	
			W_HDIAMOND(1,3);
		}
		
		if(BUFFER2[0]>1&&BUFFER2[0]<14)
		{
			W_DIAMOND(2,(BUFFER2[0]-2)*2+5);
			W_HDIAMOND(2,(BUFFER2[0]-2)*2+7);
		}
		
		if(BUFFER2[0]>14&&BUFFER2[0]<27)
		{
			W_DIAMOND(21,(BUFFER2[0]-15)*2+5);
			W_HDIAMOND(21,(BUFFER2[0]-15)*2+7);
		}  
		
	}

	if (G_Key==DOWN)
	{
		G_Key=0;							//��������
		BUFFER2[0]=(BUFFER2[0]+1)%28;       //�����������ƶ�  
		if(BUFFER2[0]==0)					//�ƶ����֮���ѡ����Ӻ�
		{
			W_DIAMOND(1,3);	
			W_HDIAMOND(21,29);	
		}
		
		if(BUFFER2[0]==1)
		{
			W_DIAMOND(1,4);	
			W_HDIAMOND(1,3);	
		}

		if(BUFFER2[0]==15)
		{
			W_HDIAMOND(2,29);	
			W_DIAMOND(21,5);	
		}
		if(BUFFER2[0]==2)
		{
			W_DIAMOND(2,5);	
			W_HDIAMOND(1,4);
		}
		
		if(BUFFER2[0]>2&&BUFFER2[0]<15)
		{
			W_DIAMOND(2,(BUFFER2[0]-2)*2+5);
			W_HDIAMOND(2,(BUFFER2[0]-2)*2+3);
		}
		
		if(BUFFER2[0]>15&&BUFFER2[0]<28)
		{
			W_DIAMOND(21,(BUFFER2[0]-15)*2+5);
			W_HDIAMOND(21,(BUFFER2[0]-15)*2+3);
		} 		     	

	}

}

//****************************************************/
/*	���ܣ����Ұ��������������к��о�����ѡ��͹���Ƶ��ѡ��
��ڲ�������
���ڲ�������
/*****************************************************/
void Automode_Leftright();
void Automode_Leftright()
{
	char i,j;
	if (G_Key==RIGHT||G_Key==LEFT)
	{
		if (BUFFER2[0]==0)                         	//���о�����ѡ��
		{   
		    if (G_Key==RIGHT)
			{
		        BUFFER2[1]=BUFFER2[1]%16+1;         //�����ƶ���BUFFER2[1]������ 
			}
			if (G_Key==LEFT)
			{
		       	BUFFER2[1]=(BUFFER2[1]+14)%16+1;             
			}
			
			DISASCII(10,3,BUFFER2[1]);				//��������ʾ�����ú���DISASCII	
	
			Station_display(BUFFER2[1]-1);			
		}  
		
		if (BUFFER2[0]==1)                         	//Ƶ��ѡ��
		{   
	    	if (G_Key==RIGHT) BUFFER2[2]=(BUFFER2[2]+1)%3;     //�����ƶ���BUFFER2[2]��Ƶ�� 
	       	else BUFFER2[2]=(BUFFER2[2]+2)%3;             
			
			
			if(BUFFER2[2]==0)						//��ʾ��ѡ����Ƶ��
			{			
				CTAB[0]='5';   CTAB[1]='1'; 	CTAB[2]='8';	CTAB[3]='K';	CTAB[4]='H';
				CTAB[5]='Z';   CTAB[6]=0x20;	CTAB[7]=0x20;	CTAB[8]=0x20;
				CW_PR(12,4,9); 	
			}
			
			else if(BUFFER2[2]==1)
			{			
				CTAB[0]='4';   CTAB[1]='8';	CTAB[2]='6';	CTAB[3]='K';	CTAB[4]='H';
				CTAB[5]='Z';	CTAB[6]=0x20;	CTAB[7]=0x20;	CTAB[8]=0x20;
				CW_PR(12,4,9);
			}
			
			else if(BUFFER2[2]==2)
			{			
				CTAB[0]='4';   CTAB[1]='2';		CTAB[2]='0';	CTAB[3]='9';	CTAB[4]='.';
				CTAB[5]='5';	CTAB[6]='K';	CTAB[7]='H';	CTAB[8]='Z';
				CW_PR(12,4,9); 
			}
		}

		if(BUFFER2[0]==0||BUFFER2[0]==1)
		{
			for(i=0;i<26;i++)
			{
				word temp,temp1;
				temp1=Power(BUFFER2[1]-1);
//				temp1=(word)(pow(2,BUFFER2[1]-1));
				temp=Autotemp[BUFFER2[2]][i]&temp1;
				if(temp!=0)
				{
						
					if(i<13)	W_CANCALCHOOSED(19,5+2*i);
					else W_CANCALCHOOSED(38,5+2*(i-13));
							
						
				}
				
				if(temp==0)
				{
			    
					if(i<13)	W_CHOOSED(19,5+2*i);		
					else W_CHOOSED(38,5+2*(i-13));
				}

		 	}			
		}					
		G_Key=0;	//��������
	}
}

/*************************************************/
/*	���ܣ�CLR���������������ص��ϼ��˵�Rxstation
��ڲ�������
���ڲ�������
/*************************************************/ 
void Automode_Return();
void Automode_Return()
{
	if (G_Key==CLR)  
	{
		byte i,j;
		G_Key=0;			//��������
		BUFFER2[1]=0;		//���õ�3��ȫ�ֱ�������
		BUFFER2[2]=0;
		BUFFER2[0]=0;			
		for(j=0;j<3;j++)	//Autotemp�ָ�Auto��ֵ
		{
			for(i=0;i<26;i++)
				{
					Autotemp[j][i]=Auto[j][i];
				}
		}
		LANHELP=1;			//����LANHELP�ָ�Ϊ1
		FLAG=0;				//����ѭ��
		STATE=40;			//Rxstation״̬Ϊ40
	}
}

//**********************************************************/
/*	���ܣ�ENT��������������ʱ����̨��ѡ��������Autotemp��
��ڲ�������
���ڲ�������
/***********************************************************/  
void Automode_Dealing();
void Automode_Dealing()
{
	byte i;                          
	word temp,temp1,temp2;    
	if (G_Key==ENT)
	{     
		G_Key=0;
		i=BUFFER2[0]-2;				//��ʾBUFFER2[0]��ֵ                     	 	
		if (BUFFER2[0]>=2)          //����entΪѡ������л�
		{
			temp2=0x0001;
			temp1=temp2<<(BUFFER2[1]-1);
/*			temp1=(word)(pow(2,BUFFER2[1]-1));
			temp2=pow(2,BUFFER2[1]-1);
			temp3=pow(2,15);*/
			temp=Autotemp[BUFFER2[2]][i]&temp1;
			if(temp==0)	//0��ʾ֮ǰ����
			{
				Autotemp[BUFFER2[2]][i]=Autotemp[BUFFER2[2]][i]+temp1;
					
					if(i<13)	W_CANCALCHOOSED(19,5+2*i);
					else W_CANCALCHOOSED(38,5+2*(i-13));
			}			
			if(temp!=0)	//1��ʾ����
			{
				Autotemp[BUFFER2[2]][i]=Autotemp[BUFFER2[2]][i]-temp1;
			
				if(i<13)	W_CHOOSED(19,5+2*i);		
				else W_CHOOSED(38,5+2*(i-13));
			}
		}
	}
}
 
//****************************************************/
/*	���ܣ�STAR�����������������Ӳ˵�AutomodeSubmenu
��ڲ�������
���ڲ�������
/*****************************************************/ 
 void Automode_Submenu();
 void Automode_Submenu()
 {
     if (G_Key==STAR&&STATE==400)	
     {
		G_Key=0;				//��������
//		ProtectData(); 			//���浯���˵���������
		LANHELP=1;    			//�ָ�LANHELPֵΪ1
		FLAG=0;					//����ѭ��
		STATE=4000;				//AutomodeSubmenu״̬Ϊ4000
		State4000parameter=0;	//��ڲ���Ϊ0����ʾ��Automode�˵�����

     }
 }
 
 

//**************************************************/
/*	���ܣ��Զ�ģʽ�£����Ե�������ÿ��������ÿ����̨
          ������񣬽�������ڰ�̨��򹴣���������
          BUFFER2[0] ��¼ѡ����
          BUFFER2[1] ��¼���ں��о�����ȡֵ��Χ(1~16)
          BUFFER2[2] ��¼��������Ƶ��(0~2)
          subback    ��¼�Ӻβ˵�����
��ڲ�������
���ڲ�������
/***************************************************/ 
void RunAutomode(unsigned char into)
{
    maske=0;
    maskc=0;
	subback=into;  
	LANHELP=0;
	Automode_Paintintial();

	while(FLAG)                          
	{	
		Automode_Updn();
		Automode_Leftright();		
		Automode_Return();		
		Automode_Dealing();
		Automode_Submenu();
		run_tip();        
	}
	
}