#ifndef _MOCK_MONITOR_H_
#define _MOCK_MONITOR_H_
#include "../../source/HumiditySensor/monitor.h"

extern int32_t g_iMockHumidityValue;
extern ERROR_TYPE g_errorTypeForMock;
extern int32_t g_iMockReadCount;

extern void setUpMockHumidityValue(int32_t value);
extern void setErrorTypeForMock(ERROR_TYPE errorType);
extern void setErrorReadCountForMock(uint32_t count);
extern ERROR_TYPE mockreadHumiditySensorData(int32_t *phumiditySensorVal);

#endif /* _MOCK_MONITOR_H_ */