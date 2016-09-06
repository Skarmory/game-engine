#ifndef location_component_h
#define location_component_h

#include "component.h"

struct Location : public Component
{
	Location() : Component("LocationComponent"), x(0), y(0) {}
	Location(int x, int y) : Component("LocationComponent"), x(x), y(y) {}

	int x, y;
};

#endif
