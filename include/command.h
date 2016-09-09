#ifndef command_h
#define command_h

#include <memory>
#include "entity.h"
#include "entity_manager.h"
#include "level.h"
#include "components.h"

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
	MoveCommand(std::weak_ptr<Entity>, const Level&, int, int);
	virtual void execute(void) override;

private:
	std::weak_ptr<Entity> _entity;
	const Level& _level;
	int _x, _y;
};

class QuitCommand : public ICommand
{
public:
	QuitCommand(bool&);
	virtual void execute(void) override;
private:
	bool& _state;
};

class AttackCommand : public ICommand
{
public:
	AttackCommand(EntityManager& entity_manager, std::weak_ptr<Entity>, int x, int y);
	virtual void execute(void) override;
private:
	EntityManager& _entity_manager;
	std::weak_ptr<Entity> _attacker;
	int _x, _y;
};

}
#endif
