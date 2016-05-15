#ifndef location_component_h
#define location_component_h

#include "component.h"

struct LocationComponent : public Component
{
	LocationComponent(int x, int y);
	~LocationComponent(void);

	int x, y;
};

#endif
