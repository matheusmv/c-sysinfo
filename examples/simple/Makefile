CC := gcc

CFLAGS := -pedantic-errors -Wall -Werror -Wextra -std=gnu11

LIBS := ../../src/*.c

SRC := simple.c

BIN := sysinfo

all: CFLAGS += -O2
all: relase

debug: CFLAGS += -O0 -g
debug: relase

relase:
	$(CC) $(CFLAGS) $(LIBS) $(SRC) -o $(BIN)

clean:
	$(RM) $(BIN)

BADFUNCS='[^_.>a-zA-Z0-9](str(n?cpy|n?cat|xfrm|n?dup|str|pbrk|tok|_)|stpn?cpy|a?sn?printf|byte_)'
check:
	@echo Files with potentially dangerous functions
	@egrep $(BADFUNCS) $(LIBS) || true
