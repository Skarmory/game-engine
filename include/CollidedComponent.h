#ifndef collided_component_h
#define collided_component_h

#include "component.h"
#include "entity.h"

struct CollidedComponent : public Component
{
	CollidedComponent(Entity const& collided_with) : 
		Component("CollidedComponent"), collided_with(collided_with)

	Entity const& collided_with;
};

#endif
