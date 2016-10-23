#ifndef light_h
#define light_h

#include "component.h"

const float MIN_LIGHT_PERCENT = 0.1f;
const float MAX_LIGHT_PERCENT = 1.0f;

struct LightSource : public Component
{
	LightSource(int radius) : radius(radius), dropoff(1.0f/radius) {}

	int radius;
	float dropoff;
};

#endif
