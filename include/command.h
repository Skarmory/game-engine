#ifndef command_h
#define command_h

#include "entity.h"
#include "location_component.h"

namespace Command {

class ICommand
{
public:
	virtual ~ICommand() {}
	virtual void execute(void) = 0;
};

class MoveCommand : public ICommand
{
public:
	MoveCommand(Entity* entity, int x, int y);
	virtual void execute(void);

private:
	Entity* _entity;
	int _x, _y;
};

class QuitCommand : public ICommand
{
public:
	QuitCommand(bool& game_state);
	virtual void execute(void);
private:
	bool& _state;
};

}
#endif
