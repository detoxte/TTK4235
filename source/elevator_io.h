/**
* @file
* @brief IO library for elevator, spanning set/get-functions for buttons and lights
*/
#ifndef ELEVATOR_IO_H
#define ELEVATOR_IO_H


/**
 * @brief Updates the a floor value to a valid floor
 * 
 * @param[in] floor     The last valid floor
 * 
 * @return A new valid floor if the elevator is at a valid floor, and @p valid_floor if the
 * elevator is between floors.
 * 
 * @warning Correct usage of this function requires @p valid_floor to actually be a valid floor. 
 */
int update_valid_floor(int valid_floor);


/**
 * @brief Set the floor indicator light
 * 
 * @param[in] floor    The floor whos indicator we would like to set  
 * 
 * The lights will only be set, if the elevator is at a defined floor. Therefore,
 * the light will not be changed when the elevator is between floors.
 */
void set_floor_indicator_light(int floor);


/**
 * @brief Find what floor the elevator is at
 * 
 * @return -1 if the elevator is between floors, and an int corresponding to the current floor
 * if the elevator is at a floor
 * 
 * @warning Because the elevator hardware's floors are indexed at 0, a non-truthy value (0) will
 * be returned when the elevator is at the first floor
 */
int get_current_floor();


/**
 * @brief Polls the cab buttons, and updates the cab orders for the current input
 * 
 * @param[in, out] p_orders_cab      A pointer to an array of the cab-button states
 */
void update_cab_buttons(int* p_orders_cab);


/**
 * @brief Updates the floor buttons based on current input
 * 
 * @param[in, out] p_orders_up      A pointer to an array of the up-button states
 * @param[in, out] p_orders_down    A pointer to an array of the down-button states
 * 
 * @warning This function operates on the assumption that @p p_orders_up and @p p_orders_down are 
 * set with 0's and 1's, respectively for "button not clicked" and "button clicked"
 * 
 * @warning This function also uses @c hardware_command_order_light() to set the button lights
 * 
 * The function checks every external elevator button, from the first floor to the last floor.
 * Upon finding a button that is clicked, that has not already been clicked ( by checking
 * the @p p_orders_up and @p p_orders_down arrays), the corresponding value in the array is set to 1.
 */
void update_floor_buttons(int* p_orders_up, int* p_orders_down);


#endif //ELEVATOR_IO_H