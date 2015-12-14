#include <stdio.h>
#include <stdlib.h>
#include  "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "Eprom.h"
#include "code.h"

//***************************************************/
/*	���ܣ�ѡ��ģʽ����ʾ�������ƶ���BUFFER1[1]��ģʽ 
��ڲ�������
���ڲ�������
/****************************************************/
void Rxstation_Paint_Mode();
void Rxstation_Paint_Mode()
{
    if (BUFFER1[1] == 0) 	//ѡ���Զ�ģʽ
    {

    	if(LANGUAGE == 0)	//Ӣ�Ĳ˵���ʾ��AUTO
    	{
    		CW_PR3(13,4,'A');
        	CW_PR3(14,4,'U');
        	CW_PR3(15,4,'T');
        	CW_PR3(16,4,'O');
        	CW_PR3(17,4,' ');
        	CW_PR3(18,4,' '); 
    	}
    	
    	else 				//���Ĳ˵���ʾ���Զ�
    	{
    		CCW_PR1(16,64,0xd7d4,1);
			CCW_PR1(18,64,0xb6Af,1);	
    	}
    }           

    if (BUFFER1[1] == 1) 	//ѡ���ֶ�ģʽ
    {
  
		if(LANGUAGE == 0)	//Ӣ�Ĳ˵���ʾ��MANUAL
		{
			CW_PR3(13,4,'M');
        	CW_PR3(14,4,'A');
        	CW_PR3(15,4,'N');
        	CW_PR3(16,4,'U');
        	CW_PR3(17,4,'A');
        	CW_PR3(18,4,'L');	
		}
    	else				//���Ĳ˵���ʾ���ֶ�
    	{
    		CCW_PR1(16,64,0xcad6,1);
			CCW_PR1(18,64,0xb6Af,1);		        		
    	}	        		
    } 	
}
 
 //*****************************************************/
/*	���ܣ�ѡ������Ƶ��ѡ�����ʾ��BUFFER1[2]������Ƶ��
��ڲ�������
���ڲ�������
/*******************************************************/
void Rxstation_Paint_Workfrq();
void Rxstation_Paint_Workfrq()
{
/*	if(BUFFER1[2] == 0)/* ѡ��518��490��4209.5����Ƶ�� 
	{
		if(LANGUAGE == 0)	//Ӣ�Ĳ˵�
		{
			CTAB[5] = 'O';	CTAB[6] = 'P';	CTAB[7] = 'E';	CTAB[8] = 'R';	CTAB[9] = 'A';	CTAB[10] = 'T';
			CTAB[11] = 'I';	CTAB[12] = 'N';	CTAB[13] = 'G';	CTAB[15] = 'F';	CTAB[16] = 'R';	CTAB[17] = 'E';
			CTAB[18] = 'Q';	CTAB[19] = ':';
			CTAB[20] = '5';	CTAB[21] = '1';	CTAB[22] = '8';	CTAB[23] = '/';
			CTAB[24] = '4';	CTAB[25] = '9';	CTAB[26] = '0';	CTAB[27] = '/';	CTAB[28] = '4';	CTAB[29] = '2';
			CTAB[30] = '0';	CTAB[31] = '9';	CTAB[32] = '.';	CTAB[33] = '5';
			CW_PR(0,8,34);
		}

		else
		{
			CCW_PR1(20,88,0x19a0,0);
			CCW_PR1(22,88,0x1940,0);
			CCW_PR1(24,88,0x19c0,0);
		}

	}*/


	if(BUFFER1[2] == 0)/* ѡ��518��4209.5����Ƶ�� */
	{
		if(LANGUAGE == 0)
		{
			CTAB[0] = '5';	CTAB[1] = '1';	CTAB[2] = '8';	CTAB[3] = '/';
			CTAB[4] = '4';	CTAB[5] = '2';	CTAB[6] = '0';	CTAB[7] = '9';	CTAB[8] = '.';	CTAB[9] = '5';	
			CW_PR(20,8,10);
		}
		
		else
		{
	 		CCW_PR1(26,88,0x19a0,0);
	  		CCW_PR1(28,88,0x1960,0);
	  		CCW_PR1(30,88,0x1a80,0); 
		}

	}	    


	if(BUFFER1[2] == 1)/* ѡ��518��486����Ƶ�� */
	{
		if(LANGUAGE == 0)
		{				
			CTAB[0] = '5';	CTAB[1] = '1';	CTAB[2] = '8';	CTAB[3] = '/';
			CTAB[4] = '4';	CTAB[5] = '8';	CTAB[6] = '6';	
			CW_PR(20,8,10);
		}
		
		else
		{
	 		CCW_PR1(26,88,0x1a60,0);
	  		CCW_PR1(28,88,0x1a20,0);
			CCW_PR1(30,88,0x1760,0);
		}

	} 	
}
 
//********************************************/
/*	���ܣ����ķ���̨Rxstation�������ʾ����
��ڲ�������
���ڲ�������
/*********************************************/
 void Rxstation_Paintintial();
 void Rxstation_Paintintial()
 {
	char i;
//	CLEAR1();			//��һ���Ͷ����Ĵ洢�ռ�,�Լ��߽���趨
	if(LANGUAGE == 0)	//Ӣ�Ĳ�������	
	{
		/* ��ͷ:RX STATION */
		CTAB[1] = 'R';	CTAB[2] = 'X';	CTAB[4] = 'S';	CTAB[5] = 'T';	CTAB[6] = 'A';
		CTAB[7] = 'T';	CTAB[8] = 'I';	CTAB[9] = 'O';	CTAB[10] = 'N';
		CW_PR(0,1,11);
		
		/*����Ƶ��:OPERATING FREQ: */
		CTAB[5] = 'O';		CTAB[6] = 'P';	    CTAB[7] = 'E';  	CTAB[8] = 'R';	    CTAB[9] = 'A';	    CTAB[10] = 'T';
		CTAB[11] = 'I';		CTAB[12] = 'N';		CTAB[13] = 'G';		CTAB[15] = 'F';		CTAB[16] = 'R';		CTAB[17] = 'E';
		CTAB[18] = 'Q';		CTAB[19] = ':';
		CW_PR(0,8,20);
		
		/*ģʽѡ��:RX MODE */
		CTAB[5] = 'R';		CTAB[6] = 'X';	CTAB[8] = 'M';	CTAB[9] = 'O';	CTAB[10] = 'D';
		CTAB[11] = 'E';		CTAB[12] = ':';		 
		CW_PR(0,4,13);

		/*�Զ�ģʽ����:AUTO MODE SETTING */
		CTAB[5] = 'A';		CTAB[6] = 'U';		CTAB[7] = 'T';	    CTAB[8] = 'O';		CTAB[10] = 'M';
		CTAB[11] = 'O';		CTAB[12] = 'D';		CTAB[13] = 'E';		CTAB[15] = 'S';		CTAB[16] = 'E';
		CTAB[17] = 'T';		CTAB[18] = 'T';		CTAB[19] = 'I';		CTAB[20] = 'N';		CTAB[21] = 'G';
		CW_PR(0,12,22);

		/*�ֶ�ģʽ����:MANUAL MODE SETTING */
		CTAB[5] = 'M';		CTAB[6] = 'A';		CTAB[7] = 'N';		CTAB[8] = 'U';		CTAB[9] = 'A';		CTAB[10] = 'L';
		CTAB[12] = 'M';		CTAB[13] = 'O';		CTAB[14] = 'D';		CTAB[15] = 'E';		CTAB[17] = 'S';		CTAB[18] = 'E';
		CTAB[19] = 'T';		CTAB[20] = 'T';		CTAB[21] = 'I';		CTAB[22] = 'N';		CTAB[23] = 'G';
		CW_PR(0,16,24);	
	}

	else				//���Ľ���
 	{

		XLINE(0,39,25);
		CLEARXLINE(0,39,22);	
 	
 		CCW_PR1(1,7,0xb1a8,1);		//��һ������"���ķ���̨����"
 		CCW_PR1(3,7,0xcec4,1);
 		CCW_PR1(5,7,0xb7a2,1);
 		CCW_PR1(7,7,0xc9e4,1);
 		CCW_PR1(9,7,0xcca8,1);
 	 	CCW_PR1(11,7,0xc9e8,1);
 		CCW_PR1(13,7,0xd6c3,1);
 
  		
 		CCW_PR1(6,64,0xc4a3,1);		//�ڶ�������"ģʽѡ��:�Զ�"
 		CCW_PR1(8,64,0xcabd,1);
 		CCW_PR1(10,64,0xd1a1,1);
 		CCW_PR1(12,64,0xd4f1,1);
 		CCW_PR1(14,64,0x1aa0,0);

 		
 		CCW_PR1(6,88,0xb9a4,1);		//����������"����Ƶ��:518/4" ��ʼΪ��ͨ��
 		CCW_PR1(8,88,0xd7f7,1);
 	 	CCW_PR1(10,88,0xc6b5,1);
 		CCW_PR1(12,88,0xc2ca,1); 	
 		CCW_PR1(14,88,0x1aa0,0);
 		CCW_PR1(16,88,0x1a00,0);		
  		CCW_PR1(18,88,0x1980,0);		
  		CCW_PR1(20,88,0x1a60,0);
  		CCW_PR1(22,88,0x1940,0);
  		CCW_PR1(24,88,0x19e0,0); 		
  		 		
  				
 		CCW_PR1(6,112,0xd7d4,1);	//����������"�Զ�ģʽ����"
 		CCW_PR1(8,112,0xb6Af,1);
 		CCW_PR1(10,112,0xc4a3,1);
 		CCW_PR1(12,112,0xcabd,1);
 	 	CCW_PR1(14,112,0xc9e8,1);
 		CCW_PR1(16,112,0xd6c3,1); 	
 		
 		CCW_PR1(6,136,0xcad6,1);	//����������"�ֶ�ģʽ����"
 		CCW_PR1(8,136,0xb6Af,1);
 		CCW_PR1(10,136,0xc4a3,1);
 		CCW_PR1(12,136,0xcabd,1);
 	 	CCW_PR1(14,136,0xc9e8,1);
 		CCW_PR1(16,136,0xd6c3,1); 		
 	}

	
	for(i = 1;i <= 4;i++)			//ѡ�������ʾ
	{
		W_HDIAMOND(LANGUAGE?4:3,LANGUAGE?(44+24*i):(4*i));		
	}
	
	W_DIAMOND(LANGUAGE?4:3,LANGUAGE?68:4);	
	
	if(BUFFER1[0]!= 0)
	{
		W_DIAMOND(LANGUAGE?4:3,LANGUAGE?(68+BUFFER1[0]*24):(BUFFER1[0]*4+4));	
		W_HDIAMOND(LANGUAGE?4:3,LANGUAGE?68:4);	
	}
	
	Rxstation_Paint_Workfrq();		//����Ƶ��ѡ��
	Rxstation_Paint_Mode();			//ģʽѡ�� 
	
	W_YLINE(0,0,239);				//Y����������
	W_YLINE(319,0,239);	

}

//********************************************/
/*	���ܣ����°�����������ѡ������ѡ����
��ڲ�������
���ڲ�������
/*********************************************/
void Rxstation_Updn();
void Rxstation_Updn()
{
	if (G_Key == UP)	//������������
	{
		if(BUFFER1[0]>0)
		{
			BUFFER1[0] = BUFFER1[0]-1;	//BUFFER[0]���ڼ�¼��ѡ����ѡ��        
			G_Key = 0;
			W_DIAMOND(LANGUAGE?4:3,LANGUAGE?(68+BUFFER1[0]*24):(BUFFER1[0]*4+4));	
			W_HDIAMOND(LANGUAGE?4:3,LANGUAGE?(92+BUFFER1[0]*24):(BUFFER1[0]*4+8));			
		}
	}

	if (G_Key == DOWN)	//������������
	{
		if(BUFFER1[0]<3)
		{
			BUFFER1[0] = BUFFER1[0]+1;       
			G_Key = 0;
			W_DIAMOND(LANGUAGE?4:3,LANGUAGE?(68+BUFFER1[0]*24):(BUFFER1[0]*4+4));	
			W_HDIAMOND(LANGUAGE?4:3,LANGUAGE?(44+BUFFER1[0]*24):(BUFFER1[0]*4));
	   	}
	}	
}
//****************************************************/
/*	���ܣ����Ұ���������������ģʽѡ��͹���Ƶ��ѡ��
��ڲ�������
���ڲ�������
/*****************************************************/
void Rxstation_Leftright();
void Rxstation_Leftright()                
{
	if (G_Key == RIGHT||G_Key == LEFT)
	{
		

		if (BUFFER1[0] == 0)                         //ģʽѡ��
		{   
			BUFFER1[1] = (BUFFER1[1]+1)%2;          //BUFFER1[1]��¼ѡ����ģʽ
			Rxstation_Paint_Mode();					//��ѡ��ģʽ��ʾ
			Mode = BUFFER1[1];						//ѡ��ģʽ����RAM��Mode��			
			Write_Char_Eprm(RX_MODE,Mode);			//����Mode��Eprom
		}  
		
		else if (BUFFER1[0] == 1)                        //Ƶ��ѡ��
		{   

			BUFFER1[2] = (BUFFER1[2]+1)%2; 	    	//BUFFER1[2]��¼ѡ���Ĺ���Ƶ��
	    	Workfre = BUFFER1[2];					//ѡ������Ƶ�ʴ���RAM��Workfre��
	    	Rxstation_Paint_Workfrq();				//��ʾ��ѡ������Ƶ��
	    	Write_Char_Eprm(RX_WORKFRE,Workfre);	//����Workfre��Eprom
		}
		G_Key = 0;									//��������
	}

}

//************************************************/
/*	���ܣ�CLR���������������ص��ϼ��˵�MainMenu
��ڲ�������
���ڲ�������
/*************************************************/ 
void Rxstation_Return();
void Rxstation_Return()
{
	if (G_Key == CLR)     	//���ص�MainMenu�˵�  	
	{
		G_Key = 0;			//����������		
		BUFFER1[0] = 0;		//���˵��õ���3��ȫ�ֱ�������
		BUFFER1[1] = 0;
		BUFFER1[2] = 0;
		FLAG = 0;			//����ѭ��
		STATE = 4;			//MainMenu״̬Ϊ4
		State4parameter = 0;//����0���Ӳ˵�����
	}
}


//************************************************/
/*	���ܣ�ENT�����������������Զ�ģʽ���û���
          �ֶ�ģʽ���ý���
��ڲ�������
���ڲ�������
/*************************************************/  
void Rxstation_Dealing();
void Rxstation_Dealing()
{
	if(G_Key == ENT&&STATE==40)	 
	{
		G_Key = 0;					//��������
		if (BUFFER1[0] == 2)        //�Զ�ģʽ�˵�Automodeѡ��
		{   
			FLAG = 0;				//����ѭ��
			STATE = 400;			//Automode״̬Ϊ400
			State400parameter = 0;  //��ڲ���Ϊ0      			
		}
		
		if (BUFFER1[0] == 3)        //�ֶ�ģʽ�˵�Manualmodeѡ��
		{   
			FLAG = 0;				//����ѭ��
			STATE = 401;			//Manualmode״̬Ϊ401
			State401parameter = 0; 	//��ڲ���Ϊ0    		          			
		}
	}
}

//**************************************************/
/*	���ܣ����ķ���̨���ò˵�������ģʽѡ��͹���Ƶ��
          ѡ���Լ��Զ�ģʽ�˵����ֶ�ģʽ�˵����룬
          ���˵��õ���ȫ�ֱ���������
          BUFFER1[0] ��¼ѡ����
          BUFFER1[1] ��¼����ģʽ
          BUFFER1[2] ��¼����Ƶ��
��ڲ�������
���ڲ�������
/***************************************************/  
void RunRxstation()
{
    maske=0;
    maskc=0;
	BUFFER1[1] = Mode;
	BUFFER1[2] = Workfre;

	Rxstation_Paintintial();
	while(FLAG)
	{		
		Rxstation_Updn();
		Rxstation_Leftright();		
		Rxstation_Return();		
		Rxstation_Dealing();
		run_tip();
	}    	
}
	
