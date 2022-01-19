CC=gcc

CFLAGS=-pedantic-errors -Wall -Werror

LIBS=../../src/*.c

SRC=simple.c

BIN=sysinfo

all: CFLAGS+=-O2
all: relase

debug: CFLAGS+=-O0 -g
debug: relase

relase:
	$(CC) $(CFLAGS) $(LIBS) $(SRC) -o $(BIN)

clean:
	rm $(BIN)
