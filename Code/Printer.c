#include <stdio.h>
#include <stdlib.h>
#include "printer.h"
#include "flash.h"
#include "run.h"
#include "code.h"
#include "stm32f2xx.h"
#include "usart.h"
//int TEMP[1600];
/*
volatile PrtLink *PrtStart;
volatile int print_list[600];
volatile int print_sum;
*/
//*******************************************/
/*���ܣ�SCI0�����ʵ�����
��ڲ��������������ò���
/********************************************/
void BadurateSet(char badurate);
void BadurateSet(char badurate)
{

	if(badurate==3)
	{
	USART_BaudRate(USART3,4800*3);		//������Ϊ4800bps	
	}
	else if(badurate==2)
	{
	USART_BaudRate(USART3,9600*3);			//������Ϊ9600bps	
	}		
	else if(badurate==1)
	{
	USART_BaudRate(USART3,19200*3);   	//������Ϊ19200bps
	}
}


//*******************************************/
/*���ܣ�SCI0�ĳ�ʼ�����ã�������Ϊ4800bps��8���أ�����żУ��λ
��ڲ�������
���ڲ�������
/********************************************/
void IntialRS232();
void IntialRS232()
{
  USART3_Init();
  USART2_Init();
	BadurateSet(Receiverset[3]+1);					//������Ϊ4800bps 
}


//*******************************************/
/*���ܣ���������
��ڲ�������
���ڲ�������
/********************************************/
void StartRS232(USART_TypeDef* USARTx)
{
	 USART_Cmd(USARTx,ENABLE);
}


//*******************************************/
/*���ܣ��رմ��ͺʹ����ж�
��ڲ�������
���ڲ�������
/********************************************/
void CloseRS232(USART_TypeDef* USARTx)
{
    USART_Cmd(USARTx,DISABLE);
		Checkinfo.Printover = 1;
}

//*******************************************/
/*���ܣ����ݴ���
��ڲ�������
���ڲ�������
/********************************************/
void DataTran(USART_TypeDef* USARTx)
{
//	#pragma interrupt saveall
    static int i=0;
//	PrtLink *p=PrtStart->next;
//	SCI_0_SR&=~SCI_0_SR_TDRE_MASK;		//TEλ��0��transmitter��Ч	
//	SCI_0_DR='a';
 //   if((++i)>100)
//    {
//	    COPCTR=0xAAAA;
//	    COPCTR=0x5555;
//	    i=0;	
//    }
	if(PrtStart->nowprint==PrtStart->end)				//����ǰ��Ϣ��ӡ���
	{
/*		
		free(p->start);					//��������ٵ��ڴ��
		PrtStart->next=p->next;			//��ָ��ָ��p֮��Ľڵ�
		free(p);						//�ͷŽڵ�
		PrtStart->xulie--;				//��ӡ����Ϣ����һ
		if(PrtStart==NULL)				//��ӡ��ϣ��رմ�ӡ��
		CloseRS232();
		else
		ReadPrtMsg();	//��FPGA��ȡ�����ӡ��Ϣ*/
		static char addnum=10;
		if(addnum==10)
		{
	    while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET)
	    {}
			USARTx->DR ='\n'; 	
			addnum--;
		}
		
		else if(addnum<=0)
		{
			PrtStart->nowprint=NULL;
			PrtStart->end=NULL;
			addnum=10;
			CloseRS232(USARTx);			
		}
		else if(addnum==1)
		{
			addnum--;
	    while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET)
	    {}
			USARTx->DR ='\n';
		}
		else 
		{
			addnum--;
	    while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET)
	    {}
			USARTx->DR =' ';	
		}
		
		
			
	}
	else
	{
	  while(USART_GetFlagStatus(USART3,USART_FLAG_TC)==RESET)
	  {}		
		USARTx->DR =*(++PrtStart->nowprint);
	}
}




//*******************************************/
/*���ܣ��ڴ�ӡ����������һ����Ϣ
��ڲ��������������Ϣ��Messagesavetop[]�е�λ��
���ڲ�������
/********************************************/
void InsMsg(sword xulie)
{
	print_list[print_sum++]=xulie;
	
/*	PrtLink *p;
	p=(PrtLink *)malloc(sizeof(PrtLink));
	p->xulie=xulie;
	p->next=PrtStart->next;
	PrtStart->next=p;
	PrtStart->xulie++;*/		
}

//*******************************************/
/*���ܣ��������ӡ
��ڲ�����
		frequency: 0-ȫ�� 1-518  2-490  3-4209.5 
		kind:      0-ȫ�� ��Ϣ����
		rxstation: 0-ȫ�� ����̨
		message:save:0 	lock:1	
���ڲ�������
/********************************************/
void Selectgiven(word frequency,word type,word rxstation,word messageset)
{
	sword i;
	sword msg_num=0;
	static sword print_temp=0;
	print_sum=0;
	for(i=0;i<Messageinfo.savenumber[0];i++)
	{
		if((frequency==0||Messagesavetop[Messagetoprank[i]].frequency==frequency)		//�ж��Ƿ�����
			&&(type==0||Messagesavetop[Messagetoprank[i]].mark[1]==type+64)
			&&(rxstation==0||Messagesavetop[Messagetoprank[i]].mark[0]==rxstation+64)
			&&(messageset==0||Messagesavetop[Messagetoprank[i]].lock==messageset)
		)
		
		{
			msg_num++;
			InsMsg(Messagetoprank[i]);		//�������ӡ����
		}		
	}
	if(msg_num==0)Checkinfo.Printover = 1;
	print_temp=0;
	while(print_temp<print_sum)
	{
		PrtStart->xulie=print_list[print_temp];
		ReadPrtMsg();	//��FPGA��ȡ�����ӡ��Ϣ
		StartRS232(USART3);	//������ӡ��
		Checkinfo.Printover = 0;
		while(Checkinfo.Printover==0)
		{
       DataTran(USART3);				
		};
		print_temp++;
	}
	print_sum=0;
}


//*******************************************/
/*���ܣ���ӡ��ǰ��ѡ����Ϣ
��ڲ�����Messagesavetop[]�������к�
���ڲ�������
/********************************************/
void Printmessage(sword num)
{
//	InsMsg(num);	//�������ӡ����
	PrtStart->xulie=num;
	ReadPrtMsg();	//��FPGA��ȡ�����ӡ��Ϣ
	StartRS232(USART3);	//������ӡ��
	Checkinfo.Printover = 0;
	while(Checkinfo.Printover==0)
  {
    DataTran(USART3);					
	};

}

//*******************************************/
/*���ܣ���ӡ��ѡ��������ѡ����Ϣ��������
��ڲ�������
���ڲ�������
/********************************************/
void Printselect();
void Printselect()
{
	
	sword i;
	static sword print_temp2=0;
	print_sum=0;
	for(i=0;i<Messageinfo.savenumber[0];i++)
	{
		if(Messagesavetop[Messagetoprank[i]].select==1)
		
		{
			InsMsg(Messagetoprank[i]);		//�������ӡ����
			Messagesavetop[Messagetoprank[i]].select=0;	//�����ѡ���
		}		
	}
	print_temp2=0;
	while(print_temp2<print_sum)
	{
		PrtStart->xulie=print_list[print_temp2];
		ReadPrtMsg();	//��FPGA��ȡ�����ӡ��Ϣ
		StartRS232(USART3);	//������ӡ��
		Checkinfo.Printover = 0;
		while(Checkinfo.Printover==0)
		{
      DataTran(USART3);					
		};
		print_temp2++;
	}
	print_sum=0;
}
//*******************************************/
/*���ܣ����ջ�״̬��ȡ
��ڲ�������
���ڲ�������
/********************************************/
void ReadPrtState(void);
void ReadPrtState(void)
{
	word i=0,j=0,t;
	char *l=receiver_state;
	long int address;
	PrtStart->nowprint=receiver_state;
//mode select	
	if(Mode==0)
	{
		i=34;
		receiver_state[i++]='A';
		receiver_state[i++]='U';
		receiver_state[i++]='T';
		receiver_state[i++]='0';
		receiver_state[i++]=' ';
		receiver_state[i++]=' ';
	}
	else
	{
		i=34;
		receiver_state[i++]='M';
		receiver_state[i++]='A';
		receiver_state[i++]='N';
		receiver_state[i++]='U';
		receiver_state[i++]='A';
		receiver_state[i++]='L';
	}
//area select
	i=52;
	receiver_state[i++]=manual_area/10+48;
	receiver_state[i++]=manual_area%10+48;
//518
	j=283;
	for(i=0;i<=25;i++) 	//518������Ϣ�������
	{
		if(MSGTYPE[0][i]==1) receiver_state[j++]=i+65;
		else receiver_state[j++]='-';
	}
//486
	j=349;		
	for(i=0;i<=25;i++) 	//486������Ϣ�������
	{
		if(MSGTYPE[1][i]==1) receiver_state[j++]=i+65;
		else receiver_state[j++]='-';
	}
//4209.5
	j=418;	
	for(i=0;i<=25;i++) 	//4209.5������Ϣ�������
	{
		if(MSGTYPE[2][i]==1) receiver_state[j++]=i+65;
		else receiver_state[j++]='-';
	}
	
	if(Mode==0)				//�Զ�ģʽ
 	{
		j=90;
		for(i=0;i<=25;i++) 	//518���ܷ���̨�����
		{
			word temp,temp1;
			temp1=Power(manual_area-1);
			temp=Auto[0][i]&temp1;
//			temp=Auto[0][i]&(word)(pow(2,BUFFER2[0]-1));	
			
			if(temp!=0) receiver_state[j++]=i+65;
			else receiver_state[j++]='-';
		}
		j=152;
		for(i=0;i<=25;i++) 	//490���ܷ���̨�����
		{
			word temp,temp1;
			temp1=Power(manual_area-1);
			temp=Auto[1][i]&temp1;
			
//			temp=Auto[1][i]&(word)(pow(2,BUFFER2[0]-1));	
			
			if(temp!=0) receiver_state[j++]=i+65;
			else receiver_state[j++]='-';

		}
		j=217;
		for(i=0;i<=25;i++) 	//4209.5���ܷ���̨�����
		{
			word temp,temp1;
			temp1=Power(manual_area-1);
			temp=Auto[2][i]&temp1;
//			temp=Auto[2][i]&(word)(pow(2,BUFFER2[0]-1));	
			
			if(temp!=0) receiver_state[j++]=i+65;
			else receiver_state[j++]='-';
		}	
 	}
 	
 	if(Mode==1)				//�ֶ�ģʽ
 	{
		j=90;
		for(i=0;i<=25;i++) 	//518���ܷ���̨�����
		{
			if(Manual[0][i]==1) receiver_state[j++]=i+65;
			else receiver_state[j++]='-';
		}
		j=152;
		for(i=0;i<=25;i++) 	//490���ܷ���̨�����
		{
			if(Manual[1][i]==1) receiver_state[j++]=i+65;
			else receiver_state[j++]='-';
		}
		j=217;
		for(i=0;i<=25;i++) 	//4209.5���ܷ���̨������
		{
			if(Manual[2][i]==1) receiver_state[j++]=i+65;
			else receiver_state[j++]='-';
		}
 	}
 	j=457;
 	t=Messageinfo.savenumber[1];
 	receiver_state[j++]=t/100+48;
 	receiver_state[j++]=(t/10)%10+48;
 	receiver_state[j++]=t%10+48;
 	
 	j=461;
 	t=Messageinfo.savenumber[2];
 	receiver_state[j++]=t/100+48;
 	receiver_state[j++]=(t/10)%10+48;
 	receiver_state[j++]=t%10+48;
 	
 	j=465;
 	t=Messageinfo.savenumber[3];
 	receiver_state[j++]=t/100+48;
 	receiver_state[j++]=(t/10)%10+48;
 	receiver_state[j++]=t%10+48;
 	
 	j=480;
 	t=Messageinfo.locknumber[1];
 	receiver_state[j++]=t/100+48;
 	receiver_state[j++]=(t/10)%10+48;
 	receiver_state[j++]=t%10+48;
 	
 	j=484;
 	t=Messageinfo.locknumber[2];
 	receiver_state[j++]=t/100+48;
 	receiver_state[j++]=(t/10)%10+48;
 	receiver_state[j++]=t%10+48;
 	
 	j=488;
 	t=Messageinfo.locknumber[3];
 	receiver_state[j++]=t/100+48;
 	receiver_state[j++]=(t/10)%10+48;
 	receiver_state[j++]=t%10+48;
	PrtStart->end=l+490;
}

//*******************************************/
/*���ܣ���ӡ���ջ�״̬����
��ڲ�������
���ڲ�������
/********************************************/
void Printstate();
void Printstate()
{
	ReadPrtState();	//��FPGA��ȡ�����ӡ��Ϣ
	StartRS232(USART3);	//������ӡ��
	Checkinfo.Printover = 0;
	//��ӡ״̬
	while(Checkinfo.Printover==0)
	{
    DataTran(USART3);					
	};
}

//*******************************************/
/*���ܣ���ӡ��������
��ڲ�������
���ڲ�������
/********************************************/
/*void Checkprint();
void Checkprint()
{
	//�޸� Checkinfo->Printstate   ��:0    ������:1
	//.......................//
}   */