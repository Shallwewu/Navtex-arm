#include "code.h"
//#include "define.h"
#include "inc.h"
#include "stm32f2xx.h"
//-----------------jietiao.c----------------------------------------------------------------------------------
//int TEMP[1600];
//int JietiaoBlcok[DemodulateBuffer];	//�ֱ�������ͨ����������
//volatile byte ReceiverarrayNow[9100];

//volatile unsigned char Receivearray[2][ReceiveMax], ReceivePeriod[2]={0,0};
//ReceivearrayΪ����Ĵ洢���飬ReceivePeriod[2]��ʾ��Ӧ����ͨ����ǰ�洢�ֽڴ洢�˼�����Ԫ
//volatile int  Receivenm[2]={0,0},Pfirst[2]={0,0};
//Receivenm[2]��ʾ��Ӧͨ������洢�������Ŀ��Pfirst��ʾ����ÿ�ν���80��ADת����������������ʼ����������ڽ��ջ�������λ��

 

volatile char Dingxiang[2]={0,0};		//�ֱ��Ӧ����ͨ�����������0δ����1����
//volatile char Dingxiangmount[2]={0,0};	//�ֱ��Ӧ����ͨ��������Ϣ�������յ�bit��

//volatile word Jietiaomount=0;		//������ַ������������е���Ϣ
//volatile word Jietiaomounttemp=0;	//��ǰ��Ϣδ������ֽ���
volatile short int Jiemamount=0;			//������Ϣ������ϵ��ֽ���
volatile short int Jiemamounttemp=0;		//���ν�����ֽ���
volatile word mesend=0;
//volatile word oldJiemamount;
//volatile word wumamount;
volatile char Antenna=0;				//0��ʱ���������1���ڼ����������	
volatile char AntennaResult=0;		//���߼������0������1δ��⵽����
//volatile unsigned char Rxstation[16][26][14];
//-------------------lcddrive.c--------------------------------------------------------------
volatile byte SYSTAB[8]={0x30,0x87,0x07,0x28,0x42,0xf0,0x29,0x00};
volatile byte SCRTAB[10]={0x00,0x00,0xf0,0xce,0x04,0xf0,0x80,0x00,0x00,0x00};
volatile byte CTAB[40];
//-----------------boot.c-------------------------------
volatile signed char TimeLeft;
//others.c
volatile char Antennaing=0;	//���������Լ����洢�ı���������ʼ�Լ���1���Լ������0
//printer.c
volatile PrtLink *PrtStart;
//volatile int print_list[600];
volatile short int print_sum=0;
//message.c
volatile word LINE;									//ͳ������ʾ��Ϣ��������
/***********************************/
/****Time.c�����ڶ����ź��ж�****/
/*volatile uint32 DxRx[14]=
{
	0x67e19f86,0xcfc33f0c,0x9f867e19,0x3f0cfc33,0x7e19f867,0xfc33f0cf,0xf867e19f,0xf0cfc33f,0xe19f867e,0xc33f0cfc,0x867e19f8,0x0cfc33f0,0x19f867e1,0x33f0cfc3
};*/
//volatile uint32 DxRxReceive[2]={0x0000,0x0000};	//����λ�Ĵ洢λ
volatile byte flag_more_message=0;
volatile byte Flashmap[300];
//volatile int Messagetoprank[600];   
volatile byte Eprommap[75];
volatile Messageinfotype Messageinfo;	
//Messagetoptype Messagesavetop[600];	   
//Messagetoptype Messagetemptop;	
volatile byte FLAG;	
Messagetoptype Messagetemptop;
volatile short int Messagenownumber;
volatile u8 G_Key=0;
short int Messagetoprank[600];
Messagetoptype msgtop;
volatile word Unread;	
volatile word STATE;				//��¼��ǰ��״̬                         
volatile byte State1parameter;  	//��Ϣ�������ڲ���
volatile byte State2parameter;  	//�洢�������������Ĺ�����ڲ���
volatile byte State200parameter;	//�洢�˵��´�ӡ��ѡ��������ѡ�˵�����ڲ���
volatile byte State2000parameter;   //�洢�������˵��µ������ͽ���ȷ�ϵĹ���ȫ�ֱ���
volatile byte State202parameter;	//�洢�������������������˵����ý���


volatile byte State13parameter;	    //��ӡ�˵�����ڲ���
volatile byte State14parameter;	    //���������˵�����ڲ���
volatile byte State300parameter;	//�����˵���������ѡ�˵�״̬300��ȫ�ֱ���
volatile byte State4parameter;  	//���˵�����ڲ���
volatile byte State400parameter;	//�Զ�ģʽ��ڲ���
volatile byte State401parameter;	//�ֶ�ģʽ��ڲ���
volatile byte State4000parameter;   //�Զ�ģʽ���ֶ�ģʽ�Ĺ����ӽ�����ڲ���
volatile byte State41parameter;  	//��Ϣ�����ڲ���
volatile byte State44parameter; 	//ά���˵���ڲ���
volatile char flag_s;			//��Ϣ��ʾ��־����flag_sΪ1ʱ����ʾ��ʾ���ţ�����flag_sΪ0ʱ�������ʾ����
//volatile char counter_flag_s;	//��Ϣ��ʾ��־����
volatile char Mode;				//��¼��ǰ���ں���ģʽ��0��ʾ�Զ���1��ʾ�ֶ�
volatile char Workfre;			//��¼��ǰ�Ĺ���Ƶ�ʣ�0ѡ��518/4209.5��1ѡ��518/486
volatile char LANGUAGE;			//������Ӣ�Ĳ���ģʽ��1�����ģ�0��Ӣ��
volatile char flag_new_message;
volatile byte msgover;
volatile byte whichchannel;
//volatile word Jiemamounte=0;
//volatile word Jiemamountc=0;
volatile word BUFFER[10];   	//��һ���˵���ÿ���˵���������������㣬�������Ӳ˵�������ı�
volatile word BUFFER1[10];	    //�ڶ����˵�
volatile word BUFFER2[10];  	//�������˵�
volatile word BUFFER3[10];  	//���ļ��˵�
volatile word BUFFER4[10];  	//���弶�˵�
volatile word BUFFERPRO[10];    //��һ���˵��ı���������Ϣ�洢�������Ϣ�������浽��Ϣ���ݲ˵��л�ʱ����
volatile short int BUFFERSELECT[22]; 	//ר���ڹ��ø�ѡ����Savelocksubmenu�Ĳ�������
volatile word BUFFERPRINT;   	//ר���ڴ�ӡȷ������MessageSubmenu�Ĳ�������
volatile short int BUFFERSELECTLOCK; 	//ר����������ѡ��������ı���
volatile byte CTAB1[40];	//Һ������ʾһ�е��ַ�
volatile byte CGTAB[2][16]; //Һ������ʾһ������
volatile short int Selectsubback; 		//���ڽ��븴ѡ����Ľ����������
volatile char Selectreturn;  		//���ڸ�ѡ����ĳ��ڲ�������
volatile short int Mulnownumber; 			//��Ϊ��ѡ����ĵ�ǰ������Ϣ����
volatile short int Returnback;  			//���ڴ洢������������湫�õ���ڲ�������
volatile short int Messagenumber; 		//���ڴ洢�������������������Ϣ���ļ�¼
volatile char Rankback; 			//�������򹫹��������ڲ�������
volatile char Returntype;       	//��ʾ�ǴӺν��������Ϣ���ݽ��棬10��ʾ�ӽ������
				  	                //1���ص��洢��2���ص�����,
volatile char PublicReturn;     	//���ڹ����������ڲ���
volatile char PitchDAPro;       	//�����������ڲ�������
volatile byte subback;				//�����Ƿ���Ӳ˵����أ�10��ʾ�����Ӳ˵�
volatile char number;          		//����ʱ�������
volatile char sign;            		//��������������
volatile char lcontrol;         	//������¼����ʱ���Ƿ�

byte iyear;
byte imonth;
byte iday;
volatile byte ihour;
volatile byte iminute;
volatile char Buzzer[4];			//���α�ʾ���ַ����Ŀ������
volatile char Buzzerstate=0;		//������ʱ�������ں���״̬��Bit0�����Ҫ��Ϣ��Bit1��ǽ��ջ�����
volatile char Contrast;				//��ʾ�Աȶȵ�ѡ��
volatile char Backlight;			//0��ʾhigh��1��ʾmedim��2��ʾlow
Diagresulttype Diaglog[10];         //���ڼ�¼�Լ���־�Ľ������ʮ��
volatile char Diaglogs;				//���ڼ�¼��ǰ��д��־��Diagresult[]��λ��
volatile char Diaglogn;				//���ڼ�¼��־������
//char *LinePoint[200];       	//һ��Ӣ����Ϣ��LCD������ʾ��һ�е�140�����ݵ��ַ�
//unsigned int *LinePoint2[200];	//һ��������Ϣ��LCD������ʾ��һ�е�140�����ݵ��ַ�
volatile word Auto[3][26]; 			//�Զ����ò�����0��ʾ����
volatile word Autotemp[3][26];		//�Զ�������ʱ����
volatile char Manual[3][26];		//�ֶ����ò�����0��ʾ����
volatile char Manualtemp[3][26];	//�ֶ�������ʱ����
volatile char MSGTYPE[3][26];		//��Ϣ������ò�����0��ʾ����
volatile char MSGTYPETEMP[3][26];	//��Ϣ�����ʱ���ò���
volatile char backpage = 0;			//0��ʾ��Ϣ���ģ�1��ʾ�洢��2��ʾ������3��ʾʱ��λ�ã� 

volatile char manual_area_temp;
volatile char manual_area;
volatile short int Msglockrank[150];  	//ר����Savemenu(��ʱ���������˵�)�����Ӳ˵���ÿ�ν��붼��Ҫ����
volatile Checkinfotype Checkinfo;				//�洢�Լ����
volatile char Receiverset[5];    	//0��ʾ�����ʣ�������������
volatile byte now_printing;         //0��ӡ�� 1���ڴ�ӡ 
volatile byte parameter;
volatile short int print_list[600];
volatile short int auto_area;	//�Զ�����
volatile short int Jiemamounte=0;			//������Ϣ������ϵ��ֽ���
volatile short int Jiemamountc=0;			//������Ϣ������ϵ��ֽ���
volatile unsigned char maske=0;
volatile unsigned char maskc=0;
volatile char counter_flag_se=0;	//��Ϣ��ʾ��־����
volatile char counter_flag_sc=0;	//��Ϣ��ʾ��־����
volatile short int readMesEnd;
volatile short int readMesMount;
volatile timetype timestruct;
