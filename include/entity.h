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
	std::shared_ptr<T> get_component(void)
	{
		return std::static_pointer_cast<T>(_components[typeid(T)]);
	}

private:

	int _id;
	std::map<std::type_index, std::shared_ptr<Component>> _components;
};

#endif
