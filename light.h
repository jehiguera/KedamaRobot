/**@file ligh.h
*@brief interface file for LEDs initialization and operation
*/

#ifndef __LIGHT_H__
#define __LIGHT_H__

#define RED (1U<<1) //PF1
#define BLUE (1U<<2) //PF2
#define GREEN (1U<<3) //PF3

void LIGHTS_Init(void);

#endif
