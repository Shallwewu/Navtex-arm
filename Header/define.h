#ifndef __define_H
#define __define_H
#include "stm32f2xx.h"
#define UP 		7
#define DOWN 	5
#define LEFT 	6
#define RIGHT 	8
#define MENU	3//11
#define DISP	2
#define STAR 	10
#define ENT 	4
#define PW  	1
#define CLR 	9
#define BACKLIGHT 12
#define CONTRAST 11//3

#define Maxpagenum 6		//�洢�б�һҳ�����ܴ洢����Ϣ����
#define MessagePageNum 7 	//�洢�б�����
#define Maxlocknum 50 		//��ͨ������������� 
#define PARA 0x29  	    	//ͬSYSTEM SET�е�P6���ã������������ַ��


typedef unsigned char byte;
typedef unsigned short int  word;
typedef short int sword;
typedef unsigned int uint32;
typedef unsigned char bool;


typedef struct
{
	char diagresult[8];//�����������ڼ�¼ROM,RAM,SERIAL PORT,POWER,ANTENNA,518,490,4209.5�Ƿ���������
	byte date[3];//date[2],date[1],date[0]�ֱ����ڼ�¼�����գ�
	byte time[2];//time[1],time[0]���ڼ�¼Сʱ�ͷ���
} Diagresulttype;

typedef struct
{
	short int nownumber[2];//�ڽ��յ��µ���Ϣ���ȸı�nownumber�������,0��ʾ�洢��1��ʾ����
	short int savenumber[4];
	short int locknumber[4];
	byte rankmode;//?��ʾ�洢�˵��������˵�����Ϣ������˳��(����)
			   	 //������0��ʾʱ�䣬1��ʾ����̨��2��ʾ��Ϣ���3��ʾδ����Ϣ,4��ʾ���о�����				
} Messageinfotype;	//savenumber[1] 580khz savenumber[2] 490khz savenumber[3] 4209.5khz
					//savenumber[0] 3��ͨ���Ĵ洢��Ϣ���llocknumber[4]ͬsavenumber[4]
typedef struct
{
	char Printerror;//��ӡ��״̬ 0:���� 1:������
	char Printover;  //��ӡ״̬   0:δ��ӡ 1:��ӡ��
} Checkinfotype;

typedef struct
{
	short int jietiaomount;	//�������Ϣ��
	volatile byte *p;            //������ݴ洢�����׵�ַ
	char useing;		//�жϱ��ṹ���Ƿ���ʹ���У�1ʹ�ã�0����
	char frequency;		//�洢ͨ��		
}JietiaoResulttype;		//�洢�������Ľṹ��


							
typedef struct
{
	byte mark[4];
	byte frequency;	//1:518khz 2:486khz 3:4209.5khz
	byte date[3];	//����,date[0],date[1],date[2]�ֱ����ڼ�¼������
	byte time[2];  	//ʱ��ttime[0],time[1]���ڼ�¼Сʱ�ͷ���,�洢�����ݲ����ַ���ʽ
	byte lock; 		//����Ϊ1������Ϊ0
	byte read; 		//0:�Ѷ�  1:δ��
	word flashadd;	    // �ļ����������Ϣ,0~1199
    byte flashmount;	// �ļ����������Ϣ
	byte select;		//��ʾ�Ƿ�ѡ��������һ�θ�ѡ��������������㣬1��ʾѡ��,����洢��eprom��
	byte area;			//��ʾ16�����������е�һ��,ȡֵ1~16
	char dealed;		//��Ϣ�Ƿ񳬹����죬1��ʾ������0��ʾ��
	char cer;			//�洢�����ʵİٷֱ�
	word amount;       //@��Ϣ���ֽ���
} Messagetoptype;				//�洢��Ϣͷ�ļ�

typedef struct
{
	char rx_data;					//��ǰ�����ֽ�
	short int nownum;//
	short int allnum;//	
	unsigned char start_flag;		//��Ϣͷ������ϱ�־
	unsigned char end_flag;			//��Ϣβ������ϱ�־
	unsigned char data_valid_flag;	//���յ���ЧGPS���ݱ�־
	unsigned char time;				//��ʱ����
	unsigned char new_flag;		//���յ�����,0δ�յ���1���յ�
} iec_tx_type;

typedef struct node
{
	short int xulie;
//	char *start;
	char *nowprint;
	char *end;
//	struct node *next;			
}PrtLink;

typedef struct
{
	u8 year;
	u8 month;
	u8 day;
	u8 hour;
	u8 minute;
	u8 second;
} timetype;

#endif
