#include "command.h"

#include <memory>

#include "environment.h"
#include "entity.h"
#include "events.h"
#include "location.h"
#include "level_transition.h"
#include "level.h"
#include "move_system.h"

using namespace std;

MoveCommand::MoveCommand(int x, int y) : _x(x), _y(y) {}

void MoveCommand::execute(void)
{
	Entity* player = Environment::get().get_entity_manager()->get_player();

	// Player already moving
	if (player->has_component<Move>())
		return;

	Level& _level = Environment::get().get_level_manager()->get_current();
	Location* lc = player->get_component<Location>();

	int dx = lc->x + _x;
	int dy = lc->y + _y;

	if(_level.is_in_bounds(dx, dy) && _level.is_walkable(dx, dy))
	{
		player->add_component(new Move(dx, dy, lc->x * 32.0f, lc->y * 32.0f, 0.f));
		Environment::get().get_event_manager()->broadcast<MoveEvent>(player);

		lc->x = dx;
		lc->y = dy;
	}
}

AttackCommand::AttackCommand(int x, int y) : _x(x), _y(y) {}

void AttackCommand::execute(void)
{
	Entity* player = Environment::get().get_entity_manager()->get_player();
	
	Location* loc = player->get_component<Location>();
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
	Entity* player = Environment::get().get_entity_manager()->get_player();
	Location* loc = player->get_component<Location>();

	auto location_entities = Environment::get().get_entity_manager()->get_entities_at_loc(loc->x, loc->y, loc->z);

	for (auto& entity : location_entities)
	{
		if (entity->has_component<LevelTransition>())
		{
			LevelTransition* transition = entity->get_component<LevelTransition>();
			Environment::get().get_event_manager()->broadcast<LevelTransitionEvent>(transition);

			loc->x = transition->next_level_x;
			loc->y = transition->next_level_y;
			loc->z = transition->next_level_z;

			break;
		}
	}
}
