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
//void Checkprint(); //检测打印机状态函数
void InsMsg(short int xulie);

void Printmessage(short int);//打印一条信息
void Printselect(void);  //打印带选中标记的信息
void Printstate(void);//打印状态

void Selectgiven(word frequency,word type,word rxstation,word messageset);  //批处理显示等同于Select
void ReadPrtMsg(void);
#endif 
