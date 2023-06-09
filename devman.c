/* Basic imports */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>

/* Display imports */
#include <curses.h>

#define DEVMAN_VERSION 1.0
#define Y_MARGIN 1
#define X_MARGIN 4
#define BUFFSIZE 512
#define DEVMAN_FILE_EXTENSION "txt"
#define DEVMAN_SEARCH_DIR ".devman"


/* functions to be defined later */
int display_line(int, int, int);

int main(int argc, char** argv) {
	
	/* Ensure the proper number of arguments are supplied */
	if (2 > argc) {
		printf("error: no search term provided\n");
		printf("example:  %s help\n", argv[0]);
		return EXIT_FAILURE;
	} else if (2 < argc) {
		printf("error: too many search terms provided\n");
		printf("example:  %s help\n", argv[0]);
		return EXIT_FAILURE;
	}

	/* get man page file path */
	char filepath[BUFFSIZE];

	snprintf(filepath, BUFFSIZE - 1, "%s/%s/%s.%s", getenv("HOME"), DEVMAN_SEARCH_DIR, argv[1], DEVMAN_FILE_EXTENSION);

	int fd = open(filepath, O_RDONLY);

	if (0 > fd) {
		printf("Error: Page not found\n");
		printf("No devman page at: %s\n", filepath);
		perror("open");
		return EXIT_FAILURE;
	}

	/* Initialize the curses library */
	initscr();
	cbreak();
	noecho();
	keypad(stdscr, true);

	/* get screen size information */
	int rows, cols;
	getmaxyx(stdscr, rows, cols);

	int offset = Y_MARGIN;
	
	bool can_move = false;

	/* main loop: */
	while (true) {

		int line = offset;

		lseek(fd, 0, SEEK_SET);
		while (display_line(line, cols, fd)) {
			fflush(stdout);
			line ++;
		}

		if (line > rows) {
			can_move = true;
		}

		/* refresh screen */
		refresh();

		/* Allow user to exit, also blocking: */
		int key_pressed = getch();

		if ('q' == key_pressed) {
			break;
		} else if (can_move && KEY_DOWN == key_pressed) {
			offset --;
			if (line + Y_MARGIN <= rows) {
				offset ++; // undo that last move
			}
		} else if (can_move && KEY_UP == key_pressed) {
			offset ++;
			if (Y_MARGIN < offset) {
				offset --; // undo that last move
			}
		}


		clear();
	}

	close(fd);
	
	/* close the screen, exit cleanly */
	endwin();


	return EXIT_SUCCESS;
}

int display_line(int line_number, int width, int fd) {
	
	bool eof_triggered = false;

	char c;

	for (int i = X_MARGIN;i < width - 2 * X_MARGIN;i ++) {
		read(fd, &c, 1);

		if (c == 0x00) {
			eof_triggered = true;
			break;
		} else if (c == '\n') {
			break;
		} else if (c == '\t') {
			mvprintw(line_number, i, "   ");
			c = ' ';
			i += 3;
		}

		mvprintw(line_number, i, "%c", c);
	}

	return !eof_triggered;
}
