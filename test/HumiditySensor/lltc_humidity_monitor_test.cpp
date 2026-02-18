#include <gtest/gtest.h>
extern "C" {
    #include "../../source/HumiditySensor/monitor.h"
    #include "mock_monitor.h"
}


TEST(SetWarningAlarm_LLTC_1, SetWarningAlarm_LLTC_MAX_THRESHOLD) 
{ 
    int32_t humidityValue = MONITOR_UPPER_THRESHOLD_LIMIT + 1;
    // Simulate a valid humidity value 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(setWarningAlarm(ERROR_THRESHOLD_MAX, pHumiditySensorVal), NO_ERROR);
}

TEST(SetWarningAlarm_LLTC_2, SetWarningAlarm_LLTC_MIN_THRESHOLD) 
{ 
    int32_t humidityValue = MONITOR_LOWER_THRESHOLD_LIMIT - 1; 
    // Simulate a valid humidity value 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(setWarningAlarm(ERROR_THRESHOLD_MIN, pHumiditySensorVal), NO_ERROR); 
}
TEST(SetWarningAlarm_LLTC_1, SetWarningAlarm_LLTC_OUT_OF_BOUND) 
{ 
    int32_t humidityValue = MONITOR_OPERATING_RANGE_MAX + 1;
    // Simulate a valid humidity value 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(setWarningAlarm(ERROR_OUT_OF_BOUND, pHumiditySensorVal), NO_ERROR);
}

TEST(SetWarningAlarm_LLTC_2, SetWarningAlarm_LLTC_MAX_THRESHOLD) 
{ 
    int32_t humidityValue = MONITOR_OPERATING_RANGE_MIN - 1; 
    // Simulate a valid humidity value 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(setWarningAlarm(ERROR_OUT_OF_BOUND, pHumiditySensorVal), NO_ERROR); 
}

TEST(MonitorHumiditySensorData_LLTC_3, MonitorHumiditySensorData_UpperOutOfBound) 
{ 
    int32_t humidityValue = MONITOR_OPERATING_RANGE_MAX + 1; // Simulate an out-of-bound humidity value 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(monitorHumiditySensorData(pHumiditySensorVal), ERROR_OUT_OF_BOUND);
}

TEST(MonitorHumiditySensorData_LLTC_4, MonitorHumiditySensorData_LowerOutOfBound) 
{ 
    int32_t humidityValue = MONITOR_OPERATING_RANGE_MIN - 1; // Simulate an out-of-bound humidity value 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(monitorHumiditySensorData(pHumiditySensorVal), ERROR_OUT_OF_BOUND);
}

TEST(MonitorHumiditySensorData_LLTC_5, MonitorHumiditySensorData_ThresholdMin) 
{ 
    int32_t humidityValue = MONITOR_LOWER_THRESHOLD_LIMIT - 1; // Simulate a value below the lower threshold 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(monitorHumiditySensorData(pHumiditySensorVal), ERROR_THRESHOLD_MIN);
}

TEST(MonitorHumiditySensorData_LLTC_6, MonitorHumiditySensorData_ThresholdMax) 
{ 
    int32_t humidityValue = MONITOR_UPPER_THRESHOLD_LIMIT + 1; // Simulate a value above the upper threshold 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(monitorHumiditySensorData(pHumiditySensorVal), ERROR_THRESHOLD_MAX);
}

TEST(MonitorHumiditySensorData_LLTC_7, MonitorHumiditySensorData_INT32_MAX) 
{ 
    int32_t humidityValue = INT32_MAX; // Simulate a value above the upper threshold 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(monitorHumiditySensorData(pHumiditySensorVal), ERROR_OUT_OF_BOUND);
}

TEST(MonitorHumiditySensorData_LLTC_8, MonitorHumiditySensorData_INT32_MIN) 
{ 
    int32_t humidityValue = INT32_MIN; // Simulate a value below the lower threshold 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(monitorHumiditySensorData(pHumiditySensorVal), ERROR_OUT_OF_BOUND);
}

TEST(MonitorHumiditySensorData_LLTC_9, MonitorHumiditySensorData_INT32_MAX_OVERFLOW) 
{ 
    int32_t humidityValue = INT32_MAX + 1; // Simulate a value above the upper threshold 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(monitorHumiditySensorData(pHumiditySensorVal), ERROR_OUT_OF_BOUND);
}

TEST(MonitorHumiditySensorData_LLTC_10, MonitorHumiditySensorData_INT32_MIN_UNDERFLOW) 
{ 
    int32_t humidityValue = INT32_MIN - 1; // Simulate a value below the lower threshold 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(monitorHumiditySensorData(pHumiditySensorVal), ERROR_OUT_OF_BOUND);
}

TEST(FaultHandler_LLTC_1, FaultHandler_LLTC_NO_ERROR) 
{ 
    int32_t iReadCount = 0;

    setErrorTypeForMock(NO_ERROR); // Set mock error type to ERROR_INVALID

    iReadCount = MAX_READ_COUNT/2;
    setErrorReadCountForMock(iReadCount); // Set mock read count to simulate error for a specific number of reads

    setUpMockHumidityValue(MONITOR_LOWER_THRESHOLD_LIMIT + 1); // Simulate a value below the lower threshold

    readHumiditySensorDatamock = mockreadHumiditySensorData;
    // value below the lower threshold
    EXPECT_EQ(faultHandler(), NO_ERROR);

    readHumiditySensorDatamock = readHumiditySensorData;
    g_iMockReadCount = 0; // Reset read count after test
    g_errorTypeForMock = NO_ERROR; // Reset error type after test
    g_iMockHumidityValue = 0; // Reset mock humidity value after test
}

TEST(FaultHandler_LLTC_1, FaultHandler_LLTC_Error_Failed) 
{ 
    int32_t iReadCount = 0;

    setErrorTypeForMock(NO_ERROR); // Set mock error type to ERROR_INVALID

    iReadCount = MAX_READ_COUNT;
    setErrorReadCountForMock(iReadCount); // Set mock read count to simulate error for a specific number of reads

    readHumiditySensorDatamock = mockreadHumiditySensorData;
    // value below the lower threshold
    EXPECT_EQ(faultHandler(), ERROR_FAILED);

    readHumiditySensorDatamock = readHumiditySensorData;
    g_iMockReadCount = 0; // Reset read count after test
    g_errorTypeForMock = NO_ERROR; // Reset error type after test
    g_iMockHumidityValue = 0; // Reset mock humidity value after test
}

TEST(FaultHandler_LLTC_2, FaultHandler_LLTC_INTMAX) 
{
    setUpMockHumidityValue(INT32_MAX); // Simulate a value at INT32_MAX
    setErrorTypeForMock(NO_ERROR); // Set mock error type to NO_ERROR
    setErrorReadCountForMock(MAX_READ_COUNT); // Set mock read count to simulate error for a specific number of reads
    readHumiditySensorDatamock = mockreadHumiditySensorData;
    EXPECT_EQ(faultHandler(), ERROR_FAILED);
    readHumiditySensorDatamock = readHumiditySensorData;
    g_errorTypeForMock = NO_ERROR; // Reset error type after test
    g_iMockHumidityValue = 0; // Reset mock humidity value after test
    g_iMockReadCount = 0; // Reset read count after test

}

TEST(FaultHandler_LLTC_2, FaultHandler_LLTC_INTMIN) 
{
    setUpMockHumidityValue(INT32_MIN); // Simulate a value at INT32_MIN
    setErrorTypeForMock(NO_ERROR); // Set mock error type to NO_ERROR
    setErrorReadCountForMock(MAX_READ_COUNT); // Set mock read count to simulate error for a specific number of reads
    readHumiditySensorDatamock = mockreadHumiditySensorData;
    EXPECT_EQ(faultHandler(), ERROR_FAILED);
    readHumiditySensorDatamock = readHumiditySensorData;
    g_errorTypeForMock = NO_ERROR; // Reset error type after test
    g_iMockHumidityValue = 0; // Reset mock humidity value after test
    g_iMockReadCount = 0; // Reset read count after test

}




