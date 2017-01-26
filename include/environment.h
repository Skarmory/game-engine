#ifndef environment_h
#define environment_h

#include "entity_manager.h"
#include "event.h"
#include "input.h"
#include "level_manager.h"
#include "system.h"

// This class is an access point for all the managers in the game

class Environment
{
	static Environment* env;

	EntityManager* _entity_manager;
	InputManager* _input_manager;
	SystemManager* _system_manager;
	EventManager* _event_manager;
	LevelManager* _level_manager;

public:
	explicit Environment(void);
	~Environment(void);

	void set_entity_manager(EntityManager* entity_manager);
	void set_system_manager(SystemManager* system_manager);
	void set_event_manager(EventManager* event_manager);
	void set_level_manager(LevelManager* level_manager);
	void set_input_manager(InputManager* input_manager);

	EntityManager* get_entity_manager(void) const;
	SystemManager* get_system_manager(void) const;
	EventManager* get_event_manager(void) const;
	LevelManager* get_level_manager(void) const;
	InputManager* get_input_manager(void) const;

	static const Environment& get(void);
};

#endif