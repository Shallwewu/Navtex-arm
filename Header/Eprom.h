#ifndef __Eprom_H
#define __Eprom_H
#include "define.h"
#include "stm32f2xx.h"
#define SDA_IN()  {GPIOC->MODER&=0xfff3ffff;}
#define SDA_OUT()  {GPIOC->MODER&=0xfff3ffff;GPIOC->MODER|=0x00040000;}

void Save_A_Message_Eprom(sword position);
void WriteMesinfo(void); 
void LockAMessageHeader(sword position);
void UnlockAMessageHeader(sword position);
void WritebitDeal(sword position);
char Eprom_Check(void);
void Eprom_AutoMode_Save(void);
void Eprom_ManualMsgMode_Save(word address);
void Eprom_Buzzer_Save(void);
void Eprom_Diaglog_Save(char diaglogs);
void Eprom_Diaglog_Read(Diagresulttype *temp,char diaglogs);
void Intial_Normal_Receiver(void);
void Intial_Message(void);
void Reset_Message(void);
void ReadTime(void);
void SaveTime(void);
void IIC_Init(void);
void IICStart(void);
void IICStop(void);
void InI2C_OutputACK(u8 mAck);
void IICWrite_ONE_BYTE(u8 txd);
u8 IICRead_ONE_BYTE(void);
void Write_Char_Eprm(u16 WriteAddr,u8 data);
u16 Read_Int_Eprm(u16 address);
void Write_Int_Eprm(u16 address,u16 data);
void IICWrite_ONE_MEHE(Messagetoptype * messagetop,u16 address);
void IICRead_ONE_MEHE(u16 address,Messagetoptype * messagetop);
//void cleareeprom();
//void readalleeprom();
/*Eprom�ܴ�СΪ32k�ֽڣ�0x0000~0x7fff*/


#define MESSTYPELENGTH  	32   //һ��struct Messagetoptype����19���ֽڣ�select����洢��Ϊ�˱���ҳд���⣬ÿ������32�ֽ� 
								 //	32*600=19200,0x0000~0x4aff


#define FlashmapStart		19337	//19337(0x4b89)~19636 ռ��300���ֽڣ�һ���ֽڹ�4���飬Flash�з���1200�����ʹ�������ÿ�����СΪ1K�ֽ�
#define EprommapStart		19637	//19637~19711 ռ��75���ֽڣ�һ���ֽڹ�8���飬Eprom�з���600�����ʹ�������ÿ�����СΪ19�ֽ�
#define MESSAGEINFO 		19712	//19712(4d00)�洢Messageinfo����ʼλ�ã�����21���ֽ�

//#define DIAGRESULT			19840//(0x4d80)�洢9���Լ����ṹ�����ʼλ�ã�ÿ��13���ֽڣ���117

#define DIAGLOGS			19968//(0x4e00)�Լ���־�Ŀ�д��־ָ������,1���ֽ�
#define DIAGLOGN			19969//�Լ���־������,1���ֽ�
#define RX_BUZZER 			19970//�������Ϳ��ƣ���4���ֽ�
#define PRINTER_FORMAT		19974//��ӡ��ʽ������5��char��
#define RX_MODE			    19979//���ջ�ģʽ������һ���ֽ�	
#define RX_WORKFRE			19980//���ջ�����Ƶ�ʲ�����һ���ֽ�
#define RX_TIME				19981//���ջ�����ʱ�����ã�3���ֽ�
#define RX_LANGUAGE			19984//���ջ����Բ�����һ���ֽ�
#define UNREAD_MSG			19985//δ����Ϣ������int�ͣ�2���ֽ�
#define RX_CONTRAST			19987//���ջ��ĶԱȶȣ�һ���ֽ�
#define OPERATED			19988//���ջ��Ƿ����������ѡ��1���裬0�裬һ���ֽ�
#define RX_BACKLIGHT		19989//���ջ��ı��⣬һ���ֽ�

#define YEAR        0x5900
#define MONTH       0x5902
#define DAY 				0x6000//���ջ�����--�챣�棬2���ֽ�
#define HOUR				0x6002//���ջ�����--Сʱ���棬2���ֽ�
#define MINUTE 				0x6004//���ջ�����--���ӱ��棬2���ֽ�



#define RXSTATION_AUTO  	0x5000//20480(0x5000)�Զ�ģʽ����̨��ѡ��int�ͣ�3*26*2=156�ֽڣ�����3ҳ64*3=192�ֽ�0x5000---0x50bf
//#define RXSTATION_MANUAL 	0x5180//�ֶ�ģʽ����̨��ѡ��char�ͣ�3*26=78�ֽ�,����һ���ֽڵĵ�ǰ����Ϣ,����һҳ128�ֽ�
//#define RX_MSGTYPE		0x5200//���ջ�������Ϣ���ѡ��char�ͣ�3*26=78�ֽ�,����һҳ�ֽ�
//revised@2010-7-1
#define RXSTATION_MANUAL 	0x50c0//�ֶ�ģʽ����̨��ѡ��char�ͣ�3*26=78�ֽ�,����һ���ֽڵĵ�ǰ����Ϣ��79���ֽ�,����3ҳ192�ֽ�
#define RX_MSGTYPE			0x5180//���ջ�������Ϣ���ѡ��char�ͣ�3*26=78�ֽ�,����3ҳ192�ֽ�

#define IEC_MODE			0x6006//IEC���ģʽ��һ���ֽ�
#define DIAGRESULT			0x6040//(0x24640)�洢9���Լ����ṹ�����ʼλ�ã�ÿ��13���ֽڣ���117,��9ҳд
#endif
