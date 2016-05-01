#ifndef location_component_h
#define location_component_h

#include "component.h"

class LocationComponent : virtual public Component
{
public:
	LocationComponent(int x, int y);

	int x(void) const;
	int y(void) const;

private:
	int _x, _y;
};

#endif
