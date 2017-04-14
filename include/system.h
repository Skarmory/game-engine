#ifndef system_h
#define system_h

#include <vector>
#include <unordered_map>
#include <memory>
#include <typeindex>

#include "entity.h"

class System 
{
public:
	explicit System(void) {};
	virtual ~System(void) {};
	
	virtual void init(void) = 0;
	virtual void update(void) = 0;
	
	virtual void add_entity(Entity* entity)
	{
		_entities.push_back(entity);
	}

protected:
	std::vector<Entity*> _entities;
};

class SystemManager
{
public:
	explicit SystemManager(void) {}

	void init(void)
	{
		for(auto& system : _systems)
			system.second->init();
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
	void create(void)
	{
		_systems[typeid(S)] = make_shared<S>();
	}

	template<class S>
	void update(void)
	{
		_systems[typeid(S)]->update();
	}

	void update(void)
	{
		for(auto& system : _systems)
			system.second->update();
	}

	template<class S>
	const S& get(void) const
	{
		return *static_pointer_cast<const S>(_systems.at(typeid(S)));
	}

private:
	std::unordered_map<std::type_index, std::shared_ptr<System>> _systems;
};

#endif
