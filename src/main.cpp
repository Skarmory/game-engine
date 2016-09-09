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
#include "event.h"

using namespace std;
using namespace Command;

int main(int argc, char** argv)
{
	TCODConsole::initRoot(80, 40, "", false);

	EventManager evm;
	EntityManager em(evm);

	// Setup systems
	RenderSystem r_sys;
	TimeSystem t_sys;
	CollisionSystem coll_sys;
	DamageSystem d_sys;

	evm.subscribe<EntityCreated>(r_sys);

	shared_ptr<Entity> player = em.create_entity_at_loc("player", 10, 10);
	shared_ptr<Entity> enemy  = em.create_entity_at_loc("player", 8, 8);
	em.create_entity_at_loc("fire", 5, 5);
	em.create_entity_at_loc("damage", 20, 20);

	Level l;
	l.load("testing_map");

	GameTime game_time;
	Timer turn_timer(3);
	int turn = 1;

	// Prototype, will be updated to some form of game state at some point
	bool running = true;
	InputManager input(player, l, running, em);
	
	// Initial draw
	TCODConsole::root->clear();
	l.draw();
	r_sys.update(evm);
	TCODConsole::root->print(0, 0, "T: %i", turn);
	TCODConsole::root->print(0, 1, "E: 0.00");
	TCODConsole::root->print(0, 2, "HP: %i", player->get_component<Health>()->health);
	TCODConsole::root->print(30, 0, "HP: %i", enemy->get_component<Health>()->health);
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
		t_sys.update(evm);
		coll_sys.update(evm);
		d_sys.update(evm);

		// Drawing
		TCODConsole::root->clear();
		l.draw();
		r_sys.update(evm);
		TCODConsole::root->print(0, 0, "T: %i", turn);
		TCODConsole::root->print(0, 2, "HP: %i", player->get_component<Health>()->health);
		TCODConsole::root->print(30, 0, "HP: %i", enemy->get_component<Health>()->health);
		TCODConsole::flush();
		
		// Cleanup
		turn_timer.reset();
		coll_sys.clean();
		em.update();
	}

	return 0;
}

#endif
