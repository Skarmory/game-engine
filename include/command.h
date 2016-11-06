#ifndef command_h
#define command_h

#include <memory>
#include "entity.h"
#include "entity_manager.h"
#include "level.h"
#include "components.h"


class Command
{
public:
	virtual ~Command() = default;
	virtual void execute(void) = 0;
};

class MoveCommand : public Command
{
public:
	MoveCommand(std::weak_ptr<Entity>, const Level&, int, int);
	virtual void execute(void) override;

private:
	std::weak_ptr<Entity> _entity;
	const Level& _level;
	int _x, _y;
};

class QuitCommand : public Command
{
public:
	QuitCommand(bool&);
	virtual void execute(void) override;

private:
	bool& _state;
};

class AttackCommand : public Command
{
public:
	AttackCommand(EntityManager& entity_manager, std::weak_ptr<Entity>, int x, int y);
	virtual void execute(void) override;

private:
	EntityManager& _entity_manager;
	std::weak_ptr<Entity> _attacker;
	int _x, _y;
};

#endif
