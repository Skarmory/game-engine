#ifndef light_h
#define light_h

#include "component.h"

struct LightSource : public Component
{
	LightSource(int radius, int dropoff) : radius(radius), dropoff(dropoff) {}

	int radius;
	int dropoff;
};

#endif
