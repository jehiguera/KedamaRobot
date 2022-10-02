/**@file neck.h
*@brief interface file for servo motor initialization and operation
*/
#ifndef __NECK_H__
#define __NECK_H__

/**@brief Function for initialization servo motor with PWM control Enable port PF3 for PWM1 M1PWM7*/
void neck_init(void);

/**@brief Function for rotating servo-motor located at neck to a particular angle
*  @param[in] amount to rotate
*/
void neck_turn(uint32_t amount);

/**@brief Function to rotate servo-motor to the leftmost point in neck*/
void check_left(void);

/**@brief Function to rotate servo-motor to the rightmost point in  neck*/
void check_right(void);

/**@brief Function to rotate servo-motor to the rightmost point in  neck*/
void neck_move_right(void);

/**@brief Function to rotate servo-motor to the leftmost point in neck*/
void neck_move_left(void);

/**@brief Function to rotate servo-motor to the mid point in neck*/
void neck_move_center(void);

#endif
