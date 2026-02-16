cmake_minimum_required(VERSION 3.10)
project(HUMIDITYSENSOR C CXX)

set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD 17)

# Coverage flags
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} --coverage -O0 -g")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -O0 -g")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage")

# Redirect all outputs to the local gtest directory
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/gtest)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/gtest)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/gtest)

include_directories(include)

enable_testing()
find_package(GTest REQUIRED)

add_executable(runTests
    monitor_test.cpp
    ../../source/HumiditySensor/monitor.c
)

target_include_directories(runTests PRIVATE include)
target_link_libraries(runTests GTest::GTest GTest::Main pthread)

add_test(NAME HumiditySensor COMMAND runTests)

# Coverage target
find_program(LCOV_PATH lcov)
find_program(GENHTML_PATH genhtml)

add_custom_target(coverage
    COMMAND ${CMAKE_CTEST_COMMAND} --output-on-failure
    COMMAND ${LCOV_PATH} --capture --directory ${CMAKE_BINARY_DIR} --output-file coverage.info --ignore-errors mismatch
    COMMAND ${LCOV_PATH} --remove coverage.info '/usr/*' '*/test/*' --output-file coverage.info --ignore-errors mismatch
    COMMAND ${GENHTML_PATH} coverage.info --output-directory coverage-report
    WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/gtest
    COMMENT "Running tests and generating coverage report"
)

add_custom_target(clean_coverage
    COMMAND ${CMAKE_COMMAND} -E remove -f coverage.info
    COMMAND ${CMAKE_COMMAND} -E remove_directory coverage-report
    COMMENT "Cleaning coverage files and report"
)
