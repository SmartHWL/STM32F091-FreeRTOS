#include "BLMC.h"

volatile unsigned char Phase = 0;
char SENSE_H=0,SENSE_L=0;

/*
* �������ƣ�commutation_control
* ���ã�������
* ������
* �����
*/
void commutation_control(void)
{
	unsigned char sense = 0;
	SENSE_H = (((ADC_num0>ADC_num1)||(ADC_num0>ADC_num2)||(ADC_num0>ADC_num2))?0:1);//MITTEL��ѹ���ڱ����õĸ�������ˣ�NULL_A �� NULL_B �� NULL_C�����ʽΪ1
	SENSE_L = (((ADC_num0>ADC_num1)||(ADC_num0>ADC_num2)||(ADC_num0>ADC_num2))?1:0);//MITTEL��ѹ���ڱ����õĸ�������ˣ�NULL_A �� NULL_B �� NULL_C�����ʽΪ0
	do
	{
		if(SENSE_H) sense = 1; else sense = 0; 
		switch(Phase)
	     {
	     case 0:                        //AB��ͨ��
	          STEUER_A_H;              //���STEUER_A+��PWM
	          if(sense)                //��⵽��0 
            {
	             STEUER_C_L;   //��STEUER_C-�����AB��AC�Ļ���
	             //if(ZeitZumAdWandeln) AdConvert();     //���ڽ�ZeitZumAdWandeln��1�����MOS�ܹ�������
	             //SENSE_FALLING_INT;    //��ⷽʽ �½��ز����ж�
//	             SENSE_B;              //ģ��Ƚ������NULL_B��MITTLE��ѹ ACͨ���ڼ�B���ѹ�ӵ���MITTLE�����ڸõ�����
	             Phase++;              //��ʱ��Ϊ AC��ͨ��  //--��ʱģ��Ƚϻ���һ���½���	          
							 CntKommutierungen++;   //��������ۼ�
	           }
	          else                    //û�м�⵽��0
	           {
	            STEUER_B_L;
	           }break;
			 case 1:  //AC��ͨ��
            STEUER_C_L;   //87���Ѿ���STEUER_C-
            if(!sense)   //case0��û�н�sense��0����ִ��else�������������¼���Ӱ��
            {
              STEUER_B_H;
             // if(ZeitZumAdWandeln) AdConvert();
             // SENSE_A; 
              //SENSE_RISING_INT;
              Phase++; 
              CntKommutierungen++;
             }
             else 
             {
               STEUER_A_H;
             }break;
			 case 2:  //BC��ͨ��
            STEUER_B_H;
            if(sense) 
            {
              STEUER_A_L;
              //if(ZeitZumAdWandeln) AdConvert();
             // SENSE_C; 
             // SENSE_FALLING_INT;
              Phase++; 
              CntKommutierungen++;
             }
             else 
             {
              STEUER_C_L;
             }break;
        case 3:  //BA��ͨ��
             STEUER_A_L;
             if(!sense) 
             {
              STEUER_C_H;
             // if(ZeitZumAdWandeln) AdConvert();
             // SENSE_B; 
             // SENSE_RISING_INT;
              Phase++; 
              CntKommutierungen++;
             }
             else 
             {
              STEUER_B_H;
             }break;
        case 4:  //CA��ͨ��
             STEUER_C_H;
             if(sense) 
             {
              STEUER_B_L;
              //if(ZeitZumAdWandeln) AdConvert();
             // SENSE_A;                     
             // SENSE_FALLING_INT;
              Phase++; 
              CntKommutierungen++;
             }
             else 
             {
              STEUER_A_L;
             }break;
        case 5:  //CB��ͨ��
             STEUER_B_L;
             if(!sense) 
             {
              STEUER_A_H;
              //if(ZeitZumAdWandeln) AdConvert();
             // SENSE_C; 
              //SENSE_RISING_INT;
              Phase = 0; 
              CntKommutierungen++;
             }
             else 
             {
              STEUER_C_H;
             }break;	 
	     }
	}
	while((SENSE_L && sense) || (SENSE_H && !sense));
}

/*
* �������ƣ�Manuell
* ���ã���������㷨
* ������
* �����
*/
void Manuell(void)  
{
 switch(Phase)
  {
   case 0:  
           STEUER_A_H;
           STEUER_B_L; //AB��ͨ��
          // SENSE_C; 
          // SENSE_RISING_INT; //����C�������رȽ�--166��main.c�Ѿ������жϲ���
          break;
   case 1:  
           STEUER_A_H;
           STEUER_C_L; //AC��ͨ��
          // SENSE_B; 
           //SENSE_FALLING_INT;
          break;
   case 2:  
           STEUER_B_H;
           STEUER_C_L;
          // SENSE_A; 
          // SENSE_RISING_INT;
          break;
   case 3:  
           STEUER_B_H;
           STEUER_A_L;
         //  SENSE_C; 
         //  SENSE_FALLING_INT;
          break;
   case 4:  
           STEUER_C_H;
           STEUER_A_L;
        //   SENSE_B; 
       //    SENSE_RISING_INT;
          break;
   case 5:  
           STEUER_C_H;
           STEUER_B_L;
      //     SENSE_A; 
       //    SENSE_FALLING_INT;
          break;
  }
}




