#include <gtest/gtest.h>
extern "C" {
    #include "../../source/HumiditySensor/monitor.h"
    #include "mock_monitor.h"
}

TEST(ReadHumidity_HLTC_1, ReadHumidity_HLTC_Nullcheck) 
{
    int32_t *pHumiditySensorVal = nullptr;
    EXPECT_EQ(readHumiditySensorData(pHumiditySensorVal), ERROR_INVALID);
}

TEST(ReadHumidity_HLTC_2, ReadHumidity_HLTC_ValidData) 
{
    int32_t humidityValue = 0;
    // Simulate a valid humidity value
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(readHumiditySensorData(pHumiditySensorVal), NO_ERROR);
}

TEST(SetWarningAlarm_HLTC_1, SetWarningAlarm_HLTC_Nullcheck)
{
    int32_t *pHumiditySensorVal = nullptr;
    EXPECT_EQ(setWarningAlarm(ERROR_THRESHOLD_MIN, pHumiditySensorVal),ERROR_INVALID);
}

TEST(SetWarningAlarm_HLTC_2, SetWarningAlarm_HLTC_ValidData) 
{ 
    int32_t humidityValue = MONITOR_LOWER_THRESHOLD_LIMIT + 1;
    // Simulate a valid humidity value 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(setWarningAlarm(NO_ERROR, pHumiditySensorVal), NO_ERROR);
}

TEST(SetWarningAlarm_HLTC_3, SetWarningAlarm_HLTC_InvalidErrorType) 
{ 
    int32_t humidityValue = 0; 
    // Simulate a valid humidity value 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(setWarningAlarm(static_cast<ERROR_TYPE>(999), pHumiditySensorVal), ERROR_INVALID); 
}

TEST(FaultHandler_HLTC_1, FaultHandler_HLTC_ValidData) 
{ 
    EXPECT_EQ(faultHandler(), NO_ERROR);
}

TEST(FaultHandler_HLTC_3, FaultHandler_HLTC_Error_Failed) 
{ 
    setErrorTypeForMock(ERROR_FAILED); // Set mock error type to NO_ERROR
    readHumiditySensorDatamock = mockreadHumiditySensorData;
    EXPECT_EQ(faultHandler(), ERROR_INVALID);
    readHumiditySensorDatamock = readHumiditySensorData;
    g_errorTypeForMock = NO_ERROR; // Reset error type after test
    g_iMockHumidityValue = 0; // Reset mock humidity value after test
    g_iMockReadCount = 0; // Reset read count after test
}

TEST(FaultHandler_HLTC_2, FaultHandler_HLTC_Error_invalid) 
{ 
    setErrorTypeForMock(ERROR_INVALID); // Set mock error type to NO_ERROR
    readHumiditySensorDatamock = mockreadHumiditySensorData;
    EXPECT_EQ(faultHandler(), ERROR_INVALID);
    readHumiditySensorDatamock = readHumiditySensorData;
    g_errorTypeForMock = NO_ERROR; // Reset error type after test
    g_iMockHumidityValue = 0; // Reset mock humidity value after test
    g_iMockReadCount = 0; // Reset read count after test
}


TEST(MonitorHumiditySensorData_HLTC_1, ValidData) 
{ 
    int32_t humidityValue = MONITOR_UPPER_THRESHOLD_LIMIT - 1; 
    // Simulate a valid humidity value 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(monitorHumiditySensorData(pHumiditySensorVal), NO_ERROR);
}

TEST(MonitorHumiditySensorData_HLTC_2, Nullcheck) 
{
    int32_t *pHumiditySensorVal = nullptr; 
    EXPECT_EQ(monitorHumiditySensorData(pHumiditySensorVal), ERROR_INVALID); 
}

TEST(MonitorHumiditySensorData_HLTC_3, UpperOutOfBound) 
{ 
    int32_t humidityValue = MONITOR_OPERATING_RANGE_MAX + 1; // Simulate an out-of-bound humidity value 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(monitorHumiditySensorData(pHumiditySensorVal), ERROR_OUT_OF_BOUND);
}

TEST(MonitorHumiditySensorData_HLTC_4, LowerOutOfBound) 
{ 
    int32_t humidityValue = MONITOR_OPERATING_RANGE_MIN - 1; // Simulate an out-of-bound humidity value 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(monitorHumiditySensorData(pHumiditySensorVal), ERROR_OUT_OF_BOUND);
}

TEST(MonitorHumiditySensorData_HLTC_5, ThresholdMin) 
{ 
    int32_t humidityValue = MONITOR_LOWER_THRESHOLD_LIMIT - 1; // Simulate a value below the lower threshold 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(monitorHumiditySensorData(pHumiditySensorVal), ERROR_THRESHOLD_MIN);
}

TEST(MonitorHumiditySensorData_HLTC_6, ThresholdMax) 
{ 
    int32_t humidityValue = MONITOR_UPPER_THRESHOLD_LIMIT + 1; // Simulate a value above the upper threshold 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(monitorHumiditySensorData(pHumiditySensorVal), ERROR_THRESHOLD_MAX);
}

int main(int argc, char **argv) 
{ 
    ::testing::InitGoogleTest(&argc, argv); 
    return RUN_ALL_TESTS(); 
}