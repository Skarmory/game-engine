#ifndef input_h
#define input_h

#include <memory>
#include <SFML/Window.hpp>

#include "command.h"

class InputManager
{
public:
	InputManager(sf::Window& handle, bool& is_running);

	std::unique_ptr<Command> handle_input(void);

private:
	sf::Window& _handle;
	bool& _is_running;
};

#endif
