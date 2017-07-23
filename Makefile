CC ?= gcc

SRCDIR := benchmark
SUBDIRS := benchmark
PROGNAME := benchmark

all:
	for f in $(SUBDIRS); do $(MAKE) -C $$f $@; done
	cp $(SRCDIR)/$(PROGNAME) ./bm

clean:
	for f in $(SUBDIRS); do $(MAKE) -C $$f clean; done
	rm -f ./bm

.PHONY:all clean
