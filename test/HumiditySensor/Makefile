CC       = gcc
CXX      = g++
CXXFLAGS = -lgtest -lgtest_main -pthread -fprofile-arcs -ftest-coverage
CFLAGS   = -DUNIT_TEST --coverage -Iinclude -I.
LDFLAGS += -fprofile-arcs -ftest-coverage

TESTSRC  = hltc_humidity_monitor_test.cpp lltc_humidity_monitor_test.cpp mock_monitor.c
TESTOBJ  = monitor.o
OUTDIR   = gtest
TARGET   = $(OUTDIR)/runTests
COV_DIR  = coverage

.PHONY: all clean

# Compile C sources into OUTDIR
$(OUTDIR)/%.o: ../../source/HumiditySensor/%.c
	@echo "Compile C sources into $(OUTDIR)"
	@mkdir -p $(OUTDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Compile C++ test source into OUTDIR
$(OUTDIR)/%.o: %.cpp
	@mkdir -p $(OUTDIR)
	@echo "Compile C++ test source into $(OUTDIR)"
	$(CXX) $(CFLAGS) -c $< -o $@

# Compile C++ test source into OUTDIR
$(OUTDIR)/%.o: %.c
	@mkdir -p $(OUTDIR)
	@echo "Compile C test source into $(OUTDIR)"
	$(CC) $(CFLAGS) -c $< -o $@

all: $(addprefix $(OUTDIR)/,$(TESTOBJ)) $(OUTDIR)/hltc_humidity_monitor_test.o $(OUTDIR)/lltc_humidity_monitor_test.o $(OUTDIR)/mock_monitor.o
	$(CXX) --coverage $^ $(CXXFLAGS) -o $(TARGET)
	@echo "Run test target $(TARGET)"
	./$(TARGET)
	@echo ">>> Generating coverage..."
	mkdir -p $(COV_DIR)
	gcov -o $(OUTDIR) $(TESTSRC) -n
	lcov --capture --directory $(OUTDIR) --output-file $(COV_DIR)/coverage.info --ignore-errors mismatch
	lcov --remove $(COV_DIR)/coverage.info '/usr/*' --output-file $(COV_DIR)/coverage.info
	genhtml $(COV_DIR)/coverage.info --output-directory $(COV_DIR)
	@echo ">>> Coverage report available in $(COV_DIR)/index.html"

clean:
	rm -rf $(OUTDIR) $(COV_DIR)
