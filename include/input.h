#ifndef input_h
#define input_h

#include <ncurses.h>
#include <memory>
#include "command.h"

class InputManager {
public:
	InputManager(std::shared_ptr<Entity>&, std::shared_ptr<Level>, bool&);
	std::unique_ptr<Command::ICommand> handle_input(void);
private:
	std::shared_ptr<Entity>& _player;
	std::shared_ptr<Level> _level;
	bool& _is_running;
};

#endif
