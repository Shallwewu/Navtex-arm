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
/*¹¦ÄÜ£»SCI0²¨ÌØÂÊµÄÉèÖÃ
Èë¿Ú²ÎÊı£º²¨ÌØÂÊÉèÖÃ²ÎÊı
/********************************************/
void BadurateSet(char badurate);
void BadurateSet(char badurate)
{

	if(badurate==3)
	{
	USART_BaudRate(USART3,4800*3);		//²¨ÌØÂÊÎª4800bps	
	}
	else if(badurate==2)
	{
	USART_BaudRate(USART3,9600*3);			//²¨ÌØÂÊÎª9600bps	
	}		
	else if(badurate==1)
	{
	USART_BaudRate(USART3,19200*3);   	//²¨ÌØÂÊÎª19200bps
	}
}


//*******************************************/
/*¹¦ÄÜ£»SCI0µÄ³õÊ¼»¯ÅäÖÃ£¬²¨ÌØÂÊÎª4800bps£¬8±ÈÌØ£¬ÎŞÆæÅ¼Ğ£ÑéÎ»
Èë¿Ú²ÎÊı£ºÎŞ
³ö¿Ú²ÎÊı£ºÎŞ
/********************************************/
void IntialRS232();
void IntialRS232()
{
  USART3_Init();
  USART2_Init();
	BadurateSet(Receiverset[3]+1);					//²¨ÌØÂÊÎª4800bps 
}


//*******************************************/
/*¹¦ÄÜ£»¿ªÆô´«ËÍ
Èë¿Ú²ÎÊı£ºÎŞ
³ö¿Ú²ÎÊı£ºÎŞ
/********************************************/
void StartRS232(USART_TypeDef* USARTx)
{
	 USART_Cmd(USARTx,ENABLE);
}


//*******************************************/
/*¹¦ÄÜ£»¹Ø±Õ´«ËÍºÍ´«ËÍÖĞ¶Ï
Èë¿Ú²ÎÊı£ºÎŞ
³ö¿Ú²ÎÊı£ºÎŞ
/********************************************/
void CloseRS232(USART_TypeDef* USARTx)
{
    USART_Cmd(USARTx,DISABLE);
		Checkinfo.Printover = 1;
}

//*******************************************/
/*¹¦ÄÜ£»Êı¾İ´«ËÍ
Èë¿Ú²ÎÊı£ºÎŞ
³ö¿Ú²ÎÊı£ºÎŞ
/********************************************/
void DataTran(USART_TypeDef* USARTx)
{
//	#pragma interrupt saveall
    static int i=0;
//	PrtLink *p=PrtStart->next;
//	SCI_0_SR&=~SCI_0_SR_TDRE_MASK;		//TEÎ»ÖÃ0£¬transmitterÎŞĞ§	
//	SCI_0_DR='a';
 //   if((++i)>100)
//    {
//	    COPCTR=0xAAAA;
//	    COPCTR=0x5555;
//	    i=0;	
//    }
	if(PrtStart->nowprint==PrtStart->end)				//Èôµ±Ç°ĞÅÏ¢´òÓ¡Íê±Ï
	{
/*		
		free(p->start);					//ÏÈÇå³ı¿ª±ÙµÄÄÚ´æ¿é
		PrtStart->next=p->next;			//Ê×Ö¸ÕëÖ¸ÏòpÖ®ºóµÄ½Úµã
		free(p);						//ÊÍ·Å½Úµã
		PrtStart->xulie--;				//´òÓ¡×ÜĞÅÏ¢Êı¼õÒ»
		if(PrtStart==NULL)				//´òÓ¡Íê±Ï£¬¹Ø±Õ´òÓ¡»ú
		CloseRS232();
		else
		ReadPrtMsg();	//´ÓFPGA¶ÁÈ¡ËùĞè´òÓ¡ĞÅÏ¢*/
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
/*¹¦ÄÜ£»ÔÚ´òÓ¡¶ÓÁĞÖĞÔö¼ÓÒ»ÌõĞÅÏ¢
Èë¿Ú²ÎÊı£ºËùĞèÌí¼ÓĞÅÏ¢ÔÚMessagesavetop[]ÖĞµÄÎ»ÖÃ
³ö¿Ú²ÎÊı£ºÎŞ
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
/*¹¦ÄÜ£»Åú´¦Àí´òÓ¡
Èë¿Ú²ÎÊı£º
		frequency: 0-È«²¿ 1-518  2-490  3-4209.5 
		kind:      0-È«²¿ ĞÅÏ¢ÀàĞÍ
		rxstation: 0-È«²¿ ·¢ÉäÌ¨
		message:save:0 	lock:1	
³ö¿Ú²ÎÊı£ºÎŞ
/********************************************/
void Selectgiven(word frequency,word type,word rxstation,word messageset)
{
	sword i;
	sword msg_num=0;
	static sword print_temp=0;
	print_sum=0;
	for(i=0;i<Messageinfo.savenumber[0];i++)
	{
		if((frequency==0||Messagesavetop[Messagetoprank[i]].frequency==frequency)		//ÅĞ¶ÏÊÇ·ñÂú×ã
			&&(type==0||Messagesavetop[Messagetoprank[i]].mark[1]==type+64)
			&&(rxstation==0||Messagesavetop[Messagetoprank[i]].mark[0]==rxstation+64)
			&&(messageset==0||Messagesavetop[Messagetoprank[i]].lock==messageset)
		)
		
		{
			msg_num++;
			InsMsg(Messagetoprank[i]);		//Ìí¼ÓÖÁ´òÓ¡ĞòÁĞ
		}		
	}
	if(msg_num==0)Checkinfo.Printover = 1;
	print_temp=0;
	while(print_temp<print_sum)
	{
		PrtStart->xulie=print_list[print_temp];
		ReadPrtMsg();	//´ÓFPGA¶ÁÈ¡ËùĞè´òÓ¡ĞÅÏ¢
		StartRS232(USART3);	//¿ªÆô´òÓ¡»ú
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
/*¹¦ÄÜ£»´òÓ¡µ±Ç°ËùÑ¡¶¨ĞÅÏ¢
Èë¿Ú²ÎÊı£ºMessagesavetop[]Êı×éĞòÁĞºÅ
³ö¿Ú²ÎÊı£ºÎŞ
/********************************************/
void Printmessage(sword num)
{
//	InsMsg(num);	//Ìí¼ÓÖÁ´òÓ¡ĞòÁĞ
	PrtStart->xulie=num;
	ReadPrtMsg();	//´ÓFPGA¶ÁÈ¡ËùĞè´òÓ¡ĞÅÏ¢
	StartRS232(USART3);	//¿ªÆô´òÓ¡»ú
	Checkinfo.Printover = 0;
	while(Checkinfo.Printover==0)
  {
    DataTran(USART3);					
	};

}

//*******************************************/
/*¹¦ÄÜ£»´òÓ¡¸´Ñ¡½çÃæÖĞËùÑ¡¶¨ĞÅÏ¢£¨¶àÌõ£©
Èë¿Ú²ÎÊı£ºÎŞ
³ö¿Ú²ÎÊı£ºÎŞ
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
			InsMsg(Messagetoprank[i]);		//Ìí¼ÓÖÁ´òÓ¡ĞòÁĞ
			Messagesavetop[Messagetoprank[i]].select=0;	//Çå³ı¸´Ñ¡±ê¼Ç
		}		
	}
	print_temp2=0;
	while(print_temp2<print_sum)
	{
		PrtStart->xulie=print_list[print_temp2];
		ReadPrtMsg();	//´ÓFPGA¶ÁÈ¡ËùĞè´òÓ¡ĞÅÏ¢
		StartRS232(USART3);	//¿ªÆô´òÓ¡»ú
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
/*¹¦ÄÜ£»½ÓÊÕ»ú×´Ì¬¶ÁÈ¡
Èë¿Ú²ÎÊı£ºÎŞ
³ö¿Ú²ÎÊı£ºÎŞ
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
	for(i=0;i<=25;i++) 	//518½ÓÊÕĞÅÏ¢Àà±ğµÄÇé¿ö
	{
		if(MSGTYPE[0][i]==1) receiver_state[j++]=i+65;
		else receiver_state[j++]='-';
	}
//486
	j=349;		
	for(i=0;i<=25;i++) 	//486½ÓÊÕĞÅÏ¢Àà±ğµÄÇé¿ö
	{
		if(MSGTYPE[1][i]==1) receiver_state[j++]=i+65;
		else receiver_state[j++]='-';
	}
//4209.5
	j=418;	
	for(i=0;i<=25;i++) 	//4209.5½ÓÊÕĞÅÏ¢Àà±ğµÄÇé¿ö
	{
		if(MSGTYPE[2][i]==1) receiver_state[j++]=i+65;
		else receiver_state[j++]='-';
	}
	
	if(Mode==0)				//×Ô¶¯Ä£Ê½
 	{
		j=90;
		for(i=0;i<=25;i++) 	//518½ÓÊÜ·¢ÉäÌ¨µÄÇé¿ö
		{
			word temp,temp1;
			temp1=Power(manual_area-1);
			temp=Auto[0][i]&temp1;
//			temp=Auto[0][i]&(word)(pow(2,BUFFER2[0]-1));	
			
			if(temp!=0) receiver_state[j++]=i+65;
			else receiver_state[j++]='-';
		}
		j=152;
		for(i=0;i<=25;i++) 	//490½ÓÊÜ·¢ÉäÌ¨µÄÇé¿ö
		{
			word temp,temp1;
			temp1=Power(manual_area-1);
			temp=Auto[1][i]&temp1;
			
//			temp=Auto[1][i]&(word)(pow(2,BUFFER2[0]-1));	
			
			if(temp!=0) receiver_state[j++]=i+65;
			else receiver_state[j++]='-';

		}
		j=217;
		for(i=0;i<=25;i++) 	//4209.5½ÓÊÜ·¢ÉäÌ¨µÄÇé¿ö
		{
			word temp,temp1;
			temp1=Power(manual_area-1);
			temp=Auto[2][i]&temp1;
//			temp=Auto[2][i]&(word)(pow(2,BUFFER2[0]-1));	
			
			if(temp!=0) receiver_state[j++]=i+65;
			else receiver_state[j++]='-';
		}	
 	}
 	
 	if(Mode==1)				//ÊÖ¶¯Ä£Ê½
 	{
		j=90;
		for(i=0;i<=25;i++) 	//518½ÓÊÜ·¢ÉäÌ¨µÄÇé¿ö
		{
			if(Manual[0][i]==1) receiver_state[j++]=i+65;
			else receiver_state[j++]='-';
		}
		j=152;
		for(i=0;i<=25;i++) 	//490½ÓÊÜ·¢ÉäÌ¨µÄÇé¿ö
		{
			if(Manual[1][i]==1) receiver_state[j++]=i+65;
			else receiver_state[j++]='-';
		}
		j=217;
		for(i=0;i<=25;i++) 	//4209.5½ÓÊÜ·¢ÉäÌ¨µÄÇé¿öö
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
/*¹¦ÄÜ£»´òÓ¡½ÓÊÕ»ú×´Ì¬º¯Êı
Èë¿Ú²ÎÊı£ºÎŞ
³ö¿Ú²ÎÊı£ºÎŞ
/********************************************/
void Printstate();
void Printstate()
{
	ReadPrtState();	//´ÓFPGA¶ÁÈ¡ËùĞè´òÓ¡ĞÅÏ¢
	StartRS232(USART3);	//¿ªÆô´òÓ¡»ú
	Checkinfo.Printover = 0;
	//´òÓ¡×´Ì¬
	while(Checkinfo.Printover==0)
	{
    DataTran(USART3);					
	};
}

//*******************************************/
/*¹¦ÄÜ£»´òÓ¡»ú¼ì²â³ÌĞò
Èë¿Ú²ÎÊı£ºÎŞ
³ö¿Ú²ÎÊı£ºÎŞ
/********************************************/
/*void Checkprint();
void Checkprint()
{
	//ĞŞ¸Ä Checkinfo->Printstate   ºÃ:0    ÓĞÎÊÌâ:1
	//.......................//
}   */