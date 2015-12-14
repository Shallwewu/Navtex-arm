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
#define MesMount 	 299	//��Ϣ����ȡλ��
#define	MesEnd		297	//Ϊ��Ϣ������־��ͬʱҲ�洢��				  ����400���ַ��ӿ�ʼ����Ϣ������				  ����
#define	CERH		296	//������ֽ�
#define	CERL		295	//������ֽ�
#define msgisover   291
#define BLOCK_SIZE   32768	//32k���С�Ķ���
#define whchannel   292
void mesdeletelook();
//static Block1;
//*************************************************   
//���ܣ�����Ϣ�Ĵ������½��A
//��ڲ�������
//���ڲ�������
//*************************************************
/*void Flasherror_Paintintial();
void Flasherror_Paintintial()
{
	byte i;
	WFRAME();		//�����Ӳ˵���ͼ��ʾ
    IntialLCD(1);


	    
	   	CTAB[4]=42;  CTAB[5]='E';   CTAB[6]='R';  CTAB[7]='R'; 
	   	CTAB[8]='O';  CTAB[9]='R'; CTAB[10]=42;
	    CW_PR(9,10,11);	//��ͷ SETUP
	    

	      
	    CTAB[5]='F';  CTAB[6]='L';  CTAB[7]='A';  CTAB[8]='S';  CTAB[9]='H'; 
	    CW_PR(9,11,10);	//��һ�����ݣ�UNLOCK MSG
	    

	      
	    CTAB[4]='O'; CTAB[5]='V';  CTAB[6]='E';  CTAB[7]='R';  CTAB[8]='F';  CTAB[9]='L'; 
	    CTAB[10]='O'; CTAB[11]='W'; 
	    CW_PR(9,12,12);	//�ڶ������ݣ�PRINT MSG
	    

}    */
void ENABLEIRQB(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½����ж�
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}

void DISABLEIRQB(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
  EXTI_InitStructure.EXTI_Line = EXTI_Line1;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½����ж�
  EXTI_InitStructure.EXTI_LineCmd = DISABLE;
  EXTI_Init(&EXTI_InitStructure); 
}

void ENABLEIRQA(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½����ж�
  EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  EXTI_Init(&EXTI_InitStructure); 
}

void DISABLEIRQA(void)
{
	EXTI_InitTypeDef EXTI_InitStructure;
  EXTI_InitStructure.EXTI_Line = EXTI_Line0;
  EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
  EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; //�½����ж�
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
//		flag_s=0;		//�����ʾ��ʾ
 //       counter_flag_s=0;//	
	}
	if(flag_new_message==1)		//modified@2010-10-9
	{
/*	   if(msgover==1)
	   {
		flag_s=0;		//�����ʾ��ʾ
  		counter_flag_s=0;//	
	    first2=0;
	   }  */
		SaveTime();
		FLAG=0;
		if(STATE==16)now_printing=1;
		STATE=1;	
		BUFFER[0]=0;
		State1parameter=0;		//Ϊ��ָ������Ϣ������ֱ�ӱ�ʾ�Ӵ洢������� ������DISP���룬�޷��ؼ�����modified@2010-8-17
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
//		flag_s=0;		//�����ʾ��ʾ
 //       counter_flag_s=0;//	
	}
	if(flag_new_message==1)		//modified@2010-10-9
	{
/*	   if(msgover==1)
	   {
		flag_s=0;		//�����ʾ��ʾ
  		counter_flag_s=0;//	
	  	first2=0;
	   }     */
		SaveTime();
		FLAG=0;
		if(STATE==16)now_printing=1;
		STATE=1;	
		BUFFER[0]=0;
		State1parameter=0;		//Ϊ��ָ������Ϣ������ֱ�ӱ�ʾ�Ӵ洢������� ������DISP���룬�޷��ؼ�����modified@2010-8-17
	}
   }
 }


//*************************************************   
	//MESDEL()����
	//���ܣ���������ʱ����Ϣ��ɾ������
	//��ڲ�����numtoprankΪ�账����Ϣ��Messagetoprank[]��λ��
	//���ڲ�������
	
	//Msgdel()����
	//���ܣ���Ϣ��ɾ������
	//��ڲ�����numtoprankΪ��ɾ����Ϣ��Messagetoprank[]��λ��
	//���ڲ�������	
//*************************************************


void Msgdel(int numtoprank);
void Msgdel(int numtoprank)
{
	sword i,j,k,read;
	
	sword position=Messagetoprank[numtoprank];

	DelAMessFlash(position);	//ɾ����Ϣ��FLASH���еĴ洢���ݣ�ͬʱ�޸�Flashmap[](�ڴ��Eprom)
	
	j=position/8;	//���ڵ��ֽ���
	k=position%8;	//���ڵ�bitλ
	Eprommap[j]&=~(0x01<<k);	//��Ӧbitλ��0
	
	Write_Char_Eprm(EprommapStart+j,Eprommap[j]);//�޸Ĵ洢��eprom�е�״̬���Ӧ״̬
	
	
	read=Messagesavetop[Messagetoprank[numtoprank]].read;	//1δ��;0�Ѷ�
	if(read)
	{
		Unread--;
		Write_Int_Eprm(UNREAD_MSG,Unread);			//�洢Unread��Eprom	
	}
	
	for(i=numtoprank;i<Messageinfo.savenumber[0]-1;i++)		//Messagetoprank[]�޸�
	{
		Messagetoprank[i]=Messagetoprank[i+1];
	}
	Messagetoprank[i]=0;
	Messageinfo.savenumber[0]--;		//����Ϣ����1
	Messageinfo.nownumber[0]=Messageinfo.savenumber[0]-1;
	Messageinfo.savenumber[Messagesavetop[position].frequency]--;	//��Ӧͨ����Ϣ����1			
	WriteMesinfo();					//�洢�޸������Ϣͷ�ļ���Eprom	
//	COPCTR=0xAAAA;
//    COPCTR=0x5555;	
	
}


/*void MesDel(int numtoprank);
void MesDel(int numtoprank)
{



	int position=Messagetoprank[numtoprank];
	MessageProcess|=0x10;	//MessageProcess��bit4��1����ʾ��ʱ���ڽ�����Ϣɾ������

	if(Messagesavetop[position].lock==0)//��������Ϣ�Ĳ���
	{
		if(MessageProcess&0x01)
		{
			MessageProcess|=0x02;	//MessageProcess��bit1λ��1
			TMR0_SCR|=TMR0_SCR_TCFIE_MASK;	//����8K�Ķ�ʱ��0���ж�
		}
		else
		{
			Msgdel(numtoprank);
		}

	}

	MessageProcess&=0xef;	//MessageProcess��bit4��0����ʾ��ʱ�����Ϣɾ������ 

	
//������Ϣ������в���

}  */
/************ɾ��һ���������Ϣ********/
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
		if(Messageinfo.savenumber[0]==0) position=0xffff;		//��ʱ�޴洢��Ϣ������0xffff
		else
		{
			if(position==0xffff)
			{
				//do nothing
			}
			else
			{	
				for(l=position_temp+1;l<Messageinfo.savenumber[0];l++)		//�ҳ�δ�������Ϣ��������յ�����Ϣ������i
				{
					i=Messagetoprank[l];
					if(Messagesavetop[i].lock==1) 
					{
						Messagesavetop[i].dealed=1;
					    addressa=i*MESSTYPELENGTH+17;
                       	Write_Char_Eprm(addressa,1); 
					    continue;	//������Ϣ����
						
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
		Msgdel(position_temp2);			//ɾ����Ϣ
}
/*************************************************   
  /*���ܣ�����Ϣ�Ĵ洢
��ڲ�������
���ڲ�������
*************************************************/
void NewMsg_Save();
void NewMsg_Save()
{
	sword i,days,n;
	sword position,position_temp,position_temp2=0,l;
    mesdeletelook();
//	MessageProcess|=0x10;	//MessageProcess��bit4��1����ʾ��ʱ���ڽ�����Ϣ��Ӳ���	
	/*1.��ɴ�Messagetemptop�л�ȡ��ص���Ϣд��Messagesavetop[Messsagetoprank[Messageinfo.savenumber[0]]]
	�У���EpromAdd�����Ϣ���������ڻ�������������Ϣ��ʽ���ݿ�*/
	for(i=0;i<75;i++)//3.���ҵ�ǰ�Ŀ���λ�ã���i��n��¼,
	{
		for(n=0;n<8;n++)
		{
			if((Eprommap[i]&(0x01<<n))==0) break;
		}
		
		if(n!=8) 	
		{
			Eprommap[i]|=(0x01<<n);	//�ڶ�Ӧλ����1
			break;
		}
	}

	if(n==8) //�洢���洢��Ϣ�����Ѿ�����600������Ҫ������Ϣ�������
	{
        deleteoldmess();
		for(i=0;i<75;i++)	//�������ҵ�ǰ�Ŀ���λ�ã���i��n��¼,
		{
			for(n=0;n<8;n++)
			{
				if((Eprommap[i]&(0x01<<n))==0) break;
			}
			
			if(n!=8) 	
			{
				Eprommap[i]|=(0x01<<n);	//�ڶ�Ӧλ����1
				break;
			}
		}		
		//ֻ����б���������ʱ�䲻���ܳ����յ�600����Ϣ������ض��еط�����
		//���������춨ʱ������Ҳ���ܳ������
	}
	
	//�ҵ�����λ�ã���1�����ڶ�Ӧͷ�ļ���д���Ӧ����λ��
			
		
	Messagetoprank[Messageinfo.savenumber[0]]=i*8+n;//�洢��Ϣ��λ�ã������ʱ��ֻ��Ķ�Messagetoprank���ɣ�����Ķ��ṹ��Messagsavetop
	/*1.��Flash����״̬���ײ���ʼ��Ѱ�������㹻�ķ����洢�ļ���Flash����״̬���ж�Ӧλ״̬��11
	Eprom�ж�Ӧ��״̬��Ҳ�����޸ģ�ͬʱ���ļ������������Ϣ(������ʼ�����������ͷ�������)�����½��ļ�Ŀ¼*/

	WriteAMessToFlash(Messagetoprank[Messageinfo.savenumber[0]],Block1);//��ʱBlock1����Ч��δ�ջض�̬�ռ�	
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
	Write_Char_Eprm(EprommapStart+i,Eprommap[i]);//6.�޸Ĵ洢��eprom�е�״̬���Ӧ״̬

	
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
	Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]]].dealed=0;				//0��ʾδ�������촦��
	Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]]].lock=0;				//0δ����
	Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]]].select=0;				//0δ��ѡ
	Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]]].read=1;				//��Ϣδ��
	Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]]].cer=Messagetemptop.cer; //������	
	Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]]].amount=Messagetemptop.amount; //@wu	


	/*4.�洢��Ϣͷ�ļ���Eprom*/
	Save_A_Message_Eprom(Messagetoprank[Messageinfo.savenumber[0]]);

	/*5.��Ϣ��ͷ�ļ����޸��Լ�д��Eprom,��ʱ����Ҫ�޸Ķ�Ӧͨ���������Լ�δ����Ϣ��*/
	Messageinfo.savenumber[0]++;						//����Ϣ����1
	Messageinfo.savenumber[Messagetemptop.frequency]++;	//��Ӧͨ����Ϣ������1
	
	/*7�ж��Ƿ���Ҫ�������춨ʱ��*/
/*	if(ThreeDayAlarm)	//���ThreeDayAlarmΪ1����Ҫ���� 
	{
//		Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]-1]].dealed=1;	//��Ϣdealedλ��1
		
//		WritebitDeal(Messagetoprank[Messageinfo.savenumber[0]-1]);				//��ӦEpromλд��1
		
//		EpromAddNow=Messagetoprank[Messageinfo.savenumber[0]-1];											//�´��账����Ϣi����EpromAddNow
		/*3.ȡ���账����Ϣ��ʱ�䣬���붨ʱ����������ʱ��
		//������ڵ�������ת��
		days=DatesToDays(Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]-1]].date[0],Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]-1]].date[1],Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]-1]].date[2]);
		TODDAL=days+3;												//д������
		TODHAL=Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]-1]].time[0];	//д��Сʱ��
		TODMAL=Messagesavetop[Messagetoprank[Messageinfo.savenumber[0]-1]].time[1];	//д�����

		TODCS|=TODCS_TODAEN_MASK;									//������ʱ�����ж�	
		ThreeDayAlarm=0;											//ThreeDayAlarm��0����������Ϣ�����迪����ʱ��
	}*/
	
	Messageinfo.nownumber[0]=Messageinfo.savenumber[0]-1;//�յ�����Ϣ��ʹMessageinfo.nownumber[0]ָ������Ϣ
	WriteMesinfo();								//���޸���ϵ�Messinfo����Eprom

	Unread++;
	Write_Int_Eprm(UNREAD_MSG,Unread);			//�洢Unread��Eprom

    if(Messagetemptop.mark[1]=='D')//D��Ϣ
	{
		FPGARW(3600)=0x04;
		Buzzerstate|=0x01;        
	}        
	else if((Messagetemptop.mark[1]=='A'||Messagetemptop.mark[1]=='B'||Messagetemptop.mark[1]=='L')&&Buzzer[1])//ABL&&������
	{
		FPGARW(3600)=0x04;
		Buzzerstate|=0x01;	
	}
	else	//�յ���ͨ��Ϣ
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
//	RunNewmsgtip();	//��ʾ�յ�����Ϣ����ʾ�˵�
/*�������Ϣ�յ�������ʾzzy@2010-6-9*/

//	if(Jietiaomounttemp==0)
/*	{
		FLAG=0;
		STATE=1;	
		BUFFER[0]=0;
		State1parameter=0;		//Ϊ��ָ������Ϣ������ֱ�ӱ�ʾ�Ӵ洢������� ������DISP���룬�޷��ؼ�����modified@2010-8-17
		CLEAR1();
//	}
*/	
/*����Ϣ�յ�������ʾ�������*/	
//	MessageProcess&=0xef;	//MessageProcess��bit4��1����ʾ��ʱ�����Ϣɾ������
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
	/*���ܣ���Ϣ������
	��ڲ�����numtoprankΪ�������Ϣ��Messagetoprank[]��λ��
	���ڲ�������
*************************************************/
void MsgLock(int numtoprank);
void MsgLock(int numtoprank)
{	
	char k;
	sword num=Messagetoprank[numtoprank];	//��ȡnumtoprank��ָ���ͷ�ļ�λ�� 
  DISABLEIRQA();
//	MessageProcess|=0x01;		//��ʱ�ڽ�����Ϣ�������
	/*1,��ǰ��������Ϣlockλ��1���ҳ���ǰ��Ϣ��ͨ������k,*/
	k=Messagesavetop[num].frequency;	//����k��¼��ǰ��Ϣͨ��
	Messagesavetop[num].lock=1;			//�������λlock��1
	LockAMessageHeader(num);			//��ӦEprom��lockλ��1
	
	/*2.��Ϣ��ͷ�ļ����޸��Լ�д��Eprom*/
	Messageinfo.locknumber[0]++;	//������Ϣ����1
	Messageinfo.locknumber[k]++;	//��Ӧͨ����Ϣ����1
	WriteMesinfo();					//�洢�޸������Ϣͷ�ļ���Eprom
  ENABLEIRQA();
//	MessageProcess&=0xfe;			//��Ϣ���������ϣ�bit1λ��0
}



//*************************************************   
	//���ܣ���Ϣ�Ľ���
  	//��ڲ�����numtoprankΪ�������Ϣ��Messagetoprank[]��λ��
//*************************************************
void MsgUnlock(int numtoprank);
void MsgUnlock(int numtoprank)
{ 

/*1.	����Ŀ¼�е��ļ����������Ϣ�ҵ���Ӧ����
2.	�жϷ����������������(Flash�Ĳ�����Ϊ2K�֣�����4������)����������״̬�Ƿ�01(�ǿ��е�δ����)��
3.	���������������4�������Ķ�Ӧλ״̬����00��ͬʱ���п������������ֻ֮���ļ���������Ķ�Ӧ״̬λ��01��
4.	����Ŀ¼��Ŀ¼���������Ϣ����Ŀ¼��������Ķ�Ӧ״̬λ��0��
5.	ɾ���ļ�Ŀ¼���޸Ĵ洢��E2prom�����ŷ���״̬��*/
	u8 channel,read;
	u16 days,daysnow,hours,minutes;
	sword j,k,overtime=0,meslocknum,i=0;//j���ڼ�¼�������Ϣ��������Ϣͷ�ļ������е�λ��
	sword num=Messagetoprank[numtoprank];	//��ȡnumtoprank��ָ���ͷ�ļ�λ��
  DISABLEIRQA();
//	MessageProcess|=0x01;		//��ʱ�ڽ�����Ϣ�������
	/*1.�ж��������Ϣ�Ľ���ʱ���Ƿ��ѹ�3�죬�ò���overtime����ʾ��1Ϊ����3�죬
    	0��ʾδ����*/
	days=DatesToDays(Messagesavetop[num].date[0],Messagesavetop[num].date[1],Messagesavetop[num].date[2]);
//	years=Messagesavetop[num].date[0];
//	months=Messagesavetop[num].date[1];
//	days=Messagesavetop[num].date[2]
	hours=Messagesavetop[num].time[0];
	minutes=Messagesavetop[num].time[1];	//��ȡ��Ӧ��Ϣ��ʱ�� 	

//	TODCS|=TODCS_TOD_LOCK_MASK;		//����TOD_Lockλ����ȡTODģ����ʱ��ļĴ��� 
/*	
	if(((days+3)<TODDAL)||(((days+3)==TODDAL)&&hours<TODHAL)||
	(((days+3)==TODDAL)&&(hours==TODHAL)&&(minutes<TODMAL)))*/
//	timestruct=GetTime();   @wu
	daysnow=DatesToDays(timestruct.year,timestruct.month,timestruct.day);
	if(((days+3)<daysnow)||(((days+3)==daysnow)&&hours<timestruct.hour)||
	(((days+3)==daysnow)&&(hours==timestruct.hour)&&(minutes<=timestruct.minute)))
	overtime=1;						//�������Ϣ��3��֮ǰ�յ���overtime��1	
			
//	TODCS&=~TODCS_TOD_LOCK_MASK;	//�ر�TOD_Lock����λ 
    if(Messagesavetop[Messagetoprank[numtoprank]].dealed==1)
    {
        overtime=1;	
    }
	/*2��ɶ�Ӧͷ�ļ�lock��0,ͬʱ�޸�Eprom��Ӧlockλ����ʱ�䳬�����죬���Ӷ�FLASH
	   �洢���и����ݵ�ɾ��*/
	if(overtime==1)	//ʱ�䳬������
	{
		DelAMessFlash(num);	//ɾ����Ϣ��FLASH���еĴ洢���ݣ�ͬʱ�޸�Flashmap[](�ڴ��Eprom)
		
		j=num/8;	//���ڵ��ֽ���
		k=num%8;	//���ڵ�bitλ
		Eprommap[j]&=~(0x01<<k);	//��Ӧbitλ��0
		Write_Char_Eprm(EprommapStart+j,Eprommap[j]);//�޸Ĵ洢��eprom�е�״̬���Ӧ״̬
//
		read=Messagesavetop[Messagetoprank[numtoprank]].read;	//1δ��;0�Ѷ�
		if(read)
		{
			Unread--;
			Write_Int_Eprm(UNREAD_MSG,Unread);			//�洢Unread��Eprom	
		}
		
		for(i=numtoprank;i<Messageinfo.savenumber[0]-1;i++)		//Messagetoprank[]�޸�
		{
			Messagetoprank[i]=Messagetoprank[i+1];
		}
		Messageinfo.savenumber[0]--;		//����Ϣ����1
		Messageinfo.savenumber[Messagesavetop[num].frequency]--;	//��Ӧͨ����Ϣ����1
 //       COPCTR=0xAAAA;
 //       COPCTR=0x5555;
	}

	else	//ʱ��δ�������죬ֻ���޸�lockλ
	{
		Messagesavetop[num].lock=0;
		UnlockAMessageHeader(num);			//��ӦEprom��lockλ��0
		State1parameter=10;					//��ʱ������Ϣδ��ɾ��
	}
	
	Messageinfo.locknumber[0]--;	//��������Ϣ����1
	Messageinfo.locknumber[Messagesavetop[num].frequency]--;	//��Ӧͨ����Ϣ����1	
/*
	if(STATE==12&&(Returntype==2||Returntype==4))	//������Ϣ����Ϣ�˵��Ӳ˵��½��У�����Ϣ�˵��������˵�����
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
		Messageinfo.nownumber[1]=0;		//�ı�nownumber[1]��ʹ��ָ�����һ��������Ϣ��ͬʱ�ı�Returntype

		State1parameter=4;				//State1parameter��ֵ�����ı�˵������Ϣɾ���������ٴν�����Ϣ�˵�
										//ʱ����Ҫ����ˢ��		
	}
	
	if(STATE==12&&(Returntype==0||Returntype==1||Returntype==3))//�洢�˵�������Ϣ�˵�������Ϣ�˵��µĽ���
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
	if(STATE==12&&(Returntype==2||Returntype==4))	//������Ϣ����Ϣ�˵��Ӳ˵��½��У�����Ϣ�˵��������˵�����
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
			Messageinfo.nownumber[1]=0;		//�ı�nownumber[1]��ʹ��ָ�����һ��������Ϣ��ͬʱ�ı�Returntype
		if(Messageinfo.savenumber[0]>0)
			Messageinfo.nownumber[0]=Messageinfo.savenumber[0]-1;
		else
			Messageinfo.nownumber[0]=0;
		
		State1parameter=4;				//State1parameter��ֵ�����ı�˵������Ϣɾ���������ٴν�����Ϣ�˵�
										//ʱ����Ҫ����ˢ��		
	}
	
	if(STATE==12&&(Returntype==0||Returntype==1||Returntype==3))//�洢�˵�������Ϣ�˵�������Ϣ�˵��µĽ���
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
			Messageinfo.nownumber[1]=0;		//�ı�nownumber[1]��ʹ��ָ�����һ��������Ϣ��ͬʱ�ı�Returntype
		if(Messageinfo.savenumber[0]>0)
		Messageinfo.nownumber[0]=Messageinfo.savenumber[0]-1;
			else
			Messageinfo.nownumber[0]=0;
		if(Returntype)
			State1parameter=3;
		else
			State1parameter=0;
	}
	if(STATE==2000)//�洢�˵�������Ϣ�˵�������Ϣ�˵��µĽ���
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
			Messageinfo.nownumber[1]=0;		//�ı�nownumber[1]��ʹ��ָ�����һ��������Ϣ��ͬʱ�ı�Returntype
		if(Messageinfo.savenumber[0]>0)
			Messageinfo.nownumber[0]=Messageinfo.savenumber[0]-1;
		else
			Messageinfo.nownumber[0]=0;
	}

	WriteMesinfo();				//�洢�޸������Ϣͷ�ļ���Eprom
//	MessageProcess&=0xfe;		//��Ϣ���������ϣ�bit1λ��0
  ENABLEIRQA();
} 





/*************************************************   
	���ܣ��ӽ��յ�����FPGA������ɵ���Ϣ���ҳ�
		  ��Ϣͷ�ļ��洢��ȫ�ֱ���Messagetemptop��;
	��ڲ�������
	���ز�������
 *************************************************/
void Savetemptop();
void Savetemptop()
{
	
	static sword i=0; 
	word cernum=0;
//	cer=(word)(FPGARW(CERH)&0x00ff);	//��ȡ��8λ
//	cer=cer<<8;
//	cer=cer+(word)(FPGARW(CERL)&0x00ff);	//��ȡ��Ϣ���ֽ���
    for(i=0;i<Jiemamount;i++)
    {
    	if(Block1[i]=='*')
    	{
    		cernum++;
    	}
    }
	Messagetemptop.cer=((uint32)cernum)*100/((uint32)Jiemamount-2);	//��ȡ��Ϣ��������  @wu

	Messagetemptop.mark[0]=Block1[2];	//���������Ϣֱ�Ӵ�B1B2B3B4��ʼ
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
			case(34):Messagetemptop.mark[i]='H';break;//' "  '˫����
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
			case(39):Messagetemptop.mark[i]='S';break;//' ' '������
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

/*	Messagetemptop.mark[0]=Block1[3];	//���������Ϣֱ�Ӵ�B1B2B3B4��ʼ
	Messagetemptop.mark[1]=Block1[4];
	Messagetemptop.mark[2]=Block1[5];	
	Messagetemptop.mark[3]=Block1[6];*/

//		if(Dingxiang[1]==1)//(G_Key&0x20)//Messagetemptop.frequency=2;//JietiaoResult[0].frequency;		//ͨ���洢
//		{
//			if(Workfre)
//   	  		Messagetemptop.frequency=2;   	//486ͨ����Ӧ2
//   	   	else
//  	    		Messagetemptop.frequency=3;	//4Mͨ����Ӧ3		
//		}
//		else
//			Messagetemptop.frequency=1;
	if(manual_area==0)
	{
 		manual_area=11;
		Eprom_ManualMsgMode_Save(RXSTATION_MANUAL);	//������Ϣ����Eprom		
	}
		
	if(Mode==1)
		Messagetemptop.area=manual_area;			//
	else
		Messagetemptop.area=auto_area;
//	TODCS|=TODCS_TOD_LOCK_MASK;		//����TOD_Lockλ����ȡTODģ����ʱ��ļĴ��� 
//	DaysToDates(TODDAY,&Messagetemptop.date[2],&Messagetemptop.date[1],&Messagetemptop.date[0]);
//	timestruct=GetTime();
  Messagetemptop.date[2]=timestruct.day;
  Messagetemptop.date[1]=timestruct.month;
	Messagetemptop.date[0]=timestruct.year;
	Messagetemptop.time[1]=timestruct.minute;
	Messagetemptop.time[0]=timestruct.hour;
//	TODCS&=~TODCS_TOD_LOCK_MASK;//�ر�TOD_Lock����λ 
	SaveTime();	
}
 
 

	

	
//*************************************************   
	//���ܣ�����Ϣ�Ĵ�����
	//��ڲ�������
	//���ڲ�������
//*************************************************
void MesDeal();
void MesDeal()
{
	char channel,navtexstation,abandon=0,navtexsarea,msgtype,cer,avail=0;
	sword i,temp,cherr=0;
	sword chnnnn=0;
	sword jiemamount_temp=0;
//	Intial_Message();  //����DSP�ⲿSRAM����,���¼���
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
  	  		Messagetemptop.frequency=2;   	//486ͨ����Ӧ2
   	   	else
      		Messagetemptop.frequency=3;	//4Mͨ����Ӧ3	
    }
    else
    {
    	Jiemamount=0;
    }
	if(Jiemamount)
	{
		Jiemamount=Jiemamount+2;	//���ӵ�2λ�ֱ��ʾ��2���ֽ��������ڶ�ȡ���ݵ�һ��λ�գ���ʡ��һ���ֽڣ�1NULL
		jiemamount_temp=Jiemamount;
		Block1[0]=Jiemamount>>8;	//���ֽ����ĸ�8λ
		Block1[1]=Jiemamount;		//���ֽ����ĵ�8λ
     	Messagetemptop.amount=Jiemamount;
		Savetemptop();
		Jiemamount=0;					//һ����Ϣ������ϣ�����ʹ��ȫ�ֱ���
		channel=Messagetemptop.frequency-1;		//��ȡ��ǰ��Ϣ��ͨ�����洢��ʱ��Ϊ1~3����һת��
		navtexsarea=Messagetemptop.area;		//��ȡ��ǰ��Ϣ���ڵķ�����������16��������
		navtexstation=Messagetemptop.mark[0]-65;//���ڴ洢����̨���ַ���ʾΪA~Z����ת��Ϊ��Ӧ��0~25
		msgtype=Messagetemptop.mark[1]-65;		//���ڴ洢��Ϣ������ַ���ʾΪA~Z����ת��Ϊ��Ӧ��0~25

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
	//				case('*'):Messagetemptop.mark[i]='D';break;  //???*����������??
					case('3'):Messagetemptop.mark[i]='E';break;
					case('%'):Messagetemptop.mark[i]='F';break;
					case('#'):Messagetemptop.mark[i]='G';break;
					case(34):Messagetemptop.mark[i]='H';break;//' "  '˫����
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
					case(39):Messagetemptop.mark[i]='S';break;//' ' '������
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
			if(Messagetemptop.mark[2]=='0'&&Messagetemptop.mark[3]=='0')	//�յ�00��Ҫ��Ϣ
	//		if(Messagetemptop.mark[2]=='4'&&Messagetemptop.mark[3]=='9')	//�յ�00��Ҫ��Ϣ
			{
			//		TMR0_SCR|=TMR0_SCR_TCFIE_MASK;	//������Ϣ�����ж�			    
	//			if(MessageProcess&0x01)
	//			{
	//				MessageProcess|=0x04;	//MessageProcess��bit2λ��1
	//				TMR0_SCR|=TMR0_SCR_TCFIE_MASK;	//������Ϣ�����ж�
	//			}
	//			else
	           if(Messagetemptop.cer>33) 
	            {
	               ResultA();	
	            }
    	            else
	            {
					NewMsg_Save();	//�洢����Ϣ	
	            }					
			}
			
			else
			{
//#if 0
//				if(Messagetemptop.mark[1]!='A'&&Messagetemptop.mark[1]!='B'&&
//				Messagetemptop.mark[1]!='D'&&Messagetemptop.mark[1]!='L')			//�յ����Ѿ���Ϣ
//				{
//#endif				
				if(Mode==0)							//�ж���Ϣ�Ƿ�����������õ�����
				{
					temp=Power(navtexsarea-1);
					if(Auto[channel][navtexstation]&temp) abandon=1;
	//				if((Auto[channel][navtexstation]&temp)!=0) abandon=1;
	//				if(Auto[channel][navtexstation]&(word)(pow(2,navtexsarea-1))) abandon=1;					
				}
				
				if(Mode==1&&Manual[channel][navtexstation]) abandon=1;	//�����㰶̨���ã�abandon��1
	//if((Mode==1)&&(Manual[channel][navtexstation]==1)) abandon=1;	//�����㰶̨���ã�abandon��1
				if(MSGTYPE[channel][msgtype]) abandon=1;				//��������Ϣ������ã�abandon��1
	//if(MSGTYPE[channel][msgtype]!=0) abandon=1;
	//            if(Messagetemptop.mark[0]=='S') abandon=1;
	            if((channel==1)||(channel==2))
	            {
					   for(i=18;i<jiemamount_temp-6;i++)
					   {
					   	
					   	    
					if(Block1[i]==0)                   //���ַ�??
					{
								//δ�����׵����ո���
							continue;
					}
					else if(((Block1[i]<='M')&&(Block1[i]>='A'))&&
					   ((Block1[i+1]<='Z')&&(Block1[i+1]>='A'))&&
					   ((Block1[i+2]<='Z')&&(Block1[i+2]>='A')))
					{
						//chinese[mountbyte_lcd++]=eng_to_lcd(&MessagePoint[i]);			//����ת��Ҫ��������ת��	
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
					 		//�����ֽ�
					   		//i���䣬�Զ���1
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
					   		//chinese[mountbyte_lcd++]=0xa3aa;				//���*
					   		cherr++;
					   		i=i+1;//��ʧ�ֽ�
					   		//i���䣬�Զ���1
					   }
					   else
					   {
					   		cherr++;
					   		//chinese[mountbyte_lcd++]=0xa3aa;				//���*
					   		i=i+2;//���򵱴����ֽڴ���
					   }
					}
					else if((Block1[i+1]>'Z')||(Block1[i+1]<'A'))
					{
					   if((Block1[i+1]=='\r')/*�س�*/||(Block1[i+1]=='\n'))
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
					   		//chinese[mountbyte_lcd++]=0xa3aa;				//���*
					   		i=i+3;//�����ֽ�
					   		//i���䣬�Զ���1
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
					   		//chinese[mountbyte_lcd++]=0xa3aa;				//���*
					   		i=i+1;//��ʧ�ֽ�
					   		//i���䣬�Զ���1
					   }
					   else
					   {
					   		cherr++;
					   		//chinese[mountbyte_lcd++]=0xa3aa;				//���*
					   		i=i+2;//���򵱴����ֽڴ���
					   }		
					}
					else if((Block1[i+2]>'Z')||(Block1[i+2]<'A'))
					{
						if((Block1[i+2]=='\r')/*�س�*/||(Block1[i+2]=='\n'))
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
					   		//chinese[mountbyte_lcd++]=0xa3aa;				//���*
					   		i=i+3;//�����ֽ�
					   		//i���䣬�Զ���1
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
					   		//hinese[mountbyte_lcd++]=0xa3aa;				//���*
					   		i=i+1;//��ʧ�ֽ�
					   		//i���䣬�Զ���1
					   }
					   else
					   {
					   		cherr++;
					   		//chinese[mountbyte_lcd++]=0xa3aa;				//���*
					   		i=i+2;//���򵱴����ֽڴ���
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
				if(abandon) ResultA();	//�յ���Ϊ���Ѿ���Ϣ���Ҳ����㰶̨������Ϣ�������
		
				
//				}			
				else
/*				
				if(Messagetemptop.mark[1]=='A'||Messagetemptop.mark[1]=='B'||
				Messagetemptop.mark[1]=='D'||Messagetemptop.mark[1]=='L'||
				(Messagetemptop.mark[1]!='A'&&Messagetemptop.mark[1]!='B'&&
				Messagetemptop.mark[1]!='D'&&Messagetemptop.mark[1]!='L'&&abandon==0))	//�յ������Ϣ�����յ��������Ϣ�����㰶̨����Ϣ�������
*/			
				{
					if(Messagetemptop.cer>33) ResultA();	//����Ϣ�����ʴ���33%��ִ�н��A  @wu
					else
					{
						for(i=0;i<=Messageinfo.savenumber[0];i++)//������Ϣ�Ƿ�Ϊ����Ϣ���������������޽�����ͬ��ǵ���Ϣ��
																//����˵��֮ǰ�ѽ��ܹ���abondan��1,��dealΪ0����δ�������촦����dealΪ1���뿼��
																//�������������ʱ����Ϣ�������촦��������ڣ��ж�����ΪEpromAddNow==Messagetoprank[i]
						{
							if(/*(Messagesavetop[Messagetoprank[i]].dealed==0)&&*/	
							   (Messagetemptop.mark[0]==Messagesavetop[Messagetoprank[i]].mark[0])&&
							   (Messagetemptop.mark[2]==Messagesavetop[Messagetoprank[i]].mark[2])&&
							   (Messagetemptop.mark[1]==Messagesavetop[Messagetoprank[i]].mark[1])&&
							   (Messagetemptop.mark[3]==Messagesavetop[Messagetoprank[i]].mark[3])&&
							   (Messagetemptop.frequency==Messagesavetop[Messagetoprank[i]].frequency))//added@2010-9-16������ͬ��ͨ����֮ǰ���յ�����Ϣ
							   break;
							   						
						}
						
						if(i==Messageinfo.savenumber[0]+1) //��ʾ���ѽ��չ���ǰ��Ϣ
						{
						//	if(MessageProcess&0x01)
						//	{
						//		MessageProcess|=0x04;			//MessageProcess��bit2λ��1
						//		TMR0_SCR|=TMR0_SCR_TCFIE_MASK;	//������Ϣ�����ж�
						//	}
					//		else
						NewMsg_Save();	//�洢����Ϣ
						}
						
						else	//��ʾ�н��չ���ǰ��Ϣ
						{
							if(Messagesavetop[Messagetoprank[i]].cer<4) ResultA();	//�ѽ�����Ϣ������С��4%
							else
							{
								if(Messagetemptop.cer>Messagesavetop[Messagetoprank[i]].cer) ResultA();
								else
								{
				/*					if(MessageProcess&0x01)
									{
										MessageProcess|=0x04;			//MessageProcess��bit2λ��1
							     		MessageProcess|=0x08;			//MessageProcess��bit3λ��1
										TMR0_SCR|=TMR0_SCR_TCFIE_MASK;	//������Ϣ�����ж�
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
											
											ThreeDayAlarm=1;	//����ʱ��ɾ������ϢΪ���ڴ������Ϣ�������촦��������1
																//�������Ϣ�迪�����춨ʱ��
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
									NewMsg_Save();	//�洢����Ϣ
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
	else		//��Ϣ����Ϊ0
	{
 		ResultA();
	}
}
/*************************************************   
	���ܣ����ղ���������FPGA������ɵ���Ϣ
	��ڲ�������
	���ز�������
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
	readMesMount = FPGARW(MesMount)&0x00ff;	//������Ϣ���ĵ�8λ
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
	if(G_Key&0x40)   //�����ѽ���
	{
	
//		Jiemamounttemp = FPGARW(MesMount)&0x00ff;	//������Ϣ���ĵ�8λ
/**/	if(Jiemamounttemp==0)
		{
			if(Jiemamount!=0)
			MesDeal();
			if(msgover==1)
			{
			flag_s=0;		//�����ʾ��ʾ
  			counter_flag_se=0;//	
	    	maske=0;			
			}
		}
		else
		{
			readMesEnd=FPGARW(MesEnd)&0x00ff;
			mesend=readMesEnd;			//��ȡ���һ����ǰһ����Ϣ��
			if(mesend==0)							//������һ����ǰһ����Ϣ��Ϊ0����ֱ�Ӵ���������Ϣ
			{
				flag_more_message =1;    //???
				if(Jiemamounte!=0)
				MesDeal();                   
			if(msgover==1)
			{
			flag_s=0;		//�����ʾ��ʾ
  			counter_flag_se=0;//	
	    	maske=0;			
			}
			}
			else
			{
				if(Jiemamounttemp>mesend) flag_more_message =1;
				else
				{	
					//flag_s=0;		//�����ʾ��ʾ
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
		    	flag_s=0;		//�����ʾ��ʾ
  		     	counter_flag_se=0;//		
	        	maske=0;			
		    	}
					
			}
		}
	}
	else
	{
		
//		Jiemamounttemp = FPGARW(MesMount)&0x00ff;	//������Ϣ���ĵ�8λ
//		mesend1 = FPGARW(MesEnd)&0x00ff;
		if(Jiemamounttemp==0)						//������һ��Ϊ��Ч��Ϣ
		{
			if(Jiemamounte!=0)
			MesDeal();
			if(msgover==1)
			{
			flag_s=0;		//�����ʾ��ʾ
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
	if(G_Key&0x40)   //�����ѽ���
	{
	
//		Jiemamounttemp = FPGARW(MesMount)&0x00ff;	//������Ϣ���ĵ�8λ
/**/	if(Jiemamounttemp==0)
		{
			if(Jiemamountc!=0)
			MesDeal();
			if(msgover==1)
			{
			flag_s=0;		//�����ʾ��ʾ
  			counter_flag_sc=0;//	
	    	maskc=0;				
			}
		}
		else
		{
			mesend=FPGARW(MesEnd)&0x00ff;			//��ȡ���һ����ǰһ����Ϣ��
			if(mesend==0)							//������һ����ǰһ����Ϣ��Ϊ0����ֱ�Ӵ���������Ϣ
			{
				flag_more_message =1;    //???
				if(Jiemamountc!=0)
				MesDeal();                   
			if(msgover==1)
			{
			flag_s=0;		//�����ʾ��ʾ
  			counter_flag_sc=0;//
	    	maskc=0;					
			}
			}
			else
			{
				if(Jiemamounttemp>mesend) flag_more_message =1;
				else
				{	
					//flag_s=0;		//�����ʾ��ʾ
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
		    	flag_s=0;		//�����ʾ��ʾ
  		     	counter_flag_sc=0;//
	        	maskc=0;					
		    	}			
			}
		}
	}
	else
	{
		
//		Jiemamounttemp = FPGARW(MesMount)&0x00ff;	//������Ϣ���ĵ�8λ
//		mesend1 = FPGARW(MesEnd)&0x00ff;
		if(Jiemamounttemp==0)						//������һ��Ϊ��Ч��Ϣ
		{
			if(Jiemamountc!=0)MesDeal();
			if(msgover==1)
			{
			flag_s=0;		//�����ʾ��ʾ
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
    	Fpga_reset();				//FPGA��ʼ��
    	Jiemamounte=0;
    	Jiemamountc=0;
 		  flag_s=0;		//�����ʾ��ʾ
  		counter_flag_se=0;//
  		counter_flag_sc=0;//
    	maske=0;
    	maskc=0;
		flag_more_message=0;
  }
}




/**********************************
��ʱ���жϺ���
*******************************/
/*void isrTimer0Compare ();
void isrTimer0Compare ()
{
    #pragma interrupt saveall    //��ջ�ȼĴ�������
 	int i=0,j,days,hours,minutes;
    TMR0_SCR&=~TMR0_SCR_TCF_MASK;   //���жϱ�־λ
    
    if((MessageProcess&0x01)==0)
    {
       	TMR0_SCR&=~TMR0_SCR_TCFIE_MASK;	//�ر�64K�Ķ�ʱ��0���ж�
       	if(MessageProcess&0x02)			//bit1λΪ1��˵���������Ϣɾ������
       	{
 //     		for(i=0;i<Messageinfo.savenumber[0];i++)	//�ҳ��账����Ϣ��Messagetoprank[]��λ�ã���i��¼
//			{
//				if(EpromAddNow==Messagetoprank[i]) break;	
//			}
			for(j=0;j<Messageinfo.savenumber[0];j++)
			{
				days=DatesToDays(Messagesavetop[Messagetoprank[j]].date[0],Messagesavetop[Messagetoprank[j]].date[1],Messagesavetop[Messagetoprank[j]].date[2]);
				hours=Messagesavetop[Messagetoprank[j]].time[0];	//��ȡСʱ��
				minutes=Messagesavetop[Messagetoprank[j]].time[1];	//��ȡ����	
				TODCS|=TODCS_TOD_LOCK_MASK;//����TOD_Lockλ����ȡTODģ����ʱ��ļĴ��� 
//				if(((days+3)<TODDAY)||(((days+3)==TODDAY)&&hours<TODHR)||
//					(((days+3)==TODDAY)&&(hours==TODHR)&&(minutes<=TODMIN)))
				if(((days+3)<TODDAY)||(((days+3)==TODDAY)&&hours<TODHR)||
					(((days+3)==TODDAY)&&(hours==TODHR)&&(minutes<=TODMIN)))
				{
//					MesDel(j);				//���ﻹ��Ҫ����������Ϣ���ж�
//					j--;
					if(Messagesavetop[Messagetoprank[j]].lock==0)//��������Ϣ�Ĳ���
					{
						Msgdel(j);
						j--;
					}
				}
				TODCS&=~TODCS_TOD_LOCK_MASK;//�ر�TOD_Lock����λ 
					
			}
			FindMsg();
 //      	   	MesDel(i);
 //      	   	FindMsg();
       	   	MessageProcess&=0xfd;//bit1λ����
       	}
       	
		
       	if(MessageProcess&0x04)
       	{
       		if(MessageProcess&0x08)	//�������Ϣ�滻����
       		{
       			
   				for(i=0;i<Messageinfo.savenumber[0];i++)//������Ϣ�Ƿ�Ϊ����Ϣ���������������޽�����ͬ��ǵ���Ϣ��
														//����˵��֮ǰ�ѽ��ܹ���abondan��1,��dealΪ0����δ�������촦����dealΪ1���뿼��
														//�������������ʱ����Ϣ�������촦��������ڣ��ж�����ΪEpromAddNow==Messagetoprank[i]
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
				
				 if(i!=Messageinfo.savenumber[0]) //��ʾ���չ���ǰ��Ϣ
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
       		NewMsg_Save();	//�洢����Ϣ
       		MessageProcess&=0xfb;//bit2λ����
       	}
       
    }

}  */
/*********************************ÿ�δ�����Ϣǰ���ѳ����������Ϣ����ɨ�貢ɾ��**********/
void mesdeletelook()
{
    u16 i,j,days,daysnow,hours,minutes,addressa,deletenum=0,temp=Messageinfo.savenumber[0],q=0;
	for(j=0;j<temp;j++)
    {
	days=DatesToDays(Messagesavetop[Messagetoprank[j]].date[0],Messagesavetop[Messagetoprank[j]].date[1],Messagesavetop[Messagetoprank[j]].date[2]);
	hours=Messagesavetop[Messagetoprank[j]].time[0];	//��ȡСʱ��
	minutes=Messagesavetop[Messagetoprank[j]].time[1];	//��ȡ����	
//	TODCS|=TODCS_TOD_LOCK_MASK;//����TOD_Lockλ����ȡTODģ����ʱ��ļĴ��� 
//	timestruct=GetTime();
	daysnow=DatesToDays(timestruct.year,timestruct.month,timestruct.day);
	if(((days+3)<daysnow)||(((days+3)==daysnow)&&hours<timestruct.hour)||(((days+3)==daysnow)&&(hours==timestruct.hour)&&(minutes<=timestruct.minute)))
	{
	
		if(Messagesavetop[Messagetoprank[j]].lock==0)//��������Ϣ�Ĳ���
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
//	TODCS&=~TODCS_TOD_LOCK_MASK;//�ر�TOD_Lock����λ 	
	if(deletenum>=3)
	break;				
	}	
}