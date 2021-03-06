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
#include "level_manager.h"
#include "input.h"
#include "environment.h"
#include "sprite.h"

// Systems
#include "system.h"
#include "render_system.h"
#include "light_system.h"
#include "visibility_system.h"
#include "collision_system.h"
#include "damage_system.h"
#include "move_system.h"

#include "ui.h"

#include "lua_vm.h"

using namespace std;

int main(int argc, char** argv)
{	
	/*Font font;
	if (!font.loadFromFile("arial.ttf"))
		return -1;*/

	GameTime* game_time = new GameTime();
	Timer turn_timer(3);
	Timer fixed(1.0f / 30.0f);
	int turn = 1;

	Environment* env = new Environment();

	env->set_game_time(game_time);

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

	AnimationCache* anim_cache = new AnimationCache();
	env->set_animation_cache(anim_cache);

	LuaVM* lua = new LuaVM();

	Viewport* viewport = new Viewport(0, 0, 20, 15);
	//StatusDisplay status(window, 0, 40, 80, 10, turn_timer, turn, font);
	//InventoryDisplay inventory(window, 80, 0, 20, 50, font);

	//sm->create<VisibilitySystem>();
	sm->create<RenderSystem>(viewport);
	sm->create<LightSystem>();
	sm->create<CollisionSystem>();
	sm->create<AnimationSystem>();
	////sm->create<DamageSystem>();
	sm->create<MoveSystem>();

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
	float accumulate = 0.f;

	while(running && viewport->isOpen())
	{
		game_time->tick();
		//std::cout << game_time->delta() << std::endl;
		turn_timer.tick(*game_time);
		fixed.tick(*game_time);
		accumulate += game_time->delta();

		if (fixed.finished())
		{
			std::unique_ptr<Command> input_command = input->handle_input();

			// Input
			if (input_command != nullptr || turn_timer.finished())
			{
				turn_timer.reset();
				turn++;

				if (input_command != nullptr)
					input_command->execute();
			}

			sm->update<CollisionSystem>();
			sm->update<MoveSystem>();

			em->update();
		}
		
		/*if (accumulate >= (1.f / 30.f))
		{*/
			sm->update<AnimationSystem>();
			sm->update<LightSystem>();

			viewport->update();
			viewport->clear();

			// Drawing
			sm->update<RenderSystem>();

			viewport->display();

		/*	accumulate = 0.f;
		}*/
	}

	delete env;

	return 0;
}

#endif
