#include "MOTOR.h"
unsigned char maxpwm;
extern volatile unsigned char Phase;
unsigned char maxstrom;
extern unsigned int  Strom,RuheStrom; //ca. in 0,1A  Ruhe---Quiet //当前电流和全关断静止电流

//芯片内部生成PWM,将全局变量PWM的值设置到PWM1_Duty,PWM2_Duty,PWM3_Duty 
void SetPwm(unsigned char tmp_pwm)
{
	if(tmp_pwm>maxpwm)
	{
		tmp_pwm=maxpwm;
	}
	if(ADC_num4>maxstrom)
	{
		PWM_OFF;
		LED1_Blink(10);
	}
	else 
	{
		PWM1_Duty=set_pwm;
		PWM2_Duty=set_pwm;
		PWM3_Duty=set_pwm;
	}
}

#define TEST_STROMGRENZE 120    //GRENZE---BORDER 上限为13A
unsigned char DelayM(unsigned int timer )
{
	while(timer--)
	{
		FastADConvert();
		if(ADC_num4 > (TEST_STROMGRENZE + RuheStrom)) //TEST_STROMGRENZE为228行宏定义
	   {                 //QuietCurrent全局变量，当所有场效应管全关时各管的漏电流总和
	     STEUER_OFF      //  FETS_OFF;        //电流超限，关闭MOSFET
		   return(1);
		 }
	}
	return 0;
}

//fire up--电机启动 先尝试启动，然后写入入口参数pwm运行
char Anwerfen(unsigned char pwm)
{
	//unsigned long timer =300,i;
	//DISABLE_SENSE_INT;
	SetPwm(5);
	Manuell(); 
//	 MinUpmPulse = SetDelay(300);    //最小Rpm转速脉冲--延时定时器变量
//	 while(!CheckDelay(MinUpmPulse)) //不停的监测MOS管工作电流 执行此循环约300ms
//		{
		  FastADConvert();
		  if(ADC_num4 > 200)           //电流大于阈值关闭MOSFET
		   {
		     STEUER_OFF;          // Abschalten wegen Kurzschluss---Shutdown due to short circuit
		     LED1_Blink(10);        //红灯闪烁10次
		     return(0);           //返回0，表示启动失败
		   }
//		}
	while(1)
	{
//		for(i=0;i<timer; i++)       //timer初值为300，循环300m, 第二次减少为(14/15)*300=280ms ,第三次减为(14/15)*280=261ms 。。。直到减为小于25ms，然后return 1
//		{                         //如果串口不繁忙，发送调试信息UebertragungAbgeschlossen=0表示空闲，=1表示繁忙
//		 if(!UebertragungAbgeschlossen) SendUart();          //Transmission Completed 发送SendeBuffer[ ]中的数据
//		   else DatenUebertragung(); //Data transfer 输出DebugOut结构体中的数值，数据包以D开头
//  		 DelayUs(1);              // warten 延迟100ns
//	  } 
//		DebugAusgaben();           //DebugAusgaben---debug output 将当前信息写入调试结构体 往 DebugOut.Analog[]中写数据
  		FastADConvert();           //获取MOS管电流数值
		  if(ADC_num4 > 200)         //如果电流大于60，关闭MOS管，闪红灯退出循环  --------------------------------------------------------------8-8
		  {
		   STEUER_OFF;             //Shutdown due to short circuit
		   LED1_Blink(10);
		   return(0);
		  }  
//---------若电流正确执行下列代码
//		timer-= timer/15+1;         //以14/15的速度衰减--------debug1  注释掉
//    if(timer < 25)              //如果宏定义TEST_MANUELL不为0，则一直循环，否则return循环
//	  { if(TEST_MANUELL) timer = 25; else return(1); } 
    Manuell();                  //Manuell--Manually  第一次执行该段代码保持AB相通电，后面会在AB BC...之间切换
    Phase++;
		Phase %= 6;                 //求余6运算后phase在0-5之间循环
//    AdConvert();
    SetPwm(pwm);
//    if(SENSE)                   //判断C相电压有没有变负，通过绿灯指示状态
//    {
//	    LED2_Blink(10);         //第一次执行，如果检测到C相（后面在A B C相之间切换）电压变负，指示灯变绿，电机已正常
//    }
	}
}

//MOSFET及驱动电路的自检
void MotorTon(void)
{
	unsigned int i,t=1000;
//	unsigned char anz = 0,grenze=50;
	//DISABLE_SENSE_INT;                                  //关闭模拟比较器中断
	// cli();                                              //关闭所有中断
	STEUER_OFF;                                         //关闭所有MOS管
	//MaxCurrent = 0;                                     //全局变量MaxCurrent置0
	//QuietCurrent = MaxCurrent;                          //全局变量QuietCurrent全关断漏电流置0
	for(i=0;i<t;i++)
	{
//		LOW_A_EIN;                                     //打开STUERE_A-
  	DelayM(1);                                     //delayM会检测MOS管电流
    STEUER_OFF//		FETS_OFF;                                      //关断MOS管
  	DelayUs(5);
//		HIGH_A_EIN;                                    //打开STUERE_A+
  	DelayM(1);
    STEUER_OFF//		FETS_OFF;
		//if(ADC_num4 > grenze + RuheStrom)
		{
		 //anz = 4; 
		 STEUER_OFF//FETS_OFF;
		} 
    DelayUs(5);                                           //如果被击穿或下降沿太缓慢，故障编号4通过串口发送
		                                                      //334至346行有两个目的，一：是否有MOS管已被击穿
			                                                    //                     二：场效应管的开关特性是否足够陡峭
	}
	DelayUs(1000);
	for(i=0;i<t;i++)                                    //同333-347功能，测试B相MOS管，故障编号5
  {
//	 LOW_B_EIN; 
  	 DelayM(1);
     STEUER_OFF//	 FETS_OFF;
  	 DelayUs(5);
//	 HIGH_B_EIN;
  	 DelayM(1);
     STEUER_OFF//	 FETS_OFF;
	// if(ADC_num4 > grenze + RuheStrom)
	 {
		 //anz = 5;
		 STEUER_OFF//FETS_OFF; 
	 }
	 DelayUs(5);
  }
  DelayUs(1000);
	for(i=0;i<t;i++)                                    //同333-347功能，测试C相MOS管，故障编号6
	{
//	LOW_C_EIN; 
  	DelayM(1);
    STEUER_OFF//	FETS_OFF;
    DelayUs(5);
//	HIGH_C_EIN;
  	DelayM(1);
    STEUER_OFF//	FETS_OFF;
	// if(ADC_num4 > grenze + RuheStrom) 
	 {
	 // anz = 6;
 		STEUER_OFF//FETS_OFF;
   }
	DelayUs(5);
  }
//如果MOS管存在故障，进入死循环，红灯闪烁anz（故障编号的次数）
// if(anz)                             
// {
//  while(1) LED1_Blink(anz); 
// }     
}


