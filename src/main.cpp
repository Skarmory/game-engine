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
#include "entity_manager.h"

int main(int argc, char** argv)
{
	initscr();
	noecho();
	raw();
	curs_set(0);
	timeout(1);

	std::shared_ptr<Entity> e = EntityManager::get_instance().create_entity();

	e->add_component(std::make_shared<LocationComponent>(10, 10));
	e->add_component(std::make_shared<GraphicComponent>('@'));

	RenderSystem r_sys;
	r_sys.add_entity(e);

	std::shared_ptr<Level> l = std::make_shared<Level>();
	l->load("sira_field");
	l->draw();

	r_sys.update();

	// Prototype, will be updated to some form of game state at some point
	bool running = true;
	InputManager input(e, l, running);
	
	std::unique_ptr<Command::ICommand> input_command(nullptr);
	while(running)
	{	
		input_command = input.handle_input();
		
		if(input_command != nullptr)
		{
			input_command->execute();
		}
		
		l->draw();
		r_sys.update();
	}

	refresh();
	getch();
	
	endwin();
	return 0;
}

#endif
