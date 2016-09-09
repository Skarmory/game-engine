#include "command.h"
using namespace std;
using namespace Command;

MoveCommand::MoveCommand(weak_ptr<Entity> e, const Level& l, int x, int y) :
   	_entity(e), _level(l), _x(x), _y(y) {}

void MoveCommand::execute(void)
{
	if(shared_ptr<Entity> e = _entity.lock())
	{
		int dx, dy;
		shared_ptr<Location> lc = e->get_component<Location>();
			
		dx = lc->x + _x;
		dy = lc->y + _y;

		if(_level.is_in_bounds(dx, dy) && _level.is_walkable(dx, dy))
		{
			lc->x = dx;
			lc->y = dy;	
		}
	}
}

AttackCommand::AttackCommand(EntityManager& entity_manager, weak_ptr<Entity> attacker, int x, int y) 
	: _entity_manager(entity_manager), _attacker(attacker), _x(x), _y(y) {}

void AttackCommand::execute(void)
{
	if(shared_ptr<Entity> atker = _attacker.lock())
	{
		if(atker->has_component<Location>())
		{
			shared_ptr<Location> loc = atker->get_component<Location>();
			shared_ptr<Entity> e = _entity_manager.create_entity_at_loc("damage", loc->x + _x, loc->y + _y);
		}
	}
}	

QuitCommand::QuitCommand(bool& game_state) : _state(game_state) {}

void QuitCommand::execute(void)
{
	_state = false;
}
