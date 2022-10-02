/**@file head.c
* @author J.Higuera
* @date 25/03/2021
* @brief This file contains functions to initialize Timer0 in Edge-capture\n
* mode in order to be able detect the precise time when the echo signals is detected
*/

#include "TM4C123.h"                    // Device header
#include <stdint.h>
#include "head.h"
#include "delay.h"

void echoAndTimer0_Init(void)
{
	SYSCTL->RCGCTIMER |=(1U<<0); //Enable Clock access to Timer0
	SYSCTL->RCGCGPIO |=(1U<<1); //Enable clock accces to Port PB6
	GPIOB->DIR &=~ECHO; //set the direction register: input type
	GPIOB->DEN |=ECHO; //Digital enable pin
	GPIOB->AFSEL |=ECHO; //Set alternative function register PB6
	GPIOB->PCTL &=~0x0F000000; //access port control register edge capture step1
	GPIOB->PCTL |=~0x0F000000; //access port control register step 2
	
	TIMER0->CTL &=~1; //disabled timer
	TIMER0->CFG = 4; //16 BIT MODE
	TIMER0->TAMR = 0x17; //TIMER0
	TIMER0->CTL |= 0x0C; //enable edge trigger mode 
	TIMER0->CTL |= 1; //Enable timer0
	
}

void HEAD_Init(void){
	SYSCTL->RCGCGPIO |=(1U<<0); //Enable PortA 0000 0001
	GPIOA->DIR |=TRIGGER; //binario = 0001 0000 / hexa: 0x10
	GPIOA->DEN |=TRIGGER;
}

uint32_t headSensor_detect(void)
{
	GPIOA->DATA &=~TRIGGER;
	delay_Microsecond(12);
	GPIOA->DATA |=TRIGGER;
	delay_Microsecond(12);
	GPIOA->DATA &=~TRIGGER;
	/*Capture first edge i.e rising edge*/
	TIMER0->ICR=4; //clear timer capture flag
	while((TIMER0->RIS &4)==0){};
		highEdge =TIMER0->TAR;
	/*Capture secondEdge i.e fallingedge*/
	TIMER0->ICR=4; //clear timer capture flag
	while((TIMER0->RIS &4)==0){};	
	lowEdge = TIMER0->TAR;
	ddistance = lowEdge - highEdge;
	ddistance = _16MHz_1clock*(double) MULTIPLIER *(double)ddistance;
		return ddistance;
}
