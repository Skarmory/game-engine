#ifndef input_h
#define input_h

#include <ncurses.h>
#include "command.h"

class InputManager {
public:
	InputManager(Entity*, bool&);
	Command::ICommand* handle_input(void);
private:
	Entity* _player;
	bool& _is_running;
};

#endif
