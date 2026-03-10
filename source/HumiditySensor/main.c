/* main.c - main function library */ 
/* 
* Copyright (c) 2026 Trenser Technologies Ltd. 
* 
* The right to copy, distribute, modify, or otherwise make use 
* of this software may be licensed only pursuant to the terms 
* of an applicable Trenser license agreement. 
*/

/*
DESCRIPTION
This library is main entry point for the application.
INCLUDE FILES: common.h
*/

/* includes */
#ifndef UNIT_TEST
#include <vxWorks.h>
#include <taskLib.h>
#endif
#include <stdio.h>
#include "monitor.h"

/* defines */

/* typedefs */

/* globals */

/* locals */


/* function definitions */

/*******************************************************************************
* main - main entry point
* 
* DESCRIPTION
* This function is the main entry point for the application.
* 
* PARAMETERS N/A
* 
* GLOBALS: 
* 
* RETURNS: 
* \is  
* \i <SUCCESS> 
* when there are no errors in reading configuration and processing data
* 
* \i <FAILURE> 
* if there is an error in reading configuration or processing data
* 
* ERRNO: N/A
* 
* \INTERNAL 
* This function uses the ONE_SECOND macro for sleep duration and FOREVER macro * for infinite loop condition.
*/
int main(void)
{

    while (1)
    {
        if (monitorHumiditySensorMonitorloop() != NO_ERROR)
        {
            printf("Error in monitoring humidity sensor data\n");
            return -1; // Return failure if there is an error in monitoring
        }
        else
        {
            /* No Process*/
        }
    }
    return 0;
}

/* end of file*/