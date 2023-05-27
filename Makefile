CC=gcc
CFLAGS=-g -Wall -lc -lncurses
SRC=devman.c
EXTRAS=
BIN=devman

all: $(BIN) init

%:%.c
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f *.o a.out $(BIN)

init:
	rm -rf ~/.devman
	mkdir ~/.devman
	cp -r ./devman-pages/* ~/.devman/

