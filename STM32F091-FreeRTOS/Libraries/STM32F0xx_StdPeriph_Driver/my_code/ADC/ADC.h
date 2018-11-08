#ifndef __ADC_H
#define __ADC_H	 
#include "main.h"

typedef enum
{
  ADC1_In0,
	ADC1_In1,
	ADC1_In2,
	ADC1_In3,
	ADC1_In4,
	ADC1_In5,
	ADC1_In6,
	ADC1_In7,
}ADCn_Che;



void RCC_Configuration(void);
void ADC_Config(void);
void GetValue(unsigned char num);
//uint32_t ADC_GetValue(uint8_t times,unsigned char num);
void FastADConvert(void);
void ADC_GetNum(void);
void ADC_conversion(void);
#endif








