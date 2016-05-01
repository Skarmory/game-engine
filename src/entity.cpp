#include "entity.h"


Entity::Entity(int id) : _id(id)
{
}

Entity::~Entity(void)
{
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
