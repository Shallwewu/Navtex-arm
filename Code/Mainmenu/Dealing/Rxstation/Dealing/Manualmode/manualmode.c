#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "code.h"

//*****************************************************/
/*	���ܣ��Զ�ģʽ�˵�Automode����ʾ
��ڲ�������
���ڲ�������
/******************************************************/
void Manualmode_Paintintial();
void Manualmode_Paintintial()
{
	unsigned char i;
	
	if(subback==10) RecoverData();
	else
	{
		
//		CLEAR1();		//��һ���Ͷ����Ĵ洢�ռ�
	
		W_CLEARXLINE(0,319,230);
		W_CLEARXLINE(0,319,4);
		W_CLEARXLINE(0,319,5);
		
		if(LANGUAGE==0)	//Ӣ�Ĳ˵�
		{
			/* ��ͷ MANUALMODE */
			CTAB[1]='M';	CTAB[2]='A';	CTAB[3]='N';	CTAB[4]='U';	CTAB[5]='A';
			CTAB[6]='L';	CTAB[8]='M';	CTAB[9]='O';	CTAB[10]='D';	CTAB[11]='E';
			CW_PR(0,1,12);	
		}
		else			//���Ĳ˵�
		{
			CCW_PR1(1,4,0xcad6,1);	//д�����ı�ͷ����"�ֶ�ģʽ"
			CCW_PR1(3,4,0xb6af,1);
			CCW_PR1(5,4,0xc4a3,1);
			CCW_PR1(7,4,0xcabd,1);
		}
		/* д��ڶ�������FREQUENCY: */
		CTAB[3]='F';   CTAB[4]='R';	CTAB[5]='E';	CTAB[6]='Q';	CTAB[7]='U';	CTAB[8]='E';
		CTAB[9]='N';	CTAB[10]='C';	CTAB[11]='Y';	CTAB[12]=':';	CTAB[13]='5';	CTAB[14]='1';
		CTAB[15]='8';	CTAB[16]='K';	CTAB[17]='H';	CTAB[18]='Z';	
		CW_PR(0,3,19);  
		W_CLEARXLINE(0,319,230);

		CTAB[3]='C';    CTAB[4]='U';	CTAB[5]='R';	CTAB[6]='R';	CTAB[7]='E';	CTAB[8]='N';
		CTAB[9]='T';	CTAB[10]=' ';	CTAB[11]='A';	CTAB[12]='R';	CTAB[13]='E';	CTAB[14]='A';
		CTAB[15]=':';		
		CW_PR(0,4,16);
		BUFFER2[2]=manual_area_temp;
		DISASCII(17,4,BUFFER2[2]); 
		
		for(i=0;i<13;i++)	//��̨A~Z����ʾ
		{
			W_HDIAMOND(4,5+2*i); 
			CW_PR3(5,5+2*i,'A'+i);
			CW_PR3(6,5+2*i,':');	
				  
			W_HDIAMOND(23,5+2*i); 
			CW_PR3(24,5+2*i,'N'+i);
			CW_PR3(25,5+2*i,':');		
		}

		
		for(i=0;i<26;i++)	//��ʼ����ʾ����518khz�°�̨��ѡ�����
		{
			if(i<13&&Manualtemp[BUFFER2[1]][i]==0)
			{
				W_CHOOSED(7,5+2*i);
			}
			
			if(i>12&&i<26&&Manualtemp[BUFFER2[1]][i]==0)
			{
				W_CHOOSED(26,5+2*(i-13));
			}
			
		}


		W_YLINE(0,0,239);
		W_YLINE(319,0,239);	

//		W_DIAMOND(2,3);		//���ѡ�������ʾ
		W_DIAMOND(2,3);			//���ѡ�������ʾ
		W_HDIAMOND(2,4);
		
		if(BUFFER2[1]==1)	//��֤��ʱ����Ƶ��Ҳ����
		{
			CTAB[0]='4';   CTAB[1]='8';		CTAB[2]='6';	CTAB[3]='K';	CTAB[4]='H';
			CTAB[5]='Z';	CTAB[6]=0x20;	CTAB[7]=0x20;
			CW_PR(13,3,8); 
		}
		
		if(BUFFER2[1]==2)
		{
			CTAB[0]='4';   CTAB[1]='2';	CTAB[2]='0';	CTAB[3]='9';	CTAB[4]='.';
			CTAB[5]='5';	CTAB[6]='K';	CTAB[7]='H';	CTAB[8]='Z';
			CW_PR(13,3,9); 
		}	
	}
	

	W_HDIAMOND(23,15);				//��ԭ�������Ӳ˵����ǵ�����ʾ��
	W_HDIAMOND(23,17);
	W_HDIAMOND(23,19);
	W_HDIAMOND(23,21);
	
	if(BUFFER2[0]==1)
	{
		W_DIAMOND(2,4);
		W_HDIAMOND(2,3);		
	}	
	if(BUFFER2[0]>1&&BUFFER2[0]<15) //��֤����ʱ����ѡ���򲻱�
	{
		W_DIAMOND(4,5+2*(BUFFER2[0]-2));
		W_HDIAMOND(2,3);
	}
	
				
	if(BUFFER2[0]>14&&BUFFER2[0]<27)
	{
		W_DIAMOND(23,5+2*(BUFFER2[0]-15));
		W_HDIAMOND(2,3);
	}
	subback=0;
}

//********************************************/
/*	���ܣ����°�����������ѡ������ѡ����
��ڲ�������
���ڲ�������
/*********************************************/ 
void Manualmode_Updn();
void Manualmode_Updn()                 //��auto��ȣ�BUFFER2[0]������ǰ��һ��BUFFER2[k] k>0��Ӧ����       
{
	if (G_Key==UP)
	{
		G_Key=0;							//��������
		BUFFER2[0]=(BUFFER2[0]+27)%28;      //�����������ƶ�    
		if(BUFFER2[0]==0)					//�ƶ����֮���ѡ����Ӻ�
		{
			W_DIAMOND(2,3);	
			W_HDIAMOND(2,4);	
		}
		
		if(BUFFER2[0]==1)
		{
			W_DIAMOND(2,4);	
			W_HDIAMOND(4,5);	
		}

		if(BUFFER2[0]==14)
		{
			W_DIAMOND(4,29);	
			W_HDIAMOND(23,5);	
		}
		if(BUFFER2[0]==27)
		{
			W_DIAMOND(23,29);	
			W_HDIAMOND(2,3);
		}
		
		if(BUFFER2[0]>1&&BUFFER2[0]<14)
		{
			W_DIAMOND(4,(BUFFER2[0]-2)*2+5);
			W_HDIAMOND(4,(BUFFER2[0]-2)*2+7);
		}
		
		if(BUFFER2[0]>14&&BUFFER2[0]<27)
		{
			W_DIAMOND(23,(BUFFER2[0]-15)*2+5);
			W_HDIAMOND(23,(BUFFER2[0]-15)*2+7);
		}
	}
	
	if (G_Key==DOWN&&BUFFER2[0]<27)
	{
		G_Key=0;							//��������
		BUFFER2[0]=(BUFFER2[0]+1)%28;       //�����������ƶ�  
		if(BUFFER2[0]==0)					//�ƶ����֮���ѡ����Ӻ�
		{
			W_DIAMOND(2,3);	
			W_HDIAMOND(23,29);	
		}
		
		if(BUFFER2[0]==1)
		{
			W_DIAMOND(2,4);	
			W_HDIAMOND(2,3);	
		}

		if(BUFFER2[0]==15)
		{
			W_HDIAMOND(4,29);	
			W_DIAMOND(23,5);	
		}
		if(BUFFER2[0]==2)
		{
			W_DIAMOND(4,5);	
			W_HDIAMOND(2,4);
		}
		
		if(BUFFER2[0]>2&&BUFFER2[0]<15)
		{
			W_DIAMOND(4,(BUFFER2[0]-2)*2+5);
			W_HDIAMOND(4,(BUFFER2[0]-2)*2+3);
		}
		
		if(BUFFER2[0]>15&&BUFFER2[0]<28)
		{
			W_DIAMOND(23,(BUFFER2[0]-15)*2+5);
			W_HDIAMOND(23,(BUFFER2[0]-15)*2+3);
		} 
		
	}
}
//****************************************************/
/*	���ܣ����Ұ��������������й���Ƶ��ѡ��
��ڲ�������
���ڲ�������
/*****************************************************/
void Manualmode_Leftright() ;
void Manualmode_Leftright()          
{
 	 if (G_Key==RIGHT||G_Key==LEFT)
    {
    	unsigned char i;
    	if(BUFFER2[0]==0)
    	{
	    	if (G_Key==RIGHT)
			{
	       
	        	BUFFER2[1]=(BUFFER2[1]+1)%3;              	//�����ƶ���BUFFER2[1]��Ƶ�� 
			}
			
			if (G_Key==LEFT)
			{
	      
	        	BUFFER2[1]=(BUFFER2[1]+2)%3;             
			}
			G_Key=0;
			if(BUFFER2[1]==0)								//��ʾѡ��Ƶ��
			{
			
				CTAB[0]='5';   CTAB[1]='1';	CTAB[2]='8';	CTAB[3]='K';	CTAB[4]='H';
				CTAB[5]='Z';   CTAB[6]=' ';	CTAB[7]=' ';	CTAB[8]=' ';
				CW_PR(13,3,9);
			}
			
			if(BUFFER2[1]==1)
			{
				CTAB[0]='4';   CTAB[1]='8';	CTAB[2]='6';	CTAB[3]='K';	CTAB[4]='H';
				CTAB[5]='Z';   CTAB[6]=' ';	CTAB[7]=' ';	CTAB[8]=' ';
				CW_PR(13,3,9); 
			}
			
			if(BUFFER2[1]==2)
			{
				CTAB[0]='4';   CTAB[1]='2';	CTAB[2]='0';	CTAB[3]='9';	CTAB[4]='.';
				CTAB[5]='5';	CTAB[6]='K';	CTAB[7]='H'; CTAB[8]='Z';
				CW_PR(13,3,9); 
			}
			
			for(i=0;i<13;i++)
			{
				if(Manualtemp[BUFFER2[1]][i]==0) W_CHOOSED(7,i*2+5);
				else  W_CANCALCHOOSED(7,i*2+5);
			}
			
			for(i=13;i<26;i++)
			{
				if(Manualtemp[BUFFER2[1]][i]==0) W_CHOOSED(26,(i-13)*2+5);
				else  W_CANCALCHOOSED(26,(i-13)*2+5);
			}	
    	}
    	if(BUFFER2[0]==1)
    	{
    		if (G_Key==RIGHT)
			{
		        BUFFER2[2]=BUFFER2[2]%16+1;         //�����ƶ���BUFFER2[1]������ 
			}
			if (G_Key==LEFT)
			{
		       	BUFFER2[2]=(BUFFER2[2]+14)%16+1;             
			}
			G_Key=0;
			DISASCII(17,4,BUFFER2[2]);				//��������ʾ�����ú���DISASCII	
    		manual_area_temp=BUFFER2[2];
    	}					
    }

}
//************************************************/
/*	���ܣ�CLR���������������ص��ϼ��˵�Rxstation
��ڲ�������
���ڲ�������
/*************************************************/ 
void Manualmode_Return();
void Manualmode_Return()
{
	unsigned char i,j;
	if (G_Key==CLR)         //���ص�ԭ������  
	{
		G_Key=0;
		BUFFER2[2]=0;		//�õ�ȫ�ֱ�������
		BUFFER2[1]=0;
		BUFFER2[0]=0;	
		for(j=0;j<3;j++)	//Manualtemp�ָ�Manual��ֵ
		{
			for(i=0;i<26;i++)
			{
				Manualtemp[j][i]=Manual[j][i];
			}
		}
		manual_area_temp=manual_area;
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
void Manualmode_Dealing();
void Manualmode_Dealing()
{
	word i;             
	if (G_Key==ENT&&BUFFER2[0]>1)
	{
		G_Key=0;
		if(BUFFER2[0]<15)
		{
			Manualtemp[BUFFER2[1]][BUFFER2[0]-2]=(Manualtemp[BUFFER2[1]][BUFFER2[0]-2]+1)%2;           //����һ��ENT�ı�BUFFER2[i+1]��ֵ���Ƿ����	
			if(Manualtemp[BUFFER2[1]][BUFFER2[0]-2]==0) W_CHOOSED(7,(BUFFER2[0]-2)*2+5);
			else  W_CANCALCHOOSED(7,(BUFFER2[0]-2)*2+5);
		}

		if(BUFFER2[0]>14)
		{
			Manualtemp[BUFFER2[1]][BUFFER2[0]-2]=(Manualtemp[BUFFER2[1]][BUFFER2[0]-2]+1)%2;           //����һ��ENT�ı�BUFFER2[i+1]��ֵ���Ƿ����	
			if(Manualtemp[BUFFER2[1]][BUFFER2[0]-2]==0) W_CHOOSED(26,(BUFFER2[0]-15)*2+5);
			else  W_CANCALCHOOSED(26,(BUFFER2[0]-15)*2+5);
		}	

	}        

}

//****************************************************/
/*	���ܣ�STAR�����������������Ӳ˵�AutomodeSubmenu
��ڲ�������
���ڲ�������
/*****************************************************/ 
void Manualmode_Submenu();
void Manualmode_Submenu()
{
	if (G_Key==STAR&&STATE==401)	
	{
		G_Key=0;				//��������
//		ProtectData(); 			//���浯���˵���������
		LANHELP=1;    			//�ָ�LANHELPֵΪ1
		FLAG=0;					//����ѭ��
		STATE=4000;				//AutomodeSubmenu״̬Ϊ4000
		State4000parameter=1;	//��ڲ���Ϊ1����ʾ��Manualmode�˵�����
	}
}


//**************************************************/
/*	���ܣ��Զ�ģʽ�£����Ե�������ÿ��������ÿ����̨
          ������񣬽�������ڰ�̨��򹴣���������
          BUFFER2[0] ��¼ѡ����
          BUFFER2[1] ��¼��������Ƶ��(0~2)
          BUFFER2[2] ��¼��ǰ����(0~2)���Զ�ģʽ������
          subback    ��¼�Ӻβ˵�����
��ڲ�����into char�� ��¼�ӺͲ˵�����
���ڲ�������
/***************************************************/ 
void RunManualmode(unsigned char into)
{
    maske=0;
    maskc=0;
	subback=into;
	LANHELP=0;
	Manualmode_Paintintial();
	
	while(FLAG)                          
	{
		Manualmode_Updn();
		Manualmode_Leftright();		
		Manualmode_Return();		
		Manualmode_Dealing();
		Manualmode_Submenu();
		run_tip();
	}

}