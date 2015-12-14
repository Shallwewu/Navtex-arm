#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"	
#include "Eprom.h"
#include "code.h"
#include "MessageDeal.h"

//***************************************/
  /*���ܣ�Messagetoprank[]�Ļ���
��ڲ��������軥����Ϣ�ĵ�ַ
���ڲ�������
/****************************************/
//void Msgtoprankchange(int num1,int num2); 							 
#define Msgtoprankchange(num1,num2) {   \
	sword temp;                           \
	temp=Messagetoprank[num1];          \
	Messagetoprank[num1]=Messagetoprank[num2];  \
	Messagetoprank[num2]=temp; }





//*****************************************/
  /*���ܣ���580khzͨ������ ��3 2 1��ʾ����
��ڲ�����mode��1��ʾ�洢�б�0��ʾ�����б�
���ڲ�������
/******************************************/
void Rankfrequency1();
void Rankfrequency1()
{
	sword j=0,i=0;
	for(j=0;j<Messageinfo.savenumber[0]-1;j++)
	{
		for (i=0;i<(Messageinfo.savenumber[0]-1-j);i++)
		{
			if(Messagesavetop[Messagetoprank[i]].frequency<Messagesavetop[Messagetoprank[i+1]].frequency)	
			{
				Msgtoprankchange(i,i+1);
			}
		}
	}
		
}

//*****************************************/
  /*���ܣ���4209.5khzͨ������ ��1 2 3��ʾ����
��ڲ�����mode��1��ʾ�洢�б�0��ʾ�����б�
���ڲ�������
/******************************************/
void Rankfrequency3();
void Rankfrequency3()	
{
	sword j=0,i=0;
	for(j=0;j<Messageinfo.savenumber[0]-1;j++)
	{
		for (i=0;i<(Messageinfo.savenumber[0]-1-j);i++)
		{
			if(Messagesavetop[Messagetoprank[i]].frequency>Messagesavetop[Messagetoprank[i+1]].frequency)	
			{
				Msgtoprankchange(i,i+1);
			}
		}
	}
		
}

//*****************************************/
  /*���ܣ���490khzͨ������,��1 3 2��ʾ����
��ڲ�����mode��1��ʾ�洢�б�0��ʾ�����б�
���ڲ�������
/******************************************/
void Rankfrequency2();
void Rankfrequency2()	
{
	sword j=0,i=0,t;

	for(j=0;j<Messageinfo.savenumber[0]-1;j++)	//��ʱ�Ѱ�1 2 3˳������
	{
		for (i=0;i<(Messageinfo.savenumber[0]-1-j);i++)
		{
			if(Messagesavetop[Messagetoprank[i]].frequency>Messagesavetop[Messagetoprank[i+1]].frequency)	
			{
				Msgtoprankchange(i,i+1);
			}
		}
	}
	
	for(i=0;i<Messageinfo.savenumber[0];i++)
	{
		if(Messagesavetop[Messagetoprank[i]].frequency==2)	//�õ���һ��ָ��ͨ��2��Messagtoprank[]λ��	
		{
			t=i;
			break;
		}
	}

	
	if(t<(Messageinfo.savenumber[0]-1))
	{
			for(j=t;j<(Messageinfo.savenumber[0]-1);j++)
		
			for (i=t;i<(Messageinfo.savenumber[0]-1-j+t);i++)
			{
				if(Messagesavetop[Messagetoprank[i]].frequency<Messagesavetop[Messagetoprank[i+1]].frequency)	
				{
					Msgtoprankchange(i,i+1);
				}
			}
	}
		
}

//*****************************************/
  /*���ܣ�����̨����
��ڲ�����mode��1��ʾ�洢�б�0��ʾ�����б�
���ڲ�������
/******************************************/
void Rankrxstaion();
void Rankrxstaion()	
{
	sword j=0,i=0;
	for(j=0;j<Messageinfo.savenumber[0]-1;j++)
	{
		for (i=0;i<(Messageinfo.savenumber[0]-1-j);i++)
		{
			if(Messagesavetop[Messagetoprank[i]].mark[0]<Messagesavetop[Messagetoprank[i+1]].mark[0])	
			{
				Msgtoprankchange(i,i+1);
			}
		}
	}
}


//*****************************************/
  /*���ܣ���������Ϣ���ں������У��Ӵ�С
��ڲ�����mode��1��ʾ�洢�б�0��ʾ�����б�
���ڲ�������
/******************************************/
void Rankarea();
void Rankarea()
{
	sword j=0,i=0;
	for(j=0;j<Messageinfo.savenumber[0]-1;j++)
	{
		for (i=0;i<(Messageinfo.savenumber[0]-1-j);i++)
		{
			if(Messagesavetop[Messagetoprank[i]].area<Messagesavetop[Messagetoprank[i+1]].area)	
			{
				Msgtoprankchange(i,i+1);
			}
		}
	}
}

//*****************************************/
  /*���ܣ�����Ϣ������У��Ӵ�С
��ڲ�����mode��1��ʾ�洢�б�0��ʾ�����б�
���ڲ�������
/******************************************/
void Rankmessagetype();
void Rankmessagetype()	
{
	sword j=0,i=0;
	for(j=0;j<Messageinfo.savenumber[0]-1;j++)
	{
		for (i=0;i<(Messageinfo.savenumber[0]-1-j);i++)
		{
			if(Messagesavetop[Messagetoprank[i]].mark[1]<Messagesavetop[Messagetoprank[i+1]].mark[1])	
			{
				Msgtoprankchange(i,i+1);
			}
		}
	}		
}

//*****************************************/
  /*���ܣ���δ����Ϣ���У��Ӵ�С
��ڲ�����mode��1��ʾ�洢�б�0��ʾ�����б�
���ڲ�������
/******************************************/
void Ranklockread();
void Ranklockread()	
{
	sword j=0,i=0;
	for(j=0;j<Messageinfo.savenumber[0]-1;j++)
	{
		for (i=0;i<(Messageinfo.savenumber[0]-1-j);i++)
		{
			if(Messagesavetop[Messagetoprank[i]].read<Messagesavetop[Messagetoprank[i+1]].read)	
			{
				Msgtoprankchange(i,i+1);
			}
		}
	}
	
}


//*****************************************/
  /*���ܣ���ʱ������(ð�ݷ�)
��ڲ�����mode��1��ʾ�洢�б�0��ʾ�����б�
���ڲ�������
/******************************************/
void Ranktime();
void Ranktime()
{
	sword j=0,i=0;

	for(j=0;j<Messageinfo.savenumber[0]-1;j++)
	{
		for (i=0;i<(Messageinfo.savenumber[0]-1-j);i++)
		{

		 if(Messagesavetop[Messagetoprank[i]].date[0]>Messagesavetop[Messagetoprank[i+1]].date[0])
			{
				Msgtoprankchange(i,i+1); 
			}
			else if(Messagesavetop[Messagetoprank[i]].date[0]==Messagesavetop[Messagetoprank[i+1]].date[0])
			{
				if(Messagesavetop[Messagetoprank[i]].date[1]>Messagesavetop[Messagetoprank[i+1]].date[1])
				{
					Msgtoprankchange(i,i+1);
					
				}
				
				else if(Messagesavetop[Messagetoprank[i]].date[1]==Messagesavetop[Messagetoprank[i+1]].date[1])
				{
					if(Messagesavetop[Messagetoprank[i]].date[2]>Messagesavetop[Messagetoprank[i+1]].date[2])
					{
						Msgtoprankchange(i,i+1);
						
					}
					
					else if(Messagesavetop[Messagetoprank[i]].date[2]==Messagesavetop[Messagetoprank[i+1]].date[2])
					{
						if(Messagesavetop[Messagetoprank[i]].time[0]>Messagesavetop[Messagetoprank[i+1]].time[0])
						{
							Msgtoprankchange(i,i+1);
					
						}
						
						else if(Messagesavetop[Messagetoprank[i]].time[0]==Messagesavetop[Messagetoprank[i+1]].time[0])
						{
							if(Messagesavetop[Messagetoprank[i]].time[1]>Messagesavetop[Messagetoprank[i+1]].time[1])
							{
								Msgtoprankchange(i,i+1);
						
							}		
						}
					}
				}
			}
		}
//        COPCTR=0xAAAA;
//        COPCTR=0x5555;		
	}
}

/*******************************************************************/
  /*���ܣ����Ƶ�ʣ����ͶԴ洢��Ϣ��������Ϣ��������
��ڲ�����frequency char��:0������Ƶ�ʣ�1��ͨ��1��2��ͨ��2��3��ͨ��3
		  type char��: ������0��ʾʱ�䣬1��ʾ����̨��2��ʾ��Ϣ���
					   3��ʾδ����Ϣ,4��ʾ���о�����
		  ���ڲ�������
/*******************************************************************/
void Rankfuction(char frequency,char type);
void Rankfuction(char frequency,char type)
{
//	MessageProcess|=0x01;		//��ʱ�ڽ�����Ϣ�������
	DISABLEIRQA();		
	Messageinfo.rankmode=BUFFER2[0];	//�ѵ�ǰ������״̬д����Ϣ��¼�ṹ��
	Write_Char_Eprm(MESSAGEINFO+20,Messageinfo.rankmode);//����Ϣ��¼�ṹ��д��Eprom
	
	Ranktime();						//����ʱ������
	if(type==1) Rankrxstaion();		//����̨����
	if(type==2) Rankmessagetype();     //��Ϣ�������
	if(type==3) Ranklockread();        //δ����Ϣ����
	if(type==4) Rankarea();            //���о���ȥ����
	if(frequency==1) Rankfrequency1(); //ͨ��1 518
	if(frequency==2) Rankfrequency2(); //ͨ��2 490
	if(frequency==3) Rankfrequency3();	//ͨ��3 4029.5
//	MessageProcess&=0xfe;		//��Ϣ���������ϣ�bit1λ��0
	ENABLEIRQA();	
}


