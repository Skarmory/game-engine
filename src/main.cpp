#ifndef main_h
#define main_h

#include <ncurses.h>
#include <vector>
#include <time.h>
#include "level.h"
#include "render_system.h"
#include "entity.h"
#include "graphic_component.h"
#include "location_component.h"

int main(int argc, char** argv)
{
	srand(time(NULL));
	initscr();
	noecho();
	raw();

	Entity e(0);
	LocationComponent lc(10, 10);
	GraphicComponent  gc('@');
	
	e.add_component(&lc);
	e.add_component(&gc);

	RenderSystem r_sys;
	r_sys.add_entity(&e);

	Level l;
	l.load("sira_field");
	l.draw();

	r_sys.update();

	refresh();
	getch();
	
	endwin();
	return 0;
}

#endif
