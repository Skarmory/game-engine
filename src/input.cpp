#include "input.h"
using namespace Command;

typedef std::unique_ptr<ICommand> c_uptr;

InputManager::InputManager(
		std::shared_ptr<Entity>& player, std::shared_ptr<Level> level, bool& is_running) 
	: _player(player),_level(level), _is_running(is_running) {}

c_uptr InputManager::handle_input(void)
{
	TCOD_key_t in;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY_PRESS, &in, NULL);
	
	switch(in.vk)
	{
		case TCODK_CHAR:
			switch(in.c)
			{
				case 'h':
					if(in.shift)
						return c_uptr(new AttackCommand(_player, -1, 0));
					return c_uptr(new MoveCommand(_player, _level, -1, 0));
				case 'j':
					if(in.shift)
						return c_uptr(new AttackCommand(_player, 0, 1));
					return c_uptr(new MoveCommand(_player, _level,  0, 1));
				case 'k':
					if(in.shift)
						return c_uptr(new AttackCommand(_player, 0, -1));
					return c_uptr(new MoveCommand(_player, _level, 0, -1));
				case 'l':
					if(in.shift)
						return c_uptr(new AttackCommand(_player, 1, 0));
					return c_uptr(new MoveCommand(_player, _level, 1, 0));
				case 'y':
					if(in.shift)
						return c_uptr(new AttackCommand(_player, -1, -1));
					return c_uptr(new MoveCommand(_player, _level, -1, -1));
				case 'u':
					if(in.shift)
						return c_uptr(new AttackCommand(_player, 1, -1));
					return c_uptr(new MoveCommand(_player, _level, 1, -1));
				case 'b':
					if(in.shift)
						return c_uptr(new AttackCommand(_player, -1, 1));
					return c_uptr(new MoveCommand(_player, _level, -1, 1));
				case 'n':
					if(in.shift)
						return c_uptr(new AttackCommand(_player, 1, 1));
					return c_uptr(new MoveCommand(_player, _level, 1, 1));
				case 'q':
					return c_uptr(new QuitCommand(_is_running));
			}
		default:
			return nullptr;
	}
}
