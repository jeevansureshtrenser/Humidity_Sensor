#include <gtest/gtest.h>
extern "C" {
    #include "../../source/HumiditySensor/monitor.h"
}

TEST(ReadHumidityTest, Nullcheck) 
{
    int32_t *pHumiditySensorVal = nullptr; 
    EXPECT_EQ(readHumiditySensorData(pHumiditySensorVal), ERROR_INVALID); 
}

TEST(ReadHumidityTest, ValidData) 
{ 
    int32_t humidityValue = 50; 
    // Simulate a valid humidity value 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(readHumiditySensorData(pHumiditySensorVal), NO_ERROR);
}

TEST(SetWarningAlarmTest, Nullcheck) 
{
    int32_t *pHumiditySensorVal = nullptr; 
    EXPECT_EQ(setWarningAlarm(ERROR_THRESHOLD_MIN, pHumiditySensorVal), ERROR_INVALID); 
}

TEST(SetWarningAlarmTest, ValidData) 
{ 
    int32_t humidityValue = MONITOR_LOWER_THRESHOLD_LIMIT - 1; 
    // Simulate a valid humidity value 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(setWarningAlarm(ERROR_THRESHOLD_MIN, pHumiditySensorVal), NO_ERROR);
}

TEST(SetWarningAlarmTest, InvalidErrorType) 
{ 
    int32_t humidityValue = 50; 
    // Simulate a valid humidity value 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(setWarningAlarm(static_cast<ERROR_TYPE>(999), pHumiditySensorVal), ERROR_INVALID); 
}

TEST(SetWarningAlarmTest, ValidErrorType) 
{ 
    int32_t humidityValue = 50; 
    // Simulate a valid humidity value 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(setWarningAlarm(ERROR_THRESHOLD_MAX, pHumiditySensorVal), NO_ERROR); 
}

TEST(SetWarningAlarmTest, ThresholdMin) 
{ 
    int32_t humidityValue = MONITOR_LOWER_THRESHOLD_LIMIT - 1; 
    // Simulate a value below the lower threshold 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(setWarningAlarm(ERROR_THRESHOLD_MIN, pHumiditySensorVal), NO_ERROR); 
}

TEST(SetWarningAlarmTest, UpperOutOfBound) 
{ 
    int32_t humidityValue = MONITOR_OPERATING_RANGE_MAX + 1; // Simulate an out-of-bound humidity value 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(setWarningAlarm(ERROR_OUT_OF_BOUND, pHumiditySensorVal), NO_ERROR); 
}

TEST(SetWarningAlarmTest, LowerOutOfBound) 
{ 
    int32_t humidityValue = MONITOR_OPERATING_RANGE_MIN - 1; // Simulate an out-of-bound humidity value 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(setWarningAlarm(ERROR_OUT_OF_BOUND, pHumiditySensorVal), NO_ERROR); 
}

TEST(FaultHandlerTest, ValidData) 
{ 
    EXPECT_EQ(faultHandler(), NO_ERROR);
}

TEST(MonitorHumiditySensorDataTest, ValidData) 
{ 
    int32_t humidityValue = MONITOR_UPPER_THRESHOLD_LIMIT - 1; 
    // Simulate a valid humidity value 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(monitorHumiditySensorData(pHumiditySensorVal), NO_ERROR);
}

TEST(MonitorHumiditySensorDataTest, Nullcheck) 
{
    int32_t *pHumiditySensorVal = nullptr; 
    EXPECT_EQ(monitorHumiditySensorData(pHumiditySensorVal), ERROR_INVALID); 
}

TEST(MonitorHumiditySensorDataTest, UpperOutOfBound) 
{ 
    int32_t humidityValue = MONITOR_OPERATING_RANGE_MAX + 1; // Simulate an out-of-bound humidity value 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(monitorHumiditySensorData(pHumiditySensorVal), ERROR_OUT_OF_BOUND);
}

TEST(MonitorHumiditySensorDataTest, LowerOutOfBound) 
{ 
    int32_t humidityValue = MONITOR_OPERATING_RANGE_MIN - 1; // Simulate an out-of-bound humidity value 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(monitorHumiditySensorData(pHumiditySensorVal), ERROR_OUT_OF_BOUND);
}

TEST(MonitorHumiditySensorDataTest, ThresholdMin) 
{ 
    int32_t humidityValue = MONITOR_LOWER_THRESHOLD_LIMIT - 1; // Simulate a value below the lower threshold 
    int32_t *pHumiditySensorVal = &humidityValue;
    EXPECT_EQ(monitorHumiditySensorData(pHumiditySensorVal), ERROR_THRESHOLD_MIN);
}

TEST(MonitorHumiditySensorDataTest, ThresholdMax) 
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