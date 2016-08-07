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
#include "damage_component.h"
#include "input.h"
#include "command.h"
#include "entity_manager.h"
#include "collision_system.h"
#include "damage_system.h"

#include <exception>

int main(int argc, char** argv)
{
	initscr();
	noecho();
	raw();
	curs_set(0);
	timeout(1);

	// Create the player entity
	// TODO: Create some entity factory or builder
	std::shared_ptr<Entity> e = EntityManager::get_instance().create_entity();

	e->add_component(std::make_shared<LocationComponent>(10, 10));
	e->add_component(std::make_shared<GraphicComponent>('@'));
	e->add_component(std::make_shared<CollisionComponent>());
	e->add_component(std::make_shared<HealthComponent>(1));

	// Create a fire entity for the purposes of testing damage
	std::shared_ptr<Entity> fire = EntityManager::get_instance().create_entity();
	
	fire->add_component(std::make_shared<LocationComponent>(5, 5));
	fire->add_component(std::make_shared<GraphicComponent>('F'));
	fire->add_component(std::make_shared<CollisionComponent>());
	fire->add_component(std::make_shared<DamageComponent>(1));

	// Setup systems
	RenderSystem    r_sys;
	CollisionSystem coll_sys;
	DamageSystem	d_sys;

	r_sys.add_entity(e);
	r_sys.add_entity(fire);

	coll_sys.add_entity(e);
	coll_sys.add_entity(fire);

	d_sys.add_entity(e);

	std::shared_ptr<Level> l = std::make_shared<Level>();
	l->load("testing_map");
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
		
			coll_sys.update();
			d_sys.update();

			l->draw();
			r_sys.update();
		}
	
		mvprintw(0,0, "HP: %i", e->get_component<HealthComponent>()->health);
		mvprintw(20,0, "Player: %i, %i", e->get_component<LocationComponent>()->x, e->get_component<LocationComponent>()->y);
		mvprintw(21,0, "  Fire: %i, %i", fire->get_component<LocationComponent>()->x, fire->get_component<LocationComponent>()->y);
	}

	refresh();
	getch();
	
	endwin();
	return 0;
}

#endif
