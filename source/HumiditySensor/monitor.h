/* monitor.h - header file for humidity sensor monitoring */
/* 
* Copyright (c) 2026 Trenser Technologies Ltd.
* 
* The right to copy, distribute, modify, or otherwise make use
* of this software may be licensed only pursuant to the terms
* of an applicable Trenser license agreement. 
*/ 

#ifndef __INCmonitorh_
#define __INCmonitorh_

/* includes */
#include <stdint.h>
#include <stdbool.h>

/* defines */
#define MONITOR_UPPER_THRESHOLD_LIMIT 	(75)
#define MONITOR_LOWER_THRESHOLD_LIMIT  	(10)
#define MONITOR_OPERATING_RANGE_MAX    	(105)
#define MONITOR_OPERATING_RANGE_MIN   	(2)

#define MONITOR_DEF_CLEAR              	(0U)
#define MONITOR_DATE_STR_MAX_LENGTH		(32U)
#define MONITOR_MESSAGE_MAX_LENGTH		(256U)
#define MONITOR_DATA_STR_MAX_LENGTH		(64U)
#define MONITOR_INDEX_ONE               (1U)
#define MAX_READ_COUNT                  (5U)
#define ONE_SECOND                      (1000U) /* in milliseconds */
#define TIME_DELAY                      (100U) /* in ticks */
#define CALIB_CONST                     (5U) /* Calibration constant for humidity sensor */

/* globals */

/* typedefs */
typedef enum
{
	NO_ERROR,
    ERROR_FAILED,
	ERROR_INVALID,
	ERROR_THRESHOLD_MIN,
	ERROR_THRESHOLD_MAX,
    ERROR_OUT_OF_BOUND,
}ERROR_TYPE;


typedef enum
{
	NORMAL_STATE,
	ERROR_STATE,
	SAFE_STATE,
}COMMON_STATE;

typedef struct
{
	uint32_t     commoniLowerThresholdRange;
	uint32_t     commoniUpperThresholdRange;
	uint32_t     commoniLowerOperatingRange;
	uint32_t     commoniUpperOperatingRange;

}COMMON_PRESSURE_CONFIG;

/* function declarations */
extern ERROR_TYPE monitorHumiditySensorData(int32_t *pHumditySensorVal);
extern ERROR_TYPE faultHandler(void);
extern ERROR_TYPE readHumiditySensorData(int32_t *pHumiditySensorVal);
extern ERROR_TYPE setWarningAlarm(ERROR_TYPE error_type_t, int32_t *pHumiditySensorVal);
extern ERROR_TYPE monitorHumiditySensorMonitorloop(void);

#ifdef UNIT_TEST
extern ERROR_TYPE (*readHumiditySensorDatamock)(int32_t *phumiditySensorVal);
#endif

#endif /* __INCmonitorh_ */