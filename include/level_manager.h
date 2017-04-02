#ifndef level_manager_h
#define level_manager_h

#include "level.h"
#include "events.h"

class LevelManager : public sov::Observer<LevelTransitionEvent>
{
public:
	explicit LevelManager(void);
	virtual ~LevelManager(void);

	void load(const string& name);

	Level& get_current(void) const;
	
	void receive(const LevelTransitionEvent& e);

private:
	const string _path = "resources/levels/";
	Level* _current;
	map<string, Level*> _levels;

	void _load(const string& name);
};
#endif
