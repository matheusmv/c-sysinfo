CC=gcc

CFLAGS=-pedantic-errors -Wall -Werror

LFLAGS=-lpthread

OBJS=../../src/*.c buffer.c

SRC=cfetch.c

BIN=cfetch

all: CFLAGS+=-O2
all: relase

debug: CFLAGS+=-O0 -g
debug: relase

relase:
	$(CC) $(CFLAGS) $(COMPILER_FLAGS) $(OBJS) $(SRC) -o $(BIN) $(LFLAGS)

clean:
	rm $(BIN)
