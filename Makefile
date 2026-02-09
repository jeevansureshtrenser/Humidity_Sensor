# Get a list of all subdirectories that contain a Makefile
SUBDIRS := $(wildcard */Makefile)
SUBDIRS := $(patsubst %/Makefile,%,$(SUBDIRS))

.PHONY: all clean $(SUBDIRS)

# Default target
all: $(SUBDIRS)

# Rule to enter each subdirectory and run make
$(SUBDIRS):
	@echo "------------------------------------------"
	@echo "Building VxWorks module: $@"
	@echo "------------------------------------------"
	$(MAKE) -C $@
	@echo "Done"

clean:
	@for dir in $(SUBDIRS); do \
		$(MAKE) -C $$dir clean; \
	done