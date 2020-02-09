/**
* @file
* @brief Important includes and definitions that all files require
*/
#ifndef INCLUDES_H
#define INCLUDES_H

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "driver/hardware.h"

#define MAX_FLOOR 4
#define MIN_FLOOR 1

/** 
 * Size of the queue. 512 elements to better suit the CPU
*/
#define QUEUE_SIZE 512

/** 
 * Normal wait-time, in seconds, for the elevator.
 * Will be used everytime after obstruction and stop 
*/
#define NORMAL_WAIT_TIME 3

/** 
 * Enum of the different commands the elevator must handle. 
*/
typedef enum{
    CMD_STOP,
    CMD_TIMER_START,
    CMD_OPEN_DOOR,
    CMD_SET_FLOOR_LIGHT,
    CMD_SET_CAB_LIGHT,
    CMD_ELEVATOR_UP,
    CMD_ELEVATOR_DOWN,
    CMD_ELEVATOR_STOP,
    CMD_NO_ACTION
} CmdType_t;


#endif