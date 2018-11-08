#include "COMP.h"
/**
  * @brief  Configures COMP2: PA3 as COMP2 non inverting input
  *                           VREFINT as COMP2 inverting input
  *                           and COMP2 output to TIM1 BKIN.
  * @param  None
  * @retval None
	��ʵ��A3���Ųɼ��ĵ�ѹ���ڲ��ο���ѹVREFINT 1.2V���Ƚϣ�����A8�������PWM�ź�,�����3.3V
  */
	
void COMP2_Config(void)
{
  
  COMP_InitTypeDef        COMP_InitStructure;
  GPIO_InitTypeDef        GPIO_InitStructure;
  /* GPIOA Peripheral clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  /* Configure PA3 in analog mode: PA3 is connected to COMP2 non inverting input */
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* COMP Peripheral clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

  /* COMP2 config */
  COMP_StructInit(&COMP_InitStructure);
  COMP_InitStructure.COMP_InvertingInput = COMP_InvertingInput_VREFINT;//VREFINT���ӵ��Ƚ���������
	
  COMP_InitStructure.COMP_Output = COMP_Output_TIM1BKIN;//���ӵ�TIM1�ж������COMP��� 
	
  COMP_InitStructure.COMP_Hysteresis = COMP_Hysteresis_No;//�޳���
  COMP_InitStructure.COMP_Mode = COMP_Mode_UltraLowPower;//���͹���ģʽ
  COMP_InitStructure.COMP_OutputPol =  COMP_OutputPol_NonInverted;
  COMP_Init(COMP_Selection_COMP2, &COMP_InitStructure);

  /* Enable COMP2 */
  COMP_Cmd(COMP_Selection_COMP2, ENABLE);
}
