#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "run.h"
#include "Eprom.h"
#include "flash.h"
#include "math.h"
#include "ThreeDays.h"
#include "inc.h"
#include "lcddrive.h"
#include "iec.h"
#include "code.h"
#include "Printer.h"
#include "rtc.h"
#define MesMount 	 299	//信息数读取位置
#define	MesEnd		297	//为信息结束标志，同时也存储了				  本组400个字符从开始到信息结束的				  数量
#define	CERH		296	//误码高字节
#define	CERL		295	//误码低字节
#define msgisover   291
#define BLOCK_SIZE   32768	//32k块大小的定义
#define whchannel   292
void mesdeletelook();
//static Block1;
//*************************************************   
//功能：新信息的处理函数下结果A
//入口参数：无
//出口参数：无
//*************************************************
/*void Flasherror_Paintintial();
void Flasherror_Paintintial()
{
	byte i;
	WFRAME();		//弹出子菜单框图显示
    IntialLCD(1);


	    
	   	CTAB[4]=42;  CTAB[5]='E';   CTAB[6]='R';  CTAB[7]='R'; 
	   	CTAB[8]='O';  CTAB[9]='R'; CTAB[10]=42;
	    CW_PR(9,10,11);	//表头 SETUP
	    

	      
	    CTAB[5]='F';  CTAB[6]='L';  CTAB[7]='A';  CTAB[8]='S';  CTAB[9]='H'; 
	    CW_PR(9,11,10);	//第一行内容：UNLOCK MSG
	    

	      
	    CTAB[4]='O'; CTAB[5]='V';  CTAB[6]='E';  CTAB[7]='R';  CTAB[8]='F';  CTAB[9]='L'; 
	    CTAB[10]='O'; CTAB[11]='W'; 
	    CW_PR(9,12,12);	//第二行内容：PRINT MSG
	    

}    */
void ENABLEIRQB(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}

void DISABLEIRQB(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
  EXTI_InitStructure.EXTI_LineCmd = DISABLE;
  EXTI_Init(&EXTI_InitStructure); 
}

void ENABLEIRQA(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}

void DISABLEIRQA(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //下降沿中断
  EXTI_InitStructure.EXTI_LineCmd = DISABLE;
  EXTI_Init(&EXTI_InitStructure); 
}

void ResultA();
void ResultA()
{
	sword i,start,stop;
	char state;
   if(whichchannel==0xf0)
   {
	Jiemamounte=0;	
	if(flag_more_message==1)
	{
		flag_more_message=0;
		start=readMesEnd;
		stop=readMesMount;
		Jiemamounttemp=stop-start;
		for(i=0;(i<Jiemamounttemp)&&(1+i+Jiemamounte<4400);i++)
		{
			Blocke[1+i+Jiemamounte]=FPGARW(i+start);
		}
		Jiemamounte=Jiemamounte+Jiemamounttemp;		
	}
	else
	{
//		flag_s=0;		//清除提示显示
 //       counter_flag_s=0;//	
	}
	if(flag_new_message==1)		//modified@2010-10-9
	{
/*	   if(msgover==1)
	   {
		flag_s=0;		//清除提示显示
  		counter_flag_s=0;//	
	    first2=0;
	   }  */
		SaveTime();
		FLAG=0;
		if(STATE==16)now_printing=1;
		STATE=1;	
		BUFFER[0]=0;
		State1parameter=0;		//为了指向新信息，这里直接表示从存储界面进入 ，且是DISP进入，无返回键可用modified@2010-8-17
	}
   }
   else if(whichchannel==0x0f)
   {
	Jiemamountc=0;	
	if(flag_more_message==1)
	{
		flag_more_message=0;
		start=readMesEnd;
		stop=readMesMount;
		Jiemamounttemp=stop-start;
		for(i=0;(i<Jiemamounttemp)&&(1+i+Jiemamountc<4400);i++)
		{
			Blockc[1+i+Jiemamountc]=FPGARW(i+start);
		}
		Jiemamountc=Jiemamountc+Jiemamounttemp;		
	}
	else
	{
//		flag_s=0;		//清除提示显示
 //       counter_flag_s=0;//	
	}
	if(flag_new_message==1)		//modified@2010-10-9
	{
/*	   if(msgover==1)
	   {
		flag_s=0;		//清除提示显示
  		counter_flag_s=0;//	
	  	first2=0;
	   }     */
		SaveTime();
		FLAG=0;
		if(STATE==16)now_printing=1;
		STATE=1;	
		BUFFER[0]=0;
		State1parameter=0;		//为了指向新信息，这里直接表示从存储界面进入 ，且是DISP进入，无返回键可用modified@2010-8-17
	}
   }
 }


//*************************************************   
	//MESDEL()函数
	//功能：超过三天时间信息的删除处理
	//入口参数：numtoprank为需处理信息在Messagetoprank[]的位置
	//出口参数：无
	
	//Msgdel()函数
	//功能：信息的删除处理
	//入口参数：numtoprank为需删除信息在Messagetoprank[]的位置
	//出口参数：无	
//*************************************************


void Msgdel(int numtoprank);
void Msgdel(int numtoprank)
{
	sword i,j,k,read;
	
	sword position=Messagetoprank[numtoprank];

	DelAMessFlash(position);	//删除信息在FLASH块中的存储内容，同时修改Flashmap[](内存和Eprom)
	
	j=position/8;	//所在的字节数
	k=position%8;	//所在的bit位
	Eprommap[j]&=~(0x01<<k);	//对应bit位置0
	
	Write_Char_Eprm(EprommapStart+j,Eprommap[j]);//修改存储在eprom中的状态表对应状态
	
	
	read=Messagesavetop[Messagetoprank[numtoprank]].read;	//1未读;0已读
	if(read)
	{
		Unread--;
		Write_Int_Eprm(UNREAD_MSG,Unread);			//存储Unread于Eprom	
	}
	
	for(i=numtoprank;i<Messageinfo.savenumber[0]-1;i++)		//Messagetoprank[]修改
	{
		Messagetoprank[i]=Messagetoprank[i+1];
	}
	Messagetoprank[i]=0;
	Messageinfo.savenumber[0]--;		//总信息数减1
	Messageinfo.nownumber[0]=Messageinfo.savenumber[0]-1;
	Messageinfo.savenumber[Messagesavetop[position].frequency]--;	//对应通道信息数减1			
	WriteMesinfo();					//存储修改完毕信息头文件于Eprom	
//	COPCTR=0xAAAA;
//    COPCTR=0x5555;	
	
}


/*void MesDel(int numtoprank);
void MesDel(int numtoprank)
{



	int position=Messagetoprank[numtoprank];
	MessageProcess|=0x10;	//MessageProcess的bit4置1，表示此时正在进行信息删除操作

	if(Messagesavetop[position].lock==0)//非锁定信息的步骤
	{
		if(MessageProcess&0x01)
		{
			MessageProcess|=0x02;	//MessageProcess的bit1位置1
			TMR0_SCR|=TMR0_SCR_TCFIE_MASK;	//开启8K的定时器0的中断
		}
		else
		{
			Msgdel(numtoprank);
		}

	}

	MessageProcess&=0xef;	//MessageProcess的bit4置0，表示此时完成信息删除操作 

	
//锁定信息无须进行操作

}  */
/************删除一条最早的信息********/
void deleteoldmess();
void deleteoldmess()
{
    	sword i,n,addressa;
    	sword position,position_temp,position_temp2=0,l;
		for(i=0;i<Messageinfo.savenumber[0];i++)
		{
			if(Messagesavetop[Messagetoprank[i]].lock==0)
				break;
		}
		if(i!=Messageinfo.savenumber[0])
		{
			position=Messagetoprank[i];
			position_temp2=i;
			position_temp=i;
		}
		else
		{	
			position=0xffff;
			position_temp=Messageinfo.savenumber[0]-1;
		}
		if(Messageinfo.savenumber[0]==0) position=0xffff;		//此时无存储信息，返回0xffff
		else
		{
			if(position==0xffff)
			{
				//do nothing
			}
			else
			{	
				for(l=position_temp+1;l<Messageinfo.savenumber[0];l++)		//找出未处理过信息中最早接收到的信息，存入i
				{
					i=Messagetoprank[l];
					if(Messagesavetop[i].lock==1) 
					{
						Messagesavetop[i].dealed=1;
					    addressa=i*MESSTYPELENGTH+17;
                       	Write_Char_Eprm(addressa,1); 
					    continue;	//若此信息锁定
						
					}
					if(Messagesavetop[i].date[0]<Messagesavetop[position].date[0])
					{
						position=i;
						position_temp2=l;
						continue;	
					}
					
					if(Messagesavetop[i].date[0]==Messagesavetop[position].date[0])
					{
						if(Messagesavetop[i].date[1]<Messagesavetop[position].date[1])
						{
							position=i;
							position_temp2=l;
							continue;
						}
						
						if(Messagesavetop[i].date[1]==Messagesavetop[position].date[1])
						{
							if(Messagesavetop[i].date[2]<Messagesavetop[position].date[2])
							{
								position=i;
								position_temp2=l;
								continue;
							}
							
							if(Messagesavetop[i].date[2]==Messagesavetop[position].date[2])
							{
								if(Messagesavetop[i].time[0]<Messagesavetop[position].time[0])
								{
									position=i;
									position_temp2=l;
									continue;
								}
								
							    if(Messagesavetop[i].time[0]==Messagesavetop[position].time[0])
								{
									if(Messagesavetop[i].time[1]<Messagesavetop[position].time[1])
									{
										position=i;
										position_temp2=l;
										continue;
									}		
								}
							}
						}
					}
				}
			}
		}	
		Msgdel(position_temp2);			//删除信息
}
/*************************************************   
  /*功能：新信息的存储
入口参数：无
出口参数：无
*************************************************/
void NewMsg_Save();
void NewMsg_Save()
{
	sword i,days,n;
	sword position,position_temp,position_temp2=0,l;
    mesdeletelook();
//	MessageProcess|=0x10;	//MessageProcess的bit4置1，表示此时正在进行信息添加操作	
	/*1.完成从Messagetemptop中获取相关的信息写入Messagesavetop[Messsagetoprank[Messageinfo.savenumber[0]]]
	中（除EpromAdd外的信息）由于现在还不清楚具体的信息格式，暂空*/
	for(i=0;i<75;i++)//3.查找当前的空余位置，用i和n记录,
	{
		for(n=0;n<8;n++)
		{
			if((Eprommap[i]&(0x01<<n))==0) break;
		}
		
		if(n!=8) 	
		{
			Eprommap[i]|=(0x01<<n);	//在对应位置置1
			break;
		}
	}

	if(n==8) //存储器存储信息数量已经超过600条，需要进行信息溢出处理
	{
        deleteoldmess();
		for(i=0;i<75;i++)	//继续查找当前的空余位置，用i和n记录,
		{
			for(n=0;n<8;n++)
			{
				if((Eprommap[i]&(0x01<<n))==0) break;
			}
			
			if(n!=8) 	
			{
				Eprommap[i]|=(0x01<<n);	//在对应位置置1
				break;
			}
		}		
		//只需进行报错处理，三天时间不可能出现收到600条信息情况，必定有地方出错，
		//可以是三天定时器坏，也可能程序出错
	}
	
	//找到空余位置，置1，并在对应头文件处写入对应数组位置
			
		
	Messagetoprank[Messageinfo.savenumber[0]]=i*8+n;//存储信息的位置，排序的时候只需改动Messagetoprank即可，无需改动结构体Messagsavetop
	/*1.从Flash分区状态表首部开始，寻找连续足够的分区存储文件，Flash分区状态表中对应位状态置11
	Eprom中对应的状态表也进行修改，同时把文件分配分区的信息(包括起始分区次序数和分区数量)存入新建文件目录*/

	WriteAMessToFlash(Messagetoprank[Messageinfo.savenumber[0]],Block1);//此时Block1还有效，未收回动态空间	
/*	if(falsh_error==1)
	{
		FLAG=0;
		STATE=911;	
		BUFFER[0]=0;
		State1parameter=0;		
		CLEAR1();
		Flasherror_Paintintial();
		while(1)
		;
	}   */
 //   COPCTR=0xAAAA;
 //   COPCTR=0x5555;	
	Write_Char_Eprm(EprommapStart+i,Eprommap[i]);//6.修改存储在eprom中的状态表对应状态

	
	Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]]].mark[0]=Messagetemptop.mark[0];
	Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]]].mark[1]=Messagetemptop.mark[1];
	Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]]].mark[2]=Messagetemptop.mark[2];
	Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]]].mark[3]=Messagetemptop.mark[3];
	Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]]].frequency=Messagetemptop.frequency;
	Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]]].date[0]=Messagetemptop.date[0];
	Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]]].date[1]=Messagetemptop.date[1];
	Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]]].date[2]=Messagetemptop.date[2];
	Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]]].time[0]=Messagetemptop.time[0];
	Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]]].time[1]=Messagetemptop.time[1];		
	Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]]].area=Messagetemptop.area;
	Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]]].dealed=0;				//0表示未经过三天处理
	Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]]].lock=0;				//0未锁定
	Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]]].select=0;				//0未复选
	Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]]].read=1;				//信息未读
	Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]]].cer=Messagetemptop.cer; //误码率	
	Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]]].amount=Messagetemptop.amount; //@wu	


	/*4.存储信息头文件至Eprom*/
	Save_A_Message_Eprom(Messagetoprank[Messageinfo.savenumber[0]]);

	/*5.信息总头文件的修改以及写入Eprom,此时还需要修改对应通道的数量以及未读信息数*/
	Messageinfo.savenumber[0]++;						//总信息数加1
	Messageinfo.savenumber[Messagetemptop.frequency]++;	//对应通道信息数量加1
	
	/*7判断是否需要开启三天定时器*/
/*	if(ThreeDayAlarm)	//标记ThreeDayAlarm为1，需要开启 
	{
//		Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]-1]].dealed=1;	//信息dealed位置1
		
//		WritebitDeal(Messagetoprank[Messageinfo.savenumber[0]-1]);				//对应Eprom位写入1
		
//		EpromAddNow=Messagetoprank[Messageinfo.savenumber[0]-1];											//下次需处理信息i存入EpromAddNow
		/*3.取出需处理信息的时间，置入定时器，开启定时器
		//完成日期到天数的转换
		days=DatesToDays(Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]-1]].date[0],Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]-1]].date[1],Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]-1]].date[2]);
		TODDAL=days+3;												//写入天数
		TODHAL=Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]-1]].time[0];	//写入小时数
		TODMAL=Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]-1]].time[1];	//写入分钟

		TODCS|=TODCS_TODAEN_MASK;									//开启定时器的中断	
		ThreeDayAlarm=0;											//ThreeDayAlarm置0，接受新信息后无需开启定时器
	}*/
	
	Messageinfo.nownumber[0]=Messageinfo.savenumber[0]-1;//收到新信息，使Messageinfo.nownumber[0]指向新信息
	WriteMesinfo();								//把修改完毕的Messinfo存入Eprom

	Unread++;
	Write_Int_Eprm(UNREAD_MSG,Unread);			//存储Unread于Eprom

    if(Messagetemptop.mark[1]=='D')//D信息
	{
		FPGARW(3600)=0x04;
		Buzzerstate|=0x01;        
	}        
	else if((Messagetemptop.mark[1]=='A'||Messagetemptop.mark[1]=='B'||Messagetemptop.mark[1]=='L')&&Buzzer[1])//ABL&&报警开
	{
		FPGARW(3600)=0x04;
		Buzzerstate|=0x01;	
	}
	else	//收到普通信息
	{
			if(Buzzer[1])
			FPGARW(3600)=0x02;
	}
	flag_new_message=1;	
//	if(Receiverset[1]==1)
//	InsMsg(Messagetoprank[Messageinfo.savenumber[0]-1]);
	if(flag_auto_iec==1)
		iec_InsMsg(Messagetoprank[Messageinfo.savenumber[0]-1]);
	else if(nrmflag_on==1&&((nrmareamk[Messagetemptop.mark[1]-'A']==1)&&
    	    	   (nrmtypemk[Messagetemptop.mark[1]-'A']==1)&&
                   (Messagetemptop.frequency==nrmfre)))
	{
		 iec_alarm_data=0x40;
		 	iec_InsMsg(Messagetoprank[Messageinfo.savenumber[0]-1]);
	}
	if((Messagetemptop.mark[1]=='A')||(Messagetemptop.mark[1]=='L'))
		iec_alarm_data=0x01;
	else if(Messagetemptop.mark[1]=='B')
		iec_alarm_data=0x02;
	else if(Messagetemptop.mark[1]=='D')
		iec_alarm_data=0x04;
//	RunNewmsgtip();	//显示收到新信息的提示菜单
/*添加新信息收到马上显示zzy@2010-6-9*/

//	if(Jietiaomounttemp==0)
/*	{
		FLAG=0;
		STATE=1;	
		BUFFER[0]=0;
		State1parameter=0;		//为了指向新信息，这里直接表示从存储界面进入 ，且是DISP进入，无返回键可用modified@2010-8-17
		CLEAR1();
//	}
*/	
/*新信息收到马上显示代码结束*/	
//	MessageProcess&=0xef;	//MessageProcess的bit4置1，表示此时完成信息删除操作
	ResultA();
//    readalleeprom();	
//	readflash();
//   recenum++;
//    if(recenum==10)
//    {
  //	Intial_FPGA();
//    	recenum=0;
//    }
}


/*************************************************   
	/*功能：信息的锁定
	入口参数：numtoprank为需解锁信息在Messagetoprank[]的位置
	出口参数：无
*************************************************/
void MsgLock(int numtoprank);
void MsgLock(int numtoprank)
{	
	char k;
	sword num=Messagetoprank[numtoprank];	//获取numtoprank所指向的头文件位置 
  DISABLEIRQA();
//	MessageProcess|=0x01;		//此时在进行信息处理操作
	/*1,当前需锁定信息lock位置1，找出当前信息的通道存入k,*/
	k=Messagesavetop[num].frequency;	//变量k记录当前信息通道
	Messagesavetop[num].lock=1;			//锁定标记位lock置1
	LockAMessageHeader(num);			//对应Eprom中lock位置1
	
	/*2.信息总头文件的修改以及写入Eprom*/
	Messageinfo.locknumber[0]++;	//锁定信息数加1
	Messageinfo.locknumber[k]++;	//对应通道信息数加1
	WriteMesinfo();					//存储修改完毕信息头文件于Eprom
  ENABLEIRQA();
//	MessageProcess&=0xfe;			//信息处理操作完毕，bit1位置0
}



//*************************************************   
	//功能：信息的解锁
  	//入口参数：numtoprank为需解锁信息在Messagetoprank[]的位置
//*************************************************
void MsgUnlock(int numtoprank);
void MsgUnlock(int numtoprank)
{ 

/*1.	根据目录中的文件分配分区信息找到对应分区
2.	判断分配分区所属擦除块(Flash的擦除块为2K字，包含4个分区)中其它分区状态是否01(非空闲但未分配)。
3.	若满足则擦出块内4个分区的对应位状态都置00，同时进行块擦除操作，反之只把文件分配分区的对应状态位置01。
4.	根据目录中目录分配分区信息，把目录分配分区的对应状态位置0。
5.	删除文件目录，修改存储在E2prom中两张分区状态表。*/
	u8 channel,read;
	u16 days,daysnow,hours,minutes;
	sword j,k,overtime=0,meslocknum,i=0;//j用于记录需解锁信息在锁定信息头文件数组中的位置
	sword num=Messagetoprank[numtoprank];	//获取numtoprank所指向的头文件位置
  DISABLEIRQA();
//	MessageProcess|=0x01;		//此时在进行信息处理操作
	/*1.判定需解锁信息的接收时间是否已过3天，用参数overtime来表示，1为超过3天，
    	0表示未超过*/
	days=DatesToDays(Messagesavetop[num].date[0],Messagesavetop[num].date[1],Messagesavetop[num].date[2]);
//	years=Messagesavetop[num].date[0];
//	months=Messagesavetop[num].date[1];
//	days=Messagesavetop[num].date[2]
	hours=Messagesavetop[num].time[0];
	minutes=Messagesavetop[num].time[1];	//获取对应信息的时间 	

//	TODCS|=TODCS_TOD_LOCK_MASK;		//开启TOD_Lock位，读取TOD模块中时间的寄存器 
/*	
	if(((days+3)<TODDAL)||(((days+3)==TODDAL)&&hours<TODHAL)||
	(((days+3)==TODDAL)&&(hours==TODHAL)&&(minutes<TODMAL)))*/
//	timestruct=GetTime();   @wu
	daysnow=DatesToDays(timestruct.year,timestruct.month,timestruct.day);
	if(((days+3)<daysnow)||(((days+3)==daysnow)&&hours<timestruct.hour)||
	(((days+3)==daysnow)&&(hours==timestruct.hour)&&(minutes<=timestruct.minute)))
	overtime=1;						//需解锁信息在3天之前收到，overtime置1	
			
//	TODCS&=~TODCS_TOD_LOCK_MASK;	//关闭TOD_Lock锁定位 
    if(Messagesavetop[Messagetoprank[numtoprank]].dealed==1)
    {
        overtime=1;	
    }
	/*2完成对应头文件lock置0,同时修改Eprom对应lock位，若时间超过三天，增加对FLASH
	   存储块中该内容的删除*/
	if(overtime==1)	//时间超过三天
	{
		DelAMessFlash(num);	//删除信息在FLASH块中的存储内容，同时修改Flashmap[](内存和Eprom)
		
		j=num/8;	//所在的字节数
		k=num%8;	//所在的bit位
		Eprommap[j]&=~(0x01<<k);	//对应bit位置0
		Write_Char_Eprm(EprommapStart+j,Eprommap[j]);//修改存储在eprom中的状态表对应状态
//
		read=Messagesavetop[Messagetoprank[numtoprank]].read;	//1未读;0已读
		if(read)
		{
			Unread--;
			Write_Int_Eprm(UNREAD_MSG,Unread);			//存储Unread于Eprom	
		}
		
		for(i=numtoprank;i<Messageinfo.savenumber[0]-1;i++)		//Messagetoprank[]修改
		{
			Messagetoprank[i]=Messagetoprank[i+1];
		}
		Messageinfo.savenumber[0]--;		//总信息数减1
		Messageinfo.savenumber[Messagesavetop[num].frequency]--;	//对应通道信息数减1
 //       COPCTR=0xAAAA;
 //       COPCTR=0x5555;
	}

	else	//时间未超过三天，只需修改lock位
	{
		Messagesavetop[num].lock=0;
		UnlockAMessageHeader(num);			//对应Eprom中lock位置0
		State1parameter=10;					//此时解锁信息未被删除
	}
	
	Messageinfo.locknumber[0]--;	//总锁定信息数减1
	Messageinfo.locknumber[Messagesavetop[num].frequency]--;	//对应通道信息数减1	
/*
	if(STATE==12&&(Returntype==2||Returntype==4))	//解锁信息在信息菜单子菜单下进行，且信息菜单由锁定菜单进入
	{
		if(Messageinfo.locknumber[0]>0)
		{
			for(i=Messageinfo.savenumber[0]-1;i>=0;i--)
			{
				if(Messagesavetop[Messagetoprank[i]].lock==1) 
				{
					Messageinfo.nownumber[1]=i;
					break;	
				}
			}				
		}
		else
		Messageinfo.nownumber[1]=0;		//改变nownumber[1]，使其指向最后一条锁定信息，同时改变Returntype

		State1parameter=4;				//State1parameter的值发生改变说明有信息删除发声，再次进入信息菜单
										//时，需要重新刷新		
	}
	
	if(STATE==12&&(Returntype==0||Returntype==1||Returntype==3))//存储菜单进入信息菜单，在信息菜单下的解锁
	{
		if(Messageinfo.savenumber[0]>0)
		Messageinfo.nownumber[0]=Messageinfo.savenumber[0]-1;
		else
		Messageinfo.nownumber[0]=0;
		if(Returntype)
		State1parameter=3;
		else
		State1parameter=0;
	}*/
	if(STATE==12&&(Returntype==2||Returntype==4))	//解锁信息在信息菜单子菜单下进行，且信息菜单由锁定菜单进入
	{
		if(Messageinfo.locknumber[0]>0)
		{
			for(i=Messageinfo.savenumber[0]-1;i>=0;i--)
			{
				if(Messagesavetop[Messagetoprank[i]].lock==1) 
				{
					Messageinfo.nownumber[1]=i;
					break;	
				}
			}				
		}
		else
			Messageinfo.nownumber[1]=0;		//改变nownumber[1]，使其指向最后一条锁定信息，同时改变Returntype
		if(Messageinfo.savenumber[0]>0)
			Messageinfo.nownumber[0]=Messageinfo.savenumber[0]-1;
		else
			Messageinfo.nownumber[0]=0;
		
		State1parameter=4;				//State1parameter的值发生改变说明有信息删除发声，再次进入信息菜单
										//时，需要重新刷新		
	}
	
	if(STATE==12&&(Returntype==0||Returntype==1||Returntype==3))//存储菜单进入信息菜单，在信息菜单下的解锁
	{
		if(Messageinfo.locknumber[0]>0)
		{
			for(i=Messageinfo.savenumber[0]-1;i>=0;i--)
			{
				if(Messagesavetop[Messagetoprank[i]].lock==1) 
				{
					Messageinfo.nownumber[1]=i;
					break;	
				}
			}				
		}
		else
			Messageinfo.nownumber[1]=0;		//改变nownumber[1]，使其指向最后一条锁定信息，同时改变Returntype
		if(Messageinfo.savenumber[0]>0)
		Messageinfo.nownumber[0]=Messageinfo.savenumber[0]-1;
			else
			Messageinfo.nownumber[0]=0;
		if(Returntype)
			State1parameter=3;
		else
			State1parameter=0;
	}
	if(STATE==2000)//存储菜单进入信息菜单，在信息菜单下的解锁
	{
		if(Messageinfo.locknumber[0]>0)
		{
			for(i=Messageinfo.savenumber[0]-1;i>=0;i--)
			{
				if(Messagesavetop[Messagetoprank[i]].lock==1) 
				{
					Messageinfo.nownumber[1]=i;
					break;	
				}
			}				
		}
		else
			Messageinfo.nownumber[1]=0;		//改变nownumber[1]，使其指向最后一条锁定信息，同时改变Returntype
		if(Messageinfo.savenumber[0]>0)
			Messageinfo.nownumber[0]=Messageinfo.savenumber[0]-1;
		else
			Messageinfo.nownumber[0]=0;
	}

	WriteMesinfo();				//存储修改完毕信息头文件于Eprom
//	MessageProcess&=0xfe;		//信息处理操作完毕，bit1位置0
  ENABLEIRQA();
} 





/*************************************************   
	功能：从接收的来自FPGA解码完成的信息内找出
		  信息头文件存储与全局变量Messagetemptop中;
	入口参数：无
	返回参数：无
 *************************************************/
void Savetemptop();
void Savetemptop()
{
	
	static sword i=0; 
	word cernum=0;
//	cer=(word)(FPGARW(CERH)&0x00ff);	//获取高8位
//	cer=cer<<8;
//	cer=cer+(word)(FPGARW(CERL)&0x00ff);	//获取信息的字节数
    for(i=0;i<Jiemamount;i++)
    {
    	if(Block1[i]=='*')
    	{
    		cernum++;
    	}
    }
	Messagetemptop.cer=((uint32)cernum)*100/((uint32)Jiemamount-2);	//获取信息的误码率  @wu

	Messagetemptop.mark[0]=Block1[2];	//假设接收信息直接从B1B2B3B4开始
	Messagetemptop.mark[1]=Block1[3];
	Messagetemptop.mark[2]=Block1[4];	
	Messagetemptop.mark[3]=Block1[5];
	for(i=0;i<2;i++)
	{
		switch(Messagetemptop.mark[i])
		{
			case('-'):Messagetemptop.mark[i]='A';break;
			case('?'):Messagetemptop.mark[i]='B';break;
			case(':'):Messagetemptop.mark[i]='C';break;
	//		case('*'):Messagetemptop.mark[i]='D';break;
			case('3'):Messagetemptop.mark[i]='E';break;
			case('%'):Messagetemptop.mark[i]='F';break;
			case('#'):Messagetemptop.mark[i]='G';break;
			case(34):Messagetemptop.mark[i]='H';break;//' "  '双引号
			case('8'):Messagetemptop.mark[i]='I';break;
			case('@'):Messagetemptop.mark[i]='J';break;
			case('('):Messagetemptop.mark[i]='K';break;
			case(')'):Messagetemptop.mark[i]='L';break;
			case('.'):Messagetemptop.mark[i]='M';break;
			case(','):Messagetemptop.mark[i]='N';break;
			case('9'):Messagetemptop.mark[i]='O';break;
			case('0'):Messagetemptop.mark[i]='P';break;
			case('1'):Messagetemptop.mark[i]='Q';break;
			case('4'):Messagetemptop.mark[i]='R';break;
			case(39):Messagetemptop.mark[i]='S';break;//' ' '单引号
			case('5'):Messagetemptop.mark[i]='T';break;
			case('7'):Messagetemptop.mark[i]='U';break;
			case('='):Messagetemptop.mark[i]='V';break;
			case('2'):Messagetemptop.mark[i]='W';break;
			case('/'):Messagetemptop.mark[i]='X';break;
			case('6'):Messagetemptop.mark[i]='Y';break;
			case('+'):Messagetemptop.mark[i]='Z';break;
			default:break;
		}	
	}
	Block1[2]=Messagetemptop.mark[0];
	Block1[3]=Messagetemptop.mark[1];
//	Messagetemptop.mark[3]=Block1[5]+i++;
//	Block1[5]=Messagetemptop.mark[3];

/*	Messagetemptop.mark[0]=Block1[3];	//假设接收信息直接从B1B2B3B4开始
	Messagetemptop.mark[1]=Block1[4];
	Messagetemptop.mark[2]=Block1[5];	
	Messagetemptop.mark[3]=Block1[6];*/

//		if(Dingxiang[1]==1)//(G_Key&0x20)//Messagetemptop.frequency=2;//JietiaoResult[0].frequency;		//通道存储
//		{
//			if(Workfre)
//   	  		Messagetemptop.frequency=2;   	//486通道对应2
//   	   	else
//  	    		Messagetemptop.frequency=3;	//4M通道对应3		
//		}
//		else
//			Messagetemptop.frequency=1;
	if(manual_area==0)
	{
 		manual_area=11;
		Eprom_ManualMsgMode_Save(RXSTATION_MANUAL);	//配置信息存入Eprom		
	}
		
	if(Mode==1)
		Messagetemptop.area=manual_area;			//
	else
		Messagetemptop.area=auto_area;
//	TODCS|=TODCS_TOD_LOCK_MASK;		//开启TOD_Lock位，读取TOD模块中时间的寄存器 
//	DaysToDates(TODDAY,&Messagetemptop.date[2],&Messagetemptop.date[1],&Messagetemptop.date[0]);
//	timestruct=GetTime();
  Messagetemptop.date[2]=timestruct.day;
  Messagetemptop.date[1]=timestruct.month;
	Messagetemptop.date[0]=timestruct.year;
	Messagetemptop.time[1]=timestruct.minute;
	Messagetemptop.time[0]=timestruct.hour;
//	TODCS&=~TODCS_TOD_LOCK_MASK;//关闭TOD_Lock锁定位 
	SaveTime();	
}
 
 

	

	
//*************************************************   
	//功能：新信息的处理函数
	//入口参数：无
	//出口参数：无
//*************************************************
void MesDeal();
void MesDeal()
{
	char channel,navtexstation,abandon=0,navtexsarea,msgtype,cer,avail=0;
	sword i,temp,cherr=0;
	sword chnnnn=0;
	sword jiemamount_temp=0;
//	Intial_Message();  //以免DSP外部SRAM出错,重新加载
    if(whichchannel==0xf0)
    {
    	for(i=0;(i<=Jiemamounte)&&(i<3600);i++)
    	{
    		Block1[i]=Blocke[i];
    	}
    	Jiemamount=Jiemamounte;
  	  	Messagetemptop.frequency=1; 
    }
    else if(whichchannel==0x0f)
    {
    	for(i=0;(i<=Jiemamountc)&&(i<3600);i++)
    	{
    		Block1[i]=Blockc[i];
    	}
    	Jiemamount=Jiemamountc;
		if(Workfre)
  	  		Messagetemptop.frequency=2;   	//486通道对应2
   	   	else
      		Messagetemptop.frequency=3;	//4M通道对应3	
    }
    else
    {
    	Jiemamount=0;
    }
	if(Jiemamount)
	{
		Jiemamount=Jiemamount+2;	//所加的2位分别表示：2总字节数（由于读取数据第一个位空，可省下一个字节）1NULL
		jiemamount_temp=Jiemamount;
		Block1[0]=Jiemamount>>8;	//总字节数的高8位
		Block1[1]=Jiemamount;		//总字节数的低8位
     	Messagetemptop.amount=Jiemamount;
		Savetemptop();
		Jiemamount=0;					//一条信息解码完毕，清零使用全局变量
		channel=Messagetemptop.frequency-1;		//获取当前信息的通道，存储的时候为1~3，减一转化
		navtexsarea=Messagetemptop.area;		//获取当前信息所在的发射区，共有16个发射区
		navtexstation=Messagetemptop.mark[0]-65;//由于存储发射台用字符表示为A~Z，需转化为对应的0~25
		msgtype=Messagetemptop.mark[1]-65;		//由于存储信息类别用字符表示为A~Z，需转化为对应的0~25

		if((Messagetemptop.mark[0]!='*')&&
		   (Messagetemptop.mark[1]!='*')&&
		   ((Messagetemptop.mark[2]<='9')&&(Messagetemptop.mark[2]>='0'))&&
		   ((Messagetemptop.mark[3]<='9')&&(Messagetemptop.mark[3]>='0')))
		{
			for(i=0;i<2;i++)
			{
				switch(Messagetemptop.mark[i])
				{
					case('-'):Messagetemptop.mark[i]='A';break;
					case('?'):Messagetemptop.mark[i]='B';break;
					case(':'):Messagetemptop.mark[i]='C';break;
	//				case('*'):Messagetemptop.mark[i]='D';break;  //???*不是误码吗??
					case('3'):Messagetemptop.mark[i]='E';break;
					case('%'):Messagetemptop.mark[i]='F';break;
					case('#'):Messagetemptop.mark[i]='G';break;
					case(34):Messagetemptop.mark[i]='H';break;//' "  '双引号
					case('8'):Messagetemptop.mark[i]='I';break;
					case('@'):Messagetemptop.mark[i]='J';break;
					case('('):Messagetemptop.mark[i]='K';break;
					case(')'):Messagetemptop.mark[i]='L';break;
					case('.'):Messagetemptop.mark[i]='M';break;
					case(','):Messagetemptop.mark[i]='N';break;
					case('9'):Messagetemptop.mark[i]='O';break;
					case('0'):Messagetemptop.mark[i]='P';break;
					case('1'):Messagetemptop.mark[i]='Q';break;
					case('4'):Messagetemptop.mark[i]='R';break;
					case(39):Messagetemptop.mark[i]='S';break;//' ' '单引号
					case('5'):Messagetemptop.mark[i]='T';break;
					case('7'):Messagetemptop.mark[i]='U';break;
					case('='):Messagetemptop.mark[i]='V';break;
					case('2'):Messagetemptop.mark[i]='W';break;
					case('/'):Messagetemptop.mark[i]='X';break;
					case('6'):Messagetemptop.mark[i]='Y';break;
					case('+'):Messagetemptop.mark[i]='Z';break;
					default:break;
				}	
			}
			if(((Messagetemptop.mark[0]<='Z')&&(Messagetemptop.mark[0]>='A'))&&
		   ((Messagetemptop.mark[1]<='Z')&&(Messagetemptop.mark[1]>='A'))&&
		   ((Messagetemptop.mark[2]<='9')&&(Messagetemptop.mark[2]>='0'))&&
		   ((Messagetemptop.mark[3]<='9')&&(Messagetemptop.mark[3]>='0'))&&
		   (jiemamount_temp>=18)&&(jiemamount_temp<=4502))
		   		avail=1;
		}		   
		if(avail)
		{	
			if(Messagetemptop.mark[2]=='0'&&Messagetemptop.mark[3]=='0')	//收到00重要信息
	//		if(Messagetemptop.mark[2]=='4'&&Messagetemptop.mark[3]=='9')	//收到00重要信息
			{
			//		TMR0_SCR|=TMR0_SCR_TCFIE_MASK;	//开启信息处理中断			    
	//			if(MessageProcess&0x01)
	//			{
	//				MessageProcess|=0x04;	//MessageProcess的bit2位置1
	//				TMR0_SCR|=TMR0_SCR_TCFIE_MASK;	//开启信息处理中断
	//			}
	//			else
	           if(Messagetemptop.cer>33) 
	            {
	               ResultA();	
	            }
    	            else
	            {
					NewMsg_Save();	//存储新信息	
	            }					
			}
			
			else
			{
//#if 0
//				if(Messagetemptop.mark[1]!='A'&&Messagetemptop.mark[1]!='B'&&
//				Messagetemptop.mark[1]!='D'&&Messagetemptop.mark[1]!='L')			//收到非搜救信息
//				{
//#endif				
				if(Mode==0)							//判断信息是否满足接收设置的条件
				{
					temp=Power(navtexsarea-1);
					if(Auto[channel][navtexstation]&temp) abandon=1;
	//				if((Auto[channel][navtexstation]&temp)!=0) abandon=1;
	//				if(Auto[channel][navtexstation]&(word)(pow(2,navtexsarea-1))) abandon=1;					
				}
				
				if(Mode==1&&Manual[channel][navtexstation]) abandon=1;	//不满足岸台设置，abandon置1
	//if((Mode==1)&&(Manual[channel][navtexstation]==1)) abandon=1;	//不满足岸台设置，abandon置1
				if(MSGTYPE[channel][msgtype]) abandon=1;				//不满足信息类别设置，abandon置1
	//if(MSGTYPE[channel][msgtype]!=0) abandon=1;
	//            if(Messagetemptop.mark[0]=='S') abandon=1;
	            if((channel==1)||(channel==2))
	            {
					   for(i=18;i<jiemamount_temp-6;i++)
					   {
					   	
					   	    
					if(Block1[i]==0)                   //空字符??
					{
								//未穿带孔当作空格处理
							continue;
					}
					else if(((Block1[i]<='M')&&(Block1[i]>='A'))&&
					   ((Block1[i+1]<='Z')&&(Block1[i+1]>='A'))&&
					   ((Block1[i+2]<='Z')&&(Block1[i+2]>='A')))
					{
						//chinese[mountbyte_lcd++]=eng_to_lcd(&MessagePoint[i]);			//符合转换要求，则正常转换	
						i=i+2;
					}
					else if((Block1[i]>'M')||(Block1[i]<'A'))
					{
					   
					   if(((Block1[i+1]<='M')&&(Block1[i+1]>='A'))&&
					   ((Block1[i+2]<='Z')&&(Block1[i+2]>='A'))&&
					   ((Block1[i+3]<='Z')&&(Block1[i+3]>='A'))&&
					   
					   ((Block1[i+4]<='M')&&(Block1[i+4]>='A'))&&
					   ((Block1[i+5]<='Z')&&(Block1[i+5]>='A'))&&
					   ((Block1[i+6]<='Z')&&(Block1[i+6]>='A'))&&
					   
					   ((Block1[i+7]<='M')&&(Block1[i+7]>='A'))&&
					   ((Block1[i+8]<='Z')&&(Block1[i+8]>='A'))&&
					   ((Block1[i+9]<='Z')&&(Block1[i+9]>='A')))
					   {
					 		continue;
					 		//多余字节
					   		//i不变，自动增1
					   }
					   else if(((Block1[i+2]<='M')&&(Block1[i+2]>='A'))&&
					   ((Block1[i+3]<='Z')&&(Block1[i+3]>='A'))&&
					   ((Block1[i+4]<='Z')&&(Block1[i+4]>='A'))&&
					   
					   ((Block1[i+5]<='M')&&(Block1[i+5]>='A'))&&
					   ((Block1[i+6]<='Z')&&(Block1[i+6]>='A'))&&
					   ((Block1[i+7]<='Z')&&(Block1[i+7]>='A'))&&
					   
					   ((Block1[i+8]<='M')&&(Block1[i+8]>='A'))&&
					   ((Block1[i+9]<='Z')&&(Block1[i+9]>='A'))&&
					   ((Block1[i+10]<='Z')&&(Block1[i+10]>='A')))
					   {
					   		//chinese[mountbyte_lcd++]=0xa3aa;				//输出*
					   		cherr++;
					   		i=i+1;//丢失字节
					   		//i不变，自动增1
					   }
					   else
					   {
					   		cherr++;
					   		//chinese[mountbyte_lcd++]=0xa3aa;				//输出*
					   		i=i+2;//否则当错误字节处理
					   }
					}
					else if((Block1[i+1]>'Z')||(Block1[i+1]<'A'))
					{
					   if((Block1[i+1]=='\r')/*回车*/||(Block1[i+1]=='\n'))
					   {
					   		cherr++;
					   		//chinese[mountbyte_lcd++]=0xa3aa;
					   }
					   else if(Block1[i+1]==0)
					   {
					   		cherr++;
					   		//chinese[mountbyte_lcd++]=0xa3aa;
					   		i=i+1;	
					   }
					   else if(((Block1[i]<='M')&&(Block1[i]>='A'))&&
					   ((Block1[i+2]<='Z')&&(Block1[i+2]>='A'))&&
					   ((Block1[i+3]<='Z')&&(Block1[i+3]>='A'))&&
					   
					   ((Block1[i+4]<='M')&&(Block1[i+4]>='A'))&&
					   ((Block1[i+5]<='Z')&&(Block1[i+5]>='A'))&&
					   ((Block1[i+6]<='Z')&&(Block1[i+6]>='A'))&&
					   
					   ((Block1[i+7]<='M')&&(Block1[i+7]>='A'))&&
					   ((Block1[i+8]<='Z')&&(Block1[i+8]>='A'))&&
					   ((Block1[i+9]<='Z')&&(Block1[i+9]>='A')))
					   {
					   		cherr++;
					   		//chinese[mountbyte_lcd++]=0xa3aa;				//输出*
					   		i=i+3;//多余字节
					   		//i不变，自动增1
					   }
					   else if(((Block1[i+2]<='M')&&(Block1[i+2]>='A'))&&
					   ((Block1[i+3]<='Z')&&(Block1[i+3]>='A'))&&
					   ((Block1[i+4]<='Z')&&(Block1[i+4]>='A'))&&
					   
					   ((Block1[i+5]<='M')&&(Block1[i+5]>='A'))&&
					   ((Block1[i+6]<='Z')&&(Block1[i+6]>='A'))&&
					   ((Block1[i+7]<='Z')&&(Block1[i+7]>='A'))&&
					   
					   ((Block1[i+8]<='M')&&(Block1[i+8]>='A'))&&
					   ((Block1[i+9]<='Z')&&(Block1[i+9]>='A'))&&
					   ((Block1[i+10]<='Z')&&(Block1[i+10]>='A')))
					   {
					   		cherr++;
					   		//chinese[mountbyte_lcd++]=0xa3aa;				//输出*
					   		i=i+1;//丢失字节
					   		//i不变，自动增1
					   }
					   else
					   {
					   		cherr++;
					   		//chinese[mountbyte_lcd++]=0xa3aa;				//输出*
					   		i=i+2;//否则当错误字节处理
					   }		
					}
					else if((Block1[i+2]>'Z')||(Block1[i+2]<'A'))
					{
						if((Block1[i+2]=='\r')/*回车*/||(Block1[i+2]=='\n'))
					   {
					   		cherr++;
					   		//chinese[mountbyte_lcd++]=0xa3aa;
					   		i=i+2;
					   }
					   else if(Block1[i+2]==0)
					   {
					   		cherr++;
					   		//chinese[mountbyte_lcd++]=0xa3aa;
					   		i=i+2;	
					   }
					   else if(((Block1[i]<='M')&&(Block1[i]>='A'))&&
					   ((Block1[i+1]<='Z')&&(Block1[i+1]>='A'))&&
					   ((Block1[i+3]<='Z')&&(Block1[i+3]>='A'))&&
					   
					   ((Block1[i+4]<='M')&&(Block1[i+4]>='A'))&&
					   ((Block1[i+5]<='Z')&&(Block1[i+5]>='A'))&&
					   ((Block1[i+6]<='Z')&&(Block1[i+6]>='A'))&&
					   
					   ((Block1[i+7]<='M')&&(Block1[i+7]>='A'))&&
					   ((Block1[i+8]<='Z')&&(Block1[i+8]>='A'))&&
					   ((Block1[i+9]<='Z')&&(Block1[i+9]>='A')))
					   {
					   		cherr++;
					   		//chinese[mountbyte_lcd++]=0xa3aa;				//输出*
					   		i=i+3;//多余字节
					   		//i不变，自动增1
					   }
					   else if(((Block1[i+2]<='M')&&(Block1[i+2]>='A'))&&
					   ((Block1[i+3]<='Z')&&(Block1[i+3]>='A'))&&
					   ((Block1[i+4]<='Z')&&(Block1[i+4]>='A'))&&
					   
					   ((Block1[i+5]<='M')&&(Block1[i+5]>='A'))&&
					   ((Block1[i+6]<='Z')&&(Block1[i+6]>='A'))&&
					   ((Block1[i+7]<='Z')&&(Block1[i+7]>='A'))&&
					   
					   ((Block1[i+8]<='M')&&(Block1[i+8]>='A'))&&
					   ((Block1[i+9]<='Z')&&(Block1[i+9]>='A'))&&
					   ((Block1[i+10]<='Z')&&(Block1[i+10]>='A')))
					   {
					   		cherr++;
					   		//hinese[mountbyte_lcd++]=0xa3aa;				//输出*
					   		i=i+1;//丢失字节
					   		//i不变，自动增1
					   }
					   else
					   {
					   		cherr++;
					   		//chinese[mountbyte_lcd++]=0xa3aa;				//输出*
					   		i=i+2;//否则当错误字节处理
					   }		
					}
					
				
					   }
					   if(cherr==0)
					   {
					   	cherr=1;
					   }
					  if(channel==1)
					  {
					   if(((jiemamount_temp-23)/cherr)<25/*9/*75*/)abandon=1;	
					   if(jiemamount_temp<170)
					   {
					   for(i=18;i<jiemamount_temp;i++)
					   {
					   if(Block1[i]=='A'&&Block1[i+1]=='I'&&Block1[i+2]=='Z'&&
					      Block1[i+3]=='A'&&Block1[i+4]=='I'&&Block1[i+5]=='Z'&&        //????
					      Block1[i+6]=='A'&&Block1[i+7]=='I'&&Block1[i+8]=='Z'&&
					      Block1[i+9]=='A'&&Block1[i+10]=='I'&&Block1[i+11]=='Z')
					       chnnnn=1;
					   else if(Block1[i]=='N'&&Block1[i+1]=='N'&&Block1[i+2]=='N'&&Block1[i+3]=='N')
					       chnnnn=1;
					   }
					   if(chnnnn==0)abandon=1;
					   	
					   }
					  }
					  else if(channel==2)
					  {
					   if(((jiemamount_temp-23)/cherr)>=5/*9/*75*/)abandon=1;		
					   if(jiemamount_temp<120)
					   {
					   for(i=18;i<jiemamount_temp;i++)
					   {
					   if(Block1[i]=='A'&&Block1[i+1]=='I'&&Block1[i+2]=='Z'&&
					      Block1[i+3]=='A'&&Block1[i+4]=='I'&&Block1[i+5]=='Z'&&        //????
					      Block1[i+6]=='A'&&Block1[i+7]=='I'&&Block1[i+8]=='Z'&&
					      Block1[i+9]=='A'&&Block1[i+10]=='I'&&Block1[i+11]=='Z')
					       chnnnn=1;
					   else if(Block1[i]=='N'&&Block1[i+1]=='N'&&Block1[i+2]=='N'&&Block1[i+3]=='N')
					       chnnnn=1;
					   }
					   if(chnnnn==0)abandon=1;
					   }
					  }
	            }
				if(abandon) ResultA();	//收到的为非搜救信息，且不满足岸台或者信息类别设置
		
				
//				}			
				else
/*				
				if(Messagetemptop.mark[1]=='A'||Messagetemptop.mark[1]=='B'||
				Messagetemptop.mark[1]=='D'||Messagetemptop.mark[1]=='L'||
				(Messagetemptop.mark[1]!='A'&&Messagetemptop.mark[1]!='B'&&
				Messagetemptop.mark[1]!='D'&&Messagetemptop.mark[1]!='L'&&abandon==0))	//收到求救信息或者收到非求救信息但满足岸台和信息类别设置
*/			
				{
					if(Messagetemptop.cer>33) ResultA();	//新信息误码率大于33%，执行结果A  @wu
					else
					{
						for(i=0;i<=Messageinfo.savenumber[0];i++)//检测此信息是否为新信息，方法：三天有无接收相同标记的信息，
																//有则说明之前已接受过，abondan置1,当deal为0都是未经过三天处理，若deal为1则须考虑
																//特殊情况，即此时的信息正在三天处理的周期内，判断条件为EpromAddNow==Messagetoprank[i]
						{
							if(/*(Messagesavetop[Messagetoprank[i]].dealed==0)&&*/	
							   (Messagetemptop.mark[0]==Messagesavetop[Messagetoprank[i]].mark[0])&&
							   (Messagetemptop.mark[2]==Messagesavetop[Messagetoprank[i]].mark[2])&&
							   (Messagetemptop.mark[1]==Messagesavetop[Messagetoprank[i]].mark[1])&&
							   (Messagetemptop.mark[3]==Messagesavetop[Messagetoprank[i]].mark[3])&&
							   (Messagetemptop.frequency==Messagesavetop[Messagetoprank[i]].frequency))//added@2010-9-16必须是同个通道的之前已收到的信息
							   break;
							   						
						}
						
						if(i==Messageinfo.savenumber[0]+1) //表示无已接收过当前信息
						{
						//	if(MessageProcess&0x01)
						//	{
						//		MessageProcess|=0x04;			//MessageProcess的bit2位置1
						//		TMR0_SCR|=TMR0_SCR_TCFIE_MASK;	//开启信息处理中断
						//	}
					//		else
						NewMsg_Save();	//存储新信息
						}
						
						else	//表示有接收过当前信息
						{
							if(Messagesavetop[Messagetoprank[i]].cer<4) ResultA();	//已接收信息误码率小于4%
							else
							{
								if(Messagetemptop.cer>Messagesavetop[Messagetoprank[i]].cer) ResultA();
								else
								{
				/*					if(MessageProcess&0x01)
									{
										MessageProcess|=0x04;			//MessageProcess的bit2位置1
							     		MessageProcess|=0x08;			//MessageProcess的bit3位置1
										TMR0_SCR|=TMR0_SCR_TCFIE_MASK;	//开启信息处理中断
					     			}
									else
									{
										if(Messagesavetop[Messagetoprank[i]].lock==0)
										{
											if(Messagesavetop[Messagetoprank[i]].dealed==1)
											{
												Msgdel(i);
												FindMsg();
											}
											else
											{
												Msgdel(i);
											}
											
											ThreeDayAlarm=1;	//若此时需删除的信息为正在处理的信息，则三天处理标记需置1
																//新添加信息需开启三天定时器
	     									Msgdel(i);	
										}   */
									if(Messagesavetop[Messagetoprank[i]].lock==1)
									{
							//		   Messagesavetop[Messagetoprank[i]].dealed=1;
									}
									else
									{
										Msgdel(i);
									}
									NewMsg_Save();	//存储新信息
						//			}
								 		
							   	}
							 	
							}
						}
					}
				}
			}
		}
		else
		{
			ResultA();
		}
				
	}
	else		//信息总数为0
	{
 		ResultA();
	}
}
/*************************************************   
	功能：接收并处理来自FPGA解码完成的信息
	入口参数：无
	返回参数：无
 *************************************************/
void MsgFromFpga();
void MsgFromFpga()
{	
	char abandon=0,navtexsarea,msgtype;
	char ilow,ihigh;
	sword k,j=0,i,mesend,mesend1,totalamount;
//	static sword l=0;
	whichchannel=FPGARW(whchannel);
	msgover=FPGARW(msgisover);
	readMesMount = FPGARW(MesMount)&0x00ff;	//接收信息数的低8位
	Jiemamounttemp = readMesMount;
	if(whichchannel==0xf0)
	{
		totalamount=Jiemamounte+Jiemamounttemp;
	}
	if(whichchannel==0x0f)
	{
		totalamount=Jiemamountc+Jiemamounttemp;
	}
  if(totalamount<3500)
  {
   if(whichchannel==0xf0)
   {
	if(G_Key&0x40)   //正文已结束
	{
	
//		Jiemamounttemp = FPGARW(MesMount)&0x00ff;	//接收信息数的低8位
/**/	if(Jiemamounttemp==0)
		{
			if(Jiemamount!=0)
			MesDeal();
			if(msgover==1)
			{
			flag_s=0;		//清除提示显示
  			counter_flag_se=0;//	
	    	maske=0;			
			}
		}
		else
		{
			readMesEnd=FPGARW(MesEnd)&0x00ff;
			mesend=readMesEnd;			//读取最后一波的前一条信息数
			if(mesend==0)							//如果最后一波的前一条信息数为0，则直接处理这条信息
			{
				flag_more_message =1;    //???
				if(Jiemamounte!=0)
				MesDeal();                   
			if(msgover==1)
			{
			flag_s=0;		//清除提示显示
  			counter_flag_se=0;//	
	    	maske=0;			
			}
			}
			else
			{
				if(Jiemamounttemp>mesend) flag_more_message =1;
				else
				{	
					//flag_s=0;		//清除提示显示
  				//	counter_flag_s=0;//	
				}
				Jiemamounttemp = mesend;
				for(i=0;(i<Jiemamounttemp)&&(1+i+Jiemamounte<3600);i++) 
				{
				Blocke[1+i+Jiemamounte]=FPGARW(i);    //??why not begin with 2+i??
				}
				Jiemamounte=Jiemamounte+Jiemamounttemp;
				MesDeal();	
    			if(msgover==1)
		    	{
		    	flag_s=0;		//清除提示显示
  		     	counter_flag_se=0;//		
	        	maske=0;			
		    	}
					
			}
		}
	}
	else
	{
		
//		Jiemamounttemp = FPGARW(MesMount)&0x00ff;	//接收信息数的低8位
//		mesend1 = FPGARW(MesEnd)&0x00ff;
		if(Jiemamounttemp==0)						//如果最后一波为无效信息
		{
			if(Jiemamounte!=0)
			MesDeal();
			if(msgover==1)
			{
			flag_s=0;		//清除提示显示
  			counter_flag_se=0;//	
	    	maske=0;				
			}
		}
		else
		{
			for(i=0;(i<Jiemamounttemp)&&(1+i+Jiemamounte<3600);i++)
			{
				Blocke[1+i+Jiemamounte]=FPGARW(i);    
			}
			Jiemamounte=Jiemamounte+Jiemamounttemp;	
		}
	}
   }
   if(whichchannel==0x0f)
   {
	if(G_Key&0x40)   //正文已结束
	{
	
//		Jiemamounttemp = FPGARW(MesMount)&0x00ff;	//接收信息数的低8位
/**/	if(Jiemamounttemp==0)
		{
			if(Jiemamountc!=0)
			MesDeal();
			if(msgover==1)
			{
			flag_s=0;		//清除提示显示
  			counter_flag_sc=0;//	
	    	maskc=0;				
			}
		}
		else
		{
			mesend=FPGARW(MesEnd)&0x00ff;			//读取最后一波的前一条信息数
			if(mesend==0)							//如果最后一波的前一条信息数为0，则直接处理这条信息
			{
				flag_more_message =1;    //???
				if(Jiemamountc!=0)
				MesDeal();                   
			if(msgover==1)
			{
			flag_s=0;		//清除提示显示
  			counter_flag_sc=0;//
	    	maskc=0;					
			}
			}
			else
			{
				if(Jiemamounttemp>mesend) flag_more_message =1;
				else
				{	
					//flag_s=0;		//清除提示显示
  				//	counter_flag_s=0;//	
				}
				Jiemamounttemp = mesend;
				for(i=0;(i<Jiemamounttemp)&&(1+i+Jiemamountc<3600);i++) 
				{
				Blockc[1+i+Jiemamountc]=FPGARW(i);    //??why not begin with 2+i??
				}
				Jiemamountc=Jiemamountc+Jiemamounttemp;
				MesDeal();	
    			if(msgover==1)
		    	{
		    	flag_s=0;		//清除提示显示
  		     	counter_flag_sc=0;//
	        	maskc=0;					
		    	}			
			}
		}
	}
	else
	{
		
//		Jiemamounttemp = FPGARW(MesMount)&0x00ff;	//接收信息数的低8位
//		mesend1 = FPGARW(MesEnd)&0x00ff;
		if(Jiemamounttemp==0)						//如果最后一波为无效信息
		{
			if(Jiemamountc!=0)MesDeal();
			if(msgover==1)
			{
			flag_s=0;		//清除提示显示
  			counter_flag_sc=0;//
	    	maskc=0;		
			}
		}
		else
		{
			for(i=0;(i<Jiemamounttemp)&&((1+i+Jiemamountc)<3600);i++)
			{
				Blockc[1+i+Jiemamountc]=FPGARW(i);    
			}
			Jiemamountc=Jiemamountc+Jiemamounttemp;	
		}
	}
   }
  }
  else
  {
    	Fpga_reset();				//FPGA初始化
    	Jiemamounte=0;
    	Jiemamountc=0;
 		  flag_s=0;		//清除提示显示
  		counter_flag_se=0;//
  		counter_flag_sc=0;//
    	maske=0;
    	maskc=0;
		flag_more_message=0;
  }
}




/**********************************
定时器中断函数
*******************************/
/*void isrTimer0Compare ();
void isrTimer0Compare ()
{
    #pragma interrupt saveall    //堆栈等寄存器保存
 	int i=0,j,days,hours,minutes;
    TMR0_SCR&=~TMR0_SCR_TCF_MASK;   //清中断标志位
    
    if((MessageProcess&0x01)==0)
    {
       	TMR0_SCR&=~TMR0_SCR_TCFIE_MASK;	//关闭64K的定时器0的中断
       	if(MessageProcess&0x02)			//bit1位为1，说明需进行信息删除操作
       	{
 //     		for(i=0;i<Messageinfo.savenumber[0];i++)	//找出需处理信息在Messagetoprank[]中位置，用i记录
//			{
//				if(EpromAddNow==Messagetoprank[i]) break;	
//			}
			for(j=0;j<Messageinfo.savenumber[0];j++)
			{
				days=DatesToDays(Messagesavetop[Messagetoprank[j]].date[0],Messagesavetop[Messagetoprank[j]].date[1],Messagesavetop[Messagetoprank[j]].date[2]);
				hours=Messagesavetop[Messagetoprank[j]].time[0];	//获取小时数
				minutes=Messagesavetop[Messagetoprank[j]].time[1];	//获取分钟	
				TODCS|=TODCS_TOD_LOCK_MASK;//开启TOD_Lock位，读取TOD模块中时间的寄存器 
//				if(((days+3)<TODDAY)||(((days+3)==TODDAY)&&hours<TODHR)||
//					(((days+3)==TODDAY)&&(hours==TODHR)&&(minutes<=TODMIN)))
				if(((days+3)<TODDAY)||(((days+3)==TODDAY)&&hours<TODHR)||
					(((days+3)==TODDAY)&&(hours==TODHR)&&(minutes<=TODMIN)))
				{
//					MesDel(j);				//这里还需要进行锁定信息的判断
//					j--;
					if(Messagesavetop[Messagetoprank[j]].lock==0)//非锁定信息的步骤
					{
						Msgdel(j);
						j--;
					}
				}
				TODCS&=~TODCS_TOD_LOCK_MASK;//关闭TOD_Lock锁定位 
					
			}
			FindMsg();
 //      	   	MesDel(i);
 //      	   	FindMsg();
       	   	MessageProcess&=0xfd;//bit1位清零
       	}
       	
		
       	if(MessageProcess&0x04)
       	{
       		if(MessageProcess&0x08)	//需进行信息替换处理
       		{
       			
   				for(i=0;i<Messageinfo.savenumber[0];i++)//检测此信息是否为新信息，方法：三天有无接收相同标记的信息，
														//有则说明之前已接受过，abondan置1,当deal为0都是未经过三天处理，若deal为1则须考虑
														//特殊情况，即此时的信息正在三天处理的周期内，判断条件为EpromAddNow==Messagetoprank[i]
				{
					if((Messagesavetop[Messagetoprank[i]].dealed==0||
					   (Messagesavetop[Messagetoprank[i]].dealed==1&&EpromAddNow==Messagetoprank[i]))&&	
					   Messagetemptop.mark[0]==Messagesavetop[Messagetoprank[i]].mark[0]&&
					   Messagetemptop.mark[2]==Messagesavetop[Messagetoprank[i]].mark[2]&&
					   Messagetemptop.mark[1]==Messagesavetop[Messagetoprank[i]].mark[1]&&
					   Messagetemptop.mark[3]==Messagesavetop[Messagetoprank[i]].mark[3]
					   )
					   break;
				}
				
				 if(i!=Messageinfo.savenumber[0]) //表示接收过当前信息
				 {

					if(Messagesavetop[Messagetoprank[i]].lock==0)
					{
						if(Messagesavetop[Messagetoprank[i]].dealed==1)
						{
							Msgdel(i);
							FindMsg();
						}
						else
						{
							Msgdel(i);
						}
					}				 	
				 }
				 MessageProcess&=0xf7;
       			
       		}
       		NewMsg_Save();	//存储新信息
       		MessageProcess&=0xfb;//bit2位清零
       	}
       
    }

}  */
/*********************************每次存新信息前对已超过三天的信息进行扫描并删除**********/
void mesdeletelook()
{
    u16 i,j,days,daysnow,hours,minutes,addressa,deletenum=0,temp=Messageinfo.savenumber[0],q=0;
	for(j=0;j<temp;j++)
    {
	days=DatesToDays(Messagesavetop[Messagetoprank[j]].date[0],Messagesavetop[Messagetoprank[j]].date[1],Messagesavetop[Messagetoprank[j]].date[2]);
	hours=Messagesavetop[Messagetoprank[j]].time[0];	//获取小时数
	minutes=Messagesavetop[Messagetoprank[j]].time[1];	//获取分钟	
//	TODCS|=TODCS_TOD_LOCK_MASK;//开启TOD_Lock位，读取TOD模块中时间的寄存器 
//	timestruct=GetTime();
	daysnow=DatesToDays(timestruct.year,timestruct.month,timestruct.day);
	if(((days+3)<daysnow)||(((days+3)==daysnow)&&hours<timestruct.hour)||(((days+3)==daysnow)&&(hours==timestruct.hour)&&(minutes<=timestruct.minute)))
	{
	
		if(Messagesavetop[Messagetoprank[j]].lock==0)//非锁定信息的步骤
     	{
			Msgdel(j);
			j--;
			temp--;
	        deletenum++;
		}
	
		else
	    {
	    	Messagesavetop[Messagetoprank[j]].dealed=1;
	    	i=Messagetoprank[j];
		    addressa=i*MESSTYPELENGTH+17;
           	Write_Char_Eprm(addressa,1); 
  //          COPCTR=0xAAAA;
  //          COPCTR=0x5555;
	    }
//  	  deletenum++;
//        COPCTR=0xAAAA;
//        COPCTR=0x5555;
	}
//	TODCS&=~TODCS_TOD_LOCK_MASK;//关闭TOD_Lock锁定位 	
	if(deletenum>=3)
	break;				
	}	
}