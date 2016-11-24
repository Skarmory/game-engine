#ifndef main_h
#define main_h

#include <SFML/Graphics.hpp>

#include <vector>
#include <time.h>
#include <chrono>

#include "entity.h"
#include "input.h"
#include "command.h"
#include "entity_manager.h"
#include "game_time.h"
#include "systems.h"
#include "components.h"
#include "event.h"
#include "ui.h"

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

	EventManager evm;
	EntityManager em(evm);
	SystemManager sm(evm);

	Level l(em);
	l.load("testing_map");

	sm.create<VisibilitySystem>(sm, em, &l);
	sm.create<RenderSystem>(sm, &l);
	sm.create<LightSystem>(sm, &l);
	sm.create<PeriodicDamageUpdateSystem>(sm);
	sm.create<CollisionSystem>(sm);
	sm.create<DamageSystem>(sm);
	sm.create<TimedHealthSystem>(sm);
	
	sm.init();

	shared_ptr<Entity> player = em.create_entity_at_loc("player", 10, 10);
	
	em.create_entity_at_loc("fire", 5, 5);
	em.create_entity_at_loc("aoe_dmg", 10, 30);
	em.create_entity_at_loc("aoe_dmg", 10, 31);
	em.create_entity_at_loc("aoe_dmg", 9, 30);
	em.create_entity_at_loc("aoe_dmg", 10, 32);
	em.create_entity_at_loc("aoe_dmg", 9, 31);
	em.create_entity_at_loc("aoe_dmg", 9, 29);
	em.create_entity_at_loc("aoe_dmg", 10, 33);

	GameTime game_time;
	Timer turn_timer(3);
	int turn = 1;

	Canvas world(window, 0, 0, 80, 40, &l, em, sm, tex);
	StatusDisplay status(window, 0, 40, 80, 10, em, turn_timer, turn, font);
	InventoryDisplay inventory(window, 80, 0, 20, 50, font);

	// Prototype, will be updated to some form of game state at some point
	bool running = true;
	InputManager input(window, player, l, running, em);
	
	while(running && window.isOpen())
	{
		game_time.tick();
		turn_timer.tick(game_time);

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

		// Drawing	
		sm.update<LightSystem>();
		sm.update<VisibilitySystem>();
		sm.update<RenderSystem>();

		window.clear();

		world.draw();
		status.draw();
		inventory.draw();
		
		window.display();
		
		// Cleanup
		em.update();
	}

	return 0;
}

#endif
