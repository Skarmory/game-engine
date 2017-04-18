#ifndef light_h
#define light_h

#include "component.h"

struct LightSource : public Component<LightSource>
{
	explicit LightSource(int radius) : radius(radius), dropoff(1.0f/radius) {}

	int radius;
	float dropoff;
};

#endif
