/**@file ddelay.c
*	@email: jhiguera@ieee.org
*	@date: 12/08/2024
* @brief This file contains functions for delays with timer1 and timer2 initialization
*/

#include "TM4C123GH6PM.h"                    // Device header
#include <stdint.h>
#include "delay.h"

void delay_Microsecond(uint32_t time)
{
	int i;
	SYSCTL->RCGCTIMER |=(1U<<1); //Enable Clock access to Timer1
	TIMER1->CTL &=0; //disabled timer
	TIMER1->CFG = 0x4; //16 Bit MODE
	TIMER1->TAMR = 0x02; //TIMER1
	TIMER1->TAILR = 16-1; //Preescaler 16MHz
	TIMER1->ICR = 0x1; //Enable timer1 SET FLAG HIGH
	TIMER1->CTL |= 1; //Enable timer1
	
	for (i=0;i<time; i++){
		while((TIMER1->RIS&0x1)==0){
			TIMER1->ICR =0x1;
		}
	}	
}


void timer2A_init(void)
{
	SYSCTL->RCGCTIMER |=(1U<<4); //Enable Clock access to Timer2
	TIMER2->CTL &=0; //disabled timer2 before initialization
	TIMER2->CFG = 0x04; //16-bit mode option
	TIMER2->TAMR = 0x02; //TIMER2 in periodic mode and down-counter
	TIMER2->TAPR = 250; //16000000Hz /250  = 64000 Hz
  TIMER2->TAILR = 64000; //64000Hz /64000  = 1Hz
  TIMER2->ICR = 0x1; //Clear the timer2A timeout flag
  TIMER2->IMR |= 0x01; //Enable timer2A timeout interruption 	
	TIMER2->CTL |= 0x01; //Enable timer2A after initialization
	NVIC->ISER[0] |= 0x00800000; //Enable IRQ23 (D23 of ISER[0])
}

int8_t rand_lim(int8_t limit) {
/* return a random number between 0 and limit inclusive.
 */

    int divisor = RAND_MAX/(limit+1);
    int retval;

    do { 
        retval = rand() / divisor;
    } while (retval > limit);

    return retval;
}


