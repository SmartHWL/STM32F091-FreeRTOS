#include "ADC.h"

extern unsigned char maxstrom;

unsigned int  Strom = 0,RuheStrom; //ca. in 0,1A  Ruhe---Quiet //当前电流和全关断静止电流
int ADC_num0=0,ADC_num1=0,ADC_num2=0,ADC_num3=0,ADC_num4=0,ADC_num5=0;

//RCC时钟配置
void RCC_Configuration(void)
{
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOA|RCC_AHBPeriph_GPIOB|
	                      RCC_AHBPeriph_GPIOC|RCC_AHBPeriph_GPIOD,ENABLE);
	 /* ADC1 Periph clock enable */
  RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	/* APB1 clock enable */
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM6,ENABLE);
	//ADC 2分频
  //RCC_ADCCLKConfig(RCC_ADCCLK_PCLK_Div2);
}


/*
* 函数名称：ADC_Config
* 作用：ADC初始化函数
* 参数：
* 输出：A0 A1 A2引脚采集
*/
void ADC_Config(void)
{
  GPIO_InitTypeDef    GPIO_InitStructure;
	NVIC_InitTypeDef    NVIC_InitStructure;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 |GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3 |GPIO_Pin_4|GPIO_Pin_5;
  GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd = GPIO_PuPd_NOPULL ;//无上下拉（浮空）
  GPIO_Init(GPIOA, &GPIO_InitStructure);
	
	ADC_InitTypeDef     ADC_InitStructure;
  /* ADCs DeInit */  
   ADC_DeInit(ADC1);
  /* Initialize ADC structure */
   ADC_StructInit(&ADC_InitStructure);
  
  /* Configure the ADC1 in continuous mode with a resolution equal to 12 bits  */
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b;
  ADC_InitStructure.ADC_ContinuousConvMode = DISABLE; 
  ADC_InitStructure.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_ScanDirection = ADC_ScanDirection_Backward;
  ADC_Init(ADC1, &ADC_InitStructure); 
  
	 ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);//允许adc传输完成中断
	
  /* ADC Calibration */
  ADC_GetCalibrationFactor(ADC1);
   NVIC_InitStructure.NVIC_IRQChannel = ADC1_COMP_IRQn;
  NVIC_InitStructure.NVIC_IRQChannelPriority = 0;
  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
  NVIC_Init(&NVIC_InitStructure);
  /* Enable the ADC peripheral */
  ADC_Cmd(ADC1, ENABLE);     
  
//  /* Wait the ADRDY flag */
//  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY)); 
//  
//  /* ADC1 regular Software Start Conv */ 
//  ADC_StartOfConversion(ADC1) 
}

/*
* 函数名称：GetValue
* 作用：ADC获取通道选择函数
* 参数：num：通道
* 输出：对应AD通道数值
  ||||||||||||||||||||||||||||||||
	A0-----------------ADC_Channel_0
	A1-----------------ADC_Channel_1
	A2-----------------ADC_Channel_2
	A3-----------------ADC_Channel_3
	A4-----------------ADC_Channel_4
	A5-----------------ADC_Channel_5
	||||||||||||||||||||||||||||||||
*/ 
uint32_t  ParaMeter=0;
unsigned char ADC_num=0,ADC_flag=0; 
void GetValue(unsigned char num)
{
	
    if(num==1){
			ADC_num=1;
	  ADC_ChannelConfig(ADC1, ADC_Channel_0 , ADC_SampleTime_239_5Cycles);//修改引脚ADC序号
		ADC1->CHSELR = ADC_Channel_0;
			
	  }
	  else if(num==2){
			ADC_num=2;
	  ADC_ChannelConfig(ADC1, ADC_Channel_1 , ADC_SampleTime_239_5Cycles);//修改引脚ADC序号
		ADC1->CHSELR = ADC_Channel_1;
	  }
		else if(num==3){
			ADC_num=3;
	  ADC_ChannelConfig(ADC1, ADC_Channel_2 , ADC_SampleTime_239_5Cycles);//修改引脚ADC序号
		ADC1->CHSELR = ADC_Channel_2;
	  }
		else if(num==4){
			ADC_num=4;
		ADC_ChannelConfig(ADC1, ADC_Channel_3 , ADC_SampleTime_239_5Cycles);//修改引脚ADC序号
		ADC1->CHSELR = ADC_Channel_3;
		}
		else if(num==5){
			ADC_num=5;
		ADC_ChannelConfig(ADC1, ADC_Channel_4 , ADC_SampleTime_239_5Cycles);//修改引脚ADC序号
		ADC1->CHSELR = ADC_Channel_4;
		}
		else if(num==6){
			ADC_num=6;
		ADC_ChannelConfig(ADC1, ADC_Channel_5 , ADC_SampleTime_239_5Cycles);//修改引脚ADC序号
		ADC1->CHSELR = ADC_Channel_5;
		}
		
   while(ADC_GetFlagStatus(ADC1, ADC_FLAG_ADRDY)==RESET);
   ADC_StartOfConversion(ADC1);
	 ADC_flag=1;
}

///*
//* 函数名称：ADC_GetValue
//* 作用：AD均值处理
//* 参数：times/倍数  num/通道
//* 输出：对应AD通道均值，经过电压值换算,
//*/
//uint32_t ADC_GetValue(uint8_t times,unsigned char num)
//{
//  uint32_t  ParaMeter=0;
//	//uint8_t i;
////	for(i=0;i<times;i++)
////	{
//    ParaMeter=GetValue(num); //+=GetValue(num);
////	} 
////    ParaMeter = ParaMeter/times;//除倍
//    /* Compute the volt age */
//    ParaMeter = (ParaMeter *3300) >> 12;//计算得1000倍的电压值
//	  return ParaMeter;
//}


void FastADConvert(void)
{
	unsigned int i=0;
	//i=GetValue(4);
	if(i>200)i=200;
	Strom=i;
	if(maxstrom<Strom)maxstrom=Strom;
//	ADCSRA = 0x00;     //关闭ADC
//  SFIOR = 0x08;      //Analog Comperator ein 恢复AC管脚复用功能
}

/*
* 函数名称：ADC_conversion
* 作用：电压换算并串口1发送
* 参数：
* 输出：串口1发送换算后的电压值
*/
uint32_t v=0,mv=0;
void ADC_conversion(void)//电压换算并串口1发送
{ 
	//,v1,mv1,v2,mv2,v3=0,mv3=0,v4,mv4,v5,mv5;
	//uint8_t text[50];
	//v=(GetValue(1))/1000;
  //mv = (GetValue(1)%1000)/100;//A0引脚的ADC值
//  v1=(ADC_GetValue(8,2))/1000;
//  mv1 = (ADC_GetValue(8,2)%1000)/100;//A1引脚的ADC值
//  v2=(ADC_GetValue(8,3))/1000;
//  mv2 = (ADC_GetValue(8,3)%1000)/100;//A2引脚的ADC值
//	v3=(ADC_GetValue(8,4))/1000;
//  mv3 = (ADC_GetValue(8,4)%1000)/100;//A3引脚的ADC值
//  v4=(ADC_GetValue(8,5))/1000;
//  mv4 = (ADC_GetValue(8,5)%1000)/100;//A4引脚的ADC值
//  v5=(ADC_GetValue(8,6))/1000;
//  mv5 = (ADC_GetValue(8,6)%1000)/100;//A5引脚的ADC值
  //sprintf((char*)text,"%d.%d V ",v,mv);//%d.%d V %d.%d V%d.%d V %d.%d V %d.%d V",v,mv,v1,mv1,v2,mv2,v3,mv3,v4,mv4,v5,mv5);
	//Usart_SendString(USART3, text, 10);
	//USART_SendData(USART3, v);
}





