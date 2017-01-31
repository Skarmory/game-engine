#ifndef main_h
#define main_h

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

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
	RenderWindow window(VideoMode(800, 400), "Sovereign Incarnate");

	Image img;
	if (!img.loadFromFile("terminal.png"))
		return -1;

	img.createMaskFromColor(Color::Black);

	Texture tex;
	if (!tex.loadFromImage(img))
		return -1;

	Font font;
	if (!font.loadFromFile("arial.ttf"))
		return -1;

	GameTime game_time;
	Timer turn_timer(3);
	Timer draw_timer(0.03);
	int turn = 1;

	Environment env;
	sov::EventManager evm;
	env.set_event_manager(&evm);
	EntityManager em;
	env.set_entity_manager(&em);
	SystemManager sm;
	env.set_system_manager(&sm);
	LevelManager lm;
	env.set_level_manager(&lm);
	LuaVM lua;
	
	Camera camera(window, 0, 0, 80, 40, tex);
	StatusDisplay status(window, 0, 40, 80, 10, turn_timer, turn, font);
	InventoryDisplay inventory(window, 80, 0, 20, 50, font);

	sm.create<VisibilitySystem>();
	sm.create<RenderSystem>(camera);
	sm.create<LightSystem>();
	sm.create<PeriodicDamageUpdateSystem>();
	sm.create<CollisionSystem>();
	sm.create<DamageSystem>();
	sm.create<TimedHealthSystem>();
	
	sm.init();

	lm.load("testing_map");
	lua.load_script("test.lua");
	lua.call("onLoad");

	/*em.create_entity_at_loc("player", 10, 10, 0);
	em.create_entity_at_loc("fire", 5, 5, 0);
	em.create_entity_at_loc("rime", 10, 30, 0);
	em.create_entity_at_loc("rime", 10, 31, 0);
	em.create_entity_at_loc("rime", 9, 30, 0);
	em.create_entity_at_loc("rime", 10, 32, 0);
	em.create_entity_at_loc("rime", 9, 31, 0);
	em.create_entity_at_loc("rime", 9, 29, 0);
	em.create_entity_at_loc("rime", 10, 33, 0);

	shared_ptr<Entity> transition = em.create_entity_at_loc("level_transition", 10, 15, 0);
	shared_ptr<LevelTransition> lt = transition->get_component<LevelTransition>();
	lt->next_level_name = "testing_map2";
	lt->next_level_x = 70;
	lt->next_level_y = 30;
	lt->next_level_z = 1;*/

	// Prototype, will be updated to some form of game state at some point
	bool running = true;
	InputManager input(window, running);
	env.set_input_manager(&input);

	while(running && window.isOpen())
	{
		game_time.tick();
		turn_timer.tick(game_time);
		draw_timer.tick(game_time);

		unique_ptr<Command> input_command = input.handle_input();

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
		
		if (draw_timer.finished())
		{
			// Drawing	
			sm.update<LightSystem>();
			sm.update<VisibilitySystem>();

			camera.update();

			sm.update<RenderSystem>();

			window.clear();

			camera.draw();
			status.draw();
			inventory.draw();

			window.display();
		}
		
		// Cleanup
		em.update();
	}

	return 0;
}

#endif
