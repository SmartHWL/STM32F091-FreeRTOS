#ifndef __BLMC_H
#define __BLMC_H	 
#include "main.h"

extern int ADC_num0,ADC_num1,ADC_num2,ADC_num3,ADC_num4,ADC_num5;
extern int set_pwm;

#define PWM_A_ON  {PWM1_Duty=set_pwm;PWM2_Duty=0;PWM3_Duty=0;}//STEUER_A+���PWM�źŵ�ͬʱ��STEUER_C+��STEUER_B+���ص���
#define PWM_B_ON  {PWM1_Duty=0;PWM2_Duty=set_pwm;PWM3_Duty=0;}
#define PWM_C_ON  {PWM1_Duty=0;PWM2_Duty=0;PWM3_Duty=set_pwm;}
#define PWM_OFF   {PWM1_Duty=0;PWM2_Duty=0;PWM3_Duty=0;}

#define  STEUER_A_H {PWM_A_ON} 
#define  STEUER_B_H {PWM_B_ON}
#define  STEUER_C_H {PWM_C_ON}

#define STEUER_A_L {GPIO_SetBits(GPIOB,GPIO_Pin_8);GPIO_ResetBits(GPIOB,GPIO_Pin_9);GPIO_ResetBits(GPIOB,GPIO_Pin_10);}//STEUER_A-����ߵ磬ͬʱ�ض� NB-�� NC-��ЧӦ�ܡ�
#define STEUER_B_L {GPIO_ResetBits(GPIOB,GPIO_Pin_8);GPIO_SetBits(GPIOB,GPIO_Pin_9);GPIO_ResetBits(GPIOB,GPIO_Pin_10);}
#define STEUER_C_L {GPIO_ResetBits(GPIOB,GPIO_Pin_8);GPIO_ResetBits(GPIOB,GPIO_Pin_9);GPIO_SetBits(GPIOB,GPIO_Pin_10);}
#define STEUER_OFF {GPIO_ResetBits(GPIOB,GPIO_Pin_8);GPIO_ResetBits(GPIOB,GPIO_Pin_9);GPIO_SetBits(GPIOB,GPIO_Pin_10);PWM1_Duty=0;PWM2_Duty=0;PWM3_Duty=0;}//�ر�6����ЧӦ�ܣ�����ֹPWM�ź�
 
//#define SENSE_A                             //�� ADC0 �ܽŸ���Ϊģ��Ƚ����ķ�������ˡ�

//#define SENSE_L {sense_l}//MITTEL��ѹ���ڱ����õĸ�������ˣ�NULL_A �� NULL_B �� NULL_C�����ʽΪ0
//#define SENSE_H {sense_r}//MITTEL��ѹ���ڱ����õĸ�������ˣ�NULL_A �� NULL_B �� NULL_C�����ʽΪ1



void commutation_control(void);
void Manuell(void);


#endif





