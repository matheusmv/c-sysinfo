CC=gcc

CFLAGS=-O2 \
	-pedantic-errors \
	-Wall \
	-Werror \

OBJS=src/*.c

OBJ_NAME=sysinfo

all: relase

debug: CFLAGS += -g
debug: all

relase:
	$(CC) $(CFLAGS) $(COMPILER_FLAGS) $(OBJS) $(ARGS) -o $(OBJ_NAME)

clean:
	rm $(OBJ_NAME)
