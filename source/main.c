/**
 * @file
 * @brief main linker point of elevator program
 */

#include "timer.h"
#include "queue.h"
#include "elevator_fsm.h"


// Antar:

    // At cab-knappene kun kan trykkes inn med "Folk" i heisen



int elevator_init() {
    hardware_command_door_open(0);
    
    if(!at_floor()) {
        hardware_command_movement(HARDWARE_MOVEMENT_DOWN);
    }
    
    return 0;
}


int main(){

    // ELEVATOR INITIAL SETUP
    Order queue[QUEUE_SIZE];

    int current_floor = -1; //invalid floor to set the elevator's intitial floor-value
    
    int door_open = DOOR_CLOSED;
    int next_action  = -1;
    time_t* stop_timer;
    time_t* door_timer;
    start_timer(stop_timer);
    start_timer(door_timer);

    elevator_state_t elevator_state = STATE_IDLE;
    
    int error = hardware_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize hardware\n");
        exit(1);
    }

    error = elevator_init();
    if(error != 0){
        fprintf(stderr, "Unable to initialize software\n");
        exit(1);
    }


    // ELEVATOR PROGRAM LOOP
    // If we made new commands for set/get, we can set/get multiple connected things at once
    // ex: elevator_open_doors() can both open/close the door, and also set the lamp
    while(1){

        // Can be part of update_state and next action!!!
        if(hardware_read_stop_signal()) {
            hardware_command_stop_light(LIGHT_ON);
            elevator_state = STATE_IDLE;
            erase_queue();
            if(at_floor()){
                hardware_command_door_open(DOOR_OPEN);
                door_open = DOOR_OPEN;
            }
            start_timer(stop_timer);
        }
        else{
            hardware_command_stop_light(LIGHT_OFF);
            if(check_timer(stop_timer) && door_open == DOOR_OPEN){
                door_open = DOOR_CLOSED;
                hardware_command_door_open(DOOR_CLOSED);
            }
        }

        if(hardware_read_obstruction_signal() && door_open == DOOR_OPEN) {
            start_timer(door_timer);
        }
        else if(!hardware_read_obstruction_signal() && door_open == DOOR_OPEN){
            if(check_timer(door_timer)){
                door_open = DOOR_CLOSED;
                hardware_command_door_open(DOOR_CLOSED);
                //skal nå transisere til neste state
                //denne staten er da avhengig av køen av elementer
            }
        }
    
        poll_floor_buttons();
    
        update_floor_lights(current_floor);

        // update next_action in each case
        // After finishing one order, set the elevator back to idle.
        Order current_order = queue[0];
        next_action = update_state(elevator_state);

        switch(next_action) {
            case START_DOOR_TIMER:
                start_timer(door_timer);
                break;
                
        }

    }
}
