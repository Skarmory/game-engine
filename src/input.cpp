#include "input.h"
using namespace Command;

InputManager::InputManager(Entity* player, bool& is_running) : _player(player), _is_running(is_running) {}

ICommand* InputManager::handle_input(void)
{
	int in = getch();

	switch(in)
	{
		case 'h':
			return new MoveCommand(_player, -1, 0);
		case 'j':
			return new MoveCommand(_player, 0, 1);
		case 'k':
			return new MoveCommand(_player, 0, -1);
		case 'l':
			return new MoveCommand(_player, 1, 0);
		case 'y':
			return new MoveCommand(_player, -1, -1);
		case 'u':
			return new MoveCommand(_player, 1, -1);
		case 'b':
			return new MoveCommand(_player, -1, 1);
		case 'n':
			return new MoveCommand(_player, 1, 1);
		case 'q':
			return new QuitCommand(_is_running);
		case ERR:
		default:
			return nullptr;
	}
}
