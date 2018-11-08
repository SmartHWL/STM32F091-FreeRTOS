#include "GPIO.h"
/*
* 函数名称：GPIO_init
* 作用：部分引脚初始化
* 参数：
* 输出：PB8 PB9 PB10 输出高低电平
*/
void GPIO_init(void)
{
	GPIO_InitTypeDef        GPIO_InitStructure;

  /* GPIOA clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

  GPIO_StructInit(&GPIO_InitStructure);
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin   = GPIO_Pin_8  | GPIO_Pin_9  | GPIO_Pin_10 ;
  GPIO_Init(GPIOA, &GPIO_InitStructure);
}










