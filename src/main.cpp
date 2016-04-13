#ifndef main_h
#define main_h

#include <ncurses.h>
#include <vector>
#include <time.h>
#include "room.h"
#include "level.h"

int main(int argc, char** argv)
{
	srand(time(NULL));
	initscr();
	noecho();
	raw();

	int mapx, mapy;

	getmaxyx(stdscr, mapy, mapx);

	Level l;
	l.load("sira_field");
	l.draw();

	mvprintw(0, 0, "Scr x: %d", mapx);
	mvprintw(1, 0, "Scr y: %d", mapy);
	
	refresh();
	getch();
	
	endwin();
	return 0;
}

#endif
