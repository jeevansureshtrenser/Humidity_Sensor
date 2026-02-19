# Just pass the command down to the next level
SUBDIRS := $(wildcard */.)

.PHONY: clean $(SUBDIRS)

clean test: $(SUBDIRS)

$(SUBDIRS):
	$(MAKE) -C $@ $(MAKECMDGOALS)