/**@file tail.h
*@brief interface file for IR sensor initialization and operation
*/
#ifndef	TAIL_H__
#define TAIL_H__

#include <stdint.h>

#define IR_PIN   (1U<<5)//PA5 (INPUT);

void TAIL_Init(void);
uint32_t TAIL_sense(void);


#endif
