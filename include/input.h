#ifndef input_h
#define input_h

#include <memory>
#include <SFML/Window.hpp>

#include "command.h"
#include "level.h"
#include "entity.h"
#include "entity_manager.h"

using namespace std;

class InputManager
{
public:
	InputManager(
		sf::Window& handle,
		LevelManager& level_manager, 
		bool& is_running, 
		EntityManager& entity_manager,
		EventManager& event_manager
	);
	unique_ptr<Command> handle_input(void);

private:
	sf::Window& _handle;
	LevelManager& _level_manager;
	bool& _is_running;
	EntityManager& _entity_manager;
	EventManager& _event_manager;
};

#endif
