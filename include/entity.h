#ifndef entity_h
#define entity_h

#include <memory>
#include <unordered_map>
#include <string>
#include <typeindex>

#include "component.h"

using namespace std;

class Entity {
public:
	explicit Entity(int id) : obsolete(false), _id(id) {}
	~Entity(void)
	{
		for (auto& elem : _components)
			delete elem.second;
	}

	Entity clone(void)
	{
		Entity e(-1);

		for (const auto& elem : _components)
		{
			BaseComponent* b = elem.second->clone();
			e._components.insert(std::make_pair(elem.first, b));
		}

		return e;
	}

	// Add component to the entity
	void add_component(BaseComponent* c)
	{
		_components[typeid(*c)] = c;
	}

	// Remove component from entity
	template<class T>
	void remove_component(void)
	{
		_components.erase(typeid(T));
	}

	template<class T>
	T* get_component(void)
	{
		if(has_component<T>())
			return static_cast<T*>(_components.at(typeid(T)));
		
		return nullptr;
	}

	// Return const pointer to const component
	template<class T>
	const T const* get_component(void) const
	{
		if(has_component<T>())
			return static_cast<const T const*>(_components.at(typeid(T)));

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
	std::unordered_map<std::type_index, BaseComponent*> _components;

	friend class EntityManager;
};

#endif
