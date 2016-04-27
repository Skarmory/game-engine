#include "entity.h"

static int _NEXT_ID = 0;

Entity::Entity(int id) : _id(id)
{
	//_components = new std::map<const std::string, Component*>;
}

Entity::~Entity(void)
{
	//for(std::map<std::string, Component*>::iterator it = _components->begin(); it != _components->end(); it++)
	//	_components->erase(it);

	//delete _components;
}

void Entity::add_component(Component* component)
{
	_components[component->name()] = component;	
}

const Component* Entity::get_component(std::string name)
{
	assert(name.length() > 0);

	return _components[name];
}
