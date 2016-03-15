CC ?= gcc

SRCDIR := benchmark
SUBDIRS := benchmark
PROGNAME := benchmark

all:
	for f in $(SUBDIRS); do $(MAKE) -C $$f all; done
	cp $(SRCDIR)/$(PROGNAME) ./bm

clean:
	for f in $(SUBDIRS); do $(MAKE) -C $$f clean; done
	rm $(PROGNAME)

.PHONY:all clean