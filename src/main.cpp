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
	SystemManager sm(evm);

	Level l(em);

	sm.create<RenderSystem>(l);
	sm.create<LightSystem>(l);
	sm.create<PeriodicDamageUpdateSystem>();
	sm.create<CollisionSystem>();
	sm.create<DamageSystem>();
	sm.create<TimedHealthSystem>();
	
	sm.init();

	shared_ptr<Entity> player = em.create_entity_at_loc("player", 10, 10);
	//shared_ptr<Entity> enemy  = em.create_entity_at_loc("player", 8, 8);
	em.create_entity_at_loc("fire", 5, 5);
	em.create_entity_at_loc("aoe_dmg", 10, 30);
	em.create_entity_at_loc("aoe_dmg", 10, 31);
	em.create_entity_at_loc("aoe_dmg", 9, 30);
	em.create_entity_at_loc("aoe_dmg", 10, 32);
	em.create_entity_at_loc("aoe_dmg", 9, 31);
	em.create_entity_at_loc("aoe_dmg", 9, 29);
	em.create_entity_at_loc("aoe_dmg", 10, 33);

	l.load("testing_map");

	GameTime game_time;
	Timer turn_timer(3);
	int turn = 1;

	// Prototype, will be updated to some form of game state at some point
	bool running = true;
	InputManager input(player, l, running, em);
	
	while(running && !TCODConsole::isWindowClosed())
	{
		game_time.tick();
		turn_timer.tick(game_time);

		unique_ptr<ICommand> input_command = input.handle_input();

		// Input
		if(input_command != nullptr || turn_timer.finished())
		{
			turn_timer.reset();
			turn++;

			sm.update<PeriodicDamageUpdateSystem>();
			
			if(input_command != nullptr)
				input_command->execute();

			sm.update<CollisionSystem>();
			sm.update<DamageSystem>();
			sm.update<TimedHealthSystem>();
		}

		// Drawing
		TCODConsole::root->clear();
		l.base_draw();
		sm.update<LightSystem>();
		l.draw();
		sm.update<RenderSystem>();
		TCODConsole::root->print(0, 0, "T: %i", turn);
		TCODConsole::root->print(0, 2, "C: %i, %i", player->get_component<Location>()->x, player->get_component<Location>()->y);
		TCODConsole::root->print(0, 1, "HP: %i", player->get_component<Health>()->health);
		TCODConsole::flush();
		
		// Cleanup
		em.update();
	}

	return 0;
}

#endif
