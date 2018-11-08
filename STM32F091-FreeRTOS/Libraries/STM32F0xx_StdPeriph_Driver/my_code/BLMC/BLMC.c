#include "BLMC.h"

volatile unsigned char Phase = 0;
char SENSE_H=0,SENSE_L=0;

/*
* 函数名称：commutation_control
* 作用：换相检测
* 参数：
* 输出：
*/
void commutation_control(void)
{
	unsigned char sense = 0;
	SENSE_H = (((ADC_num0>ADC_num1)||(ADC_num0>ADC_num2)||(ADC_num0>ADC_num2))?0:1);//MITTEL电压高于被复用的负向输入端（NULL_A 或 NULL_B 或 NULL_C）表达式为1
	SENSE_L = (((ADC_num0>ADC_num1)||(ADC_num0>ADC_num2)||(ADC_num0>ADC_num2))?1:0);//MITTEL电压高于被复用的负向输入端（NULL_A 或 NULL_B 或 NULL_C）表达式为0
	do
	{
		if(SENSE_H) sense = 1; else sense = 0; 
		switch(Phase)
	     {
	     case 0:                        //AB相通电
	          STEUER_A_H;              //输出STEUER_A+的PWM
	          if(sense)                //检测到过0 
            {
	             STEUER_C_L;   //打开STEUER_C-，完成AB到AC的换相
	             //if(ZeitZumAdWandeln) AdConvert();     //定期将ZeitZumAdWandeln置1，监测MOS管工作电流
	             //SENSE_FALLING_INT;    //监测方式 下降沿产生中断
//	             SENSE_B;              //模拟比较器监测NULL_B和MITTLE电压 AC通电期间B点电压从低于MITTLE到高于该点跳变
	             Phase++;              //此时已为 AC相通电  //--此时模拟比较会跳一个下降沿	          
							 CntKommutierungen++;   //换相次数累加
	           }
	          else                    //没有检测到过0
	           {
	            STEUER_B_L;
	           }break;
			 case 1:  //AC相通电
            STEUER_C_L;   //87行已经打开STEUER_C-
            if(!sense)   //case0并没有将sense置0，将执行else，消除“消磁事件”影响
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
			 case 2:  //BC相通电
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
        case 3:  //BA相通电
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
        case 4:  //CA相通电
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
        case 5:  //CB相通电
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
* 函数名称：Manuell
* 作用：电机启动算法
* 参数：
* 输出：
*/
void Manuell(void)  
{
 switch(Phase)
  {
   case 0:  
           STEUER_A_H;
           STEUER_B_L; //AB相通电
          // SENSE_C; 
          // SENSE_RISING_INT; //启动C相上升沿比较--166行main.c已经禁用中断产生
          break;
   case 1:  
           STEUER_A_H;
           STEUER_C_L; //AC相通电
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




