#ifndef light_h
#define light_h

#include "component.h"

struct LightSource : public Component<LightSource>
{
	explicit LightSource(int radius, bool occludes) : radius(radius), dropoff(1.0f/radius), occludes(occludes) {}

	int radius;
	float dropoff;
	bool occludes;
};

#endif
