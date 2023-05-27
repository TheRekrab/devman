CC=gcc
CFLAGS=-s -Wall -lc -lncurses
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

install: $(BIN) init
	@echo "-->>>>> IMPORTANT: Please make sure you run install as root! If you cannot do that, then run 'local-install' instead"
	cp $(BIN) /usr/bin/$(BIN)

local-install: $(BIN) init
	cp $(BIN) ~/.local/bin/$(BIN)
