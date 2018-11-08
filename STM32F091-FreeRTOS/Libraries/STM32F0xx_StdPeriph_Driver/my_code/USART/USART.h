#ifndef __USART_H
#define __USART_H	 
#include "main.h"


void USART3_Config(unsigned int baud);
void Usart_SendString(USART_TypeDef *USARTx, unsigned char  *str, unsigned short len);
void Usart_ReceiveString(USART_TypeDef *USARTx, unsigned char *str);
void Usart_DataUse(USART_TypeDef *USARTx,int str[]);
//void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...);


#endif



