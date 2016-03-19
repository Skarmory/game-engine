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

	Level* l = new Level(mapx, mapy);

	mvprintw(0, 0, "Scr x: %d", mapx);
	mvprintw(1, 0, "Scr y: %d", mapy);
	
	Room* r;
	char c;
	for(std::vector<Room*>::const_iterator it = l->rooms_begin(); it != l->rooms_end(); it++)
	{
		r = *it;
		const Dimensions d = r->getDimensions();

		for(int x = d.x; x < d.x + d.width; x++)	
		for(int y = d.y; y < d.y + d.height; y++)
		{
			if(r->isCorner(x, y))
			{
				c = Room::WALL_HORIZONTAL;
			}
			else if(x == d.x || x == d.x + d.width - 1)
			{
				c = Room::WALL_VERTICAL;
			}
			else if(y == d.y || y == d.y + d.height - 1)
			{
				c = Room::WALL_HORIZONTAL;
			}
			else
			{
				c = Room::ROOM_FLOOR;
			}
			
			mvaddch(y, x, c);
		}
	}	

	/*
	const Dimensions d = r.getDimensions();
	char c;
	
	mvprintw(0, 0, "Here: %d %d %d %d", d.x, d.y, d.width, d.height);
	
	for(int x = d.x; x < d.x + d.width; x++)	
	for(int y = d.y; y < d.y + d.height; y++)
	{
		if(r.isCorner(x, y))
		{
			c = Room::WALL_HORIZONTAL;
		}
		else if(x == d.x || x == d.x + d.width - 1)
		{
			c = Room::WALL_VERTICAL;
		}
		else if(y == d.y || y == d.y + d.height - 1)
		{
			c = Room::WALL_HORIZONTAL;
		}
		else
		{
			c = Room::ROOM_FLOOR;
		}
		
		mvaddch(y, x, c);
	}
	*/

	refresh();
	getch();
	
	delete l;	
	endwin();
	return 0;
}

#endif
