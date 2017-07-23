TARGET := benchmark
SRCDIR := benchmark

CC ?= gcc

OPTIMIZATION_LEVEL ?= -O2

LDFLAGS ?=
LDFLAGS += -lmyhtml -pthread

CFLAGS ?= -Wall -Werror
CFLAGS += $(OPTIMIZATION_LEVEL) -fPIC --std=c99 -pthread -I. -I ../html5ever_parse_capi/include

UNAM := $(shell uname -s)
ifeq ($(UNAM),Linux)
	CFLAGS += -D_POSIX_C_SOURCE=199309L
    LDFLAGS += -lrt
endif

BENCHMARK_BUILD_WITH_ONLY_MyHTML ?= NO
ifeq ($(BENCHMARK_BUILD_WITH_ONLY_MyHTML),NO)
    LDFLAGS +=  -lgumbo -L ../html5ever_parse_capi/target/release -lhtml5ever_parse_capi -lpthread -l dl
else
    CFLAGS += -DBENCHMARK_BUILD_WITH_ONLY_MyHTML
endif

#LDFLAGS += -lhubbub -lparserutils -ldom -lwapcaplet -L/opt/local/lib -liconv

SRCS := $(wildcard *.c)
HDRS := $(wildcard *.h)
OBJS := $(patsubst %.c, %.o, $(SRCS))

all: build

build: $(OBJS) $(HDRS)
	$(CC) $(OBJS) $(LDFLAGS) -o $(TARGET)

clean:
	rm -f *.o
	rm -f $(TARGET)

.PHONY: all clean
