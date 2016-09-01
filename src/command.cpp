#include "command.h"
using namespace std;
using namespace Command;

MoveCommand::MoveCommand(weak_ptr<Entity> e, weak_ptr<Level> l, int x, int y) :
   	_entity(e), _level(l), _x(x), _y(y) {}

void MoveCommand::execute(void)
{
	if(shared_ptr<Entity> e = _entity.lock())
	{
		if(shared_ptr<Level> lev = _level.lock())
		{
			int dx, dy;
			shared_ptr<LocationComponent> lc = e->get_component<LocationComponent>();
				
			dx = lc->x + _x;
			dy = lc->y + _y;

			if(lev->is_in_bounds(dx, dy) && lev->is_walkable(dx, dy))
			{
				lc->x = dx;
				lc->y = dy;	
			}
		}
	}
}

AttackCommand::AttackCommand(const shared_ptr<EntityManager>& entity_manager, weak_ptr<Entity> attacker, int x, int y) 
	: _entity_manager(entity_manager), _attacker(attacker), _x(x), _y(y) {}

void AttackCommand::execute(void)
{
	if(shared_ptr<Entity> atker = _attacker.lock())
	{
		if(atker->has_component<LocationComponent>())
		{
			shared_ptr<LocationComponent> loc = atker->get_component<LocationComponent>();
			shared_ptr<Entity> e = _entity_manager->create_entity_at_loc("fire", loc->x + _x, loc->y + _y);
		}
	}
}	

QuitCommand::QuitCommand(bool& game_state) : _state(game_state) {}

void QuitCommand::execute(void)
{
	_state = false;
}
