/* mock_monitor.c - mock function library */ 
/* 
* Copyright (c) 2026 Trenser Technologies Ltd. 
* 
* The right to copy, distribute, modify, or otherwise make use 
* of this software may be licensed only pursuant to the terms 
* of an applicable Trenser license agreement. 
*/

/* includes */
#include "mock_monitor.h"
#include "../../source/HumiditySensor/monitor.h"
#include <stdio.h>

/* defines */

/* typedefs */

/* globals */

/* locals */
int32_t g_iMockHumidityValue = 0; // Default mock humidity value for testing
ERROR_TYPE g_errorTypeForMock = NO_ERROR; // Default error type for mock function
int32_t g_iMockReadCount = 0; // Default read count for mock function

/* function declarations */
void setUpMockHumidityValue(int32_t value);
void setErrorTypeForMock(ERROR_TYPE errorType);
void setErrorReadCountForMock(uint32_t count);
ERROR_TYPE mockreadHumiditySensorData(int32_t *phumiditySensorVal);

/* function definitions */

void setUpMockHumidityValue(int32_t value)
{
    g_iMockHumidityValue = value;
}

void setErrorTypeForMock(ERROR_TYPE errorType)
{
    g_errorTypeForMock = errorType;
}

void setErrorReadCountForMock(uint32_t count)
{
    /* This function can be implemented to set a specific read count for the mock function if needed */
    g_iMockReadCount = count;
}

ERROR_TYPE mockreadHumiditySensorData(int32_t *phumiditySensorVal)
{

    if (phumiditySensorVal == NULL)
    {
        return ERROR_INVALID;
    }
    else
    {
        if(g_iMockReadCount > 0)
        {
            *phumiditySensorVal = MONITOR_OPERATING_RANGE_MAX + 1; // Simulate an out-of-bound value
            g_iMockReadCount--;
            return NO_ERROR; // Return error after decrementing read count
        }
        else
        {
            /* Mock function to read humidity sensor data */
            *phumiditySensorVal = g_iMockHumidityValue;
        }
    }
    return g_errorTypeForMock;
}