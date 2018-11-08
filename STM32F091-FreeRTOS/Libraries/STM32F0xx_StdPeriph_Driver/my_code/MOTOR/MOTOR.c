#include "MOTOR.h"
unsigned char maxpwm;
extern volatile unsigned char Phase;
unsigned char maxstrom;
extern unsigned int  Strom,RuheStrom; //ca. in 0,1A  Ruhe---Quiet //��ǰ������ȫ�ضϾ�ֹ����

//оƬ�ڲ�����PWM,��ȫ�ֱ���PWM��ֵ���õ�PWM1_Duty,PWM2_Duty,PWM3_Duty 
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

#define TEST_STROMGRENZE 120    //GRENZE---BORDER ����Ϊ13A
unsigned char DelayM(unsigned int timer )
{
	while(timer--)
	{
		FastADConvert();
		if(ADC_num4 > (TEST_STROMGRENZE + RuheStrom)) //TEST_STROMGRENZEΪ228�к궨��
	   {                 //QuietCurrentȫ�ֱ����������г�ЧӦ��ȫ��ʱ���ܵ�©�����ܺ�
	     STEUER_OFF      //  FETS_OFF;        //�������ޣ��ر�MOSFET
		   return(1);
		 }
	}
	return 0;
}

//fire up--������� �ȳ���������Ȼ��д����ڲ���pwm����
char Anwerfen(unsigned char pwm)
{
	//unsigned long timer =300,i;
	//DISABLE_SENSE_INT;
	SetPwm(5);
	Manuell(); 
//	 MinUpmPulse = SetDelay(300);    //��СRpmת������--��ʱ��ʱ������
//	 while(!CheckDelay(MinUpmPulse)) //��ͣ�ļ��MOS�ܹ������� ִ�д�ѭ��Լ300ms
//		{
		  FastADConvert();
		  if(ADC_num4 > 200)           //����������ֵ�ر�MOSFET
		   {
		     STEUER_OFF;          // Abschalten wegen Kurzschluss---Shutdown due to short circuit
		     LED1_Blink(10);        //�����˸10��
		     return(0);           //����0����ʾ����ʧ��
		   }
//		}
	while(1)
	{
//		for(i=0;i<timer; i++)       //timer��ֵΪ300��ѭ��300m, �ڶ��μ���Ϊ(14/15)*300=280ms ,�����μ�Ϊ(14/15)*280=261ms ������ֱ����ΪС��25ms��Ȼ��return 1
//		{                         //������ڲ���æ�����͵�����ϢUebertragungAbgeschlossen=0��ʾ���У�=1��ʾ��æ
//		 if(!UebertragungAbgeschlossen) SendUart();          //Transmission Completed ����SendeBuffer[ ]�е�����
//		   else DatenUebertragung(); //Data transfer ���DebugOut�ṹ���е���ֵ�����ݰ���D��ͷ
//  		 DelayUs(1);              // warten �ӳ�100ns
//	  } 
//		DebugAusgaben();           //DebugAusgaben---debug output ����ǰ��Ϣд����Խṹ�� �� DebugOut.Analog[]��д����
  		FastADConvert();           //��ȡMOS�ܵ�����ֵ
		  if(ADC_num4 > 200)         //�����������60���ر�MOS�ܣ�������˳�ѭ��  --------------------------------------------------------------8-8
		  {
		   STEUER_OFF;             //Shutdown due to short circuit
		   LED1_Blink(10);
		   return(0);
		  }  
//---------��������ȷִ�����д���
//		timer-= timer/15+1;         //��14/15���ٶ�˥��--------debug1  ע�͵�
//    if(timer < 25)              //����궨��TEST_MANUELL��Ϊ0����һֱѭ��������returnѭ��
//	  { if(TEST_MANUELL) timer = 25; else return(1); } 
    Manuell();                  //Manuell--Manually  ��һ��ִ�иöδ��뱣��AB��ͨ�磬�������AB BC...֮���л�
    Phase++;
		Phase %= 6;                 //����6�����phase��0-5֮��ѭ��
//    AdConvert();
    SetPwm(pwm);
//    if(SENSE)                   //�ж�C���ѹ��û�б为��ͨ���̵�ָʾ״̬
//    {
//	    LED2_Blink(10);         //��һ��ִ�У������⵽C�ࣨ������A B C��֮���л�����ѹ�为��ָʾ�Ʊ��̣����������
//    }
	}
}

//MOSFET��������·���Լ�
void MotorTon(void)
{
	unsigned int i,t=1000;
//	unsigned char anz = 0,grenze=50;
	//DISABLE_SENSE_INT;                                  //�ر�ģ��Ƚ����ж�
	// cli();                                              //�ر������ж�
	STEUER_OFF;                                         //�ر�����MOS��
	//MaxCurrent = 0;                                     //ȫ�ֱ���MaxCurrent��0
	//QuietCurrent = MaxCurrent;                          //ȫ�ֱ���QuietCurrentȫ�ض�©������0
	for(i=0;i<t;i++)
	{
//		LOW_A_EIN;                                     //��STUERE_A-
  	DelayM(1);                                     //delayM����MOS�ܵ���
    STEUER_OFF//		FETS_OFF;                                      //�ض�MOS��
  	DelayUs(5);
//		HIGH_A_EIN;                                    //��STUERE_A+
  	DelayM(1);
    STEUER_OFF//		FETS_OFF;
		//if(ADC_num4 > grenze + RuheStrom)
		{
		 //anz = 4; 
		 STEUER_OFF//FETS_OFF;
		} 
    DelayUs(5);                                           //������������½���̫���������ϱ��4ͨ�����ڷ���
		                                                      //334��346��������Ŀ�ģ�һ���Ƿ���MOS���ѱ�����
			                                                    //                     ������ЧӦ�ܵĿ��������Ƿ��㹻����
	}
	DelayUs(1000);
	for(i=0;i<t;i++)                                    //ͬ333-347���ܣ�����B��MOS�ܣ����ϱ��5
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
	for(i=0;i<t;i++)                                    //ͬ333-347���ܣ�����C��MOS�ܣ����ϱ��6
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
//���MOS�ܴ��ڹ��ϣ�������ѭ���������˸anz�����ϱ�ŵĴ�����
// if(anz)                             
// {
//  while(1) LED1_Blink(anz); 
// }     
}


