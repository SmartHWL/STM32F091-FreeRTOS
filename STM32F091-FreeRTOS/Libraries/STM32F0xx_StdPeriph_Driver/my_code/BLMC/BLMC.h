#ifndef __BLMC_H
#define __BLMC_H	 
#include "main.h"

extern int ADC_num0,ADC_num1,ADC_num2,ADC_num3,ADC_num4,ADC_num5;
extern int set_pwm;

#define PWM_A_ON  {PWM1_Duty=set_pwm;PWM2_Duty=0;PWM3_Duty=0;}//STEUER_A+输出PWM信号的同时将STEUER_C+和STEUER_B+都关掉。
#define PWM_B_ON  {PWM1_Duty=0;PWM2_Duty=set_pwm;PWM3_Duty=0;}
#define PWM_C_ON  {PWM1_Duty=0;PWM2_Duty=0;PWM3_Duty=set_pwm;}
#define PWM_OFF   {PWM1_Duty=0;PWM2_Duty=0;PWM3_Duty=0;}

#define  STEUER_A_H {PWM_A_ON} 
#define  STEUER_B_H {PWM_B_ON}
#define  STEUER_C_H {PWM_C_ON}

#define STEUER_A_L {GPIO_SetBits(GPIOB,GPIO_Pin_8);GPIO_ResetBits(GPIOB,GPIO_Pin_9);GPIO_ResetBits(GPIOB,GPIO_Pin_10);}//STEUER_A-输出高电，同时关断 NB-和 NC-场效应管。
#define STEUER_B_L {GPIO_ResetBits(GPIOB,GPIO_Pin_8);GPIO_SetBits(GPIOB,GPIO_Pin_9);GPIO_ResetBits(GPIOB,GPIO_Pin_10);}
#define STEUER_C_L {GPIO_ResetBits(GPIOB,GPIO_Pin_8);GPIO_ResetBits(GPIOB,GPIO_Pin_9);GPIO_SetBits(GPIOB,GPIO_Pin_10);}
#define STEUER_OFF {GPIO_ResetBits(GPIOB,GPIO_Pin_8);GPIO_ResetBits(GPIOB,GPIO_Pin_9);GPIO_SetBits(GPIOB,GPIO_Pin_10);PWM1_Duty=0;PWM2_Duty=0;PWM3_Duty=0;}//关闭6个场效应管，并终止PWM信号
 
//#define SENSE_A                             //将 ADC0 管脚复用为模拟比较器的反向输入端。

//#define SENSE_L {sense_l}//MITTEL电压高于被复用的负向输入端（NULL_A 或 NULL_B 或 NULL_C）表达式为0
//#define SENSE_H {sense_r}//MITTEL电压高于被复用的负向输入端（NULL_A 或 NULL_B 或 NULL_C）表达式为1



void commutation_control(void);
void Manuell(void);


#endif





