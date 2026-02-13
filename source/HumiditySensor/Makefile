# Compiler and Flags
CC      = wr-cc
CFLAGS  = -rtp -static -Iinclude
TARGET  = humiditysensor.vxe
SRC     = main.c monitor.c

TEST_CC = gcc
TEST_GCC = g++
TEST_CFLAGS = -I. -Iinclude
TEST_SRC = monitor_test.cpp
TEST_TARGET = runTests
LDFLAGS = -lgtest -lgtest_main -pthread
LCOV_FLAGS = --coverage
LCOV = lcov
GENHTML = genhtml
GENHTML_FLAGS = --output-directory coverage_report
GCOV_FLAGS = -n -o . *.c
GCOV = gcov

.PHONY: all clean

all: $(TARGET)

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) $(SRC) -o $(TARGET)

clean:
	rm -f $(TARGET) *.o *.gcda *.gcno runTests

test:
	$(TEST_CC) -DUNIT_TEST --coverage -c monitor.c $(TEST_CFLAGS)
	$(TEST_GCC) -DUNIT_TEST --coverage -c $(TEST_SRC) $(TEST_CFLAGS)
	$(TEST_GCC) --coverage *.o $(LDFLAGS) -o $(TEST_TARGET)
	./$(TEST_TARGET)

coverage:
	$(GCOV) $(GCOV_FLAGS)
	$(LCOV) --capture --directory . --output-file coverage.info
	$(LCOV) --remove coverage.info '/usr/*' --output-file coverage.info
	$(GENHTML) coverage.info $(GENHTML_FLAGS)