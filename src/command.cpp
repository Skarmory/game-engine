#include "command.h"
using namespace std;

MoveCommand::MoveCommand(EntityManager& entity_manager, LevelManager& level_manager, int x, int y) :
   	_entity_manager(entity_manager), _level_manager(level_manager), _x(x), _y(y) {}

void MoveCommand::execute(void)
{
	Level& _level = _level_manager.get_current();
	Entity& player = _entity_manager.get_player();
	int dx, dy;
	shared_ptr<Location> lc = player.get_component<Location>();
			
	dx = lc->x + _x;
	dy = lc->y + _y;

	if(_level.is_in_bounds(dx, dy) && _level.is_walkable(dx, dy))
	{
		lc->x = dx;
		lc->y = dy;	
	}
	
}

AttackCommand::AttackCommand(EntityManager& entity_manager, int x, int y) 
	: _entity_manager(entity_manager), _x(x), _y(y) {}

void AttackCommand::execute(void)
{
	Entity& player = _entity_manager.get_player();
	
	shared_ptr<Location> loc = player.get_component<Location>();
	_entity_manager.create_entity_at_loc("damage", loc->x + _x, loc->y + _y, loc->z);
	
}	

QuitCommand::QuitCommand(bool& game_state) : _state(game_state) {}

void QuitCommand::execute(void)
{
	_state = false;
}

LevelTransitionCommand::LevelTransitionCommand(EntityManager& entity_manager, EventManager& event_manager) : _entity_manager(entity_manager), _event_manager(event_manager) {}

void LevelTransitionCommand::execute(void)
{
	auto& player = _entity_manager.get_player();
	shared_ptr<Location> loc = player.get_component<Location>();

	auto location_entities = _entity_manager.get_entities_at_loc(loc->x, loc->y, loc->z);

	for (auto& entity : location_entities)
	{
		if (entity->has_component<LevelTransition>())
		{
			shared_ptr<LevelTransition> transition = entity->get_component<LevelTransition>();
			_event_manager.broadcast<LevelTransitionEvent>(transition);

			loc->x = transition->next_level_x;
			loc->y = transition->next_level_y;
			loc->z = transition->next_level_z;

			break;
		}
	}
}
