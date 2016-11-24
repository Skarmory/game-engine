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
		const shared_ptr<Entity>& player, 
		const Level& level, 
		bool& is_running, 
		EntityManager& entity_manager
	);
	unique_ptr<Command> handle_input(void);

private:
	sf::Window& _handle;
	const shared_ptr<Entity>& _player;
	const Level& _level;
	bool& _is_running;
	EntityManager& _entity_manager;
};

#endif
