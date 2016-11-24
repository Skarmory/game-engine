#include "input.h"

typedef std::unique_ptr<Command> c_uptr;

InputManager::InputManager(
		sf::Window& handle,
		const std::shared_ptr<Entity>& player, 
		const Level& level, 
		bool& is_running, 
		EntityManager& entity_manager) 
	: _handle(handle), _player(player),_level(level), _is_running(is_running), _entity_manager(entity_manager) 
{}

c_uptr InputManager::handle_input(void)
{	
	sf::Event event;

	_handle.pollEvent(event);

	if(event.type == sf::Event::TextEntered)
	{
		switch(event.text.unicode)
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
			default:
				return nullptr;
		}
	}
	else if(event.type == sf::Event::Closed)
		return c_uptr(new QuitCommand(_is_running));

	return nullptr;
}
