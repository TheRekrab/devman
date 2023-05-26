CC=gcc
CFLAGS=-g -Wall -lc -lncurses
SRC=devman.c
EXTRAS=
BIN=devman

all: $(BIN)

%:%.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o a.out $(BIN)
