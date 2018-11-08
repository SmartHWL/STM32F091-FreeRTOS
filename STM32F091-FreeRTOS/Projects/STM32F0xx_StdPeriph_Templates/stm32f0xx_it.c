/**
  ******************************************************************************
  * @file    GPIO/GPIO_IOToggle/stm32f0xx_it.c 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    24-July-2014
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2014 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "stm32f0xx_it.h"
#include "FreeRTOS.h"

extern void vPortSVCHandler( void );
extern void xPortPendSVHandler( void );
extern void xPortSysTickHandler( void );


#define countof(a)   (sizeof(a) / sizeof(*(a)))
	
/* Private macro -------------------------------------------------------------*/
	
__IO uint8_t TxCount = 0; 
__IO uint16_t RxCount = 0; 

__IO uint16_t IC2Value = 0;
__IO uint16_t DutyCycle = 0;//捕获得到的脉冲值
__IO uint32_t Frequency = 0;

__IO uint8_t RxCounter= 0, ReceiveState = 0;
unsigned char aRxBuffer[10]={0};
/******************************************************************************/
/*            Cortex-M0 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
	vPortSVCHandler();
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
	
	xPortPendSVHandler();
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
	xPortSysTickHandler();
}
/******************************************************************************/
/*                 STM32F0xx Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f0xx.s).                                               */
/******************************************************************************/
/******************************************************************************/
/**
  * @brief  This function handles TIM1 Break, Update, Trigger and Commutation interrupt request.
  * @param  None
  * @retval None
  */
//函数每执行一次为1ms，这里执行频率与timer.c中的 SysTickConfig()有关
//这里写了个前50ms灭后50ms亮的测试程序
int num=0;
void TIM1_BRK_UP_TRG_COM_IRQHandler(void)
{
  /* Clear TIM1 COM pending bit */
  TIM_ClearITPendingBit(TIM1, TIM_IT_COM);
  //GPIO_SetBits(GPIOA,GPIO_Pin_5);
	num++;
	
  if (num == 1)
  {
		
		//GPIO_SetBits(GPIOA,GPIO_Pin_5);
    //step++;
  }
  else if (num == 2)
  {
	//	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
    //step=1;
  }
	if(num==50)
	{
	  //GPIO_SetBits(GPIOA,GPIO_Pin_5);
		
	}
	else if(num == 100)
	{
	//	GPIO_ResetBits(GPIOA,GPIO_Pin_5);
		num=0;
	}
}

char TIM15_num=0;
void TIM15_IRQHandler(void)
{
	
	TIM_ClearITPendingBit(TIM15, TIM_IT_COM);
//	if(TIM15_num==50)
//	{
//	  GPIO_SetBits(GPIOA,GPIO_Pin_5);
//		
//	}
//	else if(TIM15_num == 100)
//	{
//		GPIO_ResetBits(GPIOA,GPIO_Pin_5);
//		TIM15_num=0;
//	}
}


void TIM2_IRQHandler(void)
{
  /* Clear TIM2 Capture compare interrupt pending bit */
  TIM_ClearITPendingBit(TIM2, TIM_IT_CC2);

  /* Get the Input Capture value */
  IC2Value = TIM_GetCapture2(TIM2);

  if (IC2Value != 0)
  {
    /* Duty cycle computation */
    DutyCycle = (TIM_GetCapture1(TIM2) * 100) / IC2Value;

    /* Frequency computation */
    Frequency = SystemCoreClock / IC2Value;
  }
  else
  {
    DutyCycle = 0;
    Frequency = 0;
  }
}

extern uint32_t  ParaMeter;
extern unsigned char ADC_num,ADC_flag;
void ADC1_COMP_IRQHandler(void)
{
  if(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != RESET){//判断ADC是否转换完成，完成值为SET,未完成值为RESET 
	if(ADC_flag)
	  {
			 ParaMeter=ADC_GetConversionValue(ADC1);
			if(ADC_num==1)
			{
			   ADC_num0 = ((((ParaMeter *3300) >> 12)/1000)*10)+(((ParaMeter *3300) >> 12)%1000)/100;
				 USART_SendData(USART3, ADC_num0);
			}
			if(ADC_num==2)
			{
			   ADC_num1 = ((((ParaMeter *3300) >> 12)/1000)*10)+(((ParaMeter *3300) >> 12)%1000)/100;
				 USART_SendData(USART3, ADC_num1);
			}
			if(ADC_num==3)
			{
			   ADC_num2 = ((((ParaMeter *3300) >> 12)/1000)*10)+(((ParaMeter *3300) >> 12)%1000)/100;
			   USART_SendData(USART3, ADC_num2);
			}
			if(ADC_num==4)
			{
			   ADC_num3 = ((((ParaMeter *3300) >> 12)/1000)*10)+(((ParaMeter *3300) >> 12)%1000)/100;
		   	USART_SendData(USART3, ADC_num3);
			}
			if(ADC_num==5)
			{
			   ADC_num4 = ((((ParaMeter *3300) >> 12)/1000)*10)+(((ParaMeter *3300) >> 12)%1000)/100;
			   USART_SendData(USART3, ADC_num4);
			}
			if(ADC_num==6)
			{
			  ADC_num5 = ((((ParaMeter *3300) >> 12)/1000)*10)+(((ParaMeter *3300) >> 12)%1000)/100;
			  USART_SendData(USART3, ADC_num5);
			}
     ADC_flag=0;
   }
		ADC_ClearFlag(ADC1, ADC_FLAG_EOC);
		ADC_num=0;
	}
}

void USART3_8_IRQHandler(void)
{
	  if(USART_GetITStatus(USART3, USART_IT_RXNE) != RESET)
  {
    /* Read one byte from the receive data register */
    aRxBuffer[RxCounter++] = USART_ReceiveData(USART3);

    if(RxCounter == 10)
    {
		//	USART_ITConfig(USART1, USART_IT_RXNE, DISABLE);
      ReceiveState = 1;
      RxCounter = 0;
    }
  }
}


/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
