#ifndef main_h
#define main_h

#include <SFML/Graphics.hpp>

#include <vector>
#include <time.h>
#include <chrono>
#include <iostream>

#include "lua_inc.h"
#include "game_time.h"

// Managers
#include "event.h"
#include "entity_manager.h"
#include "system.h"
#include "level_manager.h"
#include "input.h"
#include "environment.h"
#include "sprite.h"

// Systems
#include "render_system.h"
#include "light_system.h"
#include "visibility_system.h"
#include "periodic_damage_system.h"
#include "collision_system.h"
#include "timed_health_system.h"
#include "damage_system.h"

#include "ui.h"

#include "lua_vm.h"

using namespace std;

int main(int argc, char** argv)
{	
	/*Font font;
	if (!font.loadFromFile("arial.ttf"))
		return -1;*/

	GameTime game_time;
	Timer turn_timer(3);
	Timer draw_timer(0.03);
	int turn = 1;

	Environment* env = new Environment();

	sov::EventManager* evm = new sov::EventManager();
	env->set_event_manager(evm);

	EntityManager* em = new EntityManager();
	env->set_entity_manager(em);

	SystemManager* sm = new SystemManager();
	env->set_system_manager(sm);

	LevelManager* lm = new LevelManager();
	env->set_level_manager(lm);

	SpriteCache* sprite_cache = new SpriteCache();
	env->set_sprite_cache(sprite_cache);

	LuaVM* lua = new LuaVM();

	Viewport viewport(0, 0, 20, 15);
	//StatusDisplay status(window, 0, 40, 80, 10, turn_timer, turn, font);
	//InventoryDisplay inventory(window, 80, 0, 20, 50, font);

	sm->create<VisibilitySystem>();
	sm->create<RenderSystem>(viewport);
	sm->create<LightSystem>();
	sm->create<PeriodicDamageUpdateSystem>();
	sm->create<CollisionSystem>();
	sm->create<DamageSystem>();
	sm->create<TimedHealthSystem>();
	
	sm->init();

	lm->load("testing_map.dat");
	lua->load_script("test.lua");
	lua->call("onLoad");

	/*shared_ptr<Entity> transition = em.create_entity_at_loc("level_transition", 10, 15, 0);
	shared_ptr<LevelTransition> lt = transition->get_component<LevelTransition>();
	lt->next_level_name = "testing_map2";
	lt->next_level_x = 70;
	lt->next_level_y = 30;
	lt->next_level_z = 1;*/

	// Prototype, will be updated to some form of game state at some point
	bool running = true;
	InputManager* input = new InputManager(viewport, running);
	env->set_input_manager(input);

	while(running && viewport.isOpen())
	{
		game_time.tick();
		turn_timer.tick(game_time);
		draw_timer.tick(game_time);

		unique_ptr<Command> input_command = input->handle_input();

		// Input
		if(input_command != nullptr || turn_timer.finished())
		{
			turn_timer.reset();
			turn++;

			sm->update<PeriodicDamageUpdateSystem>();
			
			if(input_command != nullptr)
				input_command->execute();

			sm->update<CollisionSystem>();
			sm->update<DamageSystem>();
			sm->update<TimedHealthSystem>();
		}
		
		if (draw_timer.finished())
		{
			viewport.clear();
			viewport.update();

			// Drawing	
			sm->update<LightSystem>();
			sm->update<VisibilitySystem>();

			sm->update<RenderSystem>();

			viewport.display();
		}
		
		// Cleanup
		em->update();
	}

	delete sprite_cache;
	delete input;
	delete lua;
	delete lm;
	delete sm;
	delete em;
	delete evm;
	delete env;

	return 0;
}

#endif
