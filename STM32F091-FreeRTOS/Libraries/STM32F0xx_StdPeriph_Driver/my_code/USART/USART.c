#include "USART.h"

uint8_t Active_Motor=0;
uint8_t UART_value=0;
extern 	__IO uint8_t RxCounter, ReceiveState;

/*
* �������ƣ�USART1_Config
* ���ã�����1��ʼ������
* ������baud     ������
* ���ţ�
* �����RX��C11
*      TX��C10
*/
void USART3_Config(unsigned int baud)
{ 
 	GPIO_InitTypeDef GPIO_InitStructure;
  USART_InitTypeDef USART_InitStructure;
  NVIC_InitTypeDef NVIC_InitStructure;
  /* USARTx configured as follow:
  - BaudRate = 115200 baud  
  - Word Length = 8 Bits
  - Stop Bit = 1 Stop Bit
  - Parity = No Parity
  - Hardware flow control disabled (RTS and CTS signals)
  - Receive and transmit enabled
  */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
  /* USART1 Pins configuration ************************************************/
  /* Connect pin to Periph */
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource10, GPIO_AF_1); 
  GPIO_PinAFConfig(GPIOC, GPIO_PinSource11, GPIO_AF_1);    
  
  /* Configure pins as AF pushpull */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_10 | GPIO_Pin_11;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure); 
	
  USART_InitStructure.USART_BaudRate = baud;//����������
  USART_InitStructure.USART_WordLength = USART_WordLength_8b;
  USART_InitStructure.USART_StopBits = USART_StopBits_1;//1��ֹͣλ
  USART_InitStructure.USART_Parity = USART_Parity_No;
  USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
  USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
  USART_Init(USART3, &USART_InitStructure);
	USART_ITConfig(USART3, USART_IT_RXNE, ENABLE);									//??????
	USART_Cmd(USART3, ENABLE);	//ʹ�ܴ���
	
	NVIC_InitStructure.NVIC_IRQChannel = USART3_8_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
														
}

/*
* �������ƣ�Usart_SendString
* ���ã����ڷ��ͽ��յ�������
* ������USARTx  USARTͨ��
*       str     �������ݵ�����
*       len     ����ĳ���
* �����
*/

void Usart_SendString(USART_TypeDef *USARTx, unsigned char  *str, unsigned short len)
{

	unsigned short count = 0;
	
	if(ReceiveState==1)
	{
	  for(; count < len; count++)
	   {
	    	USART_SendData(USARTx, *str++);									//��������
		
	    	while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);		//�ȴ��������
   	}
		 ReceiveState=0;
  }
}

/*
* �������ƣ�Usart_DataUse
* ���ã��Դ��ڷ��͵����ݽ��д���
* ������USARTx  USARTͨ��
*       str     ���ݴ��������
* �����
*/

void Usart_DataUse(USART_TypeDef *USARTx,   int str[])
{
	unsigned short count = 0;
  int sum_data1=0,sum_data2=0;
	if(ReceiveState==1)
  {
		//sum_data1=0;
		for(count=0; count < 8; count++)sum_data1 += str[count];
	  sum_data2=str[8]+str[9];
		if(sum_data1 == sum_data2)
		{
			Active_Motor=str[2];//������
			UART_value =str[3];//���������
		}
		USART_SendData(USARTx, sum_data1);
		ReceiveState=0;
	}
//
//	switch(count)
//	{
//		case 0:
//		{
//		    
//		}
//			break;
//		case 1:{}break;
//		case 2:{}break;
//		case 3:{}break;
//		case 4:{}break;
//		case 5:{}break;
//		case 6:{}break;
//		case 7:{}break;
//		case 8:{}break;
//		case 9:{}break;
//			
//	}
}
/*
void UsartPrintf(USART_TypeDef *USARTx, char *fmt,...)
{

	unsigned char UsartPrintfBuf[296];
	va_list ap;
	unsigned char *pStr = UsartPrintfBuf;
	
	va_start(ap, fmt);
	vsnprintf((char *)UsartPrintfBuf, sizeof(UsartPrintfBuf), fmt, ap);							//��ʽ��
	va_end(ap);
	
	while(*pStr != 0)
	{
		USART_SendData(USARTx, *pStr++);
		while(USART_GetFlagStatus(USARTx, USART_FLAG_TC) == RESET);
	}

}
*/
