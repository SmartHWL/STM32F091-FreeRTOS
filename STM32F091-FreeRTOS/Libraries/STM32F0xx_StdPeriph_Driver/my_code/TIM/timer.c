#include "timer.h"

void TIM15_Config()
{
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseStructure;
  NVIC_InitTypeDef NVIC_InitStructure;

  /* TIM1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM15, ENABLE);  
	
  /* Time Base configuration */
  TIM_TimeBaseStructure.TIM_Prescaler =0 ;//psc
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = 4095;//;arr
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;

  TIM_TimeBaseInit(TIM15, &TIM_TimeBaseStructure);

  TIM_ITConfig(TIM15, TIM_IT_COM, ENABLE);

  /* TIM1 counter enable */
  TIM_Cmd(TIM15, ENABLE);

  /* Main Output Enable */
  TIM_CtrlPWMOutputs(TIM15, ENABLE);

  /* Enable the TIM1 Trigger and commutation interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM15_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);   
}

/**
  * @brief  Configures the SysTick.
  * @param  None
  * @retval None
  */
void SysTickConfig(void)
{
	//(SystemCoreClock) / 1000):
	//1000即为1000hz，时间为1ms
	//100为100hz，时间为10ms,以此类推
	 if(SysTick_Config((SystemCoreClock) / 1000))
  { 
   while (1);
  }
  NVIC_SetPriority(SysTick_IRQn, 0x0);
}











