#ifndef command_h
#define command_h

#include <memory>
#include "entity.h"
#include "entity_manager.h"
#include "level_manager.h"
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
	explicit MoveCommand(EntityManager& entity_manager, LevelManager& level_manager, int x, int y);
	virtual void execute(void) override;

private:
	EntityManager& _entity_manager;
	LevelManager& _level_manager;
	int _x, _y;
};

class QuitCommand : public Command
{
public:
	explicit QuitCommand(bool& running);
	virtual void execute(void) override;

private:
	bool& _state;
};

class AttackCommand : public Command
{
public:
	explicit AttackCommand(EntityManager& entity_manager, int x, int y);
	virtual void execute(void) override;

private:
	EntityManager& _entity_manager;
	int _x, _y;
};

class LevelTransitionCommand : public Command
{
public:
	explicit LevelTransitionCommand(EntityManager& entity_manager);
	virtual void execute(void) override;

private:
	EntityManager& _entity_manager;
};

#endif
