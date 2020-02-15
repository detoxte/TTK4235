/**
* @file
* @brief IO library for elevator, spanning set/get-functions for buttons and lights
*/
#ifndef ELEVATOR_IO_H
#define ELEVATOR_IO_H

#include "includes.h"
#include "queue.h"

typedef struct{
    int door_open;
    int next_action;
    int last_floor;
    HardwareMovement last_dir;
    elevator_state_t state;
} elevator_data_t;

/**
 * @brief Find what floor the elevator is at
 * 
 * @return -1 if the elevator is between floors, and an int corresponding to the current floor
 * if the elevator is at a floor
 * 
 * @warning Because the elevator hardware's floors are indexed at 0, a non-truthy value (0) will
 * be returned when the elevator is at the first floor
 */
int at_floor();


/**
 * @brief Poll all floor buttons
 * 
 * @warning This function operates on the assumption that @c ORDERS_UP and @c ORDERS_DOWN are 
 * set with 0's and 1's, respectively for "button not clicked" and "button clicked"
 * 
 * @warning This function also uses @c set_floor_button_lights() to set the button lights
 * 
 * The function checks every external elevator button, from the first floor to the last floor.
 * Upon finding a button that is clicked, that has not already been clicked ( by checking
 * the @c ORDERS_UP and @c ORDERS_DOWN arrays), the corresponding value in the array is set to 1.
 */
void floor_button_event_handler();


/**
 * @brief Set the cab button requests for an @c Order
 * 
 * @param[out] p_queue  A pointer to the QUEUE
 * 
 * @warning If the first element of the QUEUE is not passed to this function, we might
 * encounter problems. This function also handles all the lights for the cab buttons.
 * 
 * @warning This function uses @c set_cab_button_lights() to set the cab button lights
 * The function updates the cab orders for the current Order 
 */
void cab_button_event_handler();


/**
 * @brief Set the floor button lights 
 * 
 * Set the lights on/off for each floor button, in accordance to the values 1/0
 * in @c ORDERS_UP and @c ORDERS_DOWN
 */
void set_floor_button_lights();

/**
 * @brief Set the cab button lights 
 * 
 * @param[in] p_order_up       A pointer to an array containing the states of the cab buttons
 * 
 * Set the lights on/off for each floor button, in accordance to the values 1/0 in @c ORDERS_CAB
 */
void set_cab_button_lights();

/**
 * @brief Set the floor indicator light
 * 
 * @param[in] last_floor    The last floor the elevator was at
 * 
 * Sets the floor light indicator to the last floor the elevator was on. The floor
 * indicator should still light for the last floor it visited, when it is between floors. 
 */
void set_floor_indicator_light(int last_floor);


#endif

