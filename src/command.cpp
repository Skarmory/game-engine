#include "command.h"
using namespace Command;

MoveCommand::MoveCommand(std::weak_ptr<Entity> e, int x, int y) : _entity(e), _x(x), _y(y) {}

void MoveCommand::execute(void)
{
	if(std::shared_ptr<Entity> e = _entity.lock())
	{
		std::shared_ptr<LocationComponent> lc = e->get_component<LocationComponent>();
	
		lc->x += _x;
		lc->y += _y;	
	}
}

QuitCommand::QuitCommand(bool& game_state) : _state(game_state) {}

void QuitCommand::execute(void)
{
	_state = false;
}

Debug_KillPlayerCommand::Debug_KillPlayerCommand(std::shared_ptr<Entity>& e) : _entity(e) {}

void Debug_KillPlayerCommand::execute(void)
{
	_entity.reset();
}

