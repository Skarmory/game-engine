#ifndef location_component_h
#define location_component_h

#include "component.h"

struct Location : public Component<Location>
{
	explicit Location(void) : x(0), y(0), z(0) {}
	explicit Location(int x, int y, int z) : x(x), y(y), z(z) {}

	float x, y, z;
};

#endif
