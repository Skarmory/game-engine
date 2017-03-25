#include "input.h"

typedef std::unique_ptr<Command> c_uptr;

InputManager::InputManager(sf::Window& handle, bool& is_running) : _handle(handle), _is_running(is_running)
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
				return c_uptr(new MoveCommand(-0.5, 0));
			case 'j':
				return c_uptr(new MoveCommand(0, 0.5));
			case 'k':
				return c_uptr(new MoveCommand(0, -0.5));
			case 'l':
				return c_uptr(new MoveCommand(0.5, 0));
			case 'y':
				return c_uptr(new MoveCommand(-0.5, -0.5));
			case 'u':
				return c_uptr(new MoveCommand(0.5, -0.5));
			case 'b':
				return c_uptr(new MoveCommand(-0.5, 0.5));
			case 'n':
				return c_uptr(new MoveCommand(0.5, 0.5));
			case 'H':
				return c_uptr(new AttackCommand(-1, 0));
			case 'J':
				return c_uptr(new AttackCommand(0, 1));
			case 'K':
				return c_uptr(new AttackCommand(0, -1));
			case 'L':
				return c_uptr(new AttackCommand(1, 0));
			case 'Y':
				return c_uptr(new AttackCommand(-1, -1));
			case 'U':
				return c_uptr(new AttackCommand(1, -1));
			case 'B':
				return c_uptr(new AttackCommand(-1, 1));
			case 'N':
				return c_uptr(new AttackCommand(1, 1));
			case 'q':
				return c_uptr(new QuitCommand(_is_running));
			case '>':
			case '<':
				return c_uptr(new LevelTransitionCommand());
			default:
				return nullptr;
		}
	}
	else if (event.type == sf::Event::Closed)
	{
		//return c_uptr(new QuitCommand(_is_running));
	}

	return nullptr;
}
