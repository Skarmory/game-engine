#include "input.h"
using namespace Command;

typedef std::unique_ptr<ICommand> CPtr;

InputManager::InputManager(
		std::shared_ptr<Entity>& player, std::shared_ptr<Level> level, bool& is_running) 
	: _player(player),_level(level), _is_running(is_running) {}

CPtr InputManager::handle_input(void)
{
	int in = getch();
	
	switch(in)
	{
		case 'h':
			return CPtr(new MoveCommand(_player, _level, -1, 0));
		case 'j':
			return CPtr(new MoveCommand(_player, _level,  0, 1));
		case 'k':
			return CPtr(new MoveCommand(_player, _level, 0, -1));
		case 'l':
			return CPtr(new MoveCommand(_player, _level, 1, 0));
		case 'y':
			return CPtr(new MoveCommand(_player, _level, -1, -1));
		case 'u':
			return CPtr(new MoveCommand(_player, _level, 1, -1));
		case 'b':
			return CPtr(new MoveCommand(_player, _level, -1, 1));
		case 'n':
			return CPtr(new MoveCommand(_player, _level, 1, 1));
		case 'q':
			return CPtr(new QuitCommand(_is_running));
		case 'z':
			return CPtr(new Debug_KillPlayerCommand(_player));
		case ERR:
		default:
			return nullptr;
	}
}
