#ifndef system_h
#define system_h

#include <vector>
#include <map>
#include <memory>
#include <typeindex>

#include "entity.h"
#include "event.h"

using namespace std;

class System 
{
public:
	System(void) {};
	virtual ~System(void) {};

	virtual void update(const EventManager& evm) = 0;
	
	virtual void add_entity(const shared_ptr<Entity>& entity)
	{
		_entities.push_back(entity);
	}

protected:
	vector<weak_ptr<Entity>> _entities;
};

class SystemManager
{
public:
	explicit SystemManager(EventManager& evm) : _event_manager(evm) {}

	typedef map<type_index, shared_ptr<System>>::iterator system_iterator;

	template<class S>
	void add(shared_ptr<S> system)
	{
		_systems[typeid(S)] = system;
	}

	void update(void)
	{
		for(system_iterator it = _systems.begin(); it != _systems.end(); it++)
		{
			(*it).second->update(_event_manager);
		}
	}

private:
	EventManager& _event_manager;
	map<type_index, shared_ptr<System>> _systems;
};

#endif
