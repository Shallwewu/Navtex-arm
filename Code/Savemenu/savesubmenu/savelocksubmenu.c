#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "code.h"
/********************************************************/
/*���ܣ���������ƶ���Ǻ����½���Ϣ����ʾ��
��ڲ�������
���ڲ�������
/********************************************************/ 
void SaveMenu_biaoji1();
void SaveMenu_biaoji1()
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
void SaveMenu_Paint1();
void SaveMenu_Paint1()
{	
	sword i,j;
	j=0;
	for(i=BUFFERSELECT[21];(i>=0&&(BUFFERSELECT[21]-i)<6);i--)
	{	
		W_MSGTOP(i,5+4*j,0);
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
void Fuxuanbiaoji();
void Fuxuanbiaoji()
{
	if(Messagesavetop[Messagetoprank[Mulnownumber]].select==1) W_CHOOSED(1,(BUFFERSELECT[21]-Mulnownumber)*4+7);	//��ѡѡ����
	else  W_CANCALCHOOSED(1,(BUFFERSELECT[21]-Mulnownumber)*4+7);									//�����ѡ���
}

/********************************************************/
/*���ܣ�������ѡ���ӡ��ѡ����ʾ
��ڲ�������
���ڲ�������
/********************************************************/
void SaveLockSubMenu_Paintintial();
void SaveLockSubMenu_Paintintial()
{
	byte i;
	if(Selectsubback==10) RecoverData();	//���Ӳ˵����أ�ֻ��ָ������ǵ�����
	else 
	{
		if(LANGUAGE==0)
		{
		     /* д���ͷ��һ������ */
			CTAB[2]='M';	CTAB[3]='U';	CTAB[4]='L';	CTAB[5]='T';	CTAB[6]='I';	 CTAB[7]='-';
			CTAB[8]='C';	CTAB[9]='H';	CTAB[10]='O';	CTAB[11]='O';	CTAB[12]='S';	 CTAB[13]='E';
			CW_PR(0,1,14);

		     /* д���ͷ�ڶ������� */
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
			
	 		CCW_PR1(1,3,0xb8b4,1);	//��ѡ�˵�
	 		CCW_PR1(3,3,0xd1a1,1);
	 		CCW_PR1(5,3,0xb2cb,1);
	 		CCW_PR1(7,3,0xb5a5,1);
	 		
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
		CW_PR(0,29,16); 			//����Ϣ�����͵�ǰ��Ϣ������ʾ


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
//   		BUFFERSELECT[21]=Messageinfo.savenumber[0]-1;//��ʼ������BUFFERSELECT[21]��ֵΪ���һ����Ϣ�ı��
//   		Mulnownumber=Messageinfo.savenumber[0]-1;
  		BUFFERSELECT[21]=Messagenumber-1;//��ʼ������BUFFERSELECT[21]��ֵΪ���һ����Ϣ�ı��
  		Mulnownumber=Messagenumber-1;

		SaveMenu_Paint1();					//��ϢժҪ����ʾ
		SaveMenu_biaoji1();					//��������ƶ���Ǻ����½���Ϣ����ʾ��

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
void SaveLockSubMenu_Updn();
void SaveLockSubMenu_Updn()
{
	if(BUFFERSELECT[21]>=0&&BUFFERSELECT[21]<Messagenumber)
	{
		if(G_Key == DOWN&&Mulnownumber>0)
		{	
	
			if((Mulnownumber+5)==BUFFERSELECT[21])	//��ʱ��ѡ��������Ϣ����LCD��ʾ����
			{
				Mulnownumber--;		//��ǰ��ѡ��Ϣ��1	
				BUFFERSELECT[21]--;	//ҳ��������ϢҲ���1
				SaveMenu_Paint1();	//LCD��������ʾ�����µ���ϢҪ��ʾ
			}
			
			else if(Mulnownumber+5>BUFFERSELECT[21])
			{
				Mulnownumber--;		//��ǰ��ѡ��Ϣ��1
				W_BLOCK(39,((BUFFERSELECT[21]-Mulnownumber)%6)*4+5);//��Ӧ������޸ģ��������ڱ�ǵ�ǰ��ѡ��Ϣ
				W_CLEARBLOCK(39,((BUFFERSELECT[21]-Mulnownumber)%6)*4+1);
			}
			SaveMenu_biaoji1();		//��������ƶ���Ǻ����½���Ϣ����ʾ��
			G_Key=0;
		}
			
		
		else if(G_Key == UP&&((Mulnownumber+1)<Messagenumber))
		{	

			
			if(Mulnownumber==BUFFERSELECT[21])
			{
				Mulnownumber++;		//��ǰ��ѡ��Ϣ��1	
				BUFFERSELECT[21]++;	//ҳ��������ϢҲ���1
				SaveMenu_Paint1();	//LCD��������ʾ�����µ���ϢҪ��ʾ
			}
			
			else if(Mulnownumber<BUFFERSELECT[21])
			{
				Mulnownumber++;		//��ǰ��ѡ��Ϣ��1
				W_BLOCK(39,((BUFFERSELECT[21]-Mulnownumber)%6)*4+5);//��Ӧ������޸ģ��������ڱ�ǵ�ǰ��ѡ��Ϣ
				W_CLEARBLOCK(39,((BUFFERSELECT[21]-Mulnownumber)%6)*4+9);
			}
			SaveMenu_biaoji1();		//��������ƶ���Ǻ����½���Ϣ����ʾ��
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
void SaveLockSubMenu_Leftright();
void SaveLockSubMenu_Leftright()
{
	if(BUFFERSELECT[21]>=0&&BUFFERSELECT[21]<Messagenumber)
	{	
		if(G_Key == RIGHT&&Mulnownumber>=Maxpagenum)	//���·�ҳ��Mulnownumber�����ж�
														//Mulnownumber��ֵ�������ҳ����Ϣ����ɷ�ҳ
		{
			Mulnownumber=Mulnownumber-Maxpagenum;
			BUFFERSELECT[21]=BUFFERSELECT[21]-Maxpagenum;//��ǰ��ѡ��Ϣ��ת			
			SaveMenu_Paint1();					//��ϢժҪ����ʾ
			SaveMenu_biaoji1();					//��������ƶ���Ǻ����½���Ϣ����ʾ��			
			G_Key=0;
		}
		else if(G_Key == LEFT&&((BUFFERSELECT[21]+Maxpagenum)<Messagenumber))
																	//���Ϸ�ҳ��BUFFER[0]�����ж�
		{															//BUFFER[0]��ֵ��ȥ���ҳ����Ϣ��С������Ϣ����ɷ�ҳ			Mulnownumber=Mulnownumber+Maxpagenum;
			Mulnownumber=Mulnownumber+Maxpagenum;
			BUFFERSELECT[21]=BUFFERSELECT[21]+Maxpagenum;
			SaveMenu_Paint1();					//��ϢժҪ����ʾ
			SaveMenu_biaoji1();					//��������ƶ���Ǻ����½���Ϣ����ʾ��				
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
void SaveLockSubMenu_Return();
void SaveLockSubMenu_Return()
{
	if(G_Key == CLR&&STATE==200)//��Ϊ������ѡ
	{
		sword i=0;

		BUFFERSELECT[21]=0;		//���˵�ʹ�õ�ȫ�ֱ�������
		BUFFERSELECT[1]=0;
		BUFFERSELECT[2]=0;
		BUFFERSELECT[3]=0;
		BUFFERSELECT[0]=0;
		for(i=0;i<Messagenumber;i++)	//��ѡ���λȫ������
		Messagesavetop[Messagetoprank[i]].select=0;

		BUFFER1[0]=0;			//Խһ�������м��ȫ�ֱ�������
		FLAG=0;					//����ѭ��
		STATE=2;				//����������ֲ˵����ض���SaveMenu��״̬Ϊ2
		State2parameter=1;		//��ڲ���Ϊ1
		if(Selectreturn==1)	  	//��ʱ��������Ϊ��ӡ��ѡ�˵���Խ�����������м�ʹ�õ�ȫ�ֱ�������	                               
		{
			BUFFER2[0]=0;
			BUFFER3[0]=0;
		}	
		G_Key=0;				//��������
	}
}



/*****************************************/
/*���ܣ���ѡ��ѡ��������������ѡ�˵���ֻ��
        δ��������Ϣ�ܹ����ϸ�ѡ���
        ���ڴ�ӡ��ѡ����������
��ڲ�������
���ڲ�������
/****************************************/
void SaveLockSubMenu_Dealing();
void SaveLockSubMenu_Dealing()  //ֻ��δ��������Ϣ�ܹ����ϸ�ѡ���
{
	char i;
	if(G_Key == ENT&&Messagesavetop[Messagetoprank[Mulnownumber]].lock==0&&Selectreturn==0)//��Ϊ������ѡ
	{
        
        Messagesavetop[Messagetoprank[Mulnownumber]].select=(Messagesavetop[Messagetoprank[Mulnownumber]].select+1)%2;
        i=Messagesavetop[Messagetoprank[Mulnownumber]].frequency;
        if(Messagesavetop[Messagetoprank[Mulnownumber]].select==1)
					{
						BUFFERSELECT[i]++;	//ѡ�������£�ͨ����Ϣ������1
						BUFFERSELECT[0]++;				//������������1
					}
		if(BUFFERSELECT[i]<=Maxlocknum)Fuxuanbiaoji();
		else 
		{
		    Messagesavetop[Messagetoprank[Mulnownumber]].select=(Messagesavetop[Messagetoprank[Mulnownumber]].select+1)%2;
			BUFFERSELECT[i]--;	//���ѡ����ͨ����Ϣ������1
			BUFFERSELECT[0]--;
			FLAG=0;					//����ѭ��
			State14parameter=1;		//��ڲ���1��������������ѡ����	
			ProtectData();
			CLEAR2();			
			STATE=14;				//Message_OverCapacity��״̬14
		
		}
/*		switch(Messagesavetop[Messagetoprank[Mulnownumber]].frequency)
		{
			case 1:   //����518ͨ��
			{

				if(BUFFERSELECT[1]<=Maxlocknum)	//ͨ��1����������δ��
				{
				//	Messagesavetop[Messagetoprank[Mulnownumber]].select=(Messagesavetop[Messagetoprank[Mulnownumber]].select+1)%2;
					if(Messagesavetop[Messagetoprank[Mulnownumber]].select==1)
					{
						BUFFERSELECT[1]++;	//ѡ�������£�ͨ����Ϣ������1
						BUFFERSELECT[0]++;				//������������1
					}
					
					else
					{
						BUFFERSELECT[1]--;	//���ѡ����ͨ����Ϣ������1
						BUFFERSELECT[0]--;				//����Ϣ������1						
					}
					Fuxuanbiaoji();			//��ʾ��ѡ���
				}
				else
				{
				    
					FLAG=0;					//����ѭ��
					STATE=14;				//Message_OverCapacity��״̬14
					State14parameter=1;		//��ڲ���1��������������ѡ����				
				}
				break;
			}
			case 2:  //����490ͨ����ͬ��
			{
				if(BUFFERSELECT[2]<=Maxlocknum)
				{
				
				
			//		Messagesavetop[Messagetoprank[Mulnownumber]].select=(Messagesavetop[Messagetoprank[Mulnownumber]].select+1)%2;
					if(Messagesavetop[Messagetoprank[Mulnownumber]].select==1)
					{
						BUFFERSELECT[2]++;
						BUFFERSELECT[0]++;
					}
					else
					{
						BUFFERSELECT[2]--;
						BUFFERSELECT[0]--;						
					}
				    Fuxuanbiaoji();					
				}
				else
				{
		
					FLAG=0;
					STATE=14;
					State14parameter=1;	
				}
				break;
				
			}
			default:	//����4209.5ͨ����ͬ��
			{
				if(BUFFERSELECT[3]<=Maxlocknum)
				{
			//		Messagesavetop[Messagetoprank[Mulnownumber]].select=(Messagesavetop[Messagetoprank[Mulnownumber]].select+1)%2;
					if(Messagesavetop[Messagetoprank[Mulnownumber]].select==1)
					{
						BUFFERSELECT[3]++;
						BUFFERSELECT[0]++;
					}
					
					else
					{
						BUFFERSELECT[3]--;
						BUFFERSELECT[0]--;						
					}
					Fuxuanbiaoji();					
				}
				else
				{
				//	ProtectData();
					FLAG=0;
					STATE=14;
					State14parameter=1;	
				}
				
			}

		}*/
		G_Key=0;	
	}
	
	if(G_Key == ENT&&Selectreturn==1)	//��ӡ��ѡ
	{
		Messagesavetop[Messagetoprank[Mulnownumber]].select=(Messagesavetop[Messagetoprank[Mulnownumber]].select+1)%2;
		Fuxuanbiaoji();	//��ѡ�������ʾ
		G_Key=0;		//��������
	}
	
	
}

/*****************************************/
/*���ܣ�������ѡ�ʹ�ӡ��ѡ���Ӳ˵�
��ڲ�������
���ڲ�������
/****************************************/
void SaveLockSubMenu_Star();
void SaveLockSubMenu_Star()
{
	if(G_Key == STAR&&Selectreturn==0&&STATE==200)	//��ת��������ѡ���Ӳ˵�SaveLockSubSure
	{
		FLAG=0;					//����ѭ��
		STATE=2000;				//SaveLockSubSure��״̬Ϊ2000
		State2000parameter=0;	//��ڲ���0����Ϊ������ѡ���Ӳ˵�
		G_Key=0;				//��������
	}
	
	else if(G_Key == STAR&&Selectreturn==1&&STATE==200)	//��ת����ӡ��ѡ���Ӳ˵�Message_PrintSubmenu
	{
		G_Key=0;				//��������
		FLAG=0;					//����ѭ��
		STATE=13;				//Message_PrintSubmenu��״̬Ϊ13
		State13parameter=3;		//��ڲ���Ϊ3���ɴ�ӡ�˹���ѡ����ѡ����Ϣ����
	}	
}


/*********************************************************/
/*	���ܣ�������ѡ�ʹ�ӡ��ѡ���ã����ڽ��ж�����Ϣ�Ĵ�ӡ������
		  ��Ϣ����ѡ��������Ϣͷ�ļ����е�selectλ���ж�
          ���˵��õ���ȫ�ֱ�����
		  BUFFERSELECT[21] ҳ��������ʾ��Ϣ���
		  BUFFERSELECT[1] 518khz��ʱͨ����������
		  BUFFERSELECT[2] 490khz��ʱͨ���������� 
		  BUFFERSELECT[3] 4209.5khz��ʱͨ����������
		  BUFFERSELECT[0] ��ͨ����ʱ�ܵ�������Ϣ��
		  Mulnumber��Ϊ��ѡ����ĵ�ǰ������Ϣ����
		  Selectreturn���ڸ�ѡ����ĳ��ڲ�������
		  Selectsubback���ڽ��븴ѡ����Ľ����������
��ڲ�����into  ��¼�Ӻβ˵�����
���ڲ�������
/*********************************************************/
void RunSaveLockSubMenu(unsigned char into)//������ѡ����ʹ�ӡ��ѡ����Ĺ���
{
    maske=0;
    maskc=0;
	Selectsubback=into;
	if(into!=10)
	{
		BUFFERSELECT[0]=Messageinfo.locknumber[0];//��ʼ��BUFFERSELECT[0]Ϊ�㣬���ڼ�¼������Ϣ����
		Selectreturn=into;
		BUFFERSELECT[1]=Messageinfo.locknumber[1];
		BUFFERSELECT[2]=Messageinfo.locknumber[2];
		BUFFERSELECT[3]=Messageinfo.locknumber[3];	
	}

	SaveLockSubMenu_Paintintial();
	
	while(FLAG)
	{
		SaveLockSubMenu_Updn();
		SaveLockSubMenu_Leftright();
		SaveLockSubMenu_Dealing();
		SaveLockSubMenu_Star();
		SaveLockSubMenu_Return();
		run_tip();

	}
  	
}