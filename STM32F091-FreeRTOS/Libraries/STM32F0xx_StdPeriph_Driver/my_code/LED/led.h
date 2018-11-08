#ifndef __LED_H
#define __LED_H	 
#include "main.h"

typedef enum
{

	LED_OFF = 0,
	LED_ON

} LED_ENUM;


void LED1_Init(void);
void LED1_Set(LED_ENUM status);
void LED1_Blink(char num);



#endif
