#ifndef command_h
#define command_h

#include <memory>
#include <ncurses.h>
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
	MoveCommand(std::weak_ptr<Entity>, int, int);
	virtual void execute(void);

private:
	std::weak_ptr<Entity> _entity;
	int _x, _y;
};

class QuitCommand : public ICommand
{
public:
	QuitCommand(bool&);
	virtual void execute(void);
private:
	bool& _state;
};

class Debug_KillPlayerCommand : public ICommand
{
public:
	Debug_KillPlayerCommand(std::shared_ptr<Entity>&);
	virtual void execute(void);
private:
	std::shared_ptr<Entity>& _entity;
};

}
#endif
