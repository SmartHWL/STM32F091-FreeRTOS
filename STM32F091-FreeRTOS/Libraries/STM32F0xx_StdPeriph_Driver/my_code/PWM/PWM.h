#ifndef __PWM_H
#define __PWM_H	 
#include "main.h"
/**********************************************************************************************
 *
 * 
 *
 *
 *
 *
 *
 *
***********************************************************************************************/
void TIM1_PWM_OUTPUT_Config(int arr,int psc);
void TIM17_PWM_OUTPUT_Config(int arr,int psc);
void TIM16_PWM_OUTPUT_Config(int arr,int psc);
void TIM2_PWM_INPUT_Config(void);
//ͨ���ı�PWM_Duty��ֵ���ı�ռ�ձ�
#define PWM1_Duty  TIM1->CCR1 
#define PWM2_Duty  TIM1->CCR2
#define PWM3_Duty  TIM1->CCR3
#endif



