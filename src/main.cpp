#ifndef main_h
#define main_h

#include "libtcod.hpp"

#include <vector>
#include <time.h>
#include <chrono>

#include "level.h"
#include "entity.h"
#include "input.h"
#include "command.h"
#include "entity_manager.h"
#include "game_time.h"
#include "systems.h"
#include "components.h"
#include "observer.h"

using namespace std;
using namespace Command;

int main(int argc, char** argv)
{
	TCODConsole::initRoot(80, 40, "Words of Command", false);
	// Create the player entity
	// TODO: Create some entity factory or builder
	/*
	shared_ptr<Entity> e = EntityManager::get_instance().create_entity();

	e->add_component(make_shared<LocationComponent>(10, 10));
	e->add_component(make_shared<GraphicComponent>('@', TCODColor::white, TCODColor::black, DrawLayer::CREATURE));
	e->add_component(make_shared<CollisionComponent>());
	e->add_component(make_shared<HealthComponent>(1));

	// Create a fire entity for the purposes of testing damage
	shared_ptr<Entity> fire = EntityManager::get_instance().create_entity();
	
	fire->add_component(make_shared<LocationComponent>(5, 5));
	fire->add_component(make_shared<GraphicComponent>('F', TCODColor::orange, TCODColor::darkOrange, DrawLayer::EFFECT));
	fire->add_component(make_shared<CollisionComponent>());
	fire->add_component(make_shared<DamageComponent>(1));
	*/

	shared_ptr<EntityManager> eman = make_shared<EntityManager>();

	// Setup systems
	shared_ptr<RenderSystem> r_sys = make_shared<RenderSystem>();
	shared_ptr<TimeSystem> t_sys = make_shared<TimeSystem>();
	CollisionSystem coll_sys;
	DamageSystem	d_sys;

	eman->add_observer(r_sys);
	eman->add_observer(t_sys);
	eman->add_observer(coll_sys);
	coll_sys->add_observer(d_sys);

	shared_ptr<Entity> player = eman->create_entity_at_loc("player", 10, 10);
	shared_ptr<Entity> fire   = eman->create_entity_at_loc("fire", 5, 5);
	shared_ptr<Entity> damage = eman->create_entity_at_loc("damage", 20, 20);

	shared_ptr<Level> l = make_shared<Level>();
	l->load("testing_map");

	GameTime game_time;
	Timer turn_timer(3);
	int turn = 1;

	// Prototype, will be updated to some form of game state at some point
	bool running = true;
	InputManager input(player, l, running, eman);
	
	// Initial draw
	TCODConsole::root->clear();
	l->draw();
	r_sys->update();
	TCODConsole::root->print(0, 0, "T: %i", turn);
	TCODConsole::root->print(0, 1, "E: 0.00");
	TCODConsole::flush();

	while(running && !TCODConsole::isWindowClosed())
	{
		unique_ptr<ICommand> input_command(nullptr);

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
		t_sys->update();
		coll_sys.update();
		d_sys.update();

		// Drawing
		TCODConsole::root->clear();
		l->draw();
		r_sys->update();
		TCODConsole::root->print(0, 0, "T: %i", turn);
		TCODConsole::flush();

		turn_timer.reset();
		eman->update();
	}

	return 0;
}

#endif
