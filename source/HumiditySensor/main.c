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
#include <vxWorks.h>
#include <taskLib.h>
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
        int32_t humiditySensorVal  = 0;
        ERROR_TYPE errorStatus     = NO_ERROR;

        errorStatus = readHumiditySensorData(&humiditySensorVal);

        if (errorStatus != NO_ERROR)
        {
            printf("Error in reading humidity sensor data\n");
        }
        else
        {
            errorStatus = monitorHumiditySensorData(&humiditySensorVal);
            if (errorStatus != ERROR_INVALID)
            {
                errorStatus = setWarningAlarm(errorStatus, &humiditySensorVal);
                if (errorStatus == ERROR_OUT_OF_BOUND)
                {
                    errorStatus = faultHandler();

                    if (errorStatus != NO_ERROR)
                    {
                        printf("Error in fault handler\n");
                    }
                    else
                    {
                        /* No Process*/
                    }
                }
                else if (errorStatus == ERROR_INVALID)
                {
                    printf("Error in setting warning alarm\n");
                }
                else
                {
                    /* No Process*/
                }
            }
            else
            {
                /* No Process*/
            }
        }
        
        taskDelay(TIME_DELAY); /* delay for 100 ticks */
    }

    return 0;
}

/* end of file*/