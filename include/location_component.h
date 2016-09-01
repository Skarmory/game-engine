#ifndef location_component_h
#define location_component_h

#include "component.h"

struct LocationComponent : public Component
{
	LocationComponent() : Component("LocationComponent"), x(0), y(0) {}
	LocationComponent(int x, int y);
	~LocationComponent(void);

	int x, y;
};

#endif
