#ifndef collision_component_h
#define collision_component_h

#include "component.h"

struct Collision : public Component
{
	// Will eventually contain some data to determine which other collidable entities it collides with

	Collision(void) = default;
};

#endif
