#ifndef system_h
#define system_h

#include <vector>
#include <map>
#include <memory>
#include <typeindex>

#include "entity.h"
#include "event.h"

using namespace std;

typedef vector<weak_ptr<Entity>>::iterator entity_iterator;

class SystemManager;

class System 
{
public:
	System(const SystemManager& system_manager) : _system_manager(system_manager) {};
	virtual ~System(void) = default;

	virtual void init(sov::EventManager& evm) = 0;
	virtual void update(sov::EventManager& evm) = 0;
	
	virtual void add_entity(const shared_ptr<Entity>& entity)
	{
		_entities.push_back(entity);
	}

protected:
	vector<weak_ptr<Entity>> _entities;
	const SystemManager& _system_manager;
};

class SystemManager
{
public:
	explicit SystemManager(sov::EventManager& evm) : _event_manager(evm) {}

	typedef map<type_index, shared_ptr<System>>::iterator system_iterator;

	void init(void)
	{
		for(auto& system : _systems)
			system.second->init(_event_manager);
	}

	template<class S>
	void add(shared_ptr<S> system)
	{
		_systems[typeid(S)] = system;
	}

	template<class S, class ... Args>
	void create(Args&& ... args)
	{
		_systems[typeid(S)] = make_shared<S>(forward<Args>(args) ...);
	}

	template<class S>
	void update(void)
	{
		_systems[typeid(S)]->update(_event_manager);
	}

	void update(void)
	{
		for(auto& system : _systems)
			system.second->update(_event_manager);
	}

	template<class S>
	const S& get(void) const
	{
		return *static_pointer_cast<const S>(_systems.at(typeid(S)));
	}

private:
	sov::EventManager& _event_manager;
	map<type_index, shared_ptr<System>> _systems;
};

#endif
