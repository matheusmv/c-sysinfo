CC=gcc

CFLAGS=-O2 \
	-pedantic-errors \
	-Wall \
	-Werror \

OBJS=../../src/*.c buffer.c

SRC=cfetch.c

OBJ_NAME=cfetch

all: relase

debug: CFLAGS += -g
debug: all

relase:
	$(CC) $(CFLAGS) $(COMPILER_FLAGS) $(OBJS) $(SRC) -o $(OBJ_NAME) -lpthread

clean:
	rm $(OBJ_NAME)
