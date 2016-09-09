#include "input.h"
using namespace Command;

typedef std::unique_ptr<ICommand> c_uptr;

InputManager::InputManager(
		const std::shared_ptr<Entity>& player, 
		const Level& level, 
		bool& is_running, 
		EntityManager& entity_manager) 
	: _player(player),_level(level), _is_running(is_running), _entity_manager(entity_manager) 
{}

c_uptr InputManager::handle_input(void)
{
	TCOD_key_t in;
	TCODSystem::checkForEvent(TCOD_EVENT_KEY, &in, NULL);
	
	if(in.pressed)
	{
		switch(in.vk)
		{
			case TCODK_CHAR:
				switch(in.c)
				{
					case 'h':
						return c_uptr(new MoveCommand(_player, _level, -1, 0));
					case 'j':
						return c_uptr(new MoveCommand(_player, _level,  0, 1));
					case 'k':
						return c_uptr(new MoveCommand(_player, _level, 0, -1));
					case 'l':
						return c_uptr(new MoveCommand(_player, _level, 1, 0));
					case 'y':
						return c_uptr(new MoveCommand(_player, _level, -1, -1));
					case 'u':
						return c_uptr(new MoveCommand(_player, _level, 1, -1));
					case 'b':
						return c_uptr(new MoveCommand(_player, _level, -1, 1));
					case 'n':
						return c_uptr(new MoveCommand(_player, _level, 1, 1));
					case 'H':
						return c_uptr(new AttackCommand(_entity_manager, _player, -1, 0));
					case 'J':
						return c_uptr(new AttackCommand(_entity_manager, _player, 0, 1));
					case 'K':
						return c_uptr(new AttackCommand(_entity_manager, _player, 0, -1));
					case 'L':
						return c_uptr(new AttackCommand(_entity_manager, _player, 1, 0));
					case 'Y':
						return c_uptr(new AttackCommand(_entity_manager, _player, -1, -1));
					case 'U':
						return c_uptr(new AttackCommand(_entity_manager, _player, 1, -1));
					case 'B':
						return c_uptr(new AttackCommand(_entity_manager, _player, -1, 1));
					case 'N':
						return c_uptr(new AttackCommand(_entity_manager, _player, 1, 1));
					case 'q':
						return c_uptr(new QuitCommand(_is_running));
				}
			default:
				return nullptr;
		}
	}

	return nullptr;
}
