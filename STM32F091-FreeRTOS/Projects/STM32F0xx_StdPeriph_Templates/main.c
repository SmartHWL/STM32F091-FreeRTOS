/**
  ******************************************************************************
  * @file    GPIO/GPIO_IOToggle/main.c 
  * @author  MCD Application Team
  * @version V1.4.0
  * @date    24-July-2014
  * @brief   Main program body
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
#ifdef __GNUC__
  /* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
     set to 'Yes') calls __io_putchar() */
  #define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
  #define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */
  
/* Includes ------------------------------------------------------------------*/
#include "main.h"
extern __IO uint16_t DutyCycle;//捕获得到的脉冲值


/* Private define ------------------------------------------------------------*/
unsigned int  CntKommutierungen = 0;  //Kommutierungen---commutations换相计数

/*
*********************************************************************************
*                                    主函数
*********************************************************************************
*/
int main(void)
{
  LED1_Init();//LED初始化
	//TIM1_PWM_OUTPUT_Config(4799,199);//PWM1 PWM2 PWM3输出初始化
  //TIM2_PWM_INPUT_Config();//PWM捕获初始化
	USART3_Config(115200);//串口3初始化
//  RCC_Configuration();
//	ADC_Config();//ADC初始化
  // Delay_Init();//TIM3延时
  /* TIM1 Configuration */
//	TIM15_Config();//TIM1初始化
	/* SysTick Configuration */
  	//SysTickConfig();
	start_TaskCreate();
  vTaskStartScheduler();          //开启任务调度
	while(1);
}



/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  /* Place your implementation of fputc here */
  /* e.g. write a character to the USART */
  USART_SendData(USART1, (uint8_t) ch);

  /* Loop until transmit data register is empty */
  while (USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET)
  {}

  return ch;
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif



