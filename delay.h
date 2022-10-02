#ifndef __DELAY_H__
#define __DELAY_H__

#include <stdint.h> //standard int library

void delay_Microsecond(uint32_t time); //delay in microseconds
void timer2A_init(void); //timer initialization interrupt service

static const uint8_t LIMIT = 10;
static const uint32_t RAND_MAX = 32767;

int8_t rand_lim(int8_t limit);

/*returns a pseudo-random number in the range of 0 to RAND_MAX
*RAND_MAX is a constant whose default value may vary between implementations but it is granted to be at least 32767*/

int rand(void);

#endif
