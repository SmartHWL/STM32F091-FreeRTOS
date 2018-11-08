#include "PWM.h"
int set_pwm=0;

/*
* 函数名称：TIM1_PWM_OUTPUT_Config
* 作用：PWM1输出函数
* 参数：
* 输出：PA8 PA9 PA10 输出PWM信号
*/
//        
//TIM1_PWM_Config(int arr,int psc)
//arr:  4799      psc： 199
//得出的频率的50HZ，之后的PWM1_Duty控制量从0%~100%的值为0~4799
//示例程序TIM1，PA8 A9 A10输出PWM信号
void TIM1_PWM_OUTPUT_Config(int arr,int psc)
{
 
//  TIM_BDTRInitTypeDef     TIM_BDTRInitStructure;
  TIM_OCInitTypeDef       TIM_OCInitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  GPIO_InitTypeDef        GPIO_InitStructure;

  /* GPIOA clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  /* TIM1 channels pin configuration:
       TIM1_CH1 -> PA8
	     TIM1_CH2 -> PA9
	     TIM1_CH3 -> PA10
  */
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8  |GPIO_Pin_9  |GPIO_Pin_10 ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Enable Alternate function on PA8 PA9 PA10 to be controlled by TIM1 */
   GPIO_PinAFConfig(GPIOA, GPIO_PinSource8, GPIO_AF_2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource9, GPIO_AF_2);
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource10, GPIO_AF_2);
  /* TIM1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);

  /* Time Base configuration */
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = psc;//199
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = arr;//4799
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM1, &TIM_TimeBaseStructure);

  /* Channel 1 Configuration in PWM mode */
  TIM_OCStructInit(&TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//指定TIM输出比较状态
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;//指定TIM互补输出比较状态
  TIM_OCInitStructure.TIM_Pulse =100;//指定要加载到捕捉比较寄存器中的脉冲值
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;//在空闲状态下指定TIM输出Pin状态
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
  TIM_OC1Init(TIM1, &TIM_OCInitStructure);
	
	TIM_OCInitStructure.TIM_Pulse =100;
  TIM_OC2Init(TIM1, &TIM_OCInitStructure);

  TIM_OCInitStructure.TIM_Pulse =100;
  TIM_OC3Init(TIM1, &TIM_OCInitStructure);

//  /* Automatic Output enable, Break, dead time and lock configuration*/
//  TIM_BDTRStructInit(&TIM_BDTRInitStructure);
//  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;//指定运行模式中使用的非状态选择
//  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;//指定空闲状态中使用的状态
//  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;//指定锁级参数
//  TIM_BDTRInitStructure.TIM_DeadTime = 11;//指定输出和输出之间的延迟时间
//  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;//指定是否启用了TIM Break输入
//  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;//指定TIM中断输入销极性
//  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;//指定是否启用了TIM自动输出特性
//  TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);

  /* Main Output Enable */
  TIM_CtrlPWMOutputs(TIM1, ENABLE);

  /* TIM1 counter enable */
  TIM_Cmd(TIM1, ENABLE);
}

//PWM输出实验，A6引脚输出PWM引脚
void TIM16_PWM_OUTPUT_Config(int arr,int psc)
{
//  TIM_BDTRInitTypeDef     TIM_BDTRInitStructure;
  TIM_OCInitTypeDef       TIM_OCInitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  GPIO_InitTypeDef        GPIO_InitStructure;

  /* GPIOA clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  /* TIM1 channels pin configuration:
       TIM16_CH1 -> PA6
  */
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_6;
  GPIO_Init(GPIOA, &GPIO_InitStructure);

  /* Enable Alternate function on PA6 to be controlled by TIM16 */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource6, GPIO_AF_5);

  /* TIM1 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM16 , ENABLE);
  /* Time Base configuration */
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = psc;//199
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = arr;//4799
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM16, &TIM_TimeBaseStructure);

  /* Channel 1 Configuration in PWM mode */
  TIM_OCStructInit(&TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//指定TIM输出比较状态
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;//指定TIM互补输出比较状态
  TIM_OCInitStructure.TIM_Pulse =100;//指定要加载到捕捉比较寄存器中的脉冲值
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;//在空闲状态下指定TIM输出Pin状态
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
  TIM_OC1Init(TIM16, &TIM_OCInitStructure);

//  /* Automatic Output enable, Break, dead time and lock configuration*/
//  TIM_BDTRStructInit(&TIM_BDTRInitStructure);
//  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;//指定运行模式中使用的非状态选择
//  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;//指定空闲状态中使用的状态
//  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;//指定锁级参数
//  TIM_BDTRInitStructure.TIM_DeadTime = 11;//指定输出和输出之间的延迟时间
//  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;//指定是否启用了TIM Break输入
//  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;//指定TIM中断输入销极性
//  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;//指定是否启用了TIM自动输出特性
//  TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);

  /* Main Output Enable */
  TIM_CtrlPWMOutputs(TIM16, ENABLE);

  /* TIM16 counter enable */
  TIM_Cmd(TIM16, ENABLE);
}

//PWM输出实验，B9引脚输出PWM信号
void TIM17_PWM_OUTPUT_Config(int arr,int psc)
{
//  TIM_BDTRInitTypeDef     TIM_BDTRInitStructure;
  TIM_OCInitTypeDef       TIM_OCInitStructure;
  TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
  GPIO_InitTypeDef        GPIO_InitStructure;

  /* GPIOB clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  /* TIM17 channels pin configuration:
       TIM17_CH1 -> PB9
  */
  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_9;
  GPIO_Init(GPIOB, &GPIO_InitStructure);

  /* Enable Alternate function on PB9 to be controlled by TIM17 */
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource9, GPIO_AF_2);

  /* TIM17 clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM17 , ENABLE);
  /* Time Base configuration */
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure);
  TIM_TimeBaseStructure.TIM_Prescaler = psc;//199
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseStructure.TIM_Period = arr;//4799
  TIM_TimeBaseStructure.TIM_ClockDivision = 0;
  TIM_TimeBaseStructure.TIM_RepetitionCounter = 0;
  TIM_TimeBaseInit(TIM17, &TIM_TimeBaseStructure);

  /* Channel 1 Configuration in PWM mode */
  TIM_OCStructInit(&TIM_OCInitStructure);
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM2;
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;//指定TIM输出比较状态
  TIM_OCInitStructure.TIM_OutputNState = TIM_OutputNState_Enable;//指定TIM互补输出比较状态
  TIM_OCInitStructure.TIM_Pulse =100;//指定要加载到捕捉比较寄存器中的脉冲值
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_Low;
  TIM_OCInitStructure.TIM_OCNPolarity = TIM_OCNPolarity_Low;
  TIM_OCInitStructure.TIM_OCIdleState = TIM_OCIdleState_Set;//在空闲状态下指定TIM输出Pin状态
  TIM_OCInitStructure.TIM_OCNIdleState = TIM_OCIdleState_Reset;
  TIM_OC1Init(TIM17, &TIM_OCInitStructure);

//  /* Automatic Output enable, Break, dead time and lock configuration*/
//  TIM_BDTRStructInit(&TIM_BDTRInitStructure);
//  TIM_BDTRInitStructure.TIM_OSSRState = TIM_OSSRState_Enable;//指定运行模式中使用的非状态选择
//  TIM_BDTRInitStructure.TIM_OSSIState = TIM_OSSIState_Enable;//指定空闲状态中使用的状态
//  TIM_BDTRInitStructure.TIM_LOCKLevel = TIM_LOCKLevel_1;//指定锁级参数
//  TIM_BDTRInitStructure.TIM_DeadTime = 11;//指定输出和输出之间的延迟时间
//  TIM_BDTRInitStructure.TIM_Break = TIM_Break_Enable;//指定是否启用了TIM Break输入
//  TIM_BDTRInitStructure.TIM_BreakPolarity = TIM_BreakPolarity_High;//指定TIM中断输入销极性
//  TIM_BDTRInitStructure.TIM_AutomaticOutput = TIM_AutomaticOutput_Enable;//指定是否启用了TIM自动输出特性
//  TIM_BDTRConfig(TIM1, &TIM_BDTRInitStructure);

  /* Main Output Enable */
  TIM_CtrlPWMOutputs(TIM17, ENABLE);

  /* TIM1 counter enable */
  TIM_Cmd(TIM17, ENABLE);
}

//       PWM捕获函数
//示例程序采用TIM2，PA1引脚捕获PWM脉冲
////PWM捕获实验需最终  PWM_Duty=DutyCycle 		A8引脚才会输出捕获的PWM
void TIM2_PWM_INPUT_Config(void)
{
  TIM_ICInitTypeDef  TIM_ICInitStructure;
  GPIO_InitTypeDef   GPIO_InitStructure;
  NVIC_InitTypeDef   NVIC_InitStructure;

  /* TIM2 clock enable */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

  /* GPIOA clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);
  
  /* TIM2 chennel2 configuration : PA.01 */
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
  
  /* Connect TIM pin to AF2 */
  GPIO_PinAFConfig(GPIOA, GPIO_PinSource1, GPIO_AF_2);
  
    /* Enable the TIM2 global Interrupt */
  NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  
 /* --------------------------------------------------------------------------- 
    TIM2 configuration: PWM Input mode
     The external signal is connected to TIM2 CH2 pin (PA.01)
     TIM2 CCR2 is used to compute the frequency value 
     TIM2 CCR1 is used to compute the duty cycle value

    In this example TIM2 input clock (TIM2CLK) is set to APB1 clock (PCLK1), since
    APB1 prescaler is set to 1.
      TIM2CLK = PCLK1 = HCLK = SystemCoreClock

    External Signal Frequency = SystemCoreClock / TIM2_CCR2 in Hz.
    External Signal DutyCycle = (TIM2_CCR1*100)/(TIM2_CCR2) in %.
  Note: 
  SystemCoreClock variable holds HCLK frequency and is defined in system_stm32f0xx.c file.
  Each time the core clock (HCLK) changes, user had to call SystemCoreClockUpdate()
  function to update SystemCoreClock variable value. Otherwise, any configuration
  based on this variable will be incorrect.
  --------------------------------------------------------------------------- */
  
  TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
  TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
  TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
  TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
  TIM_ICInitStructure.TIM_ICFilter = 0x0;

  TIM_PWMIConfig(TIM2, &TIM_ICInitStructure);

  /* Select the TIM2 Input Trigger: TI2FP2 */
  TIM_SelectInputTrigger(TIM2, TIM_TS_TI2FP2);

  /* Select the slave Mode: Reset Mode */
  TIM_SelectSlaveMode(TIM2, TIM_SlaveMode_Reset);
  TIM_SelectMasterSlaveMode(TIM2,TIM_MasterSlaveMode_Enable);

  /* TIM enable counter */
  TIM_Cmd(TIM2, ENABLE);

  /* Enable the CC2 Interrupt Request */
   TIM_ITConfig(TIM2, TIM_IT_CC2, ENABLE);

}




