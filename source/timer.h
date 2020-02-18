/**
* @file
* @brief Library for the elevator's timer.
*/
#ifndef TIMER_H
#define TIMER_H

#include <time.h>

time_t DOOR_TIMER;

// void reset_timer();

// int check_timer();

/**
 * @brief Start the timer by setting the global variable @c DOOR_TIMER to the current time
 */
void start_timer();


/**
 * @brief Check if a certain amount of time has passed
 * 
 * @param[in] time_req  The time requirement to which we compare time passed.
 * 
 * @return 1 if @p time_req amount of time has passed since @c start_timer() was called, 0 if not.
 * 
 * @warning The return value for this function will not be 
 */
int check_timer(unsigned int time_req);

#endif //TIMER_H