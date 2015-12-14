#ifndef __code_H
#define __code_H

#include "define.h"
#include "inc.h"
extern volatile char MessageProcess;	/*���ڼ�¼��Ϣ�����״̬����������Ϣ����������Ϣ��������ʱ��MessageProcess��bit0Ϊ1
��ʱ����Ϣɾ���жϵ������򲻽�����Ϣɾ��������������ʱ��0�жϣ�����MessageProcess��bit1Ϊ1������������жϵ���
��Ҳ����������Ϣ��Ӳ�����������ʱ��0������MessageProcess��bit2Ϊ1,��ͬʱ������Ϣ��Ҫ�����滻��MessageProcess��
bit3λ��1�������ڽ�����Ϣɾ��������Ϣ��Ӳ�������MessageProcess��bit4Ϊ1*/
/*       bit7	bit6	bit5	bit4	bit3	bit2	bit1	bit0
          |		 |		 |		 |		 |		 |		 |		 |-----��������Ϣ����������Ϣ��������ʱ��MessageProcess��bit0Ϊ1
          |		 |		 |		 |		 |		 |		 |-------------��ʱ����Ϣɾ���жϵ������򲻽�����Ϣɾ��������������ʱ��0�жϣ�����MessageProcess��bit1Ϊ1
          |		 |		 |		 |		 |		 |---------------------����������жϵ�����Ҳ����������Ϣ��Ӳ�����������ʱ��0������MessageProcess��bit2Ϊ1
          |		 |		 |		 |		 |-----------------------------��ͬʱ������Ϣ��Ҫ�����滻��MessageProcess��bit3λ��1
          |		 |		 |		 |-------------------------------------�����ڽ�����Ϣɾ��������Ϣ��Ӳ�������MessageProcess��bit4Ϊ1
          |		 |		 |---------------------------------------------δ����
          |		 |-----------------------------------------------------δ����
          |------------------------------------------------------------δ����  

bit[1]+bit[0]    һ�������Ϣɾ���жϸ���Ϣ�����Ĵ���
bit[4 3 2]+bit[0]һ����ɽ����жϸ���Ϣ�����Ĵ���
*/ 

//extern volatile int  EpromAddNow;		//���ڼ�¼��3��ʱ���ൽʱ��Ӧ�ô������Ϣ��EpromAdd����Ϣ
//extern volatile char ThreeDayAlarm;		//���ڼ�¼������Ϣ�洢�Ƿ���Ҫ����3��ʱ����ж�,1��ʾ��Ҫ


/***********************************/
/****FILE SYSTEM****/
/***********************************/
extern volatile byte Flashmap[300]; 	//���ص��ڴ��Flashmapʹ�������һ���ֽڹ�4���飬2��bit��һ���飬���Ӵ��ҵ����˳��
						//���з�����00��ʾ���ѷ��������11��ʾ���ǿ��е�δ���������10��ʾ
extern short int Messagetoprank[600];//�洢��Ϣ��λ�ã������ʱ��ֻ��Ķ�Messagetoprank���ɣ�����Ķ��ṹ��Messagsavetop
extern volatile byte Eprommap[75];		//���ص��ڴ��Eprommapʹ�������һ���ֽڹ�8���飬1��bit��һ���飬�����ҵ����˳��
						//���з�����0��ʾ���ѷ��������1��ʾ
extern volatile Messageinfotype Messageinfo;			//�洢���ջ�����Ϣ��ز���
extern Messagetoptype Messagesavetop[600];		//�洢��Ϣͷ

extern Messagetoptype Messagetemptop;			//��ʱ�洢��Ϣͷ
extern volatile Checkinfotype Checkinfo;				//�洢�Լ����

/***********************************/
/****LCD for MessageDisplay****/
/***********************************/


extern char *LinePoint[300];	//һ��Ӣ����Ϣ��LCD������ʾ��һ�е�140�����ݵ��ַ�
extern unsigned short int *LinePoint2[300];	//һ��������Ϣ��LCD������ʾ��һ�е�140�����ݵ��ַ�
/***********************************/
/****Demodulate.c****/
/***********************************/
extern char Block1[4500];			//���մ洢����FPGA�Ľ�����Ϣ�Ķ�̬Memory���׵�ַ
extern volatile short int flag_valid;			//������λ��Ч��־
extern char MessagePoint[4500];	//��Ϣ���������ָ��
extern unsigned short int chinese[2000]; //�洢����LCD�ֿ������
extern char PrtMsg[4500];			//�����ӡ��Ϣ��������
extern char PrtMsgChn[4000];
extern char receiver_state[500];
extern char receiver_alarm[100];
extern volatile char TempBlock;	//��ǰʹ�û����ı�־��1��ʾ720~1439�������ݴ���0~719����֮��ͬ
extern volatile short int Stop[2];			//ͬ�������ı�־λ��2ʹ������ͬ����1��ֵ����ͬ������ʱ�ѽ��붨�򣩣�0��ͬ��
extern volatile short int Num[2];			//��stopΪ1������£�����̶�������Ҫ����ͬ��
extern volatile word Unread;				//��δ����Ϣ��
extern volatile JietiaoResulttype JietiaoResult[4];		//�洢���账��洢�������Ľṹ����������
//extern volatile char JietiaoState[4];			//���δ洢���账��ṹ����������У�������Ϊ0
/***********************************/
/****Time.c�����ڶ����ź��ж�****/
//extern volatile uint32 DxRx[14];
//extern volatile uint32 DxRxReceive[2];	//����λ�Ĵ洢λ
/***********************************/
/****Public Parameters****/
/***********************************/

extern volatile word STATE;				//��¼��ǰ��״̬                         
extern volatile byte State1parameter;	//��Ϣ�������ڲ���
extern volatile byte State2parameter;	//�洢�������������Ĺ�����ڲ���
extern volatile byte State200parameter;	//�洢�˵��´�ӡ��ѡ��������ѡ�˵�����ڲ���
extern volatile byte State2000parameter;//�洢�������˵��µ������ͽ���ȷ�ϵĹ���ȫ�ֱ���
extern volatile byte State202parameter;	//�洢�������������������˵����ý���


extern volatile byte State13parameter;	//��ӡ�˵�����ڲ���
extern volatile byte State14parameter;	//���������˵�����ڲ���
extern volatile byte State300parameter;	//�����˵���������ѡ�˵�״̬300��ȫ�ֱ���
extern volatile byte State4parameter;	//���˵�����ڲ���
extern volatile byte State400parameter;	//�Զ�ģʽ��ڲ���
extern volatile byte State401parameter;	//�ֶ�ģʽ��ڲ���
extern volatile byte State4000parameter;//�Զ�ģʽ���ֶ�ģʽ�Ĺ����ӽ�����ڲ���
extern volatile byte State41parameter;	//��Ϣ�����ڲ���
extern volatile byte State44parameter;	//ά���˵���ڲ���
extern volatile byte FLAG;				//���ڸ�������whileѭ���ڵı�־λ


extern volatile word BUFFER[10];	//��һ���˵���ÿ���˵���������������㣬�������Ӳ˵�������ı�
extern volatile word BUFFER1[10];	//�ڶ����˵�
extern volatile word BUFFER2[10];	//�������˵�
extern volatile word BUFFER3[10];	//���ļ��˵�
extern volatile word BUFFER4[10];	//���弶�˵�
extern volatile word BUFFERPRO[10]; //��һ���˵��ı���������Ϣ�洢�������Ϣ�������浽��Ϣ���ݲ˵��л�ʱ����
extern volatile short int BUFFERSELECT[22]; 		//ר���ڹ��ø�ѡ����Savelocksubmenu�Ĳ�������
extern volatile word BUFFERPRINT;	//ר���ڴ�ӡȷ������MessageSubmenu�Ĳ�������
extern volatile short int BUFFERSELECTLOCK; 		//ר����������ѡ��������ı���



extern volatile short int Messagenownumber; //��Ϣ���ĵ�ǰ��ʾ����λ��


extern volatile char LANHELP;		//���ڻ���ͼ�����ĸ���ѡ��
					//����LANGUAGEΪ1������£���ͼ�����Ծɿ���ʹ��Ӣ��ģʽ,��Ϊ0��ɼ���ʹ��Ӣ�Ŀ�ͼ
					 
					 
/***********************************/
/****LCD****/
/***********************************/					 

extern volatile byte CTAB1[40];	//Һ������ʾһ�е��ַ�
extern volatile byte CGTAB[2][16]; //Һ������ʾһ������
extern volatile byte G_Key;

/***********************************/
/****FLASH****/
/***********************************/	

/***********************************/
/*  ��Ϣ�洢�˵����漰�ӽ������   */
/***********************************/

extern volatile short int Selectsubback; 			//���ڽ��븴ѡ����Ľ����������
extern volatile char Selectreturn;  		//���ڸ�ѡ����ĳ��ڲ�������
extern volatile short int Mulnownumber; 			//��Ϊ��ѡ����ĵ�ǰ������Ϣ����
extern volatile short int Returnback;  			//���ڴ洢������������湫�õ���ڲ�������
extern volatile short int Messagenumber; 			//���ڴ洢�������������������Ϣ���ļ�¼
extern volatile char Rankback; 				//�������򹫹��������ڲ�������
extern volatile short int Msglockrank[150];	//ר����Savemenu(��ʱ���������˵�)�����Ӳ˵���ÿ�ν��붼��Ҫ����


/*******************************/
/*  ��Ϣ�˵����漰�ӽ������   */
/*******************************/
/*MESSAGE*/
extern volatile char Returntype; 	//��ʾ�ǴӺν��������Ϣ���ݽ��棬10��ʾ�ӽ������
				  	//1���ص��洢��2���ص�����,
extern volatile char PublicReturn; 	//���ڹ����������ڲ���
extern volatile char PitchDAPro;	//�����������ڲ�������
extern volatile byte subback;								//�����Ƿ���Ӳ˵����أ�10��ʾ�����Ӳ˵�
/*******************************/
/*  ���˵����漰�ӽ������   */
/*******************************/
extern volatile word Auto[3][26]; 			//�Զ����ò�����0��ʾ����
extern volatile word Autotemp[3][26];		//�Զ�������ʱ����
extern volatile char Manual[3][26];			//�ֶ����ò�����0��ʾ����
extern volatile char Manualtemp[3][26];		//�ֶ�������ʱ����
extern volatile char MSGTYPE[3][26];		//��Ϣ������ò�����0��ʾ����
extern volatile char MSGTYPETEMP[3][26];	//��Ϣ�����ʱ���ò���
extern volatile char backpage;			//0��ʾ��Ϣ���ģ�1��ʾ�洢��2��ʾ������3��ʾʱ��λ�ã� 

extern volatile char manual_area_temp;
extern volatile char manual_area;

/*����ʱ��*/                //�����ֱ��ʾ����ʱ���������ʱ��

extern volatile char number;          		//����ʱ�������
extern volatile char sign;            		//��������������
extern volatile char lcontrol;         		//������¼����ʱ���Ƿ�

extern byte iyear;
extern byte imonth;
extern byte iday;
extern volatile byte ihour;
extern volatile byte iminute;
/*���ջ�����*/              //�ֱ�������ʾ���ջ���һЩ����
extern volatile char Receiverset[5];    	//0��ʾ�����ʣ�������������


extern volatile char Buzzer[4];			//���α�ʾ���ַ����Ŀ������
extern volatile char Buzzerstate;		//������ʱ�������ں���״̬��Bit0�����Ҫ��Ϣ��Bit1��ǽ��ջ�����
extern volatile char Contrast;				//��ʾ�Աȶȵ�ѡ��
extern volatile char Backlight;				//0��ʾhigh��1��ʾmedim��2��ʾlow
extern Diagresulttype Diaglog[10];//���ڼ�¼�Լ���־�Ľ������ʮ��
extern volatile char Diaglogs;				//���ڼ�¼��ǰ��д��־��Diagresult[]��λ��
extern volatile char Diaglogn;				//���ڼ�¼��־������

/* Rx station*/
extern volatile char Mode;				//��¼��ǰ���ں���ģʽ��0��ʾ�Զ���1��ʾ�ֶ�
extern volatile char Workfre;			//��¼��ǰ�Ĺ���Ƶ�ʣ�0ѡ��518/4209.5��1ѡ��518/486

extern volatile char LANGUAGE;			//������Ӣ�Ĳ���ģʽ��1�����ģ�0��Ӣ��
extern volatile char Operated;			//�����ж��Ƿ���Ҫ��������ѡ�����

/*��Ϣ��ʾ��־*/
extern volatile char flag_s;			//��Ϣ��ʾ��־����flag_sΪ1ʱ����ʾ��ʾ���ţ�����flag_sΪ0ʱ�������ʾ����
extern volatile char counter_flag_se;	//��Ϣ��ʾ��־����
extern volatile char counter_flag_sc;	//��Ϣ��ʾ��־����
/*����Ϣ�յ���־���������յ���Ϣ����λ����������Ϣ������Ϻ���0*/
extern volatile char flag_new_message;
/*IEC61162���սṹ��*/
extern volatile iec_tx_type iec_rx;
/*GPSת�������ݣ��������ȡ�γ���Լ�������Ϣ*/
extern volatile short int gpslldt[3][5];//gpslldt[0][]:γ��  gpslldt[1][]:����  gpslldt[2][]:����(������ʱ��) 
/*�Զ�����*/
extern volatile short int auto_area;	//�Զ�����
/*�Զ������־��0--�ֶ���1�Զ�*/
extern volatile char flag_auto_iec;
//extern volatile char Ham[1000];

//extern volatile char Cos[1000];
//extern volatile char Sin[1000];

//extern volatile char Ham1[250];

//extern volatile char Cos1[250];
//extern volatile char Sin1[250];
//-----------------jietiao.c----------------------------------------------------------------------------------
//extern int JietiaoBlcok[DemodulateBuffer];	//�ֱ�������ͨ����������
//extern volatile byte ReceiverarrayNow[9100];

//extern volatile unsigned char Receivearray[2][ReceiveMax], ReceivePeriod[2];
//ReceivearrayΪ����Ĵ洢���飬ReceivePeriod[2]��ʾ��Ӧ����ͨ����ǰ�洢�ֽڴ洢�˼�����Ԫ
//extern volatile int  Receivenm[2],Pfirst[2];
//Receivenm[2]��ʾ��Ӧͨ������洢�������Ŀ��Pfirst��ʾ����ÿ�ν���80��ADת����������������ʼ����������ڽ��ջ�������λ��

 

extern volatile char Dingxiang[2];		//�ֱ��Ӧ����ͨ�����������0δ����1����
//extern volatile char Dingxiangmount[2];	//�ֱ��Ӧ����ͨ��������Ϣ�������յ�bit��

//extern volatile word Jietiaomount;		//������ַ������������е���Ϣ
//extern volatile word Jietiaomounttemp;	//��ǰ��Ϣδ������ֽ���
extern volatile short int Jiemamount;			//������Ϣ������ϵ��ֽ���
extern volatile short int Jiemamounttemp;		//���ν�����ֽ���

extern volatile char Antenna;				//0��ʱ���������1���ڼ����������	
extern volatile char AntennaResult;		//���߼������0������1δ��⵽����
//------------------automode.c------------------------------------------------------------------------------------------
extern volatile unsigned char Rxstation[16][26][14];
//automodesubmenu.c
extern volatile byte parameter;
//-------------------lcddrive.c--------------------------------------------------------------
extern volatile byte SYSTAB[8];
extern volatile byte SCRTAB[10];
extern volatile byte CTAB[40];
//-----------------boot.c-------------------------------
extern volatile signed char TimeLeft;
//others.c
extern volatile char Antennaing;	//���������Լ����洢�ı���������ʼ�Լ���1���Լ������0
extern volatile char flag_on;				//�����Լ��־
//printer.c
extern int TEMP[1600];

extern volatile PrtLink *PrtStart;
extern volatile short int print_list[600];
extern volatile short int print_sum;
//iec.c
extern volatile short int iec_send_list[600];
extern volatile short int iec_send_sum;
extern char bice[75][82];
extern volatile  char nrmareamk[26];
extern volatile char nrmtypemk[26];
extern volatile  char nrmflag_on;
extern volatile  char nrmfre;
extern volatile char checkdata[6];
extern char iec_rx_data[70];		//��Ч���ݴ洢
extern volatile unsigned char iec_rx_array[500];//�������ݻ�����
extern volatile unsigned char iec_alarm_data;
//messagetype.c
extern volatile byte MessagetypeEn[26][13];
extern volatile word MessagetypeCn[26][4];
//message.c
extern volatile word LINE;									//ͳ������ʾ��Ϣ��������
extern volatile byte now_printing;
extern volatile byte flag_more_message;
extern volatile byte falsh_error;
//extern volatile byte eepromdata[33000];            //@wuxianwei
//extern volatile byte flashdata[40000];
extern volatile short int recenum;
extern volatile byte msgover;
//extern volatile word Jiemamounttempa;
extern Messagetoptype msgtop;
//extern volatile word wrongmessage;
extern volatile byte whichchannel;
extern volatile short int Jiemamounte;
extern volatile short int Jiemamountc;
extern char Blocke[4500];
extern char Blockc[4500];
extern volatile unsigned char maske;
extern volatile unsigned char maskc;
extern volatile short int readMesEnd;
extern volatile short int readMesMount;
extern volatile timetype timestruct;
#endif
