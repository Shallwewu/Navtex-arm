#include <stdio.h>
#include <stdlib.h>
#include  "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "code.h"



/********************************************************/
/*���ܣ���������ƶ���Ǻ����½���Ϣ����ʾ��
��ڲ�������
���ڲ�������
/********************************************************/   
void LockMenu_biaoji2();
void LockMenu_biaoji2()
{
	if(Mulnownumber>0) W_DOWNMOVE(39,29);
	else W_CLEARUPDN(39,29);
	
	if(Mulnownumber<(Messagenumber-1)) W_UPMOVE(39,1);
	else W_CLEARUPDN(39,1);
	DISASCIII(16,29,Messagenumber);
	DISASCIII(12,29,Messagenumber-Mulnownumber);
		
}



/********************************************************/
/*���ܣ������ϢժҪ����ʾ
��ڲ�������
���ڲ�������
/********************************************************/
void LockMenu_Paint2();
void LockMenu_Paint2()
{	
	char i,j;
	j=0;
	for(i=BUFFERSELECT[21];(i>=0&&(BUFFERSELECT[21]-i)<6);i--)
	{	
		W_MSGTOP(i,5+4*j,1);
		j++;	
	}
	if(j<6)
	{
		for (j;j<6;j++)
		W_CLEARMSGTOP(5+4*j);		
	}
	
}

/********************************************************/
/*���ܣ���ɸ�ѡ��ǵ���ʾ
��ڲ�������
���ڲ�������
/********************************************************/
void Fuxuanbiaoji2();
void Fuxuanbiaoji2()
{
	if(Messagesavetop[Msglockrank[Mulnownumber]].select==1) W_CHOOSED(1,(BUFFERSELECT[21]-Mulnownumber)*4+7);	//��ѡѡ����
	else  W_CANCALCHOOSED(1,(BUFFERSELECT[21]-Mulnownumber)*4+7);									//�����ѡ���
}


/********************************************************/
/*���ܣ�������ѡ���ӡ��ѡ����ʾ
��ڲ�������
���ڲ�������
/********************************************************/
void LockLockSubMenu_Paintintial();
void LockLockSubMenu_Paintintial()
{

	byte i;
	if(Selectsubback==10) 
	RecoverData();	//���Ӳ˵����أ�ֻ��ָ������ǵ�����
	else 
	{

		if(LANGUAGE==0)
		{

		     /* д���ͷ��һ������MULTI_UNLOCK */
			CTAB[2]='M';	CTAB[3]='U';	CTAB[4]='L';	CTAB[5]='T';	CTAB[6]='I';	 CTAB[7]='-';
			CTAB[8]='U';	CTAB[9]='N';	CTAB[10]='L';	CTAB[11]='O';	CTAB[12]='C';	 CTAB[13]='K';
			CW_PR(0,1,14);
	
		     /* д���ͷ�ڶ�������ID FREQ LINES DATE TIME  */
			CTAB[4]='I';	 CTAB[5]='D';	 CTAB[10]='F';	 CTAB[11]='R';	  CTAB[12]='E'; CTAB[13]='Q';
		    CTAB[16]='L';   CTAB[17]='I';  CTAB[18]='N';  CTAB[19]='E';   CTAB[20]='S';
		    CTAB[23]='D';   CTAB[24]='A';  CTAB[25]='T';  CTAB[26]='E';   CTAB[31]='T'; 
		    CTAB[32]='I';   CTAB[33]='M';  CTAB[34]='E';     
			CW_PR(0,3,35);
		}
		
		else
		{

		    CLEARXLINE(0,39,3);		//������ʾ����
			CLEARXLINE(0,39,4);
			CLEARXLINE(0,39,5);
			CLEARXLINE(0,39,22);	
			XLINE(0,39,19);

			
	 		CCW_PR1(1,3,0xd0c5,1);		//��ͷ����"��Ϣ����"
	 		CCW_PR1(3,3,0xcfa2,1);
	 		CCW_PR1(5,3,0xbde2,1);
	 		CCW_PR1(7,3,0xcbf8,1);
	 		
	 		
	  		CW_PR3(4,3,'I');CW_PR3(5,3,'D');	//��־������"Ƶ�� ���� ���� ʱ��"
	 		CCW_PR1(10,20,0xc6b5,1);
	 		CCW_PR1(12,20,0xc2ca,1);
	 		CCW_PR1(16,20,0xd0d0,1);
	 		CCW_PR1(18,20,0xcafd,1);
	 	 	CCW_PR1(23,20,0xcab1,1);
	 		CCW_PR1(25,20,0xbce4,1);
	 	 	CCW_PR1(31,20,0xc5c5,1);
	 		CCW_PR1(33,20,0xd0f2,1);					
		}		

	     /* д������ */
 		CTAB[1]='M';	CTAB[2]='S';	CTAB[3]='G';	CTAB[5]='A';	CTAB[6]='M';
		CTAB[7]='O';	CTAB[8]='U';	CTAB[9]='N';	CTAB[10]='T';	CTAB[11]=':';
		CTAB[15]='/';
		CW_PR(0,29,16); //����ַ�����ʾ
		

		XLINE(0,37,36);			//�����ͼ����ʾ��һ����ϢժҪռ��3��
		W_XLINE(304,309,36);
		XLINE(0,37,37);
		W_XLINE(304,309,37);
		XLINE(0,37,68);
		W_XLINE(304,309,68);
		XLINE(0,37,69);
		W_XLINE(304,309,69);
		XLINE(0,37,100);		
		W_XLINE(304,309,100);
		XLINE(0,37,196);
		W_XLINE(304,309,196);
		XLINE(0,37,197);
		W_XLINE(304,309,197);
		
		XLINE(0,39,229);
		CLEARXLINE(0,39,230);
		
		W_YLINE(0,0,239);
		W_YLINE(309,0,239);
		W_YLINE(319,0,239);			//���ͼ������ʾ
		

		
   		W_BLOCK(39,5);				//�ܽ��뱾�˵����ش�����Ϣ
   		BUFFERSELECT[21]=Messagenumber-1;//��ʼ������BUFFERSELECT[21]��ֵΪ���һ����Ϣ�ı��
   		Mulnownumber=Messagenumber-1;
		LockMenu_Paint2();					//��ϢժҪ����ʾ
		LockMenu_biaoji2();					//��������ƶ���Ǻ����½���Ϣ����ʾ��

	}
	
	XLINE(0,37,101);
	W_XLINE(304,309,101);
	XLINE(0,37,132);
	W_XLINE(304,309,132);
	XLINE(0,37,133);
	W_XLINE(304,309,133);
	XLINE(0,37,164);
	W_XLINE(304,309,164);
	XLINE(0,37,165);		
	W_XLINE(304,309,165);

	W_Mode(35,3,32,1);	//�ֶ����Զ�ģʽ����ʾ
	Selectsubback=0;	//�ж�ʹ����ϣ�����	
	
}


/********************************************************/
/*���ܣ�UP��DOWN������������ʵ����Ϣ�������ƶ�ѡ�����ܣ�
		Mulnownumberָ��ǰ��ѡ������Ϣ
��ڲ�������
���ڲ�������
/********************************************************/
void LockLockSubMenu_Updn();
void LockLockSubMenu_Updn()
{

		if(BUFFERSELECT[21]>=0&&BUFFERSELECT[21]<Messagenumber)
		{
			if(G_Key == DOWN&&Mulnownumber>0)
			{	
				if((Mulnownumber+5)>BUFFERSELECT[21])	//��ʱ��ѡ��������Ϣ��LCD��ʾ����
				{
					Mulnownumber--;			//��ǰ��ѡ��Ϣ��1
					W_BLOCK(39,((BUFFERSELECT[21]-Mulnownumber)%6)*4+5);//��Ӧ������޸ģ��������ڱ�ǵ�ǰ��ѡ��Ϣ
					W_CLEARBLOCK(39,((BUFFERSELECT[21]-Mulnownumber)%6)*4+1);
				}
				
				else if((Mulnownumber+5)==BUFFERSELECT[21])	//��ʱ��ѡ��������Ϣ����LCD��ʾ����
				{
					Mulnownumber--;		//��ǰ��ѡ��Ϣ��1
					BUFFERSELECT[21]--;	//ҳ��������ϢҲ���1
					LockMenu_Paint2();	//LCD��������ʾ�����µ���ϢҪ��ʾ
				}
				LockMenu_biaoji2();		//��������ƶ���Ǻ����½���Ϣ����ʾ��
				G_Key=0;				
			}
				
	
			else if(G_Key == UP&&((Mulnownumber+1)<Messagenumber))
			{	

				
				if(Mulnownumber==BUFFERSELECT[21])
				{
					Mulnownumber++;		//��ǰ��ѡ��Ϣ��1	
					BUFFERSELECT[21]++;	//ҳ��������ϢҲ���1
					LockMenu_Paint2();	//LCD��������ʾ�����µ���ϢҪ��ʾ
				}
				
				else if(Mulnownumber<BUFFERSELECT[21])
				{
					Mulnownumber++;	//��ǰ��ѡ��Ϣ��1
					W_BLOCK(39,((BUFFERSELECT[21]-Mulnownumber)%6)*4+5);//��Ӧ������޸ģ��������ڱ�ǵ�ǰ��ѡ��Ϣ
					W_CLEARBLOCK(39,((BUFFERSELECT[21]-Mulnownumber)%6)*4+9);
				}
				LockMenu_biaoji2();	//��������ƶ���Ǻ����½���Ϣ����ʾ��
				G_Key=0;				
			}
			
		}
}

		

/********************************************************/
/*���ܣ�LEFT��RIGHT������������ʵ����Ϣ�����·�ҳ���ܣ�
		���·�ҳָ����ҳ����л���
		Mulnownumberָ��ǰ��ѡ������Ϣ
��ڲ�������
���ڲ�������
/********************************************************/
void LockLockSubMenu_Leftright();
void LockLockSubMenu_Leftright()
{
	if(BUFFERSELECT[21]>=0&&BUFFERSELECT[21]<Messagenumber)
	{	
		if(G_Key == RIGHT&&Mulnownumber>=Maxpagenum)	//���·�ҳ��Mulnownumber�����ж�
														//Mulnownumber��ֵ�������ҳ����Ϣ����ɷ�ҳ
		{

			Mulnownumber=Mulnownumber-Maxpagenum;//��ǰ��ѡ��Ϣ��ת	
			BUFFERSELECT[21]=BUFFERSELECT[21]-Maxpagenum;			

			LockMenu_Paint2();	//��ϢժҪ����ʾ
			LockMenu_biaoji2();	//��������ƶ���Ǻ����½���Ϣ����ʾ��
			G_Key=0;			
		}
		else if(G_Key == LEFT&&(BUFFERSELECT[21]+Maxpagenum<Messagenumber))	//���Ϸ�ҳ��BUFFER[0]�����ж�
																					//BUFFER[0]��ֵ��ȥ���ҳ����Ϣ��С������Ϣ����ɷ�ҳ
		{
			Mulnownumber=Mulnownumber+Maxpagenum;
			BUFFERSELECT[21]=BUFFERSELECT[21]+Maxpagenum;
			LockMenu_Paint2();	//��ϢժҪ����ʾ
			LockMenu_biaoji2();	//��������ƶ���Ǻ����½���Ϣ����ʾ��
			G_Key=0;				
		}
	}

}


/*****************************************/
/*���ܣ����˵����˳���������ѡ�˵���һ��������
        ��ӡ��ѡ��3���������м伶�˵�ʹ�õ�
        ��ȫ�ֱ�������ȫ������
��ڲ�������
���ڲ�������
/****************************************/
void LockLockSubMenu_Return();
void LockLockSubMenu_Return()
{
	if(G_Key == CLR&&STATE==300)//��Ϊ������ѡ
	{
		sword i=0;

		BUFFERSELECT[21]=0;

		for(i=0;i<Messagenumber;i++)	//��ѡ���λȫ������
		Messagesavetop[Msglockrank[i]].select=0;
		BUFFER1[0]=0;			//Խһ�������м��ȫ�ֱ�������
		FLAG=0;					//����ѭ��
		STATE=2;				//����������ֲ˵����ض���SaveMenu��״̬Ϊ2
		State2parameter=2;		//��ڲ���Ϊ2��������ѡ���淵�������˵�
		G_Key=0;
	}

}


/*****************************************/
/*���ܣ���ѡ��ѡ��
��ڲ�������
���ڲ�������
/****************************************/
void LockLockSubMenu_Dealing();
void LockLockSubMenu_Dealing()
{
	if(G_Key == ENT)
	{
		Messagesavetop[Msglockrank[Mulnownumber]].select=(Messagesavetop[Msglockrank[Mulnownumber]].select+1)%2;
		Fuxuanbiaoji2();	//��ѡ�������ʾ	
		G_Key=0;		//��������
	}
}


/*****************************************/
/*���ܣ�������ѡ���Ӳ˵�
��ڲ�������
���ڲ�������
/****************************************/
void LockLockSubMenu_Star();
void LockLockSubMenu_Star()
{
	if(G_Key == STAR&&STATE==300)
	{

//		ProtectData();			//�������������渲�ǵ�����
		FLAG=0;					//����ѭ��
		STATE=2000;				//SaveLockSubSure��״̬Ϊ2000
		State2000parameter=1;	//��ڲ���1����Ϊ������ѡ���Ӳ˵�
		G_Key=0;				//��������
	}

}


/*********************************************************/
/*	���ܣ�������ѡ�˵������ڽ��ж�����Ϣ�Ľ���
		  ��Ϣ����ѡ��������Ϣͷ�ļ����е�selectλ���ж�
          ���˵��õ���ȫ�ֱ�����
		  BUFFERSELECT[21] ҳ��������ʾ��Ϣ���
		  Mulnumber��Ϊ��ѡ����ĵ�ǰ������Ϣ����
		  Selectsubback���ڽ��븴ѡ����Ľ����������
��ڲ�����into  ��¼�Ӻβ˵�����
���ڲ�������
/*********************************************************/
void RunLockLockSubMenu(unsigned char into)
{
    maske=0;
    maskc=0;
	Selectsubback=into;
	LockLockSubMenu_Paintintial();
	
	while(FLAG)
	{
		LockLockSubMenu_Updn();
		LockLockSubMenu_Leftright();
		LockLockSubMenu_Dealing();
		LockLockSubMenu_Star();
		LockLockSubMenu_Return();
		run_tip();
	}
}