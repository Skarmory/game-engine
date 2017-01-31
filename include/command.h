#ifndef command_h
#define command_h

class Command
{
public:
	virtual ~Command() = default;
	virtual void execute(void) = 0;
};

class MoveCommand : public Command
{
public:
	explicit MoveCommand(int x, int y);
	virtual void execute(void) override;

private:
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
	explicit AttackCommand(int x, int y);
	virtual void execute(void) override;

private:
	int _x, _y;
};

class LevelTransitionCommand : public Command
{
public:
	explicit LevelTransitionCommand(void);
	virtual void execute(void) override;
};

#endif
