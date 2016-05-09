#ifndef entity_h
#define entity_h

#include <map>
#include <string>
#include <assert.h>
#include "component.h"

class Entity {
public:
	Entity(int _id);
	~Entity(void);

	void	   add_component(Component* component);
	Component* get_component(std::string name);

private:

	int _id;
	std::map<const std::string, Component*> _components;
};

#endif
