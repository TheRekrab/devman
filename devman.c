/* Basic imports */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

/* Display imports */
#include <curses.h>

#define DEVMAN_VERSION 1.0

int main(int argc, char** argv) {
	
	/* Ensure the proper number of arguments are supplied */
	if (1 == argc) {
		printf("error: no search term provided\n");
		printf("example:  %s help\n", argv[0]);
		return EXIT_FAILURE;
	} else if (2 < argc) {
		printf("error: too many search terms provided\n");
		printf("example:  %s help\n", argv[0]);
		return EXIT_FAILURE;
	}

	/* Initialize the curses library */
	initscr();
	cbreak();
	noecho();

	/* main loop: */
	while (true) {
		refresh();
		int key_pressed = getch();

		if (key_pressed == 'q') {
			break;
		}

		clear();
	}
	
	/* close the screen, exit cleanly */
	endwin();


	return EXIT_SUCCESS;
}
