#include "command.h"
using namespace Command;

MoveCommand::MoveCommand(std::weak_ptr<Entity> e, std::weak_ptr<Level> l, int x, int y) :
   	_entity(e), _level(l), _x(x), _y(y) {}

void MoveCommand::execute(void)
{
	if(std::shared_ptr<Entity> e = _entity.lock())
	{
		if(std::shared_ptr<Level> lev = _level.lock())
		{
			int dx, dy;
			std::shared_ptr<LocationComponent> lc = e->get_component<LocationComponent>();
				
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

AttackCommand::AttackCommand(std::weak_ptr<Entity> e, int x, int y) : _entity(e), _x(x), _y(y) {}

void AttackCommand::execute(void)
{
	if(std::shared_ptr<Entity> e = _entity.lock())
	{

	}
}	

QuitCommand::QuitCommand(bool& game_state) : _state(game_state) {}

void QuitCommand::execute(void)
{
	_state = false;
}
