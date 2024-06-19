// # ================================================== #
// #                    bspwmTest.c                     #
// # -------------------------------------------------- #
// # Writen by:  InvisibleBox                           #
// # Create date: June 18, 2024                         #
// # License: GPL - General Public License              #
// # Objective: For practice understanding the movement #
// #           of the display window in BSPWM :         #
// # -------------------------------------------------- #
// #   BSPWM - Binary Split Partitioning Window Manager #
// # ================================================== #


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <ncurses.h>
#include <string.h>
#include <sys/ioctl.h>

#define CURSOR_I system ("tput civis")
#define CURSOR_V system ("tput cvvis")


void RefreshScreen () {
	struct winsize tw;
	bool chg_flag = true;
	static int ox =0,  oy = 0;
	int cx, cy;	// Center of Cols and Height
	char msgT[] = "Super+alt+K ^ v Super+alt+shift+J",
		 msgB[] = "Super+alt+J v ^ Super+alt+shift+K",
		 msgL[] = "=> Super+alt+shift+L",
		 msgLc[] = "<= Super+alt+H",
		 msgR[] = "Super+alt+L =>",
		 msgRc[] = "Super+alt+shift+H <=",
		 msgEXIT[] = "Press [spacebar] to Exit";

	ioctl (0, TIOCGWINSZ, &tw);
	if ( tw.ws_col != ox )  {
		ox = tw.ws_col;
	//	chg_flag = true;
	}
	if ( tw.ws_row != oy ) {
		oy = tw.ws_row;
	//	chg_flag = true;
	}
	if ( chg_flag ) {
		clear ();	
		cx = tw.ws_col / 2;		cy = tw.ws_row / 2;
		mvprintw (0, cx - strlen (msgT) / 2, msgT);
		mvprintw (tw.ws_row - 1, cx - strlen( msgB) / 2, msgB);
		mvprintw (cy - 1, 0, msgL);
		mvprintw (cy + 1, 0, msgLc);
		mvprintw (cy - 1, tw.ws_col - strlen (msgR), msgR);
		mvprintw (cy + 1, tw.ws_col - strlen (msgRc), msgRc);
		mvprintw (cy, cx - strlen (msgEXIT) / 2, msgEXIT);
		refresh ();
	}
}


/* ======= MAIN PROGRAM ======= */

int main (int argc, char* argv[]) {

	struct termios term, oterm;
	struct winsize tw;
	char ch=0;
	
	tcgetattr (STDIN_FILENO, &term);
	ioctl (0, TIOCGWINSZ, &tw);
	oterm = term;
	term.c_lflag &= ~ ( ICANON  | ECHO | ISIG );  // disable { canonical input, echo, [^C,^\,^Z] }
	tcsetattr (STDIN_FILENO, TCSANOW, & term);
	CURSOR_I;
	initscr (); noecho ();
	while ( ch != ' ' ) {
		RefreshScreen ();
		napms (200);
		ch = getch ();
	}
	endwin ();
	CURSOR_V;
	tcsetattr (STDIN_FILENO, TCSANOW, &oterm);
	return 0;	
}

/* ======= END MAIN PROGRAM ======= */
