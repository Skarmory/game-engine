#include "command.h"

#include <memory>

#include "environment.h"
#include "entity.h"
#include "events.h"
#include "location.h"
#include "level_transition.h"
#include "level.h"

using namespace std;

MoveCommand::MoveCommand(float x,float y) : _x(x), _y(y) {}

void MoveCommand::execute(void)
{
	Level& _level = Environment::get().get_level_manager()->get_current();
	Entity& player = Environment::get().get_entity_manager()->get_player();
	float dx, dy;
	shared_ptr<Location> lc = player.get_component<Location>();
			
	dx = lc->x + _x;
	dy = lc->y + _y;

	if(_level.is_in_bounds(dx, dy) && _level.is_walkable(dx, dy))
	{
		lc->x = dx;
		lc->y = dy;	
	}
}

AttackCommand::AttackCommand(int x, int y) : _x(x), _y(y) {}

void AttackCommand::execute(void)
{
	Entity& player = Environment::get().get_entity_manager()->get_player();
	
	shared_ptr<Location> loc = player.get_component<Location>();
	Environment::get().get_entity_manager()->create_entity_at_loc("damage", loc->x + _x, loc->y + _y, loc->z);
	
}	

QuitCommand::QuitCommand(bool& game_state) : _state(game_state) {}

void QuitCommand::execute(void)
{
	_state = false;
}

LevelTransitionCommand::LevelTransitionCommand(void) {}

void LevelTransitionCommand::execute(void)
{
	Entity& player = Environment::get().get_entity_manager()->get_player();
	shared_ptr<Location> loc = player.get_component<Location>();

	auto location_entities = Environment::get().get_entity_manager()->get_entities_at_loc(loc->x, loc->y, loc->z);

	for (auto& entity : location_entities)
	{
		if (entity->has_component<LevelTransition>())
		{
			shared_ptr<LevelTransition> transition = entity->get_component<LevelTransition>();
			Environment::get().get_event_manager()->broadcast<LevelTransitionEvent>(transition);

			loc->x = transition->next_level_x;
			loc->y = transition->next_level_y;
			loc->z = transition->next_level_z;

			break;
		}
	}
}
