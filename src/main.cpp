#ifndef main_h
#define main_h

#include "libtcod.hpp"

#include <vector>
#include <time.h>
#include <chrono>

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
#include "game_time.h"

int main(int argc, char** argv)
{
	TCODConsole::initRoot(80, 40, "Words of Command", false);

	// Create the player entity
	// TODO: Create some entity factory or builder
	std::shared_ptr<Entity> e = EntityManager::get_instance().create_entity();

	e->add_component(std::make_shared<LocationComponent>(10, 10));
	e->add_component(std::make_shared<GraphicComponent>('@', TCODColor::white));
	e->add_component(std::make_shared<CollisionComponent>());
	e->add_component(std::make_shared<HealthComponent>(1));

	// Create a fire entity for the purposes of testing damage
	std::shared_ptr<Entity> fire = EntityManager::get_instance().create_entity();
	
	fire->add_component(std::make_shared<LocationComponent>(5, 5));
	fire->add_component(std::make_shared<GraphicComponent>('F', TCODColor::orange));
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

	GameTime game_time;
	Timer turn_timer(3);
	int turn = 1;

	// Prototype, will be updated to some form of game state at some point
	bool running = true;
	InputManager input(e, l, running);
	
	std::unique_ptr<Command::ICommand> input_command(nullptr);

	// Initial draw
	TCODConsole::root->clear();
	l->draw();
	r_sys.update();
	TCODConsole::root->print(0, 0, "T: %i", turn);
	TCODConsole::root->print(0, 1, "E: 0.00");
	TCODConsole::flush();

	while(running && !TCODConsole::isWindowClosed())
	{
		// TODO: Make the input manager handle all of this
		// Input
		do 
		{
			game_time.tick();
			turn_timer.tick(game_time);
			input_command = input.handle_input();
			TCODConsole::root->print(0,1,"E: %1.2f", turn_timer.time_elapsed());
			TCODConsole::flush();
		} 
		while(input_command == nullptr && !turn_timer.finished());
		

		if(input_command != nullptr)
		{
			input_command->execute();
		}

		turn++;

		// Logic
		coll_sys.update();
		d_sys.update();

		// Drawing
		TCODConsole::root->clear();
		l->draw();
		r_sys.update();
		TCODConsole::root->print(0, 0, "T: %i", turn);
		TCODConsole::flush();

		turn_timer.reset();
	}

	return 0;
}

#endif
