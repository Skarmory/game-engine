#ifndef entity_h
#define entity_h

#include <stdlib.h>
#include <memory>
#include <map>
#include <string>
#include <assert.h>
#include <typeindex>
#include "component.h"

class Entity {
public:
	Entity(int _id);
	~Entity(void);

	void add_component(const std::shared_ptr<Component>& c)
	{
		_components[typeid(*c)] = c;
	}

	template<class T>
	void remove_component(void)
	{
		_components.erase(typeid(T));
	}

	template<class T>
	std::shared_ptr<T> get_component(void)
	{
		return std::static_pointer_cast<T>(_components[typeid(T)]);
	}

	template<class T>
	const std::shared_ptr<const T> get_component(void) const
	{
		return std::static_pointer_cast<const T>(_components.at(typeid(T)));
	}

	template<class T>
	bool has_component(void)
	{
		return _components.find(typeid(T)) != _components.end();
	}

private:

	int _id;
	std::map<std::type_index, std::shared_ptr<Component>> _components;
};

#endif
