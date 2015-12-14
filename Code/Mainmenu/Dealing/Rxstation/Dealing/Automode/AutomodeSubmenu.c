#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "run.h"
#include "define.h"	
#include "Eprom.h"
#include "lcddrive.h"
#include "code.h"

//volatile byte parameter;

//********************************************/
/*	���ܣ�Automodesubmenu�������ʾ
��ڲ�������
���ڲ�������
/*********************************************/
void Automodesubmenu_Paintintial();
void Automodesubmenu_Paintintial()
{
	byte i;
//	CLEAR2();		//�����Ӳ˵������������
	WFRAME();		//�����Ӳ˵���ͼ��ʾ
	if(LANGUAGE==0)	//Ӣ�Ĳ˵�
	{
		CTAB[4]='*';  CTAB[5]='S';   CTAB[6]='E';  CTAB[7]='T'; 
		CTAB[9]='U';  CTAB[10]='P'; CTAB[11]='*';
		CW_PR(9,14,12);	//��һ����ʾ����"*SET UP*"


		  
		CTAB[5]='S';  CTAB[6]='A';  CTAB[7]='V';  CTAB[8]='E';  
		CW_PR(8,16,9);	//�ڶ�����ʾ����"SAVE"

		  
		CTAB[5]='C';  CTAB[6]='L';  CTAB[7]='E';  CTAB[9]='C'; CTAB[10]='U';
		CTAB[11]='R'; CTAB[12]='S'; CTAB[13]='E'; CTAB[14]='T';
		CW_PR(8,17,15);	//��������ʾ����"CLE CUR SET"

		  
		CTAB[5]='C';  CTAB[6]='L';  CTAB[7]='E';  CTAB[9]='A';  CTAB[10]='L';
		CTAB[11]='L'; CTAB[12]='S'; CTAB[13]='E'; CTAB[14]='T'; 
		CW_PR(8,18,15);	//��������ʾ����"CLE ALL SET"


		CTAB[5]='C';  CTAB[6]='A';  CTAB[7]='N';  CTAB[8]='C';  CTAB[9]='E';
		CTAB[10]='L';  
		CW_PR(8,19,11);	//��������ʾ����"CLNCEL"		
	}
	else				//���Ĳ˵�
	{
		CCW_PR1(13,100,0xb1a3,1);	//��һ����ʾ����"����"
		CCW_PR1(15,100,0xb4e6,1);
		
		CCW_PR1(13,118,0xc8a1,1);	//�ڶ�����ʾ����"ȡ����ǰ����"
		CCW_PR1(15,118,0xcffb,1);
		CCW_PR1(17,118,0xb5b1,1);
		CCW_PR1(19,118,0xc7b0,1);
		CCW_PR1(21,118,0xb2d9,1);
		CCW_PR1(23,118,0xd7f7,1);  
				
		CCW_PR1(13,136,0xc8a1,1);	//��������ʾ����"ȡ�����в���"
		CCW_PR1(15,136,0xcffb,1);
		CCW_PR1(17,136,0xcbf9,1);
		CCW_PR1(19,136,0xd3d0,1);
		CCW_PR1(21,136,0xb2d9,1);
		CCW_PR1(23,136,0xd7f7,1);  
				
		CCW_PR1(13,154,0xb7b5,1);	//��������ʾ����"����"
		CCW_PR1(15,154,0xbbd8,1);		
	}

	W_DIAMOND(11,LANGUAGE?104:16);	//��ѡ����
	W_HDIAMOND(11,LANGUAGE?122:17);
	W_HDIAMOND(11,LANGUAGE?140:18);
	W_HDIAMOND(11,LANGUAGE?158:19);
}

//********************************************/
/*	���ܣ����°�����������ѡ������ѡ����
��ڲ�������
���ڲ�������
/*********************************************/
void Automodesubmenu_Updn();
void Automodesubmenu_Updn()
{
	if(parameter==2)	//��ʱѡ�������Ϣ�����Ӳ˵������õĲ�����BUFFER2[]
	{
		if (G_Key==UP&&BUFFER2[0]>0)
		{
			BUFFER2[0]=BUFFER2[0]-1;        //������������
			G_Key=0;						//��������
			W_DIAMOND(11,LANGUAGE?(104+BUFFER2[0]*18):(BUFFER2[0]+16));	
			W_HDIAMOND(11,LANGUAGE?(122+BUFFER2[0]*18):(BUFFER2[0]+17));	
		}
		
		if (G_Key==DOWN&&BUFFER2[0]<3)
		{
			BUFFER2[0]=BUFFER2[0]+1;       	//������������
			G_Key=0;						//��������
			W_DIAMOND(11,LANGUAGE?(104+BUFFER2[0]*18):(BUFFER2[0]+16));	
			W_HDIAMOND(11,LANGUAGE?(86+BUFFER2[0]*18):(BUFFER2[0]+15));		
		}	
	}
	
	else				//��parameter������2ѡ���������ΪBUFFER3[]
	{
		if (G_Key==UP&&BUFFER3[0]>0)
		{
			BUFFER3[0]=BUFFER3[0]-1;        //������������
			G_Key=0;						//��������			
			W_DIAMOND(11,LANGUAGE?(104+BUFFER3[0]*18):(BUFFER3[0]+16));	
			W_HDIAMOND(11,LANGUAGE?(122+BUFFER3[0]*18):(BUFFER3[0]+17));	
		}
		
		if (G_Key==DOWN&&BUFFER3[0]<3)
		{
			BUFFER3[0]=BUFFER3[0]+1;       	//������������
			G_Key=0;						//��������
			W_DIAMOND(11,LANGUAGE?(104+BUFFER3[0]*18):(BUFFER3[0]+16));	
			W_HDIAMOND(11,LANGUAGE?(86+BUFFER3[0]*18):(BUFFER3[0]+15));			
		}	
	}
}


//**************************************************************/
/*	���ܣ�ENT���������������б��棬ȡ����ǰ������ȡ�����Բ���
          ���߷�����һ���˵�����
��ڲ�������
���ڲ�������
/***************************************************************/
void Automodesubmenu_Dealing();
void Automodesubmenu_Dealing()
{		
 	if(parameter==0)		//�Զ�ģʽ�˵����Ӳ˵�
 	{
		if(G_Key==ENT)
		{
			G_Key=0;				//��������
			FLAG=0;         		//����ѭ��
			STATE=400;      		//Automode��״̬Ϊ400
			State400parameter=10; 	//��ڲ���Ϊ10���������Ӳ˵�����
			
			if (BUFFER3[0]==0)                         	//���浱ǰ
			{
				unsigned char i,j;
				for(j=0;j<3;j++)
				{
					for(i=0;i<26;i++)
						{
							Auto[j][i]=Autotemp[j][i];	//����ʱ����Autotemp������Auto
						}
				}
				Eprom_AutoMode_Save();					//������Ϣ����Eprom	
				BUFFER3[0]=0;							//ȫ�ֱ�������
			}
						
		        
			if (BUFFER3[0]==1)                         	//ȡ����ǰ���ã�ֻ�Ե�ǰ������Ƶ���½�������ȡ��
			{   
				word i,temp,t,p,temp1,temp2;
				temp2=Power(BUFFER2[1]-1);
				t=~temp2;
//				t=(word)(pow(2,16))-1-(word)(pow(2,BUFFER2[1]-1));
				p=temp2;
				for(i=0;i<26;i++)
				{
					temp1=Power(BUFFER2[1]-1);
				//	temp1=(word)(pow(2,BUFFER2[1]-1));
					temp=Auto[BUFFER2[2]][i]&temp1;
					if(temp==0) 
					Autotemp[BUFFER2[2]][i]=Autotemp[BUFFER2[2]][i]&t;
					else
					Autotemp[BUFFER2[2]][i]=Autotemp[BUFFER2[2]][i]|p;	
				}
				BUFFER3[0]=0;
			}
			
			if (BUFFER3[0]==2)                         	//ȡ������
			{   
				unsigned char i,j;

				for(j=0;j<3;j++)
				{
					for(i=0;i<26;i++)
						{
							Autotemp[j][i]=Auto[j][i];	//Autotemp�ָ�ΪAuto��ֵ
						}
				}			
				BUFFER3[0]=0;
			}
	    
	    	if (BUFFER3[0]==3)                         	//�˳�
			{   
		        	BUFFER3[0]=0;                       //�����������κβ���
 			}
		} 	
	}

	if(parameter==1)		//�ֶ�ģʽ�˵����Ӳ˵�
	{
 		unsigned char i,j;
	 	if(G_Key==ENT)									
		{	
			G_Key=0;				//��������
			FLAG=0;         		//����ѭ��
			STATE=401;      		//Manualmode��״̬Ϊ400
			State400parameter=10; 	//��ڲ���Ϊ10���������Ӳ˵�����
		
			if (BUFFER3[0]==0)                         		//����
			{
				for(j=0;j<3;j++)
				{
					for(i=0;i<26;i++)
					{
						Manual[j][i]=Manualtemp[j][i];		//����ʱ����Autotemp������Auto
					}
				}
				manual_area=manual_area_temp;
				BUFFER3[0]=0;
				Eprom_ManualMsgMode_Save(RXSTATION_MANUAL);	//������Ϣ����Eprom
			}
			
			
			if (BUFFER3[0]==1)                         		//ȡ����ǰ��¼
			{   
								
				for(i=0;i<26;i++)							
					{
						Manualtemp[BUFFER2[1]][i]=Manual[BUFFER2[1]][i];
					}
				manual_area_temp=manual_area;
				BUFFER3[0]=0;	
			}
			
			if (BUFFER3[0]==2)                         		//ȡ�����ã�����ȫ��������Ƶ��
			{   
				for(j=0;j<3;j++)
				{
					for(i=0;i<26;i++)
					{
						Manualtemp[j][i]=Manual[j][i];
					}
				}
				manual_area_temp=manual_area;
				BUFFER3[0]=0;
			}
			    
	    	if (BUFFER3[0]==3)                         		//�˳�
			{   
		 			BUFFER3[0]=0;                     
			}
 		}		
	}
 		
 	if(parameter==2)						//��Ϣ���˵����Ӳ˵�												
 	{
	 	if(G_Key==ENT)						//����Messagetypemenu�˵�;
		{
			unsigned char i=0,j;		
			G_Key=0;				//��������
			FLAG=0;         		//����ѭ��
			STATE=41;      			//Messagetypemenu��״̬Ϊ400
			State400parameter=10; 	//��ڲ���Ϊ10���������Ӳ˵�����								
			if (BUFFER2[0]==0)                         	//���浱ǰ
			{
				for(j=0;j<3;j++)
				{
					for(i=0;i<26;i++)
					{
						MSGTYPE[j][i]=MSGTYPETEMP[j][i];	
					}
					Eprom_ManualMsgMode_Save(RX_MSGTYPE);//������Ϣ����Eprom
				}
				BUFFER2[0]=0;
			}
			
			if (BUFFER2[0]==1)                         	//ȡ�����ã�������ȫ����ֻ����ĳƵ��ǰ����
			{   
				for(i=0;i<26;i++)
				{
					MSGTYPETEMP[BUFFER1[1]][i]=MSGTYPE[BUFFER1[1]][i];
				}
				BUFFER2[0]=0;		
			}
			
			if (BUFFER2[0]==2)                         	//ȡ�����ã�����ȫ��������Ƶ��
			{   
				for(j=0;j<3;j++)
				{
					for(i=0;i<26;i++)
					{
						MSGTYPETEMP[j][i]=MSGTYPE[j][i];
					}
				}
				BUFFER2[0]=0;
			}
			
	    	if (BUFFER2[0]==3)                         	//�˳�
			{   
		    	{
	   				BUFFER2[0]=0;                    
				}
			}
		}
 	}
 }


//**********************************************************/
/*	���ܣ��Զ�ģʽ�˵����ֶ�ģʽ�˵�����Ϣ���˵��ǵ��Ӳ˵���
          ����ȷ����ѡ���İ�̨����Ϣ��� 	
          BUFFER2[0] ��¼ѡ����
          BUFFER3[0] ������Ϣ���˵�ѡ����ļ�¼
          parameter  ��¼�Ӻβ˵�����
��ڲ�����into ��¼�Ӻβ˵�����
          0��ʾ�Զ�ģʽ�˵���
          1��ʾ�ֶ�ģʽ�˵���
          2��ʾ��Ϣ���˵�
���ڲ�������
/***********************************************************/ 
void RunAutomodeSubmenu(byte into)
{
    maske=0;
    maskc=0;
	parameter=into;
	Automodesubmenu_Paintintial();
	
	while(FLAG)
	{
		Automodesubmenu_Updn();		
		Automodesubmenu_Dealing();
		run_tip();
	}	
}