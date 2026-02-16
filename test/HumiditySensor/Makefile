CC       = gcc
CXX      = g++
CXXFLAGS = -lgtest -lgtest_main -pthread -fprofile-arcs -ftest-coverage
CFLAGS   = -DUNIT_TEST --coverage -Iinclude -I.
LDFLAGS += -fprofile-arcs -ftest-coverage

TESTSRC  = hlr_monitor_test.cpp
TESTOBJ  = monitor.o
OUTDIR   = gtest
TARGET   = $(OUTDIR)/runTests

.PHONY: all clean

# Compile C sources into OUTDIR
$(OUTDIR)/%.o: ../../source/HumiditySensor/%.c 
	mkdir -p $(OUTDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C++ test source into OUTDIR
$(OUTDIR)/%.o: %.cpp
	mkdir -p $(OUTDIR)
	$(CXX) $(CFLAGS) -c $< -o $@

all: $(addprefix $(OUTDIR)/,$(TESTOBJ)) $(OUTDIR)/hlr_monitor_test.o
	$(CXX) --coverage $^ $(CXXFLAGS) -o $(TARGET)
	./$(TARGET)
	gcov -o $(OUTDIR) ../../source/HumiditySensor/*.c -n
	lcov --capture --directory $(OUTDIR) --output-file $(OUTDIR)/coverage.info --ignore-errors mismatch
	lcov --remove $(OUTDIR)/coverage.info '/usr/*' --output-file $(OUTDIR)/coverage.info --ignore-errors mismatch
	genhtml $(OUTDIR)/coverage.info --output-directory $(OUTDIR)/output

	@echo "Test execution and coverage report generation complete. Check $(OUTDIR)/output/index.html for details."

clean:
	rm -rf $(OUTDIR)
