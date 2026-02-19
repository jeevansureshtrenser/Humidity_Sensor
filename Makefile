# Get a list of all subdirectories that contain a Makefile
SRC_DIR 		:= source
TEST_DIR 		:= test
OUTDIR 			:= outputs
SUBDIRS 		:= $(wildcard $(SRC_DIR)/*/Makefile)
SUBDIRS 		:= $(patsubst %/Makefile,%,$(SUBDIRS))
TEST_SUBDIRS 	:= $(wildcard $(TEST_DIR)/*/.)

.PHONY: all clean test testclean $(SUBDIRS)

# Default target
all: $(SUBDIRS)

# Rule to enter each subdirectory and run make
$(SUBDIRS):
	@echo "------------------------------------------"
	@echo "Building VxWorks module: $@"
	@echo "------------------------------------------"
	@$(MAKE) -C $@
	@echo "Done"

clean:
	@echo "------------------------------------------"
	@echo "Cleaning VxWorks module: $@"
	@echo "------------------------------------------"
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	rm -rf $(OUTDIR)/*
	@echo "done"

testclean:
	@echo "------------------------------------------"
	@echo "Cleaning test module: $@"
	@echo "------------------------------------------"
	@for dir in $(TEST_SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done
	@echo "done"


test:
	@echo "------------------------------------------"
	@echo "Running unit tests for VxWorks module: $@"
	@echo "------------------------------------------"
	@for dir in $(TEST_SUBDIRS); do \
		echo "------------------------------------------"; \
		echo "Entering test directory: $$dir"; \
		echo "Running tests in: $$dir"; \
		echo "------------------------------------------"; \
		$(MAKE) -C $$dir test; \
	done
	@echo "done"