/**@file limbs.c
*  @author J. Higuera
*	@email: jhiguera@ieee.org
*	@date: 12/08/2024
*  @brief This file contains functions that intialize and controls the DC motors and  
*/
#include <stdint.h>
#include "limbs.h" 
#include "delay.h"
 
void WALK_away(uint16_t distance)
 {
	 TURN_Left();
	 delay_Microsecond(6000);
	 FORWARD();
	 delay_Microsecond(10000+distance);
	 
 }
 void TURN_away(void)
 {
	 TURN_Right();
	 delay_Microsecond(6000);
 }
 void turnAwayRight(void)
 {
	 TURN_Right();
	 delay_Microsecond(6000);
 }
 void turnAwayRight180(void)
 {
	 TURN_Right();
	  delay_Microsecond(8000);
	 
 }
 void turnAwayRight360(void)
 {
	 TURN_Right();
	  delay_Microsecond(12000);
	
 }
 void turnAwayLeft180(void)
 {
	 TURN_Left();
	  delay_Microsecond(8000);
	
	}
 void turnAwayLeft360(void)
 {
	 TURN_Left();
	  delay_Microsecond(12000);
	 
 }

void turnAwayLeft(void)
{
	TURN_Left();
	delay_Microsecond(6000);
}
void walkForward(uint16_t distance)
{
	FORWARD();
	delay_Microsecond(1+distance);
}
void runToHide()
{
	STOP();
	delay_Microsecond(1000);
	turnAwayLeft360();
	walkForward(20000);
	STOP();
	
}
void seeWhoAndRun()
{
	STOP();
	delay_Microsecond(500);
	turnAwayRight360();
	STOP();
	delay_Microsecond(1000);
	turnAwayLeft360();
	walkForward(20000);
}
