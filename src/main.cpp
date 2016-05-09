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
#include "input.h"
#include "command.h"

int main(int argc, char** argv)
{
	srand(time(NULL));
	initscr();
	noecho();
	raw();
	curs_set(0);
	timeout(1);

	Entity* e = new Entity(0);
	LocationComponent lc(10, 10);
	GraphicComponent  gc('@');
	
	e->add_component(&lc);
	e->add_component(&gc);

	RenderSystem r_sys;
	r_sys.add_entity(e);

	Level l;
	l.load("sira_field");
	l.draw();

	r_sys.update();

	// Prototype, will be updated to some form of game state at some point
	bool running = true;
	InputManager input(e, running);
	
	Command::ICommand* input_command;
	while(running)
	{	
		input_command = input.handle_input();
		
		if(input_command != nullptr)
		{
			input_command->execute();
			delete input_command;
		}
		
		l.draw();
		r_sys.update();
	}

	delete e;

	refresh();
	getch();
	
	endwin();
	return 0;
}

#endif
