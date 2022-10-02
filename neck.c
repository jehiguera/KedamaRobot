/**@file neck.c
* @author J.Higuera
* @date 30/03/2021
* @brief This file implements functions which initialize PWM control\n
*  for the servo motor.
*/

                   
#include "TM4C123GH6PM.h" // MCU package used
#include "delay.h"

#define LOAD_VALUE 320000 //Desired frequency= 50Hz  System frequency= 16MHz  Load value = 320000
#define MIN_DUTY_CYCLE 319000 //Value to rotate servo motor to the leftmost point
#define MAX_DUTY_CYCLE 1000 //Value to rotate servo motor to the rightmost point
#define _50P_DUTY_CYCLE 160000 //Value to rotate servo motor to the mid-point


void neck_init(void)
{
	int i = 0;
	//Enable peripheral clocks
	SYSCTL->RCGCPWM |= 2; //Enable clock to PWM1 
	SYSCTL->RCGCGPIO |= 0x20; //Enable clock to PORTF
	SYSCTL->RCC &= ~0x00100000; // No pre-divide for PWM clock
		while(i<40){i++;}
		
		//Enable port PF3 for PWM1 M1PWM7
		GPIOF->AFSEL = 8; //(1000) PF3 uses alternative function
		GPIOF->PCTL &= ~0x0000F000; //make PF3 PWM output pin step A
		GPIOF->PCTL |= 0x00005000; //Step B
		GPIOF->DEN |= 8; //pin digital enable
	
		PWM1->_3_CTL =0;//disable the PWM before configuration stop counter
		PWM1->_3_GENB =0x0000008C; //M1PWM7 output set when reload
		PWM1->_3_LOAD = LOAD_VALUE-1;//LOAD_VALUE = (1/Desired PWM frequency)*System frequency
		PWM1->_3_CMPA = MIN_DUTY_CYCLE; //set duty cycle %
		PWM1->_3_CTL = 1; //start timer
		PWM1->ENABLE = 0x80; //start PWM1 CH7
}

void neck_turn(uint32_t amount)
{
	PWM1->_3_CMPA = amount;
}

void check_left(void)
{
	uint32_t i;
	
	PWM1->ENABLE |= 0x80;
	for(i=319000; i<=1; i-=5000)
	{
		PWM1->_3_CMPA = i;
		delay_Microsecond(500000); //1 seg
	}
	PWM1->ENABLE &= ~0x80;
}

void check_right(void)
{
	uint32_t i;
	
	PWM1->ENABLE |= 0x80;
	for(i=1000; i<=160000; i+=1000)
	{
		PWM1->_3_CMPA = i;
		delay_Microsecond(100000); //1seg
	}
	PWM1->ENABLE &= ~0x80;
}

void neck_move_left(void)
{
	PWM1->_3_CMPA = MIN_DUTY_CYCLE;
}

void neck_move_right(void)
{
	//PWM1->ENABLE |= 0x80;
	PWM1->_3_CMPA = MAX_DUTY_CYCLE;
	//PWM1->ENABLE &= ~0x80;
}

void neck_move_center(void)
{
	PWM1->_3_CMPA = _50P_DUTY_CYCLE;
}
