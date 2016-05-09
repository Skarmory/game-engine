#include "command.h"
using namespace Command;

MoveCommand::MoveCommand(Entity* e, int x, int y) : _entity(e), _x(x), _y(y) {}

void MoveCommand::execute(void)
{
	LocationComponent* lc = static_cast<LocationComponent*>(_entity->get_component("LocationComponent"));
	lc->x += _x;
	lc->y += _y;	
}

QuitCommand::QuitCommand(bool& game_state) : _state(game_state) {}

void QuitCommand::execute(void)
{
	_state = false;
}
