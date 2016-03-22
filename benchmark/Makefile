TARGET := benchmark
SRCDIR := benchmark

CC ?= gcc

OPTIMIZATION_LEVEL ?= -O2

CFLAGS ?= -Wall -Werror
CFLAGS += $(OPTIMIZATION_LEVEL) -fPIC --std=c99 -pthread -I.

UNAM := $(shell uname -s)
ifeq ($(UNAM),Linux)
	CFLAGS += -D_POSIX_C_SOURCE=199309L
endif

LDFLAGS ?= 
LDFLAGS += -lmyhtml -pthread -lhtml2html_lib -lm -ldl -lgumbo
#LDFLAGS += -lhubbub -lparserutils -ldom -lwapcaplet -L/opt/local/lib -liconv 

SRCS := $(wildcard *.c)
HDRS := $(wildcard *.h)
OBJS := $(patsubst %.c, %.o, $(SRCS))

all: build

build: $(OBJS) $(HDRS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

clean:
	rm *.o
	rm $(TARGET)

.PHONY: all clean
