#include "delay.h"

void Delay_Init(void)
{

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
	//STM32F10x��Ƭ����ʱ����BUG����Ҫ������һ�Σ�Ȼ�������־�����������BUG
	TIM3->CR1 = 1;
	while(!(TIM3->SR & 1));							//�ȴ������ж��¼�
	TIM3->SR &= ~(1UL << 0);						//�����־
	TIM3->CR1 = 0;
	
	TIM3->CR1 |= 1UL << 3;							//������ģʽ
	
	TIM3->EGR |= 1;									//��������
	
	TIM3->DIER = 0;									//��ֹ�����ж�
	
	TIM3->CR1 &= (unsigned short)~TIM_CR1_CEN;		//ֹͣ��ʱ
	
	TIM3->PSC = 71;

}

/*
************************************************************
*	�������ƣ�	DelayUs
*
*	�������ܣ�	΢�뼶��ʱ
*
*	��ڲ�����	us����ʱ��ʱ��
*
*	���ز�����	��
*
*	˵����		��ʱ��(21MHz)�����ʱ798915us
************************************************************
*/
void DelayUs(unsigned short us)
{

	TIM3->ARR = us;
	
	TIM3->PSC = 48;									//timer4Ϊ72MHz������Ϊ71+1��Ƶ��1MHz��1us����һ��
	
	TIM3->CR1 |= (unsigned short)TIM_CR1_CEN;		//��ʼ��ʱ
	
	while(!(TIM3->SR & 1));							//�ȴ������ж��¼�
	
	TIM3->SR &= ~(1UL << 0);						//�����־

}

/*
************************************************************
*	�������ƣ�	DelayXms
*
*	�������ܣ�	���뼶��ʱ
*
*	��ڲ�����	ms����ʱ��ʱ��
*
*	���ز�����	��
*
*	˵����		
************************************************************
*/
void DelayXms(unsigned short ms)
{

	while(ms--)
		DelayUs(1000);

}

/*
************************************************************
*	�������ƣ�	DelayMs
*
*	�������ܣ�	΢�뼶����ʱ
*
*	��ڲ�����	ms����ʱ��ʱ��
*
*	���ز�����	��
*
*	˵����		��ε���DelayXms����������ʱ
************************************************************
*/
void DelayMs(unsigned short ms)
{

	unsigned char repeat = 0;
	unsigned short remain = 0;
	
	repeat = ms / 500;
	remain = ms % 500;
	
	while(repeat)
	{
		DelayXms(500);
		repeat--;
	}
	
	if(remain)
		DelayXms(remain);

}
