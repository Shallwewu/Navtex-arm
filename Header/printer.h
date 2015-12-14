#ifndef	__printer_H
#define __printer_H

#include "stm32f2xx.h"
#include "define.h"
//extern PrtLink *PrtStart;
void IntialRS232(void);
void BadurateSet(char badurate);
void StartRS232(USART_TypeDef* USARTx);

void CloseRS232(USART_TypeDef* USARTx);
void DataTran(USART_TypeDef* USARTx);
//void Checkprint(); //����ӡ��״̬����
void InsMsg(short int xulie);

void Printmessage(short int);//��ӡһ����Ϣ
void Printselect(void);  //��ӡ��ѡ�б�ǵ���Ϣ
void Printstate(void);//��ӡ״̬

void Selectgiven(word frequency,word type,word rxstation,word messageset);  //��������ʾ��ͬ��Select
void ReadPrtMsg(void);
#endif 
