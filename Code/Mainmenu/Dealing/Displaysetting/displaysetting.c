#include <stdio.h>
#include <stdlib.h>
#include  "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "Eprom.h"
#include "ThreeDays.h"
#include "code.h"
#include "rtc.h"
#include "PWM.h"

//��ʼʱ����������Ļ��λ�� Ӣ��(13,15) ����(15,19)
//��ʼʱ����������Ļ��λ�� Ӣ��(14,20) ����(15,24)

extern void TIM3_IRQHandler(void);

//********************************************/
/*	���ܣ���ʾ���ò˵�Displaysetting����ʾ
��ڲ�������
���ڲ�������
/*********************************************/
void Displaysetting_Con_Back();
void Displaysetting_Con_Back()
{
	
	if(LANGUAGE==0) 	//Ӣ��
	{
		CW_PR3(14,5,'1'+Contrast);		//�Աȶȼ�����ʾ
		CW_PR3(16,23,'1'+Backlight);	//���⼶����ʾ
	}
	
	else				//����
	{
		CCW_PR1(13,32,0x1980+Contrast*0x20,0);
		CCW_PR1(11,208,0x1980+Backlight*0x20,0);			
	}
	
}
//********************************************/
/*	���ܣ���ʾ���ò˵�Displaysetting����ʾ
��ڲ�������
���ڲ�������
/*********************************************/
void Displaysetting_Paintintial();
void Displaysetting_Paintintial()
{
	byte i;

	
	if(LANGUAGE==0)	//Ӣ�Ľ���
	{

		 /* д���ͷ����DISPLAY SET */
		CTAB[2]='D';	CTAB[3]='I';	CTAB[4]='S';	CTAB[5]='P';	CTAB[6]='L';
		CTAB[7]='A';	CTAB[8]='Y';
		CTAB[10]='S';	CTAB[11]='E';	CTAB[12]='T';
		CW_PR(0,1,13);
		
		 /* �Աȶ�RX_CONTRAST: LEVEL */
		CTAB[5]='C';	CTAB[6]='O';	CTAB[7]='N';	CTAB[8]='T';	CTAB[9]='R';
		CTAB[10]='A';	CTAB[11]='S';	CTAB[12]='T';	CTAB[13]=':'; 	CTAB[16]='L';
		CTAB[17]='E';	CTAB[18]='V';	CTAB[19]='E';	CTAB[20]='L'; 		 
		CW_PR(0,5,21);

		 /* ����BUZZER */
		CTAB[5]='B';	CTAB[6]='U';	CTAB[7]='Z';	CTAB[8]='Z';	CTAB[9]='E';
		CTAB[10]='R';	 
		CW_PR(0,8,11);

		 /* �������ĸ���ѡ��ALARM MSG:ON */
		CTAB[0]='A';	CTAB[1]='L';	CTAB[2]='A';	CTAB[3]='R';	CTAB[4]='M';
		CTAB[6]='M';	CTAB[7]='S';	CTAB[8]='G';	CTAB[13]=':';	CTAB[14]='O';
		CTAB[15]='N';	 
		CW_PR(8,9,16);

		 /* �������ĸ���ѡ��:RECEIVER MSG:ON */
		CTAB[0]='R';	CTAB[1]='E';	CTAB[2]='C';	CTAB[3]='E';	CTAB[4]='I';
		CTAB[5]='V';	CTAB[6]='E';	CTAB[7]='R';	CTAB[9]='M';	CTAB[10]='S';
		CTAB[11]='G';	CTAB[13]=':';	CTAB[14]='O';	CTAB[15]='N'; 
		CW_PR(8,10,16);
		
		 /* �������ĸ���ѡ�� NAVTEX ALARM:ON*/
		CTAB[0]='N';	CTAB[1]='A';	CTAB[2]='V';	CTAB[3]='T';	CTAB[4]='E';
		CTAB[5]='X';	CTAB[7]='A';	CTAB[8]='L';	CTAB[9]='A';
		CTAB[10]='R';	CTAB[11]='M';	CTAB[13]=':';	CTAB[14]='O';	CTAB[15]='N'; 
		CW_PR(8,11,16);
		
		 /* �������ĸ���ѡ�� CLICK:ON*/
		CTAB[0]='C';	CTAB[1]='L';	CTAB[2]='I';	CTAB[3]='C';	CTAB[4]='K';
		CTAB[13]=':';	CTAB[14]='O';	CTAB[15]='N';
		CW_PR(8,12,16);

		/* ����ʱ��LOCAL TIME:20  /  /  /  : */
		CTAB[5]='L';	CTAB[6]='O';	CTAB[7]='C';	CTAB[8]='A';	CTAB[9]='L';  CTAB[11]='T';
		CTAB[12]='I';	
		CTAB[13]='M';	CTAB[14]='E';	CTAB[15]=':';   CTAB[16]='2';	CTAB[17]='0';	CTAB[20]='/';	
		CTAB[23]='/';	
		CTAB[26]='/';	CTAB[29]=':';
		CW_PR(0,15,30);  

		/* ����ʱ��IT TIME:OFF */
		CTAB[0]='I';	CTAB[1]='T';	CTAB[3]='T';	CTAB[4]='I';	CTAB[5]='M';	CTAB[6]='E';
		CTAB[7]=':';
		CTAB[8]='O';	CTAB[9]='F';	CTAB[10]='F';
		CW_PR(5,18,11);
		
		
		/* ����ʱ��IT TIME:20  /  /  /  : */
		//CTAB[5]='I';	CTAB[6]='T';	CTAB[8]='T';	CTAB[9]='I';	CTAB[10]='M';
		//CTAB[11]='E';	CTAB[12]=':';	CTAB[13]='2';	CTAB[14]='0';
		//CTAB[17]='/';	CTAB[20]='/';	CTAB[23]='/';	CTAB[26]=':';
		//CW_PR(0,15,27);  

		/* ����ʱ��LOCAL TIME:OFF */
		//CTAB[0]='L';	CTAB[1]='O';	CTAB[2]='C';	CTAB[3]='A';	CTAB[4]='L';	CTAB[6]='T';
		//CTAB[7]='I';
		//CTAB[8]='M';	CTAB[9]='E';	CTAB[10]=':';	CTAB[11]='O';	CTAB[12]='F';	CTAB[13]='F';
		//CW_PR(5,18,14);

		/* ����ʱ��ʱ������TIME DIF:+ */
		CTAB[0]='T';	CTAB[1]='I';	CTAB[2]='M';	CTAB[3]='E';	CTAB[5]='D';
		CTAB[6]='I';
		CTAB[7]='F';	CTAB[8]=':';	CTAB[9]='+';
		CW_PR(5,20,10);	
		
		/* �Աȶ�����BACKLIGHT: LEVEL */
		CTAB[0]='B';	CTAB[1]='A';	CTAB[2]='C';	CTAB[3]='K';	CTAB[5]='L';
		CTAB[6]='I';	CTAB[7]='G';	CTAB[8]='H';	CTAB[9]='T';
		CTAB[10]=':'; 	
		CTAB[13]='L';	CTAB[14]='E';	CTAB[15]='V';	CTAB[16]='E';	CTAB[17]='L'; 
		CW_PR(5,23,18);			
	}
	
	else //���Ľ���
	{
 		CCW_PR1(1,6,0xcfd4,1);		//��һ������"��ʾ����"
 		CCW_PR1(3,6,0xcabe,1);
 		CCW_PR1(5,6,0xc9e8,1);
 		CCW_PR1(7,6,0xd6c3,1);
 		
 		CCW_PR1(5,32,0xb6d4,1);		//�ڶ�������"�Աȶ�: ��"
 		CCW_PR1(7,32,0xb1c8,1);
 		CCW_PR1(9,32,0xb6c8,1);
 		CCW_PR1(11,32,0x1aa0,0);
 		CCW_PR1(15,32,0xbcb6,1); 		
 		
  		CCW_PR1(5,56,0xb7e4,1);		//����������"����"
 		CCW_PR1(7,56,0xc3f9,1);
 			
 		CCW_PR1(8,72,0xd0c5,1);		//����������"��Ϣ����():��"
 		CCW_PR1(10,72,0xcfa2,1);
 		CCW_PR1(12,72,0xbeaf,1);
 		CCW_PR1(14,72,0xb1a8,1);
 		CCW_PR1(18,72,0x1aa0,0);
 		CCW_PR1(20,72,0xbfaa,1);  
 
 		CCW_PR1(8,88,0xbdd3,1);		//����������"������Ϣ:��"
 		CCW_PR1(10,88,0xcad5,1);
 		CCW_PR1(12,88,0xd0c5,1);
 		CCW_PR1(14,88,0xcfa2,1);
 		CCW_PR1(18,88,0x1aa0,0);
 		CCW_PR1(20,88,0xbfaa,1); 		
 		
  		CCW_PR1(8,104,0xbdd3,1);	//����������"���ջ�����:��"
 		CCW_PR1(10,104,0xcad5,1);
 		CCW_PR1(12,104,0xbbfa,1);
 		CCW_PR1(14,104,0xbeaf,1);
 		CCW_PR1(16,104,0xb1a8,1);
 		CCW_PR1(18,104,0x1aa0,0);
 		CCW_PR1(20,104,0xbfaa,1);
 		
  		CCW_PR1(8,120,0xb5e3,1);	//����������"���:��"
 		CCW_PR1(10,120,0xbbf7,1);
 		CCW_PR1(18,120,0x1aa0,0);
 		CCW_PR1(20,120,0xbfaa,1); 		
 		
 		CCW_PR1(5,144,0xb1be,1);	//�ڰ�������"����ʱ��"
 		CCW_PR1(7,144,0xb5d8,1);
 		CCW_PR1(9,144,0xcab1,1);
 		CCW_PR1(11,144,0xbce4,1);
 		CCW_PR1(13,144,0x1aa0,0); 

		/* ����ʱ�䣬���Ľ�����ʱ�����ֵ��ʵ�Ծ�ʹ��Ӣ�ĵ��ַ���ʵ */
		CTAB[13]='2';	CTAB[14]='0';	CTAB[17]='/';CTAB[20]='/';	CTAB[23]='/';
		CTAB[26]=':';
		CW_PR(2,19,27);  		
 		
  		CCW_PR1(5,168,0xb9fa,1);	//�ھ�������"����ʱ��:��"
 		CCW_PR1(7,168,0xbcca,1);
 		CCW_PR1(9,168,0xcab1,1);
 		CCW_PR1(11,168,0xbce4,1);
 		CCW_PR1(13,168,0x1aa0,0); 		
 		CCW_PR1(15,168,0xb9d8,1);		 		
 		
  		CCW_PR1(9,184,0xcab1,1);	//��ʮ������"ʱ��"
 		CCW_PR1(11,184,0xb2ee,1);		
 		CCW_PR1(13,184,0x1aa0,0); 
 		CW_PR3(LANGUAGE?15:14,LANGUAGE?24:20,'+'); 			//��ʾʱ���������
 		
 		CCW_PR1(5,208,0xb1b3,1);		//��ʮһ������"����: ��"
 		CCW_PR1(7,208,0xb9e2,1);
 		CCW_PR1(9,208,0x1aa0,0);
 		CCW_PR1(13,208,0xbcb6,1);  		
	}
 

	DISASCII(LANGUAGE?17:18,LANGUAGE?19:15,iyear);			//��ʾ����ʱ�����ֵ
	DISASCII(LANGUAGE?20:21,LANGUAGE?19:15,imonth);
	DISASCII(LANGUAGE?23:24,LANGUAGE?19:15,iday);
	DISASCII(LANGUAGE?26:27,LANGUAGE?19:15,ihour);
	DISASCII(LANGUAGE?29:30,LANGUAGE?19:15,iminute);
	
	W_YLINE(0,0,239);				//Y��������߿�
	W_YLINE(319,0,239);	
						
						
	for(i=0;i<4;i++)				//���ѡ�������ʾ
	{
		W_HDIAMOND(6,LANGUAGE?(76+16*i):(9+i));
	}
	
	W_DIAMOND(3,LANGUAGE?36:5);	   
	W_HDIAMOND(3,LANGUAGE?60:8);
	W_HDIAMOND(3,LANGUAGE?148:15);
	W_HDIAMOND(3,LANGUAGE?172:18);
	W_HDIAMOND(3,LANGUAGE?212:23);
	
	if(sign==0) CW_PR3(LANGUAGE?15:14,LANGUAGE?24:20,'-'); 	//��ʾʱ���������
	DISASCII(LANGUAGE?16:15,LANGUAGE?24:20,number);			//��ʾʱ�����ֵ
		
/*	if(Contrast==1)											//��ʾ�Աȶ�
	{
		if(LANGUAGE==0) CW_PR3(14,5,'M');	
		else CCW_PR1(13,32,0xd6d0,1);
	}
	
	if(Contrast==2)	
	{
		if(LANGUAGE==0) CW_PR3(14,5,'L');					//��ʾ�Աȶ�
		else CCW_PR1(13,32,0xb5cd,1);
	}	
	
	if(Backlight==1)										//��ʾ���⣺��
	{
		if(LANGUAGE==0) CW_PR3(16,23,'M');	
		else CCW_PR1(11,208,0xd6d0,1);		
	}
	
	if(Backlight==2)										//��ʾ���⣺��
	{
		if(LANGUAGE==0) CW_PR3(16,23,'L');	
		else CCW_PR1(11,208,0xb5cd,1);		
	}*/
	Displaysetting_Con_Back();
	
	for(i=0;i<4;i++)										//��ʾ�����Ŀ�������
	{
		if(Buzzer[i]==0&&LANGUAGE==0)
		{
			CW_PR3(23,i+9,'F');
			CW_PR3(24,i+9,'F');
		}
		
		if(Buzzer[i]==0&&LANGUAGE==1)
		CCW_PR1(20,72+i*16,0xb9d8,1); 
	}
	
	if(lcontrol==1&&LANGUAGE==0)							//��ʾ����ʱ�� �Ŀ���
		{
			CW_PR3(14,18,'N');
			CW_PR3(15,18,' ');
		}
		
	if(lcontrol==1&&LANGUAGE==1)
	CCW_PR1(15,168,0xbfaa,1);
	
	W_Mode(35,6,32,1);										//�ֶ����Զ�ģʽ����ʾ
}
 
//********************************************/
/*	���ܣ����°�����������ѡ������ѡ���
����������TODʱ�����ã�����ʱ�������ã�ʱ������
��ڲ�������
���ڲ�������
/*********************************************/ 
void Displaysetting_Updn();
void Displaysetting_Updn()
{
	if(G_Key==UP||G_Key==DOWN)
	{
		if (G_Key==UP)
		{
			G_Key=0;		//��������
			if(BUFFER1[0]==1 || BUFFER1[0]==2 || BUFFER1[0]==3 || BUFFER1[0]==4 )	//������������,0 1 2 3 4Ϊ�Աȶȡ�����������ʱ��ͱ���ʱ��
			{
				BUFFER1[0]=BUFFER1[0]-1;
				if(BUFFER1[0]==0)
				{
					W_DIAMOND(3,LANGUAGE?36:5);	   
					W_HDIAMOND(3,LANGUAGE?60:8); 			
				}
				
				if(BUFFER1[0]==1)
				{
					W_DIAMOND(3,LANGUAGE?60:8);	   
					W_HDIAMOND(3,LANGUAGE?148:15); 			
				}
				if(BUFFER1[0]==2)
				{
					W_DIAMOND(3,LANGUAGE?148:15);	   
					W_HDIAMOND(3,LANGUAGE?172:18); 			
				}			
	
				if(BUFFER1[0]==3)
				{
					W_DIAMOND(3,LANGUAGE?172:18);	   
					W_HDIAMOND(3,LANGUAGE?212:23); 			
				}       
			}
			
			if(BUFFER1[0]>5 && BUFFER1[0]<=8 )        				//������������, 4 5 6 7Ϊ��Ϣ������������Ϣ��������Ϣ�����
			{
				BUFFER1[0]=BUFFER1[0]-1;
				
				W_DIAMOND(6,LANGUAGE?(76+(BUFFER1[0]-5)*16):(BUFFER1[0]+4));	   
				W_HDIAMOND(6,LANGUAGE?(76+(BUFFER1[0]-4)*16):(BUFFER1[0]+5)); 			
				        
			}
			
		 	/*  TOD���ã�ʱ�����룭��  */

			if (BUFFER1[0]==9&&iyear<99)            //���1 ֻ��ʾ����λ����ʼֵΪ08����Χ08��99
			{
				iyear=iyear+1;
			}
				
			if (BUFFER1[0]==10&&imonth<12)        	//�¼�1,��ʼֵΪ1����Χ1��12,ͬʱ��Ҫ�޸Ķ�Ӧ��������������ĳЩ�·ݳ��ֲ����е�����
			{
				imonth=imonth+1;
				if(imonth==4||imonth==6||imonth==9||imonth==11) 
				{
					if (iday>30 )					//С������30,��ʱ����������30�죬�ָ���30��
					iday=30;
				}
				if(imonth==2)
				{
					if(iyear%4==0)                  //��ʾ���꣬2������29,��ʱ����������29�죬�ָ���29��
					{
						if (iday>29 )
						iday=29;
					}
					else							//�����꣬2������28,��ʱ����������28�죬�ָ���28��
					{
						if (iday>28 )
						iday=28; 
					}
				}
			}
			
			if (BUFFER1[0]==11)       				//�ռ�1,��ʼֵΪ1����Χ1��31,1-30,1-29,1-28
			{
				if(imonth==1||imonth==3||imonth==5||imonth==7||imonth==8||imonth==10||imonth==12)   //���£�ÿ������31��
				{
					if (iday<31 )
					iday=iday+1;
				}
				
				if(imonth==4||imonth==6||imonth==9||imonth==11)     	//С�£�ÿ������30��
				{
					if (iday<30 )
					iday=iday+1;
				}
				if(imonth==2)
				{
					if(iyear%4==0)                  //��ʾ���꣬2������29
					{
						if (iday<29 )
						iday=iday+1;
					}
					else							//�����꣬2������28
					{
						if (iday<28 )
						iday=iday+1; 
					}
				}
			}
				
			
			if (BUFFER1[0]==12&&ihour<23)       	//ʱ��1,��ʼֵΪ0����Χ0��23
			{
				ihour=ihour+1;
			}
				
			
			if (BUFFER1[0]==13&&iminute<59)       	//�ּ�1,��ʼֵΪ0����Χ0��59
			{
				
				iminute=iminute+1;
			}
			
			
	
			if (BUFFER1[0]==14)         
			{
				sign=(sign+1)%2;  					//sign=1������sign=0��
			}
			
			if(BUFFER1[0]==15&&number<12)	number=number+1;	//����ʱ�����������
			
		}
		
		if (G_Key==DOWN)
		{
			G_Key=0;								//��������
			if(BUFFER1[0]==0||BUFFER1[0]==1||BUFFER1[0]==2 ||BUFFER1[0]==3)        
			{
				BUFFER1[0]=BUFFER1[0]+1;			//������������,0 1 2 3Ϊ�Աȶȡ�����������ʱ��ͱ���ʱ��
				if(BUFFER1[0]==3)
				{
					W_DIAMOND(3,LANGUAGE?172:18);	   
					W_HDIAMOND(3,LANGUAGE?148:15); 			
				}
				
				if(BUFFER1[0]==1)
				{
					W_DIAMOND(3,LANGUAGE?60:8);	   
					W_HDIAMOND(3,LANGUAGE?36:5); 			
				}
				if(BUFFER1[0]==2)
				{
					W_DIAMOND(3,LANGUAGE?148:15);	   
					W_HDIAMOND(3,LANGUAGE?60:8); 			
				}
				
				if(BUFFER1[0]==4)
				{
					W_DIAMOND(3,LANGUAGE?212:23);	   
					W_HDIAMOND(3,LANGUAGE?172:18); 			
				}				
				        
			}
			if(BUFFER1[0]>4 && BUFFER1[0]<8 )        //������������,BUFFER1[0]= 4 5 6 7Ϊ��Ϣ������������Ϣ��������Ϣ�����
			{
				BUFFER1[0]=BUFFER1[0]+1;
				W_DIAMOND(6,LANGUAGE?(76+(BUFFER1[0]-5)*16):(BUFFER1[0]+4));	   
				W_HDIAMOND(6,LANGUAGE?(76+(BUFFER1[0]-6)*16):(BUFFER1[0]+3)); 	        
			}
			

	
		 	/*  TOD���ã�ʱ�����룭��  */
	
			if (BUFFER1[0]==9&&iyear>14 )       	//���1 ֻ��ʾ����λ����ʼֵΪ2008
			{
				iyear=iyear-1;
			}
				
			
			if (BUFFER1[0]==10&&imonth>1)        //�¼�1,��ʼֵΪ1����СΪ1��ͬʱ��Ҫ�޸Ķ�Ӧ��������������ĳЩ�·ݳ��ֲ����е�����
			{
				imonth=imonth-1;
				
				if(imonth==4||imonth==6||imonth==9||imonth==11) 
				{
					if (iday>30 )					//С������30,��ʱ����������30�죬�ָ���30��
					iday=30;
				}
				if(imonth==2)
				{
					if(iyear%4==0)                  //��ʾ���꣬2������29,��ʱ����������29�죬�ָ���29��
					{
						if (iday>29 )
						iday=29;
					}
					else							//�����꣬2������28,��ʱ����������28�죬�ָ���28��
					{
						if (iday>28 )
						iday=28; 
					}
				}
			}
			
			if (BUFFER1[0]==11&&iday >1)       	//�ռ�1,��ʼֵΪ1����СΪ1
			{
				iday=iday-1;
			}
				
			
			if (BUFFER1[0]==12&&ihour>0)       	//ʱ��1,��ʼֵΪ0����СΪ0
			{
				ihour=ihour-1;
			}
				
			
			if (BUFFER1[0]==13&&iminute>0)      //�ּ�1,��ʼֵΪ0����СΪ0
			{
				iminute=iminute-1;
			}
			
				
			if (BUFFER1[0]==14)
			{
				sign=(sign+1)%2;  				//sign=1������sign=0��
			}
			
			if(BUFFER1[0]==15&&number>0)	number=number-1;	//����ʱ�����������		
		}
	
		if(sign==0) CW_PR3(LANGUAGE?15:14,LANGUAGE?24:20,'-'); 	//��ʾʱ���������
		if(sign==1) CW_PR3(LANGUAGE?15:14,LANGUAGE?24:20,'+');
		
		DISASCII(LANGUAGE?16:15,LANGUAGE?24:20,number);			//��ʾʱ�����ֵ
		
		DISASCII(LANGUAGE?17:18,LANGUAGE?19:15,iyear);			//��ʾ����ʱ�����ֵ
		DISASCII(LANGUAGE?20:21,LANGUAGE?19:15,imonth);
		DISASCII(LANGUAGE?23:24,LANGUAGE?19:15,iday);
		DISASCII(LANGUAGE?26:27,LANGUAGE?19:15,ihour);
		DISASCII(LANGUAGE?29:30,LANGUAGE?19:15,iminute);
	}
 }
 
//**********************************************************/
/*	���ܣ����Ұ������������Աȶȵ�ѡ�񣬱���ʱ��Ŀ���
��������������ʱ���������ƶ���������ѡ���ѡ��
��ڲ�������
���ڲ�������
/***********************************************************/ 
void Displaysetting_Leftright();
void Displaysetting_Leftright()
{
	byte i;
	if (G_Key==RIGHT||G_Key==LEFT)
    {
    
    	if(BUFFER1[0]==0||BUFFER1[0]==4)
    	{
	    	if (BUFFER1[0]==0&&G_Key==RIGHT)                //�Աȶ�ѡ��,������ǿ
			{   
			   	Contrast=(Contrast+1)%5;  
        Set_Contrast(Contrast);					
				Write_Char_Eprm(RX_CONTRAST,Contrast);			//Controst ��Ϣд��Eprom

			}  
		
		 	if (BUFFER1[0]==0&&G_Key==LEFT)                            
			{   
			   	Contrast=(Contrast+4)%5;   
        Set_Contrast(Contrast);					
				Write_Char_Eprm(RX_CONTRAST,Contrast);			//Controst ��Ϣд��Eprom
			
			}

	    	if (BUFFER1[0]==4&&G_Key==RIGHT)                //����ѡ��������ǿ
			{   
			   	Backlight=(Backlight+1)%5;   
         Set_Backlight(Backlight);					
				Write_Char_Eprm(RX_BACKLIGHT,Backlight);			//Backlight ��Ϣд��Eprom

			}  
		
		 	if (BUFFER1[0]==4&&G_Key==LEFT)                            
			{   
			   	Backlight=(Backlight+4)%5;    
         Set_Backlight(Backlight);							
				Write_Char_Eprm(RX_BACKLIGHT,Backlight);			//Backlight ��Ϣд��Eprom
			
			} 
				Displaysetting_Con_Back();   		
    	}

		
		if (BUFFER1[0]==3)                            	//����ʱ��
		{
			lcontrol=(lcontrol+1)%2;                	//�����ƶ�ת��״̬				
			Write_Char_Eprm(RX_TIME+2,lcontrol);		//lcontrol ��Ϣд��Eprom
		}
	
		for (i=0;i<=3;i++)                             	//�Է��������ѡ��
		{
			if(BUFFER1[0]==i+5)
			{
				Buzzer[i]=(Buzzer[i]+1)%2;	
			}
		}
		
		
		
		if(BUFFER1[0]>=9&&BUFFER1[0]<=13&&G_Key==RIGHT)
		{
			BUFFER1[0]=((BUFFER1[0]-9)+1)%5+9;
		}
		
		
		if(BUFFER1[0]>=9&&BUFFER1[0]<=13&&G_Key==LEFT)
		{
			BUFFER1[0]=((BUFFER1[0]-9)+4)%5+9;
		}
		
		
		if(BUFFER1[0]==14||BUFFER1[0]==15) BUFFER1[0]=(BUFFER1[0]-14+1)%2+14;
	
		G_Key=0;				//��������
		
		for(i=0;i<4;i++)		//����������ʾ
		{
			
			if(Buzzer[i]==0&&LANGUAGE==0)
			{
				CW_PR3(23,i+9,'F');
				CW_PR3(24,i+9,'F');
			}
			
			if(Buzzer[i]==0&&LANGUAGE==1)
			CCW_PR1(20,72+i*16,0xb9d8,1); 
		}
		
		
		for(i=0;i<4;i++)
		{
			if(Buzzer[i]==1&&LANGUAGE==0)
			{
				CW_PR3(23,i+9,'N');
				CW_PR3(24,i+9,' ');
			}
			
			if(Buzzer[i]==1&&LANGUAGE==1)
			CCW_PR1(20,72+i*16,0xBFAA,1); 
		}
		

		
				
		if(lcontrol==1)			//��ʾ����ʱ�� �Ŀ���
		{
			if(LANGUAGE==0) 
			{
				CW_PR3(14,18,'N');
				CW_PR3(15,18,' ');	
			}
			
			else CCW_PR1(15,168,0xbfaa,1);
		}
		
		if(lcontrol==0)			//��ʾ����ʱ�� �Ŀ���
		{
		
			if(LANGUAGE==0)
			{
				CW_PR3(14,18,'F');
				CW_PR3(15,18,'F');	
			}
			else CCW_PR1(15,168,0xb9d8,1);

		}
		
		
	 	if (BUFFER1[0]==9)		//����ʱ��ײ����ߵ���ת
	 	{
	 	
	 		//W_XLINE(LANGUAGE?120:104,LANGUAGE?151:135,LANGUAGE?160:128);
	 		//W_CLEARXLINE(LANGUAGE?160:144,LANGUAGE?175:159,LANGUAGE?160:128);
	 		//W_CLEARXLINE(LANGUAGE?232:216,LANGUAGE?247:231,LANGUAGE?160:128);	
	 		W_XLINE(LANGUAGE?120:128,LANGUAGE?151:159,LANGUAGE?160:128);
	 		W_CLEARXLINE(LANGUAGE?160:168,LANGUAGE?175:183,LANGUAGE?160:128);
	 		W_CLEARXLINE(LANGUAGE?232:240,LANGUAGE?247:255,LANGUAGE?160:128);			 		 	
	 	}
	 	
	 	if (BUFFER1[0]==10)	
	 	{
	 	
	 		W_XLINE(LANGUAGE?160:168,LANGUAGE?175:183,LANGUAGE?160:128);
	 		W_CLEARXLINE(LANGUAGE?120:128,LANGUAGE?151:159,LANGUAGE?160:128);
	 		W_CLEARXLINE(LANGUAGE?184:192,LANGUAGE?199:207,LANGUAGE?160:128);			 		 	
	 	}
	 	if (BUFFER1[0]==11)	
	 	{
	 	
	 		W_XLINE(LANGUAGE?184:192,LANGUAGE?199:207,LANGUAGE?160:128);
	 		W_CLEARXLINE(LANGUAGE?160:168,LANGUAGE?175:183,LANGUAGE?160:128);
	 		W_CLEARXLINE(LANGUAGE?208:216,LANGUAGE?223:231,LANGUAGE?160:128);			 		 	
	 	}
	 	
	 	if (BUFFER1[0]==12)	
	 	{
	 	
	 		W_XLINE(LANGUAGE?208:216,LANGUAGE?223:231,LANGUAGE?160:128);
	 		W_CLEARXLINE(LANGUAGE?184:192,LANGUAGE?199:207,LANGUAGE?160:128);
	 		W_CLEARXLINE(LANGUAGE?232:240,LANGUAGE?247:255,LANGUAGE?160:128);			 		 	
	 	}
	 	
	 	
	 	if (BUFFER1[0]==13)	
	 	{
	 	
	 		W_XLINE(LANGUAGE?232:240,LANGUAGE?247:255,LANGUAGE?160:128);
	 		W_CLEARXLINE(LANGUAGE?208:216,LANGUAGE?223:231,LANGUAGE?160:128);
	 		W_CLEARXLINE(LANGUAGE?120:128,LANGUAGE?151:159,LANGUAGE?160:128);			 		 	
	 	}
	 	
	 	//if (BUFFER1[0]==11||BUFFER1[0]==12)	
	 	//{
	 	//	int i;
	 	//	i=(BUFFER1[0]-11)*24;
	 //		W_XLINE(LANGUAGE?(184+i):(168+i),LANGUAGE?(199+i):(183+i),LANGUAGE?160:128);
	 //		W_CLEARXLINE(LANGUAGE?(160+i):(144+i),LANGUAGE?(175+i):(159+i),LANGUAGE?160:128);
	 //		W_CLEARXLINE(LANGUAGE?(208+i):(192+i),LANGUAGE?(223+i):(207+i),LANGUAGE?160:128);			 		 	
	 //	}
	 	
	 	
	 	if (BUFFER1[0]==14)		//ʱ��ײ�������ת
	 	{
	 	
	 		W_XLINE(LANGUAGE?120:112,LANGUAGE?127:119,LANGUAGE?200:168);
	 		W_CLEARXLINE(LANGUAGE?128:120,LANGUAGE?143:135,LANGUAGE?200:168);			 		 	
	 	}	    		
	 	if (BUFFER1[0]==15)	
	 	{
	 	
	 		W_CLEARXLINE(LANGUAGE?120:112,LANGUAGE?127:119,LANGUAGE?200:168);
	 		W_XLINE(LANGUAGE?128:120,LANGUAGE?143:135,LANGUAGE?200:168);			 		 	
	 	}
	 	
				
    }
    
 }
 
//**************************************************************/
/*	���ܣ�CLR�������������˳����˵������TOD���ã�����ʱ������
�����������˳�������ѡ��
��ڲ�������
���ڲ�������
/***************************************************************/
 
void Displaysetting_Return();
void Displaysetting_Return()
{
	if (G_Key==CLR&&BUFFER1[0]>=5&&BUFFER1[0]<=8)                        //�ӷ�����ѡ��� 
	{						
		G_Key=0;					//��������		
		W_DIAMOND(3,LANGUAGE?60:8);	//ѡ����˳�������ѡ��   
		W_HDIAMOND(6,LANGUAGE?(76+(BUFFER1[0]-5)*16):(BUFFER1[0]+4));
		BUFFER1[0]=1;				//�޸�BUFFER1[0]Ϊ1
		Eprom_Buzzer_Save();		//���޸���ϵķ������ô���Eprom
	}

	else if (G_Key==CLR&&BUFFER1[0]<5) 	//�ӵ�ǰ�˵��˳�  
	{
		G_Key=0;					//��������
		BUFFER1[0]=0;               //���˵�ʹ��ȫ�ֱ�������		
		FLAG=0;						//����ѭ��
		STATE=4;					//MianMenu�����״̬4
		State4parameter=0;			//��ڲ���Ϊ0
	}

 	/* TOD���ã�λ��ת�ƺ�ת�� */
	else if (G_Key==CLR&&BUFFER1[0]>=9&&BUFFER1[0]<=13)                  		//�ڹ���ʱ��λ���°���clr����
	{
		G_Key=0;					//��������
		W_CLEARXLINE(LANGUAGE?120:128,LANGUAGE?247:255,LANGUAGE?160:128);	//����»���
		W_DIAMOND(3,LANGUAGE?148:15);		
		
//		TODCS=TODCS&0xfffe;	            			//TODEN=0,�ر�TODģ��
//		TODDAY=DatesToDays(iyear,imonth,iday);
		

//		TODHR=ihour;		//��Сʱ����TODHR	
//		TODMIN=iminute;		//�ѷ�������TODMIN
//		TODCS|=0x0001;		//����ʱ�� 
		RTC_TimeRegulate(iyear,imonth,iday,ihour,iminute);
//		ReadTime();
		timestruct=GetTime();	
		SaveTime();
//		ReadTime();
//  	TIM3->CR1 |= 0x01;   //����ʱ��
		BUFFER1[0]=2;       //BUFFER1[0]=2��ʾ���ر���ʱ��
	}
						 
	/*����ʱ������*/
	else if (G_Key==CLR&&BUFFER1[0]>=14&&BUFFER1[0]<=15)
	{
		G_Key=0;			//��������	
		BUFFER1[0]=3;		//����������ʱ��ѡ���
		W_CLEARXLINE(LANGUAGE?120:112,LANGUAGE?143:135,LANGUAGE?200:168);
		W_DIAMOND(3,LANGUAGE?172:18);
		Write_Char_Eprm(RX_TIME,number);//number ��Ϣд��Eprom
		Write_Char_Eprm(RX_TIME+1,sign);//sign ��Ϣд��Eprom
	}
}
 
 
 
 
//**************************************************************/
/*	���ܣ�ENT��������������ѡ�������ѡ������
��ڲ�������
���ڲ�������
/***************************************************************/
 void Displaysetting_Dealing();
 void Displaysetting_Dealing()
 {
	 if(G_Key==ENT&&STATE==42)
	 {
	 	G_Key=0;
	 	if (BUFFER1[0]==1)	 	
	 	{
	 		BUFFER1[0]=5;                  	//�ڷ���ʱ����ENTʱ�ɶ���������ѡ��	
	 		W_HDIAMOND(3,LANGUAGE?60:8);	   
			W_DIAMOND(6,LANGUAGE?76:9); 
	 	}
	 
	 	if (BUFFER1[0]==2)					//�������ʱ������
	 	{
	 		BUFFER1[0]=9;
	 		//W_XLINE(LANGUAGE?120:104,LANGUAGE?151:135,LANGUAGE?160:128);
	 		W_XLINE(LANGUAGE?120:128,LANGUAGE?151:159,LANGUAGE?160:128);
	 		W_HDIAMOND(3,LANGUAGE?148:15);	 		 	
	 	}
	    
	 	if (BUFFER1[0]==3)					//���뱾��ʱ���ʱ������
	 	{
	 		BUFFER1[0]=14;
	 		W_XLINE(LANGUAGE?120:112,LANGUAGE?127:119,LANGUAGE?200:168);
	 		W_HDIAMOND(3,LANGUAGE?172:18);	 		 	
	 	}	      
	 }
 }

//**************************************************/
/*	���ܣ����ջ���ʾ���ò˵��������Աȶ����ã��������ã�����ʱ���Լ�����ʱ������
          BUFFER1[0] ��¼ѡ����
          iyear,imonth,iday,ihour,iminute������ǰʱ��ļ��أ�������ʾ��ǰʱ��
          ͬʱ�����޸Ĺ���ʱ��Ҳ��ͨ���޸����ϵı�����Ȼ������ֵ����ʼ��TOD
          

��ڲ�������
���ڲ�������
/***************************************************/ 
void RunDisplaySetting()
{
  maske=0;
  maskc=0;
	timestruct=GetTime();
  TIM3_IRQHandler();   		//�ѵ�ǰ��ʱ����ؽ���iyear,imonth,iday,ihour,iminute	
	BUFFER1[0]=0;
	
	Displaysetting_Paintintial();
	while(FLAG)                         
	{
//        COPCTR=0xAAAA;
//        COPCTR=0x5555;
		Displaysetting_Updn();
		Displaysetting_Leftright();	
		Displaysetting_Return();		
		Displaysetting_Dealing();
		run_tip();		
	}
}