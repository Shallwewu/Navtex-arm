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
/*功能；SCI0波特率的设置
入口参数：波特率设置参数
/********************************************/
void BadurateSet(char badurate);
void BadurateSet(char badurate)
{

	if(badurate==3)
	{
	USART_BaudRate(USART3,4800*3);		//波特率为4800bps	
	}
	else if(badurate==2)
	{
	USART_BaudRate(USART3,9600*3);			//波特率为9600bps	
	}		
	else if(badurate==1)
	{
	USART_BaudRate(USART3,19200*3);   	//波特率为19200bps
	}
}


//*******************************************/
/*功能；SCI0的初始化配置，波特率为4800bps，8比特，无奇偶校验位
入口参数：无
出口参数：无
/********************************************/
void IntialRS232();
void IntialRS232()
{
  USART3_Init();
  USART2_Init();
	BadurateSet(Receiverset[3]+1);					//波特率为4800bps 
}


//*******************************************/
/*功能；开启传送
入口参数：无
出口参数：无
/********************************************/
void StartRS232(USART_TypeDef* USARTx)
{
	 USART_Cmd(USARTx,ENABLE);
}


//*******************************************/
/*功能；关闭传送和传送中断
入口参数：无
出口参数：无
/********************************************/
void CloseRS232(USART_TypeDef* USARTx)
{
    USART_Cmd(USARTx,DISABLE);
		Checkinfo.Printover = 1;
}

//*******************************************/
/*功能；数据传送
入口参数：无
出口参数：无
/********************************************/
void DataTran(USART_TypeDef* USARTx)
{
//	#pragma interrupt saveall
    static int i=0;
//	PrtLink *p=PrtStart->next;
//	SCI_0_SR&=~SCI_0_SR_TDRE_MASK;		//TE位置0，transmitter无效	
//	SCI_0_DR='a';
 //   if((++i)>100)
//    {
//	    COPCTR=0xAAAA;
//	    COPCTR=0x5555;
//	    i=0;	
//    }
	if(PrtStart->nowprint==PrtStart->end)				//若当前信息打印完毕
	{
/*		
		free(p->start);					//先清除开辟的内存块
		PrtStart->next=p->next;			//首指针指向p之后的节点
		free(p);						//释放节点
		PrtStart->xulie--;				//打印总信息数减一
		if(PrtStart==NULL)				//打印完毕，关闭打印机
		CloseRS232();
		else
		ReadPrtMsg();	//从FPGA读取所需打印信息*/
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
/*功能；在打印队列中增加一条信息
入口参数：所需添加信息在Messagesavetop[]中的位置
出口参数：无
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
/*功能；批处理打印
入口参数：
		frequency: 0-全部 1-518  2-490  3-4209.5 
		kind:      0-全部 信息类型
		rxstation: 0-全部 发射台
		message:save:0 	lock:1	
出口参数：无
/********************************************/
void Selectgiven(word frequency,word type,word rxstation,word messageset)
{
	sword i;
	sword msg_num=0;
	static sword print_temp=0;
	print_sum=0;
	for(i=0;i<Messageinfo.savenumber[0];i++)
	{
		if((frequency==0||Messagesavetop[Messagetoprank[i]].frequency==frequency)		//判断是否满足
			&&(type==0||Messagesavetop[Messagetoprank[i]].mark[1]==type+64)
			&&(rxstation==0||Messagesavetop[Messagetoprank[i]].mark[0]==rxstation+64)
			&&(messageset==0||Messagesavetop[Messagetoprank[i]].lock==messageset)
		)
		
		{
			msg_num++;
			InsMsg(Messagetoprank[i]);		//添加至打印序列
		}		
	}
	if(msg_num==0)Checkinfo.Printover = 1;
	print_temp=0;
	while(print_temp<print_sum)
	{
		PrtStart->xulie=print_list[print_temp];
		ReadPrtMsg();	//从FPGA读取所需打印信息
		StartRS232(USART3);	//开启打印机
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
/*功能；打印当前所选定信息
入口参数：Messagesavetop[]数组序列号
出口参数：无
/********************************************/
void Printmessage(sword num)
{
//	InsMsg(num);	//添加至打印序列
	PrtStart->xulie=num;
	ReadPrtMsg();	//从FPGA读取所需打印信息
	StartRS232(USART3);	//开启打印机
	Checkinfo.Printover = 0;
	while(Checkinfo.Printover==0)
  {
    DataTran(USART3);					
	};

}

//*******************************************/
/*功能；打印复选界面中所选定信息（多条）
入口参数：无
出口参数：无
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
			InsMsg(Messagetoprank[i]);		//添加至打印序列
			Messagesavetop[Messagetoprank[i]].select=0;	//清除复选标记
		}		
	}
	print_temp2=0;
	while(print_temp2<print_sum)
	{
		PrtStart->xulie=print_list[print_temp2];
		ReadPrtMsg();	//从FPGA读取所需打印信息
		StartRS232(USART3);	//开启打印机
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
/*功能；接收机状态读取
入口参数：无
出口参数：无
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
	for(i=0;i<=25;i++) 	//518接收信息类别的情况
	{
		if(MSGTYPE[0][i]==1) receiver_state[j++]=i+65;
		else receiver_state[j++]='-';
	}
//486
	j=349;		
	for(i=0;i<=25;i++) 	//486接收信息类别的情况
	{
		if(MSGTYPE[1][i]==1) receiver_state[j++]=i+65;
		else receiver_state[j++]='-';
	}
//4209.5
	j=418;	
	for(i=0;i<=25;i++) 	//4209.5接收信息类别的情况
	{
		if(MSGTYPE[2][i]==1) receiver_state[j++]=i+65;
		else receiver_state[j++]='-';
	}
	
	if(Mode==0)				//自动模式
 	{
		j=90;
		for(i=0;i<=25;i++) 	//518接受发射台的情况
		{
			word temp,temp1;
			temp1=Power(manual_area-1);
			temp=Auto[0][i]&temp1;
//			temp=Auto[0][i]&(word)(pow(2,BUFFER2[0]-1));	
			
			if(temp!=0) receiver_state[j++]=i+65;
			else receiver_state[j++]='-';
		}
		j=152;
		for(i=0;i<=25;i++) 	//490接受发射台的情况
		{
			word temp,temp1;
			temp1=Power(manual_area-1);
			temp=Auto[1][i]&temp1;
			
//			temp=Auto[1][i]&(word)(pow(2,BUFFER2[0]-1));	
			
			if(temp!=0) receiver_state[j++]=i+65;
			else receiver_state[j++]='-';

		}
		j=217;
		for(i=0;i<=25;i++) 	//4209.5接受发射台的情况
		{
			word temp,temp1;
			temp1=Power(manual_area-1);
			temp=Auto[2][i]&temp1;
//			temp=Auto[2][i]&(word)(pow(2,BUFFER2[0]-1));	
			
			if(temp!=0) receiver_state[j++]=i+65;
			else receiver_state[j++]='-';
		}	
 	}
 	
 	if(Mode==1)				//手动模式
 	{
		j=90;
		for(i=0;i<=25;i++) 	//518接受发射台的情况
		{
			if(Manual[0][i]==1) receiver_state[j++]=i+65;
			else receiver_state[j++]='-';
		}
		j=152;
		for(i=0;i<=25;i++) 	//490接受发射台的情况
		{
			if(Manual[1][i]==1) receiver_state[j++]=i+65;
			else receiver_state[j++]='-';
		}
		j=217;
		for(i=0;i<=25;i++) 	//4209.5接受发射台的情况�
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
/*功能；打印接收机状态函数
入口参数：无
出口参数：无
/********************************************/
void Printstate();
void Printstate()
{
	ReadPrtState();	//从FPGA读取所需打印信息
	StartRS232(USART3);	//开启打印机
	Checkinfo.Printover = 0;
	//打印状态
	while(Checkinfo.Printover==0)
	{
    DataTran(USART3);					
	};
}

//*******************************************/
/*功能；打印机检测程序
入口参数：无
出口参数：无
/********************************************/
/*void Checkprint();
void Checkprint()
{
	//修改 Checkinfo->Printstate   好:0    有问题:1
	//.......................//
}   */