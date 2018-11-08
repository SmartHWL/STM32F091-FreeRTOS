#include "led.h"
extern char TIM15_num;

void LED1_Init(void)
{
	GPIO_InitTypeDef        GPIO_InitStructure;
	
	 /* GPIOC Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA, ENABLE);

  /* Configure PC10 and PC11 in output pushpull mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_OUT;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}

void LED1_Set(LED_ENUM status)
{
	GPIO_WriteBit(GPIOA, GPIO_Pin_5, status != LED_ON ? Bit_SET : Bit_RESET);
}



void LED1_Blink(char num)
{
	while(num--)
	{
		LED1_Set(LED_OFF);
		DelayXms(50);
		LED1_Set(LED_ON);
		DelayXms(50);
		LED1_Set(LED_OFF);
		DelayXms(50);
		LED1_Set(LED_ON);
		DelayXms(50);
		LED1_Set(LED_OFF);
		DelayXms(50);
		LED1_Set(LED_ON);
		DelayXms(1000);
	}
	
}





