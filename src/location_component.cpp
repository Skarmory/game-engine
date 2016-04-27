#include "location_component.h"

LocationComponent::LocationComponent(int x, int y) : Component("LocationComponent"), _x(x), _y(y) 
{
}

int LocationComponent::x(void) const
{
	return _x;
}

int LocationComponent::y(void) const
{
	return _y;
}

