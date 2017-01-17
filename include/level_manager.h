#ifndef level_manager_h
#define level_manager_h

#include <random>
#include <sstream>
#include <fstream>

#include "level.h"
#include "events.h"
#include "entity_manager.h"

class LevelManager : public Observer<LevelTransitionEvent>
{
public:
	explicit LevelManager(EventManager& evm);
	virtual ~LevelManager(void);

	void load(const string& name);

	Level& get_current(void) const;
	
	void receive(const LevelTransitionEvent& e);

private:
	const string _path = "resources/levels/";
	Level* _current;
	map<string, Level*> _levels;
	EventManager& _event_manager;

	void _load(const string& name);
};

#endif
