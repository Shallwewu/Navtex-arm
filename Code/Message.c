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
#define FlashmapSize_Word	 0x0400		//存储信息的块大小1K字
//extern volatile byte LINE;									//统计所显示信息的总行数
/* BUFFER[0]表示液晶界面首行在信息正文中位置，BUFFER[1]表示当前所指的行在信息正文中位置*/


//********************************************/
/*功能；完成图形区的显示
入口参数：无
出口参数：无
/*********************************************/
void Mgga_pt();
void Mgga_pt()	
{
//	CLEARXLINE(0,39,22);			//完成图形区显示
				
//	XLINE(0,39,17);
//	W_YLINE(0,0,239);
//	W_YLINE(309,17,229);
//	W_YLINE(319,0,239);
	CLEARXLINE(0,39,17);			//完成图形区显示
	CLEARXLINE(0,39,22);
	CLEARXLINE(0,39,17);			//完成图形区显示
				
		//		XLINE(0,39,20);
			    XLINE(0,39,22);
				W_YLINE(0,0,239);
				W_YLINE(309,22,225);
				W_YLINE(319,0,239);
				
				 W_XLINE(0,319,225);		//调整底边框	
                 W_CLEARXLINE(1,318,230);
}

//********************************************/
/*功能；完成三个英文字符到一个中文汉字的转换
入口参数：三个英文字符的首字母地址
出口参数：LCD机内码
/*********************************************/
u16 eng_to_lcd(char *p)
{
	u16 lcd;
	u16 temp,temp1,temp2;
	temp=(*p-'A')*676+(*(p+1)-'A')*26+(*(p+2)-'A');	//计算总值
	temp1=temp/94+0xa1;								//计算区码+0xA0,temp/94为区码-1
	temp2=temp%94+0xa1;								//计算位码+0xA0,temp/94为位码-1
	lcd=(temp1<<8)+temp2;							//合成GB2312-1980机内码
	return lcd;
}
//********************************************/
/*功能；完成上下移动标记和左下角信息的显示数
入口参数：无
出口参数：无
/*********************************************/
void Message_line();	
void Message_line()
{

	DISASCIII(15,19,LINE);			//显示总信息数
	DISASCIII(11,19,BUFFER[0]);		//显示当前信息数
		
}
//********************************************/
/*功能；完成信息表头的显示
入口参数：无
出口参数：无
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
						case(34):temp->mark[i]='H';break;//' "  '双引号
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
						case(39):temp->mark[i]='S';break;//' ' '单引号
						case('5'):temp->mark[i]='T';break;
						case('7'):temp->mark[i]='U';break;
						case('='):temp->mark[i]='V';break;
						case('2'):temp->mark[i]='W';break;
						case('/'):temp->mark[i]='X';break;
						case('6'):temp->mark[i]='Y';break;
						case('+'):temp->mark[i]='Z';break;
						default:break;
					
	}*/
	for(i=0;i<4;i++) 				//信息标记符号
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
						case(34):CW_PR3(3+i,1,'H');break;//' "  '双引号
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
						case(39):CW_PR3(3+i,1,'S');break;//' ' '单引号
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
	switch(msgtop.frequency)			//频率显示完成
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
	
	DISASCII(21,1,msgtop.date[0]);  	//年
	CW_PR3(23,1,'/');	
	DISASCII(24,1,msgtop.date[1]);  	//月
	CW_PR3(26,1,'/');
	DISASCII(27,1,msgtop.date[2]);	//日
	
	DISASCII(31,1,msgtop.time[0]);	//小时
	CW_PR3(33,1,':');	
	DISASCII(34,1,msgtop.time[1]);	//分钟
	
	if(msgtop.read==1) 				//未读标记的显示
	{
		W_NEWMESSAGE(37,1);
	}							
	else 	
	{
		W_CLEARMESSAGE(37,1);
	}
	
}

//********************************************/
/*功能；信息界面的显示函数
入口参数：无
出口参数：无
/*********************************************/
void Message_Paintintial();
void Message_Paintintial()
{   
  	word zishu=0,i=0,mountbyte=0,temp,temp_end,i_temp,mountbyte_lcd=0,k=0;
  	sword chresult;//中文码元对应情况：0：错字符 1：少字符 2：多字符
  	byte t;
  	
  	
  	

  	
//    SYSTAB[2]=0x0b;
	if((Messageinfo.savenumber[0]&&(Returntype==0||Returntype==1||Returntype==3))||
	   (Messageinfo.locknumber[0]&&(Returntype==2||Returntype==4)))			//接收机内有信息存在
	{
		if(subback==10) RecoverData();		//子界面返回，恢复子界面覆盖的数据
		else
		{
			CLEAR1();				  				  	
			MessagePoint[0]=MessagePoint[1]=MessagePoint[3]=NULL;
			IICRead_ONE_MEHE((Messagetoprank[Messagenownumber])*((word)MESSTYPELENGTH),&msgtop);
			ReadMessFlash((msgtop.flashadd)*(uint32)FlashmapSize_Word,MessagePoint);//把信息读入内存
			mountbyte=msgtop.amount;				//获取信息的数量
		//	mountbyte=mountbyte<<8;
		//	t=(byte)MessagePoint[1];
		//	mountbyte+=t;					//mountbyte为实际字符数+1


/*添加信息末尾显示程序zzy@2010-6-9*/
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
						case(34):MessagePoint[i]='H';break;//' "  '双引号
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
						case(39):MessagePoint[i]='S';break;//' ' '单引号
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
						chresult=32;                           //\r,\n照常转化




					else if((MessagePoint[i]<='M')&&(MessagePoint[i]>='A'))
					{
						if((MessagePoint[i+1]<='Z')&&(MessagePoint[i+1]>='A'))
						{
							if((MessagePoint[i+2]<='Z')&&(MessagePoint[i+2]>='A'))
							{
									//if(MessagePoint[i+2]==MessagePoint[i+5]==MessagePoint[i+8]=='A')chresult=11;
									chresult=30;            //三个字母符合转化要求
							}
							                      
							else if(((MessagePoint[i+3]<='Z')&&(MessagePoint[i+3]>='N'))&&((MessagePoint[i+4]<='M')&&(MessagePoint[i+4]>='A'))&&((MessagePoint[i+6]<='Z')&&(MessagePoint[i+6]>='N')))
								chresult=23;                     //多第三个字符
							else 
								chresult=03;                     //错第三个字符
						}
						else
						{
							if((MessagePoint[i+2]<='Z')&&(MessagePoint[i+2]>='A'))
							{
								if(((MessagePoint[i+3]<='Z')&&(MessagePoint[i+3]>='N'))&&((MessagePoint[i+4]<='M')&&(MessagePoint[i+4]>='A'))&&((MessagePoint[i+7]<='M')&&(MessagePoint[i+7]>='A')))
									chresult=22;                 //多第二个字符
								else 
									chresult=02;                 //错第二个字符
							}
							else
								chresult=0;                     //错二三个字符				
						}
					}
					else 
					{
						if(((MessagePoint[i]<='Z')&&(MessagePoint[i]>='N'))&&((MessagePoint[i+2]<='M')&&(MessagePoint[i+2]>='A'))&&((MessagePoint[i+3]<='Z')&&(MessagePoint[i+3]>='N')))
							chresult=11;                       //少第一个字符
						else if(((MessagePoint[i+1]<='M')&&(MessagePoint[i+1]>='A'))&&((MessagePoint[i+3]<='Z')&&(MessagePoint[i+3]>='N'))&&((MessagePoint[i+4]<='M')&&(MessagePoint[i+4]>='A')))
							chresult=21;                       //多第一个字符
						else if(((MessagePoint[i+1]<='Z')&&(MessagePoint[i+1]>='A'))&&((MessagePoint[i+2]<='Z')&&(MessagePoint[i+2]>='A'))&&((MessagePoint[i+3]<='M')&&(MessagePoint[i+3]>='A')))
							chresult=01;                       //错第一个字符
						else 
							chresult=0;                         //错两个字符以上
						if(MessagePoint[i+4]=='A'&&MessagePoint[i+7]=='A'&&MessagePoint[i+10]=='A')
						    chresult=21;			
					}
					if(MessagePoint[i]=='A'&&((MessagePoint[i+1]>='H'&&MessagePoint[i+1]<='K')||(MessagePoint[i-3]=='A'&&MessagePoint[i-2]>='H'&&MessagePoint[i-2]<='K')))
					{
					    if(MessagePoint[i+2]=='A'&&MessagePoint[i+3]>='H'&&MessagePoint[i+3]<='K'&&MessagePoint[i+5]=='A'&&MessagePoint[i+6]>='H'&&MessagePoint[i+6]<='I')
					    chresult=13;
					}

					switch(chresult)                            //算法处理
					{
						case(30):                               //正常转化三个字母                     
							chinese[mountbyte_lcd++]=eng_to_lcd(&MessagePoint[i]);
							/*if(((MessagePoint[i+3]<='M')&&(MessagePoint[i+3]>='A'))&&((MessagePoint[i+4]<='Z')&&(MessagePoint[i+4]>='A'))&&((MessagePoint[i+5]<='Z')&&(MessagePoint[i+5]>='A')))         //建立关联表
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
						case(31):                              //‘\r’的转化                         
					//		chinese[mountbyte_lcd++]='\r';
					//		i=i+1;
							break;
						case(32):                              //‘\n’的转化                          
					//		chinese[mountbyte_lcd++]='\n';
					//		i=i+1;
							break;
						case(21):                             //多第一个字符 
							//MessagePoint[i]='*';                                  //调试用                          
							break;
						case(22):                             //多第二个字符
							MessagePoint[i+1]=MessagePoint[i+2];
							MessagePoint[i+2]=MessagePoint[i+3];
							//MessagePoint[i+3]='*';                                 //调试用
							chinese[mountbyte_lcd++]=eng_to_lcd(&MessagePoint[i]);
							i=i+3;
							break;
						case(23):                             //多第三个字符                        
							MessagePoint[i+2]=MessagePoint[i+3];
							//MessagePoint[i+3]='*';                                 //调试用
							chinese[mountbyte_lcd++]=eng_to_lcd(&MessagePoint[i]);
							i=i+3;
							break;
						case(01):                       
						case(02):                       
						case(03): 
	                              //调试用
								chinese[mountbyte_lcd++]=0xa3aa;
					   		i=i+2;                   
							break;
						case(0):
							//MessagePoint[i]=MessagePoint[i+1]=MessagePoint[i+2]='*';                                 //调试用
							chinese[mountbyte_lcd++]=0xa3aa;
					   		i=i+3;  
							break;
						case(13):                              //少第一个字符
					    case(11):                             //少第二个字符
							                    //调试用
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
					chinese[mountbyte_lcd++]=0xcdea;			//'完'
					chinese[mountbyte_lcd++]=0xd5fb;			//'整'
					chinese[mountbyte_lcd++]=0xd0c5;			//'信'
					chinese[mountbyte_lcd++]=0xcfa2;			//'息'
					chinese[mountbyte_lcd++]=0xa3a9;			//')'
					for(i_temp=0;i_temp<21;i_temp++)		//清除末行尾部显示
						chinese[mountbyte_lcd++]=0xa1a1;
					mountbyte_lcd=mountbyte_lcd-21;	
				}
				else if((MessagePoint[mountbyte-2]=='N')&&		//针对福州的信息添加
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
					chinese[mountbyte_lcd++]=0xcdea;			//'完'
					chinese[mountbyte_lcd++]=0xd5fb;			//'整'
					chinese[mountbyte_lcd++]=0xd0c5;			//'信'
					chinese[mountbyte_lcd++]=0xcfa2;			//'息'
					chinese[mountbyte_lcd++]=0xa3a9;			//')'
					for(i_temp=0;i_temp<21;i_temp++)		//清除末行尾部显示
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
					chinese[mountbyte_lcd++]=0xb2bb;			//'不'
					chinese[mountbyte_lcd++]=0xcdea;			//'完'
					chinese[mountbyte_lcd++]=0xd5fb;			//'整'
					chinese[mountbyte_lcd++]=0xd0c5;			//'信'
					chinese[mountbyte_lcd++]=0xcfa2;			//'息'
					chinese[mountbyte_lcd++]=0xa3a9;			//')'
					for(i_temp=0;i_temp<21;i_temp++)		//清除末行尾部显示
						chinese[mountbyte_lcd++]=0xa1a1;
					mountbyte_lcd=mountbyte_lcd-21;	
				}                                        
	/*信息末尾代码结束*/				
			  	BUFFER[0]=1;					//
		  		LinePoint2[1]=&chinese[0];	//
		  		LINE=1;
		  		i=0;							
				/*中文需要重新统计行数，根据页面设置规定*/
		  		while(i<mountbyte_lcd)
		  		{
					if(chinese[i]=='\r')		//遇到回车符则行数加一，字数清零，同时i也得++，因NAVTEX中编码把
					{	
//						i++;	//在NAVTEX编码中回车和换行是同时出现的，直接跳过换行的处理
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
					else if(chinese[i]==9) 	//遇到TAB键则字数增加四个
						zishu+=4;*///TAB功能未添加
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
					
					if(zishu>=18)			//字数满一行则行数加一，字数清零，字数出现超过37可能碰到TAB键
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
								
				Message_toppaint();				//头信息内容的显示
				
				MessageDisplay(BUFFER[0]);		//信息正文显示,BUFFER[0]中为第几行开始

				CTAB[1]='M';	CTAB[2]='S';	CTAB[3]='G';	CTAB[5]='L';	CTAB[6]='I';
				CTAB[7]='N';	CTAB[8]='E';	CTAB[9]='S';	CTAB[10]=':';
				CTAB[14]='/';
				CW_PR(0,19,15); 					//字符区显示
				        			
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
					for(i_temp=0;i_temp<21;i_temp++)		//清除末行尾部显示
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
					for(i_temp=0;i_temp<17;i_temp++)		//清除末行尾部显示
						MessagePoint[temp_end++]=' ';
					mountbyte=mountbyte+26;			
				}               
			


	/*信息末尾代码结束*/				
			  	BUFFER[0]=1;					//BUFFER[0]用于LCD当前显示页的第一行在整条信息中的位置
		  		LinePoint[1]=&MessagePoint[6];	//6 去掉之前的信息数和岸台信息标识
		  		LINE=1;
		  		i=6;							
				/*中文需要重新统计行数，根据页面设置规定*/
		  		while(i<mountbyte-1)
		  		{
					if(((MessagePoint[i]==13)&&(MessagePoint[i+1]==10))||((MessagePoint[i]==10)&&(MessagePoint[i+1]==13)))		//遇到回车符则行数加一，字数清零，同时i也得++，因NAVTEX中编码把
					{	
						i++;	//在NAVTEX编码中回车和换行是同时出现的，直接跳过换行的处理
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
					else if(MessagePoint[i]==9) 	//遇到TAB键则字数增加四个
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
					else if(zishu>=37)			//字数满一行则行数加一，字数清零，字数出现超过37可能碰到TAB键
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
								
				Message_toppaint();				//头信息内容的显示
				
				MessageDisplay(BUFFER[0]);		//信息正文显示,BUFFER[0]中为第几行开始

				CTAB[1]='M';	CTAB[2]='S';	CTAB[3]='G';	CTAB[5]='L';	CTAB[6]='I';
				CTAB[7]='N';	CTAB[8]='E';	CTAB[9]='S';	CTAB[10]=':';
				CTAB[14]='/';
				CW_PR(0,19,15); 					//字符区显示
				        			
				Message_line();
			}
			else
			{
				Mgga_pt();
				
				Message_toppaint();
			
				if(LANGUAGE==0)						//英文菜单
				{
					CTAB[1]='I';	CTAB[2]='N';	CTAB[3]='C';	CTAB[4]='O';
					CTAB[5]='M';	CTAB[6]='P';	CTAB[7]='L';	CTAB[8]='E';
					CTAB[9]='T';	CTAB[10]='E';	CTAB[11]=' ';	CTAB[12]='M';
					CTAB[13]='E';	CTAB[14]='S';	CTAB[15]='S';	CTAB[16]='A';
					CTAB[17]='G';	CTAB[18]='E';	
					CW_PR(1,3,19);					//提示内容：INCOMPLETE MESSAGE 				
				}
				
				else								//中文菜单
				{
					CCW_PR1(2,28,0xb2bb,1);			
			 		CCW_PR1(4,28,0xcdea,1);		
			 	 	CCW_PR1(6,28,0xd5fb,1);
			 	 	CCW_PR1(8,28,0xd0c5,1);		
			 		CCW_PR1(10,28,0xcfa2,1);		//提示内容：不完整信息
				}	
			}
	     }
		subback=0;							//subback 只需作为进入菜单的判断，判断完则清零
	}
	
	else									//无信息
	{
	
			Mgga_pt();
				
	
		if(LANGUAGE==0)						//英文菜单
		{
			CTAB[1]='N';	CTAB[2]='O';	CTAB[4]='M';	CTAB[5]='E';
			CTAB[6]='S';	CTAB[7]='S';	CTAB[8]='A';	CTAB[9]='G';
			CTAB[10]='E';	CTAB[11]='!';
			CW_PR(10,10,12);					//提示内容：NO MESSAGE! 				
		}
		
		else								//中文菜单
		{
			CCW_PR1(12,100,0xcede,1);
	 		CCW_PR1(14,100,0xd0c5,1);
	 	 	CCW_PR1(16,100,0xcfa2,1);
	 		CCW_PR1(18,100,0x1780,0);		//提示内容：无信息！
		}
					
	}
	
//	      SYSTAB[2]=0x07;

//		for(k=0;k<4500;k++)MessagePoint[k]=0;
}

//********************************************/
/*功能；上下按键处理函数，实现信息的上下换行
入口参数：无
出口参数：无
/*********************************************/
void Message_Updn();
void Message_Updn()
{
//    maske=0;
//    maskc=0;
	if(Messagesavetop[(uint32)Messagetoprank[Messagenownumber]].frequency==2)
	{
		if (G_Key==UP&&BUFFER[0]>1)				//上翻一行
		{
            maske=0;
            maskc=0;
			CLEAR1();
			Mgga_pt();

							
			Message_toppaint();				//头信息内容的显示
			
	//		MessageDisplay(BUFFER[0]);		//信息正文显示,BUFFER[0]中为第几行开始

			CTAB[1]='M';	CTAB[2]='S';	CTAB[3]='G';	CTAB[5]='L';	CTAB[6]='I';
			CTAB[7]='N';	CTAB[8]='E';	CTAB[9]='S';	CTAB[10]=':';
			CTAB[14]='/';
			CW_PR(0,19,15); 					//字符区显示
			        			
//			Message_line();
			G_Key=0;			
			BUFFER[0]--;
			MessageDisplay(BUFFER[0]);	//刷新页面内容
			Message_line();						//刷新行数
        	run_tip();
		}

	/*此处修改翻行的设置，英文对应13行一页，中文还需要进行设置*/	
		else if (G_Key==DOWN&&(BUFFER[0]+9)<=LINE)	//下翻一行
		{
            maske=0;
            maskc=0;
			CLEAR1();
			Mgga_pt();
							
			Message_toppaint();				//头信息内容的显示
			
		//		MessageDisplay(BUFFER[0]);		//信息正文显示,BUFFER[0]中为第几行开始

			CTAB[1]='M';	CTAB[2]='S';	CTAB[3]='G';	CTAB[5]='L';	CTAB[6]='I';
			CTAB[7]='N';	CTAB[8]='E';	CTAB[9]='S';	CTAB[10]=':';
			CTAB[14]='/';
			CW_PR(0,19,15); 					//字符区显示
			        			
//			Message_line();
			G_Key=0;		
			BUFFER[0]++;
			MessageDisplay(BUFFER[0]);	//刷新页面内容
			Message_line();						//刷新行数	
			run_tip();		
		}
	}
	else
	{
		if (G_Key==UP&&BUFFER[0]>1)				//上翻一行
		{
            maske=0;
            maskc=0;
			CLEAR1();
			Mgga_pt();
			Message_toppaint();				//头信息内容的显示
			
	//		MessageDisplay(BUFFER[0]);		//信息正文显示,BUFFER[0]中为第几行开始

			CTAB[1]='M';	CTAB[2]='S';	CTAB[3]='G';	CTAB[5]='L';	CTAB[6]='I';
			CTAB[7]='N';	CTAB[8]='E';	CTAB[9]='S';	CTAB[10]=':';
			CTAB[14]='/';
			CW_PR(0,19,15); 					//字符区显示
			        			
//			Message_line();
			G_Key=0;			
			BUFFER[0]--;
			MessageDisplay(BUFFER[0]);	//刷新页面内容
			Message_line();						//刷新行数
			run_tip();
		}

	/*此处修改翻行的设置，英文对应13行一页，中文还需要进行设置*/	
		else if (G_Key==DOWN&&(BUFFER[0]+17)<=LINE)	//下翻一行
		{
            maske=0;
            maskc=0;
			CLEAR1();
			Mgga_pt();

							
			Message_toppaint();				//头信息内容的显示
			
	//		MessageDisplay(BUFFER[0]);		//信息正文显示,BUFFER[0]中为第几行开始

			CTAB[1]='M';	CTAB[2]='S';	CTAB[3]='G';	CTAB[5]='L';	CTAB[6]='I';
			CTAB[7]='N';	CTAB[8]='E';	CTAB[9]='S';	CTAB[10]=':';
			CTAB[14]='/';
			CW_PR(0,19,15); 					//字符区显示
			        			
//			Message_line();
			G_Key=0;		
			BUFFER[0]++;
			MessageDisplay(BUFFER[0]);	//刷新页面内容
			Message_line();						//刷新行数	
			run_tip();
		}
	}
}

//****************************************************/
/*功能；左右按键处理函数，实现上一条和下一条信息的切换
入口参数：无
出口参数：无
/*****************************************************/
void Message_Leftright();//信息翻动
void Message_Leftright()
{

	sword i,j,k;
	if(G_Key==LEFT||G_Key==RIGHT)
	{
	    maske=0;
	    maskc=0;
		if (G_Key==RIGHT&&(Returntype==1||Returntype==0||Returntype==3))		//存储信息的上翻信息处理
		{
			G_Key=0;	
			if(Messagenownumber>0) 	//可以进行上翻处理
			{
				CLEAR1();			//清一区和二区的存储空间
				Messagenownumber=Messagenownumber-1;		
				Message_Paintintial();				
			}
			
		}
	
		if (G_Key==RIGHT&&(Returntype==2||Returntype==4))							//锁定信息的上翻信息处理
		{
			G_Key=0;
			for(i=Messagenownumber-1;i>=0;i--)
			{
				if(Messagesavetop[Messagetoprank[i]].lock==1)	//可以进行上翻处理
				{
					CLEAR1();			//清一区和二区的存储空间
					Messagenownumber=i;		
					Message_Paintintial();	
					break;	
				}
			}
			

		}
		
		
		if (G_Key==LEFT&&(Returntype==1||Returntype==0||Returntype==3))		//存储信息处理的下翻信息处理
		{
			G_Key=0;	
			if(Messagenownumber<Messageinfo.savenumber[0]-1) 	//可以进行下翻处理
			{
				CLEAR1();			//清一区和二区的存储空间
				Messagenownumber=Messagenownumber+1;		
				Message_Paintintial();				
			}
			
		}
	
		if (G_Key==LEFT&&(Returntype==2||Returntype==4))						//锁定信息处理的下翻信息处理
		{
			G_Key=0;	
			for(i=Messagenownumber+1;i<Messageinfo.savenumber[0];i++)
			{
				if(Messagesavetop[Messagetoprank[i]].lock==1)	//可以进行下翻处理
				{
					CLEAR1();			//清一区和二区的存储空间
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
/*功能；STAR按键处理函数，信息子菜单跳转
入口参数：无
出口参数：无
/*****************************************************/
void Message_Messagesubmenu();
void Message_Messagesubmenu()
{
	if (G_Key==STAR)
	{	
		ProtectData();
		CLEAR2();		//弹出子菜单区域数据清空
		G_Key=0;
		FLAG=0;			//结束Message界面循环，跳入其它状态界面
		STATE=11;	//当前页有信息弹出信息子菜单界面 MessageSubmenu
	}
}


//****************************************************/
/*功能；MENU和DISP按键处理函数，实现一级菜单间跳转
入口参数：无
出口参数：无
/*****************************************************/
void Message_Menuchange();
void Message_Menuchange()
{
	sword i;
	if(G_Key==MENU||G_Key==DISP)
	{
	
		if(Returntype!=0)	//表示从信息存储菜单进入，若没有返回信息存储菜单则配置相关数据
		{
			BUFFERPRO[0]=0; //保护清零
			BUFFERPRO[1]=0;
			Returntype=0;   //返回标记清零
	//		Messageinfo.nownumber[0]=Messageinfo.savenumber[0]-1;//存储信息指向最后一条			
		}
		
/*		if(Returntype==2||Returntype==4)
		{
			BUFFERPRO[0]=0;	//保护清零
			Returntype=0;	//返回标记清零
			for(i=Messageinfo.savenumber[0]-1;i>=0;i--)
			{
				if(Messagesavetop[Messagetoprank[i]].lock==1) break;
			}
			Messageinfo.nownumber[1]=i;//锁定信息指向最后一条			
		}*/
	

		if (G_Key==MENU)	//跳转进入MainMenu界面，入口参数0
		{	
			STATE=4;
			State4parameter=0;
		}
			
		if (G_Key==DISP)	//跳转进入SaveMenu界面，入口参数0
		{		
			STATE=2;
			State2parameter=0;
		}
		
		G_Key=0;			//按键清零
		BUFFER[0]=0;		
		FLAG=0;				//结束循环
	}
}


//**************************************************************/
/*功能；CLR按键处理函数，根据Returntype返回至存储菜单或锁定菜单
入口参数：无
出口参数：无
/***************************************************************/
void Message_Return();
void Message_Return()
{
	sword i=0;
	if (G_Key==CLR)			//返回键有效只有在进入该界面的是存储菜单或锁定菜单
	{	
		G_Key=0;
		if (Returntype==1||Returntype==2)	//返回到存储菜单
		{	
				
			BUFFER[0]=BUFFERPRO[0];	//把之前进入信息内容菜单所保存的BUFFERPRO[0]赋予BUFFER[0]
			BUFFERPRO[0]=0;		   	//此时BUFFERPRO[0]无用清零				
			FLAG=0;					//结束循环
			STATE=2;
			State2parameter=Returntype;
			Messageinfo.nownumber[Returntype-1]=BUFFERPRO[1];		//从菜单界面返回锁定或存储菜单,Messageinfo.nownumber[1]需要改变			
			BUFFERPRO[1]=0;
			Returntype=0;		   	//返回标记清零
		}
		
		if(Returntype==3||Returntype==4)	//此时解锁信息时有信息删除情况发生
		{
	/*		if(Returntype==3)	//表示从信息存储菜单进入，若没有返回信息存储菜单则配置相关数据
			{
				if(Messageinfo.savenumber[0]>0)
				Messageinfo.nownumber[0]=Messageinfo.savenumber[0]-1;//存储信息指向最后一条			
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
					Messageinfo.nownumber[1]=i;//锁定信息指向最后一条					
				}
				else
				Messageinfo.nownumber[1]=0;
			
			}*/
		
			BUFFERPRO[0]=0;		   	//此时BUFFERPRO[0]无用清零
			BUFFERPRO[1]=0;				
			FLAG=0;					//结束循环
			STATE=2;
			State2parameter=Returntype;
			Returntype=0;		   	//返回标记清零
						
		}
	}
	
}

//**************************************************************/
/*功能；ENT按键处理函数，去除信息标记功能
		若此条为新信息，则按下ENT键去除新信息标记
入口参数：无
出口参数：无
/***************************************************************/
void Message_Dealing();
void Message_Dealing()
{
	word address;
	if (G_Key==ENT)
	{   
		G_Key=0;
    DISABLEIRQA();
		if(Messagesavetop[Messagetoprank[Messagenownumber]].read==1)	//信息为新信息
		{
	//		MessageProcess|=0x01;		//此时在进行信息处理操作
			Messagesavetop[Messagetoprank[Messagenownumber]].read=0;	//修改新信息变量为0
			W_CLEARMESSAGE(37,1);						//去除新信息标记
			Unread--;									//未读信息数减一
			Write_Int_Eprm(UNREAD_MSG,Unread);			//存储Unread于Eprom
			address=Messagetoprank[Messagenownumber]*MESSTYPELENGTH+11;	//read位在Erpom位置
			Write_Char_Eprm(address,Messagesavetop[Messagetoprank[Messagenownumber]].read);			//头文件信息中read位在Erpom存储
	//		MessageProcess&=0xfe;			//信息处理操作完毕，bit1位置0
		}
   ENABLEIRQA();
	}	
}

//************************************************************************/
/*功能；Message界面显示存储信息或锁定信息，当入口参数为0或1此时显示存储信息
		当入口参数为2显示的是锁定信息，用参数Returntype判断并作记录，
		Returntype生存周期为本界面和其子界面，只有再跳出本界面，
		进入一级界面时该参数才修改。在进入本界面和其子界面后，所有信息的处理
		都已Messagenownumber处理为准，这样可以避免出错
入口参数：byte型，记录从何菜单进入
出口参数：无
/*************************************************************************/

void RunMessage(byte into)
{
  	sword t;
    unsigned char print_temp;
    maske=0;
    maskc=0;
  	subback=into; 						//用于判断是否从子菜单进入
//  	print_sum=0;
  	if(subback!=10) 
  	{
	  	Returntype=into;				//用于记录返回时从何菜单出去
	   	if(Returntype==1||Returntype==0||Returntype==3)//从存储块加载 
		{
			Messagenownumber=Messageinfo.nownumber[0];//在接收到新的信息首先改变nownumber这个变量
		}
		
		else
		{
			Messagenownumber=Messageinfo.nownumber[1];//从锁定块加载
		}
  	}
  	IntialLCD(1);
	Message_Paintintial();				//信息界面刷新
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
		ReadPrtMsg();	//从FPGA读取所需打印信息
		StartRS232(USART3);	//开启打印机
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
	   		(Messageinfo.locknumber[0]&&(Returntype==2||Returntype==4)))	//当存在信息时，下列函数才有效
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