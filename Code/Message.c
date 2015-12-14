#include <stdio.h>
#include <stdlib.h>
#include "run.h"
#include "define.h"	
#include "lcddrive.h"
#include "flash.h"
#include "Eprom.h"
#include "iec.h"
#include "code.h"
#include "printer.h"
#include "stm32f2xx.h"
#include "MessageDeal.h"
#define FlashmapSize_Word	 0x0400		//�洢��Ϣ�Ŀ��С1K��
//extern volatile byte LINE;									//ͳ������ʾ��Ϣ��������
/* BUFFER[0]��ʾҺ��������������Ϣ������λ�ã�BUFFER[1]��ʾ��ǰ��ָ��������Ϣ������λ��*/


//********************************************/
/*���ܣ����ͼ��������ʾ
��ڲ�������
���ڲ�������
/*********************************************/
void Mgga_pt();
void Mgga_pt()	
{
//	CLEARXLINE(0,39,22);			//���ͼ������ʾ
				
//	XLINE(0,39,17);
//	W_YLINE(0,0,239);
//	W_YLINE(309,17,229);
//	W_YLINE(319,0,239);
	CLEARXLINE(0,39,17);			//���ͼ������ʾ
	CLEARXLINE(0,39,22);
	CLEARXLINE(0,39,17);			//���ͼ������ʾ
				
		//		XLINE(0,39,20);
			    XLINE(0,39,22);
				W_YLINE(0,0,239);
				W_YLINE(309,22,225);
				W_YLINE(319,0,239);
				
				 W_XLINE(0,319,225);		//�����ױ߿�	
                 W_CLEARXLINE(1,318,230);
}

//********************************************/
/*���ܣ��������Ӣ���ַ���һ�����ĺ��ֵ�ת��
��ڲ���������Ӣ���ַ�������ĸ��ַ
���ڲ�����LCD������
/*********************************************/
u16 eng_to_lcd(char *p)
{
	u16 lcd;
	u16 temp,temp1,temp2;
	temp=(*p-'A')*676+(*(p+1)-'A')*26+(*(p+2)-'A');	//������ֵ
	temp1=temp/94+0xa1;								//��������+0xA0,temp/94Ϊ����-1
	temp2=temp%94+0xa1;								//����λ��+0xA0,temp/94Ϊλ��-1
	lcd=(temp1<<8)+temp2;							//�ϳ�GB2312-1980������
	return lcd;
}
//********************************************/
/*���ܣ���������ƶ���Ǻ����½���Ϣ����ʾ��
��ڲ�������
���ڲ�������
/*********************************************/
void Message_line();	
void Message_line()
{

	DISASCIII(15,19,LINE);			//��ʾ����Ϣ��
	DISASCIII(11,19,BUFFER[0]);		//��ʾ��ǰ��Ϣ��
		
}
//********************************************/
/*���ܣ������Ϣ��ͷ����ʾ
��ڲ�������
���ڲ�������
/*********************************************/
void Message_toppaint();
void Message_toppaint()	
{
	char i,j;
	
//	Messagetoptype *temp;
	 
//	temp=&Messagesavetop[Messagetoprank[Messagenownumber]];
/*	for(i=0;i<2;i++)
	{
		switch(temp->mark[i])
					{
						case('-'):temp->mark[i]='A';break;
						case('?'):temp->mark[i]='B';break;
						case(':'):temp->mark[i]='C';break;
						case('*'):temp->mark[i]='D';break;
						case('3'):temp->mark[i]='E';break;
						case('%'):temp->mark[i]='F';break;
						case('#'):temp->mark[i]='G';break;
						case(34):temp->mark[i]='H';break;//' "  '˫����
						case('8'):temp->mark[i]='I';break;
						case('@'):temp->mark[i]='J';break;
						case('('):temp->mark[i]='K';break;
						case(')'):temp->mark[i]='L';break;
						case('.'):temp->mark[i]='M';break;
						case(','):temp->mark[i]='N';break;
						case('9'):temp->mark[i]='O';break;
						case('0'):temp->mark[i]='P';break;
						case('1'):temp->mark[i]='Q';break;
						case('4'):temp->mark[i]='R';break;
						case(39):temp->mark[i]='S';break;//' ' '������
						case('5'):temp->mark[i]='T';break;
						case('7'):temp->mark[i]='U';break;
						case('='):temp->mark[i]='V';break;
						case('2'):temp->mark[i]='W';break;
						case('/'):temp->mark[i]='X';break;
						case('6'):temp->mark[i]='Y';break;
						case('+'):temp->mark[i]='Z';break;
						default:break;
					
	}*/
	for(i=0;i<4;i++) 				//��Ϣ��Ƿ���
	{
//	    if(i==0&&temp->mark[i]==0x01)CW_PR3(3+i,1,'Q');
//		else CW_PR3(3+i,1,temp->mark[i]);
		if(i==0||i==1)
		{
			switch(msgtop.mark[i])
					{
						case('-'):CW_PR3(3+i,1,'A');break;
						case('?'):CW_PR3(3+i,1,'B');break;
						case(':'):CW_PR3(3+i,1,'C');break;
						case('*'):CW_PR3(3+i,1,'D');break;
						case('3'):CW_PR3(3+i,1,'E');break;
						case('%'):CW_PR3(3+i,1,'F');break;
						case('#'):CW_PR3(3+i,1,'G');break;
						case(34):CW_PR3(3+i,1,'H');break;//' "  '˫����
						case('8'):CW_PR3(3+i,1,'I');break;
						case('@'):CW_PR3(3+i,1,'J');break;
						case('('):CW_PR3(3+i,1,'K');break;
						case(')'):CW_PR3(3+i,1,'L');break;
						case('.'):CW_PR3(3+i,1,'M');break;
						case(','):CW_PR3(3+i,1,'N');break;
						case('9'):CW_PR3(3+i,1,'O');break;
						case('0'):CW_PR3(3+i,1,'P');break;
						case('1'):CW_PR3(3+i,1,'Q');break;
						case('4'):CW_PR3(3+i,1,'R');break;
						case(39):CW_PR3(3+i,1,'S');break;//' ' '������
						case('5'):CW_PR3(3+i,1,'T');break;
						case('7'):CW_PR3(3+i,1,'U');break;
						case('='):CW_PR3(3+i,1,'V');break;
						case('2'):CW_PR3(3+i,1,'W');break;
						case('/'):CW_PR3(3+i,1,'X');break;
						case('6'):CW_PR3(3+i,1,'Y');break;
						case('+'):CW_PR3(3+i,1,'Z');break;
						default:CW_PR3(3+i,1,msgtop.mark[i]);break;
		}
		
	}
	else CW_PR3(3+i,1,msgtop.mark[i]);
	}
	switch(msgtop.frequency)			//Ƶ����ʾ���
	{
		case 1:
			{
				CW_PR3(9,1,'5');
				CW_PR3(10,1,'1');
				CW_PR3(11,1,'8');
				CW_PR3(12,1,' ');
				CW_PR3(13,1,' ');
				CW_PR3(14,1,' ');	
			} break;
		case 2:
			{
				CW_PR3(9,1,'4');
				CW_PR3(10,1,'8');
				CW_PR3(11,1,'6');
				CW_PR3(12,1,' ');
				CW_PR3(13,1,' ');
				CW_PR3(14,1,' ');	
			} break;
		case 3:
			{
				CW_PR3(9,1,'4');
				CW_PR3(10,1,'2');
				CW_PR3(11,1,'0');
				CW_PR3(12,1,'9');
				CW_PR3(13,1,'.');
				CW_PR3(14,1,'5');	
			} break;
		default:break;
	}
	
	DISASCII(21,1,msgtop.date[0]);  	//��
	CW_PR3(23,1,'/');	
	DISASCII(24,1,msgtop.date[1]);  	//��
	CW_PR3(26,1,'/');
	DISASCII(27,1,msgtop.date[2]);	//��
	
	DISASCII(31,1,msgtop.time[0]);	//Сʱ
	CW_PR3(33,1,':');	
	DISASCII(34,1,msgtop.time[1]);	//����
	
	if(msgtop.read==1) 				//δ����ǵ���ʾ
	{
		W_NEWMESSAGE(37,1);
	}							
	else 	
	{
		W_CLEARMESSAGE(37,1);
	}
	
}

//********************************************/
/*���ܣ���Ϣ�������ʾ����
��ڲ�������
���ڲ�������
/*********************************************/
void Message_Paintintial();
void Message_Paintintial()
{   
  	word zishu=0,i=0,mountbyte=0,temp,temp_end,i_temp,mountbyte_lcd=0,k=0;
  	sword chresult;//������Ԫ��Ӧ�����0�����ַ� 1�����ַ� 2�����ַ�
  	byte t;
  	
  	
  	

  	
//    SYSTAB[2]=0x0b;
	if((Messageinfo.savenumber[0]&&(Returntype==0||Returntype==1||Returntype==3))||
	   (Messageinfo.locknumber[0]&&(Returntype==2||Returntype==4)))			//���ջ�������Ϣ����
	{
		if(subback==10) RecoverData();		//�ӽ��淵�أ��ָ��ӽ��渲�ǵ�����
		else
		{
			CLEAR1();				  				  	
			MessagePoint[0]=MessagePoint[1]=MessagePoint[3]=NULL;
			IICRead_ONE_MEHE((Messagetoprank[Messagenownumber])*((word)MESSTYPELENGTH),&msgtop);
			ReadMessFlash((msgtop.flashadd)*(uint32)FlashmapSize_Word,MessagePoint);//����Ϣ�����ڴ�
			mountbyte=msgtop.amount;				//��ȡ��Ϣ������
		//	mountbyte=mountbyte<<8;
		//	t=(byte)MessagePoint[1];
		//	mountbyte+=t;					//mountbyteΪʵ���ַ���+1


/*�����Ϣĩβ��ʾ����zzy@2010-6-9*/
			if((msgtop.frequency==2)&&(mountbyte>18))
			{
				for(i=18;i<mountbyte-1;i++)
				{ 
					switch(MessagePoint[i])
					{
						case('-'):MessagePoint[i]='A';break;
						case('?'):MessagePoint[i]='B';break;
						case(':'):MessagePoint[i]='C';break;
						case('*'):if(MessagePoint[i-1]!='*'&&MessagePoint[i+1]!='*')MessagePoint[i]='D';break;
						case('3'):MessagePoint[i]='E';break;
						case('%'):MessagePoint[i]='F';break;
						case('#'):MessagePoint[i]='G';break;
						case(34):MessagePoint[i]='H';break;//' "  '˫����
						case('8'):MessagePoint[i]='I';break;
						case('@'):MessagePoint[i]='J';break;
						case('('):MessagePoint[i]='K';break;
						case(')'):MessagePoint[i]='L';break;
						case('.'):MessagePoint[i]='M';break;
						case(','):MessagePoint[i]='N';break;
						case('9'):MessagePoint[i]='O';break;
						case('0'):MessagePoint[i]='P';break;
						case('1'):MessagePoint[i]='Q';break;
						case('4'):MessagePoint[i]='R';break;
						case(39):MessagePoint[i]='S';break;//' ' '������
						case('5'):MessagePoint[i]='T';break;
						case('7'):MessagePoint[i]='U';break;
						case('='):MessagePoint[i]='V';break;
						case('2'):MessagePoint[i]='W';break;
						case('/'):MessagePoint[i]='X';break;
						case('6'):MessagePoint[i]='Y';break;
						case('+'):MessagePoint[i]='Z';break;
						default:break;
					}
					if((MessagePoint[i]=='Z')&&(MessagePoint[i+1]=='C')&&(MessagePoint[i+2]=='Z')&&(MessagePoint[i+3]=='C'))
					mountbyte=i;
					
				}
				for(i=8;i<18;i++)
				{
					switch(MessagePoint[i])
					{

						case('0'):chinese[mountbyte_lcd++]=0xa3b0;break;
						case('1'):chinese[mountbyte_lcd++]=0xa3b1;break;
						case('2'):chinese[mountbyte_lcd++]=0xa3b2;break;
						case('3'):chinese[mountbyte_lcd++]=0xa3b3;break;
						case('4'):chinese[mountbyte_lcd++]=0xa3b4;break;
						case('5'):chinese[mountbyte_lcd++]=0xa3b5;break;
						case('6'):chinese[mountbyte_lcd++]=0xa3b6;break;
						case('7'):chinese[mountbyte_lcd++]=0xa3b7;break;
						case('8'):chinese[mountbyte_lcd++]=0xa3b8;break;
						case('9'):chinese[mountbyte_lcd++]=0xa3b9;break;
						default:break;
					}		
				}
				chinese[mountbyte_lcd++]='\r';
				chinese[mountbyte_lcd++]='\n';
				for(i=18;i<mountbyte-1;i++)
				{
				    if(MessagePoint[i]==0)continue;
				    




					if(MessagePoint[i]=='\r')
						chresult=31;

					else if(MessagePoint[i]=='\n')
						chresult=32;                           //\r,\n�ճ�ת��




					else if((MessagePoint[i]<='M')&&(MessagePoint[i]>='A'))
					{
						if((MessagePoint[i+1]<='Z')&&(MessagePoint[i+1]>='A'))
						{
							if((MessagePoint[i+2]<='Z')&&(MessagePoint[i+2]>='A'))
							{
									//if(MessagePoint[i+2]==MessagePoint[i+5]==MessagePoint[i+8]=='A')chresult=11;
									chresult=30;            //������ĸ����ת��Ҫ��
							}
							                      
							else if(((MessagePoint[i+3]<='Z')&&(MessagePoint[i+3]>='N'))&&((MessagePoint[i+4]<='M')&&(MessagePoint[i+4]>='A'))&&((MessagePoint[i+6]<='Z')&&(MessagePoint[i+6]>='N')))
								chresult=23;                     //��������ַ�
							else 
								chresult=03;                     //��������ַ�
						}
						else
						{
							if((MessagePoint[i+2]<='Z')&&(MessagePoint[i+2]>='A'))
							{
								if(((MessagePoint[i+3]<='Z')&&(MessagePoint[i+3]>='N'))&&((MessagePoint[i+4]<='M')&&(MessagePoint[i+4]>='A'))&&((MessagePoint[i+7]<='M')&&(MessagePoint[i+7]>='A')))
									chresult=22;                 //��ڶ����ַ�
								else 
									chresult=02;                 //��ڶ����ַ�
							}
							else
								chresult=0;                     //��������ַ�				
						}
					}
					else 
					{
						if(((MessagePoint[i]<='Z')&&(MessagePoint[i]>='N'))&&((MessagePoint[i+2]<='M')&&(MessagePoint[i+2]>='A'))&&((MessagePoint[i+3]<='Z')&&(MessagePoint[i+3]>='N')))
							chresult=11;                       //�ٵ�һ���ַ�
						else if(((MessagePoint[i+1]<='M')&&(MessagePoint[i+1]>='A'))&&((MessagePoint[i+3]<='Z')&&(MessagePoint[i+3]>='N'))&&((MessagePoint[i+4]<='M')&&(MessagePoint[i+4]>='A')))
							chresult=21;                       //���һ���ַ�
						else if(((MessagePoint[i+1]<='Z')&&(MessagePoint[i+1]>='A'))&&((MessagePoint[i+2]<='Z')&&(MessagePoint[i+2]>='A'))&&((MessagePoint[i+3]<='M')&&(MessagePoint[i+3]>='A')))
							chresult=01;                       //���һ���ַ�
						else 
							chresult=0;                         //�������ַ�����
						if(MessagePoint[i+4]=='A'&&MessagePoint[i+7]=='A'&&MessagePoint[i+10]=='A')
						    chresult=21;			
					}
					if(MessagePoint[i]=='A'&&((MessagePoint[i+1]>='H'&&MessagePoint[i+1]<='K')||(MessagePoint[i-3]=='A'&&MessagePoint[i-2]>='H'&&MessagePoint[i-2]<='K')))
					{
					    if(MessagePoint[i+2]=='A'&&MessagePoint[i+3]>='H'&&MessagePoint[i+3]<='K'&&MessagePoint[i+5]=='A'&&MessagePoint[i+6]>='H'&&MessagePoint[i+6]<='I')
					    chresult=13;
					}

					switch(chresult)                            //�㷨����
					{
						case(30):                               //����ת��������ĸ                     
							chinese[mountbyte_lcd++]=eng_to_lcd(&MessagePoint[i]);
							/*if(((MessagePoint[i+3]<='M')&&(MessagePoint[i+3]>='A'))&&((MessagePoint[i+4]<='Z')&&(MessagePoint[i+4]>='A'))&&((MessagePoint[i+5]<='Z')&&(MessagePoint[i+5]>='A')))         //����������
							{
								for(j=0;j<3;j++)
								{
									nu0[j]=letonu(MessagePoint[i+j]);
									nu1[j]=letonu(MessagePoint[i+3+j]);
								}
								for(j=4;j>0;j--)
									rechart[nu0[0]][nu0[1]][nu0[2]][j]=rechart[nu0[0]][nu0[1]][nu0[2]][j-1];
								rechart[nu0[0]][nu0[1]][nu0[2]][0]=nu1[0]*10000+nu1[1]*100+nu1[2];
							}*/
							i=i+2;
							break;
						case(31):                              //��\r����ת��                         
					//		chinese[mountbyte_lcd++]='\r';
					//		i=i+1;
							break;
						case(32):                              //��\n����ת��                          
					//		chinese[mountbyte_lcd++]='\n';
					//		i=i+1;
							break;
						case(21):                             //���һ���ַ� 
							//MessagePoint[i]='*';                                  //������                          
							break;
						case(22):                             //��ڶ����ַ�
							MessagePoint[i+1]=MessagePoint[i+2];
							MessagePoint[i+2]=MessagePoint[i+3];
							//MessagePoint[i+3]='*';                                 //������
							chinese[mountbyte_lcd++]=eng_to_lcd(&MessagePoint[i]);
							i=i+3;
							break;
						case(23):                             //��������ַ�                        
							MessagePoint[i+2]=MessagePoint[i+3];
							//MessagePoint[i+3]='*';                                 //������
							chinese[mountbyte_lcd++]=eng_to_lcd(&MessagePoint[i]);
							i=i+3;
							break;
						case(01):                       
						case(02):                       
						case(03): 
	                              //������
								chinese[mountbyte_lcd++]=0xa3aa;
					   		i=i+2;                   
							break;
						case(0):
							//MessagePoint[i]=MessagePoint[i+1]=MessagePoint[i+2]='*';                                 //������
							chinese[mountbyte_lcd++]=0xa3aa;
					   		i=i+3;  
							break;
						case(13):                              //�ٵ�һ���ַ�
					    case(11):                             //�ٵڶ����ַ�
							                    //������
							chinese[mountbyte_lcd++]=0xa3aa;
					      	i=i+1;
					    	break;
						default:
							break;
					}
				}

				if((chinese[mountbyte_lcd-1]==0xa3ce)&&
				(chinese[mountbyte_lcd-2]==0xa3ce)&&
				(chinese[mountbyte_lcd-3]==0xa3ce)&&
				(chinese[mountbyte_lcd-4]==0xa3ce))
				{
					chinese[mountbyte_lcd-4]='\r';
					chinese[mountbyte_lcd-3]='\n';
					chinese[mountbyte_lcd-2]=0xa3ce;			//'N'
					chinese[mountbyte_lcd-1]=0xa3ce;			//'N'
					chinese[mountbyte_lcd++]=0xa3ce;			    //'N'
					chinese[mountbyte_lcd++]=0xa3ce;			//'N'
					chinese[mountbyte_lcd++]='\r';
					chinese[mountbyte_lcd++]='\n';
					chinese[mountbyte_lcd++]='\r';
					chinese[mountbyte_lcd++]='\n';
					chinese[mountbyte_lcd++]=0xa1a1;			//' '
					chinese[mountbyte_lcd++]=0xa3a8;			//'('
					chinese[mountbyte_lcd++]=0xcdea;			//'��'
					chinese[mountbyte_lcd++]=0xd5fb;			//'��'
					chinese[mountbyte_lcd++]=0xd0c5;			//'��'
					chinese[mountbyte_lcd++]=0xcfa2;			//'Ϣ'
					chinese[mountbyte_lcd++]=0xa3a9;			//')'
					for(i_temp=0;i_temp<21;i_temp++)		//���ĩ��β����ʾ
						chinese[mountbyte_lcd++]=0xa1a1;
					mountbyte_lcd=mountbyte_lcd-21;	
				}
				else if((MessagePoint[mountbyte-2]=='N')&&		//��Ը��ݵ���Ϣ���
				(MessagePoint[mountbyte-3]=='N')&&
				(MessagePoint[mountbyte-4]=='N')&&
				(MessagePoint[mountbyte-5]=='N'))
				{
					chinese[mountbyte_lcd-2]='\r';
					chinese[mountbyte_lcd-1]='\n';
					chinese[mountbyte_lcd++]=0xa3ce;			//'N'
					chinese[mountbyte_lcd++]=0xa3ce;			//'N'
					chinese[mountbyte_lcd++]=0xa3ce;			//'N'
					chinese[mountbyte_lcd++]=0xa3ce;			//'N'
					chinese[mountbyte_lcd++]='\r';
					chinese[mountbyte_lcd++]='\n';
					chinese[mountbyte_lcd++]='\r';
					chinese[mountbyte_lcd++]='\n';
					chinese[mountbyte_lcd++]=0xa1a1;			//' '
					chinese[mountbyte_lcd++]=0xa3a8;			//'('
					chinese[mountbyte_lcd++]=0xcdea;			//'��'
					chinese[mountbyte_lcd++]=0xd5fb;			//'��'
					chinese[mountbyte_lcd++]=0xd0c5;			//'��'
					chinese[mountbyte_lcd++]=0xcfa2;			//'Ϣ'
					chinese[mountbyte_lcd++]=0xa3a9;			//')'
					for(i_temp=0;i_temp<21;i_temp++)		//���ĩ��β����ʾ
						chinese[mountbyte_lcd++]=0xa1a1;
					mountbyte_lcd=mountbyte_lcd-21;
				}
				else
				{
					chinese[mountbyte_lcd++]='\r';
					chinese[mountbyte_lcd++]='\n';
					chinese[mountbyte_lcd++]='\r';
					chinese[mountbyte_lcd++]='\n';
					chinese[mountbyte_lcd++]=0xa1a1;			//' '
					chinese[mountbyte_lcd++]=0xa3a8;			//'('
					chinese[mountbyte_lcd++]=0xb2bb;			//'��'
					chinese[mountbyte_lcd++]=0xcdea;			//'��'
					chinese[mountbyte_lcd++]=0xd5fb;			//'��'
					chinese[mountbyte_lcd++]=0xd0c5;			//'��'
					chinese[mountbyte_lcd++]=0xcfa2;			//'Ϣ'
					chinese[mountbyte_lcd++]=0xa3a9;			//')'
					for(i_temp=0;i_temp<21;i_temp++)		//���ĩ��β����ʾ
						chinese[mountbyte_lcd++]=0xa1a1;
					mountbyte_lcd=mountbyte_lcd-21;	
				}                                        
	/*��Ϣĩβ�������*/				
			  	BUFFER[0]=1;					//
		  		LinePoint2[1]=&chinese[0];	//
		  		LINE=1;
		  		i=0;							
				/*������Ҫ����ͳ������������ҳ�����ù涨*/
		  		while(i<mountbyte_lcd)
		  		{
					if(chinese[i]=='\r')		//�����س�����������һ���������㣬ͬʱiҲ��++����NAVTEX�б����
					{	
//						i++;	//��NAVTEX�����лس��ͻ�����ͬʱ���ֵģ�ֱ���������еĴ���
						if(chinese[i-1]!='\r')
						{
							zishu=0;					
							if(i+2<mountbyte_lcd)
							{
								LINE++;
								LinePoint2[LINE]=&chinese[i+1];						
							}	
						}
//						else
//							zishu--;
						

					}
					else if(chinese[i]=='\n')
					{
						if((chinese[i-1]!='\r')&&(chinese[i-1]!='\n'))
						{
							zishu=0;					
							if(i+2<mountbyte_lcd)
							{
								LINE++;
								LinePoint2[LINE]=&chinese[i+1];						
							}	
						}
//						else
//							zishu--;
					}

		/*		    
					else if(chinese[i]==9) 	//����TAB�������������ĸ�
						zishu+=4;*///TAB����δ���
	/*				if((chinese[i]=='\r'||chinese[i]=='\n'))
					{
						if(rn==0)
						{
							if(i+2<mountbyte_lcd)
							{
								LINE++;
								LinePoint2[LINE]=&chinese[i+1];	
							}
						rn=1;
						}	
					}
					*/
					else zishu++;
					
					if(zishu>=18)			//������һ����������һ���������㣬�������ֳ���37��������TAB��
					{
						zishu=0;
						if((chinese[i+1]=='\r')||(chinese[i+1]=='\n'))
						{
							//do nothing	
						}
						else if(i+2<mountbyte_lcd)
						{
							LINE++;
							LinePoint2[LINE]=&chinese[i+1];
						}
					}
					i++;	  			
		  		}
		  		
		  		
				
			    Mgga_pt();
								
				Message_toppaint();				//ͷ��Ϣ���ݵ���ʾ
				
				MessageDisplay(BUFFER[0]);		//��Ϣ������ʾ,BUFFER[0]��Ϊ�ڼ��п�ʼ

				CTAB[1]='M';	CTAB[2]='S';	CTAB[3]='G';	CTAB[5]='L';	CTAB[6]='I';
				CTAB[7]='N';	CTAB[8]='E';	CTAB[9]='S';	CTAB[10]=':';
				CTAB[14]='/';
				CW_PR(0,19,15); 					//�ַ�����ʾ
				        			
				Message_line();	
			}
			else if(((msgtop.frequency==1)||(msgtop.frequency==3))&&(mountbyte>5))
			{
				temp_end=mountbyte-1;
				if((MessagePoint[mountbyte-2]=='N')&&
				(MessagePoint[mountbyte-3]=='N')&&
				(MessagePoint[mountbyte-4]=='N')&&
				(MessagePoint[mountbyte-5]=='N'))
				{
					MessagePoint[temp_end++]='\r';
					MessagePoint[temp_end++]='\n';
					MessagePoint[temp_end++]='\r';
					MessagePoint[temp_end++]='\n';
					MessagePoint[temp_end++]=' ';
					MessagePoint[temp_end++]='(';
					MessagePoint[temp_end++]='E';
					MessagePoint[temp_end++]='N';
					MessagePoint[temp_end++]='D';
					MessagePoint[temp_end++]=' ';
					MessagePoint[temp_end++]='O';
					MessagePoint[temp_end++]='F';
					MessagePoint[temp_end++]=' ';
					MessagePoint[temp_end++]='M';
					MessagePoint[temp_end++]='E';
					MessagePoint[temp_end++]='S';
					MessagePoint[temp_end++]='S';
					MessagePoint[temp_end++]='A';
					MessagePoint[temp_end++]='G';
					MessagePoint[temp_end++]='E';
					MessagePoint[temp_end++]=')';
					for(i_temp=0;i_temp<21;i_temp++)		//���ĩ��β����ʾ
						MessagePoint[temp_end++]=' ';
					mountbyte=mountbyte+23;
				}
				else
				{
					MessagePoint[temp_end++]='\r';
					MessagePoint[temp_end++]='\n';
					MessagePoint[temp_end++]='\r';
					MessagePoint[temp_end++]='\n';
					MessagePoint[temp_end++]=' ';
					MessagePoint[temp_end++]='(';
					MessagePoint[temp_end++]='I';
					MessagePoint[temp_end++]='N';
					MessagePoint[temp_end++]='C';
					MessagePoint[temp_end++]='O';
					MessagePoint[temp_end++]='M';
					MessagePoint[temp_end++]='P';
					MessagePoint[temp_end++]='L';
					MessagePoint[temp_end++]='E';
					MessagePoint[temp_end++]='T';
					MessagePoint[temp_end++]='E';
					MessagePoint[temp_end++]=' ';
					MessagePoint[temp_end++]='M';
					MessagePoint[temp_end++]='E';
					MessagePoint[temp_end++]='S';
					MessagePoint[temp_end++]='S';
					MessagePoint[temp_end++]='A';
					MessagePoint[temp_end++]='G';
					MessagePoint[temp_end++]='E';
					MessagePoint[temp_end++]=')';
					for(i_temp=0;i_temp<17;i_temp++)		//���ĩ��β����ʾ
						MessagePoint[temp_end++]=' ';
					mountbyte=mountbyte+26;			
				}               
			


	/*��Ϣĩβ�������*/				
			  	BUFFER[0]=1;					//BUFFER[0]����LCD��ǰ��ʾҳ�ĵ�һ����������Ϣ�е�λ��
		  		LinePoint[1]=&MessagePoint[6];	//6 ȥ��֮ǰ����Ϣ���Ͱ�̨��Ϣ��ʶ
		  		LINE=1;
		  		i=6;							
				/*������Ҫ����ͳ������������ҳ�����ù涨*/
		  		while(i<mountbyte-1)
		  		{
					if(((MessagePoint[i]==13)&&(MessagePoint[i+1]==10))||((MessagePoint[i]==10)&&(MessagePoint[i+1]==13)))		//�����س�����������һ���������㣬ͬʱiҲ��++����NAVTEX�б����
					{	
						i++;	//��NAVTEX�����лس��ͻ�����ͬʱ���ֵģ�ֱ���������еĴ���
						zishu=0;					
						if(i+2<mountbyte)
						{
							LINE++;
							LinePoint[LINE]=&MessagePoint[i+1];							
						}

					}
					else if(((MessagePoint[i]==10)&&(MessagePoint[i+1]!=13))||((MessagePoint[i]==13)&&(MessagePoint[i+1]!=10)))
					{
						zishu=0;					
						if(i+2<mountbyte)
						{
							LINE++;
							LinePoint[LINE]=&MessagePoint[i+1];							
						}
						
					}
					else if(MessagePoint[i]==9) 	//����TAB�������������ĸ�
						zishu+=4;
					else zishu++;
					
					if((zishu==37)&&(MessagePoint[i]>='A')&&(MessagePoint[i]<='Z')&&(((MessagePoint[i+1]>='A')&&(MessagePoint[i+1]<='Z'))||((MessagePoint[i-1]<'A')||(MessagePoint[i-1]>'Z'))))
					{
						zishu=0;
						if(i+2<mountbyte)
						{
							LINE++;
							LinePoint[LINE]=&MessagePoint[i];
						}
						i--;	
					}
					else if(zishu>=37)			//������һ����������һ���������㣬�������ֳ���37��������TAB��
					{
						zishu=0;
						if(i+2<mountbyte)
						{
							LINE++;
							LinePoint[LINE]=&MessagePoint[i+1];
						}
					}
					i++;	  			
		  		}
		  		
		  		
				
				Mgga_pt();
								
				Message_toppaint();				//ͷ��Ϣ���ݵ���ʾ
				
				MessageDisplay(BUFFER[0]);		//��Ϣ������ʾ,BUFFER[0]��Ϊ�ڼ��п�ʼ

				CTAB[1]='M';	CTAB[2]='S';	CTAB[3]='G';	CTAB[5]='L';	CTAB[6]='I';
				CTAB[7]='N';	CTAB[8]='E';	CTAB[9]='S';	CTAB[10]=':';
				CTAB[14]='/';
				CW_PR(0,19,15); 					//�ַ�����ʾ
				        			
				Message_line();
			}
			else
			{
				Mgga_pt();
				
				Message_toppaint();
			
				if(LANGUAGE==0)						//Ӣ�Ĳ˵�
				{
					CTAB[1]='I';	CTAB[2]='N';	CTAB[3]='C';	CTAB[4]='O';
					CTAB[5]='M';	CTAB[6]='P';	CTAB[7]='L';	CTAB[8]='E';
					CTAB[9]='T';	CTAB[10]='E';	CTAB[11]=' ';	CTAB[12]='M';
					CTAB[13]='E';	CTAB[14]='S';	CTAB[15]='S';	CTAB[16]='A';
					CTAB[17]='G';	CTAB[18]='E';	
					CW_PR(1,3,19);					//��ʾ���ݣ�INCOMPLETE MESSAGE 				
				}
				
				else								//���Ĳ˵�
				{
					CCW_PR1(2,28,0xb2bb,1);			
			 		CCW_PR1(4,28,0xcdea,1);		
			 	 	CCW_PR1(6,28,0xd5fb,1);
			 	 	CCW_PR1(8,28,0xd0c5,1);		
			 		CCW_PR1(10,28,0xcfa2,1);		//��ʾ���ݣ���������Ϣ
				}	
			}
	     }
		subback=0;							//subback ֻ����Ϊ����˵����жϣ��ж���������
	}
	
	else									//����Ϣ
	{
	
			Mgga_pt();
				
	
		if(LANGUAGE==0)						//Ӣ�Ĳ˵�
		{
			CTAB[1]='N';	CTAB[2]='O';	CTAB[4]='M';	CTAB[5]='E';
			CTAB[6]='S';	CTAB[7]='S';	CTAB[8]='A';	CTAB[9]='G';
			CTAB[10]='E';	CTAB[11]='!';
			CW_PR(10,10,12);					//��ʾ���ݣ�NO MESSAGE! 				
		}
		
		else								//���Ĳ˵�
		{
			CCW_PR1(12,100,0xcede,1);
	 		CCW_PR1(14,100,0xd0c5,1);
	 	 	CCW_PR1(16,100,0xcfa2,1);
	 		CCW_PR1(18,100,0x1780,0);		//��ʾ���ݣ�����Ϣ��
		}
					
	}
	
//	      SYSTAB[2]=0x07;

//		for(k=0;k<4500;k++)MessagePoint[k]=0;
}

//********************************************/
/*���ܣ����°�����������ʵ����Ϣ�����»���
��ڲ�������
���ڲ�������
/*********************************************/
void Message_Updn();
void Message_Updn()
{
//    maske=0;
//    maskc=0;
	if(Messagesavetop[(uint32)Messagetoprank[Messagenownumber]].frequency==2)
	{
		if (G_Key==UP&&BUFFER[0]>1)				//�Ϸ�һ��
		{
            maske=0;
            maskc=0;
			CLEAR1();
			Mgga_pt();

							
			Message_toppaint();				//ͷ��Ϣ���ݵ���ʾ
			
	//		MessageDisplay(BUFFER[0]);		//��Ϣ������ʾ,BUFFER[0]��Ϊ�ڼ��п�ʼ

			CTAB[1]='M';	CTAB[2]='S';	CTAB[3]='G';	CTAB[5]='L';	CTAB[6]='I';
			CTAB[7]='N';	CTAB[8]='E';	CTAB[9]='S';	CTAB[10]=':';
			CTAB[14]='/';
			CW_PR(0,19,15); 					//�ַ�����ʾ
			        			
//			Message_line();
			G_Key=0;			
			BUFFER[0]--;
			MessageDisplay(BUFFER[0]);	//ˢ��ҳ������
			Message_line();						//ˢ������
        	run_tip();
		}

	/*�˴��޸ķ��е����ã�Ӣ�Ķ�Ӧ13��һҳ�����Ļ���Ҫ��������*/	
		else if (G_Key==DOWN&&(BUFFER[0]+9)<=LINE)	//�·�һ��
		{
            maske=0;
            maskc=0;
			CLEAR1();
			Mgga_pt();
							
			Message_toppaint();				//ͷ��Ϣ���ݵ���ʾ
			
		//		MessageDisplay(BUFFER[0]);		//��Ϣ������ʾ,BUFFER[0]��Ϊ�ڼ��п�ʼ

			CTAB[1]='M';	CTAB[2]='S';	CTAB[3]='G';	CTAB[5]='L';	CTAB[6]='I';
			CTAB[7]='N';	CTAB[8]='E';	CTAB[9]='S';	CTAB[10]=':';
			CTAB[14]='/';
			CW_PR(0,19,15); 					//�ַ�����ʾ
			        			
//			Message_line();
			G_Key=0;		
			BUFFER[0]++;
			MessageDisplay(BUFFER[0]);	//ˢ��ҳ������
			Message_line();						//ˢ������	
			run_tip();		
		}
	}
	else
	{
		if (G_Key==UP&&BUFFER[0]>1)				//�Ϸ�һ��
		{
            maske=0;
            maskc=0;
			CLEAR1();
			Mgga_pt();
			Message_toppaint();				//ͷ��Ϣ���ݵ���ʾ
			
	//		MessageDisplay(BUFFER[0]);		//��Ϣ������ʾ,BUFFER[0]��Ϊ�ڼ��п�ʼ

			CTAB[1]='M';	CTAB[2]='S';	CTAB[3]='G';	CTAB[5]='L';	CTAB[6]='I';
			CTAB[7]='N';	CTAB[8]='E';	CTAB[9]='S';	CTAB[10]=':';
			CTAB[14]='/';
			CW_PR(0,19,15); 					//�ַ�����ʾ
			        			
//			Message_line();
			G_Key=0;			
			BUFFER[0]--;
			MessageDisplay(BUFFER[0]);	//ˢ��ҳ������
			Message_line();						//ˢ������
			run_tip();
		}

	/*�˴��޸ķ��е����ã�Ӣ�Ķ�Ӧ13��һҳ�����Ļ���Ҫ��������*/	
		else if (G_Key==DOWN&&(BUFFER[0]+17)<=LINE)	//�·�һ��
		{
            maske=0;
            maskc=0;
			CLEAR1();
			Mgga_pt();

							
			Message_toppaint();				//ͷ��Ϣ���ݵ���ʾ
			
	//		MessageDisplay(BUFFER[0]);		//��Ϣ������ʾ,BUFFER[0]��Ϊ�ڼ��п�ʼ

			CTAB[1]='M';	CTAB[2]='S';	CTAB[3]='G';	CTAB[5]='L';	CTAB[6]='I';
			CTAB[7]='N';	CTAB[8]='E';	CTAB[9]='S';	CTAB[10]=':';
			CTAB[14]='/';
			CW_PR(0,19,15); 					//�ַ�����ʾ
			        			
//			Message_line();
			G_Key=0;		
			BUFFER[0]++;
			MessageDisplay(BUFFER[0]);	//ˢ��ҳ������
			Message_line();						//ˢ������	
			run_tip();
		}
	}
}

//****************************************************/
/*���ܣ����Ұ�����������ʵ����һ������һ����Ϣ���л�
��ڲ�������
���ڲ�������
/*****************************************************/
void Message_Leftright();//��Ϣ����
void Message_Leftright()
{

	sword i,j,k;
	if(G_Key==LEFT||G_Key==RIGHT)
	{
	    maske=0;
	    maskc=0;
		if (G_Key==RIGHT&&(Returntype==1||Returntype==0||Returntype==3))		//�洢��Ϣ���Ϸ���Ϣ����
		{
			G_Key=0;	
			if(Messagenownumber>0) 	//���Խ����Ϸ�����
			{
				CLEAR1();			//��һ���Ͷ����Ĵ洢�ռ�
				Messagenownumber=Messagenownumber-1;		
				Message_Paintintial();				
			}
			
		}
	
		if (G_Key==RIGHT&&(Returntype==2||Returntype==4))							//������Ϣ���Ϸ���Ϣ����
		{
			G_Key=0;
			for(i=Messagenownumber-1;i>=0;i--)
			{
				if(Messagesavetop[Messagetoprank[i]].lock==1)	//���Խ����Ϸ�����
				{
					CLEAR1();			//��һ���Ͷ����Ĵ洢�ռ�
					Messagenownumber=i;		
					Message_Paintintial();	
					break;	
				}
			}
			

		}
		
		
		if (G_Key==LEFT&&(Returntype==1||Returntype==0||Returntype==3))		//�洢��Ϣ������·���Ϣ����
		{
			G_Key=0;	
			if(Messagenownumber<Messageinfo.savenumber[0]-1) 	//���Խ����·�����
			{
				CLEAR1();			//��һ���Ͷ����Ĵ洢�ռ�
				Messagenownumber=Messagenownumber+1;		
				Message_Paintintial();				
			}
			
		}
	
		if (G_Key==LEFT&&(Returntype==2||Returntype==4))						//������Ϣ������·���Ϣ����
		{
			G_Key=0;	
			for(i=Messagenownumber+1;i<Messageinfo.savenumber[0];i++)
			{
				if(Messagesavetop[Messagetoprank[i]].lock==1)	//���Խ����·�����
				{
					CLEAR1();			//��һ���Ͷ����Ĵ洢�ռ�
					Messagenownumber=i;		
					Message_Paintintial();
					break;					
				}
			}
		}
       run_tip();
	}
}	

//****************************************************/
/*���ܣ�STAR��������������Ϣ�Ӳ˵���ת
��ڲ�������
���ڲ�������
/*****************************************************/
void Message_Messagesubmenu();
void Message_Messagesubmenu()
{
	if (G_Key==STAR)
	{	
		ProtectData();
		CLEAR2();		//�����Ӳ˵������������
		G_Key=0;
		FLAG=0;			//����Message����ѭ������������״̬����
		STATE=11;	//��ǰҳ����Ϣ������Ϣ�Ӳ˵����� MessageSubmenu
	}
}


//****************************************************/
/*���ܣ�MENU��DISP������������ʵ��һ���˵�����ת
��ڲ�������
���ڲ�������
/*****************************************************/
void Message_Menuchange();
void Message_Menuchange()
{
	sword i;
	if(G_Key==MENU||G_Key==DISP)
	{
	
		if(Returntype!=0)	//��ʾ����Ϣ�洢�˵����룬��û�з�����Ϣ�洢�˵��������������
		{
			BUFFERPRO[0]=0; //��������
			BUFFERPRO[1]=0;
			Returntype=0;   //���ر������
	//		Messageinfo.nownumber[0]=Messageinfo.savenumber[0]-1;//�洢��Ϣָ�����һ��			
		}
		
/*		if(Returntype==2||Returntype==4)
		{
			BUFFERPRO[0]=0;	//��������
			Returntype=0;	//���ر������
			for(i=Messageinfo.savenumber[0]-1;i>=0;i--)
			{
				if(Messagesavetop[Messagetoprank[i]].lock==1) break;
			}
			Messageinfo.nownumber[1]=i;//������Ϣָ�����һ��			
		}*/
	

		if (G_Key==MENU)	//��ת����MainMenu���棬��ڲ���0
		{	
			STATE=4;
			State4parameter=0;
		}
			
		if (G_Key==DISP)	//��ת����SaveMenu���棬��ڲ���0
		{		
			STATE=2;
			State2parameter=0;
		}
		
		G_Key=0;			//��������
		BUFFER[0]=0;		
		FLAG=0;				//����ѭ��
	}
}


//**************************************************************/
/*���ܣ�CLR����������������Returntype�������洢�˵��������˵�
��ڲ�������
���ڲ�������
/***************************************************************/
void Message_Return();
void Message_Return()
{
	sword i=0;
	if (G_Key==CLR)			//���ؼ���Чֻ���ڽ���ý�����Ǵ洢�˵��������˵�
	{	
		G_Key=0;
		if (Returntype==1||Returntype==2)	//���ص��洢�˵�
		{	
				
			BUFFER[0]=BUFFERPRO[0];	//��֮ǰ������Ϣ���ݲ˵��������BUFFERPRO[0]����BUFFER[0]
			BUFFERPRO[0]=0;		   	//��ʱBUFFERPRO[0]��������				
			FLAG=0;					//����ѭ��
			STATE=2;
			State2parameter=Returntype;
			Messageinfo.nownumber[Returntype-1]=BUFFERPRO[1];		//�Ӳ˵����淵��������洢�˵�,Messageinfo.nownumber[1]��Ҫ�ı�			
			BUFFERPRO[1]=0;
			Returntype=0;		   	//���ر������
		}
		
		if(Returntype==3||Returntype==4)	//��ʱ������Ϣʱ����Ϣɾ���������
		{
	/*		if(Returntype==3)	//��ʾ����Ϣ�洢�˵����룬��û�з�����Ϣ�洢�˵��������������
			{
				if(Messageinfo.savenumber[0]>0)
				Messageinfo.nownumber[0]=Messageinfo.savenumber[0]-1;//�洢��Ϣָ�����һ��			
				else
				Messageinfo.nownumber[0]=0;
			}
			
			else
			{

				if(Messageinfo.locknumber[0]>0)
				{
					for(i=Messageinfo.savenumber[0]-1;i>=0;i--)
					{
						if(Messagesavetop[Messagetoprank[i]].lock==1) break;
					}
					Messageinfo.nownumber[1]=i;//������Ϣָ�����һ��					
				}
				else
				Messageinfo.nownumber[1]=0;
			
			}*/
		
			BUFFERPRO[0]=0;		   	//��ʱBUFFERPRO[0]��������
			BUFFERPRO[1]=0;				
			FLAG=0;					//����ѭ��
			STATE=2;
			State2parameter=Returntype;
			Returntype=0;		   	//���ر������
						
		}
	}
	
}

//**************************************************************/
/*���ܣ�ENT������������ȥ����Ϣ��ǹ���
		������Ϊ����Ϣ������ENT��ȥ������Ϣ���
��ڲ�������
���ڲ�������
/***************************************************************/
void Message_Dealing();
void Message_Dealing()
{
	word address;
	if (G_Key==ENT)
	{   
		G_Key=0;
    DISABLEIRQA();
		if(Messagesavetop[Messagetoprank[Messagenownumber]].read==1)	//��ϢΪ����Ϣ
		{
	//		MessageProcess|=0x01;		//��ʱ�ڽ�����Ϣ�������
			Messagesavetop[Messagetoprank[Messagenownumber]].read=0;	//�޸�����Ϣ����Ϊ0
			W_CLEARMESSAGE(37,1);						//ȥ������Ϣ���
			Unread--;									//δ����Ϣ����һ
			Write_Int_Eprm(UNREAD_MSG,Unread);			//�洢Unread��Eprom
			address=Messagetoprank[Messagenownumber]*MESSTYPELENGTH+11;	//readλ��Erpomλ��
			Write_Char_Eprm(address,Messagesavetop[Messagetoprank[Messagenownumber]].read);			//ͷ�ļ���Ϣ��readλ��Erpom�洢
	//		MessageProcess&=0xfe;			//��Ϣ���������ϣ�bit1λ��0
		}
   ENABLEIRQA();
	}	
}

//************************************************************************/
/*���ܣ�Message������ʾ�洢��Ϣ��������Ϣ������ڲ���Ϊ0��1��ʱ��ʾ�洢��Ϣ
		����ڲ���Ϊ2��ʾ����������Ϣ���ò���Returntype�жϲ�����¼��
		Returntype��������Ϊ����������ӽ��棬ֻ�������������棬
		����һ������ʱ�ò������޸ġ��ڽ��뱾��������ӽ����������Ϣ�Ĵ���
		����Messagenownumber����Ϊ׼���������Ա������
��ڲ�����byte�ͣ���¼�Ӻβ˵�����
���ڲ�������
/*************************************************************************/

void RunMessage(byte into)
{
  	sword t;
    unsigned char print_temp;
    maske=0;
    maskc=0;
  	subback=into; 						//�����ж��Ƿ���Ӳ˵�����
//  	print_sum=0;
  	if(subback!=10) 
  	{
	  	Returntype=into;				//���ڼ�¼����ʱ�Ӻβ˵���ȥ
	   	if(Returntype==1||Returntype==0||Returntype==3)//�Ӵ洢����� 
		{
			Messagenownumber=Messageinfo.nownumber[0];//�ڽ��յ��µ���Ϣ���ȸı�nownumber�������
		}
		
		else
		{
			Messagenownumber=Messageinfo.nownumber[1];//�����������
		}
  	}
  	IntialLCD(1);
	Message_Paintintial();				//��Ϣ����ˢ��
//    COPCTR=0xAAAA;
//	COPCTR=0x5555;		
	if(flag_new_message==1)
	{
	now_printing=0;
		flag_new_message=0;
		if(Receiverset[1]==1)
		{
			print_temp=0;
//	while(print_temp<print_sum)
//	{
		PrtStart->xulie=Messagetoprank[Messageinfo.savenumber[0]-1];
		ReadPrtMsg();	//��FPGA��ȡ�����ӡ��Ϣ
		StartRS232(USART3);	//������ӡ��
		Checkinfo.Printover = 0;
		while(Checkinfo.Printover==0)
		{
       DataTran(USART3);			
		};
//		print_temp++;
//	}
		}
		if(flag_auto_iec==1)
		    iec_send_alarm();
		if(flag_auto_iec==1)
			iec_send();
     	else if(nrmflag_on==1&&((nrmareamk[Messagesavetop[Messagetoprank[Messagenownumber]].mark[0]-'A']==1)&&
    	    	   (nrmtypemk[Messagesavetop[Messagetoprank[Messagenownumber]].mark[1]-'A']==1)&&
                   (Messagesavetop[Messagetoprank[Messagenownumber]].frequency==nrmfre)))
		iec_send_message(Messagetoprank[Messagenownumber]);
		StartRS232_iec();
	}
	while(FLAG)
	{
//	    COPCTR=0xAAAA;
//	    COPCTR=0x5555;	
		if((Messageinfo.savenumber[0]&&(Returntype==0||Returntype==1||Returntype==3))||
	   		(Messageinfo.locknumber[0]&&(Returntype==2||Returntype==4)))	//��������Ϣʱ�����к�������Ч
		{
			Message_Updn();
			Message_Leftright();
			Message_Dealing();			
			Message_Messagesubmenu();
		}
//		t=IRQP1;
		Message_Return();
		Message_Menuchange();
	   	run_tip();
	}
  	
}