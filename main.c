/**@file: main.c
*	@author: Jorge Higuera
*	@email: jhiguera@ieee.org
*	@date: 12/08/2024
*	@brief: this file contaians functions to work with Kedama robot 
*/

//#include "TM4C123.h"
#include "TM4C123GH6PM.h"
#include "head.h"
#include "light.h"
#include "delay.h"
#include "neck.h"
#include "tail.h"
#include "limbs.h"
#include "play_around.h"

	uint32_t dist;
	
	
int main()
{
	//HEAD_Init();    /*initialization of ultrasonics sensor*/
	//LIGHTS_Init();  /*Initialization of RGB LEDS*/
	neck_init();    /*Initialization of servo motor*/
	//LIMBS_Init();   /*Initialization of DC motors*/
	//TAIL_Init();    /*Initialization of IR sensor.*/
	//timer2A_init(); /*Initialization of TIMER2A for interrupt */
	
	//echoAndTimer0_Init();
	
	//__enable_irq(); /* global enable IRQs */
	
	while(1)
	{
		//---------Test neck--------------
		//neck_move_right();
		//delay_Microsecond(1500000);
		//neck_move_center();
		//delay_Microsecond(1500000);
		//neck_move_left();
		//delay_Microsecond(1500000);
		//neck_move_center();
		neck_turn(1000);
		delay_Microsecond(15000000);
		neck_turn(160000);
		delay_Microsecond(15000000);
		neck_turn(319000);
		delay_Microsecond(15000000);
		neck_turn(160000);
		delay_Microsecond(15000000);
		//-----------------------------
		//delay_Microsecond(150000);
		//check_left();
		//delay_Microsecond(1500000);
		//check_right();
		//delay_Microsecond(1500000);
		//shy();   /** shy()	: Assigned robot behavior*/
    //play();
	}
	
}

// Background Thread

void TIMER2A_Handler(void)
{
	volatile int readback;
	if(TIMER2->MIS & 0x1)  //Timer2A timeout flag
	{
		//Thread content
		dist = headSensor_detect();
			
			if(dist<7)
			{
				GPIOF->DATA ^=(BLUE|RED|GREEN);
			}
			else
			{
				GPIOF->DATA =0x00;
			}
		
		TIMER2->ICR = 0x1; //Clear the timer2A timeout flag
		readback = TIMER2->ICR;
	}
	else
	{
		TIMER2->ICR = TIMER2->MIS; //Clear all flags
		readback = TIMER2->ICR; //a read to force clearing of interrupt flag
	}
}
