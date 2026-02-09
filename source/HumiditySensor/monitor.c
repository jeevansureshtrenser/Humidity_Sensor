/* monitor.c - source file for humidity sensor monitoring */
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
#include <stdlib.h>
#include "monitor.h"

/* defines */

/* typedefs */

/* globals */

/* locals */

/* function declarations */
extern ERROR_TYPE monitorHumiditySensorData(int32_t *pHumditySensorVal);
extern ERROR_TYPE faultHandler(void);
extern ERROR_TYPE readHumiditySensorData(int32_t *pHumiditySensorVal);
extern ERROR_TYPE setWarningAlarm(ERROR_TYPE error_type_t, int32_t *pHumiditySensorVal);

/* function definitions */

/*******************************************************************************
* readHumiditySensorData - read humdity sensor data from a mock function
* 
* DESCRIPTION
* This API will read the humidity sensor data from a mock function and store
* the read value to the pointer passed as an argument to this function. This
* function will return [NO_ERROR] when the humidity sensor data read successful.
*
* The function will return:
* 1.[ERROR_INVALID] when the pointer [phumiditySensorVal] is not a valid
* pointer.
* 
* PARAMETERS:
* <pHumditySensorVal> 
* - [out] pointer to the humidity sensor value to be stored.
*
* GLOBALS: N/A
* 
* RETURNS: 
* \is  
* \i <NO_ERROR> - data read successfully
* \i <ERROR_INVALID> - [pHumditySensorVal] is not a valid pointer.
* \ie
* 
* ERRNO: N/A
* 
* \INTERNAL 
*/
ERROR_TYPE readHumiditySensorData(int32_t *phumiditySensorVal)
{

    if (phumiditySensorVal == NULL)
    {
        return ERROR_INVALID;
    }
    else
    {
        /* Mock function to read humidity sensor data */
        *phumiditySensorVal = ((rand() % (MONITOR_OPERATING_RANGE_MAX - MONITOR_OPERATING_RANGE_MIN + 1)) + MONITOR_OPERATING_RANGE_MIN);
    }

    return NO_ERROR;
}

/*******************************************************************************
* monitorHumiditySensorData - To check the sensor data in the range of
* threshold and operating range.
* 
* DESCRIPTION
* This function is mainly for check the read humidity sensor data is in the
* range of user defined threshold ranges or in operating range. The function
* will return [NO_ERROR] when the read sensor value is in the range of user
* defined threshold.
*
* The function will return:
*
* 1.[ERROR_INVALID] when [pHumditySensorVal] is not a valid pointer
* 2.[ERROR_THRESHOLD_MAX] when sensor value [pHumditySensorVal] value is
* more than [MAX_THRESHOLD]
* 3.[ERROR_THRESHOLD_MIN] when sensor value [pHumditySensorVal] less
* than [MIN_THRESHOLD].
* 4.[ERROR_OUT_OF_BOUND] when sensor value [pHumditySensorVal] greater
* than [MAX_OPERATING_RANGE] or less than [MIN_OPERATING_RANGE].
* 
* PARAMETERS:
* <pHumditySensorVal> - pointer to the humidity sensor value to be checked.
*
* GLOBALS: N/A
* 
* RETURNS: 
* \is  
* \i <NO_ERROR> - read data in normal range.
* \i <ERROR_INVALID> - [pHumditySensorVal] is not a valid pointer.
* \i <ERROR_THRESHOLD_MAX> - [pHumditySensorVal] value more than
*    [MAX_THRESHOLD].
* \i <ERROR_THRESHOLD_MIN> - [pHumditySensorVal] less than [MIN_THRESHOLD].
* \i <ERROR_OUT_OF_BOUND> - [pHumditySensorVal] greater than
*    [MAX_OPERATING_RANGE] or less than [MIN_OPERATING_RANGE].
* \ie
* 
* ERRNO: N/A
* 
* \INTERNAL 
* This function uses the ONE_SECOND macro for sleep duration and FOREVER macro * for infinite loop condition.
*/
ERROR_TYPE monitorHumiditySensorData(int32_t *pHumditySensorVal)
{
    if (pHumditySensorVal == NULL)
    {
        return ERROR_INVALID;
    }
    else
    {
        /* No Process*/
    }

    if (*pHumditySensorVal > MONITOR_OPERATING_RANGE_MAX ||
        *pHumditySensorVal < MONITOR_OPERATING_RANGE_MIN)
    {
        return ERROR_OUT_OF_BOUND;
    }
    else if( *pHumditySensorVal < MONITOR_LOWER_THRESHOLD_LIMIT)
    {
        return ERROR_THRESHOLD_MIN;
    }
    else if( *pHumditySensorVal > MONITOR_UPPER_THRESHOLD_LIMIT)
    {
        return ERROR_THRESHOLD_MAX;
    }
    else
    {
        /* No Process*/
    }

    return NO_ERROR;
}

/*******************************************************************************
* setwarningAlarm - To print the warning message base on the error.
* 
* DESCRIPTION
* This function will print the warning message based on the argument passed on
* to the function. There will be two argument for this function one will
* by ERROR_TYPE and other will be humidity Sensor value. The message consist of
* timestamp, type of message, temperature and error message.
*
* This function will print the following:

* 1. "Normal" when the [error_type_t] is [NO_ERROR].
* 2. "Upper threshold" when the [error_type_t] is [ERROR_THRESHOLD_MAX].
* 3. "Lower threshold" when the [error_type_t] is [ERROR_THRESHOLD_MIN].
* 4. "sensor data out of bound" when the [error_type_t] is [ERROR_OUT_OF_BOUND].
*
* This function will return:
*
* 1. [NO_ERROR] when the [pHumiditySensorVal] is a valid pointer and
* [error_type_t] is valid value.
* 2. [ERROR_INVALID] when the [pHumiditySensorVal] is not a valid pointer and
* [error_type_t] is not a valid value.
* 
* PARAMETERS:
* <error_type_t>
* - [in] error type to print the warning message.
* <pHumditySensorVal> 
* - [in] pointer to the humidity sensor value to be stored.
*
* GLOBALS: N/A
* 
* RETURNS: 
* \is  
* \i <NO_ERROR> - data read successfully
* \i <ERROR_INVALID> - [pHumditySensorVal] is not a valid pointer.
* \ie
* 
* ERRNO: N/A
* 
* \INTERNAL 
*/
ERROR_TYPE setWarningAlarm(ERROR_TYPE error_type_t, int32_t *pHumiditySensorVal)
{
    ERROR_TYPE errorStatus = NO_ERROR;

    if (pHumiditySensorVal == NULL)
    {
        return ERROR_INVALID;
    }
    else
    {
        switch (error_type_t)
        {
            case NO_ERROR:
                /* No Process*/
                printf("| Info    | %3d | Normal                |\n", *pHumiditySensorVal);
                break;
            case ERROR_THRESHOLD_MIN:
                printf("| Warning | %3d | Lower Threshold       |\n",*pHumiditySensorVal);
                break;
            case ERROR_THRESHOLD_MAX:
                printf("| Warning | %3d | Upper Threshold       |\n",*pHumiditySensorVal);
                break;
            case ERROR_OUT_OF_BOUND:
                printf("| ERROR   | %3d | Sensor Out Of Bound   |\n",*pHumiditySensorVal);
                break;
            default:
                errorStatus = ERROR_INVALID;
                break;
        }

    }

    return errorStatus;
}

/*******************************************************************************
* faultHandler - mainly for error handling when read value exceed the threshold * or out of bound.
* 
* DESCRIPTION

* This function is mainly for fault handling. If the humidity sensor data
* exceed the operating range there will be fault happens in the sensor. This 
* API will call during this condition. This API will read the humidity sensor
* data and again check the data is in the Operating range, continue for 
* [MAX_READ_COUNT] in a time interval of one second for each checking.
*
* This function will return:
* 1. [NO_ERROR] when the sensor data is in the range of [MIN_OPERATING_RANGE] 
* and [MAX_OPERATING_RANGE] range.
* 2. [ERROR_INVALID] when the sensor data less than [MIN_OPERATING_RANGE] or 
* greater than [MAX_OPERATING_RANGE] after read the sensor value
* [MAX_READ_COUNT] times.
*
* PARAMETERS:
* <pHumditySensorVal> 
* - [out] pointer to the humidity sensor value to be stored.
*
* GLOBALS: N/A
* 
* RETURNS: 
* \is  
* \i <NO_ERROR> - If humidity sensor data in the range of [MIN_OPERATING_RANGE] * and [MAX_OPERATING_RANGE]
* \i <ERROR_INVALID> - If humidity sensor data out of [MIN_OPERATING_RANGE] and * [MAX_OPERATING_RANGE] range
* \ie
* 
* ERRNO: N/A
* 
* \INTERNAL 
*/
ERROR_TYPE faultHandler(void)
{
    uint32_t uiCount = 0;
    int32_t iHumidtySensorVal = 0;
    ERROR_TYPE errorStatus = NO_ERROR;

    while (uiCount < MAX_READ_COUNT)
    {
        errorStatus = readHumiditySensorData(&iHumidtySensorVal);
        if (errorStatus != NO_ERROR)
        {
            return errorStatus;
        }

        if (iHumidtySensorVal >= MONITOR_LOWER_THRESHOLD_LIMIT && iHumidtySensorVal <= MONITOR_OPERATING_RANGE_MAX)
        {
            return NO_ERROR;
        }

        uiCount++;
        taskDelay(ONE_SECOND); /* delay for one second */
    }

    return ERROR_INVALID;
}

/* end of file*/