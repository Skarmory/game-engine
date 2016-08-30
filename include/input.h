#ifndef input_h
#define input_h

#include "libtcod.hpp"

#include <memory>
#include "command.h"

using namespace std;
using namespace Command;

class InputManager {
public:
	InputManager(shared_ptr<Entity>&, shared_ptr<Level>, bool&);
	unique_ptr<ICommand> handle_input(void);
private:
	shared_ptr<Entity>& _player;
	shared_ptr<Level> _level;
	bool& _is_running;
};

#endif
