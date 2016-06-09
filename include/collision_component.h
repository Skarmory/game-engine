#ifndef collision_component_h
#define collision_component_h

#include "component.h"

struct CollisionComponent : public Component
{
	// Will eventually contain some data to determine which other collidable entities it collides with

	CollisionComponent(void) : Component("CollisionComponent") {}
	~CollisionComponent(void) {}
};

#endif
