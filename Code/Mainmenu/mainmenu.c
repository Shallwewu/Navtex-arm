#include <stdio.h>
#include <stdlib.h>
#include "define.h"	
#include "run.h"
#include "lcddrive.h"
#include "code.h"

//********************************************/
/*���ܣ����˵�MainMenu����ʾ����
��ڲ�������
���ڲ�������
/*********************************************/
void Mainmenu_Paintintial();
void Mainmenu_Paintintial()
{
	unsigned char i;
	CLEAR1();

	if(LANGUAGE == 0)	//Ӣ�Ľ���
	{
	    /* ��ͷ��MAINMENU */
		CTAB[1] = 'M';		CTAB[2] = 'A';		CTAB[3] = 'I';		CTAB[4] = 'N';	
		CTAB[5] = 'M';		CTAB[6] = 'E';		CTAB[7] = 'N';		CTAB[8] = 'U';
		CW_PR(0,1,9);	
		

		/* д���һ������:RX STATION */
		CTAB[5] = 'R';		CTAB[6] = 'X';		CTAB[8] = 'S';		CTAB[9] = 'T';	
		CTAB[10] = 'A';		CTAB[11] = 'T';		CTAB[12] = 'I';	CTAB[13] = 'O';	
		CTAB[14] = 'N';  
		CW_PR(0,4,15);


		/* д��ڶ�������:MESSAGE TYPE */
		CTAB[5] = 'M';		CTAB[6] = 'E';		CTAB[7] = 'S';		CTAB[8] = 'S';
		CTAB[9] = 'A';		CTAB[10] = 'G';		CTAB[11] = 'E';	CTAB[13] = 'T';
		CTAB[14] = 'Y';		CTAB[15] = 'P';		CTAB[16] = 'E';
		CW_PR(0,7,17);  


		/* д�����������:DISPLAY */
		CTAB[5] = 'D';		CTAB[6] = 'I';		CTAB[7] = 'S';		CTAB[8] = 'P';
		CTAB[9] = 'L';		CTAB[10] = 'A';		CTAB[11] = 'Y';
		CW_PR(0,10,12);


		/* д�����������:NAVTEX */
		CTAB[5] = 'N';		CTAB[6] = 'A';		CTAB[7] = 'V';		CTAB[8] = 'T';
		CTAB[9] = 'E';		CTAB[10] = 'X';
		CW_PR(0,13,11);


		/* д�����������:MAINTENANCE */
		CTAB[5] = 'M';		CTAB[6] = 'A';		CTAB[7] = 'I';		CTAB[8] = 'N';
		CTAB[9] = 'T';		CTAB[10] = 'E';		CTAB[11] = 'N';  	CTAB[12] = 'A';
		CTAB[13] = 'N';		CTAB[14] = 'C';		CTAB[15] = 'E';
		CW_PR(0,16,16);


		/* д�����������:LANGUAGE */
		CTAB[5] = 'L';		CTAB[6] = 'A';		CTAB[7] = 'N';		CTAB[8] = 'G';	
		CTAB[9] = 'U';		CTAB[10] = 'A';		CTAB[11] = 'G';		CTAB[12] = 'E';
		CW_PR(0,19,13);	
	}
 	
 	else		//���Ľ���
 	{
 		W_XLINE(0,319,25);	
		W_CLEARXLINE(0,319,22);
  	
 		CCW_PR1(1,7,0xb9a6,1);		//��ͷ"���ܲ˵�"
 		CCW_PR1(3,7,0xc4dc,1);
 		CCW_PR1(5,7,0xb2cb,1);
 		CCW_PR1(7,7,0xb5a5,1);
 		
 		CCW_PR1(6,40,0xb1a8,1);		//�ڶ�������"���ķ���̨����"
 		CCW_PR1(8,40,0xcec4,1);
 		CCW_PR1(10,40,0xb7a2,1);
 		CCW_PR1(12,40,0xc9e4,1);
 		CCW_PR1(14,40,0xcca8,1);
 	 	CCW_PR1(16,40,0xc9e8,1);
 		CCW_PR1(18,40,0xd6c3,1);
 		
  		
 		CCW_PR1(6,64,0xd0c5,1);		//����������"��Ϣ�������"
 		CCW_PR1(8,64,0xcfa2,1);
 		CCW_PR1(10,64,0xc0e0,1);
 		CCW_PR1(12,64,0xb1f0,1);
 	 	CCW_PR1(14,64,0xc9e8,1);
 		CCW_PR1(16,64,0xd6c3,1);
 		
 		CCW_PR1(6,88,0xcfd4,1);		//����������"��ʾ����"
 		CCW_PR1(8,88,0xcabe,1);
 	 	CCW_PR1(10,88,0xc9e8,1);
 		CCW_PR1(12,88,0xd6c3,1); 	
 		
 		CCW_PR1(6,112,0xbdd3,1);	//����������"���ջ�����"
 		CCW_PR1(8,112,0xcad5,1);
 		CCW_PR1(10,112,0xbbfa,1);
 	 	CCW_PR1(12,112,0xc9e8,1);
 		CCW_PR1(14,112,0xd6c3,1); 	
 		
 		CCW_PR1(6,136,0xceac,1);	//����������"ά��"
 		CCW_PR1(8,136,0xbba4,1);
 		
  		CCW_PR1(6,160,0xd3ef,1);	//����������"����ѡ��"
 		CCW_PR1(8,160,0xd1D4,1);
 	 	CCW_PR1(10,160,0xd1a1,1);
 		CCW_PR1(12,160,0xd4f1,1); 		 
 	}


	W_YLINE(0,0,239);
	W_YLINE(319,0,239);	

	W_DIAMOND(LANGUAGE?4:3,LANGUAGE?44:4);	//����ʱѡ���λ�ں��ֵ��м�

	for(i = 0;i<5;i++)						//ѡ�������ʾ
	{
		W_HDIAMOND(LANGUAGE?4:3,LANGUAGE?(68+24*i):(7+3*i));		
	}
		
	if(BUFFER[0] != 0)
	{
		W_DIAMOND(LANGUAGE?4:3,LANGUAGE?(44+24*BUFFER[0]):(4+BUFFER[0]*3));	
		W_HDIAMOND(LANGUAGE?4:3,LANGUAGE?44:4);
	}
	
	W_Mode(35,7,32,1);	//�ֶ����Զ�ģʽ����ʾ

}
//********************************************/
/*���ܣ����°�����������ѡ������ѡ����
��ڲ�������
���ڲ�������
/*********************************************/
void Mainmenu_Updn();
void Mainmenu_Updn()
{
                     
	if (G_Key == UP)		
	{	
		G_Key = 0;
		if(BUFFER[0]>0)		//������������
		{
			BUFFER[0] = BUFFER[0]-1;        		
			W_DIAMOND(LANGUAGE?4:3,LANGUAGE?(44+24*BUFFER[0]):(4+BUFFER[0]*3));	
			W_HDIAMOND(LANGUAGE?4:3,LANGUAGE?(68+24*BUFFER[0]):(7+BUFFER[0]*3));

		}
	}
	
	if (G_Key == DOWN)
	{
        G_Key = 0;
		if(	BUFFER[0] <5)	//������������
		{			
			BUFFER[0] = BUFFER[0]+1;       
			W_DIAMOND(LANGUAGE?4:3,LANGUAGE?(44+24*BUFFER[0]):(4+BUFFER[0]*3));	
			W_HDIAMOND(LANGUAGE?4:3,LANGUAGE?(20+24*BUFFER[0]):(1+BUFFER[0]*3));	
		}
	}	
}

//****************************************************/
/*���ܣ�CLR��DISP������������ʵ�ֶ����˵�����ת
��ڲ�������
���ڲ�������
/*****************************************************/
void Mainmenu_Menuchange() ;
void Mainmenu_Menuchange()             
{
	if(G_Key == DISP)   	//�л�����Ϣ����
	{
		BUFFER[0] = 0;		//������ʹ��ȫ�ֱ�������
		G_Key = 0;			//��������
		FLAG = 0;			//����ѭ��
		STATE = 1;			//Message����״̬Ϊ1
		State1parameter = 0;//��ڲ���Ϊ0
		backpage = 0;		//ȫ�ֱ�������	
	}
	
	else if (G_Key == CLR)     	//���ص�ԭ������  ��Leftright,ȫ��Menuchange��
	{
		G_Key = 0;			//��������
		BUFFER[0] = 0;		//������ʹ��ȫ�ֱ�������
		FLAG = 0;			//��������
		if(backpage == 0)   	//������Ϣ���Ĳ˵�Message         
		{
			STATE = 1;			//Message״̬Ϊ1
			State1parameter = 0;//��ڲ���0	
		}
		if(backpage == 1)   	//���ش洢�˵�SaveMenu           
		{
			STATE = 2;			//Savemenu״̬Ϊ2
			State2parameter = 0;//��ڲ���Ϊ0			

		}
		if(backpage == 2)    	//���������˵�SaveMenu
		{
			STATE = 2;			//Savemenu״̬Ϊ2
			State2parameter = 5;//��ڲ���Ϊ2���������������˵��ʹ洢�˵�	
		}
		if(backpage == 3)    	//����ʱ��˵�TimeLocation         
		{
			STATE = 5;			//TimeLocation����״̬Ϊ5
		}
		backpage = 0;			//ȫ�ֱ�������
	}
}

//**************************************************************/
/*	���ܣ�ENT����������������ѡ������ѡ�����Ӳ˵�
��ڲ�������
���ڲ�������
/***************************************************************/
void Mainmenu_Dealing();
void Mainmenu_Dealing()             
{                                   
    if (G_Key == ENT&&STATE==4)
	{   
		G_Key = 0;				//��������
	 	FLAG = 0;				//����������ѭ��
		if(BUFFER[0] == 0)		//����Rxstation menu��״̬40 
		{
			STATE = 40;		
		}
		
        if(BUFFER[0] == 1)		//����Messagetype menu��״̬41		
        {
      		STATE = 41;
      		State41parameter = 0; 	
        } 
		
        if(BUFFER[0] == 2)     	//����DisplaySetting menu��״̬42 
        {
			STATE = 42;
        }			  
		
        if(BUFFER[0] == 3)		//����ReceiveSetting menu��״̬43 
        {
        	STATE = 43;		
        }
		
        if(BUFFER[0]  ==  4)	//����Maintain menu	��״̬44	
        {
			STATE = 44;
			State44parameter=0;	//��ڲ���0 		
        }
		
        if(BUFFER[0]  ==  5)    //����LanguageSetting menu��״̬45		
        {
			STATE = 45;
        }
	}
}
		
//**************************************************************/
/*	���ܣ����˵����������ڽ������˵��ĸ��Ӳ˵�
��ڲ�����byte into:��¼�Ӻβ˵����룬��ȫ�ֱ���backpage�洢��
          ��������ͬBUFFER[0],���˵������Ӳ˵�
���ڲ�������
/***************************************************************/
void RunMainMenu(byte into)
{
    maske=0;
    maskc=0;
	backpage = into;  //��¼�Ӻν�����룬����Mainmenu���淵��ȷ��                        
	Mainmenu_Paintintial();
	while(FLAG)
	{
		Mainmenu_Updn();
		Mainmenu_Menuchange();
		Mainmenu_Dealing();
		run_tip();
	}
  	
}