#ifndef entity_h
#define entity_h

#include <stdlib.h>
#include <memory>
#include <map>
#include <vector>
#include <string>
#include <assert.h>
#include <typeindex>
#include "component.h"

using namespace std;

class Entity {
public:
	explicit Entity(int id) : obsolete(false), _id(id) {}
	Entity(const Entity& entity)
	{
		_id = -1;

		for (const auto& elem : entity._components)
		{
			BaseComponent* b = elem.second->clone();
			_components.insert(make_pair(elem.first, shared_ptr<BaseComponent>(b)));
		}
	}

	// Add component to the entity
	void add_component(const shared_ptr<BaseComponent> c)
	{
		_components[typeid(*c)] = c;
	}

	// Remove component from entity
	template<class T>
	void remove_component(void)
	{
		_components.erase(typeid(T));
	}

	// Return const pointer to component
	template<class T>
	const shared_ptr<T> get_component(void)
	{
		if(has_component<T>())
			return static_pointer_cast<T>(_components.at(typeid(T)));
		
		return nullptr;
	}

	// Return const pointer to const component
	template<class T>
	const shared_ptr<const T> get_component(void) const
	{
		if(has_component<T>())
			return static_pointer_cast<const T>(_components.at(typeid(T)));

		return nullptr;
	}
	
	// Check to see whether the entity has component T
	template<class T>
	bool has_component(void)
	const
	{
		if(_components.find(typeid(T)) != _components.end())
			return true;
		return false;
	}

	int get_id(void) const
	{
		return _id;
	}

	bool obsolete;
private:

	int _id;
	map<type_index, shared_ptr<BaseComponent>> _components;

	friend class EntityManager;
};

#endif
