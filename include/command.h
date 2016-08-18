#ifndef command_h
#define command_h

#include <memory>
#include "entity.h"
#include "level.h"
#include "location_component.h"

namespace Command 
{

class ICommand
{
public:
	virtual ~ICommand() {}
	virtual void execute(void) = 0;
};

class MoveCommand : public ICommand
{
public:
	MoveCommand(std::weak_ptr<Entity>, std::weak_ptr<Level>, int, int);
	virtual void execute(void);

private:
	std::weak_ptr<Entity> _entity;
	std::weak_ptr<Level> _level;
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

class AttackCommand : public ICommand
{
public:
	AttackCommand(std::weak_ptr<Entity>, int, int);
	virtual void execute(void);
private:
	std::weak_ptr<Entity> _attacker;
	int _x, _y;
};

}
#endif
