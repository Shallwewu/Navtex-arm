#ifndef __USART_H
#define __USART_H
void USART3_Init(void);
void USART2_Init(void);
void USART_BaudRate(USART_TypeDef* USARTx,u16 BaudRate);
#endif